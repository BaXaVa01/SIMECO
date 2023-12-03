#include <iostream>
#include <windows.h>

using namespace std;

COORD GetConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return {static_cast<SHORT>(width), static_cast<SHORT>(height)};
}

void SetConsoleSize(int width, int height) {
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordMax = GetLargestConsoleWindowSize(hConsole);

    // Asegurarse de que las dimensiones deseadas no excedan el tamaño máximo posible
    if (width > coordMax.X) width = coordMax.X;
    if (height > coordMax.Y) height = coordMax.Y;

    COORD newSize;
    newSize.X = width;
    newSize.Y = height;

    // Establecer el tamaño del buffer de la pantalla
    SetConsoleScreenBufferSize(hConsole, newSize);

    SMALL_RECT rectWindow = {0, 0, width - 1, height - 1};

    // Cambiar el tamaño de la ventana de la consola
    SetConsoleWindowInfo(hConsole, TRUE, &rectWindow);
}

int main() {
    // Establecer el tamaño de la consola
    SetConsoleSize(150 , 70); // Por ejemplo, 80 caracteres de ancho por 40 de alto

    // Obtener y usar el tamaño de la consola
    COORD size = GetConsoleSize();
    std::cout << "Ancho de la consola: " << size.X << ", Alto de la consola: " << size.Y << std::endl;

    // Resto de tu código...

    return 0;
}