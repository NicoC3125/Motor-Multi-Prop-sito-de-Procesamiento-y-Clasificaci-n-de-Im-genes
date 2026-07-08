#ifndef __CONTROLMOTOR_H__
#define __CONTROLMOTOR_H__
#include "util.h"
#include "MotorImagen.h"

enum OpcionesMotor {
    DEFORESTACION,
    ESTRELLAS,
    MEDICINA
};

using ControladorMotor = void(*)(MotorImagen&, ostream&, istream&);

void pausar(ostream& os, istream& is);
void limpiar();

void procesarDeforestacion(MotorImagen& motor, ostream& os, istream& is);
void procesarEstrellas(MotorImagen& motor, ostream& os, istream& is);
void procesarMedicina(MotorImagen& motor, ostream& os, istream& is);

#endif