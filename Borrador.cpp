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

enum TipoDeConsumo {
    HERBIVORO,
    CARNIVORO,
    CARRONERO
};

enum Tamano {
    MEDIANO,
    GRANDE,
    PEQUENO
};

struct Animal {
    string tipo;
    double energia;
    int edad;  // Edad en semanas
    int edadMinimaReproduccion;
    Genero genero;
    int semanasDesdeUltimaCria;  // Nueva variable para controlar el tiempo de pausa
    TipoDeConsumo tipoDeConsumo;  // Nuevo dato para el tipo de consumo
    Tamano tamano;  // Nuevo dato para el tamaño
};

int numSemanas = 12; 

void cazar(Animal& depredador, Animal& presa, vector<Animal>& animales, vector<Animal>& animalesMuertos) {
    // Simular la caza y alimentación
    if (depredador.tipoDeConsumo == CARNIVORO && presa.tipoDeConsumo == HERBIVORO) {
        // Verificar la compatibilidad de tamaño para el consumo
        if (depredador.tamano == GRANDE || (depredador.tamano == MEDIANO && presa.tamano != GRANDE) ||
            (depredador.tamano == PEQUENO && presa.tamano == PEQUENO)) {
            depredador.energia += 20;  // Incrementar la energía del carnívoro al cazar un herbívoro
            presa.energia -= 20;  // Reducir la energía del herbívoro al ser cazado

            // Transferir parte de la energía del venado a la carroña
            int energiaTransferida = 5;
            for (auto& animal : animales) {
                if (animal.tipoDeConsumo == CARRONERO && animal.tipo == "Carrona") {
                    animal.energia += energiaTransferida;
                    break;  // Transferir la energía a un solo carroñero
                }
            }
        } else {
            // Carnívoro no puede cazar a este herbívoro debido al tamaño
            cout << "El " << depredador.tipo << " no puede cazar al " << presa.tipo << " debido al tamaño." << endl;
        }
    } else if (depredador.tipoDeConsumo == CARRONERO && presa.tipoDeConsumo == CARRONERO) {
        depredador.energia += 10;  // Incrementar la energía del carroñero al alimentarse de carroña
        presa.energia -= 10;  // Reducir la energía de la carroña al ser consumida

        // Registrar animal muerto por interacción
        animalesMuertos.push_back(presa);
    }
}

Animal reproducirse(const Animal& padre, const Animal& madre) {
    // Lógica de reproducción
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

void imprimirPoblacion(const string& mensaje, const vector<Animal>& animales) {
    cout << mensaje << endl;
    for (const auto& animal : animales) {
        cout << "Tipo: " << animal.tipo << ", Edad: " << animal.edad << " semanas, Genero: " << (animal.genero == MACHO ? "MACHO" : "HEMBRA")
             << ", Energia: " << animal.energia << ", Tipo de Consumo: " << (animal.tipoDeConsumo == HERBIVORO ? "HERBIVORO" : (animal.tipoDeConsumo == CARNIVORO ? "CARNIVORO" : "CARRONERO"))
             << ", Tamano: " << (animal.tamano == MEDIANO ? "MEDIANO" : (animal.tamano == GRANDE ? "GRANDE" : "PEQUENO"));

        if (animal.genero == HEMBRA && animal.edad >= animal.edadMinimaReproduccion) {
            cout << ", Semanas desde la ultima cria: " << animal.semanasDesdeUltimaCria;
        }
        cout << endl;
    }
}

int main() {
    // Inicializar la población de venados
    vector<Animal> animales;
    vector<Animal> animalesMuertos; 

    for (int i = 0; i < 20; ++i) {
        Animal venado;
        venado.tipo = "Venado";
        venado.energia = 100;
        venado.edad = rand() % 53 + 52;  // Rango entre 52 y 104 semanas
        venado.edadMinimaReproduccion = 52;  // Edad mínima de reproducción para venados
        venado.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        venado.semanasDesdeUltimaCria = 0;
        venado.tipoDeConsumo = HERBIVORO;
        venado.tamano = MEDIANO;  // Asignar tamaño según tus necesidades

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
        cuervo.tipoDeConsumo = CARRONERO;
        cuervo.tamano = PEQUENO;  // Asignar tamaño según tus necesidades

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
        puma.tipoDeConsumo = CARNIVORO;
        puma.tamano = GRANDE;  // Asignar tamaño según tus necesidades

        animales.push_back(puma);
    }

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


    // Inicializar la población de jaguares
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
        imprimirPoblacion("Poblacion al final de la semana " + to_string(semana) + ":", animales);
    }

    return 0;
}
