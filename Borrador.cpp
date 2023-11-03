#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enum para el género
enum Genero {
    MACHO,
    HEMBRA
};

// Struct para representar los animales
struct Animal {
    string tipo;
    double energia;
    int edad;
    Genero genero;
};

int main() {
    // Inicializar la semilla para la generación aleatoria
    srand(static_cast<unsigned int>(time(nullptr)));

    // Inicializar una población de animales
    vector<Animal> poblacion;

    // Agregar 2000 venados, 50 pumas, 50 lobos y 25 cuervos
    for (int i = 0; i < 2000; i++) {
        Genero genero = static_cast<Genero>(rand() % 2); // 0 para MACHO, 1 para HEMBRA
        poblacion.push_back({"Venado", 50.0, 1, genero});
    }

    for (int i = 0; i < 50; i++) {
        Genero genero = static_cast<Genero>(rand() % 2); // 0 para MACHO, 1 para HEMBRA
        poblacion.push_back({"Puma", 50.0, 2, genero});
    }

    for (int i = 0; i < 50; i++) {
        Genero genero = static_cast<Genero>(rand() % 2); // 0 para MACHO, 1 para HEMBRA
        poblacion.push_back({"Lobo", 50.0, 3, genero});
    }

    for (int i = 0; i < 25; i++) {
        Genero genero = static_cast<Genero>(rand() % 2); // 0 para MACHO, 1 para HEMBRA
        poblacion.push_back({"Cuervo", 50.0, 1, genero});
    }

    // Imprimir todos los animales en la población
    for (const Animal& animal : poblacion) {
        cout << "Tipo: " << animal.tipo << ", Energía: " << animal.energia << ", Edad: " << animal.edad << ", Género: " << (animal.genero == MACHO ? "MACHO" : "HEMBRA") << endl;
    }

    return 0;
}
