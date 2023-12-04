#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.cpp"
using namespace std;

int IndiceArchivoExcel(const string &nombrebase, const string &ruta);
string existeArchivoExcel(const string &nombrebase, const string &ruta);

void ExcelGenerador(string &usuario, directorios &directorio, bool Auto)
{
    FILE *archivoOriginal, *archivoClonado;
    // Declaracion de variables a usar.
    string nombreOriginal;
    string nombreNuevo = directorio.folderD + "\\" + "macroreg.csv";
    char buffer[4096];
    size_t bytesRead;
    int op;

    // Abrir archivo original
    archivoOriginal = fopen("SalidasDeSIMECO.xlsm", "rb");

    if (archivoOriginal == NULL)
    {
        printf("Error abriendo archivo original\n");
        return;
    }

    string nombreArchivo;
    searchDir(usuario, directorio);

    nombreArchivo = existeArchivoExcel("registro", directorio.folderD);

    if (nombreArchivo == "")
    {
        printf("No se pudo generar un nombre de archivo único\n");
        fclose(archivoOriginal);
        return;
    }

    string rutaArchivoClonado = directorio.folderD + "/" + nombreArchivo;
    archivoClonado = fopen(rutaArchivoClonado.c_str(), "wb");

    if (archivoClonado == NULL)
    {
        printf("Error abriendo archivo clonado\n");
        fclose(archivoOriginal);
        return;
    }

    // Leer bloques de datos del archivo original y escribirlos en el archivo clonado
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), archivoOriginal)) > 0)
    {
        fwrite(buffer, 1, bytesRead, archivoClonado);
    }

    // Cerrar ambos archivos después de la operación
    fclose(archivoOriginal);
    fclose(archivoClonado);

    cout << "1. Generar Excel del ultimo ciclo" << endl;
    cout << "2. Elegir ciclo a mostrar en Excel" << endl;
    cin >> op;
    int Indice;
    if (op == 1)
    {
        Auto = true;
    }
    if (op == 2)
    {
        Auto = false;
    }
    if (Auto)
    {
        Indice = IndiceArchivoExcel("registro", directorio.folderD);
    }
    else
    {
        system("cls");
        cout << "Numero de ciclo a cargar: ";
        cin >> Indice;
    }
    nombreOriginal = buscarNombreIndice("datos", Indice, directorio.folderD, ".csv");
    cout << nombreOriginal;
    system("pause");
    if (actualizarNombre(nombreOriginal, nombreNuevo))
    {
        system("start \"\" \"");
        system(rutaArchivoClonado.c_str());
        system("pause");

        regresarNombre(nombreOriginal, nombreNuevo);
    }
    else
    {
        cout << "vamos mal";
    }
}

// Función existeArchivo
string existeArchivoExcel(const string &nombrebase, const string &ruta)
{
    for (int i = 1; i <= 10; i++)
    {
        string nombrePrueba = nombrebase + to_string(i) + ".xlsm";

        ifstream prueba(ruta + "\\" + nombrePrueba);

        if (!prueba)
        {
            return nombrePrueba;
        }
    }

    return "";
}

int IndiceArchivoExcel(const string &nombrebase, const string &ruta)
{
    for (int i = 1; i <= 10; i++)
    {
        string nombrePrueba = nombrebase + to_string(i) + ".xlsm";

        ifstream prueba(ruta + "\\" + nombrePrueba);

        if (!prueba)
        {
            return i - 1;
        }
    }

    return 0;
}