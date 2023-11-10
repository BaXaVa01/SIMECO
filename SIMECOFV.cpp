#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>

using namespace std;

enum class TipoDesastre {
    Incendio,
    Terremoto,
    Sequia,
    Huracan
};

class Especie {
public:
    string nombre;
    int poblacionInicial;
    int poblacion;

    Especie(string nombre, int poblacionInicial) : nombre(nombre), poblacionInicial(poblacionInicial), poblacion(poblacionInicial) {}
};

class Recursos {
public:
    int agua;
    int carrona;
    int carne;
    int vegetacion;

    Recursos(int agua, int carrona, int carne, int vegetacion) : agua(agua), carrona(carrona), carne(carne), vegetacion(vegetacion) {}
};

class Ecosistema {
public:
    vector<Especie> especies;
    Recursos recursosIniciales;
    Recursos recursosActuales;

    Ecosistema(const vector<Especie>& especies, const Recursos& recursos)
        : especies(especies), recursosIniciales(recursos), recursosActuales(recursos) {}
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarEstadoInicialEcosistema(const Ecosistema& ecosistema) {
    clearScreen();
    cout << "Estado inicial del ecosistema:\n" << endl;
    cout << "Recursos iniciales:\n";
    cout << "- Agua: " << ecosistema.recursosIniciales.agua << endl;
    cout << "- Carrona: " << ecosistema.recursosIniciales.carrona << endl;
    cout << "- Carne: " << ecosistema.recursosIniciales.carne << endl;
    cout << "- Vegetacion: " << ecosistema.recursosIniciales.vegetacion << endl;

    cout << "\nEspecies registradas:\n";
    for (const auto& especie : ecosistema.especies) {
        cout << "- Especie: " << especie.nombre << ", Poblacion inicial: " << especie.poblacionInicial << endl;
    }

    cout << endl;
    cout << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

void registrarEspecies(vector<Especie>& especies) {
    clearScreen();
    int numEspecies;
    cout << "Ingrese el numero de especies en el ecosistema: ";
    cin >> numEspecies;

    for (int i = 0; i < numEspecies; ++i) {
        clearScreen();
        string nombre;
        int poblacionInicial;

        cout << "Ingrese el nombre de la especie " << (i + 1) << ": ";
        cin >> nombre;

        cout << "Ingrese la poblacion inicial de la especie " << nombre << ": ";
        cin >> poblacionInicial;

        especies.emplace_back(nombre, poblacionInicial);
    }

    clearScreen();
    cout << "Especies registradas correctamente.\n" << endl;
    cout << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

void registrarRecursos(Recursos& recursos) {
    clearScreen();
    cout << "Ingrese la cantidad de agua en el ecosistema: ";
    cin >> recursos.agua;

    cout << "Ingrese la cantidad de carrona en el ecosistema: ";
    cin >> recursos.carrona;

    cout << "Ingrese la cantidad de carne en el ecosistema: ";
    cin >> recursos.carne;

    cout << "Ingrese la cantidad de vegetacion en el ecosistema: ";
    cin >> recursos.vegetacion;

    clearScreen();
    cout << "Recursos registrados correctamente.\n" << endl;
    cout << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

void mostrarEstadoEcosistema(const Ecosistema& ecosistema) {
    clearScreen();
    cout << "Estado actual del ecosistema:\n" << endl;
    cout << "Recursos:\n";
    cout << "- Agua: " << ecosistema.recursosActuales.agua << endl;
    cout << "- Carrona: " << ecosistema.recursosActuales.carrona << endl;
    cout << "- Carne: " << ecosistema.recursosActuales.carne << endl;
    cout << "- Vegetacion: " << ecosistema.recursosActuales.vegetacion << endl;

    cout << "\nEspecies:\n";
    for (const auto& especie : ecosistema.especies) {
        cout << "- Especie: " << especie.nombre << ", Poblacion: " << especie.poblacion << endl;
    }

    cout << endl;
    cout << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

void generarDesastre(Ecosistema& ecosistema, TipoDesastre tipoDesastre) {
    clearScreen();
    cout << "Generando desastre...\n" << endl;
    cout << "Tipo de desastre: ";
    switch (tipoDesastre) {
        case TipoDesastre::Incendio:
            cout << "Incendio" << endl;
            break;
        case TipoDesastre::Terremoto:
            cout << "Terremoto" << endl;
            break;
        case TipoDesastre::Sequia:
            cout << "Sequia" << endl;
            break;
        case TipoDesastre::Huracan:
            cout << "Huracan" << endl;
            break;
        default:
            break;
    }

    // Reducir la poblacion de cada especie al azar
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.1, 0.9);

    for (auto& especie : ecosistema.especies) {
        int poblacionReduccion = especie.poblacion * dis(gen);
        especie.poblacion -= poblacionReduccion;
    }

    // Reducir los recursos disponibles al azar
    ecosistema.recursosActuales.agua *= dis(gen);
    ecosistema.recursosActuales.carrona *= dis(gen);
    ecosistema.recursosActuales.carne *= dis(gen);
    ecosistema.recursosActuales.vegetacion *= dis(gen);

    cout << "\nDesastre generado correctamente.\n" << endl;
    cout << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    vector<Especie> especies;
    Recursos recursos(100, 200, 300, 400);
    Ecosistema ecosistema(especies, recursos);

    int opcion;

    do {
        clearScreen();
        cout << "Menu:\n" << endl;
        cout << "1. Ver estado inicial del ecosistema" << endl;
        cout << "2. Ver estado actual del ecosistema" << endl;
        cout << "3. Registrar especies" << endl;
        cout << "4. Registrar recursos" << endl;
        cout << "5. Generar desastre" << endl;
        cout << "6. Salir" << endl;
        cout << "\nIngrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarEstadoInicialEcosistema(ecosistema);
                break;
            case 2:
                mostrarEstadoEcosistema(ecosistema);
                break;
            case 3:
                registrarEspecies(ecosistema.especies);
                break;
            case 4:
                registrarRecursos(ecosistema.recursosIniciales);
                ecosistema.recursosActuales = ecosistema.recursosIniciales;
                break;
            case 5:
                int tipoDesastre;
                clearScreen();
                cout << "Generar desastre:\n" << endl;
                cout << "Tipos de desastre:" << endl;
                cout << "1. Incendio" << endl;
                cout << "2. Terremoto" << endl;
                cout << "3. Sequia" << endl;
                cout << "4. Huracan" << endl;
                cout << "\nIngrese el numero correspondiente al tipo de desastre: ";
                cin >> tipoDesastre;

                switch (tipoDesastre) {
                    case 1:
                        generarDesastre(ecosistema, TipoDesastre::Incendio);
                        break;
                    case 2:
                        generarDesastre(ecosistema, TipoDesastre::Terremoto);
                        break;
                    case 3:
                        generarDesastre(ecosistema, TipoDesastre::Sequia);
                        break;
                    case 4:
                        generarDesastre(ecosistema, TipoDesastre::Huracan);
                        break;
                    default:
                        break;
                }
                break;
            case 6:
                clearScreen();
                cout << "Saliendo del programa...\n" << endl;
                break;
            default:
                clearScreen();
                cout << "Opcion invalida. Por favor, ingrese una opcion valida.\n" << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}
