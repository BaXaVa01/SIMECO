#include <iostream>
#include <Windows.h>

using namespace std;

struct directorios {
    string folder1; // = Animales
    string folder2; // = Desastres 
    string folder3; // = ecosistema
};

string getCurrentPath() {
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    return buffer;
}

void Searchdir(string usuario, directorios& directorio) {
    string folder1 = "\\usuarios\\" + usuario + "\\animales";
    string folder2 = "\\usuarios\\" + usuario + "\\desastres";
    string folder3 = "\\usuarios\\" + usuario + "\\ecosistema";

    string directorioActual = getCurrentPath();

    directorio.folder1 = directorioActual + folder1;
    directorio.folder2 = directorioActual + folder2;
    directorio.folder3 = directorioActual + folder3;
}

void createFolder(string usuario) {
    string directorioActual = getCurrentPath();
    string directorio = directorioActual + "\\usuarios\\" + usuario;

    BOOL result = CreateDirectoryA(directorio.c_str(), NULL);

    if (result != 0) {
        cout << "Folder created successfully." << endl;
    }
    else {
        cerr << "Error creating the folder." << endl;
    }

    string dirA = directorio + "\\animales";
    result = CreateDirectoryA(dirA.c_str(), NULL);

    if (result == 0) {
        cerr << "Error creating the folder." << endl;
    }

    string dirD = directorio + "\\desastres";
    result = CreateDirectoryA(dirD.c_str(), NULL);

    if (result == 0) {
        cerr << "Error creating the folder." << endl;
    }

    string dirE = directorio + "\\ecosistema";
    result = CreateDirectoryA(dirE.c_str(), NULL);

    if (result == 0) {
        cerr << "Error creating the folder." << endl;
    }
}


