%option outfile="lsql.lex.c" HEADER-FILE="lsql.lex.h"
%option noyywrap
%option reentrant
%option prefix="lsql"

%{
#include "lsql.tab.h"
%}

L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]

ID {L}{A}*

%%

{ID} {
  return TOKEN_ID;
}

%%
