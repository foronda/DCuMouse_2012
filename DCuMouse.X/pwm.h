#define RIGHT_MOTOR PORTBbits.RB15
#define LEFT_MOTOR PORTBbits.RB13

#define RDIR_FOR 0
#define RDIR_REV 1
#define LDIR_FOR 1
#define LDIR_REV 0

#define Prescalar 1

#ifndef PWM_H
#define PWM_H
#include "common.h"

void TestPWM();
void InitPWM();

unsigned int GetPWMFreq();
#endif
