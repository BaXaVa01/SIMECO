#include <iostream>
#include <string>
#include <vector>
#include <locale.h>


using namespace std;

struct Animal {
    string name;
    double energy;
    string type;

    Animal(string _name, double _energy, string _type) : name(_name), energy(_energy), type(_type) {}
};

void Simulate(vector<Animal>& animals) {
    for (int i = 0; i < 10; i++) {
        cout << "Ciclo " << i + 1 << ":" << endl;

        for (size_t j = 0; j < animals.size(); j++) {
            animals[j].energy -= 1;
            cout << animals[j].name << " perdió 1 de energía." << endl;
        }

        for (size_t j = 0; j < animals.size(); j++) {
            for (size_t k = 0; k < animals.size(); k++) {
                if (j != k && animals[j].type == "Puma" && animals[k].type == "Venado") {
                    animals[j].energy += 10;
                    animals[k].energy = 0;
                    cout << animals[j].name << " comió a " << animals[k].name << " y ganó 10 de energía." << endl;
                }
                else if (j != k && animals[j].type == "Lobo" && animals[k].type == "Venado") {
                    animals[j].energy += 10;
                    animals[k].energy = 0;
                    cout << animals[j].name << " comió a " << animals[k].name << " y ganó 10 de energía." << endl;
                }
            }
        }
    }
}

int main() {
	setlocale(LC_ALL, "spanish");
	setlocale(LC_CTYPE, "es_ES.UTF-8");
    vector<Animal> animals;
    animals.push_back(Animal("Puma1", 50.0, "Puma"));
    animals.push_back(Animal("Venado1", 50.0, "Venado"));
    animals.push_back(Animal("Lobo1", 50.0, "Lobo"));
    animals.push_back(Animal("Cuervo1", 50.0, "Cuervo"));

    Simulate(animals);

    for (size_t i = 0; i < animals.size(); i++) {
        cout << animals[i].name << " tiene " << animals[i].energy << " de energía." << endl;
    }

    return 0;
}

