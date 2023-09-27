#include "dependencias\pbPlots.cpp"
#include "dependencias\supportLib.cpp"
#include <cstdlib>
using namespace std;


int main() {
    bool success;
    StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    // Datos de crecimiento poblacional
    double time[] = {0, 1, 2, 3, 4, 5, 6};  // Tiempo
    double population[] = {100, 150, 50, 250, 300, 100, 500};  // Población

    // Convertir los arreglos de datos a vectores
    vector<double> xs(time, time + sizeof(time) / sizeof(double));
    vector<double> ys(population, population + sizeof(population) / sizeof(double));

    // Dibujar el gráfico de dispersión
    success = DrawScatterPlot(imageReference, 600, 400, &xs, &ys, errorMessage);

    if (success) {
        vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "crecimiento_poblacional.png");
        DeleteImage(imageReference->image);
		// Abrir el archivo de imagen en Windows
        system("start crecimiento_poblacional.png");
    } else {
        cerr << "Error: ";
        for (int i = 0; i < errorMessage->string->size(); i++) {
            wcerr << errorMessage->string->at(i);
        }
        cerr << endl;
    }

    FreeAllocations();

	

    return success ? 0 : 1;
}