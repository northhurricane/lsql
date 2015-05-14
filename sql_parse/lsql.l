%option outfile="lsql.lex.c" HEADER-FILE="lsql.lex.h"
%option noyywrap
%option reentrant
%option prefix="lsql"

%{
#include "lsql.tab.h"
%}

%%

