-- =====================================================================
-- Práctica 3 - Ejercicio 3
-- SALDO_FI.SQL: tabla SALDO_FI y procedimiento CARGA_SALDO_FI
--
-- En SALDO_FI se anota el saldo total de cada fondo de inversión:
--   saldo = suma de suscripciones - suma de reembolsos (tabla OP_OSRFI)
-- En este esquema los fondos se identifican por FUND.ID, así que cod_fi
-- es numérico y referencia a FUND (el nombre del fondo está en FUND.NAME).
-- =====================================================================

CREATE TABLE saldo_fi (
    cod_fi NUMBER        NOT NULL
           CONSTRAINT saldo_fi_pk PRIMARY KEY
           CONSTRAINT saldo_fi_fund_fk REFERENCES fund (id),
    saldo  NUMBER(14, 2) DEFAULT 0 NOT NULL
);

CREATE OR REPLACE PROCEDURE carga_saldo_fi IS
    -- Cursor con el saldo total de cada fondo. Se usa LEFT JOIN para que
    -- también aparezcan los fondos sin órdenes (saldo 0).
    CURSOR c_fondos IS
        SELECT f.id AS cod_fi,
               NVL(SUM(CASE o.operation
                           WHEN 'subscription' THEN  o.amount
                           WHEN 'refund'       THEN -o.amount
                       END), 0) AS saldo
        FROM   fund f
        LEFT JOIN op_osrfi o ON o.fund_id = f.id
        GROUP  BY f.id;
    r c_fondos%ROWTYPE;
BEGIN
    DELETE FROM saldo_fi;          -- por si se ejecuta más de una vez

    OPEN c_fondos;
    LOOP
        FETCH c_fondos INTO r;
        EXIT WHEN c_fondos%NOTFOUND;

        INSERT INTO saldo_fi (cod_fi, saldo)
        VALUES (r.cod_fi, r.saldo);
    END LOOP;
    CLOSE c_fondos;
END carga_saldo_fi;
/

-- Comprobar que ha compilado sin errores (debe devolver 0 filas)
SELECT line, position, text
FROM   user_errors
WHERE  name = 'CARGA_SALDO_FI';

-- Invocar el procedimiento una vez para la carga inicial
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
