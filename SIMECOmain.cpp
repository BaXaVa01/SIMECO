#include "Menues.cpp"


using namespace std;

directorios path;

int main()
{
    FullScreen();
    string usuario;
    
    MenuLogin(usuario); 
    searchDir(usuario, path);
    system("cls");
    barraCarga(5);
    
    return 0;
}

