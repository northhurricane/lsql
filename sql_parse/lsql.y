%{
#include "lex.h"
#include "parse_inner.h"

void nothing();
void yyerror(void *, void *, char const*);
%}

/*
书写规则。
1、定义符号（symbol）时，使用一个空格将符号和冒号（‘:’）隔开，从而便于查找符号的定义位置。
*/

/*token defines*/
/*key word。按照字母顺序排列*/
%token KW_CREATE
%token KW_FROM
%token KW_SELECT
%token KW_TABLE

/*misc*/
%token TOKEN_ID
%token LT_INTEGER

/* api defines */
%define api.pure full
%define api.value.type {void*}

/* param defines */
%lex-param {void *hlex}

%parse-param {void *heap}
%parse-param {void *hlex}

%%

lsql :
dml_sql {
}
| ddl_sql {
};

dml_sql :
select_sql {
};

select_sql :
KW_SELECT select_item_list from_option {
  $$ = parse_create_select_sql(heap, $2, $3);
};

select_item_list :
select_item {
}
| select_item_list ',' select_item {
};

select_item :
expr {
};

from_option :
|
KW_FROM TOKEN_ID {
};

ddl_sql :
create_table_sql {
};

create_table_sql :
KW_CREATE KW_TABLE TOKEN_ID {
};

expr :
LT_INTEGER {
};


