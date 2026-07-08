#include "MotorImagen.h"
#include <cstdio>
#include <fstream>

void MotorImagen::binarizarParaAnomalias(TI umbralMaximo) {
    for (TI i = 0; i < getFilas(); ++i) {
        for (TI j = 0; j < getColumnas(); ++j) {
            Pixel& p = matrizPixeles(i, j);
            if (p.getGris() < umbralMaximo) {
                p.r = 255; p.g = 255; p.b = 255;
            } else {
                p.r = 0; p.g = 0; p.b = 0;
            }
        }
    }
}

void MotorImagen::clasificarAnomaliaMedica() {
    TI pixelesAnomalos = 0;
    TI totalPixeles = getFilas() * getColumnas();
    
    for (TI i = 0; i < getFilas(); ++i) {
        for (TI j = 0; j < getColumnas(); ++j) {
            if (matrizPixeles(i, j).r == 255) {
                pixelesAnomalos++;
            }
        }
    }
    
    TD areaEstimadaMm2 = pixelesAnomalos / 100.0;
    TD porcentajeOcupado = (totalPixeles > 0) ? ((TD)pixelesAnomalos / totalPixeles) * 100.0 : 0.0;
    
    printf("\n=== REPORTE DEL MOTOR DE DIAGNOSTICO MEDICO ===\n");
    printf("Densidad de pixeles sospechosos: %d px.\n", pixelesAnomalos);
    printf("Area estimada de la masa: %.2f mm2.\n", areaEstimadaMm2);
    
    if (pixelesAnomalos == 0) {
        printf("Resultado: [NEGATIVO] No se detectan masas anomalas.\n");
    } else if (porcentajeOcupado > 0.0 && porcentajeOcupado <= 5.0) {
        printf("Resultado: [PRECAUCION] Masa pequena detectada. Requiere observacion.\n");
    } else {
        printf("Resultado: [ALERTA CRITICA] Masa de gran tamano detectada (%.2f%% del tejido). Se sugiere biopsia prioritaria.\n", porcentajeOcupado);
    }

    ofstream reporte("reporte_medico.txt", ios::app);
    if (reporte.is_open()) {
        reporte << "\n=== REPORTE DEL MOTOR DE DIAGNOSTICO MEDICO ===\n"
                << "Densidad de pixeles sospechosos: " << pixelesAnomalos << " px.\n"
                << "Area estimada de la masa: " << areaEstimadaMm2 << " mm2.\n";
        if (pixelesAnomalos == 0) {
            reporte << "Resultado: [NEGATIVO] No se detectan masas anomalas.\n";
        } else if (porcentajeOcupado > 0.0 && porcentajeOcupado <= 5.0) {
            reporte << "Resultado: [PRECAUCION] Masa pequena detectada. Requiere observacion.\n";
        } else {
            reporte << "Resultado: [ALERTA CRITICA] Masa de gran tamano detectada (" 
                    << porcentajeOcupado << "% del tejido). Se sugiere biopsia prioritaria.\n";
        }
        reporte.close();
    }
}