#include "MotorImagen.h"

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
    
    cout << "\n=== REPORTE DEL MOTOR DE DIAGNOSTICO MEDICO ===\n"
         << "Densidad de pixeles sospechosos: " << pixelesAnomalos << " px.\n"
         << "Area estimada de la masa: " << areaEstimadaMm2 << " mm2.\n";
    
    if (pixelesAnomalos == 0) {
        cout << "Resultado: [NEGATIVO] No se detectan masas anomalas.\n";
    } else if (porcentajeOcupado > 0.0 && porcentajeOcupado <= 5.0) {
        cout << "Resultado: [PRECAUCION] Masa pequena detectada. Requiere observacion.\n";
    } else {
        cout << "Resultado: [ALERTA CRITICA] Masa de gran tamano detectada (" 
             << porcentajeOcupado << "% del tejido). Se sugiere biopsia prioritaria.\n";
    }
}
