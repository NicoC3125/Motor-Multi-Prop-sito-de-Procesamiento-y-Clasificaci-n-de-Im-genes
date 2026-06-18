#include "MotorImagen.h"
#include <iostream>

// Filtro básico para convertir a Escala de Grises (Aritmética de punteros)
void MotorImagen::convertirEscalaGrises() {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Acceso mediante aritmética de punteros
            Pixel* pixelActual = *(matriz + i) + j;
            
            // Fórmula estándar de luminosidad
            int promedio = (pixelActual->r + pixelActual->g + pixelActual->b) / 3;
            
            pixelActual->r = promedio;
            pixelActual->g = promedio;
            pixelActual->b = promedio;
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