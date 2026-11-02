DECLARE
    CURSOR c_clientes IS
        SELECT DNI, BALANCE
        FROM VISTA_SALDO;

    v_dni VISTA_SALDO.DNI%type;
    v_balance VISTA_SALDO.BALANCE%type;
BEGIN
    OPEN c_clientes;

    DBMS_OUTPUT.PUT_LINE('Client              Defaulting');
    DBMS_OUTPUT.PUT_LINE('------------------  ----------');

    LOOP
        Fetch c_clientes INTO v_dni, v_balance;

        EXIT WHEN c_clientes%NOTFOUND;
        IF v_balance < 0 THEN
            DBMS_OUTPUT.PUT_LINE(v_dni || '              yes');
        ELSE
            DBMS_OUTPUT.PUT_LINE(v_dni || '              no');
        END IF;

    END LOOP;

    CLOSE c_clientes;
END;