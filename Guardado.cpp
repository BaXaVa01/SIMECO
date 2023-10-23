#include<iostream>
#include<stdio.h>
#include<filesystem>

using namespace std;
namespace fs = std::filesystem;


struct directorios{
    string folder1; // = Animales
    string folder2; // = Desastres 
    string folder3; // = ecosistema
};

fs::path directorio = fs::current_path();

void Searchdir (string usuario, directorios &directorio){
    string folder1 = "\\usuarios\\" + usuario + "\\animales";
    string folder2 = "\\usuarios\\" + usuario + "\\desastres";
    string folder3 = "\\usuarios\\" + usuario + "\\ecosistema";

    fs::path directorioActual = fs::current_path();

    directorio.folder1 = directorioActual.string() + folder1;
    directorio.folder2 = directorioActual.string() + folder2;
    directorio.folder3 = directorioActual.string() + folder3;

}

void createFolder (string usuario){

    fs::path directorio = fs::current_path(); 
    directorio += "\\usuarios\\" + usuario; 
    fs::path pathToFolder = directorio.string();

    try {
        create_directory(pathToFolder);
        cout << "Folder created successfully." << endl;
    } catch (fs::filesystem_error &e) {
        cerr << "Error creating the folder: " << e.what() << endl;
    }

    fs::path dirA = directorio.string() + "\\animales";
    create_directory(dirA);

    fs::path dirD = directorio.string() + "\\desastres";
    create_directory(dirD);

    fs::path dirE = directorio.string() + "\\ecosistema";
    create_directory(dirE);

}

