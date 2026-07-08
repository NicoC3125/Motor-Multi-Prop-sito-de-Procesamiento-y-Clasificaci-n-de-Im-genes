#include "ControlMotor.h"
#include <cstdio>
#include <cstdlib>

void pausar() {
    printf("\nPresione ENTER para volver.");
    while (getchar() != '\n'); 
    getchar();
}

void limpiar() {
    system("clear || cls");
}

void procesarDeforestacion(MotorImagen& motor) {
    limpiar();
    char bufferEntrada[256], bufferSalida[256];
    TS rutaEntrada, rutaSalida;
    
    printf("--- PROCESAMIENTO SATELITAL ---\n");
    printf("Ingrese la ruta de la imagen PPM: ");
    scanf("%255s", bufferEntrada);
    rutaEntrada = bufferEntrada;

    if (motor.cargarImagenPPM(rutaEntrada)) { 
        printf("Imagen satelital cargada con exito.\n");
        motor.clasificarZonasDeforestadas();                 
        motor.aplicarFiltroMediana(); 
        
        printf("Ingrese ruta para guardar resultado: ");
        scanf("%255s", bufferSalida);
        rutaSalida = bufferSalida;
        motor.guardarImagenPPM(rutaSalida); 
    } else {
        printf("Error al cargar el archivo.\n");
    }
    
    while (getchar() != '\n'); 
    pausar();
}

void procesarEstrellas(MotorImagen& motor) {
    limpiar();
    char bufferEntrada[256], bufferSalida[256];
    TS rutaEntrada, rutaSalida;
    
    printf("--- PROCESAMIENTO ASTRONOMICO ---\n");
    printf("Ingrese la ruta de la imagen espacial PPM: ");
    scanf("%255s", bufferEntrada);
    rutaEntrada = bufferEntrada;

    if (motor.cargarImagenPPM(rutaEntrada)) {
        TI umbral;
        printf("Ingrese umbral de brillo minimo para estrellas (0-255): ");
        scanf("%d", &umbral);
        
        motor.aislarEstrellas(umbral);
        motor.clasificarCumuloEstelar();
        
        printf("Ingrese ruta para guardar resultado: ");
        scanf("%255s", bufferSalida);
        rutaSalida = bufferSalida;
        motor.guardarImagenPPM(rutaSalida);
    } else {
        printf("Error al cargar el archivo.\n");
    }
    
    while (getchar() != '\n'); 
    pausar();
}

void procesarMedicina(MotorImagen& motor) {
    limpiar();
    char bufferEntrada[256], bufferSalida[256];
    TS rutaEntrada, rutaSalida;
    
    printf("--- PROCESAMIENTO MEDICO ---\n");
    printf("Ingrese la ruta de la radiografia PPM: ");
    scanf("%255s", bufferEntrada);
    rutaEntrada = bufferEntrada;

    if (motor.cargarImagenPPM(rutaEntrada)) {
        TI umbralMed;
        printf("Ingrese umbral maximo para tejido denso (0-255): ");
        scanf("%d", &umbralMed);
        
        motor.binarizarParaAnomalias(umbralMed);
        motor.clasificarAnomaliaMedica();
        
        printf("Ingrese ruta para guardar resultado: ");
        scanf("%255s", bufferSalida);
        rutaSalida = bufferSalida;
        motor.guardarImagenPPM(rutaSalida);
    } else {
        printf("Error al cargar el archivo.\n");
    }
    
    while (getchar() != '\n');
    pausar();
}