#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>

using namespace std;

enum class TipoDesastre
{
    Incendio,
    Inundacion,
    Sequia,
    Huracan
};

class Especie
{
public:
    string nombre;
    int poblacionInicial;
    int poblacion;

    Especie(string nombre, int poblacionInicial) : nombre(nombre), poblacionInicial(poblacionInicial), poblacion(poblacionInicial) {}
};

class Recursos
{
public:
    int agua;
    int carrona;
    int carne;
    int vegetacion;

    Recursos(int agua, int carrona, int carne, int vegetacion) : agua(agua), carrona(carrona), carne(carne), vegetacion(vegetacion) {}
};

class Ecosistema
{
public:
    vector<Especie> especies;
    Recursos recursosIniciales;
    Recursos recursosActuales;

    Ecosistema(const vector<Especie> &especies, const Recursos &recursos)
        : especies(especies), recursosIniciales(recursos), recursosActuales(recursos) {}
};

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void mostrarEstadoInicialEcosistema(const Ecosistema &ecosistema)
{
    clearScreen();
    cout << "Estado inicial del ecosistema:\n"
         << endl;
    cout << "Recursos iniciales:\n";
    cout << "- Agua: " << ecosistema.recursosIniciales.agua << endl;
    cout << "- Carrona: " << ecosistema.recursosIniciales.carrona << endl;
    cout << "- Carne: " << ecosistema.recursosIniciales.carne << endl;
    cout << "- Vegetacion: " << ecosistema.recursosIniciales.vegetacion << endl;

    cout << "\nEspecies registradas:\n";
    for (const auto &especie : ecosistema.especies)
    {
        cout << "- Especie: " << especie.nombre << ", Poblacion inicial: " << especie.poblacionInicial << endl;
    }

    cout << endl;
    cout << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

void iniciarVirtualizacion(vector<Especie> &especies, Ecosistema &recursos)
{
    clearScreen();
    cout << "Iniciando virtualizacion...\n"
         << endl;
}

void registrarRecursos(Recursos &recursos)
{
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
    cout << "Recursos registrados correctamente.\n"
         << endl;
    cout << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

void mostrarEstadoEcosistema(const Ecosistema &ecosistema)
{
    clearScreen();
    cout << "Estado actual del ecosistema:\n"
         << endl;
    cout << "Recursos:\n";
    cout << "- Agua: " << ecosistema.recursosActuales.agua << endl;
    cout << "- Carrona: " << ecosistema.recursosActuales.carrona << endl;
    cout << "- Carne: " << ecosistema.recursosActuales.carne << endl;
    cout << "- Vegetacion: " << ecosistema.recursosActuales.vegetacion << endl;

    cout << "\nEspecies:\n";
    for (const auto &especie : ecosistema.especies)
    {
        cout << "- Especie: " << especie.nombre << ", Poblacion: " << especie.poblacion << endl;
    }

    cout << endl;
    cout << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

void generarDesastre(Ecosistema &ecosistema, TipoDesastre tipoDesastre)
{
    clearScreen();
    cout << "Generando desastre...\n"
         << endl;
    cout << "Tipo de desastre: ";
    switch (tipoDesastre)
    {
    case TipoDesastre::Incendio:
        cout << "Incendio" << endl;
        ecosistema.recursosActuales.vegetacion *= 0.1; // Gran reducción
        ecosistema.recursosActuales.carne *= 0.7;      // Reducción moderada
        ecosistema.recursosActuales.agua *= 0.9;       // Reducción leve
        break;
    case TipoDesastre::Inundacion:
        cout << "Inundacion" << endl;
        ecosistema.recursosActuales.agua *= 1.6;       // Reducción moderada
        ecosistema.recursosActuales.carne *= 0.8;      // Reducción leve
        ecosistema.recursosActuales.vegetacion *= 1.4; // Reducción leve
        break;
    case TipoDesastre::Sequia:
        cout << "Sequia" << endl;
        ecosistema.recursosActuales.agua *= 0.3;       // Gran reducción
        ecosistema.recursosActuales.vegetacion *= 0.5; // Reducción moderada
        break;
    case TipoDesastre::Huracan:
        cout << "Huracan" << endl;
        ecosistema.recursosActuales.agua *= 0.6;       // Reducción significativa
        ecosistema.recursosActuales.vegetacion *= 0.4; // Reducción significativa
        ecosistema.recursosActuales.carne *= 0.5;      // Reducción significativa
        break;
    default:
        break;
    }

    // Reducir la población de cada especie
    // (Puedes ajustar estos valores según el tipo de desastre también)
    for (auto &especie : ecosistema.especies)
    {
        int reduccion = 0;
        switch (tipoDesastre)
        {
        case TipoDesastre::Incendio:
            reduccion = especie.poblacion * 0.2; // Reducción del 20%
            break;
        case TipoDesastre::Inundacion:
            reduccion = especie.poblacion * 0.1; // Reducción del 10%
            break;
        case TipoDesastre::Sequia:
            reduccion = especie.poblacion * 0.3; // Reducción del 30%
            break;
        case TipoDesastre::Huracan:
            reduccion = especie.poblacion * 0.4; // Reducción del 40%
            break;
        default:
            break;
        }
        especie.poblacion -= reduccion;
    }

    cout << "\nDesastre generado correctamente.\n"
         << endl;
    cout << "Presione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}
// int Fvmain(int& ciclo, directorios& path)
int Fvmain(string &usuario, directorios &directorio)
{
    vector<Especie> especies;

    Recursos recursos(100, 200, 300, 400);
    Ecosistema ecosistema(especies, recursos);
    bool Guardado=false;
    int opcion;

    do
    {
        clearScreen();
        cout << "Menu:\n"
             << endl;
        cout << "1. Ver estado inicial del ecosistema" << endl;
        cout << "2. Ver estado actual del ecosistema" << endl;
        cout << "3. Iniciar ciclos" << endl;
        cout << "4. Generar desastre" << endl;
        cout << "5. Gestor de Datos de partida" << endl;
        cout << "6. Salir" << endl;
        cout << "\nIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            mostrarEstadoInicialEcosistema(ecosistema);
            break;
        case 2:
            mostrarEstadoEcosistema(ecosistema);
            break;
        case 3:
            iniciarVirtualizacion(ecosistema.especies, ecosistema);
            break;
        // case 0:
        //     registrarRecursos(ecosistema.recursosIniciales);
        //     ecosistema.recursosActuales = ecosistema.recursosIniciales;
        //     break;
        case 4:
            int tipoDesastre;
            clearScreen();

            // if(ciclo == 0){
            //     cout << "Usted se encuentra en el ciclo <<0>>, se le recomienda no generar ningun desastrer\n" << endl;
            //     cin.get();
            //     clearScreen();
            // }

            cout << "El ciclo en el que se encuentra es:" << endl;
            cout << "Generar desastre:\n"
                 << endl;
            cout << "Tipos de desastre:" << endl;
            cout << "1. Incendio" << endl;
            cout << "2. Inundacion" << endl;
            cout << "3. Sequia" << endl;
            cout << "4. Huracan" << endl;
            cout << "\nIngrese el numero correspondiente al tipo de desastre: ";
            cin >> tipoDesastre;

            switch (tipoDesastre)
            {
            case 1:
                generarDesastre(ecosistema, TipoDesastre::Incendio);
                break;
            case 2:
                generarDesastre(ecosistema, TipoDesastre::Inundacion);
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
        case 5:
    	{
            cout<<"1. Generar Excel"<<endl;
            cout<<"2. Guardar Partida"<<endl;
            cin>>opcionS;
            esNumero(opcionS);
            opcion=stoi(opcionS);
            switch (opcion)
            {
            case 1:
            {
                if (Guardado)
                {
                    ExcelGenerador(usuario,directorio);
                }
                else{
                    cout<<"Debes guardar la partida antes de mostrar los datos";
                }
                
                break;
            }
            case 2:
            {
                GuardarAnimales(ciclonum,vector1,vector2,vector3,vector4);
                GuardarRecursos(recursos);
                GuardarDesastres(listadesastres);
                barraCarga(5);
                Guardado=true;
            }
            default:
                break;
            }
        }
        case 6:
        {
            clearScreen();
            cout << "Saliendo del programa...\n"
                 << endl;
            system("pause");
            break;
        }
        default:
            clearScreen();
            cout << "Opcion invalida. Por favor, ingrese una opcion valida.\n"
                 << endl;
            break;
        }
    } while (opcion != 6);

    return 0;
}