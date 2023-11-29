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
struct DatosAnimal
{
    int edad;
    int genero;
};
DatosAnimal datos;

void GuardarAnimal(const DatosAnimal datos, bool terminar, const string &fileName)
{
    ifstream file(fileName);
    string content;
    int commaCount = 0;
    size_t lastCommaPosition = string::npos;
    if (!file.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Lee todo el contenido del archivo
    string line;
    while (getline(file, line))
    {
        for (size_t i = 0; i < line.size(); ++i)
        {
            if (line[i] == ',')
            {
                lastCommaPosition = content.size() + i;
                commaCount++;
            }
        }
        content += line + "\n";
    }

    file.close();

    // Si terminar es true, simplemente añade "-", de lo contrario, añade los datos
    if (terminar)
    {
        content += "-";
    }
    else
    {
        if (lastCommaPosition != string::npos)
        {
            content.insert(lastCommaPosition + 1, to_string(datos.edad) + "," + to_string(datos.genero) + ",");
        }
    }

    // Sobrescribe el archivo con el contenido modificado
    ofstream outFile(fileName);
    if (outFile.is_open())
    {
        outFile << content;
        outFile.close();
    }
    else
    {
        cerr << "Error al abrir el archivo para escribir." << endl;
    }
}

string existeArchivo(const string &nombrebase, const string &ruta, string ext)
{
    if (nombrebase == "ciclo")
    {
        for (int i = 1; i <= 10; i++)
        {
            string nombrePrueba = nombrebase + to_string(i) + ext;

            ifstream prueba(ruta + "\\" + nombrePrueba);

            if (prueba)
            {
                nombrePrueba = ruta + "\\" + nombrePrueba;
                return nombrePrueba;
            }
        }
    }
    else
    {
        for (int i = 1; i <= 10; i++)
        {
            string nombrePrueba = nombrebase + to_string(i) + ext;

            ifstream prueba(ruta + "\\" + nombrePrueba);

            if (!prueba)
            {
                return nombrePrueba;
            }
        }
    }

    return "";
}

string buscarNombreIndice(const string &nombreBase, int indice, const string &ruta, string ext)
{
    string nombre = nombreBase + to_string(indice) + ext;

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
bool actualizarNombre(const string &nombreOriginal, const string &nombreNuevo)
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
    DatosSimulacion datosS;

    datosS.poblacionTotalEspecie1 = "500";
    datosS.poblacionTotalEspecie2 = "500";
    datosS.poblacionTotalEspecie3 = "0";
    datosS.poblacionTotalEspecie4 = "0";

    datosS.edadPromedioEspecie1 = "5";
    datosS.edadPromedioEspecie2 = "3";
    datosS.edadPromedioEspecie3 = "0";
    datosS.edadPromedioEspecie4 = "0";

    datosS.tasaNatalidadEspecie1 = "10";
    datosS.tasaNatalidadEspecie2 = "20";
    datosS.tasaNatalidadEspecie3 = "0";
    datosS.tasaNatalidadEspecie4 = "0";

    datosS.tasaMortalidadEspecie1 = "0.20";
    datosS.tasaMortalidadEspecie2 = "0.10";
    datosS.tasaMortalidadEspecie3 = "0";
    datosS.tasaMortalidadEspecie4 = "0";

    datosS.crecimientoPoblacionEspecie1 = "5";
    datosS.crecimientoPoblacionEspecie2 = "8";
    datosS.crecimientoPoblacionEspecie3 = "0";
    datosS.crecimientoPoblacionEspecie4 = "0";

    datosS.promedioIndividuos = "800";
    datosS.poblacionTotal = "1450";
    datosS.aguaDisponible = "50000";
    datosS.hierbaDisponible = "100000";

    datosS.carneDisponible = "20000";
    datosS.carronaDisponible = "10000";
    datosS.estacionInicial = "Verano";
    datosS.estacionActual = "Otono";

    datosS.anoInicio = "2020";
    datosS.anoActual = "2023";
    datosS.desastresOcurridos = "2";
    datosS.desastresIniciadosUsuario = "3";

    datosS.incendios = "1";
    datosS.sequias = "0";
    datosS.inundaciones = "2";
    datosS.huracanes = "2";

    string nombreCSV;
    searchDir(usuario, directorio);
    nombreCSV = existeArchivo("datos", directorio.folderD, ".csv");

    crearCSV(datosS, nombreCSV, directorio.folderD);

    string nombreBin;

    nombreBin = existeArchivo("datos", directorio.folderD, ".csv");

    nombreBin = nombreCSV + ".bin";

    guardarBinario(datosS, nombreBin, directorio.folderD);

    // Lectura del archivo binario

    DatosSimulacion datosCargados;

    // cargarDatosBinario(datosCargados, nombreBin, directorio.folderD);

    // Mostrar datos
}
