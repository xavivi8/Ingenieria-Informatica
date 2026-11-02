CREATE OR REPLACE TRIGGER trg_op_i
AFTER INSERT ON op_i
FOR EACH ROW
DECLARE
    v_cuenta account.id%TYPE;
BEGIN
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

-- Comprobar 
SELECT line, position, text
FROM   user_errors
WHERE  name = 'TRG_OP_I';

-- Prueba 

SELECT ca.id AS cli_acc, a.id AS cuenta, a.balance
FROM   "Cli-Acc" ca
JOIN   account a ON a.id = ca.ing_account_id
WHERE  ca.id = 4;

INSERT INTO operation (cod_op, "date", "Cli-Acc_id")
VALUES (21, TO_DATE('2015-01-30 14:07:01', 'YYYY-MM-DD HH24:MI:SS'), 4);

INSERT INTO op_i (cod_op, office_id_bank, office_number, check_number, amount)
VALUES (21, 0049, 1653, 000675, 450);

SELECT id, balance FROM account WHERE id = 14;

COMMIT;
