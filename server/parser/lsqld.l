%{
#include "lsqld.tab.h"
%}

%option outfile="lsqld.lex.c" HEADER-FILE="lsqld.lex.h"
%option bison-bridge
%option reentrant

digit [0-9]
integer {digit}+
decimal {digit}*\.{digit}+|{digit}+\.{digit}*
scientific_notation {decimal}[eE][+-]?{integer}

%%

{integer} {
  printf("integer:%s\n", yytext);
}

{decimal} {
  printf("decimal:%s\n", yytext);
}

{scientific_notation} {
  printf("scientific notation:%s\n", yytext);
}

%%


