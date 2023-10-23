#include<iostream>
#include<stdio.h>
#include<filesystem>

using namespace std;
namespace fs = std::filesystem;
using namespace fs;

struct directorios{
    string folder1; // = Animales
    string folder2; // = Desastres 
    string folder3; // = ecosistema
};

path directorio = current_path();

void Searchdir (string usuario, directorios &directorio){
    string folder1 = "\\usuarios\\" + usuario + "\\animales";
    string folder2 = "\\usuarios\\" + usuario + "\\desastres";
    string folder3 = "\\usuarios\\" + usuario + "\\ecosistema";

    path directorioActual = current_path();

    directorio.folder1 = directorioActual.string() + folder1;
    directorio.folder2 = directorioActual.string() + folder2;
    directorio.folder3 = directorioActual.string() + folder3;

}

void createFolder (string usuario){

    path directorio = current_path(); 
    directorio += "\\usuarios\\" + usuario; 
    path pathToFolder = directorio.string();

    try {
        create_directory(pathToFolder);
        cout << "Folder created successfully." << endl;
    } catch (filesystem_error &e) {
        cerr << "Error creating the folder: " << e.what() << endl;
    }

    path dirA = directorio.string() + "\\animales";
    create_directory(dirA);

    path dirD = directorio.string() + "\\desastres";
    create_directory(dirD);

    path dirE = directorio.string() + "\\ecosistema";
    create_directory(dirE);

}



// int main()
// {
//     string usuario = "baxava";
//     directorios directorio;
//     Searchdir(usuario, directorio);
//     cout << directorio.folder1 << endl;
//     cout << directorio.folder2 << endl;
//     cout << directorio.folder3 << endl;
    
//     createFolder("JuanElMecanico");

//     return 0;
// }