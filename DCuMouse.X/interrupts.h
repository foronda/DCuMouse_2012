#include "common.h"

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

// Initialize Motor Interrupts
void InitRMotorTimer();
void InitLMotorTimer();

// Motor Interrupt Functions
void __attribute__((__interrupt__)) _T1Interrupt(void);
void __attribute__((__interrupt__)) _T2Interrupt(void);

#endif	/* INTERRUPTS_H */

