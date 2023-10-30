
using namespace std;

//ESTRUCTRAS
struct Ecosistema
{
    int aguaCant;
    int hierbaCant;
    int carneCant;
    int carronaCant;

};
struct Desastres
{
    int tipoDesastre;
    int tiempoDesastre;
    int recursoAfectado;
    int cantidadAfectada;
    int animalesAfectados[4];
};

struct userSaved
{
    char Usuario[20];
};

struct Especie
{
    int ID;
    int cicloReproduccion;
    int probReproduccion;
    int tamanoReproduccion; //Para saber cuatos hijos puede tener
    int consumo;
    int edadMinRep;
    int edadMaxRep;
    int edadMax;
    int timeMaxSinComer;
    int timeMaxSinBeber; //Agregue esto para que no se muera de sed
};

struct Animal
{
    int ID;
    int peso;
    int edad;
    int gender;
    int nivelHambre; //Se mide en la escala de 0 a 3, siendo 0 el nivel mas bajo y 3 el mas alto
};

//FUNCIONES DE EQUILIBRIO
void ActualizacionRecursos;
void Equilibriobase;
void MedidorEquilibrioRecursos;
void MedidorEquilibrioAnimal;
