#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <conio.h>
#include <locale.h>
#include <limits>
#include "Excel.cpp"
#include "barraDeCarga.cpp"
#include "RelacionAnimalRecursos.cpp"

//HAY QUE ELIMINAR EL clearScreen al momento de unir los modulos relacion Animal recursos


using namespace std;

struct Usuario
{
    char nombreUsuario[100];
    char contrasena[100];
};

// enum class TipoDesastre
// {
//     Incendio,
//     Inundacion,
//     Sequia,
//     Huracan
// };

// class Especie
// {
// public:
//     string nombre;
//     int poblacionInicial;
//     int poblacion;

//     Especie(string nombre, int poblacionInicial) : nombre(nombre), poblacionInicial(poblacionInicial), poblacion(poblacionInicial) {}
// };

// class Recursos
// {
// public:
//     int agua;
//     int carrona;
//     int carne;
//     int vegetacion;
//     int vegetacionConsumida; // Necesitas llevar un registro de la vegetación consumida

//     Recursos(int agua, int carrona, int carne, int vegetacion)
//         : agua(agua), carrona(carrona), carne(carne), vegetacion(vegetacion), vegetacionConsumida(0) {}

//     void actualizarRecursos(estaciones estacion)
//     {
//         // Tengo que poner un nivel maximo de vegetacion
//         const int nivelMaxVegetacion = 100000;
//         const int nivelMaxAgua = 10000;

//         // switch(estacion) {
//         //     case Primavera:

//         //     case Verano:

//         //     case Otonio:

//         //     case Invierno:
//         // }
//     }
// };

// class Ecosistema
// {
// public:
//     vector<Especie> especies;
//     Recursos recursosIniciales;
//     Recursos recursosActuales;

//     Ecosistema(const vector<Especie> &especies, const Recursos &recursos)
//         : especies(especies), recursosIniciales(recursos), recursosActuales(recursos) {}
// };

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
        ecosistema.recursosActuales.vegetacion *= 0.1; // Gran reduccion
        ecosistema.recursosActuales.carne *= 0.7;      // Reduccion moderada
        ecosistema.recursosActuales.agua *= 0.9;       // Reduccion leve
        break;
    case TipoDesastre::Inundacion:
        cout << "Inundacion" << endl;
        ecosistema.recursosActuales.agua *= 1.6;       // Reduccion moderada
        ecosistema.recursosActuales.carne *= 0.8;      // Reduccion leve
        ecosistema.recursosActuales.vegetacion *= 1.4; // Reduccion leve
        break;
    case TipoDesastre::Sequia:
        cout << "Sequia" << endl;
        ecosistema.recursosActuales.agua *= 0.3;       // Gran reduccion
        ecosistema.recursosActuales.vegetacion *= 0.5; // Reduccion moderada
        break;
    case TipoDesastre::Huracan:
        cout << "Huracan" << endl;
        ecosistema.recursosActuales.agua *= 0.6;       // Reduccion significativa
        ecosistema.recursosActuales.vegetacion *= 0.4; // Reduccion significativa
        ecosistema.recursosActuales.carne *= 0.5;      // Reduccion significativa
        break;
    default:
        break;
    }

    // Reducir la poblacion de cada especie
    // (Puedes ajustar estos valores segun el tipo de desastre tambien)
    for (auto &especie : ecosistema.especies)
    {
        int reduccion = 0;
        switch (tipoDesastre)
        {
        case TipoDesastre::Incendio:
            reduccion = especie.poblacion * 0.2; // Reduccion del 20%
            break;
        case TipoDesastre::Inundacion:
            reduccion = especie.poblacion * 0.1; // Reduccion del 10%
            break;
        case TipoDesastre::Sequia:
            reduccion = especie.poblacion * 0.3; // Reduccion del 30%
            break;
        case TipoDesastre::Huracan:
            reduccion = especie.poblacion * 0.4; // Reduccion del 40%
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

void reemplazarEspacios(char *str, char find, char replace)
{
    for (; *str != '\0'; ++str)
    {
        if (*str == find)
        {
            *str = replace;
        }
    }
}

void prepararCadenaParaGuardar(char *cadena)
{
    reemplazarEspacios(cadena, ' ', '-');
}

void restaurarCadenaLeida(char *cadena)
{
    reemplazarEspacios(cadena, '-', ' ');
}

void registrarUsuario(const char *archivo, const Usuario &usuario)
{
    FILE *archivoUsuarios = fopen(archivo, "a");
    if (archivoUsuarios != NULL)
    {
        char nombreUsuarioModificado[100];
        strcpy(nombreUsuarioModificado, usuario.nombreUsuario);
        prepararCadenaParaGuardar(nombreUsuarioModificado);

        char contrasenaModificada[100];
        strcpy(contrasenaModificada, usuario.contrasena);
        prepararCadenaParaGuardar(contrasenaModificada);

        fprintf(archivoUsuarios, "%s,%s\n", nombreUsuarioModificado, contrasenaModificada);
        fclose(archivoUsuarios);
        cout << "Usuario registrado con exito." << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
    }
}

bool verificarCredenciales(const char *archivo, const char *nombreUsuario, const char *contrasena)
{
    FILE *archivoUsuarios = fopen(archivo, "rb");
    char linea[256], usuario[100], pass[100];
    if (archivoUsuarios != NULL)
    {
        while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL)
        {
            sscanf(linea, "%[^,],%s", usuario, pass);
            restaurarCadenaLeida(usuario);
            restaurarCadenaLeida(pass);

            if (strcmp(usuario, nombreUsuario) == 0 && strcmp(pass, contrasena) == 0)
            {
                fclose(archivoUsuarios);
                return true;
            }
        }
        fclose(archivoUsuarios);
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
    }
    return false;
}

bool esNumero(const string &cadena)
{
    for (char c : cadena)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

bool nombreUsuarioExistente(const char *archivo, const char *nombreUsuario)
{
    FILE *archivoUsuarios = fopen(archivo, "rb");
    char linea[256], usuario[100], *token;
    if (archivoUsuarios != NULL)
    {
        while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL)
        {
            token = strtok(linea, ",");
            if (token != NULL)
            {
                strcpy(usuario, token);
                restaurarCadenaLeida(usuario);
                if (strcmp(usuario, nombreUsuario) == 0)
                {
                    fclose(archivoUsuarios);
                    return true;
                }
            }
        }
        fclose(archivoUsuarios);
    }
    return false;
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void aMinusculas(char *cadena)
{
    if (cadena)
    {
        while (*cadena)
        {
            *cadena = tolower(static_cast<unsigned char>(*cadena));
            ++cadena;
        }
    }
}

string opcionS;

// int Fvmain(int& ciclo, directorios& path)
int Fvmain(string &usuario, directorios &directorio)
{
    vector<Especie> especies;

    Recursos recursos(0, 0, 0, 0);
    Ecosistema ecosistema(especies, recursos);
    bool Guardado=false;
    int opcion, opcionMenuExcel;
    string opcionString;

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
            mainRelacionAnimalRecurso(recursos, usuario);
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
            cin>>opcionString;
            esNumero(opcionString);
            opcionMenuExcel=stoi(opcionString);
            switch (opcionMenuExcel)
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
                // GuardarAnimales(ciclonum,vector1,vector2,vector3,vector4);
                // GuardarRecursos(recursos);
                // GuardarDesastres(listadesastres);
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

void MenuLogin(string &usuario)
{
    const char *archivoUsuarios = "usuarios.bin";
    Usuario nuevoUsuario;
    string nombreUsuario, contrasena, UsuarioConGuiones;
    directorios directorio;
    int opcion;

    do
    {
        limpiarPantalla();
        cout << "Bienvenido al sistema de registro e inicio de sesion:" << endl;
        cout << "1. Crear cuenta" << endl;
        cout << "2. Iniciar sesion" << endl;
        cout << "3. Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> opcionS;

        cin.ignore();
        if (esNumero(opcionS))
        {
            opcion = stoi(opcionS);
            switch (opcion)
            {
            case 1:
            {
                limpiarPantalla();
                cout << "Crear una nueva cuenta:" << endl;
                cout << "Nombre de usuario: ";
                cin.getline(nuevoUsuario.nombreUsuario, 100);
                aMinusculas(nuevoUsuario.nombreUsuario);
                if (nombreUsuarioExistente(archivoUsuarios, nuevoUsuario.nombreUsuario))
                {
                    cout << "El nombre de usuario ya existe. Por favor, elija otro." << endl;
                    cin.get();
                    break;
                }

                cout << "Contrasenia: ";
                cin.getline(nuevoUsuario.contrasena, 100);
                registrarUsuario(archivoUsuarios, nuevoUsuario);
                UsuarioConGuiones = nuevoUsuario.nombreUsuario;
                prepararCadenaParaGuardar(&UsuarioConGuiones[0]);
                createFolder(UsuarioConGuiones);
                searchDir(UsuarioConGuiones, directorio);
                GuardardatosSIMECO(UsuarioConGuiones, directorio);
                break;
            }
            case 2:
            {
                limpiarPantalla();
                cout << "Iniciar sesion:" << endl;
                cout << "Nombre de usuario: ";
                getline(cin, nombreUsuario);
                cout << "Contrasenia: ";
                getline(cin, contrasena);

                // Convierte el nombre de usuario a su version con guiones para la busqueda
                UsuarioConGuiones = nombreUsuario;
                prepararCadenaParaGuardar(&UsuarioConGuiones[0]);

                if (verificarCredenciales(archivoUsuarios, nombreUsuario.c_str(), contrasena.c_str()))
                {
                    cout << "Inicio de sesion exitoso." << endl;
                    usuario = nombreUsuario;
                    // Llama a searchDir con la version del nombre de usuario con guiones
                    searchDir(UsuarioConGuiones, directorio);
                    Fvmain(UsuarioConGuiones, directorio);
                    opcion = 3;
                }
                else
                {
                    cout << "Inicio de sesion fallido. Verifique sus credenciales." << endl;
                }
                cout << "Presione Enter para continuar...";
                cin.get();
                break;
            }
            case 3:
                cout << "Saliendo del programa." << endl;
                opcion = 3;
                break;
            default:
                cout << "Opcion no valida. Intentelo de nuevo." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
        else
        {
            cout << "Error: Debe ser un valor numerico" << endl;
        }
    } while (opcion != 3);
}