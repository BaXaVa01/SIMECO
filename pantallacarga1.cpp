#include <iostream>
#include <windows.h>
#include <cstdlib> // Para la función rand()

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){
    SetConsoleOutputCP(65001); 

    int x = 10, y = 10;

    while (true) {
        // Limpiar la pantalla
        system("cls");
        std::cout << "     ::::::::  ::::::::::: ::::    ::::  ::::::::::  ::::::::   ::::::::"<<std::endl;         
        std::cout << "    :+:    :+:     :+:     +:+:+: :+:+:+ :+:        :+:    :+: :+:    :+:"<<std::endl;                
        std::cout << "    +:+            +:+     +:+ +:+:+ +:+ +:+        +:+        +:+    +:+"<<std::endl;                
        std::cout << "    +#++:++#++     +#+     +#+  +:+  +#+ +#++:++#   +#+        +#+    +:+"<<std::endl;                
        std::cout << "           +#+     +#+     +#+       +#+ +#+        +#+        +#+    +#+"<<std::endl;                
        std::cout << "    #+#    #+#     #+#     #+#       #+# #+#        #+#    #+# #+#    #+#"<<std::endl;              
        std::cout << "     ########  ########### ###       ### ##########  ########   ########"<<std::endl;     
        // Dibujar el patito en la nueva posición
        gotoxy(x, y);
        std::cout << "                      ;                       ";
        gotoxy(x, y + 1);
        std::cout << "         ;               ~~`~~      ;              ";
        gotoxy(x, y + 2);
        std::cout << "        ~`~             ~~`~~`~    `~`             ";
        gotoxy(x, y + 3);
        std::cout << "       ~~`~~           `~~~`~~~~  `~`~`   ,        ";
        gotoxy(x, y + 4);
        std::cout << "      ~~`~~`~           ~`~~~`~   `~`~`\"         ";
        gotoxy(x, y + 5);
        std::cout << "    ~`~~`~~`~~~        ~~~`~~~`~   ~             ";
        gotoxy(x, y + 6);
        std::cout << "     `~~`~~~`~          ~~~|~~~`      '_--...__    ";
        gotoxy(x, y + 7);
        std::cout << "      ~`~|~\\_~\\_   __/¯¯)  |     _- _-  _       _  ";
        gotoxy(x, y + 8);
        std::cout << "         |   |/     .'( )  |              _- _-  _ ";
        gotoxy(x, y + 9);
        std::cout << "         |  / -\\   __`/\\ \\ |_- _- ¯_  -            ";
        gotoxy(x, y + 10);
        std::cout << "      _____/ /--'(^,__ /\\ \\     //\\       _        ";
        gotoxy(x, y + 11);
        std::cout << "    /'       \\      | |  \\ \\    ||\\_- _-  _       ";
        gotoxy(x, y + 12);
        std::cout << "     \\....( /       ;;;___;;;  /||~~`~~            ";
        gotoxy(x, y + 13);
        std::cout << "      ||   \\\\          | |   _/ ||~~~`~~~ -        ";
        gotoxy(x, y + 14);
        std::cout << "      \\\\    \\\\         |=|  /_( ||~~`~~~`      _   ";

        // Agregar efecto de nieve
        for (int i = 0; i < 40; ++i) {  // Adjust the number of snowflakes (e.g., 20)
            gotoxy(rand() % 80, rand() % 25);
            std::cout << "*";
        }

        // Actualizar la posición del patito
        x++;

        // Pausa para simular movimiento
        Sleep(100);

        // Restringir la posición del patito dentro de la pantalla
        if (x > 10) {
            x = 10;
        }    
    }

  return 0;
}
