#include "calc.h"
using namespace std;

int main() {
    Calc c;

    TS ops[6] = {"sumar", "restar", "multiplicar", "dividir", "dividir", "potencia"};
    T2 as[6]  = {14.582, 12.005, 5.231, 7.345, 5.781, 2.123};
    T2 bs[6]  = {3.419, 8.743, 2.894, 2.500, 0.000, 3.456};

    cout << "Calculadora:" << endl;
    cout << fixed << setprecision(2);
    for (T1 i = 0; i < 6; ++i)
        cout << ops[i] << "(" << as[i] << ", " << bs[i] << ") = "
             << c.ejecutar(ops[i], as[i], bs[i]) << endl;
    return 0;
}