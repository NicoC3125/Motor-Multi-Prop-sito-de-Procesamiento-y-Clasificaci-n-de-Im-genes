#ifndef __CALC_H__
#define __CALC_H__

#include "types.h"
#include <iomanip>
#include <sstream>
#include <iostream>

class Calc {
    using OpFn = T2 (Calc::*)(T2, T2); 
    struct Entrada {
        TS   nombre;
        OpFn fn;// lo mismo que usar directamente T2 (Calc::*fn)(T2, T2);
    };

    Entrada m_tabla[4];
    T1      m_n;

    T2 sumar(T2 a, T2 b);
    T2 restar(T2 a, T2 b);
    T2 multiplicar(T2 a, T2 b);
    T2 dividir(T2 a, T2 b);

public:
    Calc();
    
    TS ejecutar(TS op, T2 a, T2 b);
};

#endif