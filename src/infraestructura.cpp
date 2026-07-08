#include "MotorImagen.h"

MotorImagen::MotorImagen() : maxValor(255), imagenCargada(false) {}

MotorImagen::MotorImagen(const MotorImagen& otro) 
    : nombreArchivo(otro.nombreArchivo), maxValor(otro.maxValor), 
      matrizPixeles(otro.matrizPixeles), imagenCargada(otro.imagenCargada) {}

MotorImagen::MotorImagen(MotorImagen&& otro) noexcept 
    : nombreArchivo(move(otro.nombreArchivo)), 
      maxValor(exchange(otro.maxValor, 0)), 
      matrizPixeles(move(otro.matrizPixeles)), 
      imagenCargada(exchange(otro.imagenCargada, false)) {}

MotorImagen& MotorImagen::operator=(const MotorImagen& otro) {
    if (this != &otro) {
        nombreArchivo = otro.nombreArchivo;
        maxValor = otro.maxValor;
        matrizPixeles = otro.matrizPixeles;
        imagenCargada = otro.imagenCargada;
    }
    return *this;
}

MotorImagen::~MotorImagen() {}

void MotorImagen::liberarMemoria() {
    matrizPixeles.CreateMatrix(0, 0);
    imagenCargada = false;
}

TB MotorImagen::reservarMemoria(TI f, TI c) {
    matrizPixeles.CreateMatrix(f, c);
    return true;
}

TI MotorImagen::getFilas() const { return matrizPixeles.GetRows(); }
TI MotorImagen::getColumnas() const { return matrizPixeles.GetCols(); }

TB MotorImagen::cargarImagenPPM(const TS& ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return false;

    TS formato;
    archivo >> formato;
    if (formato != "P3" && formato != "Pi3") return false; 

    TI f, c;
    archivo >> c >> f >> maxValor; 
    
    if (!reservarMemoria(f, c)) return false;

    for (TI i = 0; i < getFilas(); ++i) {
        for (TI j = 0; j < getColumnas(); ++j) {
            TI r, g, b;
            if (archivo >> r >> g >> b) {
                matrizPixeles(i, j) = Pixel(static_cast<TU8>(r), static_cast<TU8>(g), static_cast<TU8>(b));
            }
        }
    }

    imagenCargada = true;
    return true;
}

TB MotorImagen::guardarImagenPPM(const TS& ruta) {
    if (!imagenCargada) return false;
    ofstream archivo(ruta);
    if (!archivo.is_open()) return false;

    archivo << "P3\n" << getColumnas() << " " << getFilas() << "\n" << maxValor << "\n";
    
    for (TI i = 0; i < getFilas(); ++i) {
        for (TI j = 0; j < getColumnas(); ++j) {
            const Pixel& p = matrizPixeles(i, j);
            archivo << static_cast<TI>(p.r) << " " 
                    << static_cast<TI>(p.g) << " " 
                    << static_cast<TI>(p.b) << "  ";
        }
        archivo << "\n";
    }
    
    return true;
}