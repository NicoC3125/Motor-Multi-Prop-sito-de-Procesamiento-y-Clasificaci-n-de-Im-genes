#include "ControlMotor.h"

void pausar(ostream& os, istream& is) {
    os << "\nPresione ENTER para volver.";
    is.ignore();
    is.get();
}

void limpiar() {
    system("clear || cls");
}

void procesarDeforestacion(MotorImagen& motor, ostream& os, istream& is) {
    limpiar();
    TS rutaEntrada, rutaSalida;
    os << "--- PROCESAMIENTO SATELITAL ---\n";
    os << "Ingrese la ruta de la imagen PPM: ";
    is >> rutaEntrada;
    if (motor.cargarImagenPPM(rutaEntrada)) { 
        os << "Imagen satelital cargada con exito.\n";
        motor.clasificarZonasDeforestadas();                 
        motor.aplicarFiltroMediana(); 
        os << "Ingrese ruta para guardar resultado: ";
        is >> rutaSalida;
        motor.guardarImagenPPM(rutaSalida); 
    } else {
        os << "Error al cargar el archivo.\n";
    }
    is.ignore();
    pausar(os, is);
}

void procesarEstrellas(MotorImagen& motor, ostream& os, istream& is) {
    limpiar();
    TS rutaEntrada, rutaSalida;
    os << "--- PROCESAMIENTO ASTRONOMICO ---\n";
    os << "Ingrese la ruta de la imagen espacial PPM: ";
    is >> rutaEntrada;
    if (motor.cargarImagenPPM(rutaEntrada)) {
        TI umbral;
        os << "Ingrese umbral de brillo minimo para estrellas (0-255): ";
        is >> umbral;
        motor.aislarEstrellas(umbral);
        motor.clasificarCumuloEstelar();
        os << "Ingrese ruta para guardar resultado: ";
        is >> rutaSalida;
        motor.guardarImagenPPM(rutaSalida);
    } else {
        os << "Error al cargar el archivo.\n";
    }
    is.ignore();
    pausar(os, is);
}

void procesarMedicina(MotorImagen& motor, ostream& os, istream& is) {
    limpiar();
    TS rutaEntrada, rutaSalida;
    os << "--- PROCESAMIENTO MEDICO ---\n";
    os << "Ingrese la ruta de la radiografia PPM: ";
    is >> rutaEntrada;
    if (motor.cargarImagenPPM(rutaEntrada)) {
        TI umbralMed;
        os << "Ingrese umbral maximo para tejido denso (0-255): ";
        is >> umbralMed;
        motor.binarizarParaAnomalias(umbralMed);
        motor.clasificarAnomaliaMedica();
        os << "Ingrese ruta para guardar resultado: ";
        is >> rutaSalida;
        motor.guardarImagenPPM(rutaSalida);
    } else {
        os << "Error al cargar el archivo.\n";
    }
    is.ignore();
    pausar(os, is);
}