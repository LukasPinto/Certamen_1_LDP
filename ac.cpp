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
float tasa_transmisibilidad;
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
                cout << grid[i][j].estado << grid[i][j].ciclo << " ";
            }
            cout << endl;
        }
    }

    string insertar_automata(celula automata, int x_pos, int y_pos)
    {
        grid[x][y] = automata;
        return "se ha insertado la celula con exito";
    }
};


int main(int argc, char const *argv[])
{
    // semilla
    srand(time(0));
    tiempo_de_infeccion = 5;
    tiempo_de_inmunidad = 5;
    tasa_transmisibilidad = 0.3;
    automata_grid grid(5, 5);
    grid.celulas_aleatorias();
    grid.imprimir_estados();

    /* code */
    return 0;
}

