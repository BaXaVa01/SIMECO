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
    int edad;
    int edadMinimaReproduccion;
    Genero genero;
};

Animal reproducirse(const Animal& padre, const Animal& madre) {
    Animal hijo;
    hijo.tipo = "Nuevo Animal";
    hijo.energia = (padre.energia + madre.energia) / 2;
    hijo.edad = 0;
    hijo.edadMinimaReproduccion = min(padre.edadMinimaReproduccion, madre.edadMinimaReproduccion);
    hijo.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;

    // Verificar edad mínima para reproducción
    if (padre.edad >= padre.edadMinimaReproduccion && madre.edad >= madre.edadMinimaReproduccion) {
        return hijo;
    } else {
        // Si no cumplen con la edad mínima, retorna un animal "nulo" o vacío
        Animal nulo;
        nulo.tipo = "Nulo";
        return nulo;
    }
}

int main() {
    // Inicializar tu población inicial de animales
    vector<Animal> animales;
    int numSemanas = 100;

    // Contadores para el resumen
    int nacimientosSemanal = 0;
    vector<int> conteoPorEdad(10, 0); // Asumiendo que la edad máxima es 10 semanas

    // Inicializar venados
    for (int i = 0; i < 2000; ++i) {
        Animal venado;
        venado.tipo = "Venado";
        venado.energia = 100;
        venado.edad = rand() % 5 + 1;
        venado.edadMinimaReproduccion = 2; // Edad mínima de reproducción para venados
        venado.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        animales.push_back(venado);
    }

    // Inicializar cuervos
    for (int i = 0; i < 10; ++i) {
        Animal cuervo;
        cuervo.tipo = "Cuervo";
        cuervo.energia = 80;
        cuervo.edad = rand() % 5 + 1;
        cuervo.edadMinimaReproduccion = 1; // Edad mínima de reproducción para cuervos
        cuervo.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        animales.push_back(cuervo);
    }

    // Inicializar pumas
    for (int i = 0; i < 20; ++i) {
        Animal puma;
        puma.tipo = "Puma";
        puma.energia = 150;
        puma.edad = rand() % 5 + 1;
        puma.edadMinimaReproduccion = 3; // Edad mínima de reproducción para pumas
        puma.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        animales.push_back(puma);
    }

    // Inicializar jaguares
    for (int i = 0; i < 20; ++i) {
        Animal jaguar;
        jaguar.tipo = "Jaguar";
        jaguar.energia = 200;
        jaguar.edad = rand() % 5 + 1;
        jaguar.edadMinimaReproduccion = 4; // Edad mínima de reproducción para jaguares
        jaguar.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        animales.push_back(jaguar);
    }

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

        // Actualizar el contador semanal
        nacimientosSemanal += nacimientosEnEstaSemana;

        // Actualizar conteo por edad
        for (const auto& animal : animales) {
            conteoPorEdad[animal.edad]++;
        }

        // Otras acciones semanales...
    }

    // Imprimir resumen
    cout << "Resumen de nacimientos semanal: " << nacimientosSemanal << " animales" << endl;
    cout << "Conteo de animales por edad:" << endl;
    for (size_t i = 0; i < conteoPorEdad.size(); ++i) {
        cout << "Edad " << i << " semanas: " << conteoPorEdad[i] << " animales" << endl;
    }

    return 0;
}
