#include "MOTOR_IMAGEN_H.h"
#include <iostream>

void MotorImagen::aislarEstrellas(int brilloMinimo) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* p = *(matrizPixeles + i) + j;
            int brillo = p->getGris();
            
            if (brillo > brilloMinimo) {
                p->r = 255; p->g = 255; p->b = 0; // Amarillo para estrellas
            } else {
                p->r = 0; p->g = 0; p->b = 0;
            }
        }
    }
}

void MotorImagen::clasificarCumuloEstelar() {
    int pixelesEstrella = 0;
    int totalPixeles = filas * columnas;
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* p = *(matrizPixeles + i) + j;
            if (p->r == 255 && p->g == 255) {
                pixelesEstrella++;
            }
        }
    }
    
    float densidadCalculada = (totalPixeles > 0) ? ((float)pixelesEstrella / totalPixeles) * 100 : 0;
    
    std::cout << "\n=== ANALIZADOR ASTROFÍSICO DE IMÁGENES ===" << std::endl;
    std::cout << "Píxeles estelares detectados: " << pixelesEstrella << " px." << std::endl;
    std::cout << "Densidad estelar del cuadrante: " << densidadCalculada << "%" << std::endl;
    
    if (densidadCalculada < 0.5) {
        std::cout << "Clasificación: [ESPACIO PROFUNDO VACÍO] Poca presencia de cuerpos celestes." << std::endl;
    } else if (densidadCalculada >= 0.5 && densidadCalculada <= 3.0) {
        std::cout << "Clasificación: [CÚMULO ESTELAR ABIERTO] Grupo de estrellas dispersas." << std::endl;
    } else {
        std::cout << "Clasificación: [NÚCLEO GALÁCTICO / NEBULOSA DENSA] Alta concentración estelar." << std::endl;
    }
}