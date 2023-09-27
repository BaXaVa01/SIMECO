#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cctype>
#include <math.h>
using namespace std;

//ESTRUCTRAS
struct Ecosistema
{
    string nombreE;
    char lugar,tipo;
    int tamano,RecursosTotal;
    struct Ambiente
    {
        int Clima,Temperatura,Humedad;
    };
    
};
struct Desastres
{
    char nombreD;
    int Amenaza,Potencial;
};
struct AnimalesDentro
{
    string nombreComun;
    string nombreCientifico;
    int ValorDepredacion,Rudeza,ConsumoAnimal,ConsumoAmbiente;
    int EpocaApareamiento,ProbApareamiento,TamanoReproduccion;

};
struct DiccionarioAnimales
{
    string nombreComun;
    string nombreCientifico;
    int ValorDepredacion,Rudeza,ConsumoAnimal,ConsumoAmbiente;
    int EpocaApareamiento,ProbApareamiento,TamanoReproduccion;
};


//Variables
int aleatorio;
int switchnum = 0;
int num = -1;
int Temp;
int Temp2;
int cantespacios = 0;
bool valid;
bool terminar = false;

//FUNCIONES DE EQUILIBRIO
void ActualizacionRecursos;
void Equilibriobase;
void MedidorEquilibrioRecursos;
void MedidorEquilibrioAnimal;