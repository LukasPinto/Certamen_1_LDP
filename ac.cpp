#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
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

// creación de un automata celular en base a caracteristicas anteriores
class automata_celular
{
public:
    int infectados, suceptibles, recuperados, poblacion;
    bool confinamiento; 

    // constructor
    automata_celular(int inf, int suc, int rec, bool conf)
    {
            confinamiento = conf; 
            infectados = inf;
            suceptibles = suc;
            recuperados = rec;
            poblacion = infectados + suceptibles + recuperados;
    }

    // alguien se infecta
    string infectar(int num_infectados)
    {
        if (suceptibles < num_infectados)
        {
            return "no se puede infectar a más que aquellos suceptibles";
        }
        else
        {
            suceptibles = suceptibles - num_infectados;
            infectados = infectados + num_infectados;
            return "se han infectado las personas exitosamente";
        }
    }

    string verificar_recuperados(int num_recuperados)
    {
        if (infectados < num_recuperados)
        {
            return "no se pueden recuperar más que aquellos infectados";
        }
        else
        {
            infectados = infectados - num_recuperados;
            recuperados = recuperados + num_recuperados;
            return "la gente se ha recuperado con exito";
        }
    }

    string random_automata(int max_population, int min_population)
    {
        confinamiento = rand() % 2 ; 
        infectados = rand() % max_population + min_population; 
        suceptibles = rand() % max_population + min_population; 
        recuperados = rand() % max_population + min_population; 
        poblacion = infectados + suceptibles + recuperados; 
        return "hemos creado este automata con valores al azar";
    }
};

// clase con el grid

class automata_grid
{
public:
    int x, y;
    vector<vector<automata_celular>> grid;
    vector<automata_celular> fila; 

    automata_grid(int x, int y){
        for(int i=0; i<x; i++){
            for(int j=0; j<y; j++){
                automata_celular automata(0,0,0,0);
                fila.push_back(automata);
            }
            grid.push_back(fila); 
            fila.clear();
        }
    }

    string insertar_automata(automata_celular automata, int x_pos, int y_pos){
        grid[x][y] = automata; 
        return "se ha insertado la celula con exito";
    }

    string eliminar_automata(int x_pos, int y_pos){
        automata_celular automata(0,0,0,0);
        grid[x][y] = automata; 
    }
};




main(int argc, char const *argv[])
{
    vector<automata_grid> timeline; 
    automata_celular automata(0,0,0,0); 

    /* code */
    return 0;
}
