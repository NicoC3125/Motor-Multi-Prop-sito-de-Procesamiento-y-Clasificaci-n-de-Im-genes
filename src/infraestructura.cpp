#include "../include/MotorImagen.h"
#include <fstream>
#include <iostream>

MotorImagen::MotorImagen() : filas(0), columnas(0), maxValor(255), matrizPixeles(nullptr), imagenCargada(false) {}

MotorImagen::~MotorImagen() {
    if (matrizPixeles != nullptr) {
        for (int i = 0; i < filas; ++i) {
            delete[] matrizPixeles[i]; 
        }
        delete[] matrizPixeles; 
    }
}

bool MotorImagen::reservarMemoria(int i, int j) {
    filas = i;
    columnas = j;
    matrizPixeles = new Pixel*[filas];
    for (int i = 0; i < filas; ++i) {
        matrizPixeles[i] = new Pixel[columnas];
    }
    return true;
}

bool MotorImagen::cargarImagenPPM(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) return false;

    std::string formato;
    archivo >> formato;
    if (formato != "P3") return false; 

    int f, c, maxVal;
    archivo >> c >> f >> maxVal; 
    
    reservarMemoria(f, c);
    maxValor = maxVal;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            int r, g, b;
            archivo >> r >> g >> b;
            matrizPixeles[i][j] = Pixel(r, g, b);
        }
    }
    imagenCargada = true;
    tipoImagen = "PPM";
    return true;
}

bool MotorImagen::guardarImagenPPM(const std::string& ruta) {
    if (!imagenCargada) return false;
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) return false;

    archivo << "P3\n" << columnas << " " << filas << "\n" << maxValor << "\n";
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* p = *(matrizPixeles + i) + j;
            archivo << (int)p->r << " " << (int)p->g << " " << (int)p->b << "  ";
        }
        archivo << "\n";
    }
    return true;
}