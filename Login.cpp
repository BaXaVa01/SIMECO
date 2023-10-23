#include <iostream>
#include <cstdio>
#include <cstring>
#include <conio.h>
#include <locale.h>
#include <cctype>
#include "Guardado.cpp"

using namespace std;

struct Usuario
{
    char nombreUsuario[100];
    char contrasena[100];
};

void registrarUsuario(const char *archivo, const Usuario &usuario)
{
    FILE *archivoUsuarios = fopen(archivo, "a");

    if (archivoUsuarios != NULL)
    {
        fprintf(archivoUsuarios, "%s,%s\n", usuario.nombreUsuario, usuario.contrasena);
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

    if (archivoUsuarios != NULL)
    {
        char linea[256];
        while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL)
        {
            char usuario[100];
            char pass[100];
            sscanf(linea, "%[^,],%s", usuario, pass);

            for (int i = 0; usuario[i] != '\0'; i++)
            {
                usuario[i] = tolower(usuario[i]);
            }

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

bool nombreUsuarioExistente(const char *archivo, const char *nombreUsuario)
{
    FILE *archivoUsuarios = fopen(archivo, "rb");

    if (archivoUsuarios != NULL)
    {
        char linea[256];
        while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL)
        {
            char usuario[100];
            sscanf(linea, "%[^,]", usuario);

            for (int i = 0; usuario[i] != '\0'; i++)
            {
                usuario[i] = tolower(usuario[i]);
            }

            if (strcmp(usuario, nombreUsuario) == 0)
            {
                fclose(archivoUsuarios);
                return true;
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

void MenuLogin(string& usuariO)
{
    setlocale(LC_ALL, "spanish");

    const char *archivoUsuarios = "usuarios.bin";
    int opcion;

    FILE *archivoExistencia = fopen(archivoUsuarios, "rb");
    if (archivoExistencia == NULL)
    {
        FILE *archivoNuevo = fopen(archivoUsuarios, "wb");
        fclose(archivoNuevo);
    }
    else
    {
        fclose(archivoExistencia);
    }

    do
    {
        limpiarPantalla();
        cout << "Bienvenido al sistema de registro e inicio de sesión:" << endl;
        cout << "1. Crear cuenta" << endl;
        cout << "2. Iniciar sesión" << endl;
        cout << "3. Salir" << endl;
        cout << "Elija una opción: ";
        cin >> opcion;

        if (opcion == 1)
        {
            limpiarPantalla();
            Usuario nuevoUsuario;
            cout << "Crear una nueva cuenta:" << endl;
            bool nombreUsuarioDuplicado;
            do
            {
                nombreUsuarioDuplicado = false;
                cout << "Nombre de usuario: ";
                cin >> nuevoUsuario.nombreUsuario;
                for (int i = 0; nuevoUsuario.nombreUsuario[i] != '\0'; i++)
                {
                    nuevoUsuario.nombreUsuario[i] = tolower(nuevoUsuario.nombreUsuario[i]);
                }
                if (nombreUsuarioExistente(archivoUsuarios, nuevoUsuario.nombreUsuario))
                {
                    nombreUsuarioDuplicado = true;
                    cout << "El nombre de usuario ya existe. Por favor, elija otro." << endl;
                }
            } while (nombreUsuarioDuplicado);

            cout << "Contraseña: ";
            char c;
            int i = 0;
            while (1)
            {
                c = _getch();
                if (c == 13)
                {
                    nuevoUsuario.contrasena[i] = '\0';
                    cout << endl;
                    break;
                }
                else if (c == 8)
                {
                    if (i > 0)
                    {
                        i--;
                        cout << "\b \b";
                    }
                }
                else
                {
                    nuevoUsuario.contrasena[i] = c;
                    cout << '*';
                    i++;
                }
            }
            registrarUsuario(archivoUsuarios, nuevoUsuario);
            createFolder(nuevoUsuario.nombreUsuario);
            cout << "Presione Enter para continuar...";
            _getch();
        }
        else if (opcion == 2)
        {
            limpiarPantalla();
            char nombreUsuario[100];
            char contrasena[100];
            cout << "Iniciar sesión:" << endl;
            cout << "Nombre de usuario: ";
            cin >> nombreUsuario;
            for (int i = 0; nombreUsuario[i] != '\0'; i++)
            {
                nombreUsuario[i] = tolower(nombreUsuario[i]);
            }
            cout << "Contraseña: ";
            char c;
            int i = 0;
            while (1)
            {
                c = _getch();
                if (c == 13)
                    break;
                else if (c == 8)
                {
                    if (i > 0)
                    {
                        i--;
                        cout << "\b \b";
                    }
                }
                else
                {
                    contrasena[i] = c;
                    cout << '*';
                    i++;
                }
            }
            contrasena[i] = '\0';
            cout << endl;
            if (verificarCredenciales(archivoUsuarios, nombreUsuario, contrasena))
            {
                cout << "Inicio de sesión exitoso." << endl;
                usuariO = nombreUsuario;
                opcion = 3;
            }
            else
            {
                cout << "Inicio de sesión fallido. Verifique sus credenciales." << endl;
            }
            cout << "Presione Enter para continuar...";
            _getch();
            

 
        }
        else if (opcion == 3)
        {
            cout << "Saliendo del programa." << endl;
        }
        else
        {
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
            cout << "Presione Enter para continuar...";
            _getch();
        }
    } while (opcion != 3);
    return;
}