#define RMOTOR_SPEED PDC1
#define LMOTOR_SPEED PDC2

#define QUARTER_ROT 512                 // Pulse count per quarter revolution
#define HALF_ROT 1024                   // Pulse count per half revolution
#define ONE_ROT 2048                    // Pulse count per one revolution

// Kinematics Calculations
#define GEAR_RATIO 3.333                // Gear Ratio 40:12, 3.33 rev/w_rev
#define DIAMETER 2.2                    // 2.3 cm wheel diameter
#define CIRCUMFERENCE 6.91               // Distance traveled per revolution (C = pi*d)
#define DIST_PER_STEP 0.00101242        // Distance traveled per QEI pulse  (D = (pi*d)/(ONE_ROT*GEAR_RATIO))
#define CELL_SIZE 16                    // 16cm cell size
#define CELL_CENTER 15804               // Distance from cell center to next (Cent = cell_size/dist_per_step)

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

