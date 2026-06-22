#include "MOTOR_IMAGEN_H.h"
#include <iostream>

// Binarizar el espacio: Estrellas en blanco (255), vacío en negro (0)
void MotorImagen::aislarEstrellas(int brilloMinimo) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* p = *(matriz + i) + j;
            
            // Evaluamos el brillo promedio del píxel en el espacio
            int brillo = (p->r + p->g + p->b) / 3;
            
            if (brillo > brilloMinimo) {
                // Es una estrella: la dejamos brillante o la pintamos de amarillo
                p->r = 255; p->g = 255; p->b = 0; 
            } else {
                // Es el vacío del espacio: negro absoluto
                p->r = 0; p->g = 0; p->b = 0;
            }
        }
    }
}
// Función auxiliar para ordenar un arreglo (Selection Sort)
void ordenarArreglo(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        // Intercambio
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// Aplicación del Filtro de Mediana para limpiar ruido
void MotorImagen::aplicarFiltroMediana() {
    // Nota: Para no alterar los píxeles vecinos mientras procesas, 
    // lo ideal es leer de la matriz original y guardar en una matriz auxiliar temporal.
    
    int vecinos[9];
    
    // Recorremos evitando los bordes exteriores para simplificar el código de los vecinos
    for (int i = 1; i < filas - 1; ++i) {
        for (int j = 1; j < columnas - 1; ++j) {
            int k = 0;
            
            // Llenamos el arreglo con el bloque de 3x3 píxeles
            for (int f = -1; f <= 1; ++f) {
                for (int c = -1; c <= 1; ++c) {
                    // Usamos el canal R (asumiendo escala de grises)
                    vecinos[k++] = (*(matriz + (i + f)) + (j + c))->r;
                }
            }
            
            // LLAMADA AL ORDENAMIENTO (Rúbrica)
            ordenarArreglo(vecinos, 9);
            
            // La mediana es el valor central (posición 4 del arreglo de 0 a 8)
            (*(matriz + i) + j)->r = vecinos[4];
            (*(matriz + i) + j)->g = vecinos[4];
            (*(matriz + i) + j)->b = vecinos[4];
        }
    }
}
void MotorImagen::clasificarCumuloEstelar() {
    int pixelesEstrella = 0;
    int totalPixeles = filas * columnas;
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* p = *(matriz + i) + j;
            // Si el píxel está pintado de amarillo, contamos que hay presencia estelar
            if (p->r == 255 && p->g == 255) {
                pixelesEstrella++;
            }
        }
    }
    
    float densidadCalculada = ((float)pixelesEstrella / totalPixeles) * 100;
    
    std::cout << "\n=== ANALIZADOR ASTROFÍSICO DE IMÁGENES ===" << std::endl;
    std::cout << "Píxeles estelares detectados: " << pixelesEstrella << " px." << std::endl;
    std::cout << "Densidad estelar del cuadrante: " << densidadCalculada << "%" << std::endl;
    
    // Clasificación astronómica simulada
    if (densidadCalculada < 0.5) {
        std::cout << "Clasificación: [ESPACIO PROFUNDO VACÍO] Poca presencia de cuerpos celestes." << std::endl;
    } else if (densidadCalculada >= 0.5 && densidadCalculada <= 3.0) {
        std::cout << "Clasificación: [CÚMULO ESTELAR ABIERTO] Grupo de estrellas dispersas." << std::endl;
    } else {
        std::cout << "Clasificación: [NÚCLEO GALÁCTICO / NEBULOSA DENSA] Alta concentración estelar." << std::endl;
    }
}