#include "../include/MotorImagen.h"
#include <iostream>

void MotorImagen::convertirEscalaGrises() {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* pixelActual = matrizPixeles(i, j);
            if (pixelActual != nullptr) {
                int promedio = pixelActual->getGris();
                pixelActual->setGris(promedio);
            }
        }
    }
}

void ordenarArreglo(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

void MotorImagen::aplicarFiltroMediana() {
    int vecinos[9];
    for (int i = 1; i < filas - 1; ++i) {
        for (int j = 1; j < columnas - 1; ++j) {
            int k = 0;
            for (int f = -1; f <= 1; ++f) {
                for (int c = -1; c <= 1; ++c) {
                    Pixel* pVecino = matrizPixeles(i + f, j + c);
                    vecinos[k++] = (pVecino != nullptr) ? pVecino->r : 0;
                }
            }
            ordenarArreglo(vecinos, 9);
            Pixel* pCentro = matrizPixeles(i, j);
            if (pCentro != nullptr) {
                pCentro->setGris(vecinos[4]);
            }
        }
    }
}

void MotorImagen::clasificarZonasDeforestadas() {
    int pixelesBosque = 0;
    int pixelesDeforestados = 0;
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* p = matrizPixeles(i, j);
            if (p != nullptr) {
                if (p->g > p->r && p->g > p->b) {
                    pixelesBosque++;
                } else if (p->r > p->g && p->r > 50) { 
                    pixelesDeforestados++;
                    p->r = 255; p->g = 0; p->b = 0;
                }
            }
        }
    }
    
    float totalImagen = filas * columnas;
    float porcentajeAlerta = (totalImagen > 0) ? ((float)pixelesDeforestados / totalImagen) * 100 : 0;
    
    std::cout << "--- REPORTE DE CLASIFICACIÓN SATELITAL ---" << std::endl;
    std::cout << "Zonas de Bosque Saludable: " << pixelesBosque << " px." << std::endl;
    std::cout << "Zonas con Alerta de Deforestación: " << pixelesDeforestados << " px." << std::endl;
    std::cout << "Porcentaje de daño territorial: " << porcentajeAlerta << "%" << std::endl;
    
    if(porcentajeAlerta > 15.0) {
        std::cout << "[ALERTA CRÍTICA]: Se sugiere intervención en la zona." << std::endl;
    }
}