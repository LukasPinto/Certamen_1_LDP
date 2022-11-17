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
            cout << rand_val << "<=" << tasa_transmisibilidad<<endl;

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
    vector<vector<celula>> nueva_grid;
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
                cout << grid[i][j].estado << grid[i][j].ciclo << " ";
            }
            cout << endl;
        }
    }


     void actualizar_grid(){
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                grid[i][j] = nueva_grid[i][j];
            }
           
        }
    }

    void infectar_celulas()
    {
      for(int i = 0;i < x;i++)
      {
        for ( int j =0;j<y;j++)
        {  

          /*
           [y-1,x-1][y-1,x][y-1,x+1]
           [y,x-1]  [y,x]  [y,x+1]
           [y+1,x-1][y+1,x][y+1,x+1]*/
          
          if(grid[i][j].estado == "I" && grid[i][j].ciclo+1<=tiempo_de_infeccion)
          //en base a una posicion infectada infecto las que estan al rededor
          {
            if(grid[(unsigned int)(i - 1)%x][(unsigned int)(j - 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i - 1)%x][(unsigned int)(j - 1)%y].infectar();
            }else if(grid[(unsigned int)(i)%x][(unsigned int)(j - 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i)%x][(unsigned int)(j - 1)%y].infectar();
            }
            else if(grid[(unsigned int)(i + 1)%x][(unsigned int)(j - 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i + 1)%x][(unsigned int)(j - 1)%y].infectar();
            }
            else if(grid[(unsigned int)(i - 1)%x][(unsigned int)(j)%y].estado == "S"){
                nueva_grid[(unsigned int)(i - 1)%x][(unsigned int)(j)%y].infectar();
            }
            else if(grid[(unsigned int)(i + 1)%x][(unsigned int)(j)%y].estado == "S"){
                nueva_grid[(unsigned int)(i + 1)%x][(unsigned int)(j)%y].infectar();
            }
            else if(grid[(unsigned int)(i - 1)%x][(unsigned int)(j + 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i - 1)%x][(unsigned int)(j + 1)%y].infectar();
            }  
            else if(grid[(unsigned int)(i)%x][(unsigned int)(j + 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i)%x][(unsigned int)(j + 1)%y].infectar();
            }
            else if(grid[(unsigned int)(i + 1)%x][(unsigned int)(j + 1)%y].estado == "S"){
                nueva_grid[(unsigned int)(i + 1)%x][(unsigned int)(j + 1)%y].infectar();
            }
            nueva_grid[i][j].ciclo = grid[i][j].ciclo+1;
          }
          else if (grid[i][j].ciclo+1>tiempo_de_infeccion && grid[i][j].estado == "I"){
            nueva_grid[i][j].estado = "R";
            nueva_grid[i][j].ciclo = 1;
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
          else{
             nueva_grid[i][j] = grid[i][j];
          }
        /*else if(grid[i][j].estado == "S"){
            nueva_grid[i][j] = grid[i][j];
        }*/
        }
      }

    actualizar_grid();
    }

    void crear_new_grid(){
        //crear una grilla auxiliar vacia
        fila.clear();
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                
                fila.push_back(grid[i][j]);
            }
            nueva_grid.push_back(fila);
            fila.clear();
        }
    }


  


};


int main(int argc, char const *argv[])
{
    // semilla
    srand(time(0));
    tiempo_de_infeccion = 3;
    tiempo_de_inmunidad = 3;
    tasa_transmisibilidad = 1;
    automata_grid grid(5, 5);
    grid.celulas_aleatorias();
    grid.imprimir_estados();
    grid.crear_new_grid();
    cout<<endl;
    grid.infectar_celulas();
    grid.imprimir_estados();

    /* code */
    return 0;
}

