#ifndef __MOTOR_IMAGEN_H__
#define __MOTOR_IMAGEN_H__
#include "util.h"
#include "Pixel.h"
#include "CMatrix.h"

class MotorImagen {
    TS nombreArchivo; 
    TI maxValor; 
    CMatrix<Pixel> matrizPixeles; 
    TB imagenCargada;

public:
    MotorImagen();
    MotorImagen(const MotorImagen& otro);
    MotorImagen(MotorImagen&& otro) noexcept;
    MotorImagen& operator=(const MotorImagen& otro);
    ~MotorImagen();

    void liberarMemoria();
    TB reservarMemoria(TI f, TI c);

    TB cargarImagenPPM(const TS& ruta); 
    TB guardarImagenPPM(const TS& ruta);

    TI getFilas() const;
    TI getColumnas() const;

    void aplicarFiltroMediana();     
    void clasificarZonasDeforestadas();
    void aislarEstrellas(TI brilloMinimo);
    void clasificarCumuloEstelar();
    void binarizarParaAnomalias(TI umbralMaximo);
    void clasificarAnomaliaMedica();
};

#endif