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
    string promedioIndividuosA, poblacionTotalA, aguaDisponibleA, hierbaDisponibleA;
    string carneDisponible, carronaDisponible, estacionInicial, estacionActual;
    string anoInicio, anoActual, desastresOcurridos, desastresIniciadosUsuario;
    string incendios, sequias, inundaciones, huracanes;
};
struct Extractordatos
{
    int contadorMuerteV;
    int contadorMuerteP;
    int AnteVenados;
    int AntePumas;
    int EdadV;
    int EdadP;
    int PV;
    int PP;
    int aguaAct;
    int vegetacionAct;
    int carronaAct;
    int carneAct;
    int aguaA;
    int EstacionA;
    int estacionAct;
    int vegetacionA;
    int carronaA;
    int carneA;
    int cantInc;
    int cantSeq;
    int cantInd;
    int cantHur;
    int cnum;
};

struct DatosAnimal
{
    int edad;
    int genero;
};
DatosAnimal datos;

void GuardarAnimal(const DatosAnimal datos, bool ultimoDelGrupo, const string &fileName)
{
    // Abre el archivo en modo de append para añadir datos al final
    ofstream outFile(fileName, ios::app);

    if (!outFile.is_open())
    {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    // Añade los datos del animal actual al final del archivo
    outFile << to_string(datos.edad) + "," + to_string(datos.genero) + ",";

    // Añade un salto de línea si es el último animal del grupo
    if (ultimoDelGrupo)
    {
        outFile << "-";
    }

    outFile.close();
}

string existeArchivo(const string &nombrebase, const string &ruta, string ext)
{
    if (nombrebase == "ciclo")
    {
        for (int i = 1; i <= 10; i++)
        {
            string nombrePrueba = nombrebase + to_string(i) + ext;

            ifstream prueba(ruta + "\\" + nombrePrueba);

            if (!prueba)
            {
                nombrePrueba = ruta + "\\" + nombrebase + to_string(i - 1) + ext;
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

void Escribircsv(DatosSimulacion &datos)
{
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

void GuardardatosSIMECO(string &usuario, directorios &directorio,DatosSimulacion datosS)
{

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
