%{
#include "lsqld.tab.h"
#include "lex.h"
%}

%option outfile="lsqld.lex.c" HEADER-FILE="lsqld.lex.h"
%option bison-bridge
%option reentrant

digit [0-9]
integer {digit}+
decimal {digit}*\.{digit}+|{digit}+\.{digit}*
scientific {decimal}[eE][+-]?{integer}

%%

{integer} {
  *yylval_param = lex_integer(yytext, yyleng);
  return LT_INTEGER;
}

{decimal} {
  *yylval_param = lex_decimail(yytext, yyleng);
  return LT_DECIMAL;
}

{scientific} {
  *yylval_param = lex_scientific(yytext, yyleng);
  return LT_SCIENTIFIC;
}

%%


