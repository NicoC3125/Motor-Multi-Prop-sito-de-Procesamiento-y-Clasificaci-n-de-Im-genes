#ifndef MATRIZ_PIXELES_H
#define MATRIZ_PIXELES_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <cstring>
#include "Pixel.h"

class MatrizPixeles{
    private:
    int filas;
    int columnas;
    Pixel** datos;
    void liberar(){
        if(datos != nullptr) {
            for(int i = 0; i<filas; ++i){
                delete[] datos[i];
            }
            delete[] datos;
            datos = nullptr;
        }
        filas = 0;
        columnas = 0;
    }
    public:
     MatrizPixeles() : filas(0), columnas(0), datos(nullptr){} 
     ~MatrizPixeles() { liberar(); }
     bool redimensionar(int f, int c){
        liberar();
        if(f <= 0 || c<= 0) return false;
        filas = f;
        columnas = c;
        datos = new Pixel*[filas];
        for (int i = 0; i < filas; ++i){
            datos[i] = new Pixel[columnas];
        }
        return true;
     }
     Pixel* operator()(int i, int j){
        if (i>=0 && i<filas && j>=0 && j<columnas){
            return &datos[i][j];
        }
        return nullptr;
     }
     const Pixel* operator()(int i, int j) const{
        if (i >= 0 && i<filas && j>= 0 && j < columnas){
            return  &datos[i][j];
        }
        return nullptr;
     }
     Pixel** getPunterosRaiz() const {return datos;}
     int getFilas() const { return filas; }
     int getColumnas() const { return columnas; }

     friend std::ostream& operator<<(std::ostream& os, const MatrizPixeles& matriz);
     friend std::istream& operator>>(std::istream& is, MatrizPixeles& matriz);
};
#endif