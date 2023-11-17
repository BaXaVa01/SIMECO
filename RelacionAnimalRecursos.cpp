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
    //Atributos peso = kg, consumo = kg/semana, edad = semanas
        int peso; // [1]Peso minimo [2] Pedo medio [3] Peso maximo
        float consumo; // [1] Consumo minimo [2] Consumo medio [3] Consumo maximo
        int edadRep; // [1] Edad minima de reproduccion [2] Edad maxima de reproduccion Trabajaremos este apartado en semanas
        int edadMax; //Edad maxima de vida

};
//Empecemos con los venados

class Venado : public Especies {
    public:
        Venado(bool genero, int edadInicial) : genero(genero), edad(edadInicial){
            if(genero){
                iniciarMacho();
            }
            else{
                iniciarHembra();
            }
        }
        void envejecer(){
            edad++;
            if(edad > edadMax){
                vivo = false;
            }

        }
    private:
        int edadMax = 234;
        int edad;
        int hambre;
        int sed;
        bool genero;
        bool vivo = true;

        void iniciarMacho(){

           //Cervatillo
           if(edad >= 0 && edad < 30){
                peso = 68;
                consumo = 28.56;
                return;
           }
           //Adolescente
           if(edad > 30 && edad < 78){
                peso = 102;
                consumo = 42.84;
                return;
           }
           //Adulto
           if(edad > 78){
                peso = 136;
                consumo = 57.12;

                return;
           }
// edadRep= 104;
// edadRep[1] = 234;
// 
            
        }
        void iniciarHembra(){
           //Cervatillo
           if(edad >= 0 && edad < 30){
                peso = 45;
                consumo = 18.9;
                return;
           }
           //Adolescente
           if(edad > 30 && edad < 78){
                peso = 72;
                consumo = 30.45;
                return;
           }
           //Adulto
           if(edad > 78){
                peso = 100;
                consumo = 42.00;

                return;
           }
        }

};
