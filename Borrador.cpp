#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <map>
#include <random>

using namespace std;

struct Animal {
    string tipo;
    double energia;
    int semanasParaReproducir;
    int semanasPasadas;
    bool haComido;
    int venadosCazados;
    int edad;
    bool estaVivo;
    int semanasSinCazar;

    Animal(string _tipo, double _energia, int _semanasParaReproducir)
        : tipo(_tipo), energia(_energia), semanasParaReproducir(_semanasParaReproducir),
          semanasPasadas(0), haComido(false), venadosCazados(0), edad(0), estaVivo(true) {}
};

bool Probabilidad(double prob) {
    return (rand() % 100) < prob;
}

int GenerarNacimientosAleatorios(mt19937& rng, uniform_int_distribution<int>& distribucion) {
    return distribucion(rng);
}

void Simular(map<string, vector<Animal>>& animalesPorTipo, int& poblacionVenados, int& poblacionLobos, int& poblacionPumas, int& poblacionCuervos) {
    for (int i = 0; i < 13; i++) {
        cout << "Semana " << i + 1 << " - Resumen:" << endl;

        int venadosMuertos = 0;

        mt19937 rng(static_cast<unsigned>(time(0)));
        uniform_int_distribution<int> distribucionNacimientosVenado(0, 60);
        uniform_int_distribution<int> distribucionNacimientosLoboPuma(0, 10);
        uniform_int_distribution<int> distribucionNacimientosCuervo(0, 20);

        int nacimientosVenados = GenerarNacimientosAleatorios(rng, distribucionNacimientosVenado);
        poblacionVenados += nacimientosVenados;

        int nacimientosLobos = GenerarNacimientosAleatorios(rng, distribucionNacimientosLoboPuma);
        poblacionLobos += nacimientosLobos;

        int nacimientosPumas = GenerarNacimientosAleatorios(rng, distribucionNacimientosLoboPuma);
        poblacionPumas += nacimientosPumas;

        int nacimientosCuervos = GenerarNacimientosAleatorios(rng, distribucionNacimientosCuervo);
        poblacionCuervos += nacimientosCuervos;
        

        for (auto& [tipo, animales] : animalesPorTipo) {
            double totalEnergia = 0.0;
            int contador = 0;

            for (Animal& animal : animales) {
                if (animal.estaVivo) {
                    totalEnergia += animal.energia;
                    contador++;
                }
            }

            double promedio = (contador > 0) ? (totalEnergia / contador) : 0.0;
            cout << "Promedio de energía de " << tipo << "s: " << promedio << endl;
        }

        for (auto& [tipo, animales] : animalesPorTipo) {
            for (size_t j = 0; j < animales.size(); j++) {
                if (animales[j].estaVivo) {
                    if (!animales[j].haComido && (animales[j].tipo == "Lobo" || animales[j].tipo == "Puma")) {
                        for (size_t k = 0; k < animalesPorTipo["Venado"].size(); k++) {
                            if (animalesPorTipo["Venado"][k].estaVivo) {
                                if (!animales[j].haComido && Probabilidad(30)) {
                                    double probExito = 50.0;
                                    double probHerido = 20.0;
                                    double probCazado = 50.0;

                                    if (animales[j].energia < 25) {
                                        probExito = 10.0;
                                    } else if (animales[j].energia < 50) {
                                        probExito = 30.0;
                                    }

                                    if (Probabilidad(probExito)) {
                                        if (Probabilidad(probHerido)) {
                                            animalesPorTipo["Venado"][k].energia -= 10;
                                            animales[j].energia -= 10;
                                        } else if (Probabilidad(probCazado)) {
                                            animales[j].energia = 0;
                                            animales[j].haComido = true;
                                            animalesPorTipo["Venado"][k].venadosCazados++;
                                            venadosMuertos++;
                                            animalesPorTipo["Venado"][k].estaVivo = false;
                                            animales[j].semanasSinCazar = 0;
                                        } else {
                                            animalesPorTipo["Venado"][k].energia -= 5;
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
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    map<string, vector<Animal>> animalesPorTipo;
    int poblacionVenados = 200;
    int poblacionLobos = 26;
    int poblacionPumas = 26;
    int poblacionCuervos = 12;

    for (int i = 1; i <= poblacionVenados; i++) {
        animalesPorTipo["Venado"].push_back(Animal("Venado", 50.0, 3));
    }

    for (int i = 1; i <= poblacionLobos; i++) {
        animalesPorTipo["Lobo"].push_back(Animal("Lobo", 50.0, 4));
    }

    for (int i = 1; i <= poblacionPumas; i++) {
        animalesPorTipo["Puma"].push_back(Animal("Puma", 50.0, 5));
    }

    for (int i = 1; i <= poblacionCuervos; i++) {
        animalesPorTipo["Cuervo"].push_back(Animal("Cuervo", 50.0, 2));
    }

    Simular(animalesPorTipo, poblacionVenados, poblacionLobos, poblacionPumas, poblacionCuervos);

    return 0;
}
