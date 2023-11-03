#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

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

// Función para que los animales se reproduzcan
void reproduccion(vector<Animal>& poblacion, int semana_actual) {
    int num_nacimientos = 0;

    for (int i = 0; i < poblacion.size(); i++) {
        Animal& animal = poblacion[i];
        
        // Actualizar la edad del animal
        animal.edad++;

        if (animal.edad >= 104) {  // Edad mínima de reproducción para venados y cuervos
            if (animal.tipo == "Venado") {
                // Venado: puede tener de 2 a 3 crías
                int probabilidad_de_nacimiento = rand() % 13;  // 1/13 de probabilidad
                if (probabilidad_de_nacimiento == 0) {
                    int numero_de_crias = 2 + rand() % 2;  // Número aleatorio entre 2 y 3
                    for (int j = 0; j < numero_de_crias; j++) {
                        Genero genero = static_cast<Genero>(rand() % 2);
                        poblacion.push_back({"Venado", 50.0, 1, genero});
                        num_nacimientos++;
                    }
                }
            } else if (animal.tipo == "Cuervo") {
                // Cuervo: puede tener de 3 a 8 crías
                int probabilidad_de_nacimiento = rand() % 13;  // 1/13 de probabilidad
                if (probabilidad_de_nacimiento == 0) {
                    int numero_de_crias = 3 + rand() % 6;  // Número aleatorio entre 3 y 8
                    for (int j = 0; j < numero_de_crias; j++) {
                        Genero genero = static_cast<Genero>(rand() % 2);
                        poblacion.push_back({"Cuervo", 50.0, 1, genero});
                        num_nacimientos++;
                    }
                }
            }
        } else if (animal.edad >= 78) {  // Edad mínima de reproducción para lobos y pumas
            if (animal.tipo == "Lobo") {
                // Lobo: puede tener de 4 a 6 crías
                int probabilidad_de_nacimiento = rand() % 13;  // 1/13 de probabilidad
                if (probabilidad_de_nacimiento == 0) {
                    int numero_de_crias = 4 + rand() % 3;  // Número aleatorio entre 4 y 6
                    for (int j = 0; j < numero_de_crias; j++) {
                        Genero genero = static_cast<Genero>(rand() % 2);
                        poblacion.push_back({"Lobo", 50.0, 1, genero});
                        num_nacimientos++;
                    }
                }
            } else if (animal.tipo == "Puma") {
                // Puma: puede tener de 1 a 4 crías
                int probabilidad_de_nacimiento = rand() % 13;  // 1/13 de probabilidad
                if (probabilidad_de_nacimiento == 0) {
                    int numero_de_crias = 1 + rand() % 4;  // Número aleatorio entre 1 y 4
                    for (int j = 0; j < numero_de_crias; j++) {
                        Genero genero = static_cast<Genero>(rand() % 2);
                        poblacion.push_back({"Puma", 50.0, 1, genero});
                        num_nacimientos++;
                    }
                }
            }
        }
    }

    cout << "Se han producido " << num_nacimientos << " nacimientos." << endl;
}

int main() {
    // Inicializar la semilla para la generación aleatoria
    srand(static_cast<unsigned int>(time(nullptr)));

    // Inicializar una población de animales
    vector<Animal> poblacion;

    // Agregar 2000 venados, 50 pumas, 50 lobos y 25 cuervos
    for (int i = 0; i < 2000; i++) {
        Genero genero = static_cast<Genero>(rand() % 2); // 0 para MACHO, 1 para HEMBRA
        poblacion.push_back({"Venado", 50.0, 104, genero});
    }

    for (int i = 0; i < 50; i++) {
        Genero genero = static_cast<Genero>(rand() % 2); // 0 para MACHO, 1 para HEMBRA
        poblacion.push_back({"Puma", 50.0, 78, genero});
    }

    for (int i = 0; i < 50; i++) {
        Genero genero = static_cast<Genero>(rand() % 2); // 0 para MACHO, 1 para HEMBRA
        poblacion.push_back({"Lobo", 50.0, 78, genero});
    }

    for (int i = 0; i < 25; i++) {
        Genero genero = static_cast<Genero>(rand() % 2); // 0 para MACHO, 1 para HEMBRA
        poblacion.push_back({"Cuervo", 50.0, 104, genero});
    }

    // Realizar la reproducción
    reproduccion(poblacion, 0); // Semana 0

    // Avanzar dos semanas adicionales (ciclos semanales)
    for (int semana = 0; semana < 2; semana++) {
        reproduccion(poblacion, semana + 1); // Ajustar la semana actual
    }

    // Actualizar la edad de los animales
    for (Animal& animal : poblacion) {
        animal.edad++;
    }

    // Imprimir todos los animales en la población después de las 3 semanas
    for (const Animal& animal : poblacion) {
        cout << "Tipo: " << animal.tipo << ", Energía: " << animal.energia << ", Edad: " << animal.edad << " semanas, Genero: " << (animal.genero == MACHO ? "MACHO" : "HEMBRA") << endl;
    }

    // Calcular el resumen
    int total_venados = 0;
    int machos_venado = 0;
    int hembras_venado = 0;
    int total_cuervos = 0;
    int machos_cuervo = 0;
    int hembras_cuervo = 0;
    int total_lobos = 0;
    int machos_lobo = 0;
    int hembras_lobo = 0;
    int total_pumas = 0;
    int machos_puma = 0;
    int hembras_puma = 0;
    double suma_energia = 0;

    for (const Animal& animal : poblacion) {
        if (animal.tipo == "Venado") {
            total_venados++;
            if (animal.genero == MACHO) {
                machos_venado++;
            } else {
                hembras_venado++;
            }
        } else if (animal.tipo == "Cuervo") {
            total_cuervos++;
            if (animal.genero == MACHO) {
                machos_cuervo++;
            } else {
                hembras_cuervo++;
            }
        } else if (animal.tipo == "Lobo") {
            total_lobos++;
            if (animal.genero == MACHO) {
                machos_lobo++;
            } else {
                hembras_lobo++;
            }
        } else if (animal.tipo == "Puma") {
            total_pumas++;
            if (animal.genero == MACHO) {
                machos_puma++;
            } else {
                hembras_puma++;
            }
        }

        suma_energia += animal.energia;
    }

    double promedio_energia = suma_energia / poblacion.size();

    // Imprimir el resumen
    cout << "Resumen:" << endl;
    cout << "Total de Venados: " << total_venados << " (Machos: " << machos_venado << ", Hembras: " << hembras_venado << ")" << endl;
    cout << "Total de Cuervos: " << total_cuervos << " (Machos: " << machos_cuervo << ", Hembras: " << hembras_cuervo << ")" << endl;
    cout << "Total de Lobos: " << total_lobos << " (Machos: " << machos_lobo << ", Hembras: " << hembras_lobo << ")" << endl;
    cout << "Total de Pumas: " << total_pumas << " (Machos: " << machos_puma << ", Hembras: " << hembras_puma << ")" << endl;
    cout << "Promedio de Energía: " << promedio_energia << endl;

    return 0;
}
