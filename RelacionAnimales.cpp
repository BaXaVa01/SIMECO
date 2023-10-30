#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

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

    Animal(NombreAnimal _nombre, double _energia, int _semanasParaReproducir) : nombre(_nombre), energia(_energia), semanasParaReproducir(_semanasParaReproducir), semanasPasadas(0) {}
};

bool Probabilidad(double prob) {
    return (rand() % 100) < prob;
}

void Simular(vector<Animal>& animales, set<string>& generaciones) {
    for (int i = 0; i < 13; i++) {
        cout << "Semana " << i + 1 << ":" << endl;

        for (size_t j = 0; j < animales.size(); j++) {
            animales[j].energia -= 1;
            cout << animales[j].nombre.tipo << animales[j].nombre.generacion << " perdió 1 de energía." << endl;

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
                cout << animales[j].nombre.tipo << animales[j].nombre.generacion << " se reprodujo y nació " << nuevoNombreAnimal.tipo << nuevoNombreAnimal.generacion << "." << endl;
                animales[j].semanasPasadas = 0;
            } else {
                animales[j].semanasPasadas++;
            }
        }

        for (size_t j = 0; j < animales.size(); j++) {
            for (size_t k = 0; k < animales.size(); k++) {
                if (j != k && animales[j].nombre.tipo == "Puma" && animales[k].nombre.tipo == "Venado" && Probabilidad(30)) {
                    animales[j].energia += 10;
                    animales[k].energia = 0;
                    cout << animales[j].nombre.tipo << animales[j].nombre.generacion << " comió a " << animales[k].nombre.tipo << animales[k].nombre.generacion << " y ganó 10 de energía." << endl;
                }
                else if (j != k && animales[j].nombre.tipo == "Lobo" && animales[k].nombre.tipo == "Venado" && Probabilidad(30)) {
                    animales[j].energia += 10;
                    animales[k].energia = 0;
                    cout << animales[j].nombre.tipo << animales[j].nombre.generacion << " comió a " << animales[k].nombre.tipo << animales[k].nombre.generacion << " y ganó 10 de energía." << endl;
                }
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    vector<Animal> animales;
    set<string> generaciones;
    NombreAnimal nombrePuma("Puma", 1);
    NombreAnimal nombreVenado("Venado", 1);
    NombreAnimal nombreLobo("Lobo", 1);
    NombreAnimal nombreCuervo("Cuervo", 1);
    animales.push_back(Animal(nombrePuma, 50.0, 5));
    animales.push_back(Animal(nombreVenado, 50.0, 3));
    animales.push_back(Animal(nombreLobo, 50.0, 4));
    animales.push_back(Animal(nombreCuervo, 50.0, 2));

    Simular(animales, generaciones);

    for (size_t i = 0; i < animales.size(); i++) {
        cout << animales[i].nombre.tipo << animales[i].nombre.generacion << " tiene " << animales[i].energia << " de energía." << endl;
    }

    return 0;   
}
