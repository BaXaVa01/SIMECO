#include "Login.cpp"
#include "SIMECOFV.cpp"
#include "barraDeCarga.cpp"

using namespace std;

directorios path;

int main()
{
    
    setlocale(LC_ALL, "spanish");
    string usuario;

    MenuLogin(usuario); 
    

    searchDir(usuario, path);
    system("cls");
    barraCarga(5);

    // Fvmain(ciclo, path);
    Fvmain();

    
    return 0;
}
