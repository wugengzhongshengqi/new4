%{
/* 词法分析器（Flex）：识别关键字、标识符、字面量与操作符并返回 token */
#include "tac.h"
#include "mini.y.h"
%}

%option yylineno

%%

"int"  {  return INT;  }
"char" {  return CHAR; }
"struct" {  return STRUCT;  }

"input"  {  return INPUT;  }

"output"  {  return OUTPUT;  }

"return"  {  return RETURN;  }

"if"  {  return IF;  }

"else"  {  return ELSE;  }

"while"  {  return WHILE;  }

"switch" {  return SWITCH;  }

"case"   {  return CASE;    }

"default" {  return DEFAULT; }

"break"  {  return BREAK;   }

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

"."   {  return DOT;  }

[ \t\r\n]|#.*

. 	{	return *yytext; }

%%

/* 输入结束回调 */
int yywrap()
{
	return 1;
}

