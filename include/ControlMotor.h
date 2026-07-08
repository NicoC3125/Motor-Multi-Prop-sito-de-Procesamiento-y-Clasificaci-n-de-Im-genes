#ifndef __CONTROLMOTOR_H__
#define __CONTROLMOTOR_H__
#include "util.h"
#include "MotorImagen.h"

enum OpcionesMotor {
    DEFORESTACION,
    ESTRELLAS,
    MEDICINA
};

using ControladorMotor = void(*)(MotorImagen&);

void pausar();
void limpiar();

void procesarDeforestacion(MotorImagen& motor);
void procesarEstrellas(MotorImagen& motor);
void procesarMedicina(MotorImagen& motor);

#endif