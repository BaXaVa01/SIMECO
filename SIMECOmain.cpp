#include "Login.cpp"
#include "Excel.cpp"


using namespace std;

int main()
{
    directorios folders;
    string usuario;
    MenuLogin(usuario);
    cout<< usuario << endl;

    searchDir(usuario, folders);
    cout << endl << folders.folder1 << endl;
    cout << folders.folder2 << endl;
    cout << folders.folder3 << endl;
    return 0;
}
