%{
	#include "read.h"
%}

%option noyywrap

INTEGER	-?[0-9]+
/* TODO: more acceped symbol chars */
SYMBOL	[a-zA-Z][a-zA-Z0-9]*
STRING	\"(\\.|[^"\n\\])*\"

%%

\(			{ return T_OPEN_PAREN;  }
\)			{ return T_CLOSE_PAREN; }
{STRING}	{ return T_STRING;      }
{SYMBOL}	{ return T_SYMBOL;      }
{INTEGER}	{ return T_INTEGER;     }
[:space:]	{ yyless(1);            }
