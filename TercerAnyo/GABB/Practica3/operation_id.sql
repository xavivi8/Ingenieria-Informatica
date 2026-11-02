-- =====================================================================
-- Práctica 3 - Ejercicio 6
-- OPERATION_ID.SQL: secuencia y disparador para asignar automáticamente
-- el ID (cod_op) de la tabla OPERATION.
-- Se ejecuta después del ejercicio 5 (máximo cod_op = 21).
-- =====================================================================

-- Comprobar el máximo actual (debe ser 21)
SELECT MAX(cod_op) FROM operation;

CREATE SEQUENCE seq_op
    START WITH 22
    INCREMENT BY 1
    NOCACHE;

CREATE OR REPLACE TRIGGER trg_op
BEFORE INSERT ON operation
FOR EACH ROW
BEGIN
    -- Solo si no se indica el código, para no romper inserciones explícitas
    IF :new.cod_op IS NULL THEN
        :new.cod_op := seq_op.NEXTVAL;
    END IF;
END;
/

-- Comprobar que ha compilado sin errores (debe devolver 0 filas)
SELECT line, position, text
FROM   user_errors
WHERE  name = 'TRG_OP';

-- ---------------------------------------------------------------------
-- Prueba: dos operaciones tipo D (una tupla en OPERATION y otra en OP_D)
--
-- * "id cuenta-titular" es la columna "OwnerAsAc-AsAc_id" de OP_D
--   (relación titular - cuenta asociada, destino de la disposición).
-- * El "Cli-Acc_id" de OPERATION se obtiene del Cli-Acc cuya cuenta ING
--   está vinculada a esa cuenta asociada.
-- * "periodicidad: no" se guarda como 'once', porque PERIODICITY es
--   NOT NULL y solo admite 'once', 'bimonthly', 'monthly' y 'annual'.
-- * En OP_D se usa seq_op.CURRVAL para tomar el código que el disparador
--   acaba de asignar a la operación.
-- ---------------------------------------------------------------------

-- Comprobar que los registros cuenta-titular 8 y 10 tienen un Cli-Acc vinculado
SELECT oa.id AS cuenta_titular, oa.associated_account_id, ca.id AS cli_acc
FROM   "OwnerAsAc-AsAc" oa
JOIN   "INGAc-AsAc" ia ON ia.associated_account_id = oa.associated_account_id
JOIN   "Cli-Acc" ca    ON ca.ing_account_id = ia.ing_account_id
WHERE  oa.id IN (8, 10)
ORDER  BY oa.id, ca.id;

-- Operación 1: 500 eur, mensual, cuenta-titular 8
INSERT INTO operation ("date", "Cli-Acc_id")
VALUES (SYSDATE,
        (SELECT MIN(ca.id)
         FROM   "OwnerAsAc-AsAc" oa
         JOIN   "INGAc-AsAc" ia ON ia.associated_account_id = oa.associated_account_id
         JOIN   "Cli-Acc" ca    ON ca.ing_account_id = ia.ing_account_id
         WHERE  oa.id = 8));

INSERT INTO op_d (cod_op, amount, periodicity, "OwnerAsAc-AsAc_id")
VALUES (seq_op.CURRVAL, 500, 'monthly', 8);

-- Operación 2: 9850 eur, sin periodicidad, cuenta-titular 10
INSERT INTO operation ("date", "Cli-Acc_id")
VALUES (SYSDATE,
        (SELECT MIN(ca.id)
         FROM   "OwnerAsAc-AsAc" oa
         JOIN   "INGAc-AsAc" ia ON ia.associated_account_id = oa.associated_account_id
         JOIN   "Cli-Acc" ca    ON ca.ing_account_id = ia.ing_account_id
         WHERE  oa.id = 10));

INSERT INTO op_d (cod_op, amount, periodicity, "OwnerAsAc-AsAc_id")
VALUES (seq_op.CURRVAL, 9850, 'once', 10);

-- Deben aparecer las operaciones 22 y 23
SELECT o.cod_op, o."date", o."Cli-Acc_id",
       d.amount, d.periodicity, d."OwnerAsAc-AsAc_id"
FROM   operation o
JOIN   op_d d ON d.cod_op = o.cod_op
WHERE  o.cod_op >= 22
ORDER  BY o.cod_op;

COMMIT;
