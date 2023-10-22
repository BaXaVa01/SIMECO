#include <iostream>
#include <cstdio>
#include <cstring>
#include <conio.h>
#include <locale.h>
#include <cctype> // Incluir cctype para funciones de manipulación de caracteres

using namespace std;

// Estructura para representar un usuario
struct Usuario {
    char nombreUsuario[100];
    char contrasena[100];
};

// Función para registrar un nuevo usuario
void registrarUsuario(const char* archivo, const Usuario& usuario) {
    FILE* archivoUsuarios = fopen(archivo, "a");

    if (archivoUsuarios != NULL) {
        fprintf(archivoUsuarios, "%s,%s\n", usuario.nombreUsuario, usuario.contrasena);
        fclose(archivoUsuarios);
        cout << "Usuario registrado con éxito." << endl;
    } else {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
    }
}

// Función para verificar las credenciales de inicio de sesión
bool verificarCredenciales(const char* archivo, const char* nombreUsuario, const char* contrasena) {
    FILE* archivoUsuarios = fopen(archivo, "r");

    if (archivoUsuarios != NULL) {
        char linea[256];
        while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL) {
            char usuario[100];
            char pass[100];
            sscanf(linea, "%[^,],%s", usuario, pass);

            // Convertir los nombres de usuario a minúsculas para la comparación
            for (int i = 0; usuario[i] != '\0'; i++) {
                usuario[i] = tolower(usuario[i]);
            }

            // Comparar las cadenas
            if (strcmp(usuario, nombreUsuario) == 0 && strcmp(pass, contrasena) == 0) {
                fclose(archivoUsuarios);
                return true;  // Credenciales válidas
            }
        }
        fclose(archivoUsuarios);
    } else {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
    }

    return false;  // Credenciales inválidas
}

// Función para comprobar si un nombre de usuario ya existe en el archivo
bool nombreUsuarioExistente(const char* archivo, const char* nombreUsuario) {
    FILE* archivoUsuarios = fopen(archivo, "r");

    if (archivoUsuarios != NULL) {
        char linea[256];
        while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL) {
            char usuario[100];
            sscanf(linea, "%[^,]", usuario);

            // Convertir los nombres de usuario a minúsculas para la comparación
            for (int i = 0; usuario[i] != '\0'; i++) {
                usuario[i] = tolower(usuario[i]);
            }

            // Comparar las cadenas
            if (strcmp(usuario, nombreUsuario) == 0) {
                fclose(archivoUsuarios);
                return true; // Nombre de usuario ya existe
            }
        }
        fclose(archivoUsuarios);
    }

    return false;  // Nombre de usuario no existe
}

// Función para limpiar la pantalla
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    setlocale(LC_ALL, "spanish");

    const char* archivoUsuarios = "usuarios.txt";
    int opcion;

    FILE* archivoExistencia = fopen(archivoUsuarios, "r");
    if (archivoExistencia == NULL) {
        FILE* archivoNuevo = fopen(archivoUsuarios, "w");
        fclose(archivoNuevo);
    } else {
        fclose(archivoExistencia);
    }

    do {
        limpiarPantalla();
        cout << "Bienvenido a SIMECO:" << endl;
        cout << "1. Crear cuenta" << endl;
        cout << "2. Iniciar sesión" << endl;
        cout << "3. Salir" << endl;
        cout << "Elija una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            limpiarPantalla();
            Usuario nuevoUsuario;
            cout << "Crear una nueva cuenta:" << endl;
            bool nombreUsuarioDuplicado;
            do {
                nombreUsuarioDuplicado = false;
                cout << "Nombre de usuario: ";
                cin >> nuevoUsuario.nombreUsuario;
                // Convertir el nombre de usuario a minúsculas para la comparación
                for (int i = 0; nuevoUsuario.nombreUsuario[i] != '\0'; i++) {
                    nuevoUsuario.nombreUsuario[i] = tolower(nuevoUsuario.nombreUsuario[i]);
                }
                if (nombreUsuarioExistente(archivoUsuarios, nuevoUsuario.nombreUsuario)) {
                    nombreUsuarioDuplicado = true;
                    cout << "El nombre de usuario ya existe. Por favor, elija otro." << endl;
                }
            } while (nombreUsuarioDuplicado);

            cout << "Contraseña: ";
            char c;
            int i = 0;
            while (1) {
                c = _getch();
                if (c == 13) {
                    nuevoUsuario.contrasena[i] = '\0';
                    cout << endl;
                    break;
                } else if (c == 8) {
                    if (i > 0) {
                        i--;
                        cout << "\b \b";
                    }
                } else {
                    nuevoUsuario.contrasena[i] = c;
                    cout << '*';
                    i++;
                }
            }
            registrarUsuario(archivoUsuarios, nuevoUsuario);
            cout << "Presione Enter para continuar...";
            _getch();
        } else if (opcion == 2) {
            limpiarPantalla();
            char nombreUsuario[100];
            char contrasena[100];
            cout << "Iniciar sesión:" << endl;
            cout << "Nombre de usuario: ";
            cin >> nombreUsuario;
            // Convertir el nombre de usuario a minúsculas para la comparación
            for (int i = 0; nombreUsuario[i] != '\0'; i++) {
                nombreUsuario[i] = tolower(nombreUsuario[i]);
            }
            cout << "Contraseña: ";
            char c;
            int i = 0;
            while (1) {
                c = _getch();
                if (c == 13)
                    break;
                else if (c == 8) {
                    if (i > 0) {
                        i--;
                        cout << "\b \b";
                    }
                } else {
                    contrasena[i] = c;
                    cout << '*';
                    i++;
                }
            }
            contrasena[i] = '\0';
            cout << endl;
            if (verificarCredenciales(archivoUsuarios, nombreUsuario, contrasena)) {
                cout << "Inicio de sesión exitoso." << endl;
            } else {
                cout << "Inicio de sesión fallido. Verifique sus credenciales." << endl;
            }
            cout << "Presione Enter para continuar...";
            _getch();
        } else if (opcion == 3) {
            cout << "Saliendo del programa." << endl;
        } else {
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
            cout << "Presione Enter para continuar...";
            _getch();
        }
    } while (opcion != 3);

    return 0;
}
