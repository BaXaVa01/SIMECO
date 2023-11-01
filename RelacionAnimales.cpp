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
    int edad;
    bool estaVivo;
    int semanasSinCazar; 

    Animal(NombreAnimal _nombre, double _energia, int _semanasParaReproducir)
        : nombre(_nombre), energia(_energia), semanasParaReproducir(_semanasParaReproducir),
          semanasPasadas(0), haComido(false), venadosCazados(0), edad(0), estaVivo(true) {}
};

struct Recurso {
    string tipo;
    double energia;

    Recurso(string _tipo, double _energia) : tipo(_tipo), energia(_energia) {}
};

struct Carroña {
    string tipo;
    double energia;

    Carroña(string _tipo, double _energia) : tipo(_tipo), energia(_energia) {}
};

bool Probabilidad(double prob) {
    return (rand() % 100) < prob;
}

int GenerarNacimientosAleatorios(mt19937& rng, uniform_int_distribution<int>& distribucion) {
    return distribucion(rng);
}

void Simular(map<int, vector<Animal>>& animalesPorGeneracion, set<string>& generaciones, int& poblacionVenados, vector<Recurso>& recursos) {
    for (int i = 0; i < 13; i++) {
        cout << "Semana " << i + 1 << " - Resumen:" << endl;

        int venadosMuertos = 0;

        mt19937 rng(static_cast<unsigned>(time(0)));
        uniform_int_distribution<int> distribucionNacimientosVenado(0, 60);
        uniform_int_distribution<int> distribucionNacimientosLoboPuma(0, 10);
        uniform_int_distribution<int> distribucionNacimientosCuervo(0, 20);

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
                animales[j].edad++;
                if (animales[j].edad >= 40) {
                    animales[j].estaVivo = false;
                }

                if (animales[j].estaVivo) {
                    animales[j].energia -= 1;
                    if (animales[j].energia > 100) {
                        animales[j].energia = 100;
                    }
                    animales[j].haComido = false;

                    if (animales[j].energia == 100) {
                        animales[j].semanasPasadas++;
                    }

                    if (animales[j].semanasPasadas == 3) {
                        animales[j].semanasPasadas = 0;
                        animales[j].energia = 0;
                    }

                    if (animales[j].nombre.tipo == "Venado") {
                        for (auto& recurso : recursos) {
                            if (animales[j].energia < 100 && Probabilidad(20)) {
                                animales[j].energia += recurso.energia;
                                recurso.energia = 0;
                                animales[j].haComido = true;
                            }
                        }
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
        }

        for (auto& [generacion, animales] : animalesPorGeneracion) {
            for (size_t j = 0; j < animales.size(); j++) {
                if (animales[j].estaVivo) {
                    if (!animales[j].haComido && (animales[j].nombre.tipo == "Lobo" || animales[j].nombre.tipo == "Puma")) {
                        for (size_t k = 0; k < animales.size(); k++) {
                            if (j != k && animales[k].nombre.tipo == "Venado") {
                                if (animales[k].estaVivo) {
                                    if (!animales[j].haComido && Probabilidad(30)) {
                                        double probExito = 50.0;
                                        double probHerido = 20.0;
                                        double probCazado = 50.0;

                                        if (animales[j].energia < 25) {
                                            probExito = 10.0;
                                        }
                                        else if (animales[j].energia < 50) {
                                            probExito = 30.0;
                                        }

                                        if (Probabilidad(probExito)) {
                                            if (Probabilidad(probHerido)) {
                                                animales[k].energia -= 10;
                                                animales[j].energia -= 10;
                                            }
                                            else if (Probabilidad(probCazado)) {
                                                animales[j].energia = 0;
                                                animales[j].haComido = true;
                                                animales[k].venadosCazados++;
                                                venadosMuertos++;
                                                animales[k].estaVivo = false;
                                                animales[j].semanasSinCazar = 0;
                                            }
                                            else {
                                                animales[k].energia -= 5;
                                            }
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

        // Calcular el promedio de energía por tipo de animal
        map<string, double> promedioEnergiaPorTipo;
        map<string, int> contadorPorTipo;
        for (auto& [generacion, animales] : animalesPorGeneracion) {
            for (size_t j = 0; j < animales.size(); j++) {
                if (animales[j].estaVivo) {
                    promedioEnergiaPorTipo[animales[j].nombre.tipo] += animales[j].energia;
                    contadorPorTipo[animales[j].nombre.tipo]++;
                }
            }
        }

        cout << "Promedio de energia por tipo de animal:" << endl;
        for (const auto& [tipo, sumaEnergia] : promedioEnergiaPorTipo) {
            double promedio = sumaEnergia / contadorPorTipo[tipo];
            cout << tipo << ": " << promedio << endl;
        }

        // Calcular el promedio de energía de todos los animales vivos
        double promedioEnergiaTotal = 0;
        int contadorTotal = 0;
        for (auto& [generacion, animales] : animalesPorGeneracion) {
            for (size_t j = 0; j < animales.size(); j++) {
                if (animales[j].estaVivo) {
                    promedioEnergiaTotal += animales[j].energia;
                    contadorTotal++;
                }
            }
        }

        cout << "Promedio de energia de todos los animales vivos: " << promedioEnergiaTotal / contadorTotal << endl;
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

    vector<Recurso> recursos;
    recursos.push_back(Recurso("Recurso1", 20.0));
    recursos.push_back(Recurso("Recurso2", 20.0));
    recursos.push_back(Recurso("Recurso3", 20.0));

    Simular(animalesPorGeneracion, generaciones, poblacionVenados, recursos);

    return 0;
}
