
%{

#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
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

double aux;

// hacer un creador de automatas celular
/*
################################################################################
# Los individuos de una población pueden ser Suceptibles, Infectados y re      #
# cuperados. Por lo que definiremos a cada automata con los siguientes para-   #
# metros, primero, cada cuadrante tendrá una población. luego de esa pobl      #
# acion definiremos aquellos que están suceptibles, infectados y recupera      #
# dos. Luego, tenemos que hacer una función que permita agregar transiciónes   #
# a nuestros automatas celulares, osea definir su comportamiento, en base a    #
# los parametros antes mencionados de la población.                            #
################################################################################
*/

// variables globales
int tiempo_de_infeccion;
// posibilidad de contagiarte por vecino
double tasa_transmisibilidad;
// tiempo que dura la inmunidad una vez recuperado
int tiempo_de_inmunidad;
// estados
vector<string> estados = {"S", "I", "R"};

int n,m;
class celula
{
public:
    // cero significa que no existe el ciclo para este estado, partiendo del 1 se entiende como el t(1) del estado actual.
    int ciclo;
    // los estados pueden ser (S)suceptible, (I)infectado, (R)recuperado.
    string estado;

    celula(int cic, string est)
    {
        ciclo = cic;
        estado = est;
    }

    celula()
    {
        ciclo = 0;
        estado = "S";
    }

    void celula_aleatoria()
    {
        estado = estados[rand() % 3];
        if (estado != "S")
        {
            if (estado == "I")
            {
                ciclo = rand() % tiempo_de_infeccion + 1;
            }
            else if (estado == "R")
            {
                ciclo = rand() % tiempo_de_inmunidad + 1;
            }
        }
        else
        {
            ciclo = 0;
        }
    }
    void infectar()
    { // funcion para transformar la celula en infectada en base a la tasa de transmisibilidad
        double rand_val = (double)rand() / RAND_MAX;
        if ( rand_val <= tasa_transmisibilidad )
        {
            //cout << rand_val << "<=" << tasa_transmisibilidad<<endl;

            estado = "I";
            ciclo = 1;
        }

    }
};

class automata_grid
{
public:
    int x, y;
    vector<vector<celula>> grid;
    vector<celula> fila;


    // esto hay que llamarlo al toque.
    automata_grid(int m, int n)
    {
        x = m;
        y = n;
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                celula automata(0, "S");
                fila.push_back(automata);
            }
            grid.push_back(fila);
            fila.clear();
        }
    }

    void celulas_aleatorias()
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                grid[i][j].celula_aleatoria();
            }
        }
    }

    void imprimir_estados()
    {
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                if( grid[i][j].estado == "I"){
                  cout <<"\e[0;33m" <<grid[i][j].estado << grid[i][j].ciclo <<"\e[0m ";
                }
                else if ( grid[i][j].estado == "R"){
                  cout <<"\e[0;36m" <<grid[i][j].estado << grid[i][j].ciclo <<"\e[0m ";
                }
                else if( grid[i][j].estado == "S"){
                  cout <<"\e[0;32m" <<grid[i][j].estado << grid[i][j].ciclo <<"\e[0m ";
                }
            }
            cout << endl;
        }
    }



void infectar_celulas()
    {
      vector<vector<celula>> nueva_grid;//nueva grilla
      nueva_grid = grid;
      for(int i = 0;i < x;i++)
      {
        for ( int j =0;j<y;j++)
        {            
          if(grid[i][j].estado == "I" )
          //en base a una posicion infectada infecto las que estan al rededor
          {
            if(nueva_grid[(unsigned int)(i - 1)%x][(unsigned int)(j - 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i - 1)%x][(unsigned int)(j - 1)%y].infectar();
            }if(nueva_grid[(unsigned int)(i)%x][(unsigned int)(j - 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i)%x][(unsigned int)(j - 1)%y].infectar();
            }
            if(nueva_grid[(unsigned int)(i + 1)%x][(unsigned int)(j - 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i + 1)%x][(unsigned int)(j - 1)%y].infectar();
            }
            if(nueva_grid[(unsigned int)(i - 1)%x][(unsigned int)(j)%y].estado == "S"){
                nueva_grid[(unsigned int)(i - 1)%x][(unsigned int)(j)%y].infectar();
            }
            if(nueva_grid[(unsigned int)(i + 1)%x][(unsigned int)(j)%y].estado == "S"){
                nueva_grid[(unsigned int)(i + 1)%x][(unsigned int)(j)%y].infectar();
            }
            if(nueva_grid[(unsigned int)(i - 1)%x][(unsigned int)(j + 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i - 1)%x][(unsigned int)(j + 1)%y].infectar();
            }  
            if(nueva_grid[(unsigned int)(i)%x][(unsigned int)(j + 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i)%x][(unsigned int)(j + 1)%y].infectar();
            }
            if(nueva_grid[(unsigned int)(i + 1)%x][(unsigned int)(j + 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i + 1)%x][(unsigned int)(j + 1)%y].infectar();
            }
            
          }
            }
        }
        //revision de ciclos para modifcar en nueva grilla.   
        for(int i = 0;i < x;i++){
            for ( int j =0;j<y;j++){
                if(grid[i][j].estado == "I"){
                    if (grid[i][j].ciclo +1 > tiempo_de_infeccion){
                        nueva_grid[i][j].estado = "R";
                        nueva_grid[i][j].ciclo = 1;
                    }
                    else{
                        nueva_grid[i][j].ciclo = grid[i][j].ciclo+1;
                    }
                }
                else if (grid[i][j].estado == "R"){
                    if (grid[i][j].ciclo +1 > tiempo_de_inmunidad){
                        nueva_grid[i][j].estado = "S";
                        nueva_grid[i][j].ciclo = 0;
                    }
                    else{
                    nueva_grid[i][j].ciclo = grid[i][j].ciclo+1;
                    }   
                }
            }
        }
    grid = nueva_grid;
    }


};



extern automata_grid aux_automata(10,10); //se define una variable auxiliar para poder almacenar el automata durante la ejecucion del parser
%} 

%union {

    char *sval;
    int intval;
}
/* declaramos los tokens */
//%token NUMERO
//%token SUMA RESTA MULTIPLICA DIVIDE ABS
%token AP CP FINLINEA FINLINEA TIEMPO_INFECCION TIEMPO_INMUNIDAD DIMENSION COMA TRASABILIDAD SIMULAR INICIAR
%token <intval> INT_NUM
%token <sval> PORC_TRASABILIDAD
%%

input   : /* empty string */
        | input linea
        ;

linea   : FINLINEA
        | func FINLINEA
        ;

func    : TIEMPO_INMUNIDAD AP tiempo_inmunidad CP
        | TIEMPO_INFECCION AP tiempo_infeccion CP
        | DIMENSION AP dimension CP
        | TRASABILIDAD AP trasabilidad CP
        | SIMULAR AP CP {cout<<endl;aux_automata.infectar_celulas();aux_automata.imprimir_estados();cout<<endl; }
        | SIMULAR AP simular CP 
        | INICIAR AP CP { automata_grid grid(n,m);grid.celulas_aleatorias();aux_automata  = grid; }
        ;

tiempo_inmunidad  : INT_NUM { tiempo_de_inmunidad = $1;}
                  ;
tiempo_infeccion : INT_NUM { tiempo_de_infeccion = $1;}
                 ;
dimension : INT_NUM COMA INT_NUM { n=$1;m=$3}
          ;
trasabilidad  : PORC_TRASABILIDAD { aux = stod($1);tasa_transmisibilidad = aux; }
              ;
simular : INT_NUM { for ( int i=0 ; i < $1 ;i++){
          cout<<endl;aux_automata.infectar_celulas();aux_automata.imprimir_estados();cout<<endl;
        } }

%%


int main(int argc, char const *argv[]){
   
  srand(time(0));
  printf("\nIngresa una funcion\n");
  yyin = stdin;
  yyparse();
  }
/* 
inputs de ej:
  dimension{5,5}
  trasabilidad{0.80}
  tiempo_infeccion{2}
  tiempo_inmunidad{3}
  inicia{}
  simular{} // puede ser sin argumento lo cual equivale a un ciclo
  simular{3} // o puede ser con un numero entero el cual equivale a n ciclos desde el estado actual
*/
//resetear genera otra grilla e inicia el AC
