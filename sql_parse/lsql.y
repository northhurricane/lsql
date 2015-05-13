%{
#include "lsql.tab.h"

int yylex(YYSTYPE *lvalp);
void yyerror(char const*);
%}
/*
书写规则。
1、定义符号（symbol）时，使用一个空格将符号和冒号（‘:’）隔开，从而便于查找符号的定义位置。
*/

/*key word。按照字母顺序排列*/
%token KW_CREATE
%token KW_FROM
%token KW_SELECT
%token KW_TABLE

/*misc*/
%token ID
%token LT_INTEGER

%define api.pure full
%define api.value.type {void*}

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
KW_FROM ID {
};

ddl_sql :
create_table_sql {
};

create_table_sql :
KW_CREATE KW_TABLE ID {
};

expr :
LT_INTEGER {
};


