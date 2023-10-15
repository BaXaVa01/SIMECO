#include <iostream>
#include <fstream>
#include <string>

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

void crearCSV(const DatosSimulacion &datos)
{
    ofstream archivo("datos.csv");
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

void guardarBinario(DatosSimulacion datos)
{

    ofstream archivo("datos.bin", ios::binary);

    archivo.write((char *)&datos, sizeof(datos));

    archivo.close();
}

void cargarDesdeBinario(DatosSimulacion &datos)
{

    ifstream archivo("datos.bin", ios::binary);

    archivo.read((char *)&datos, sizeof(datos));

    archivo.close();
}

bool verificadorCSV()
{
    ifstream archivo("datos.csv");
    return archivo.good();
}

int main()
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

    if (!verificadorCSV())
    {
        crearCSV(datos);
        cout << "Creando archivo CSV" << endl;
    }
    else
    {
        leerCSV(datos);
        cout << "Leyendo CSV" << endl;
    }

    guardarBinario(datos);
    cout << "Guardando a binario" << endl;

    DatosSimulacion datosCargados;
    cargarDesdeBinario(datosCargados);
    cout << "Cargando desde binario" << endl;

    cout << "Datos cargados(inicio y fin):\n" << datosCargados.poblacionTotalEspecie1<<"\n"<<datosCargados.huracanes<< endl;

    return 0;
}