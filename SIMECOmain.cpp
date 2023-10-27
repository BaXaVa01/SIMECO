#include "Login.cpp"


using namespace std;

directorios path;

int main()
{
    
    string usuario;
    MenuLogin(usuario);
    cout<< usuario << endl;

    searchDir(usuario, path);
    cout << endl << path.folder1 << endl;
    cout << path.folder2 << endl;
    cout << path.folder3 << endl;
    cout << path.folderD << endl;
    return 0;
}
