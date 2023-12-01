#include "Menues.cpp"


using namespace std;

directorios path;

int main()
{
    mainImagenes();
    string usuario;
    
    MenuLogin(usuario); 

    searchDir(usuario, path);
    system("cls");
    barraCarga(5);
    
    return 0;
}

