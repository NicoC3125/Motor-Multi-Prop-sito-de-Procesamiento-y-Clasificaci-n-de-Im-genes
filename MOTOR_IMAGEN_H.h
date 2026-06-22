#ifndef MOTOR_IMAGEN_H
#define MOTOR_IMAGEN_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <cstring>
//Estructura Pixel con soporte RGB(para imagenes satelitales y médicas)
struct Pixel {
    unsigned char r, g, b;
    //constructores
    Pixel(): r(0), g(0), b(0) {}
    Pixel(int rojo, int cerde, int azul): r(rojo), g(cerde), b(azul) {}
    //Métodos auxiliares
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
//Clase principal del Motor de Imágenes
class MotorImagen {
    private:
    // Atributos Privados
    std::string nombreArchivo; // Nombre del archivo cargado
    int filas; //"alto"
    int columnas; //"ancho"
    int maxValor; //valor máximo de intensidad(255 para RGB)
    Pixel** matrizPixeles;
    bool imagenCargada;
    std::string tipoImagen; //"medica" o "satelital" o "astronomica"

    public:
    //Constructor y destructor
    MotorImagen();
    ~MotorImagen();
    //Gestión de memoria dinámica
    void liberarMemoria();
    bool reservarMemoria(int filas, int columnas);
    void copiarMatriz(const MotorImagen& origen);
// carga y guardado de archivos
bool cargarImagen(const std::string& ruta);
bool guardarImagen(const std::string& ruta);
bool cargarImagenPPM(const std::string& ruta); //Imagenes a color
bool guardarImagenPPM(const std::string& ruta);
//Métodos de acceso(Getters)
std::string getNombreArchivo() const{return nombreArchivo; }
int getFilas() const { return filas; }
int getColumnas() const { return columnas; }
int getMaxValor() const { return maxValor; }
Pixel** getMatriz() const { return matrizPixeles; }
bool isImagenCargada() const { return imagenCargada; }
std::string getTipoImagen() const { return tipoImagen; }
//Métodos de acceso a Píxeles
Pixel getPixel(int fila, int col) const;
void setPixel(int fila, int col, const Pixel& pixel);
void setPixel(int fila, int col, int r, int g, int b);
//Estadísticas
void mostrarEstadisticas() const;
void generarHistograma() const;
//Métodos de utilidad
bool validarCoordenadas(int fila, int col) const;
void estableccerTipoImagen(const std::string& tipo);
};
#endif
