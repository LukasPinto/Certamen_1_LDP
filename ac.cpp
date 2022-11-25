#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// variables globales

// tasa de transmisión
float B;
// tasa de reclutamiento
float A;
// tasa de morbilidad
float a1;
// tasa de recuperacion
float a2;
// tasa de perdida de inmunidad
float p;
// tasa de mortalidad por razones distintas a la enfermedad
float u;
// tasa de mortalidad inducida por la enfermedad
float g;

float r;
float e;
float y;

class celula
{
public:
    vector<int> foto;
    vector<vector<int>> calendario;

    long ciclo;
    long infectados;
    long suceptibles;
    long expuestos;
    long recuperados;
    long total_poblacion;
    long total_poblacion_anterior; 
    long total_muertos;

    celula(int inf, int suc, int exps, int recup)
    {
        infectados = inf;
        suceptibles = suc;
        expuestos = exps;
        recuperados = recup;
        total_poblacion = infectados + suceptibles + expuestos + recuperados;
        total_poblacion_anterior = total_poblacion; 
        total_muertos = 0;
    }

    // Setter
    void set_total_poblacion()
    {
        total_poblacion = infectados + suceptibles + expuestos + recuperados;
    }

    void set_total_poblacion_anterior(){
        total_poblacion_anterior = total_poblacion; 
    }

    // tasa de cambio de los suceptibles
    float tasa_cambio_suceptibles(float recuperados_aux,float suceptibles_aux,float infectados_aux)
    {
         float tasa_cambio_S = (A*total_poblacion) - ((r * B*suceptibles_aux*infectados_aux)/total_poblacion) - (u*suceptibles_aux);
        //float tasa_cambio_S = A + (p * recuperados_aux) - (B * suceptibles_aux) - (u * suceptibles_aux);
        //cout << suceptibles_aux * u  <<endl;//+ (p * recuperados) - (B * suceptibles) - (u * suceptibles);
        return tasa_cambio_S;
    }

    float tasa_cambio_expuesto(float suceptibles_aux , float expuestos_aux, float infectados_aux)
    {
        
        float tasa_cambio_E = ceil(((r * B * suceptibles_aux * infectados_aux)/total_poblacion) - (e*expuestos_aux));
        //cout << tasa_cambio_E <<endl;
        //float tasa_cambio_E = (B * suceptibles_aux) - (a1 * expuestos_aux) - (u * expuestos_aux);
        
        return tasa_cambio_E;
    }

    float tasa_cambio_infectado(float expuestos_aux,float infectados_aux)
    {
        float tasa_cambio_I = (e*expuestos_aux) - (y*infectados_aux) - (u *infectados_aux);
        //float tasa_cambio_I = (a1 * expuestos_aux) - (a2 * infectados_aux) - (u * infectados_aux) - (g * infectados_aux);
        return tasa_cambio_I;
    }

    float tasa_cambio_recuperados(float infectados_aux,float recuperados_aux)
    {
        float tasa_cambio_R = ceil((y*infectados_aux) - (u * recuperados_aux));
        //float tasa_cambio_R = (a2 * infectados_aux) - (p * recuperados_aux) - (u * recuperados_aux);
        return tasa_cambio_R;
    }

    // calcular total poblacion

    // variacion datos
    void avance_enfermedad()
    {

     
        long expuestos_aux = expuestos ;
        long infectados_aux = infectados ;
        long recuperados_aux = recuperados ;
        long suceptibles_aux = suceptibles ;
        cout << "Ciclo numero: " << ciclo << endl;
        cout << "expuestos: " << expuestos << endl;
        cout << "infectados: " << infectados << endl;
        cout << "suceptibles: " << suceptibles << endl;
        cout << "recuperados: " << recuperados << endl;
        cout << "total de muertos: " << total_muertos << endl;
        cout << "poblacion total: " << total_poblacion<<endl;
        cout << ":::::::::::::::::::::::::::::" << endl;
        
        expuestos = expuestos_aux + tasa_cambio_expuesto(suceptibles_aux,expuestos_aux,infectados_aux);
        infectados = infectados_aux + tasa_cambio_infectado(expuestos_aux,infectados_aux);
        recuperados = recuperados_aux + tasa_cambio_recuperados(infectados_aux,recuperados_aux);
        suceptibles = suceptibles_aux + tasa_cambio_suceptibles( recuperados_aux,suceptibles_aux,infectados_aux);
        
        cout << "tasa de suceptibles: " << tasa_cambio_suceptibles(recuperados,suceptibles_aux,infectados_aux) << endl;
        cout << "tasa de expuestos: " << tasa_cambio_expuesto(suceptibles,expuestos_aux,infectados_aux) << endl;
        cout << "tasa de infectados: " << tasa_cambio_infectado(expuestos,infectados_aux) << endl;
        cout << "tasa de recuperados: " << tasa_cambio_recuperados(infectados,recuperados_aux) << endl;
        cout << endl;
        set_total_poblacion();
        
        total_muertos = total_poblacion_anterior - total_poblacion;
       
        set_total_poblacion_anterior();
    }
};

// determinar cantidad de gente que se va de la celula G_M
//  determinar que tipo de gente se va a mover
//  deteminar que cantidad de cada tipo se movera a cada celula

class grilla
{
public:
    float tasa_de_migracion; // numero entre 0 y 1, que determina el porcentaje de la población que se cambiará de celula.
    vector<vector<celula>> grid;
    vector<celula> fila_grid;
    vector<vector<celula>> grid_antigua;

    grilla(int max_infectados, int max_poblacion, int x, int y, float tasa_migracion)
    {
        tasa_de_migracion = tasa_migracion;
        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                int poblacion = 1 + rand() % max_poblacion;
                int infectado = 1 + rand() % max_infectados;
                celula manhattan(infectado, poblacion, 0, 0);
                fila_grid.push_back(manhattan);
            }
            grid.push_back(fila_grid);
            fila_grid.clear();
        }

        // igualamos la grid a la copia
        grid_antigua = grid;
    }

    void grilla_vacia(int max_infectados, int max_poblacion, int x, int y)
    {
        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                celula manhattan(0, 0, 0, 0);
                fila_grid.push_back(manhattan);
            }
            grid.push_back(fila_grid);
        }
    }

    void grilla_personalizada(int posicion_x, int posicion_y, int infectados, int suceptibles, int expuestos, int recuperados)
    {
        celula manhattan(infectados, suceptibles, expuestos, recuperados);
        grid[posicion_y][posicion_x] = manhattan;
    }

    // tranpaso de población.
    void transpaso_poblacion(int x, int y)
    {

        int infectados = grid_antigua[y][x].infectados * tasa_de_migracion;
        int suceptibles = grid_antigua[y][x].suceptibles * tasa_de_migracion;
        int expuestos = grid_antigua[y][x].expuestos * tasa_de_migracion;
        int recuperados = grid_antigua[y][x].recuperados * tasa_de_migracion;

        // definir donde van los migrantes

        srand(time(NULL));
        int n = infectados;
        int new_num;
        int aux = n; // para ir achicando el rango del random
        vector<int> indices = {0, 1, -1};

        // infectados
        while (aux > 0)
        {
            int indice_aux_x = indices[rand() % 3];
            int indice_aux_y = indices[rand() % 3];

            if (indice_aux_x == 0 and indice_aux_y == 0)
            {
                continue;
            }
            else
            {

                new_num = 1 + rand() % aux;
                grid_antigua[(y + indice_aux_y) % grid[0].size()][(x + indice_aux_x) % grid[0].size()].infectados += new_num;
                grid_antigua[(y + indice_aux_y) % grid[0].size()][(y + indice_aux_x) % grid[0].size()].set_total_poblacion();

                aux = aux - new_num;
            }
        }

        // recuperados
        srand(time(NULL));
        n = recuperados;
        aux = n; // para ir achicando el rango del random

        // infectados
        while (aux > 0)
        {
            int indice_aux_x = indices[rand() % 3];
            int indice_aux_y = indices[rand() % 3];

            if (indice_aux_x == 0 and indice_aux_y == 0)
            {
                continue;
            }
            else
            {

                new_num = 1 + rand() % aux;
                grid_antigua[(y + indice_aux_y) % grid[0].size()][(x + indice_aux_x) % grid[0].size()].recuperados += new_num;
                grid_antigua[(y + indice_aux_y) % grid[0].size()][(y + indice_aux_x) % grid[0].size()].set_total_poblacion();

                aux = aux - new_num;
            }
        }

        // expuestos
        srand(time(NULL));
        n = expuestos;
        aux = n; // para ir achicando el rango del rando

        // infectados
        while (aux > 0)
        {
            int indice_aux_x = indices[rand() % 3];
            int indice_aux_y = indices[rand() % 3];

            if (indice_aux_x == 0 and indice_aux_y == 0)
            {
                continue;
            }
            else
            {

                new_num = 1 + rand() % aux;
                grid_antigua[(y + indice_aux_y) % grid[0].size()][(x + indice_aux_x) % grid[0].size()].expuestos += new_num;
                grid_antigua[(y + indice_aux_y) % grid[0].size()][(y + indice_aux_x) % grid[0].size()].set_total_poblacion();

                aux = aux - new_num;
            }
        }

        // suceptibles
        srand(time(NULL));
        n = suceptibles;
        aux = n; // para ir achicando el rango del random

        // infectados
        while (aux > 0)
        {
            int indice_aux_x = indices[rand() % 3];
            int indice_aux_y = indices[rand() % 3];

            if (indice_aux_x == 0 and indice_aux_y == 0)
            {
                continue;
            }
            else
            {

                new_num = 1 + rand() % aux;
                grid_antigua[(y + indice_aux_y) % grid[0].size()][(x + indice_aux_x) % grid[0].size()].suceptibles += new_num;
                grid_antigua[(y + indice_aux_y) % grid[0].size()][(y + indice_aux_x) % grid[0].size()].set_total_poblacion();

                aux = aux - new_num;
            }
        }

        // restar los migrantes
        grid_antigua[y][x].infectados = grid[y][x].infectados - infectados;
        grid_antigua[y][x].suceptibles = grid[y][x].suceptibles - suceptibles;
        grid_antigua[y][x].expuestos = grid[y][x].expuestos - expuestos;
        grid_antigua[y][x].recuperados = grid[y][x].recuperados - recuperados;

        grid_antigua[y][x].set_total_poblacion();
    }
    void simular_celula(int y,int x ,int cant_generaciones){
        for (size_t i = 0; i < cant_generaciones; i++)
        {
        
            grid[y][x].avance_enfermedad();
            grid[y][x].set_total_poblacion();
        }
        

    }


};



int main(int argc, char const *argv[])
{
    srand(time(0));
    int largo = 5;
    int ancho = 5;
    
    //grilla con traspaso de poblacion
    grilla migrilla(100, 10000, largo, ancho, 0.1);
     for ( int i = 0 ; i < largo; i++) {
  
        for ( int j = 0 ; j < ancho; j++){
            cout << i<<"," <<j <<": "<< migrilla.grid[i][j].total_poblacion<< "||";
        }
        cout << endl;

    }
    cout << endl;
    for (int i = 0; i < largo; i++)
    {
        for (int j = 0; j < ancho; j++)
        {

            migrilla.transpaso_poblacion(j, i);
            migrilla.grid = migrilla.grid_antigua;
        }
    }
     for ( int i = 0 ; i < largo; i++) {
  
        for ( int j = 0 ; j < ancho; j++){
            cout << i<<"," <<j <<": "<< migrilla.grid[i][j].total_poblacion<< "||"; 
        }
        cout << endl;

    }
    cout << endl;
    // grilla sin traspaso de poblacion
    r = 100; // numero de contactos por unidad de tiempo
    B = 0.02; // probabilidad de contagiar a los contactos, va entre 0 y 1
    y = 0.8; // el ratio de recuperacion de la gente, va entre 0 y 1
    A = 0.0; // constante de nacimiento/reclutamiento
    u = 0.0; // la mortalidad per capita
    e = 0.7; // el ratio de progresion al estado infeccioso per capita
    grilla migrilla2(100,10000,3,3,0.1);
    // por temas de calculo va a perder poblacion total por

    migrilla2.simular_celula(0,0,10);
        



    return 0;
}
