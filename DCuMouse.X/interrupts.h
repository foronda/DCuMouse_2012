#include "common.h"

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

// Initialize Motor Interrupts, Used for tracking
void InitRMotorTimer();
void InitLMotorTimer();

// Initialize Timer Interrupts for Kinematics Calculations
void InitKinematicsTimer();

// Motor Interrupt Functions
void __attribute__((__interrupt__)) _T1Interrupt(void);
void __attribute__((__interrupt__)) _T2Interrupt(void);

// Timer Interrupt For Calculating Mouse Velocity
void __attribute__((__interrupt__)) _T3Interrupt(void);

#endif	/* INTERRUPTS_H */

