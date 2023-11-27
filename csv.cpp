#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include "Guardado.cpp"

using namespace std;

struct DatosSimulacion
{
    string poblacionTotalEspecie1, poblacionTotalEspecie2, poblacionTotalEspecie3, poblacionTotalEspecie4;
    string edadPromedioEspecie1, edadPromedioEspecie2, edadPromedioEspecie3, edadPromedioEspecie4;
    string tasaNatalidadEspecie1, tasaNatalidadEspecie2, tasaNatalidadEspecie3, tasaNatalidadEspecie4;
    string tasaMortalidadEspecie1, tasaMortalidadEspecie2, tasaMortalidadEspecie3, tasaMortalidadEspecie4;
    string crecimientoPoblacionEspecie1, crecimientoPoblacionEspecie2, crecimientoPoblacionEspecie3, crecimientoPoblacionEspecie4;
    string promedioIndividuos, poblacionTotal, aguaDisponible, hierbaDisponible;
    string carneDisponible, carronaDisponible, estacionInicial, estacionActual;
    string anoInicio, anoActual, desastresOcurridos, desastresIniciadosUsuario;
    string incendios, sequias, inundaciones, huracanes;
};

string existeArchivo(const string &nombrebase, const string &ruta)
{
    for (int i = 1; i <= 10; i++)
    {
        string nombrePrueba = nombrebase + to_string(i) + ".csv";

        ifstream prueba(ruta + "\\" + nombrePrueba);

        if (!prueba)
        {
            return nombrePrueba;
        }
    }

    return "";
}

string buscarNombreIndice(const string &nombreBase, int indice, const string &ruta)
{
    string nombre = nombreBase + to_string(indice) + ".csv";

    string nombrePrueba = ruta + "\\" + nombre;

    // Intentar abrir el archivo
    ifstream prueba(nombrePrueba);

    if (!prueba)
    {
        return "";
    }
    return nombrePrueba;
}

// Función que cambia el nombre temporalmente
bool actualizarNombre(const string& nombreOriginal, const string& nombreNuevo)
{
    if (rename(nombreOriginal.c_str(), nombreNuevo.c_str()) == 0)
    {
        return true;
    }
    else
    {
        return false; 
    }
}
void regresarNombre(string &nombreOriginal, string &nombreNuevo)
{
    rename(nombreNuevo.c_str(), nombreOriginal.c_str());
}
void crearCSV(const DatosSimulacion &datos, string &nombreArchivo, string rutacsv)
{
    string rutacompleta = rutacsv + "\\" + nombreArchivo;
    ofstream archivo(rutacompleta);
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
    archivo << datos.carronaDisponible << ',';
    archivo << datos.estacionInicial << ',';
    archivo << datos.estacionActual << ',';

    archivo << datos.anoInicio << ',';
    archivo << datos.anoActual << ',';
    archivo << datos.desastresOcurridos << ',';
    archivo << datos.desastresIniciadosUsuario << ',';

    archivo << datos.incendios << ',';
    archivo << datos.sequias << ',';
    archivo << datos.inundaciones << ',';
    archivo << datos.huracanes;

    archivo.close();

    cout << "Archivo CSV creado exitosamente en: " << rutacompleta << endl;
    return;
}

void guardarBinario(const DatosSimulacion &datos, const string &nombreArchivo, const string &ruta)
{
    string rutaCompleta = ruta + "/" + nombreArchivo;
    ofstream archivo(rutaCompleta, ios::binary);

    if (!archivo)
    {
        cerr << "Error al abrir el archivo binario." << endl;
        return;
    }

    archivo.write(reinterpret_cast<const char *>(&datos), sizeof(datos));

    if (archivo.fail())
    {
        cerr << "Error al escribir en el archivo binario." << endl;
    }
    else
    {
        cout << "Datos guardados exitosamente en el archivo binario: " << rutaCompleta << endl;
    }

    archivo.close();
    return;
}

void cargarDatosBinario(DatosSimulacion &datos, const string &nombreArchivo, const string &ruta)
{
    string rutaCompleta = ruta + "\\" + nombreArchivo;
    ifstream archivo(rutaCompleta, ios::binary);

    if (archivo.is_open())
    {
        archivo.read(reinterpret_cast<char *>(&datos), sizeof(datos));
    }
    else
    {
        cerr << "Error al abrir el archivo binario." << endl;
    }

    archivo.close();
    return;
}

void GuardardatosSIMECO(string &usuario, directorios &directorio)
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
    datos.carronaDisponible = "10000";
    datos.estacionInicial = "Verano";
    datos.estacionActual = "Otono";

    datos.anoInicio = "2020";
    datos.anoActual = "2023";
    datos.desastresOcurridos = "2";
    datos.desastresIniciadosUsuario = "3";

    datos.incendios = "1";
    datos.sequias = "0";
    datos.inundaciones = "2";
    datos.huracanes = "2";

    string nombreCSV;
    searchDir(usuario, directorio);
    nombreCSV = existeArchivo("datos", directorio.folderD);

    crearCSV(datos, nombreCSV, directorio.folderD);

    string nombreBin;

    nombreBin = existeArchivo("datos", directorio.folderD);

    nombreBin = nombreCSV + ".bin";

    guardarBinario(datos, nombreBin, directorio.folderD);

    // Lectura del archivo binario

    DatosSimulacion datosCargados;

    // cargarDatosBinario(datosCargados, nombreBin, directorio.folderD);

    // Mostrar datos
}
