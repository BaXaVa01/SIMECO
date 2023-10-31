#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <map>
#include <random>

using namespace std;

struct NombreAnimal {
    string tipo;
    int generacion;

    NombreAnimal(string _tipo, int _generacion) : tipo(_tipo), generacion(_generacion) {}
};

struct Animal {
    NombreAnimal nombre;
    double energia;
    int semanasParaReproducir;
    int semanasPasadas;
    bool haComido;
    int venadosCazados;
    int semanasSinCazar;

    Animal(NombreAnimal _nombre, double _energia, int _semanasParaReproducir) : nombre(_nombre), semanasSinCazar(0), energia(_energia), semanasParaReproducir(_semanasParaReproducir), semanasPasadas(0), haComido(false), venadosCazados(0) {}
};

bool Probabilidad(double prob) {
    return (rand() % 100) < prob;
}

int GenerarNacimientosAleatorios(std::mt19937& rng, std::uniform_int_distribution<int>& distribucion) {
    return distribucion(rng);
}

void Simular(map<int, vector<Animal>>& animalesPorGeneracion, set<string>& generaciones, int& poblacionVenados) {
    for (int i = 0; i < 13; i++) {
        cout << "Semana " << i + 1 << " - Resumen:" << endl;

        int venadosMuertos = 0;

        // Generar una distribución de números aleatorios para los nacimientos aleatorios
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> distribucionNacimientosVenado(0, 60);  // Rango para venados
        uniform_int_distribution<int> distribucionNacimientosLoboPuma(0, 10); // Rango para lobos y pumas
        uniform_int_distribution<int> distribucionNacimientosCuervo(0, 20);    // Rango para cuervos

        int nacimientosVenados = GenerarNacimientosAleatorios(rng, distribucionNacimientosVenado);
        int nacimientosLobos = GenerarNacimientosAleatorios(rng, distribucionNacimientosLoboPuma);
        int nacimientosPumas = GenerarNacimientosAleatorios(rng, distribucionNacimientosLoboPuma);
        int nacimientosCuervos = GenerarNacimientosAleatorios(rng, distribucionNacimientosCuervo);

        for (auto& [generacion, animales] : animalesPorGeneracion) {
            for (int j = 0; j < nacimientosVenados; j++) {
                animales.push_back(Animal(NombreAnimal("Venado", generacion), 50.0, 3));
            }

            for (int j = 0; j < nacimientosLobos; j++) {
                animales.push_back(Animal(NombreAnimal("Lobo", generacion), 50.0, 4));
            }

            for (int j = 0; j < nacimientosPumas; j++) {
                animales.push_back(Animal(NombreAnimal("Puma", generacion), 50.0, 5));
            }

            for (int j = 0; j < nacimientosCuervos; j++) {
                animales.push_back(Animal(NombreAnimal("Cuervo", generacion), 50.0, 2));
            }

            for (size_t j = 0; j < animales.size(); j++) {
                animales[j].energia -= 1;
                if (animales[j].energia > 100) {
                    animales[j].energia = 100; // Límite de energía en 100
                }
                animales[j].haComido = false;

                // Actualizamos las semanas sin cazar
                if (animales[j].energia == 100) {
                    animales[j].semanasSinCazar++;
                }

                if (animales[j].semanasSinCazar == 3) {
                    animales[j].semanasSinCazar = 0;
                    animales[j].energia = 0;
                }

                if (animales[j].semanasPasadas >= animales[j].semanasParaReproducir) {
                    int nuevaGeneracion = animales[j].nombre.generacion + 1;
                    string nuevoNombre = animales[j].nombre.tipo + to_string(nuevaGeneracion);
                    while (generaciones.count(nuevoNombre) > 0) {
                        nuevaGeneracion++;
                        nuevoNombre = animales[j].nombre.tipo + to_string(nuevaGeneracion);
                    }
                    generaciones.insert(nuevoNombre);
                    NombreAnimal nuevoNombreAnimal(animales[j].nombre.tipo, nuevaGeneracion);
                    Animal hijo(nuevoNombreAnimal, 50.0, animales[j].semanasParaReproducir);
                    animales.push_back(hijo);

                    if (animales[j].nombre.tipo == "Lobo") {
                        nacimientosLobos++;
                    }
                    else if (animales[j].nombre.tipo == "Puma") {
                        nacimientosPumas++;
                    }
                    else if (animales[j].nombre.tipo == "Cuervo") {
                        nacimientosCuervos++;
                    }

                    animales[j].semanasPasadas = 0;
                } else {
                    animales[j].semanasPasadas++;
                }
            }
        }

        for (auto& [generacion, animales] : animalesPorGeneracion) {
            for (size_t j = 0; j < animales.size(); j++) {
                if (!animales[j].haComido) {
                    for (size_t k = 0; k < animales.size(); k++) {
                        if (j != k && (animales[j].nombre.tipo == "Lobo" || animales[j].nombre.tipo == "Puma") && animales[k].nombre.tipo == "Venado") {
                            if (!animales[j].haComido && Probabilidad(30)) {
                                double probExito = 50.0;
                                double probEscape = 50.0;

                                if (animales[j].energia < 25) {
                                    // Menor energía, menor probabilidad de caza
                                    probExito = 10.0;
                                }
                                else if (animales[j].energia < 50) {
                                    probExito = 30.0;
                                }

                                if (Probabilidad(probExito)) {
                                    if (Probabilidad(50)) {
                                        // Venado escapa
                                        animales[k].energia -= 5;
                                    }
                                    else {
                                        // Venado cazado
                                        animales[j].energia += 10;
                                        animales[k].energia = 0;
                                        if (animales[j].energia > 100) {
                                            animales[j].energia = 100;
                                        }
                                        animales[j].haComido = true;
                                        animales[k].venadosCazados++;
                                        venadosMuertos++;
                                        animales[j].semanasSinCazar = 0;
                                    }
                                }
                                else if (Probabilidad(probEscape)) {
                                    animales[j].energia -= 5;
                                }
                            }
                            else if (Probabilidad(30)) {
                                if (animales[j].nombre.tipo == "Lobo") {
                                    // Conflicto con Puma
                                    if (animales[k].nombre.tipo == "Puma") {
                                        if (Probabilidad(30)) {
                                            animales[j].energia -= 10;
                                            animales[k].energia -= 10;
                                        }
                                    }
                                }
                                else if (animales[j].nombre.tipo == "Puma") {
                                    // Conflicto con Lobo
                                    if (animales[k].nombre.tipo == "Lobo") {
                                        if (Probabilidad(30)) {
                                            animales[j].energia -= 10;
                                            animales[k].energia -= 10;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        cout << "Venados muertos: " << venadosMuertos << endl;
        cout << "Nacimientos de Lobos: " << nacimientosLobos << endl;
        cout << "Nacimientos de Pumas: " << nacimientosPumas << endl;
        cout << "Nacimientos de Cuervos: " << nacimientosCuervos << endl;
    }

    // Resumen de la cantidad de animales que quedan en el ecosistema
    map<string, int> cantidadAnimales;
    for (auto& [generacion, animales] : animalesPorGeneracion) {
        for (size_t j = 0; j < animales.size(); j++) {
            cantidadAnimales[animales[j].nombre.tipo]++;
        }
    }

    cout << "\nResumen de la cantidad de animales restantes en el ecosistema:" << endl;
    for (const auto& [tipo, cantidad] : cantidadAnimales) {
        cout << tipo << ": " << cantidad << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    map<int, vector<Animal>> animalesPorGeneracion;
    set<string> generaciones;

    int poblacionVenados = 200;

    for (int i = 1; i <= poblacionVenados; i++) {
        animalesPorGeneracion[poblacionVenados].push_back(Animal(NombreAnimal("Venado", poblacionVenados), 50.0, 3));
    }

    for (int i = 1; i <= 26; i++) {
        animalesPorGeneracion[1].push_back(Animal(NombreAnimal("Lobo", 1), 50.0, 4));
        animalesPorGeneracion[1].push_back(Animal(NombreAnimal("Puma", 1), 50.0, 5));
    }

    for (int i = 1; i <= 8; i++) {
        animalesPorGeneracion[1].push_back(Animal(NombreAnimal("Cuervo", 1), 50.0, 2));
    }

    Simular(animalesPorGeneracion, generaciones, poblacionVenados);

    return 0;
}
