#ifndef MOTOR_IMAGEN_H
#define MOTOR_IMAGEN_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <cstring>
#include "Pixel.h"
#include "Matriz_pixeles.h"

class MotorImagen {
    private:
    std::string nombreArchivo; 
    int filas; 
    int columnas; 
    int maxValor; 
    MatrizPixeles matrizPixeles; 
    bool imagenCargada;
    std::string tipoImagen; 

    public:
    MotorImagen();
    ~MotorImagen();
    void liberarMemoria();
    bool reservarMemoria(int filas, int columnas);
    void copiarMatriz(const MotorImagen& origen);

    bool cargarImagen(const std::string& ruta);
    bool guardarImagen(const std::string& ruta);
    bool cargarImagenPPM(const std::string& ruta); 
    bool guardarImagenPPM(const std::string& ruta);

    std::string getNombreArchivo() const{return nombreArchivo; }
    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
    int getMaxValor() const { return maxValor; }
    Pixel** getMatriz() const { return matrizPixeles.getPunterosRaiz(); }
    bool isImagenCargada() const { return imagenCargada; }
    std::string getTipoImagen() const { return tipoImagen; }

    Pixel getPixel(int fila, int col) const;
    void setPixel(int fila, int col, const Pixel& pixel);
    void setPixel(int fila, int col, int r, int g, int b);

    void mostrarEstadisticas() const;
    void generarHistograma() const;

    bool validarCoordenadas(int fila, int col) const;
    void estableccerTipoImagen(const std::string& tipo);

    void aplicarFiltroMediana();     
    void convertirEscalaGrises();
    void clasificarZonasDeforestadas();

    void aislarEstrellas(int brilloMinimo);
    void clasificarCumuloEstelar();

    void binarizarParaAnomalias(int umbralMaximo);
    void clasificarAnomaliaMedica();
};
#endif