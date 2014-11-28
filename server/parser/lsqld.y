%{
#include "lsqld.tab.h"
#include "lsqld.lex.h"
#include "parser.h"
%}

%defines "lsqld.tab.h"

%define api.pure full
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
%%

