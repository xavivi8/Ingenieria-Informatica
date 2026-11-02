create table GI410.BANK
(
    ID   NUMBER            not null
        constraint BANK_PK
            primary key,
    NAME VARCHAR2(30 char) not null
        constraint BANK__UN
            unique
)
/

create table GI410.OFFICE
(
    BANK_ID       NUMBER        not null
        constraint OFFICE_BANK_FK
            references GI410.BANK,
    OFFICE_NUMBER NUMBER        not null,
    NAME          VARCHAR2(60)  not null
        constraint OFFICE__UN
            unique,
    ADDRESS       VARCHAR2(100) not null,
    constraint OFFICE_PK
        primary key (BANK_ID, OFFICE_NUMBER)
)
/

create table GI410.ACCOUNT
(
    ID             NUMBER        not null
        constraint ACCOUNT_PK
            primary key,
    OFFICE_BANK_ID NUMBER        not null,
    OFFICE_NUMBER  NUMBER        not null,
    ACCOUNT_NUMBER NUMBER        not null,
    BALANCE        NUMBER(10, 2) not null,
    constraint ACCOUNT__UN
        unique (OFFICE_BANK_ID, OFFICE_NUMBER, ACCOUNT_NUMBER),
    constraint ACCOUNT_OFFICE_FK
        foreign key (OFFICE_BANK_ID, OFFICE_NUMBER) references GI410.OFFICE
)
/

create table GI410.ING_ACCOUNT
(
    ID             NUMBER                                not null
        constraint ING_ACCOUNT_PK
            primary key
        constraint FK_ASS_2
            references GI410.ACCOUNT,
    TYPE           VARCHAR2(25) default 'Orange account' not null
        constraint CK_ING_ACCOUNT_TYPE
            check (type in ('Orange account', 'home savings account', 'fiscal savings account', 'deposit account')),
    POSTAL_ADDRESS VARCHAR2(90)                          not null
)
/

create table GI410.ASSOCIATED_ACCOUNT
(
    ID NUMBER not null
        constraint ASSOCIATED_ACCOUNT_PK
            primary key
        constraint FK_ASS_1
            references GI410.ACCOUNT
)
/

create table GI410."INGAc-AsAc"
(
    ING_ACCOUNT_ID        NUMBER not null
        constraint "INGAc-AsAc_ING_Ac_FK"
            references GI410.ING_ACCOUNT,
    ASSOCIATED_ACCOUNT_ID NUMBER not null
        constraint "INGAc-AsAc_FK"
            references GI410.ASSOCIATED_ACCOUNT,
    constraint "INGAc-AsAc_PK"
        primary key (ASSOCIATED_ACCOUNT_ID, ING_ACCOUNT_ID)
)
/

create table GI410.OWNER
(
    DNI      VARCHAR2(9 char)  not null
        constraint OWNER_PK
            primary key,
    NAME     VARCHAR2(20 char) not null,
    SURNAME1 VARCHAR2(20)      not null,
    SURNAME2 VARCHAR2(20)
)
/

create table GI410.CLIENT
(
    DNI            VARCHAR2(9 char) not null
        constraint CLIENT_PK
            primary key
        constraint FK_ASS_8
            references GI410.OWNER,
    MARITAL_STATUS VARCHAR2(10)     not null
        constraint CK_CLIENT_MARITAL_STATUS
            check (marital_status in ('married', 'single', 'widow')),
    BIRTHDAY_DATE  DATE
)
/

create table GI410.OWNERASAC
(
    DNI VARCHAR2(9 char) not null
        constraint OWNERASAC_PK
            primary key
        constraint FK_ASS_9
            references GI410.OWNER
)
/

create table GI410."OwnerAsAc-AsAc"
(
    ID                    NUMBER           not null
        constraint "OwnerAsAc-AsAc_PK"
            primary key,
    OWNERASAC_DNI         VARCHAR2(9 char) not null
        constraint "OwnerAsAc-AsAc_OwnerAsAc_FK"
            references GI410.OWNERASAC,
    ASSOCIATED_ACCOUNT_ID NUMBER           not null
        constraint "OwnerAsAc-AsAc_AsAc_FK"
            references GI410.ASSOCIATED_ACCOUNT,
    constraint "OwnerAsAc-AsAc__UN"
        unique (ASSOCIATED_ACCOUNT_ID, OWNERASAC_DNI)
)
/

create table GI410."Cli-Acc"
(
    ID             NUMBER           not null
        constraint "Cli-Acc_PK"
            primary key,
    CLIENT_DNI     VARCHAR2(9 char) not null
        constraint "Cli-Acc_Client_FK"
            references GI410.CLIENT,
    ING_ACCOUNT_ID NUMBER           not null
        constraint "Cli-Acc_ING_Account_FK"
            references GI410.ING_ACCOUNT,
    constraint "Cli-Acc__UN"
        unique (ING_ACCOUNT_ID, CLIENT_DNI)
)
/

create table GI410.SERVICE
(
    ID   NUMBER            not null
        constraint SERVICE_PK
            primary key,
    NAME VARCHAR2(80 char) not null
        constraint SERVICE__UN
            unique
        constraint CK_SERVICE_NAME
            check (name in ('ING SEGUROS', 'ING FONDOS', 'ING BROKER', 'ING HIPOTECA'))
)
/

create table GI410."Client-Service"
(
    CLIENT_DNI VARCHAR2(9 char) not null
        constraint FK_ASS_10
            references GI410.CLIENT,
    SERVICE_ID NUMBER           not null
        constraint FK_ASS_11
            references GI410.SERVICE,
    constraint "Client-Service__IDX"
        primary key (CLIENT_DNI, SERVICE_ID)
)
/

create table GI410.FUND
(
    ID   NUMBER             not null
        constraint FUND_PK
            primary key,
    NAME VARCHAR2(120 char) not null
        constraint CK_FUND_NAME
            check (name in ('Renta Variable Global FIMF', 'Mixto Europeo', 'IBEX 35'))
)
/

create table GI410.OPERATION
(
    COD_OP       NUMBER(9) not null
        constraint OPERATION_PK
            primary key,
    "date"       DATE      not null,
    "Cli-Acc_id" NUMBER    not null
        constraint "Operation_Cli-Acc_FK"
            references GI410."Cli-Acc"
)
/

create table GI410.OP_D
(
    COD_OP              NUMBER(9)    not null
        constraint OP_D_PK
            primary key
        constraint FK_ASS_3
            references GI410.OPERATION,
    AMOUNT              NUMBER(9, 2) not null,
    PERIODICITY         VARCHAR2(40) not null
        constraint CK_OPD_PERIODICITY
            check (periodicity in ('once', 'bimonthly', 'monthly', 'annual')),
    "OwnerAsAc-AsAc_id" NUMBER       not null
        constraint "OP_D_OwnerAsAc-AsAc_FK"
            references GI410."OwnerAsAc-AsAc"
)
/

create table GI410.OP_I
(
    COD_OP         NUMBER(9) not null
        constraint OP_I_PK
            primary key
        constraint FK_ASS_5
            references GI410.OPERATION,
    OFFICE_ID_BANK NUMBER    not null,
    OFFICE_NUMBER  NUMBER    not null,
    CHECK_NUMBER   NUMBER(9) not null,
    AMOUNT         NUMBER(9, 2),
    constraint OP_I_UN
        unique (OFFICE_ID_BANK, OFFICE_NUMBER, CHECK_NUMBER),
    constraint OP_I_OFFICE_FK
        foreign key (OFFICE_ID_BANK, OFFICE_NUMBER) references GI410.OFFICE
)
/

create table GI410.OP_MCA
(
    COD_OP              NUMBER(9) not null
        constraint OP_MCA_PK
            primary key
        constraint FK_ASS_4
            references GI410.OPERATION,
    JOIN                CHAR
        constraint CK_OP_MCA_JOIN
            check (join in ('T', 'F')),
    "OwnerAsAc-AsAc_id" NUMBER    not null
        constraint "OP_MCA_OwnerAsAcAsAc_FK"
            references GI410."OwnerAsAc-AsAc"
)
/

create table GI410.OP_OI
(
    COD_OP              NUMBER(9)    not null
        constraint OP_OI_PK
            primary key
        constraint FK_ASS_6
            references GI410.OPERATION,
    AMOUNT              NUMBER(9, 2) not null,
    PERIODICITY         VARCHAR2(40),
    "OwnerAsAc-AsAc_id" NUMBER       not null
        constraint "OP_OI_OwnerAsAcAsAc_FK"
            references GI410."OwnerAsAc-AsAc"
)
/

create table GI410.OP_OSRFI
(
    COD_OP          NUMBER(9)     not null
        constraint OP_OSRFI_PK
            primary key
        constraint FK_ASS_7
            references GI410.OPERATION,
    CONTRACT_NUMBER NUMBER(10)    not null
        constraint OP_OSRFI__UN
            unique,
    AMOUNT          NUMBER(10, 2) not null,
    OPERATION       VARCHAR2(20 char)
        constraint CK_OPOSRFI_OPER
            check (operation in ('subscription', 'refund')),
    FUND_ID         NUMBER        not null
        constraint OP_OSRFI_FUND_FK
            references GI410.FUND
)
/

create table GI410.INTERNET
(
    ID              NUMBER   not null
        constraint INTERNET_PK
            primary key,
    IP              CHAR(15) not null,
    CONEXION_BEGIN  DATE,
    CONEXION_END    DATE,
    OP_MCA_COD_OP   NUMBER(9)
        constraint INTERNET_OP_MCA_FK
            references GI410.OP_MCA,
    OP_D_COD_OP     NUMBER(9)
        constraint INTERNET_OP_D_FK
            references GI410.OP_D,
    OP_OI_COD_OP    NUMBER(9)
        constraint INTERNET_OP_OI_FK
            references GI410.OP_OI,
    OP_OSRFI_COD_OP NUMBER(9)
        constraint INTERNET_OP_OSRFI_FK
            references GI410.OP_OSRFI
)
/

create unique index GI410.INTERNET__IDX
    on GI410.INTERNET (OP_OI_COD_OP)
/

create unique index GI410.INTERNET__IDXV1
    on GI410.INTERNET (OP_D_COD_OP)
/

create unique index GI410.INTERNET__IDXV2
    on GI410.INTERNET (OP_MCA_COD_OP)
/

create unique index GI410.INTERNET__IDXV3
    on GI410.INTERNET (OP_OSRFI_COD_OP)
/

create table GI410.TELEPHONE
(
    ID               NUMBER not null
        constraint TELEPHONE_PK
            primary key,
    TELEPHONE_NUMBER NUMBER not null,
    "date"           DATE   not null,
    OPERATOR         NUMBER not null,
    OP_MCA_COD_OP    NUMBER(9)
        constraint TELEPHONE_OP_MCA_FK
            references GI410.OP_MCA,
    OP_D_COD_OP      NUMBER(9)
        constraint TELEPHONE_OP_D_FK
            references GI410.OP_D,
    OP_OSRFI_COD_OP  NUMBER(9)
        constraint TELEPHONE_OP_OSRFI_FK
            references GI410.OP_OSRFI
)
/

create unique index GI410.TELEPHONE__IDX
    on GI410.TELEPHONE (OP_D_COD_OP)
/

create unique index GI410.TELEPHONE__IDXV1
    on GI410.TELEPHONE (OP_MCA_COD_OP)
/

create unique index GI410.TELEPHONE__IDXV2
    on GI410.TELEPHONE (OP_OSRFI_COD_OP)
/

