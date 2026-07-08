#include "Programa.h"
#include "ControlMotor.h"
#include "MotorImagen.h"
#include <cstdio>

void DemoMotorImagen() {
    MotorImagen motor;
    ControladorMotor interfaz[] = {
        procesarDeforestacion, 
        procesarEstrellas, 
        procesarMedicina
    };

    TI aux_option = 0;
    while (aux_option != 4) {
        limpiar();
        printf("=========================================\n");
        printf("   MOTOR DE PROCESAMIENTO DE IMAGENES    \n");
        printf("=========================================\n");
        printf("1. Cargar Imagen Satelital (Deforestacion)\n");
        printf("2. Cargar Imagen de Astronomia (Estrellas)\n");
        printf("3. Cargar Imagen Medica (Anomalias)\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &aux_option);

        if (aux_option >= 1 && aux_option <= 3) {
            OpcionesMotor select = static_cast<OpcionesMotor>(aux_option - 1);
            interfaz[select](motor);
        } else if (aux_option != 4) {
            printf("Opcion invalida. Vuelva a intentarlo.\n");
            pausar();
        }
    }
}