#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

enum Genero {
    MACHO,
    HEMBRA
};

struct Animal {
    string tipo;
    double energia;
    int edad;  // Edad en semanas
    int edadMinimaReproduccion;
    Genero genero;
    int semanasDesdeUltimaCria;  // Nueva variable para controlar el tiempo de pausa
};

// Variables globales
int numSemanas = 10;  // Ajusta según tus necesidades
vector<Animal> animales;

Animal reproducirse(const Animal& padre, const Animal& madre) {
    // Verificar si los animales son del mismo tipo y si la hembra ha pasado suficiente tiempo desde la última cría
    if (padre.tipo != madre.tipo || (madre.genero == HEMBRA && madre.semanasDesdeUltimaCria < 5)) {
        // Si no cumplen con las condiciones, retornar un animal "nulo" o vacío
        Animal nulo;
        nulo.tipo = "Nulo";
        return nulo;
    }

    Animal hijo;
    hijo.tipo = padre.tipo;  // El hijo tendrá el mismo tipo que los padres
    hijo.energia = (padre.energia + madre.energia) / 2;
    hijo.edad = 0;
    hijo.edadMinimaReproduccion = madre.edadMinimaReproduccion;
    hijo.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;

    // Verificar edad mínima para reproducción
    if (hijo.edadMinimaReproduccion <= 0 || (padre.edad >= padre.edadMinimaReproduccion && madre.edad >= madre.edadMinimaReproduccion)) {
        // Establecer las semanas desde la última cría para la cría hembra como 0
        hijo.semanasDesdeUltimaCria = (hijo.genero == HEMBRA) ? 0 : madre.semanasDesdeUltimaCria + 1;

        // Hacer una copia de la madre antes de modificar su energía
        Animal madreCopia = madre;

        // Restar 10 de energía a la madre solo si es una hembra y ha dado a luz
        if (madreCopia.genero == HEMBRA && hijo.genero == HEMBRA && madreCopia.semanasDesdeUltimaCria == 0) {
            madreCopia.energia -= 10;
        }

        return hijo;
    } else {
        // Si no cumplen con la edad mínima, retornar un animal "nulo" o vacío
        Animal nulo;
        nulo.tipo = "Nulo";
        return nulo;
    }
}

void imprimirPoblacion(const string& mensaje) {
    cout << mensaje << endl;
    for (const auto& animal : animales) {
        cout << "Tipo: " << animal.tipo << ", Edad: " << animal.edad << " semanas, Genero: " << (animal.genero == MACHO ? "MACHO" : "HEMBRA") << ", Energia: " << animal.energia;
        if (animal.genero == HEMBRA && animal.edad >= animal.edadMinimaReproduccion) {
            cout << ", Semanas desde la ultima cria: " << animal.semanasDesdeUltimaCria;
        }
        cout << endl;
    }
}

int main() {
    // Inicializar la población de venados
    for (int i = 0; i < 20; ++i) {
        Animal venado;
        venado.tipo = "Venado";
        venado.energia = 100;
        venado.edad = rand() % 53 + 52;  // Rango entre 52 y 104 semanas
        venado.edadMinimaReproduccion = 52;  // Edad mínima de reproducción para venados
        venado.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        venado.semanasDesdeUltimaCria = 0;
        animales.push_back(venado);
    }

    // Inicializar la población de cuervos
    for (int i = 0; i < 5; ++i) {
        Animal cuervo;
        cuervo.tipo = "Cuervo";
        cuervo.energia = 100;
        cuervo.edad = rand() % 53 + 52;
        cuervo.edadMinimaReproduccion = 52;  // Edad mínima de reproducción para cuervos
        cuervo.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        cuervo.semanasDesdeUltimaCria = 0;
        animales.push_back(cuervo);
    }

    // Inicializar la población de pumas
    for (int i = 0; i < 10; ++i) {
        Animal puma;
        puma.tipo = "Puma";
        puma.energia = 100;
        puma.edad = rand() % 36 + 36;  
        puma.edadMinimaReproduccion = 36;  // Edad mínima de reproducción para pumas
        puma.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        puma.semanasDesdeUltimaCria = 0;
        animales.push_back(puma);
    }

    // Inicializar la población de jaguares
    for (int i = 0; i < 10; ++i) {
        Animal jaguar;
        jaguar.tipo = "Jaguar";
        jaguar.energia = 100;
        jaguar.edad = rand() % 36 + 36;  
        jaguar.edadMinimaReproduccion = 36;  // Edad mínima de reproducción para jaguares
        jaguar.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        jaguar.semanasDesdeUltimaCria = 0;
        animales.push_back(jaguar);
    }

    // Imprimir la población inicial
    imprimirPoblacion("Poblacion inicial:");

    // Simulación semanal
    for (int semana = 1; semana <= numSemanas; ++semana) {
        int nacimientosEnEstaSemana = 0;

        // Lógica de reproducción
        for (size_t i = 0; i < animales.size(); ++i) {
            for (size_t j = i + 1; j < animales.size(); ++j) {
                Animal hijo = reproducirse(animales[i], animales[j]);
                if (hijo.tipo != "Nulo") {
                    animales.push_back(hijo);
                    nacimientosEnEstaSemana++;
                }
            }
        }

        // Actualizar el estado de los animales existentes
        for (size_t i = 0; i < animales.size(); ++i) {
            animales[i].edad++;  // Incrementar la edad en 1 semana
            animales[i].energia -= 5;

            // Incrementar las semanas desde la última cría para las hembras
            if (animales[i].genero == HEMBRA && animales[i].edad >= animales[i].edadMinimaReproduccion) {
                animales[i].semanasDesdeUltimaCria++;
            }

            // Restar 10 de energía a la madre solo si es una hembra y ha dado a luz esta semana
            if (animales[i].genero == HEMBRA && animales[i].semanasDesdeUltimaCria == 0) {
                animales[i].energia -= 10;
            }

            // Si el animal se queda sin energía o supera la edad límite, eliminarlo
            if (animales[i].energia <= 0 || animales[i].edad > 520) {
                cout << "El " << animales[i].tipo << " ha muerto." << endl;
                animales.erase(animales.begin() + i);
                i--;
            }
        }

        // Imprimir la población al final de cada semana
        imprimirPoblacion("Poblacion al final de la semana " + to_string(semana) + ":");
    }

    return 0;
}
