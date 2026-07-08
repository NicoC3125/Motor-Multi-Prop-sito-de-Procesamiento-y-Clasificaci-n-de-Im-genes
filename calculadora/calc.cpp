#include "calc.h"
#include <sstream>
#include <iomanip>



T2 Calc::sumar(T2 a, T2 b) {
  return a+b;
}
T2 Calc::restar(T2 a, T2 b) {
    return a-b;
}
T2 Calc::multiplicar(T2 a, T2 b) {
    return a*b;
}
T2 Calc::dividir(T2 a, T2 b) {
    return a/b;
}

Calc::Calc() {
    m_n = 4;
    m_tabla[0].nombre = "sumar";
    m_tabla[0].fn = &Calc::sumar;
    m_tabla[1].nombre = "restar";
    m_tabla[1].fn = &Calc::restar;
    m_tabla[2].nombre = "multiplicar"  ;
    m_tabla[2].fn = &Calc::multiplicar;
    m_tabla[3].nombre = "dividir";
    m_tabla[3].fn = &Calc::dividir;
    
}

TS Calc::ejecutar(TS op, T2 a, T2 b) {
    for (T1 i = 0; i < m_n; i++) {
        if (m_tabla[i].nombre == op) {
            if (m_tabla[i].fn == &Calc::dividir && b==0.0)
                return "Error: division por cero";
            OpFn fn = m_tabla[i].fn;
            T2 res = (this->*fn)(a, b);
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(2) << res;
            return oss.str();   
        }
    }
    return "ERROR operación desconocida";
}
