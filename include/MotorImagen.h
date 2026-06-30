#ifndef MOTOR_IMAGEN_H
#define MOTOR_IMAGEN_H
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