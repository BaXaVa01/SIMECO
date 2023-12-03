#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>

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
enum class TipoDesastre {
    Incendio,
    inundacion,
    Sequia,
    Huracan
};

class Especie {
public:
    string nombre;
    int poblacionInicial;
    int poblacion;

    Especie(string nombre, int poblacionInicial) : nombre(nombre), poblacionInicial(poblacionInicial), poblacion(poblacionInicial) {}
};

class Recursos {
public:
    int agua;
    int carrona;
    int carne;
    int vegetacion;

    Recursos(int agua, int carrona, int carne, int vegetacion) : agua(agua), carrona(carrona), carne(carne), vegetacion(vegetacion) {}
};

class Ecosistema {
public:
    vector<Especie> especies;
    Recursos recursosIniciales;
    Recursos recursosActuales;

    Ecosistema(const vector<Especie>& especies, const Recursos& recursos)
        : especies(especies), recursosIniciales(recursos), recursosActuales(recursos) {}
};
class Animal {
    public:
        string tipo;
        double energia;
        int edad;
        int edadMinimaReproduccion;
        //Genero genero;
        int semanasDesdeUltimaCria;
};