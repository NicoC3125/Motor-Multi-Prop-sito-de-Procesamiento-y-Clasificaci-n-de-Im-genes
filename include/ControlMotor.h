#ifndef __CONTROLMOTOR_H__
#define __CONTROLMOTOR_H__
#include "util.h"
#include "MotorImagen.h"

enum OpcionesMotor {
    DEFORESTACION,
    ESTRELLAS,
    MEDICINA
};

using ControladorMotor = void(*)(MotorImagen&, ostream&);

void pausar();
void limpiar();

void procesarDeforestacion(MotorImagen& motor, ostream& os);
void procesarEstrellas(MotorImagen& motor, ostream& os);
void procesarMedicina(MotorImagen& motor, ostream& os);

#endif