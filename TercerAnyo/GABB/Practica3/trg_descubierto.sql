
-- EJERCICIO 1. Disparador TRG_DESCUBIERTO

-- a) Crear y compilar el disparador
CREATE OR REPLACE TRIGGER trg_descubierto
BEFORE UPDATE OF balance ON account
FOR EACH ROW
WHEN (new.balance < old.balance)          -- solo cuando sale dinero
BEGIN
    -- Saldo mínimo permitido: -10 % del saldo que había antes de retirar.
    -- Ej.: saldo 1000 -> se pueden retirar hasta 1100 (saldo final -100).
    IF :new.balance < -0.10 * :old.balance THEN
        RAISE_APPLICATION_ERROR(-20000,
            'No se puede retirar un saldo superior al 110% del saldo actual');
    END IF;
END;
/

-- Comproba
SELECT line, position, text
FROM   user_errors
WHERE  name = 'TRG_DESCUBIERTO';

-- b) Actualizar la cuenta ING de un cliente dejando un descubierto > 10 %

-- Cuentas ING con saldo positivo
SELECT a.id, a.balance
FROM   account a
JOIN   ing_account i ON i.id = a.id
WHERE  a.balance > 0
ORDER  BY a.id;

-- Retirar el 120 % del saldo de la primera cuenta ING con saldo positivo
UPDATE account
SET    balance = balance - 1.2 * balance
WHERE  id = (SELECT MIN(a.id)
             FROM   account a
             JOIN   ing_account i ON i.id = a.id
             WHERE  a.balance > 0);


-- EJERCICIO 2. Transferencia de X a Y y transacciones

-- Cuentas elegidas:
--   X = cuenta 14 (cuenta ING; según el ejercicio 5 tiene 10 eur, > 0)
--   Y = cuenta asociada del registro titular-cuenta ("OwnerAsAc-AsAc") 8
--   La operación D se registra con el Cli-Acc de la cuenta X y el
--   titular-cuenta 8 como destino.
--   Código de operación: 900, para no chocar con el 21 del ejercicio 5.
-- Para usar otras cuentas basta con cambiar 14 y 8 en todo el bloque.

-- Comprobar las cuentas elegidas (X debe tener saldo positivo)
SELECT 'X' AS cuenta, id, balance
FROM   account
WHERE  id = 14
UNION ALL
SELECT 'Y', id, balance
FROM   account
WHERE  id = (SELECT associated_account_id FROM "OwnerAsAc-AsAc" WHERE id = 8);


-- a) Iniciar la transacción
COMMIT;

-- b) Insertar la operación D: transferir el doble del saldo de X a Y
INSERT INTO operation (cod_op, "date", "Cli-Acc_id")
VALUES (900, SYSDATE, (SELECT MIN(id) FROM "Cli-Acc" WHERE ing_account_id = 14));

INSERT INTO op_d (cod_op, amount, periodicity, "OwnerAsAc-AsAc_id")
VALUES (900, (SELECT 2 * balance FROM account WHERE id = 14), 'once', 8);

-- c) Comprobar que la inserción se ha realizado
SELECT o.cod_op, o."date", o."Cli-Acc_id", d.amount, d.periodicity
FROM   operation o
JOIN   op_d d ON d.cod_op = o.cod_op
WHERE  o.cod_op = 900;

-- d) Incrementar Y con el doble del saldo de X
UPDATE account
SET    balance = balance + (SELECT 2 * balance FROM account WHERE id = 14)
WHERE  id = (SELECT associated_account_id FROM "OwnerAsAc-AsAc" WHERE id = 8);

-- e) Comprobar que la actualización se ha realizado
SELECT id, balance
FROM   account
WHERE  id = 14
   OR  id = (SELECT associated_account_id FROM "OwnerAsAc-AsAc" WHERE id = 8);

-- f) Decrementar X con el doble de su saldo -> salta TRG_DESCUBIERTO
UPDATE account
SET    balance = balance - 2 * balance
WHERE  id = 14;

-- Ver qué ha quedado
SELECT id, balance
FROM   account
WHERE  id = 14
   OR  id = (SELECT associated_account_id FROM "OwnerAsAc-AsAc" WHERE id = 8);

SELECT * FROM op_d WHERE cod_op = 900;

-- ---------------------------------------------------------------------
-- i) ¿Qué ha ocurrido con X, Y y la operación "D"? ¿Por qué?
--
-- El paso f falla: X quedaría en -100 % de su saldo y el disparador lanza
-- ORA-20000. X no cambia, pero la operación D (900) sigue insertada en
-- OPERATION y OP_D y la cuenta Y sigue incrementada.
--
-- Motivo: el cliente (SQL*Plus, SQL Developer, DataGrip) ejecuta cada
-- sentencia con un SAVEPOINT implícito delante. Cuando una sentencia
-- falla, Oracle deshace solo esa sentencia (vuelve a su savepoint), no la
-- transacción completa. Las sentencias anteriores siguen pendientes de
-- confirmar, y la BD queda en un estado incoherente: el dinero aparece en
-- Y sin haber salido de X. Si ahora se hiciera COMMIT, ese estado quedaría
-- grabado; con ROLLBACK se deshace todo.
-- ---------------------------------------------------------------------

ROLLBACK;     -- deshacer la prueba


-- =====================================================================
-- ii) Repetir el proceso con un COMMIT justo antes del paso f
-- =====================================================================
COMMIT;

INSERT INTO operation (cod_op, "date", "Cli-Acc_id")
VALUES (900, SYSDATE, (SELECT MIN(id) FROM "Cli-Acc" WHERE ing_account_id = 14));

INSERT INTO op_d (cod_op, amount, periodicity, "OwnerAsAc-AsAc_id")
VALUES (900, (SELECT 2 * balance FROM account WHERE id = 14), 'once', 8);

SELECT o.cod_op, o."date", o."Cli-Acc_id", d.amount, d.periodicity
FROM   operation o
JOIN   op_d d ON d.cod_op = o.cod_op
WHERE  o.cod_op = 900;

UPDATE account
SET    balance = balance + (SELECT 2 * balance FROM account WHERE id = 14)
WHERE  id = (SELECT associated_account_id FROM "OwnerAsAc-AsAc" WHERE id = 8);

SELECT id, balance
FROM   account
WHERE  id = 14
   OR  id = (SELECT associated_account_id FROM "OwnerAsAc-AsAc" WHERE id = 8);

COMMIT;       -- confirma los pasos b-e

UPDATE account                 -- f) -> ORA-20000
SET    balance = balance - 2 * balance
WHERE  id = 14;

ROLLBACK;     -- ya no deshace nada: b-e están confirmados

SELECT id, balance
FROM   account
WHERE  id = 14
   OR  id = (SELECT associated_account_id FROM "OwnerAsAc-AsAc" WHERE id = 8);

SELECT * FROM op_d WHERE cod_op = 900;

-- ---------------------------------------------------------------------
-- ii) ¿Obtienes el mismo resultado? ¿Por qué?
--
-- Se ve lo mismo que en i): la operación D insertada, Y incrementada y X
-- sin cambios. La diferencia es que ahora es definitivo. El COMMIT previo
-- al paso f confirmó la inserción de la operación y el ingreso en Y, y
-- cuando f falla solo se deshace f. Ni siquiera un ROLLBACK posterior
-- puede ya deshacer los pasos confirmados, de modo que la incoherencia
-- (dinero en Y que no ha salido de X) queda grabada en la BD.
-- El COMMIT parte en dos lo que debería ser una única unidad de trabajo.
-- ---------------------------------------------------------------------

-- Limpieza: operación compensatoria para dejar los datos como estaban
UPDATE account
SET    balance = balance - (SELECT amount FROM op_d WHERE cod_op = 900)
WHERE  id = (SELECT associated_account_id FROM "OwnerAsAc-AsAc" WHERE id = 8);

DELETE FROM op_d      WHERE cod_op = 900;
DELETE FROM operation WHERE cod_op = 900;
COMMIT;


-- =====================================================================
-- iii) Repetir el proceso desde el paso b dentro de un bloque PL/SQL
-- Para ver los mensajes:
--   DataGrip: activar DBMS_OUTPUT con el botón de la barra de la consola
--   SQL Developer / SQL*Plus: SET SERVEROUTPUT ON
-- =====================================================================
COMMIT;

DECLARE
    v_x       account.id%TYPE := 14;
    v_oa      "OwnerAsAc-AsAc".id%TYPE := 8;
    v_y       account.id%TYPE;
    v_importe account.balance%TYPE;
    v_saldo_y account.balance%TYPE;
    v_n       NUMBER;
BEGIN
    SELECT associated_account_id INTO v_y FROM "OwnerAsAc-AsAc" WHERE id = v_oa;
    SELECT 2 * balance INTO v_importe FROM account WHERE id = v_x;

    -- b) Insertar la operación D
    INSERT INTO operation (cod_op, "date", "Cli-Acc_id")
    VALUES (900, SYSDATE, (SELECT MIN(id) FROM "Cli-Acc" WHERE ing_account_id = v_x));

    INSERT INTO op_d (cod_op, amount, periodicity, "OwnerAsAc-AsAc_id")
    VALUES (900, v_importe, 'once', v_oa);

    -- c) Comprobar la inserción
    SELECT COUNT(*) INTO v_n FROM op_d WHERE cod_op = 900;
    DBMS_OUTPUT.PUT_LINE('Operaciones D insertadas: ' || v_n);

    -- d) Incrementar Y
    UPDATE account SET balance = balance + v_importe WHERE id = v_y;

    -- e) Comprobar la actualización
    SELECT balance INTO v_saldo_y FROM account WHERE id = v_y;
    DBMS_OUTPUT.PUT_LINE('Nuevo saldo de Y: ' || v_saldo_y);

    -- f) Decrementar X -> ORA-20000
    UPDATE account SET balance = balance - v_importe WHERE id = v_x;
END;
/

-- Ver qué ha quedado
SELECT id, balance
FROM   account
WHERE  id = 14
   OR  id = (SELECT associated_account_id FROM "OwnerAsAc-AsAc" WHERE id = 8);

SELECT * FROM op_d WHERE cod_op = 900;

-- ---------------------------------------------------------------------
-- iii) ¿Obtienes el mismo resultado? ¿Por qué?
--
-- No. Ahora no queda nada: ni la operación D, ni el ingreso en Y, ni
-- cambios en X. El cliente envía el bloque PL/SQL completo como una única
-- sentencia, así que el savepoint implícito está antes del bloque. Como la
-- excepción del disparador no se trata dentro del bloque, se propaga
-- fuera y Oracle deshace todo lo que hizo el bloque: se comporta de forma
-- atómica (todo o nada), que es lo correcto para una transferencia.
--
-- Matiz (documento anexo): si el bloque tuviera una sección
-- "EXCEPTION WHEN OTHERS THEN NULL;", la excepción se daría por tratada
-- y los pasos b-d SÍ se mantendrían. Para capturar excepciones y conservar
-- la atomicidad se pone un SAVEPOINT al principio del bloque y un
-- ROLLBACK TO SAVEPOINT en el manejador de la excepción.
-- ---------------------------------------------------------------------

ROLLBACK;


-- ---------------------------------------------------------------------
-- iv) ¿Es indispensable crear un disparador para realizar esta
--     comprobación de integridad? Justifica la respuesta.
--
-- No es estrictamente indispensable, pero sí la opción más adecuada.
--
-- * No puede hacerse con una restricción CHECK: la regla compara el saldo
--   nuevo con el saldo ANTERIOR de la misma fila, y un CHECK solo ve los
--   valores de la fila resultante. Un CHECK serviría para un límite fijo
--   (p. ej. balance >= -500), no para uno relativo al saldo previo.
--
-- * Se podría comprobar fuera de un disparador: en la aplicación, o en un
--   procedimiento almacenado por el que pasaran todas las retiradas (por
--   ejemplo, UPDATE ... WHERE balance - importe >= -0.10 * balance y
--   comprobar SQL%ROWCOUNT), quitando a los usuarios el permiso de UPDATE
--   directo sobre ACCOUNT.
--
-- * Pero esas alternativas dependen de que todas las modificaciones pasen
--   por ese camino: cualquier UPDATE lanzado desde otro programa o desde
--   un cliente SQL se saltaría la regla. El disparador vive en la propia
--   BD y se ejecuta siempre, venga de donde venga la modificación, así que
--   garantiza la integridad de forma centralizada y sin depender de las
--   aplicaciones.
--
-- * Aun así, el disparador por sí solo no garantiza que la transferencia
--   sea coherente: como se ve en i) y ii), también hace falta tratar la
--   transferencia como una transacción atómica (bloque PL/SQL o ROLLBACK
--   ante el error).
-- ---------------------------------------------------------------------
