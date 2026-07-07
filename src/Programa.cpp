#include "Programa.h"
#include "ControlMotor.h"
#include "MotorImagen.h"

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
        cout << "=========================================\n"
             << "   MOTOR DE PROCESAMIENTO DE IMAGENES    \n"
             << "=========================================\n"
             << "1. Cargar Imagen Satelital (Deforestacion)\n"
             << "2. Cargar Imagen de Astronomia (Estrellas)\n"
             << "3. Cargar Imagen Medica (Anomalias)\n"
             << "4. Salir\n"
             << "Seleccione una opcion: ";
        cin >> aux_option;

        if (aux_option >= 1 && aux_option <= 3) {
            OpcionesMotor select = static_cast<OpcionesMotor>(aux_option - 1);
            interfaz[select](motor, cout);
        } else if (aux_option != 4) {
            cout << "Opcion invalida. Vuelva a intentarlo.\n";
            pausar();
        }
    }
}