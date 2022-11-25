
/* Libro pagina 13*/
%{
//#include "calc_token.tab.h"
#include "bison.tab.h"
#include "iostream"
#include <string>
//extern int yylval;
//#define YYSTYPE char *

%}

%option noyywrap  


%%

"r" { return PARAM_R;}
"y" { return PARAM_Y;}
"A" { return PARAM_A;}
"u" { return PARAM_U;}
"B" { return PARAM_B;}
"e" { return PARAM_E;}
"mostrar_celula" { return MOSTRAR_CELULA;}
"mostrar_grilla" { return MOSTRAR_GRILLA;}
"grilla" { return GRILLA;}
"simular" { return SIMULAR;}
"iniciar" { return INICIAR;}
"celula" { return CELULA;}
"migrar" { return MIGRAR;}
[0-9]+ { yylval.intval = atoi(yytext); return INT_NUM;}
[0-9]+\.[0-9]+ { yylval.flval = atof(yytext); return FLOAT_NUM; }
"," { return COMA;}
"{" { return AP;}
"}" { return CP; }
\n	{ return FINLINEA; }

[ \t]   { /*ignoramos en este caso*/ } 
. 	{ std::cout << "OTRO CARACTER "<<*yytext<<std::endl; }
%%

