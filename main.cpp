#include "include/MotorImagen.h"
#include <iostream>

void mostrarMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "   MOTOR DE PROCESAMIENTO DE IMÁGENES    \n";
    std::cout << "=========================================\n";
    std::cout << "1. Cargar Imagen Satelital (Deforestación)\n";
    std::cout << "2. Cargar Imagen de Astronomía (Estrellas)\n";
    std::cout << "3. Cargar Imagen Médica (Anomalías)\n";
    std::cout << "4. Salir\n";
    std::cout << "Seleccione una opción: ";
}

int main() {
    MotorImagen motor;
    int opcion;
    std::string rutaEntrada, rutaSalida;

    do {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1: 
                std::cout << "Ingrese la ruta de la imagen PPM: ";
                std::cin >> rutaEntrada;
                if (motor.cargarImagenPPM(rutaEntrada)) { 
                    std::cout << "¡Imagen satelital cargada con éxito!\n";
                    motor.clasificarZonasDeforestadas();                 
                    motor.aplicarFiltroMediana(); 
                    std::cout << "Ingrese ruta para guardar resultado: ";
                    std::cin >> rutaSalida;
                    motor.guardarImagenPPM(rutaSalida); 
                } else {
                    std::cout << "Error al cargar el archivo.\n";
                }
                break;

            case 2: 
                std::cout << "Ingrese la ruta de la imagen espacial PPM: ";
                std::cin >> rutaEntrada;
                if (motor.cargarImagenPPM(rutaEntrada)) {
                    int umbral;
                    std::cout << "Ingrese umbral de brillo mínimo para estrellas (0-255): ";
                    std::cin >> umbral;
                    motor.aislarEstrellas(umbral);
                    motor.clasificarCumuloEstelar();
                    std::cout << "Ingrese ruta para guardar resultado: ";
                    std::cin >> rutaSalida;
                    motor.guardarImagenPPM(rutaSalida);
                }
                break;

            case 3: 
                std::cout << "Ingrese la ruta de la radiografía PPM: ";
                std::cin >> rutaEntrada;
                if (motor.cargarImagenPPM(rutaEntrada)) {
                    int umbralMed;
                    std::cout << "Ingrese umbral máximo para tejido denso (0-255): ";
                    std::cin >> umbralMed;
                    motor.binarizarParaAnomalias(umbralMed);
                    motor.clasificarAnomaliaMedica();
                    std::cout << "Ingrese ruta para guardar resultado: ";
                    std::cin >> rutaSalida;
                    motor.guardarImagenPPM(rutaSalida);
                }
                break;

            case 4:
                std::cout << "Saliendo del sistema... Liberando memoria.\n";
                break;
                
            default:
                std::cout << "Opción inválida.\n";
        }
    } while (opcion != 4);

    return 0;
}