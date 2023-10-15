#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
int main()
{
    FILE *archivoOriginal, *archivoClonado;
    char buffer[4096]; // Buffer de lectura/escritura de 4 KB (puedes ajustar según tus necesidades)
    size_t bytesRead;

    // Abrir el archivo original en modo de lectura binaria
    archivoOriginal = fopen("SalidasDeSIMECO.xlsm", "rb");

    // Verificar si el archivo original se abrió correctamente
    if (archivoOriginal == NULL)
    {
        printf("Error al abrir el archivo original.\n");
        return 1;
    }

    // Abrir un nuevo archivo en modo de escritura binaria
    archivoClonado = fopen("registro.xlsm", "wb");

    // Verificar si el archivo clonado se abrió correctamente
    if (archivoClonado == NULL)
    {
        printf("Error al abrir el archivo clonado.\n");
        fclose(archivoOriginal); // Cerrar el archivo original antes de salir
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

    printf("Archivo clonado exitosamente.\n");
    system("start registro.xlsm");
    return 0;
}
