CREATE TABLE saldo_fi (
    cod_fi NUMBER        NOT NULL
           CONSTRAINT saldo_fi_pk PRIMARY KEY
           CONSTRAINT saldo_fi_fund_fk REFERENCES fund (id),
    saldo  NUMBER(14, 2) DEFAULT 0 NOT NULL
);

CREATE OR REPLACE PROCEDURE carga_saldo_fi IS
    -- Cursor con el saldo total de cada fondo
    CURSOR c_fondos IS
        SELECT f.id AS cod_fi,
               NVL(SUM(CASE o.operation
                           WHEN 'subscription' THEN  o.amount
                           WHEN 'refund'       THEN -o.amount
                       END), 0) AS saldo
        FROM   fund f
        LEFT JOIN op_osrfi o ON o.fund_id = f.id
        GROUP  BY f.id;
BEGIN
    DELETE FROM saldo_fi;

    FOR r IN c_fondos LOOP
        INSERT INTO saldo_fi (cod_fi, saldo)
        VALUES (r.cod_fi, r.saldo);
    END LOOP;
END carga_saldo_fi;
/

-- Comprobar
SELECT line, position, text
FROM   user_errors
WHERE  name = 'CARGA_SALDO_FI';

BEGIN
    carga_saldo_fi;
END;
/

COMMIT;

-- Resultado
SELECT s.cod_fi, f.name, s.saldo
FROM   saldo_fi s
JOIN   fund f ON f.id = s.cod_fi
ORDER  BY s.cod_fi;
