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
void MotorImagen::clasificarAnomaliaMedica() {
    int pixelesAnomalos = 0;
    int totalPixeles = filas * columnas;
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* p = *(matriz + i) + j;
            
            // Si el píxel es blanco (255), es parte de la anomalía detectada
            if (p->r == 255) {
                pixelesAnomalos++;
            }
        }
    }
    
    // Supongamos que por escala, cada 100 píxeles equivalen a 1 mm cuadrado
    float areaEstimadaMm2 = pixelesAnomalos / 100.0;
    float porcentajeOcupado = ((float)pixelesAnomalos / totalPixeles) * 100;
    
    std::cout << "\n=== REPORTE DEL MOTOR DE DIAGNÓSTICO MÉDICO ===" << std::endl;
    std::cout << "Densidad de píxeles sospechosos: " << pixelesAnomalos << " px." << std::endl;
    std::cout << "Área estimada de la masa: " << areaEstimadaMm2 << " mm2." << std::endl;
    
    // Clasificación basada en el tamaño de la anomalía
    if (pixelesAnomalos == 0) {
        std::cout << "Resultado: [NEGATIVO] No se detectan masas anómalas." << std::endl;
    } else if (porcentajeOcupado > 0.0 && porcentajeOcupado <= 5.0) {
        std::cout << "Resultado: [PRECAUCIÓN] Masa pequeña detectada. Requiere observación." << std::endl;
    } else {
        std::cout << "Resultado: [ALERTA CRÍTICA] Masa de gran tamaño detectada (" 
                  << porcentajeOcupado << "% del tejido). Se sugiere biopsia prioritaria." << std::endl;
    }
}