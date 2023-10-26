#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct directorios {
    string folder1; // = Animales
    string folder2; // = Desastres 
    string folder3; // = ecosistema
    string folderD;
};

string getCurrentPath() {
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    return buffer;
}

void searchDir(string& usuario, directorios& directorio) {
    string folder1 = "\\usuarios\\" + usuario + "\\animales";
    string folder2 = "\\usuarios\\" + usuario + "\\desastres";
    string folder3 = "\\usuarios\\" + usuario + "\\ecosistema";
    string folder4 = "\\usuarios\\" + usuario + "\\partida";    


    string directorioActual = getCurrentPath();

    directorio.folder1 = directorioActual + folder1;
    directorio.folder2 = directorioActual + folder2;
    directorio.folder3 = directorioActual + folder3;
    directorio.folderD = directorioActual + folder4;
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
    string dirDa = directorio + "\\partida";
    result = CreateDirectoryA(dirDa.c_str(), NULL);

    if (result == 0) {
        cerr << "Error creating the folder." << endl;
    }

    //------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------

    // En esta parte se crean los archivos binarios que contendran los datos iniciales
    // se denominaran como Ciclo 0 a cada uno. 
    
    //Varaibles necesarias para el clonado de informacion
    size_t bytesRead;
    char buffer[4096];

    //Declaro las variables para clonar los archivos binarios originales y ponerlos en las carpetas
    FILE *animalFileOriginal, *animalFileClonado;
    
    //Ubico el path donde voy a guardar los archivos binarios principales
    //Declaro como UserO al usuario original, el cual sera el que se clonara para cada usuario
    string directorioUserO = directorioActual + "\\usuarios\\user";
    
    //declaro la ubicacion de la carpeta animales dentro del usuario O
    string dirAo = directorioUserO + "\\animales\\animales.bin";
    
    animalFileOriginal = fopen(dirAo.c_str(), "rb");

    if (animalFileOriginal == NULL)
    {
        printf("Error abriendo archivo animales\n");
    }

    dirA += "\\ciclo0.bin";

    animalFileClonado = fopen(dirA.c_str(), "wb");

    //Este es el algoritmo que copia el archivo original en el fake
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), animalFileOriginal)) > 0)
    {
        fwrite(buffer, 1, bytesRead, animalFileClonado);
    }

    fclose(animalFileOriginal);
    fclose(animalFileClonado);

    //Este es el algoritmo que usare para los otros 2 archivos binarios
 
    FILE *desastreFileOriginal, *desastreFileClonado;
    
    string dirDo = directorioUserO + "\\desastres\\desastres.bin";
    
    desastreFileOriginal = fopen(dirDo.c_str(), "rb");

    if (desastreFileOriginal == NULL)
    {
        printf("Error abriendo archivo Desastresl\n");
    }
    
    dirD += "\\ciclo0.bin";

    desastreFileClonado = fopen(dirD.c_str(), "wb");

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), desastreFileOriginal)) > 0)
    {
        fwrite(buffer, 1, bytesRead, desastreFileClonado);
    }

    fclose(desastreFileOriginal);
    fclose(desastreFileClonado);

    FILE *ecosistemaFileOriginal, *ecosistemaFileClonado;
    
    string dirEo = directorioUserO + "\\ecosistema\\ecosistema.bin";
    
    ecosistemaFileOriginal = fopen(dirEo.c_str(), "rb");

    if (ecosistemaFileOriginal == NULL)
    {
        printf("Error abriendo archivo Ecosisitema\n");
    }

    dirE += "\\ciclo0.bin";

    ecosistemaFileClonado = fopen(dirE.c_str(), "wb");

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), ecosistemaFileOriginal)) > 0)
    {
        fwrite(buffer, 1, bytesRead, ecosistemaFileClonado);
    }

    fclose(ecosistemaFileOriginal);
    fclose(ecosistemaFileClonado);
}


