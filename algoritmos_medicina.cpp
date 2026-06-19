#include "MotorImagen.h"
#include <iostream>

// Binarizar para resaltar áreas sospechosas (oscuras)
void MotorImagen::binarizarParaAnomalias(int umbralMaximo) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Aritmética de punteros para el píxel actual
            Pixel* p = *(matriz + i) + j;
            
            // Calculamos su nivel de gris actual (promedio)
            int gris = (p->r + p->g + p->b) / 3;
            
            // Si el píxel es más oscuro que el umbral, podría ser la anomalía (lo pintamos de blanco)
            if (gris < umbralMaximo) {
                p->r = 255; p->g = 255; p->b = 255;
            } else {
                // Si es tejido normal o hueso, lo mandamos a negro absoluto
                p->r = 0; p->g = 0; p->b = 0;
            }
        }
    }
}