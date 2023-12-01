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
#include "pantallacarga3.cpp"
#include "pantallacarga1.cpp"
// HAY QUE ELIMINAR EL clearScreen al momento de unir los modulos relacion Animal recursos

using namespace std;
Extractordatos extractor;
DatosSimulacion datosS;
struct Usuario
{
    char nombreUsuario[100];
    char contrasena[100];
};
string NombreBinA;
int contadorFase;
streampos posicionactual;
void ExtraerDatos(DatosSimulacion &datos, Extractordatos extract);
void mostrarEstadoInicialEcosistema(Ecosistema &ecosistema)
{

    clearScreen();
    cout << "Estado inicial del ecosistema:\n"
         << endl;
    cout << "Recursos iniciales:\n";
    // cout << "- Agua: " << ecosistema.recursosIniciales.agua << endl;
    cout << "- Agua: " << ecosistema.recursosIniciales.agua << "m3" << endl;
    cout << "- Carrona: " << ecosistema.recursosIniciales.carrona << "Kg" << endl;
    cout << "- Carne: " << ecosistema.recursosIniciales.carne << "Kg" << endl;
    cout << "- Vegetacion: " << ecosistema.recursosIniciales.vegetacion << "m2" << endl;

    cout << "\nEspecies registradas:\n";
    cout << "-Poblacion Venados: " << ecosistema.pVenados << endl;
    cout << "-Poblacion Pumas: " << ecosistema.pPumas << endl;

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

void mostrarEstadoEcosistema(Ecosistema &ecosistema)
{

    clearScreen();
    cout << "Estado actual del ecosistema:\n"
         << endl;
    cout << "Recursos:\n";
    cout << "- Agua: " << ecosistema.recursosActuales.agua << "m3" << endl;
    cout << "- Carrona: " << ecosistema.recursosActuales.carrona << "Kg" << endl;
    cout << "- Carne: " << ecosistema.recursosActuales.carne << "Kg" << endl;
    cout << "- Vegetacion: " << ecosistema.recursosActuales.vegetacion << "m2" << endl;

    cout << "\nEspecies:\n";
    cout << "-Poblacion Venados: " << ecosistema.pVenados << endl;
    cout << "-Poblacion Pumas: " << ecosistema.pPumas << endl;

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
        ecosistema.recursosActuales.agua *= 0.9;       // Reduccion leve

        break;
    case TipoDesastre::Inundacion:
        cout << "Inundacion" << endl;
        ecosistema.recursosActuales.agua *= 1.6;       // Aumento significativo
        ecosistema.recursosActuales.vegetacion *= 1.4; // Aumento significativo

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
        break;
    default:
        break;
    }
    // Por el momento los desastres solo afectan a los recursos

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
    // Estos vectores son necesarios siempre para el inicio de la partida
    vector<Venado> venados; // 10 machos y 10 hembras
    vector<Puma> pumas;     // 1 macho y 1 hembra

        int cantidadVenadosHembra, cantidadPumasMacho, cantidadVenadosMacho, cantidadPumasHembra;
    // Esta funcion es solo si el usuario no tiene partida guardada
    cout << "Bienvenido a SIMECO" << endl;  
    
    
    cout << "                   Desea entrar en el modo avanzado?"<<endl;
    cout << "                   1. Si \n 2.No"<<endl;
    int opl;    
    cin >> opl;
    if (opl == 1)
    {
        cout << "A continuacion, se le pedira que ingrese los datos iniciales del ecosistema." << endl;
        cout << "Ingrese los venados hembra que desea:";
        cin >> cantidadVenadosHembra;
        cout << "Ingrese los venados macho que desea:";
        cin >> cantidadVenadosMacho;
        cout << "Ingrese los pumas hembra que desea:";
        cin >> cantidadPumasHembra;
        cout << "Ingrese los pumas macho que desea:";
        cin >> cantidadPumasMacho;
        

        iniciarEspecies(venados, pumas, cantidadVenadosHembra, cantidadVenadosMacho,cantidadPumasHembra,cantidadPumasMacho);
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
    do
    {

        clearScreen();
        cout << "Menu:\n"
             << endl;
        cout << "1. Ver estado inicial del ecosistema" << endl;
        cout << "2. Ver estado anterior del ecosistema" << endl;
        cout << "3. Ver estado actual del ecosistema" << endl;
        cout << "4. Iniciar ciclos" << endl;
        cout << "5. Generar desastre" << endl;
        cout << "6. Gestor de Datos de partida" << endl;
        cout << "7. Abrir pagina Web SIMECO" << endl;
        cout << "8. Salir" << endl;
        cout << "\nIngrese una opcion: ";
        cin >> opcionS;
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
                mostrarEstadoInicialEcosistema(datosEcosistemaAnt);
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
                extractor.cantHur = 0;
                extractor.cantInc = 0;
                extractor.cantInd = 0;
                extractor.cantSeq = 0;
                mainRelacionAnimalRecurso(usuario, venados, pumas, datosEcosistema, extractor, estacion);
                extractor.aguaAct = datosEcosistema.recursosActuales.agua;
                contador = 0;
                for (auto &venado : venados)
                {
                    edadpromedio += venado.mostrarEdad();
                    contador++;
                }
                extractor.EdadV = edadpromedio / contador;
                contador = 0;
                edadpromedio=0;
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
                    generarDesastre(datosEcosistema, TipoDesastre::Incendio);
                    extractor.cantInc++;
                    break;
                case 2:
                    generarDesastre(datosEcosistema, TipoDesastre::Inundacion);
                    extractor.cantInd++;
                    break;
                case 3:
                    generarDesastre(datosEcosistema, TipoDesastre::Sequia);
                    extractor.cantSeq++;
                    break;
                case 4:
                    generarDesastre(datosEcosistema, TipoDesastre::Huracan);
                    extractor.cantHur++;
                    break;
                default:
                    break;
                }
                break;
            }
            case 6:
            {
                cout << "1. Generar Excel" << endl;
                cout << "2. Guardar Partida" << endl;
                cout << "3. Cargar Partida" << endl;
                cin >> opcionS;
                esNumero(opcionS);
                opcionMenuPartida = stoi(opcionS);
                switch (opcionMenuPartida)
                {
                case 1:
                {
                    if (Guardado)
                    {
                        clearScreen();
                        ExcelGenerador(usuario, directorio, Excel);
                    }
                    else
                    {
                        cout << "Debes guardar la partida antes de mostrar los datos";
                        system("pause");
                    }

                    break;
                }
                case 2:
                {
                    NombreBinA = existeArchivo("ciclo", directorio.folder1, ".bin");
                    bool ultimoDelGrupo;

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
                    // GuardarRecursos(recursos);
                    // GuardarDesastres(listadesastres);
                    ExtraerDatos(datosS, extractor);
                    GuardardatosSIMECO(usuario, directorio, datosS);
                    barraCarga(5);
                    Guardado = true;
                    break;
                }
                case 3:
                {
                    NombreBinA = existeArchivo("ciclo", directorio.folder1, ".bin");
                    venados.clear();
                    pumas.clear();
                    LeerAnimal(NombreBinA, venados, pumas);
                    mainP3();
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
            case 8:
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
        }
        else
        {
            cerr << "Error: Debe de ser un numero entero" << endl;
        }
    } while (opcion != 8);

    return 0;
}

void MenuLogin(string &usuario)
{
    mainBarra1();
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
                    mainBarra1();
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
    result=0;
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
}