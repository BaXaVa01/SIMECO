#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <filesystem>
#include "csv.cpp"
using namespace std;

char *existeArchivo(const char *nombrebase);
int IndiceArchivoExcel(const char *nombrebase);
char *existeArchivoExcel(const char *nombrebase);

int main()
{
    FILE *archivoOriginal, *archivoClonado;
    // Declaracion de variables a usar.
    char *nombreOriginal;
    char nombreNuevo[] = "macroreg.csv";
    char buffer[4096];
    size_t bytesRead;

    // Abrir archivo original
    archivoOriginal = fopen("SalidasDeSIMECO.xlsm", "rb");

    if (archivoOriginal == NULL)
    {
        printf("Error abriendo archivo original\n");
        return 1;
    }

    char *nombreArchivo;

    nombreArchivo = existeArchivoExcel("registro");

    if (nombreArchivo == NULL)
    {
        printf("No se pudo generar un nombre de archivo único\n");
        fclose(archivoOriginal);
        return 1;
    }

    archivoClonado = fopen(nombreArchivo, "wb");

    if (archivoClonado == NULL)
    {
        printf("Error abriendo archivo clonado\n");
        fclose(archivoOriginal);
        return 1;
    }

    // Leer bloques de datos del archivo original y escribirlos en el archivo clonado
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), archivoOriginal)) > 0)
    {
        fwrite(buffer, 1, bytesRead, archivoClonado);
    }

    // Cerrar ambos archivos después de la operación
    fclose(archivoOriginal);
    fclose(archivoClonado);
    int Indice;
    Indice = IndiceArchivoExcel("registro");
    nombreOriginal = buscarNombreIndice("datos", Indice);
    actualizarNombre(nombreOriginal, nombreNuevo);
    printf("Archivo clonado exitosamente.\n");
    system("start \"\" \"");
    system(nombreArchivo);
    system("pause");
    regresarNombre(nombreOriginal, nombreNuevo);

    return 0;
}

// Función existeArchivo
char *existeArchivoExcel(const char *nombrebase)
{
    for (int i = 1; i <= 10; i++)
    {
        char nombrePrueba[100];
        sprintf(nombrePrueba, "%s%d.xlsm", nombrebase, i);

        FILE *prueba = fopen(nombrePrueba, "rb");

        if (prueba == NULL)
        {
            return strdup(nombrePrueba);
        }

        fclose(prueba);
    }

    return NULL;
}

int IndiceArchivoExcel(const char *nombrebase)
{
    for (int i = 1; i <= 10; i++)
    {
        char nombrePrueba[100];
        sprintf(nombrePrueba, "%s%d.xlsm", nombrebase, i);

        FILE *prueba = fopen(nombrePrueba, "rb");

        if (prueba == NULL)
        {
            return i - 1;
        }

        fclose(prueba);
    }

    return 0;
}
