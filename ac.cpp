#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

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


int main(int argc, char const *argv[])
{
    // semilla
    srand(time(0));
    tiempo_de_infeccion = 3;
    tiempo_de_inmunidad = 3;
    tasa_transmisibilidad = 1;
    automata_grid grid(10, 10);
    grid.celulas_aleatorias();
    grid.imprimir_estados();
    cout<<endl;
    grid.infectar_celulas();
    grid.imprimir_estados();

    /* code */
    return 0;
}

