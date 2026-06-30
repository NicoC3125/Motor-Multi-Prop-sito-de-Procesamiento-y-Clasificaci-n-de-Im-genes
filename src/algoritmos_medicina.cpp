#include "../include/MotorImagen.h"
#include <iostream>

void MotorImagen::binarizarParaAnomalias(int umbralMaximo) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* p = matrizPixeles(i, j);
            if (p != nullptr) {
                int gris = p->getGris();
                if (gris < umbralMaximo) {
                    p->r = 255; p->g = 255; p->b = 255;
                } else {
                    p->r = 0; p->g = 0; p->b = 0;
                }
            }
        }
    }
}

void MotorImagen::clasificarAnomaliaMedica() {
    int pixelesAnomalos = 0;
    int totalPixeles = filas * columnas;
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            Pixel* p = matrizPixeles(i, j);
            if (p != nullptr) {
                if (p->r == 255) {
                    pixelesAnomalos++;
                }
            }
        }
    }
    
    float areaEstimadaMm2 = pixelesAnomalos / 100.0;
    float porcentajeOcupado = (totalPixeles > 0) ? ((float)pixelesAnomalos / totalPixeles) * 100 : 0;
    
    std::cout << "\n=== REPORTE DEL MOTOR DE DIAGNÓSTICO MÉDICO ===" << std::endl;
    std::cout << "Densidad de píxeles sospechosos: " << pixelesAnomalos << " px." << std::endl;
    std::cout << "Área estimada de la masa: " << areaEstimadaMm2 << " mm2." << std::endl;
    
    if (pixelesAnomalos == 0) {
        std::cout << "Resultado: [NEGATIVO] No se detectan masas anómalas." << std::endl;
    } else if (porcentajeOcupado > 0.0 && porcentajeOcupado <= 5.0) {
        std::cout << "Resultado: [PRECAUCIÓN] Masa pequeña detectada. Requiere observación." << std::endl;
    } else {
        std::cout << "Resultado: [ALERTA CRÍTICA] Masa de gran tamaño detectada (" 
                  << porcentajeOcupado << "% del tejido). Se sugiere biopsia prioritaria." << std::endl;
    }
}