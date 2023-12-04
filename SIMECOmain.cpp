#include "Menues.cpp"


using namespace std;

directorios path;


int main()
{
    FullScreen();
    const int maxRows = 25;
    const int maxColumns = 150;         
    cout << "\033[8;" << maxRows << ";" << maxColumns << "t";
    string usuario;
    MenuLogin(usuario); 
    searchDir(usuario, path);
    system("cls");
    
    return 0;
}
