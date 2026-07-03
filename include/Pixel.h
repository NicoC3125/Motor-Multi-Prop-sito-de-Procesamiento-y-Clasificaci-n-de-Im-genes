#ifndef PIXEL_H
#define PIXEL_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <cstring>

struct Pixel {
    unsigned char r, g, b;
    Pixel(): r(0), g(0), b(0) {}
    Pixel(int rojo, int verde, int azul): r(rojo), g(verde), b(azul) {}
    
    int getGris() const {
        return (r+g+b) / 3; 
    }
    void setGris(int valor)  {
       r=g=b=valor;
    }
    bool esOscuro(int umbral = 128) const {
        return getGris() < umbral;
    }
    bool esClaro(int umbral = 128) const {
        return getGris() >= umbral;
    }
};

#endif