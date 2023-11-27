#include "Menues.cpp"


using namespace std;

directorios path;

int main()
{
    string usuario;

    MenuLogin(usuario); 

    searchDir(usuario, path);
    system("cls");
    barraCarga(5);
    Fvmain(usuario, path);
    return 0;
}
