%{
#include "lsqld.lex.h"
#include "parser.h"
%}

%defines "lsqld.tab.h"

%define api.pure full
%define api.value.type {parse_object_t*} //保持和parse.h中的YYSTYPE一致
%param {yyscan_t scanner}

/* identifier */
%token IDENTIFIER

/* literal token */
%token LT_DECIMAL LT_INTEGER LT_SCIENTIFIC_NOTATION LT_STRING

/* keyword token */
%token KW_INSERT KW_INTO
%token KW_CREATE
%token KW_SELECT
%token KW_VALUES

%%
lsqld_sql:
  dml_sql
  {
    return 0;
  }

dml_sql:
IDENTIFIER {}

%%



