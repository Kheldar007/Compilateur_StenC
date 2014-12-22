%{
    #include <stdlib.h>
    #include <string.h>
	# include "include/tree.h"
    # include "./include/quad.h"
    # include "y.tab.h"
    # define YY_NO_INPUT
    extern YYSTYPE yylval ;
%}

%option nounput
%option noyywrap

identifier [a-zA-Z_]+[0-9a-zA-Z_]*
number     "-"{0,1}[1-9][0-9]*
type       "int"

%%

"="             { return ASSIGN; }
";"             { return END_INS; }
"+"             { return PLUS;}
"-"             { return MOINS;}
"/"             { return DIV;}
"*"             { return MULT;}
"("             { return POPEN;}
")"             { return PCLOSE;}
"while"         { return WHILE;}
"if"            { return IF;}
"else"          { return ELSE; }
"{"             { return AOPEN; }
"}"             { return ACLOSE; }

"=="            { return EQUAL;}
"!="            { return NOT_EQUAL;}
">"             { return SUP;}
"<"             { return INF;}
">="            { return SUP_EQUAL;}
"<="            { return INF_EQUAL;}
"||"            { return OR;}
"&&"            { return AND;}

{type}          { yylval.string = strdup(yytext); return TYPE;}
{identifier}    { yylval.string = strdup(yytext); return ID; }
{number}        { yylval.value = atoi(yytext); return NUM; }
[\t \n]         { }
.               { printf("[Lex] Unknown character: %s\n", yytext); }

%%

// Free the memory allocated for Lex when we are done.
void lex_free() {
  yy_delete_buffer(YY_CURRENT_BUFFER);
  free(yy_buffer_stack);
}
