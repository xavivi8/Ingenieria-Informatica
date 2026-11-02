-- =====================================================================
-- Práctica 3 - Ejercicio 4
-- TRG_SALDO_FI.SQL: mantiene actualizada la tabla SALDO_FI cada vez que
-- se recibe una OSRFI (orden de suscripción o reembolso de fondo de
-- inversión, tabla OP_OSRFI). Requiere la tabla SALDO_FI del ejercicio 3.
--
-- Además de las altas (lo que pide el enunciado), contempla bajas y
-- modificaciones de órdenes para que SALDO_FI no se descuadre.
-- =====================================================================

CREATE OR REPLACE TRIGGER trg_saldo_fi
AFTER INSERT OR UPDATE OR DELETE ON op_osrfi
FOR EACH ROW
DECLARE
    v_importe saldo_fi.saldo%TYPE;
BEGIN
    -- Quitar el efecto de la orden antigua (borrado o modificación)
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

    -- Aplicar el efecto de la orden nueva (alta o modificación)
    IF INSERTING OR UPDATING THEN
        v_importe := CASE :new.operation
                         WHEN 'subscription' THEN  :new.amount
                         WHEN 'refund'       THEN -:new.amount
                         ELSE 0
                     END;

        UPDATE saldo_fi
        SET    saldo = saldo + v_importe
        WHERE  cod_fi = :new.fund_id;

        IF SQL%ROWCOUNT = 0 THEN   -- el fondo aún no tenía fila en SALDO_FI
            INSERT INTO saldo_fi (cod_fi, saldo)
            VALUES (:new.fund_id, v_importe);
        END IF;
    END IF;
END;
/

-- Comprobar que ha compilado sin errores (debe devolver 0 filas)
SELECT line, position, text
FROM   user_errors
WHERE  name = 'TRG_SALDO_FI';

-- ---------------------------------------------------------------------
-- Prueba (con la consola en modo de transacción Manual)
-- ---------------------------------------------------------------------
SELECT * FROM saldo_fi ORDER BY cod_fi;

-- Suscripción de 1000 eur al primer fondo
INSERT INTO operation (cod_op, "date", "Cli-Acc_id")
VALUES (901, SYSDATE, (SELECT MIN(id) FROM "Cli-Acc"));

INSERT INTO op_osrfi (cod_op, contract_number, amount, operation, fund_id)
VALUES (901, 9999999901, 1000, 'subscription', (SELECT MIN(id) FROM fund));

-- El saldo del primer fondo debe haber subido 1000
SELECT * FROM saldo_fi ORDER BY cod_fi;

-- Deshacer la prueba (deja libre el código 901)
ROLLBACK;
