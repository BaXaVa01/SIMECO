#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>

using namespace std;

enum class TipoDesastre {
    Incendio,
    Inundacion,
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

//Mejor empiezo con los animales en general

class Especies{
    public:
        int peso[3]; // [1]Peso minimo [2] Pedo medio [3] Peso maximo
        float consumo[3]; // [1] Consumo minimo [2] Consumo medio [3] Consumo maximo
        int edadRep[2]; // [1] Edad minima de reproduccion [2] Edad maxima de reproduccion Trabajaremos este apartado en semanas
        int edadMax; //Edad maxima de vida

};
//Empecemos con los venados

class Venado : public Especies {
    public:
        int edad;
        int hambre;
        int sed;
        bool genero;
    private:
        Venado(bool genero){
            if(genero) { //macho
                peso[1] = 68;
                peso[2] = 102;
                peso[3] = 136;
                consumo[1] = 28.56;
                consumo[2] = 42.84;
                consumo[3] = 57.12;
                edadRep[1] = 104;
                edadRep[2] = 234;
                edadMax = 234;
            } else{ //hembra
                peso[1] = 50;
                peso[2] = 70;
                peso[3] = 90;
                consumo[1] = 10;
                consumo[2] = 15;
                consumo[3] = 20;
                edadRep[1] = 2;
                edadRep[2] = 10;
                edadMax = 10;
            }

        }

};

int main(){

}
