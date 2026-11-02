CREATE OR REPLACE TRIGGER trg_saldo_fi
AFTER INSERT OR UPDATE OR DELETE ON op_osrfi
FOR EACH ROW
DECLARE
    v_importe saldo_fi.saldo%TYPE;
BEGIN
    IF DELETING OR UPDATING THEN
        v_importe := CASE :old.operation
                         WHEN 'subscription' THEN  :old.amount
                         WHEN 'refund'       THEN -:old.amount
                         ELSE 0
                     END;

        UPDATE saldo_fi
        SET    saldo = saldo - v_importe
        WHERE  cod_fi = :old.fund_id;
    END IF;

    IF INSERTING OR UPDATING THEN
        v_importe := CASE :new.operation
                         WHEN 'subscription' THEN  :new.amount
                         WHEN 'refund'       THEN -:new.amount
                         ELSE 0
                     END;

        UPDATE saldo_fi
        SET    saldo = saldo + v_importe
        WHERE  cod_fi = :new.fund_id;

        IF SQL%ROWCOUNT = 0 THEN
            INSERT INTO saldo_fi (cod_fi, saldo)
            VALUES (:new.fund_id, v_importe);
        END IF;
    END IF;
END;
/

-- Comprobar
SELECT line, position, text
FROM   user_errors
WHERE  name = 'TRG_SALDO_FI';

-- Prueba
SELECT * FROM saldo_fi ORDER BY cod_fi;

-- Suscripción de 1000 eur al primer fondo
INSERT INTO operation (cod_op, "date", "Cli-Acc_id")
VALUES (901, SYSDATE, (SELECT MIN(id) FROM "Cli-Acc"));

INSERT INTO op_osrfi (cod_op, contract_number, amount, operation, fund_id)
VALUES (901, 9999999901, 1000, 'subscription', (SELECT MIN(id) FROM fund));

-- El saldo del primer fondo
SELECT * FROM saldo_fi ORDER BY cod_fi;

-- Deshacer la prueba
ROLLBACK;
