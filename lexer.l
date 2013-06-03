%{
	#include "read.h"
%}

%option noyywrap

INTEGER		-?[0-9]+
SYMBOL_CHAR	[a-zA-Z+\-\^.*/<=>!?$%_&~]
SYMBOL		{SYMBOL_CHAR}({SYMBOL_CHAR}|[0-9])*
STRING		\"(\\.|[^"\n\\])*\"
CHAR		#\\[a-zA-Z_]+

%%

\(			{ return T_OPEN_PAREN;  }
\)			{ return T_CLOSE_PAREN; }
{STRING}	{ return T_STRING;      }
{SYMBOL}	{ return T_SYMBOL;      }
{INTEGER}	{ return T_INTEGER;     }
{CHAR}		{ return T_CHAR;		}
[:space:]	{ yyless(1);            }
