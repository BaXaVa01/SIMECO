#include<stdio.h>
#include<windows.h>
#include<iostream>
#include<stdlib.h>

using namespace std;

int main(){

    SMALL_RECT rect; 
    COORD coord;

    coord.X = 80; // Definir ancho
    coord.Y = 25; // Definir alto

    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = coord.Y-1; // Definir coordenadas Y
    rect.Right = coord.X-1; // Definir coordenadas X

    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE); // Obtener el handle de la consola
    

    int segundos = 5;
    for(int i = 0; i < 21; i++){
        cout << "\n";
    }
    
    cout << "\t\t\t\t\t   Cargando... \n";

    for(int i = 0; i <= 79; i++){
        cout <<"_";
        
    }
    cout << "\n";
    for(int i = 0; i<=79; i++){
        cout << char(219);
        Sleep(segundos *1000/ 80);
    }
    cout <<"\n 100%";
    return 0;
}