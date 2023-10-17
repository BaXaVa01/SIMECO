#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

struct DatosSimulacion
{
    string poblacionTotalEspecie1, poblacionTotalEspecie2, poblacionTotalEspecie3, poblacionTotalEspecie4;
    string edadPromedioEspecie1, edadPromedioEspecie2, edadPromedioEspecie3, edadPromedioEspecie4;
    string tasaNatalidadEspecie1, tasaNatalidadEspecie2, tasaNatalidadEspecie3, tasaNatalidadEspecie4;
    string tasaMortalidadEspecie1, tasaMortalidadEspecie2, tasaMortalidadEspecie3, tasaMortalidadEspecie4;
    string crecimientoPoblacionEspecie1, crecimientoPoblacionEspecie2, crecimientoPoblacionEspecie3, crecimientoPoblacionEspecie4;
    string promedioIndividuos, poblacionTotal, aguaDisponible, hierbaDisponible;
    string carneDisponible, carroñaDisponible, estacionInicial, estacionActual;
    string añoInicio, añoActual, desastresOcurridos, desastresIniciadosUsuario;
    string incendios, sequias, inundaciones, huracanes;
};

char *existeArchivo(const char *nombrebase)
{

    for (int i = 1; i <= 10; i++)
    {

        char nombrePrueba[100];
        sprintf(nombrePrueba, "%s%d.csv", nombrebase, i);

        FILE *prueba = fopen(nombrePrueba, "r");

        if (prueba == NULL)
        {
            return strdup(nombrePrueba);
        }

        fclose(prueba);
    }

    return NULL;
}

char* buscarNombreIndice(char* nombreBase, int indice) {

  char nombre[100]; 
  sprintf(nombre, "%s%d.csv", nombreBase, indice);

  // Verificar que existe el archivo

  return strdup(nombre); 
}

// Función que cambia el nombre temporalmente
void actualizarNombre(char* nombreOriginal, char* nombreNuevo) {

  // Renombrar archivo original a nombreNuevo 
  rename(nombreOriginal,nombreNuevo);  
}
void regresarNombre(char*nombreOriginal,char* nombreNuevo)
{
    rename(nombreNuevo,nombreOriginal);
}

void leerCSV(DatosSimulacion &datos)
{

    ifstream archivo("datos.csv");

    getline(archivo, datos.poblacionTotalEspecie1, ',');
    getline(archivo, datos.poblacionTotalEspecie2, ',');
    getline(archivo, datos.poblacionTotalEspecie3, ',');
    getline(archivo, datos.poblacionTotalEspecie4, ',');

    getline(archivo, datos.edadPromedioEspecie1, ',');
    getline(archivo, datos.edadPromedioEspecie2, ',');
    getline(archivo, datos.edadPromedioEspecie3, ',');
    getline(archivo, datos.edadPromedioEspecie4, ',');

    getline(archivo, datos.tasaNatalidadEspecie1, ',');
    getline(archivo, datos.tasaNatalidadEspecie2, ',');
    getline(archivo, datos.tasaNatalidadEspecie3, ',');
    getline(archivo, datos.tasaNatalidadEspecie4, ',');

    getline(archivo, datos.tasaMortalidadEspecie1, ',');
    getline(archivo, datos.tasaMortalidadEspecie2, ',');
    getline(archivo, datos.tasaMortalidadEspecie3, ',');
    getline(archivo, datos.tasaMortalidadEspecie4, ',');

    getline(archivo, datos.crecimientoPoblacionEspecie1, ',');
    getline(archivo, datos.crecimientoPoblacionEspecie2, ',');
    getline(archivo, datos.crecimientoPoblacionEspecie3, ',');
    getline(archivo, datos.crecimientoPoblacionEspecie4, ',');

    getline(archivo, datos.promedioIndividuos, ',');
    getline(archivo, datos.poblacionTotal, ',');
    getline(archivo, datos.aguaDisponible, ',');
    getline(archivo, datos.hierbaDisponible, ',');

    getline(archivo, datos.carneDisponible, ',');
    getline(archivo, datos.carroñaDisponible, ',');
    getline(archivo, datos.estacionInicial, ',');
    getline(archivo, datos.estacionActual, ',');

    getline(archivo, datos.añoInicio, ',');
    getline(archivo, datos.añoActual, ',');
    getline(archivo, datos.desastresOcurridos, ',');
    getline(archivo, datos.desastresIniciadosUsuario, ',');

    getline(archivo, datos.incendios, ',');
    getline(archivo, datos.sequias, ',');
    getline(archivo, datos.inundaciones, ',');
    getline(archivo, datos.huracanes);

    archivo.close();
}

void crearCSV(const DatosSimulacion &datos, const char *nombreArchivo)
{
    ofstream archivo(nombreArchivo);
    if (!archivo)
    {
        cerr << "Error al crear el archivo CSV." << endl;
        return;
    }

    // Escribir los datos en el archivo CSV
    archivo << datos.poblacionTotalEspecie1 << ',';
    archivo << datos.poblacionTotalEspecie2 << ',';
    archivo << datos.poblacionTotalEspecie3 << ',';
    archivo << datos.poblacionTotalEspecie4 << ',';

    archivo << datos.edadPromedioEspecie1 << ',';
    archivo << datos.edadPromedioEspecie2 << ',';
    archivo << datos.edadPromedioEspecie3 << ',';
    archivo << datos.edadPromedioEspecie4 << ',';

    archivo << datos.tasaNatalidadEspecie1 << ',';
    archivo << datos.tasaNatalidadEspecie2 << ',';
    archivo << datos.tasaNatalidadEspecie3 << ',';
    archivo << datos.tasaNatalidadEspecie4 << ',';

    archivo << datos.tasaMortalidadEspecie1 << ',';
    archivo << datos.tasaMortalidadEspecie2 << ',';
    archivo << datos.tasaMortalidadEspecie3 << ',';
    archivo << datos.tasaMortalidadEspecie4 << ',';

    archivo << datos.crecimientoPoblacionEspecie1 << ',';
    archivo << datos.crecimientoPoblacionEspecie2 << ',';
    archivo << datos.crecimientoPoblacionEspecie3 << ',';
    archivo << datos.crecimientoPoblacionEspecie4 << ',';

    archivo << datos.promedioIndividuos << ',';
    archivo << datos.poblacionTotal << ',';
    archivo << datos.aguaDisponible << ',';
    archivo << datos.hierbaDisponible << ',';

    archivo << datos.carneDisponible << ',';
    archivo << datos.carroñaDisponible << ',';
    archivo << datos.estacionInicial << ',';
    archivo << datos.estacionActual << ',';

    archivo << datos.añoInicio << ',';
    archivo << datos.añoActual << ',';
    archivo << datos.desastresOcurridos << ',';
    archivo << datos.desastresIniciadosUsuario << ',';

    archivo << datos.incendios << ',';
    archivo << datos.sequias << ',';
    archivo << datos.inundaciones << ',';
    archivo << datos.huracanes;

    archivo.close();

    cout << "Archivo CSV creado exitosamente." << endl;
}

void guardarBinario(DatosSimulacion datos, const char *nombreArchivo)
{

    ofstream archivo(nombreArchivo, ios::binary);

    archivo.write((char *)&datos, sizeof(datos));

    archivo.close();
}

void cargarDatosBinario(DatosSimulacion &datos, const char *nombreArchivo)
{

    ifstream archivo(nombreArchivo, ios::binary);

    if (archivo.is_open())
    {

        archivo.read((char *)&datos, sizeof(datos));
    }
    else
    {

        cerr << "Error abriendo archivo binario" << endl;
    }

    archivo.close();
}

void GuardardatosSIMECO()
{
    DatosSimulacion datos;

    datos.poblacionTotalEspecie1 = "500";
    datos.poblacionTotalEspecie2 = "500";
    datos.poblacionTotalEspecie3 = "750";
    datos.poblacionTotalEspecie4 = "200";

    datos.edadPromedioEspecie1 = "5";
    datos.edadPromedioEspecie2 = "3";
    datos.edadPromedioEspecie3 = "4";
    datos.edadPromedioEspecie4 = "2";

    datos.tasaNatalidadEspecie1 = "10";
    datos.tasaNatalidadEspecie2 = "20";
    datos.tasaNatalidadEspecie3 = "15";
    datos.tasaNatalidadEspecie4 = "8";

    datos.tasaMortalidadEspecie1 = "5";
    datos.tasaMortalidadEspecie2 = "10";
    datos.tasaMortalidadEspecie3 = "7";
    datos.tasaMortalidadEspecie4 = "3";

    datos.crecimientoPoblacionEspecie1 = "5";
    datos.crecimientoPoblacionEspecie2 = "8";
    datos.crecimientoPoblacionEspecie3 = "6";
    datos.crecimientoPoblacionEspecie4 = "2";

    datos.promedioIndividuos = "800";
    datos.poblacionTotal = "1450";
    datos.aguaDisponible = "50000";
    datos.hierbaDisponible = "100000";

    datos.carneDisponible = "20000";
    datos.carroñaDisponible = "10000";
    datos.estacionInicial = "Verano";
    datos.estacionActual = "Otoño";

    datos.añoInicio = "2020";
    datos.añoActual = "2023";
    datos.desastresOcurridos = "2";
    datos.desastresIniciadosUsuario = "3";

    datos.incendios = "1";
    datos.sequias = "0";
    datos.inundaciones = "2";
    datos.huracanes = "2";

    char *nombreCSV;

    nombreCSV = existeArchivo("datos");

    crearCSV(datos, nombreCSV);

    char *nombreBin;

    nombreBin = existeArchivo("datos");

    sprintf(nombreBin, "%s.bin", nombreCSV);

    guardarBinario(datos, nombreBin);

    // Lectura del archivo binario

    DatosSimulacion datosCargados;

    cargarDatosBinario(datosCargados, nombreBin);

    // Mostrar datos

    cout << datosCargados.poblacionTotalEspecie1 << endl;
    cout << datosCargados.huracanes << endl;
}
