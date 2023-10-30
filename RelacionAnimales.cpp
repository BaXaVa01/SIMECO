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
    int semanasParaReproducir;  // Número de semanas requeridas para la reproducción
    int semanasPasadas;  // Número de semanas pasadas desde la última reproducción

    Animal(string _nombre, double _energia, string _tipo, int _semanasParaReproducir) : nombre(_nombre), energia(_energia), tipo(_tipo), semanasParaReproducir(_semanasParaReproducir), semanasPasadas(0) {}
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

            // Verificar si el animal puede reproducirse
            if (animales[j].semanasPasadas >= animales[j].semanasParaReproducir) {
                string nuevoNombre = animales[j].nombre + "Hijo";  // Nuevo nombre para el hijo
                Animal hijo(nuevoNombre, 50.0, animales[j].tipo, animales[j].semanasParaReproducir);  // Crear el nuevo animal hijo
                animales.push_back(hijo);  // Agregar el hijo a la lista de animales
                cout << animales[j].nombre << " se reprodujo y nacio " << nuevoNombre << "." << endl;
                animales[j].semanasPasadas = 0;  // Reiniciar las semanas pasadas
            } else {
                animales[j].semanasPasadas++;  // Incrementar las semanas pasadas
            }
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
    animales.push_back(Animal("Puma1", 50.0, "Puma", 5));  // Se requieren 5 semanas para la reproducción
    animales.push_back(Animal("Venado1", 50.0, "Venado", 3));  // Se requieren 3 semanas para la reproducción
    animales.push_back(Animal("Lobo1", 50.0, "Lobo", 4));  // Se requieren 4 semanas para la reproducción
    animales.push_back(Animal("Cuervo1", 50.0, "Cuervo", 2));  // Se requieren 2 semanas para la reproducción

    Simular(animales);

    for (size_t i = 0; i < animales.size(); i++) {
        cout << animales[i].nombre << " tiene " << animales[i].energia << " de energia." << endl;
    }

    return 0;
}
