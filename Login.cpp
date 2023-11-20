#include <iostream>
#include <cstdio>
#include <cstring>
#include <conio.h>
#include <locale.h>
#include <cctype>
#include <limits>
#include "Excel.cpp"
#include "SIMECOFV.cpp"
using namespace std;

struct Usuario
{
    char nombreUsuario[100];
    char contrasena[100];
};

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
        cout << "Usuario registrado con éxito." << endl;
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
        cout << "Bienvenido al sistema de registro e inicio de sesión:" << endl;
        cout << "1. Crear cuenta" << endl;
        cout << "2. Iniciar sesión" << endl;
        cout << "3. Salir" << endl;
        cout << "Elija una opción: ";
        cin >> opcionS;
        cin.ignore();
        if (esNumero(opcionS))
        {
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

                cout << "Contraseña: ";
                cin.getline(nuevoUsuario.contrasena, 100);
                registrarUsuario(archivoUsuarios, nuevoUsuario);
                UsuarioConGuiones = nuevoUsuario.nombreUsuario;
                prepararCadenaParaGuardar(&UsuarioConGuiones[0]);
                createFolder(UsuarioConGuiones);
                searchDir(UsuarioConGuiones, directorio);
                GuardardatosSIMECO(UsuarioConGuiones, directorio);

                cin.get();

                break;
            }
            case 2:
            {
                limpiarPantalla();
                cout << "Iniciar sesión:" << endl;
                cout << "Nombre de usuario: ";
                getline(cin, nombreUsuario);
                cout << "Contraseña: ";
                getline(cin, contrasena);

                // Convierte el nombre de usuario a su versión con guiones para la búsqueda
                UsuarioConGuiones = nombreUsuario;
                prepararCadenaParaGuardar(&UsuarioConGuiones[0]);

                if (verificarCredenciales(archivoUsuarios, nombreUsuario.c_str(), contrasena.c_str()))
                {
                    cout << "Inicio de sesión exitoso." << endl;
                    usuario = nombreUsuario;
                    // Llama a searchDir con la versión del nombre de usuario con guiones
                    searchDir(UsuarioConGuiones, directorio);
                    Fvmain(UsuarioConGuiones, directorio);
                    opcion = 3;
                }
                else
                {
                    cout << "Inicio de sesión fallido. Verifique sus credenciales." << endl;
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
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
        else
        {
            cout << "Error: Debe ser un valor numerico" << endl;
            system("pause");
        }
    } while (opcion != 3);
}

void postLogin(string usuario, string directorio)
{
    system("cls");
    cout << "Bienvenido, " << usuario << "!" << endl;
    bool opcion = verificarPartidas(directorio, usuario);
    if (opcion == true)
    {
        cout << "Tienes partidas guardadas, ¿deseas cargar alguna?" << endl;
        cout << "1. Si" << endl;
        cout << "2. No" << endl;
        cout << "Elija una opción: ";
        cin >> opcionS;
        cin.ignore();
        if (esNumero(opcionS))
        {
            if (opcion == 1)
            {
                // cargarPartida(directorio, usuario);
            }
            else
            {
                cout << "No se cargó ninguna partida." << endl;
            }
        }
        else
        {
            cout<<"Error: Debe ser un valor numerico";
        }
    }
    else
    {
        int opcion;
        cout << "Bienvenido a SIMECO, " << usuario << "!" << endl;
        cout << "Que desea hacer?" << endl;
        cout << "1. Seleccione los ciclos que desea simular" << endl;
        cout << "2. Salir" << endl;
        cout << "Elija una opción: ";
        cin >> opcionS;
        cin.ignore();
        if (esNumero(opcionS))
        {
            switch (opcion)
            {
            case 1:
                // simularCiclos(directorio, usuario);
                break;
            case 2:
                cout << "Saliendo del programa." << endl;
                break;
            }
        }
        else
        {
            cout << "Error: Debe ser un valor numerico" << endl;
        }
    }
}