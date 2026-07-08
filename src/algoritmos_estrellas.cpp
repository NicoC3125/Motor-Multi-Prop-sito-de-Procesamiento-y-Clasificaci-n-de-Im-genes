#include "MotorImagen.h"
#include <cstdio>
#include <fstream>

void MotorImagen::aislarEstrellas(TI brilloMinimo) {
    for (TI i = 0; i < getFilas(); ++i) {
        for (TI j = 0; j < getColumnas(); ++j) {
            Pixel& p = matrizPixeles(i, j);
            TI brillo = p.getGris();
            if (brillo > brilloMinimo) {
                p.r = 255; p.g = 255; p.b = 0; 
            } else {
                p.r = 0; p.g = 0; p.b = 0;
            }
        }
    }
}

void MotorImagen::clasificarCumuloEstelar() {
    TI pixelesEstrella = 0;
    TI totalPixeles = getFilas() * getColumnas();
    
    for (TI i = 0; i < getFilas(); ++i) {
        for (TI j = 0; j < getColumnas(); ++j) {
            if (matrizPixeles(i, j).r == 255 && matrizPixeles(i, j).g == 255) {
                pixelesEstrella++;
            }
        }
    }
    
    TD densidadCalculada = (totalPixeles > 0) ? ((TD)pixelesEstrella / totalPixeles) * 100.0 : 0.0;
    
    printf("\n=== ANALIZADOR ASTROFISICO DE IMAGENES ===\n");
    printf("Pixeles estelares detectados: %d px.\n", pixelesEstrella);
    printf("Densidad estelar del cuadrante: %.2f%%\n", densidadCalculada);
    
    if (densidadCalculada < 0.5) {
        printf("Clasificacion: [ESPACIO PROFUNDO VACIO] Poca presencia de cuerpos celestes.\n");
    } else if (densidadCalculada >= 0.5 && densidadCalculada <= 3.0) {
        printf("Clasificacion: [CUMULO ESTELAR ABIERTO] Grupo de estrellas dispersas.\n");
    } else {
        printf("Clasificacion: [NUCLEO GALACTICO / NEBULOSA DENSA] Alta concentracion estelar.\n");
    }

    ofstream reporte("reporte_estrellas.txt", ios::app);
    if (reporte.is_open()) {
        reporte << "\n=== ANALIZADOR ASTROFISICO DE IMAGENES ===\n"
                << "Pixeles estelares detectados: " << pixelesEstrella << " px.\n"
                << "Densidad estelar del cuadrante: " << densidadCalculada << "%\n";
        if (densidadCalculada < 0.5) {
            reporte << "Clasificacion: [ESPACIO PROFUNDO VACIO] Poca presencia de cuerpos celestes.\n";
        } else if (densidadCalculada >= 0.5 && densidadCalculada <= 3.0) {
            reporte << "Clasificacion: [CUMULO ESTELAR ABIERTO] Grupo de estrellas dispersas.\n";
        } else {
            reporte << "Clasificacion: [NUCLEO GALACTICO / NEBULOSA DENSA] Alta concentracion estelar.\n";
        }
        reporte.close();
    }
}