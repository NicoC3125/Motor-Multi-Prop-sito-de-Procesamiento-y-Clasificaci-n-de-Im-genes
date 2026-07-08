#ifndef __PIXEL_H__
#define __PIXEL_H__
#include "util.h"

struct Pixel {
    TU8 r, g, b;

    Pixel() : r(0), g(0), b(0) {}
    Pixel(TU8 rojo, TU8 verde, TU8 azul) : r(rojo), g(verde), b(azul) {}

    TI getGris() const {
        return (r + g + b) / 3; 
    }

    void setGris(TU8 valor) {
       r = g = b = valor;
    }
};

#endif