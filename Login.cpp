#include <iostream>
#include <cstdio>
#include <cstring>
#include <conio.h>
#include <locale.h>

using namespace std;

// Estructura para representar un usuario
struct Usuario {
    char nombreUsuario[100];
    char contrasena[100];
};

// Funci�n para registrar un nuevo usuario
void registrarUsuario(const char* archivo, const Usuario& usuario) {
    FILE* archivoUsuarios = fopen(archivo, "a");

    if (archivoUsuarios != NULL) {
        fprintf(archivoUsuarios, "%s,%s\n", usuario.nombreUsuario, usuario.contrasena);
        fclose(archivoUsuarios);
        cout << "Usuario registrado con �xito." << endl;
    } else {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
    }
}

// Funci�n para verificar las credenciales de inicio de sesi�n
bool verificarCredenciales(const char* archivo, const char* nombreUsuario, const char* contrasena) {
    FILE* archivoUsuarios = fopen(archivo, "r");

    if (archivoUsuarios != NULL) {
        char linea[256];
        while (fgets(linea, sizeof(linea), archivoUsuarios) != NULL) {
            char usuario[100];
            char pass[100];
            sscanf(linea, "%[^,],%s", usuario, pass);

            // Comparar las cadenas manualmente sin strcmp
            bool usuarioIgual = true;
            bool contrasenaIgual = true;
            for (int i = 0; usuario[i] != '\0' || nombreUsuario[i] != '\0'; i++) {
                if (usuario[i] != nombreUsuario[i]) {
                    usuarioIgual = false;
                    break;
                }
            }
            for (int i = 0; pass[i] != '\0' || contrasena[i] != '\0'; i++) {
                if (pass[i] != contrasena[i]) {
                    contrasenaIgual = false;
                    break;
                }
            }
            
            if (usuarioIgual && contrasenaIgual) {
                fclose(archivoUsuarios);
                return true;  // Credenciales v�lidas
            }
        }
        fclose(archivoUsuarios);
    } else {
        cout << "No se pudo abrir el archivo de usuarios." << endl;
    }

    return false;  // Credenciales inv�lidas
}

int main() {
	setlocale(LC_ALL, "spanish");
    const char* archivoUsuarios = "usuarios.txt";
    int opcion;

    // Crear el archivo si no existe
    FILE* archivoExistencia = fopen(archivoUsuarios, "r");
    if (archivoExistencia == NULL) {
        FILE* archivoNuevo = fopen(archivoUsuarios, "w");
        fclose(archivoNuevo);
    } else {
        fclose(archivoExistencia);
    }

    do {
        cout << "Bienvenido al sistema de registro e inicio de sesi�n:" << endl;
        cout << "1. Crear cuenta" << endl;
        cout << "2. Iniciar sesi�n" << endl;
        cout << "3. Salir" << endl;
        cout << "Elija una opci�n: ";
        cin >> opcion;

        if (opcion == 1) {
            Usuario nuevoUsuario;
            cout << "Nombre de usuario: ";
            cin >> nuevoUsuario.nombreUsuario;
            cout << "Contrase�a: ";
            char c;
            int i = 0;
            while (1) {
                c = _getch(); // Captura el car�cter sin mostrarlo
                if (c == 13) { // 13 es el c�digo ASCII de Enter
                    nuevoUsuario.contrasena[i] = '\0'; // Agregar terminador nulo al final
                    cout << endl; // Nueva l�nea despu�s de la contrase�a
                    break;
                }
                else if (c == 8) { // 8 es el c�digo ASCII de Backspace
                    if (i > 0) {
                        i--;
                        cout << "\b \b"; // Borrar el �ltimo car�cter mostrado
                    }
                }
                else {
                    nuevoUsuario.contrasena[i] = c;
                    cout << '*'; // Mostrar asterisco en lugar del car�cter
                    i++;
                }
            }
            registrarUsuario(archivoUsuarios, nuevoUsuario);
        } else if (opcion == 2) {
            char nombreUsuario[100];
            char contrasena[100];
            cout << "Nombre de usuario: ";
            cin >> nombreUsuario;
            cout << "Contrase�a: ";
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
                }
                else {
                    contrasena[i] = c;
                    cout << '*';
                    i++;
                }
            }
            contrasena[i] = '\0';
            cout << endl;
            if (verificarCredenciales(archivoUsuarios, nombreUsuario, contrasena)) {
                cout << "Inicio de sesi�n exitoso." << endl;
            } else {
                cout << "Inicio de sesi�n fallido. Verifique sus credenciales." << endl;
            }
        } else if (opcion == 3) {
            cout << "Saliendo del programa." << endl;
        } else {
            cout << "Opci�n no v�lida. Int�ntelo de nuevo." << endl;
        }
    } while (opcion != 3);

    return 0;
}

