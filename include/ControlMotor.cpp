#include "ControlMotor.h"

void pausar() {
    cout << "\nPresione ENTER para volver.";
    cin.ignore();
    cin.get();
}

void limpiar() {
    system("clear || cls");
}

void procesarDeforestacion(MotorImagen& motor, ostream& os) {
    limpiar();
    TS rutaEntrada, rutaSalida;
    os << "--- PROCESAMIENTO SATELITAL ---\n";
    os << "Ingrese la ruta de la imagen PPM: ";
    cin >> rutaEntrada;
    if (motor.cargarImagenPPM(rutaEntrada)) { 
        os << "Imagen satelital cargada con exito.\n";
        motor.clasificarZonasDeforestadas();                 
        motor.aplicarFiltroMediana(); 
        os << "Ingrese ruta para guardar resultado: ";
        cin >> rutaSalida;
        motor.guardarImagenPPM(rutaSalida); 
    } else {
        os << "Error al cargar el archivo.\n";
    }
    cin.ignore();
    pausar();
}

void procesarEstrellas(MotorImagen& motor, ostream& os) {
    limpiar();
    TS rutaEntrada, rutaSalida;
    os << "--- PROCESAMIENTO ASTRONOMICO ---\n";
    os << "Ingrese la ruta de la imagen espacial PPM: ";
    cin >> rutaEntrada;
    if (motor.cargarImagenPPM(rutaEntrada)) {
        TI umbral;
        os << "Ingrese umbral de brillo minimo para estrellas (0-255): ";
        cin >> umbral;
        motor.aislarEstrellas(umbral);
        motor.clasificarCumuloEstelar();
        os << "Ingrese ruta para guardar resultado: ";
        cin >> rutaSalida;
        motor.guardarImagenPPM(rutaSalida);
    } else {
        os << "Error al cargar el archivo.\n";
    }
    cin.ignore();
    pausar();
}

void procesarMedicina(MotorImagen& motor, ostream& os) {
    limpiar();
    TS rutaEntrada, rutaSalida;
    os << "--- PROCESAMIENTO MEDICO ---\n";
    os << "Ingrese la ruta de la radiografia PPM: ";
    cin >> rutaEntrada;
    if (motor.cargarImagenPPM(rutaEntrada)) {
        TI umbralMed;
        os << "Ingrese umbral maximo para tejido denso (0-255): ";
        cin >> umbralMed;
        motor.binarizarParaAnomalias(umbralMed);
        motor.clasificarAnomaliaMedica();
        os << "Ingrese ruta para guardar resultado: ";
        cin >> rutaSalida;
        motor.guardarImagenPPM(rutaSalida);
    } else {
        os << "Error al cargar el archivo.\n";
    }
    cin.ignore();
    pausar();
}