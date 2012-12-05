// PWM Duty cycle registers
#define RMOTOR_SPEED PDC1
#define LMOTOR_SPEED PDC2

// QEI counts for counting rotations
#define QUARTER_ROT 512                 // Pulse count per quarter revolution
#define HALF_ROT 1024                   // Pulse count per half revolution
#define PPR 2048                        // Pulse count per one revolution

// Kinematics Calculations
#define GEAR_RATIO 3.333                // Gear Ratio 40:12, 3.33 rev/w_rev
#define DIAMETER 22                     // 22 mm wheel diameter
#define CIRCUMFERENCE 69.1              // Distance traveled per revolution (C = pi*d)
#define DIST_PER_STEP 0.0101242         // Distance traveled per QEI pulse  (D = (pi*d)/(PPR*GEAR_RATIO))
#define CELL_SIZE 160                   // 160mm cell size
#define CELL_CENTER 14836//15804               // Steps takes to reach cell center (Cent = cell_size/dist_per_step)

// v^2 = vo^2 + 2a(r - ro)              // Acceleration/Deceleration Profile
// Prescalar value for adjusting timer speeds
// Values are x1, x4, x16
#define Prescalar 1

// Controller Gain Constants
#define Kp 8
#define Kd 1

// Motor Speeds
#define STARTING_SPEED PTPER/32
#define MAX_SPEED PTPER/2

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "common.h"
#include "interrupts.h"
#include "sensor.h"
#include "pwm.h"

/**************************************************************/
/**************** START OF MOTOR FUNCTIONS ********************/
/**************************************************************/

// Motor Functions
void DriveFor(unsigned int speed);
void DriveRev(unsigned int speed);
void LTurn(unsigned int speed);
void RTurn(unsigned int speed);
void TurnAround(unsigned int speed);
void DriveOneCell(void);

// Motor Helper functions
void ClearPos(void);

// Test functionality of motors
void TestRMotor(void);
void TestLMotor(void);

// Right Motor Functions
void RMotorFor(unsigned int speed);
void RMotorRev(unsigned int speed);
void RMotorStop(void);
void RMotorBrake(void);
void RClearPos(void);

// Left Motor Functions
void LMotorFor(unsigned int speed);
void LMotorRev(unsigned int speed);
void LMotorStop(void);
void LMotorBrake(void);
void LClearPos(void);

/************************************************************/
/**************** END OF MOTOR FUNCTIONS ********************/
/************************************************************/



/**************************************************************/
/***************** START OF PD CONTROLLER *********************/
/**************************************************************/

// Creates PD Controller struct
struct Controller
{
    int ePrev;          // Previous error
    int Proportional;   // Calculated Proportional value
    int Derivative;     // Calculated Derivative value
    int PDError;        
};

// Controller Functions
void PDTrack(int RightAverage, int LeftAverage);
void PDTrackRight(int RightAverage);
void PDTrackLeft(int LeftAverage);

// PID Calculators
void CalculatePD(int Average, char Side);
void Proportional(int Average, char Side);
void Derivative();

// Initializers
void InitPD();
void ClearPDError();

// Accessor Functions
int GetPrevError();
int GetPDError();
int GetP();
int GetD();

// Mutator Functions
void SetPrevError(int eP);
void SetPDError(int PD);
void SetP(int P);
void SetD(int D);

/****************************************************/
/************* END OF PD CONTROLLER *****************/
/****************************************************/



/**************************************************************/
/***************** START OF KINEMATICS ************************/
/**************************************************************/
struct Kinematics
{
    float Dold;
    float Dnew;
    float Vold;
    float Vnew;
    float Accel;
};

void InitKinematics(void);

float GetDistance(unsigned int count);
float CalcVelocity(float deltaX, float deltaT);
float CalcAccel(float deltaV, float deltaT);

void Accel(unsigned int Vf, unsigned int Vo);

/**************************************************************/
/****************** END OF KINEMATICS *************************/
/**************************************************************/

#endif

