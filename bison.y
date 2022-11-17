
%{
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <cstring>
//#include "dfa_token.tab.h"
//#define YYSTYPE char * no colocar el define yyystype por que abajo en %union lo estoy definiendo
//#define YYSTYPE char *
using namespace std;
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char *s){
  fprintf(stderr, "Cadena no reconocida: %s\n", s);

}


%} 

%union {

    char *sval;
    int intval;
}
/* declaramos los tokens */
//%token NUMERO
//%token SUMA RESTA MULTIPLICA DIVIDE ABS
%token AP CP FINLINEA COMA INICIAL IGUAL FINAL ESTADOS MOSTRAR_TRAN MOSTRAR_ACT MOSTRAR_EST MOSTRAR_ALF
%token <sval> ALFABETO
%token <sval> LEER
%token <sval> CONT_TRAN
%token <sval> CONT_INPUT
%token <sval> TRAN
%%

input   : /* empty string */
        | input linea
        ;

linea   : FINLINEA
        | func FINLINEA
        ;

func    : TRAN AP content
        | LEER AP content
        ;

content : CONT_TRAN {}
        | CONT_INPUT { }
        | content CP
        ;

%%

int main(int argc, char const *argv[]){
  printf("\nIngresa una funcion\n");
  yyin = stdin;
  yyparse();
  }
/* 
inputs de ej:
  estados{q1,q2,q3}
  inicial{q1}
  final{q3}
  tran{(q1,a,q2),(q2,b,q3),(q3,a,q3)}
  leer{abaa}
*/

