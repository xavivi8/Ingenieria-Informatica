-- =====================================================================
-- Práctica 3 - Ejercicio 5
-- TRG_OP_I.SQL: al ingresar un cheque (alta en OP_I) se suma su importe al
-- saldo de la cuenta en que se ingresa.
--
-- Relación en el esquema:
--   OP_I.cod_op -> OPERATION."Cli-Acc_id" -> "Cli-Acc".ing_account_id -> ACCOUNT
-- Los campos de OP_I (banco, oficina, número de cheque) identifican el
-- cheque, no la cuenta que lo recibe.
-- =====================================================================

CREATE OR REPLACE TRIGGER trg_op_i
AFTER INSERT ON op_i
FOR EACH ROW
DECLARE
    v_cuenta account.id%TYPE;
BEGIN
    -- Cuenta ING del cliente que realiza la operación
    SELECT ca.ing_account_id
    INTO   v_cuenta
    FROM   operation o
    JOIN   "Cli-Acc" ca ON ca.id = o."Cli-Acc_id"
    WHERE  o.cod_op = :new.cod_op;

    UPDATE account
    SET    balance = balance + NVL(:new.amount, 0)
    WHERE  id = v_cuenta;
END;
/

-- Comprobar que ha compilado sin errores (debe devolver 0 filas)
SELECT line, position, text
FROM   user_errors
WHERE  name = 'TRG_OP_I';

-- ---------------------------------------------------------------------
-- Prueba del enunciado
-- ---------------------------------------------------------------------

-- El Cli-Acc 4 debe corresponder a la cuenta 14, con saldo 10 eur
SELECT ca.id AS cli_acc, a.id AS cuenta, a.balance
FROM   "Cli-Acc" ca
JOIN   account a ON a.id = ca.ing_account_id
WHERE  ca.id = 4;

-- Saldo de la cuenta 14 antes del ingreso
SELECT id, balance FROM account WHERE id = 14;

-- La fecha se convierte con TO_DATE: la cadena '2015-01-30 14:07:01' tal
-- cual solo funcionaría si NLS_DATE_FORMAT coincidiera con ese formato.
-- 0049 y 000675 son columnas numéricas, así que quedan como 49 y 675.
-- La oficina (49, 1653) debe existir en OFFICE por la clave ajena.
INSERT INTO operation (cod_op, "date", "Cli-Acc_id")
VALUES (21, TO_DATE('2015-01-30 14:07:01', 'YYYY-MM-DD HH24:MI:SS'), 4);

INSERT INTO op_i (cod_op, office_id_bank, office_number, check_number, amount)
VALUES (21, 0049, 1653, 000675, 450);

-- La cuenta 14 debe haber pasado de 10 a 460 eur
SELECT id, balance FROM account WHERE id = 14;

COMMIT;
