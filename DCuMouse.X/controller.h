#define RMOTOR_SPEED PDC1
#define LMOTOR_SPEED PDC2

#define QUARTER_ROT 512
#define HALF_ROT 1024
#define ONE_ROT 2048

#define Prescalar 1

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "common.h"

void TestRMotor(void);
void TestLMotor(void);

void RMotorFor(void);
void RMotorRev(void);
void RMotorStop(void);

void LMotorFor(void);
void LMotorRev(void);
void LMotorStop(void);

#endif

