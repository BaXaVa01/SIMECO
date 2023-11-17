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
    int semanasDesdeUltimaCria;
};

int numSemanas = 10;
vector<Animal> animales;

Animal reproducirse(const Animal& padre, const Animal& madre) {
    if (padre.tipo != madre.tipo || (madre.genero == HEMBRA && madre.semanasDesdeUltimaCria < 5)) {
        Animal nulo;
        nulo.tipo = "Nulo";
        return nulo;
    }

    Animal hijo;
    hijo.tipo = padre.tipo;
    hijo.energia = (padre.energia + madre.energia) / 2;
    hijo.edad = 0;
    hijo.edadMinimaReproduccion = madre.edadMinimaReproduccion;
    hijo.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;

    if (hijo.edadMinimaReproduccion <= 0 || (padre.edad >= padre.edadMinimaReproduccion && madre.edad >= madre.edadMinimaReproduccion)) {
        hijo.semanasDesdeUltimaCria = (hijo.genero == HEMBRA) ? 0 : madre.semanasDesdeUltimaCria + 1;

        Animal madreCopia = madre;

        if (madreCopia.genero == HEMBRA && hijo.genero == HEMBRA && madreCopia.semanasDesdeUltimaCria == 0) {
            madreCopia.energia -= 10;
        }

        return hijo;
    } else {
        Animal nulo;
        nulo.tipo = "Nulo";
        return nulo;
    }
}

void imprimirResumen(const string& mensaje, int animalesMuertos) {
    cout << mensaje << endl;
    int numMachos = 0, numHembras = 0, numNacimientos = 0;

    for (const auto& animal : animales) {
        if (animal.genero == MACHO) {
            numMachos++;
        } else if (animal.genero == HEMBRA) {
            numHembras++;
        }
    }

    for (size_t i = 0; i < animales.size(); ++i) {
        if (animales[i].semanasDesdeUltimaCria == 0 && animales[i].genero == HEMBRA) {
            numNacimientos++;
        }
    }

    cout << "Machos: " << numMachos << ", Hembras: " << numHembras << ", Nacimientos: " << numNacimientos << ", Animales Muertos: " << animalesMuertos << endl;
}

int main() {
    srand(time(0));

    for (int i = 0; i < 20; ++i) {
        Animal venado;
        venado.tipo = "Venado";
        venado.energia = 100;
        venado.edad = rand() % 53 + 52;
        venado.edadMinimaReproduccion = 52;
        venado.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        venado.semanasDesdeUltimaCria = 0;
        animales.push_back(venado);
    }

    for (int i = 0; i < 5; ++i) {
        Animal cuervo;
        cuervo.tipo = "Cuervo";
        cuervo.energia = 100;
        cuervo.edad = rand() % 53 + 52;
        cuervo.edadMinimaReproduccion = 52;
        cuervo.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        cuervo.semanasDesdeUltimaCria = 0;
        animales.push_back(cuervo);
    }

    for (int i = 0; i < 10; ++i) {
        Animal puma;
        puma.tipo = "Puma";
        puma.energia = 100;
        puma.edad = rand() % 36 + 36;  
        puma.edadMinimaReproduccion = 36;
        puma.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        puma.semanasDesdeUltimaCria = 0;
        animales.push_back(puma);
    }

    for (int i = 0; i < 10; ++i) {
        Animal jaguar;
        jaguar.tipo = "Jaguar";
        jaguar.energia = 100;
        jaguar.edad = rand() % 36 + 36;  
        jaguar.edadMinimaReproduccion = 36;
        jaguar.genero = (rand() % 2 == 0) ? MACHO : HEMBRA;
        jaguar.semanasDesdeUltimaCria = 0;
        animales.push_back(jaguar);
    }

    imprimirResumen("Poblacion inicial:", 0);

    for (int semana = 1; semana <= numSemanas; ++semana) {
        int nacimientosEnEstaSemana = 0;
        int animalesMuertosEnEstaSemana = 0;

        for (size_t i = 0; i < animales.size(); ++i) {
            for (size_t j = i + 1; j < animales.size(); ++j) {
                Animal hijo = reproducirse(animales[i], animales[j]);
                if (hijo.tipo != "Nulo") {
                    animales.push_back(hijo);
                    nacimientosEnEstaSemana++;
                }
            }
        }

        for (size_t i = 0; i < animales.size(); ++i) {
            animales[i].edad++;
            animales[i].energia -= 5;

            if (animales[i].genero == HEMBRA && animales[i].edad >= animales[i].edadMinimaReproduccion) {
                animales[i].semanasDesdeUltimaCria++;
            }

            if (animales[i].genero == HEMBRA && animales[i].semanasDesdeUltimaCria == 0) {
                animales[i].energia -= 10;
            }

            if (animales[i].energia <= 0 || animales[i].edad > 520) {
                animalesMuertosEnEstaSemana++;
            }
        }

        imprimirResumen("Resumen semana " + to_string(semana) + ":", animalesMuertosEnEstaSemana);
    }

    return 0;
}


