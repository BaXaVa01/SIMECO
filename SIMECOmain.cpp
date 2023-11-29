#include "Menues.cpp"


using namespace std;

directorios path;

int main()
{
    string usuario;
    FullScreen();
    mainBarra1();
    MenuLogin(usuario); 

    searchDir(usuario, path);
    system("cls");
    
    return 0;
}

