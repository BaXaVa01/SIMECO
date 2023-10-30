#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Animal {
    string nombre;
    double energia;
    string tipo;

    Animal(string _nombre, double _energia, string _tipo) : nombre(_nombre), energia(_energia), tipo(_tipo) {}
};

bool Probabilidad(double prob) {
    return (rand() % 100) < prob;
}

void Simular(vector<Animal>& animales) {
    for (int i = 0; i < 13; i++) {
        cout << "Semana " << i + 1 << ":" << endl;

        for (size_t j = 0; j < animales.size(); j++) {
            animales[j].energia -= 1;
            cout << animales[j].nombre << " perdio 1 de energia." << endl;
        }

        for (size_t j = 0; j < animales.size(); j++) {
            for (size_t k = 0; k < animales.size(); k++) {
                if (j != k && animales[j].tipo == "Puma" && animales[k].tipo == "Venado" && Probabilidad(30)) {
                    animales[j].energia += 10;
                    animales[k].energia = 0;
                    cout << animales[j].nombre << " comio a " << animales[k].nombre << " y gano 10 de energia." << endl;
                }
                else if (j != k && animales[j].tipo == "Lobo" && animales[k].tipo == "Venado" && Probabilidad(30)) {
                    animales[j].energia += 10;
                    animales[k].energia = 0;
                    cout << animales[j].nombre << " comio a " << animales[k].nombre << " y gano 10 de energia." << endl;
                }
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Inicializa la semilla para números aleatorios
    vector<Animal> animales;
    animales.push_back(Animal("Puma1", 50.0, "Puma"));
    animales.push_back(Animal("Venado1", 50.0, "Venado"));
    animales.push_back(Animal("Lobo1", 50.0, "Lobo"));
    animales.push_back(Animal("Cuervo1", 50.0, "Cuervo"));

    Simular(animales);

    for (size_t i = 0; i < animales.size(); i++) {
        cout << animales[i].nombre << " tiene " << animales[i].energia << " de energia." << endl;
    }

    return 0;
}
