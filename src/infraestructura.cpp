#include "../include/MotorImagen.h"
#include <fstream>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const MatrizPixeles& matriz) {
    for (int i = 0; i < matriz.filas; ++i) {
        for (int j = 0; j < matriz.columnas; ++j) {
            os << (int)matriz.datos[i][j].r << " " 
               << (int)matriz.datos[i][j].g << " " 
               << (int)matriz.datos[i][j].b << "  ";
        }
        os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, MatrizPixeles& matriz) {
    for (int i = 0; i < matriz.filas; ++i) {
        for (int j = 0; j < matriz.columnas; ++j) {
            int r, g, b;
            if (is >> r >> g >> b) {
                matriz.datos[i][j].r = r;
                matriz.datos[i][j].g = g;
                matriz.datos[i][j].b = b;
            }
        }
    }
    return is;
}

MotorImagen::MotorImagen() : filas(0), columnas(0), maxValor(255), imagenCargada(false) {}

MotorImagen::~MotorImagen() {}

void MotorImagen::liberarMemoria() {
    matrizPixeles.redimensionar(0, 0);
    filas = 0;
    columnas = 0;
    imagenCargada = false;
}

bool MotorImagen::reservarMemoria(int f, int c) {
    filas = f;
    columnas = c;
    return matrizPixeles.redimensionar(filas, columnas);
}

bool MotorImagen::cargarImagenPPM(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) return false;

    std::string formato;
    archivo >> formato;
    if (formato != "P3") return false; 

    int f, c, maxVal;
    archivo >> c >> f >> maxVal; 
    
    if (!reservarMemoria(f, c)) return false;
    maxValor = maxVal;

    archivo >> matrizPixeles;

    imagenCargada = true;
    tipoImagen = "PPM";
    return true;
}

bool MotorImagen::guardarImagenPPM(const std::string& ruta) {
    if (!imagenCargada) return false;
    std::ofstream archivo(ruta);
    if (!archivo.is_open()) return false;

    archivo << "P3\n" << columnas << " " << filas << "\n" << maxValor << "\n";
    archivo << matrizPixeles;
    
    return true;
}