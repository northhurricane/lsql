%{
#include "lsqld.tab.h"
%}

%option outfile="lsqld.lex.c" HEADER-FILE="lsqld.lex.h"

digit [0-9]

integer {digit}+

%%

%%


