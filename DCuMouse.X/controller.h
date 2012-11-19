#define RIGHT_MOTOR PORTBbits.RB15
#define LEFT_MOTOR PORTBbits.RB13

#define RDIR_FOR 0
#define RDIR_REV 1
#define LDIR_FOR 1
#define LDIR_REV 0

#define Prescalar 1

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "common.h"

void TestRMotor();
void ForwardRMotor(void);
void ReverseRMotor(void);
void StopRMotor(void);
void SetRMotorSpeed(unsigned int s);

#endif

