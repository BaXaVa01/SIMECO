#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>


using namespace std;


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void imprimirPatito(int x, int y) {
    gotoxy(x, y);
    std::cout << "                                            ;                       ";
    gotoxy(x, y + 1);                 
    std::cout << "                          ;               ~~`~~      ;              ";
    gotoxy(x, y + 2);                 
    std::cout << "                         ~`~             ~~`~~`~    `~`             ";
    gotoxy(x, y + 3);                 
    std::cout << "                        ~~`~~           `~~~`~~~~  `~`~`   ,        ";
    gotoxy(x, y + 4);                 
    std::cout << "                       ~~`~~`~           ~`~~~`~   `~`~`\"         ";
    gotoxy(x, y + 5);                 
    std::cout << "                     ~`~~`~~`~~~        ~~~`~~~`~   ~             ";
    gotoxy(x, y + 6);                 
    std::cout << "                      `~~`~~~`~          ~~~|~~~`      '_--...__    ";
    gotoxy(x, y + 7);                 
    std::cout << "                       ~`~|~\\_~\\_   __/¯¯)  |     _- _-  _       _  ";
    gotoxy(x, y + 8);                 
    std::cout << "                          |   |/     .'( )  |              _- _-  _ ";
    gotoxy(x, y + 9);                 
    std::cout << "                          |  / -\\   __`/\\ \\ |_- _- ¯_  -            ";
    gotoxy(x, y + 10);                 
    std::cout << "                       _____/ /--'(^,__ /\\ \\     //\\       _        ";
    gotoxy(x, y + 11);                 
    std::cout << "                     /'       \\      | |  \\ \\    ||\\_- _-  _       ";
    gotoxy(x, y + 12);                 
    std::cout << "                      \\....( /       ;;;___;;;  /||~~`~~            ";
    gotoxy(x, y + 13);                 
    std::cout << "                       ||   \\\\          | |   _/ ||~~~`~~~ -        ";
    gotoxy(x, y + 14);                 
    std::cout << "                       \\\\    \\\\         |=|  /_( ||~~`~~~`      _   ";
}                 
                 
void imprimirTexto(int x, int y) {
    gotoxy(x, y);
    std::cout << "     ::::::::  ::::::::::: ::::    ::::  ::::::::::  ::::::::   ::::::::" << std::endl;
    gotoxy(x, y + 1);
    std::cout << "    :+:    :+:     :+:     +:+:+: :+:+:+ :+:        :+:    :+: :+:    :+:" << std::endl;
    gotoxy(x, y + 2);
    std::cout << "    +:+            +:+     +:+ +:+:+ +:+ +:+        +:+        +:+    +:+" << std::endl;
    gotoxy(x, y + 3);
    std::cout << "    +#++:++#++     +#+     +#+  +:+  +#+ +#++:++#   +#+        +#+    +:+" << std::endl;
    gotoxy(x, y + 4);
    std::cout << "           +#+     +#+     +#+       +#+ +#+        +#+        +#+    +#+" << std::endl;
    gotoxy(x, y + 5);
    std::cout << "    #+#    #+#     #+#     #+#       #+# #+#        #+#    #+# #+#    #+#" << std::endl;
    gotoxy(x, y + 6);
    std::cout << "     ########  ########### ###       ### ##########  ########   ########" << std::endl;
}

void imprimirBarraDeCarga(int x, int y, int longitud, int progreso) {
    gotoxy(x, y);
    cout << "[";
    int barrasCompletadas = static_cast<int>(static_cast<float>(progreso) / 100 * longitud);
    for (int i = 0; i < longitud; ++i) {
        if (i < barrasCompletadas+10) {
            cout << "=";
        } else {
            cout << " ";
        }
    }
    cout << "]";
}




int mainBarra1() {
    SetConsoleOutputCP(65001);

    // Calcular la posición inicial para centrar el bloque de texto
    int anchoTexto = 40; // Ajusta según el ancho de tu bloque de texto
    int alturaTexto = 7; // Ajusta según la altura de tu bloque de texto
    int xTexto = (80 - anchoTexto) / 2; // Centrar horizontalmente
     int yTexto = (25 - alturaTexto) / 2; // Centrar verticalmente

    // Calcular la posición inicial para centrar el patito
    int anchoPatito = 40; // Ajusta según el ancho de tu patito
    int alturaPatito = 15; // Ajusta según la altura de tu patito
    int xPatito = (80 - anchoTexto) / 2; // Centrar horizontalmente
    int yPatito = yTexto + alturaTexto + 1; // 
    int progresoBarra = 0;
    int longitudBarra = 75;

    while (true) {
        system("cls");

        // Imprimir el patito en la nueva posición centrada
        imprimirPatito(xPatito, yPatito);

        // Imprimir el bloque de texto en la nueva posición centrada
        imprimirTexto(xTexto, yTexto);

        int anchoMaximo = (max(anchoPatito, anchoTexto)) * 2;
        int alturaTotal = alturaPatito + alturaTexto + 2;

        // Agregar efecto de nieve para el conjunto
        for (int i = 0; i < 40; ++i) {
            int snowflakeX = xTexto + rand() % (anchoMaximo - 6);
            int snowflakeY = yTexto + rand() % alturaTotal;
            gotoxy(snowflakeX, snowflakeY);
            cout << "*";
        }
        
        imprimirBarraDeCarga(xPatito, yPatito + alturaPatito + 2, longitudBarra, progresoBarra);

        
        progresoBarra += 2;
        if(progresoBarra < 100){
            cout<<"\n                                                           "<<progresoBarra<<"%";

        }else{
            cout<<"\n                                                           100%";
        }

        if (progresoBarra > 100) {
            progresoBarra = 0;
            
            return false;
        }

        // Actualizar la posición del patito
        xPatito++;

        // Pausa para simular movimiento
        this_thread::sleep_for(chrono::milliseconds(100));

        // Restringir la posición del patito dentro de la pantalla
        if (xPatito > (80 - anchoPatito) / 2) {
            xPatito = (80 - anchoPatito) / 2;
        }
    }

    system("cls");
    return 0;
}