#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
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
#include "pantallacarga3.cpp"
#include "pantallacarga1.cpp"
// COLORES
#define PINK "\033[35m"
#define RESET "\033[0m"
#define GREEN "\e[1;32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define GREY "\033[90m"
#define UNDERLINE "\033[4m"

using namespace std;

void printColoredText(const std::string &text, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    std::cout << text;
    SetConsoleTextAttribute(hConsole, 7); // Restablece el color a blanco predeterminado
}

void printBorderLine(int length, char borderChar, int color)
{
    printColoredText(std::string(length, borderChar), color);
}

Extractordatos extractor;
DatosSimulacion datosS;
struct Usuario
{
    char nombreUsuario[100];
    char contrasena[100];
};
string NombreBinA, NombreBinB, NombreBinC; // Nombres de los archivos binarios
int contadorFase;
streampos posicionactual;
void ExtraerDatos(DatosSimulacion &datos, Extractordatos extract);
void CargarRecursos(Extractordatos &extractor, const string &rutacompleta);

void mostrarEstadoInicialEcosistema(Ecosistema &ecosistema)
{
    system("cls"); // Limpia la pantalla en Windows

    // Coordenadas para posicionar el marco del título
    int x = 5;
    int y = 5;

    // Imprime un marco alrededor del título
    const std::string titulo = "Estado inicial del ecosistema";
    const int tituloLength = titulo.length() + 4; // Longitud del título + 4 espacios de margen
    gotoxy(x, y);
    printBorderLine(tituloLength, '*', 9); // Línea superior del marco

    gotoxy(x, y + 1);
    std::cout << "* " << titulo << " *"; // Título con margen

    gotoxy(x, y + 2);
    printBorderLine(tituloLength, '*', 9); // Línea inferior del marco
    std::cout << "\n";

    // Coordenadas para el contenido
    int contenidoX = x;
    int contenidoY = y + 3;

    // Establecer coordenadas para el contenido dentro del marco
    gotoxy(contenidoX, contenidoY);
    printBorderLine(tituloLength, '*', 14); // Borde de color amarillo oscuro para el contenido

    // Imprimir el contenido dentro del marco con gotoxy
    gotoxy(contenidoX + 2, contenidoY + 1);
    printBoldText("Recursos  en el ecosistema:\n");
    gotoxy(contenidoX + 2, contenidoY + 2);
    printBoldText("-> Agua: ");
    std::cout << ecosistema.recursosIniciales.agua << GREEN << " m3" << RESET << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 3);
    printBoldText("-> Carrona: ");
    std::cout << ecosistema.recursosIniciales.carrona << GREEN << " Kg" << RESET << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 4);
    printBoldText("-> Carne: ");
    std::cout << ecosistema.recursosIniciales.carne << GREEN << " Kg" << RESET << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 5);
    printBoldText("-> Vegetacion: ");
    std::cout << ecosistema.recursosIniciales.vegetacion << GREEN << " m2" << RESET << std::endl;

    // Imprimir borde inferior para el texto de las especies
    gotoxy(contenidoX, contenidoY + 6);
    printBorderLine(tituloLength, '*', 14); // Borde de color amarillo oscuro para el contenido de las especies

    gotoxy(contenidoX + 4, contenidoY + 7);
    printBoldText("Especies registradas:\n");
    gotoxy(contenidoX + 2, contenidoY + 8);
    printBoldText("- Poblacion Venados: ");
    std::cout << ecosistema.pVenados << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 9);
    printBoldText("- Poblacion Pumas: ");
    std::cout << ecosistema.pPumas << std::endl;

    gotoxy(contenidoX, contenidoY + 10);
    std::cout << "\nPresione cualquier tecla para continuar...";
    std::cin.ignore();
    std::cin.get();
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

void mostrarEstadoEcosistema(Ecosistema &ecosistema)
{

    clearScreen();

    // Coordenadas para posicionar el marco del título
    int x = 5;
    int y = 5;

    // Imprime un marco alrededor del título
    const std::string titulo = "Estado actual del ecosistema:";
    const int tituloLength = titulo.length() + 4; // Longitud del título + 4 espacios de margen
    gotoxy(x, y);

    printBorderLine(tituloLength, '*', 9); // Línea superior del marco

    gotoxy(x, y + 1);
    std::cout << "* " << titulo << " *"; // Título con margen

    gotoxy(x, y + 2);
    printBorderLine(tituloLength, '*', 9); // Línea inferior del marco
    std::cout << "\n";

    // Coordenadas para el contenido
    int contenidoX = x;
    int contenidoY = y + 3;

    // Establecer coordenadas para el contenido dentro del marco
    gotoxy(contenidoX, contenidoY);
    printBorderLine(tituloLength, '*', 14); // Borde de color amarillo oscuro para el contenido

    // Imprimir el contenido dentro del marco con gotoxy
    gotoxy(contenidoX + 2, contenidoY + 1);
    printBoldText("Recursos:\n");
    gotoxy(contenidoX + 2, contenidoY + 2);
    printBoldText("- Agua: ");
    std::cout << ecosistema.recursosActuales.agua << GREEN << " m3" << RESET << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 3);
    printBoldText("- Carrona: ");
    std::cout << ecosistema.recursosActuales.carrona << GREEN << " Kg" << RESET << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 4);
    printBoldText("- Carne: ");
    std::cout << ecosistema.recursosActuales.carne << GREEN << " Kg" << RESET << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 5);
    printBoldText("- Vegetacion: ");
    std::cout << ecosistema.recursosActuales.vegetacion << GREEN << " m2" << RESET << std::endl;

    // Imprimir borde inferior para el texto de las especies
    gotoxy(contenidoX, contenidoY + 6);
    printBorderLine(tituloLength, '*', 14); // Borde de color amarillo oscuro para el contenido de las especies

    // Imprimir texto adicional con borde amarillo oscuro
    gotoxy(contenidoX + 2, contenidoY + 7);
    printBoldText("Especies:\n");
    gotoxy(contenidoX + 2, contenidoY + 8);
    printBoldText("- Poblacion Venados: ");
    std::cout << ecosistema.pVenados << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 9);
    printBoldText("- Poblacion Pumas: ");
    std::cout << ecosistema.pPumas << std::endl;

    gotoxy(contenidoX, contenidoY + 10);
    std::cout << "\nPresione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}
void mostrarEstadoEcosistemaAnterior(Ecosistema &ecosistema)
{

    clearScreen();

    // Coordenadas para posicionar el marco del título
    int x = 5;
    int y = 5;

    // Imprime un marco alrededor del título
    const std::string titulo = "Estado anterior del ecosistema:";
    const int tituloLength = titulo.length() + 4; // Longitud del título + 4 espacios de margen
    gotoxy(x, y);

    printBorderLine(tituloLength, '*', 9); // Línea superior del marco

    gotoxy(x, y + 1);
    std::cout << "* " << titulo << " *"; // Título con margen

    gotoxy(x, y + 2);
    printBorderLine(tituloLength, '*', 9); // Línea inferior del marco
    std::cout << "\n";

    // Coordenadas para el contenido
    int contenidoX = x;
    int contenidoY = y + 3;

    // Establecer coordenadas para el contenido dentro del marco
    gotoxy(contenidoX, contenidoY);
    printBorderLine(tituloLength, '*', 14); // Borde de color amarillo oscuro para el contenido

    // Imprimir el contenido dentro del marco con gotoxy
    gotoxy(contenidoX + 2, contenidoY + 1);
    printBoldText("Recursos:\n");
    gotoxy(contenidoX + 2, contenidoY + 2);
    printBoldText("- Agua: ");
    std::cout << ecosistema.recursosActuales.agua << GREEN << " m3" << RESET << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 3);
    printBoldText("- Carrona: ");
    std::cout << ecosistema.recursosActuales.carrona << GREEN << " Kg" << RESET << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 4);
    printBoldText("- Carne: ");
    std::cout << ecosistema.recursosActuales.carne << GREEN << " Kg" << RESET << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 5);
    printBoldText("- Vegetacion: ");
    std::cout << ecosistema.recursosActuales.vegetacion << GREEN << " m2" << RESET << std::endl;

    // Imprimir borde inferior para el texto de las especies
    gotoxy(contenidoX, contenidoY + 6);
    printBorderLine(tituloLength, '*', 14); // Borde de color amarillo oscuro para el contenido de las especies

    // Imprimir texto adicional con borde amarillo oscuro
    gotoxy(contenidoX + 2, contenidoY + 7);
    printBoldText("Especies:\n");
    gotoxy(contenidoX + 2, contenidoY + 8);
    printBoldText("- Poblacion Venados: ");
    std::cout << ecosistema.pVenados << std::endl;
    gotoxy(contenidoX + 2, contenidoY + 9);
    printBoldText("- Poblacion Pumas: ");
    std::cout << ecosistema.pPumas << std::endl;

    gotoxy(contenidoX, contenidoY + 10);
    std::cout << "\nPresione cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

void generarDesastre(Ecosistema &ecosistema, TipoDesastre tipoDesastre)
{
    clearScreen();
    // Coordenadas para posicionar el cuadro y el texto
    int x = 5;
    int y = 5;

    // Imprimir cuadro azul
    gotoxy(x, y);
    printBorderLine(40, '*', 11); // Línea superior del cuadro

    gotoxy(x, y + 1);
    cout << "*       Tipo de desastre *"; // Texto con margen

    gotoxy(x, y + 2);
    printBorderLine(40, '*', 11); // Línea inferior del cuadro
    cout << endl;

    // Posicionar texto del tipo de desastre dentro del cuadro
    gotoxy(x + 2, y + 4);
    cout << BLUE << "Generando desastre..." << RESET << endl;
    gotoxy(x + 2, y + 5);
    cout << "Tipo de desastre: ";

    switch (tipoDesastre)
    {
    case TipoDesastre::Incendio:
        cout << RED << "Incendio" << RESET << endl;
        ecosistema.recursosActuales.vegetacion *= 0.1; // Gran reduccion
        ecosistema.recursosActuales.agua *= 0.9;       // Reduccion leve
        break;
    case TipoDesastre::Inundacion:
        cout << BLUE << "Inundacion" << RESET << endl;
        ecosistema.recursosActuales.agua *= 1.6;       // Aumento significativo
        ecosistema.recursosActuales.vegetacion *= 1.4; // Aumento significativo
        break;
    case TipoDesastre::Sequia:
        cout << YELLOW << "Sequia" << RESET << endl;
        ecosistema.recursosActuales.agua *= 0.3;       // Gran reduccion
        ecosistema.recursosActuales.vegetacion *= 0.5; // Reduccion moderada
        break;
    case TipoDesastre::Huracan:
        cout << GREY << "Huracan" << RESET << endl;
        ecosistema.recursosActuales.agua *= 0.6;       // Reduccion significativa
        ecosistema.recursosActuales.vegetacion *= 0.4; // Reduccion significativa
        break;
    default:
        break;
    }
    // Por el momento los desastres solo afectan a los recursos
    gotoxy(x + 3, y + 7);

    cout << GREEN << "\nDesastre generado correctamente." << RESET << endl;
    cout << "Presione cualquier tecla para continuar...";
    std::cin.ignore();
    std::cin.get();
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
    // Estos vectores son necesarios siempre para el inicio de la partida
    vector<Venado> venados; // 10 machos y 10 hembras
    vector<Puma> pumas;     // 1 macho y 1 hembra

    int cantidadVenadosHembra, cantidadPumasMacho, cantidadVenadosMacho, cantidadPumasHembra;
    // Esta funcion es solo si el usuario no tiene partida guardada
    cout << "Bienvenido a SIMECO" << endl;

    clearScreen();

    cout << BLUE << "Desea entrar en el modo avanzado?" << RESET << endl;
    cout << GREEN << "1. Si" << RESET << endl;
    cout << RED << "2. No" << RESET << endl;
    int opl;
    cin >> opl;
    if (opl == 1)
    {
        cout << "A continuacion, se le pedira que ingrese los datos iniciales del ecosistema." << endl;
        cout << "Ingrese los venados" << PINK << " hembra" << RESET << " que desea:";
        cin >> cantidadVenadosHembra;
        cout << "Ingrese los venados" << BLUE << " macho" << RESET << " que desea:";
        cin >> cantidadVenadosMacho;
        cout << "Ingrese los pumas" << PINK << " hembra" << RESET << " que desea:";
        cin >> cantidadPumasHembra;
        cout << "Ingrese los pumas" << BLUE << " macho que desea:" << RESET;
        cin >> cantidadPumasMacho;

        iniciarEspecies(venados, pumas, cantidadVenadosHembra, cantidadVenadosMacho, cantidadPumasHembra, cantidadPumasMacho);
    }
    else
    {
        cout << "Entrara con los datos iniciales por defecto" << endl;
        iniciarEspecies(venados, pumas, 50, 50, 1, 1);
    }

    limpiarPantalla();

    int carneInicialEcosistema;
    int tipoDesastre;
    for (const auto &venado : venados)
    {
        carneInicialEcosistema += venado.peso;
    }
    Recursos recursosInicialesEcosistema(100000, 1000, carneInicialEcosistema, 100000); // 100000 m3 de agua, 1000 kg de carrona, 100000 m2 de vegetacion

    Ecosistema datosEcosistema(int(venados.size()), int(pumas.size()), recursosInicialesEcosistema);

    bool Guardado = false;
    bool Excel = true;
    bool Estacion = false;
    int opcion, opcionMenuPartida, OpcionMenuExcel;
    Ecosistema datosInicial(datosEcosistema);
    Ecosistema datosEcosistemaAnt(datosEcosistema);
    int edadpromedio;
    int contador;
    estaciones estacion;
    int ciclosSimular, cicloGlobal;
    do
    {
        clearScreen();
        int x = 5;
        int y = 5;

        // Imprimir cuadro azul
        gotoxy(x, y);
        printBorderLine(40, '*', 11); // Línea superior del cuadro

        gotoxy(x, y + 1);
        cout << "              *Menu*"; // Texto con margen

        gotoxy(x, y + 2);
        printBorderLine(40, '*', 11); // Línea inferior del cuadro
        cout << endl;

        // Imprimir opciones del menú
        gotoxy(x + 2, y + 4);
        cout << "1. Ver estado" << RED << " inicial"
             << " del ecosistema" << RESET << endl;
        gotoxy(x + 2, y + 5);
        cout << "2. Ver estado" << YELLOW << " anterior"
             << " del ecosistema" << RESET << endl;
        gotoxy(x + 2, y + 6);
        cout << "3. Ver estado" << GREEN << " actual"
             << " del ecosistema" << RESET << endl;
        gotoxy(x + 2, y + 7);
        cout << GREY << "4. Iniciar ciclos" << RESET << endl;
        gotoxy(x + 2, y + 8);
        cout << "5. Generar desastre" << endl;
        gotoxy(x + 2, y + 9);
        cout << "6. Gestor de Datos de partida" << endl;
        gotoxy(x + 2, y + 10);
        cout << BLUE << "7. Abrir pagina Web SIMECO" << RESET << endl;
        gotoxy(x + 2, y + 11);
        cout << RED << "8. Salir" << RESET << endl;

        gotoxy(x + 2, y + 12);
        cout << "Ingrese una opcion: ";
        std::cin >> opcionS;

        if (esNumero(opcionS))
        {
            opcion = stoi(opcionS);
            switch (opcion)
            {
            case 1:
            {
                mostrarEstadoInicialEcosistema(datosInicial);
                break;
            }

            case 2:
            {
                mostrarEstadoEcosistemaAnterior(datosEcosistemaAnt);
                break;
            }

            case 3:
            {
                datosEcosistema.pPumas = pumas.size();
                datosEcosistema.pVenados = venados.size();
                actualizarCarne(venados, datosEcosistema.recursosActuales);
                mostrarEstadoEcosistema(datosEcosistema);
                break;
            }
            case 4:
            {
                datosEcosistemaAnt = datosEcosistema;
                extractor.AnteVenados = venados.size();
                extractor.AntePumas = pumas.size();
                extractor.aguaA = datosEcosistemaAnt.recursosActuales.agua;
                extractor.carneA = datosEcosistemaAnt.recursosActuales.carne;
                extractor.vegetacionA = datosEcosistemaAnt.recursosActuales.vegetacion;
                extractor.carronaA = datosEcosistemaAnt.recursosActuales.carrona;
                if (Estacion)
                {
                    extractor.EstacionA = estacion;
                }
                limpiarPantalla();
                cout << "Ingrese la cantidad de ciclos que desea simular: ";
                cin >> ciclosSimular;
                mainRelacionAnimalRecurso(usuario, venados, pumas, datosEcosistema, extractor, estacion, ciclosSimular, cicloGlobal);
                cicloGlobal += ciclosSimular;
                extractor.aguaAct = datosEcosistema.recursosActuales.agua;
                contador = 0;
                for (auto &venado : venados)
                {
                    edadpromedio += venado.mostrarEdad();
                    contador++;
                }
                extractor.EdadV = edadpromedio / contador;
                contador = 0;
                edadpromedio = 0;
                for (auto &puma : pumas)
                {
                    edadpromedio += puma.mostrarEdad();
                    contador++;
                }
                extractor.EdadP = edadpromedio / contador;
                extractor.carneAct = datosEcosistema.recursosActuales.carne;
                extractor.vegetacionAct = datosEcosistema.recursosActuales.vegetacion;
                extractor.carronaAct = datosEcosistema.recursosActuales.carrona;
                extractor.PV = venados.size();
                extractor.PP = pumas.size();
                extractor.estacionAct = estacion;
                Estacion = true;
                cin.get();
                break;
            }

            case 5:
            {
                clearScreen();

                cout << "Generar desastre:\n"
                     << endl;
                cout << GREY << "Tipos de desastre:" << RESET << endl;
                cout << RED << "1. Incendio" << RESET << endl;
                cout << BLUE << "2. Inundacion" << RESET << endl;
                cout << YELLOW << "3. Sequia" << RESET << endl;
                cout << GREEN << "4. Huracan" << RESET << endl;
                cout << GREY << "\nIngrese el numero correspondiente al tipo de desastre: " << RESET;
                cin >> tipoDesastre;

                switch (tipoDesastre)
                {
                case 1:
                    generarDesastre(datosEcosistema, TipoDesastre::Incendio);
                    extractor.cantInc++;
                    extractor.cicloInc=cicloGlobal;
                    break;
                case 2:
                    generarDesastre(datosEcosistema, TipoDesastre::Inundacion);
                    extractor.cantInd++;
                    extractor.cicloInd=cicloGlobal;
                    break;
                case 3:
                    generarDesastre(datosEcosistema, TipoDesastre::Sequia);
                    extractor.cantSeq++;
                    extractor.cicloSeq=cicloGlobal;
                    break;
                case 4:
                    generarDesastre(datosEcosistema, TipoDesastre::Huracan);
                    extractor.cantHur++;
                    extractor.cicloHur=cicloGlobal;
                    break;
                default:
                    break;
                }
                break;
            }
            case 6:
            {
                clearScreen();
                // Coordenadas para posicionar el cuadro y el texto
                int x = 5;
                int y = 5;

                // Imprimir cuadro azul
                gotoxy(x, y);
                printBorderLine(40, '*', 11); // Línea superior del cuadro

                gotoxy(x, y + 1);
                cout << "         * Gestor de Partida *" << endl; // Texto con margen

                gotoxy(x, y + 2);
                printBorderLine(40, '*', 11); // Línea inferior del cuadro
                cout << endl;

                // Imprimir opciones del menú
                gotoxy(x + 2, y + 4);
                cout << BLUE << "1. Generar Excel" << RESET << endl;
                gotoxy(x + 2, y + 5);
                cout << GREEN << "2. Guardar Partida" << RESET << endl;
                gotoxy(x + 2, y + 6);
                cout << BLUE << "3. Cargar Partida" << RESET << endl;

                gotoxy(x + 2, y + 8);
                cout << "Ingrese una opcion: ";
                std::cin >> opcionS;
                esNumero(opcionS);
                opcionMenuPartida = stoi(opcionS);

                switch (opcionMenuPartida)
                {
                    NombreBinA = existeArchivo("ciclo", directorio.folder1, ".bin");
                    NombreBinA += "ciclo1.bin";
                case 1:
                {

                    if (Guardado)
                    {
                        clearScreen();
                        ExcelGenerador(usuario, directorio, Excel);
                    }
                    else
                    {
                        cout << "No tienes datos guardados \n";
                        system("pause");
                    }

                    break;
                }
                case 2:
                {
                    NombreBinA = existeArchivo("ciclo", directorio.folder1, ".bin");
                    NombreBinB = existeArchivo("ciclo", directorio.folder3, ".bin");
                    NombreBinC = existeArchivo("ciclo", directorio.folder2, ".bin");
                    bool ultimoDelGrupo;
                    recrearArchivoVacio(NombreBinA);

                    // Guardar datos de venados
                    ultimoDelGrupo = false;
                    size_t i = 1;
                    for (auto &venado : venados)
                    {
                        datos.edad = venado.mostrarEdad();
                        if (venado.determinarGenero() == Genero::Macho)
                        {
                            datos.genero = 0;
                        }
                        else
                        {
                            datos.genero = 1;
                        }
                        if (i == venados.size())
                        {
                            ultimoDelGrupo = true;
                        }

                        GuardarAnimal(datos, ultimoDelGrupo, NombreBinA);
                        i++;
                    }

                    // Guardar datos de pumas
                    i = 1;
                    ultimoDelGrupo = false;
                    for (auto &puma : pumas)
                    {
                        datos.edad = puma.mostrarEdad();
                        if (puma.determinarGenero() == Genero::Macho)
                        {
                            datos.genero = 0;
                        }
                        else
                        {
                            datos.genero = 1;
                        }
                        if (i == pumas.size())
                        {
                            ultimoDelGrupo = true;
                        }

                        GuardarAnimal(datos, ultimoDelGrupo, NombreBinA);
                        i++;
                    }
                    extractor.cnum=cicloGlobal;
                    ExtraerDatos(datosS, extractor);
                    recrearArchivoVacio(NombreBinB);
                    GuardarRecursos(extractor, NombreBinB);
                    recrearArchivoVacio(NombreBinC);
                    GuardarDesastres(extractor, NombreBinC);
                    GuardardatosSIMECO(usuario, directorio, datosS);
                    barraCarga(5);
                    Guardado = true;
                    break;
                }
                case 3:
                {
                    NombreBinA = existeArchivo("ciclo", directorio.folder1, ".bin");
                    NombreBinB = existeArchivo("ciclo", directorio.folder3, ".bin");
                    NombreBinC = existeArchivo("ciclo", directorio.folder2, ".bin");
                    venados.clear();
                    pumas.clear();
                    CargarRecursos(extractor, NombreBinB);
                    datosEcosistema.recursosActuales.agua = extractor.aguaAct;
                    datosEcosistema.recursosActuales.vegetacion = extractor.vegetacionAct;
                    datosEcosistema.recursosActuales.carne = extractor.carneAct;
                    datosEcosistema.recursosActuales.carrona = extractor.carronaAct;
                    LeerAnimal(NombreBinA, venados, pumas);

                    break;
                }
                default:
                    break;
                }
                break;
            }
            case 7:
            {
                system("start index.html");
                break;
            }
            default:
            {
                clearScreen();
                cout << "Opcion invalida. Por favor, ingrese una opcion valida.\n"
                     << endl;
                break;
            }
            }
        }
        else
        {
            cerr << "Error: Debe de ser un numero entero" << endl;
            cin.get();
        }
    } while (opcion != 8);

    return 0;
}

void MenuLogin(string &usuario)
{
    // mainBarra1();
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
                break;
            }
            case 2:
            {
                clearScreen();
                // Coordenadas para posicionar el cuadro y el texto
                int x = 5;
                int y = 5;

                // Imprimir cuadro azul
                gotoxy(x, y);
                printBorderLine(40, '*', 11); // Línea superior del cuadro

                gotoxy(x, y + 1);
                cout << "         * LOGIN *" << endl; // Texto con margen

                gotoxy(x, y + 2);
                printBorderLine(40, '*', 11); // Línea inferior del cuadro
                cout << endl;

                gotoxy(x + 2, y + 4);
                cout << BLUE << "Iniciar sesion:" << RESET << endl;
                gotoxy(x + 2, y + 5);
                cout << RED << "Nombre de usuario: " << RESET;
                gotoxy(x + 2, y + 6);
                getline(cin, nombreUsuario);
                gotoxy(x + 2, y + 7);
                cout << RED << "Contrasenia: " << RESET;
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
                    // mainBarra1();
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

void ExtraerDatos(DatosSimulacion &datos, Extractordatos extract)
{
    float result;
    datos.poblacionTotalEspecie1 = to_string(extract.PV);
    datos.poblacionTotalEspecie2 = to_string(extract.PP);
    datos.poblacionTotalEspecie3 = "0";
    datos.poblacionTotalEspecie4 = "0";

    datos.edadPromedioEspecie1 = to_string(extract.EdadV);

    datos.edadPromedioEspecie2 = to_string(extract.EdadP);
    datos.edadPromedioEspecie3 = "0";
    datos.edadPromedioEspecie4 = "0";
    result = 0;
    result = static_cast<float>((extract.PV - extract.AnteVenados + extract.contadorMuerteV) / extract.PV);
    datos.tasaNatalidadEspecie1 = to_string(result);
    result = 0;
    result = static_cast<float>((extract.PP - extract.AntePumas + extract.contadorMuerteP) / extract.PP);
    datos.tasaNatalidadEspecie2 = to_string(result);
    datos.tasaNatalidadEspecie3 = "0";
    datos.tasaNatalidadEspecie4 = "0";

    result = 0;
    result = static_cast<float>(extract.contadorMuerteV / extract.PV);
    datos.tasaMortalidadEspecie1 = to_string(result);
    result = 0;
    result = static_cast<float>(extract.contadorMuerteP / extract.PP);
    datos.tasaMortalidadEspecie2 = to_string(result);
    datos.tasaMortalidadEspecie3 = "0";
    datos.tasaMortalidadEspecie4 = "0";

    result = 0;
    result = static_cast<float>((extract.PV - extract.AnteVenados) / extract.AnteVenados);
    datos.crecimientoPoblacionEspecie1 = to_string(result);
    result = 0;
    result = static_cast<float>((extract.PP - extract.AntePumas) / extract.AntePumas);
    datos.crecimientoPoblacionEspecie2 = to_string(result);
    datos.crecimientoPoblacionEspecie3 = "0";
    datos.crecimientoPoblacionEspecie4 = "0";

    result = 0;
    result = static_cast<float>((extract.PV + extract.PP) / 2);
    datos.promedioIndividuos = to_string(result);
    result = 0;
    result = extract.PV + extract.PP;
    datos.poblacionTotal = to_string(result);
    datos.aguaDisponible = to_string(extract.aguaAct);
    datos.hierbaDisponible = to_string(extract.vegetacionAct);
    system("pause");

    datos.carneDisponible = to_string(extract.carneAct);
    datos.carronaDisponible = to_string(extract.carronaAct);
    int esta;
    string estacioncita;
    esta = extract.EstacionA;
    if (esta == 0)
    {
        estacioncita = "Primavera";
    }
    if (esta == 1)
    {
        estacioncita = "Verano";
    }
    if (esta == 2)
    {
        estacioncita = "Otonio";
    }
    if (esta == 3)
    {
        estacioncita = "Invierno";
    }

    datos.estacionInicial = estacioncita;

    esta = extract.estacionAct;
    if (esta == 0)
    {
        estacioncita = "Primavera";
    }
    if (esta == 1)
    {
        estacioncita = "Verano";
    }
    if (esta == 2)
    {
        estacioncita = "Otonio";
    }
    if (esta == 3)
    {
        estacioncita = "Invierno";
    }
    datos.estacionActual = estacioncita;

    datos.anoInicio = "2006";
    int ano = 2006 + (extract.cnum / 4);
    datos.anoActual = to_string(ano);
    datos.desastresOcurridos = to_string(extract.cantHur + extract.cantInc + extract.cantInd + extract.cantSeq);
    datos.desastresIniciadosUsuario = datos.desastresOcurridos;

    datos.incendios = to_string(extract.cantInc);
    datos.sequias = to_string(extract.cantSeq);
    datos.inundaciones = to_string(extract.cantInd);
    datos.huracanes = to_string(extract.cantHur);
    datos.anoInc=to_string(extract.cicloInc);
    datos.anoSeq=to_string(extract.cicloSeq);
    datos.anoInd=to_string(extract.cicloInd);
    datos.anoHur=to_string(extract.cicloHur);
}

void CargarRecursos(Extractordatos &extractor, const string &rutacompleta)
{
    ifstream archivo(rutacompleta, ios::binary);
    if (!archivo)
    {
        cerr << "Error al abrir el archivo binario." << endl;
        system("pause");
        return;
    }

    // Leer los datos del archivo binario y almacenarlos en el extractor
    archivo.read(reinterpret_cast<char *>(&extractor.aguaAct), sizeof(extractor.aguaAct));
    archivo.read(reinterpret_cast<char *>(&extractor.vegetacionAct), sizeof(extractor.vegetacionAct));
    archivo.read(reinterpret_cast<char *>(&extractor.carneAct), sizeof(extractor.carneAct));
    archivo.read(reinterpret_cast<char *>(&extractor.carronaAct), sizeof(extractor.carronaAct));
    cout << extractor.aguaAct << endl;
    cout << extractor.vegetacionAct << endl;
    cout << extractor.carneAct << endl;
    cout << extractor.carronaAct << endl;
    system("pause");

    archivo.close();
}