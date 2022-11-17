
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
"inicial" { return INICIAL;}
"final" { return FINAL;}
"leer" { return LEER;}
"estados" { return ESTADOS;}
"mostrar_tran" { return MOSTRAR_TRAN;}
"mostrar_act" { return MOSTRAR_ACT;}
"mostrar_est" { return MOSTRAR_EST;}
"mostrar_alf" { return MOSTRAR_ALF;}
\= { return IGUAL;}
"alfabeto" { yylval.sval = strdup(yytext);return ALFABETO;}
"tran" { yylval.sval = strdup(yytext);return TRAN ;}
"{" { return AP; }
(,*[A-Za-z0-9]+)+ { yylval.sval = strdup(yytext);return CONT_INPUT;}
(,*\([A-Za-z]+[0-9]*\,[A-Za-z]+\,[A-Za-z]+[0-9]*\))+ { yylval.sval = strdup(yytext);return CONT_TRAN; }
"}" { return CP; }
\n	{ return FINLINEA; }

[ \t]   { /*ignoramos en este caso*/ } 
. 	{ std::cout << "OTRO CARACTER "<<*yytext<<std::endl; }
%%

