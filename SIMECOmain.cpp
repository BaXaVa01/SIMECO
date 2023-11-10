#include "Login.cpp"


using namespace std;

directorios path;

int main()
{
    setlocale(LC_ALL, "spanish");
    string usuario;

    MenuLogin(usuario); 
    

    searchDir(usuario, path);

    postLogin(usuario, path.folder1);

    
    return 0;
}
