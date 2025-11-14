%{
#include "tac.h"
#include "mini.y.h"
%}

%option yylineno

%%

"int"  {  return INT;  }
"char" {  return CHAR; }

"input"  {  return INPUT;  }

"output"  {  return OUTPUT;  }

"return"  {  return RETURN;  }

"if"  {  return IF;  }

"else"  {  return ELSE;  }

"while"  {  return WHILE;  }

[A-Za-z]([A-Za-z]|[0-9])*  {  
	yylval.string = strdup(yytext); 
	return IDENTIFIER;
}

[0-9]*	{
    yylval.string = strdup(yytext); 
    return INTEGER;
}

\"[^\"]*\"  {
    yylval.string = strdup(yytext); 
    return TEXT;
}

\'(\\.|[^'])\'  {
    char ch;
    if(yytext[1]=='\\') {
        switch(yytext[2]){
            case 'n': ch='\n'; break;
            case '\\': ch='\\'; break;
            case '\'': ch='\''; break;
            case '"': ch='"'; break;
            case 't': ch='\t'; break;
            default: ch=yytext[2]; break;
        }
    } else {
        ch=yytext[1];
    }
    yylval.character = ch;
    return CHARACTER;
}

"=="  {  return EQ;  }

"!="  {  return NE;  }

"<="  {  return LE;  }

"<"  {  return LT;  }

">="  {  return GE;  }

">"  {  return GT;  }

[ \t\r\n]|#.*

. 	{	return *yytext; }

%%

int yywrap()
{
	return 1;
}

