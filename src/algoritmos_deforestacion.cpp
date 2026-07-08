#include "MotorImagen.h"
#include "Sorting.h"
#include <cstdio>
#include <fstream>

void MotorImagen::aplicarFiltroMediana() {
    TU8 vecinos[9];
    CMatrix<Pixel> copia = matrizPixeles;
    for (TI i = 1; i < getFilas() - 1; ++i) {
        for (TI j = 1; j < getColumnas() - 1; ++j) {
            TI k = 0;
            for (TI f = -1; f <= 1; ++f) {
                for (TI c = -1; c <= 1; ++c) {
                    vecinos[k++] = copia(i + f, j + c).r;
                }
            }
            quickSort<TU8, TB(*)(const TU8&, const TU8&)>(vecinos, 9, [](const TU8& a, const TU8& b) { return a < b; });
            matrizPixeles(i, j).setGris(vecinos[4]);
        }
    }
}

void MotorImagen::clasificarZonasDeforestadas() {
    TI pixelesBosque = 0;
    TI pixelesDeforestados = 0;
    
    for (TI i = 0; i < getFilas(); ++i) {
        for (TI j = 0; j < getColumnas(); ++j) {
            Pixel& p = matrizPixeles(i, j);
            if (p.g > p.r && p.g > p.b) {
                pixelesBosque++;
            } else if (p.r > p.g && p.r > 50) { 
                pixelesDeforestados++;
                p.r = 255; p.g = 0; p.b = 0;
            }
        }
    }
    
    TD totalImagen = getFilas() * getColumnas();
    TD porcentajeAlerta = (totalImagen > 0) ? ((TD)pixelesDeforestados / totalImagen) * 100.0 : 0.0;
    
    printf("--- REPORTE DE CLASIFICACION SATELITAL ---\n");
    printf("Zonas de Bosque Saludable: %d px.\n", pixelesBosque);
    printf("Zonas con Alerta de Deforestacion: %d px.\n", pixelesDeforestados);
    printf("Porcentaje de dano territorial: %.2f%%\n", porcentajeAlerta);
    
    if(porcentajeAlerta > 15.0) {
        printf("[ALERTA CRITICA]: Se sugiere intervencion en la zona.\n");
    }

    ofstream reporte("reporte_satelital.txt", ios::app);
    if (reporte.is_open()) {
        reporte << "--- REPORTE DE CLASIFICACION SATELITAL ---\n"
                << "Zonas de Bosque Saludable: " << pixelesBosque << " px.\n"
                << "Zonas con Alerta de Deforestacion: " << pixelesDeforestados << " px.\n"
                << "Porcentaje de dano territorial: " << porcentajeAlerta << "%\n";
        if(porcentajeAlerta > 15.0) {
            reporte << "[ALERTA CRITICA]: Se sugiere intervencion en la zona.\n";
        }
        reporte.close();
    }
}