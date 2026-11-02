SELECT MAX(cod_op) FROM operation;

CREATE SEQUENCE seq_op
    START WITH 22
    INCREMENT BY 1
    NOCACHE;

CREATE OR REPLACE TRIGGER trg_op
BEFORE INSERT ON operation
FOR EACH ROW
BEGIN
    IF :new.cod_op IS NULL THEN
        :new.cod_op := seq_op.NEXTVAL;
    END IF;
END;
/

-- Comprobar
SELECT line, position, text
FROM   user_errors
WHERE  name = 'TRG_OP';

-- Prueba: dos operaciones tipo D

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

SELECT o.cod_op, o."date", o."Cli-Acc_id",
       d.amount, d.periodicity, d."OwnerAsAc-AsAc_id"
FROM   operation o
JOIN   op_d d ON d.cod_op = o.cod_op
WHERE  o.cod_op >= 22
ORDER  BY o.cod_op;

COMMIT;

