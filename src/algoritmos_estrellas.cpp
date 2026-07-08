#include "MotorImagen.h"

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

void MotorImagen::clasificarCumuloEstelar(ostream& os) {
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
    
    os << "\n=== ANALIZADOR ASTROFISICO DE IMAGENES ===\n"
         << "Pixeles estelares detectados: " << pixelesEstrella << " px.\n"
         << "Densidad estelar del cuadrante: " << densidadCalculada << "%\n";
    
    if (densidadCalculada < 0.5) {
        os << "Clasificacion: [ESPACIO PROFUNDO VACIO] Poca presencia de cuerpos celestes.\n";
    } else if (densidadCalculada >= 0.5 && densidadCalculada <= 3.0) {
        os << "Clasificacion: [CUMULO ESTELAR ABIERTO] Grupo de estrellas dispersas.\n";
    } else {
        os << "Clasificacion: [NUCLEO GALACTICO / NEBULOSA DENSA] Alta concentracion estelar.\n";
    }
}
