
/* Libro pagina 13*/
%{
//#include "calc_token.tab.h"
#include "bison.tab.h"
#include "iostream"
//extern int yylval;
//#define YYSTYPE char *

%}

%option noyywrap  


%%
"tiempo_infeccion" { return TIEMPO_INFECCION;}
"tiempo_inmunidad" { return TIEMPO_INMUNIDAD;}
"dimension" { return DIMENSION;}
"trasabilidad" { return TRASABILIDAD;}
"simular" { return SIMULAR;}
"iniciar" { return INICIAR;}
[0-9]+ { yylval.intval = atoi(yytext); return INT_NUM;}
[[:digit:]]+\.[[:digit:]]+ { yylval.sval = strdup(yytext);return PORC_TRASABILIDAD;}
"," { return COMA;}
"{" { return AP;}
"}" { return CP; }
\n	{ return FINLINEA; }

[ \t]   { /*ignoramos en este caso*/ } 
. 	{ std::cout << "OTRO CARACTER "<<*yytext<<std::endl; }
%%

