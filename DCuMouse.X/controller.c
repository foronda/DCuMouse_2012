#include "controller.h"
#include "common.h"
#include "pwm.h"

#define TURN_COUNT 3400         // QEI Counts needed to complete a turn 90deg turn
#define TURN_SPEED PTPER/4     // 25% Duty Cycle to match turn count

struct Controller PID;

int RTRACKTHRESHOLD = 5;
int LTRACKTHRESHOLD = 3;
int FRONTCENTER = 200;


// Motor Functions
void DriveOneCell(void)
{
    POS1CNT = CELL_CENTER;
    QEI1CONbits.UPDN = 1;       // Have RQEI Count Down (-)
    
     // Configure interrupt to stop motors once MAXCNT has been reached
    IFS3bits.QEI1IF = 0;        // Clears QEI1 Interrupt Flag
    IPC14bits.QEI1IP = 7;       // Interrupt Has the highest priority (QEI1IP <2:0>)
    IEC3bits.QEI1IE = 1;        // Enables Interrupt for QEI, occurs when POS1CNT == MAX1CNT

    // Set QEI Count value needed to execute a turn
    MAX1CNT = 0;

    PTCONbits.PTEN = 1;         // Enable PWM
    
    DriveFor(PTPER/6);
}


void DriveFor(unsigned int speed)
{
    RMotorFor(speed);
    LMotorFor(LSTARTING_SPEED);
}

void DriveRev(unsigned int speed)
{
    RMotorRev(speed);
    LMotorRev(speed);
}

void StopMotors(void)
{
    RMotorStop();
    LMotorStop();
}

void LTurn(unsigned int speed)
{
    // Must Configure QEI interrupts to be accurate in QEI counts.
    POS1CNT = TURN_COUNT;
    QEI1CONbits.UPDN = 1;       // Have RQEI Count Down (-)

    // Configure interrupt to stop motors once MAXCNT has been reached
    IFS3bits.QEI1IF = 0;        // Clears QEI1 Interrupt Flag
    IPC14bits.QEI1IP = 7;       // Interrupt Has the highest priority (QEI1IP <2:0>)
    IEC3bits.QEI1IE = 1;        // Enables Interrupt for QEI, occurs when POS1CNT == MAX1CNT

    // Set QEI Count value needed to execute a turn
    MAX1CNT = 0;
    
    PTCONbits.PTEN = 1;         // Enable PWM
    RMotorFor(speed);
    LMotorRev(speed);
}

void RTurn(unsigned int speed)
{
    POS2CNT = 0;
    QEI2CONbits.UPDN = 0;           // Have LQEI Count Down (-)

    // Configure interrupt to stop motors once MAXCNT has been reached
    IFS4bits.QEI2IF = 0;            // Clears QEI2 Interrupt Flag
    IPC18bits.QEI2IP = 7;           // Interrupt Has the highest priority (QEI2IP <2:0>)
    IEC4bits.QEI2IE = 1;            // Enables Interrupt for QEI, occurs when POS2CNT == MAX2CNT

    // Set QEI Count value needed to execute a 90deg turn
    MAX2CNT = TURN_COUNT;

    PTCONbits.PTEN = 1;
    RMotorRev(speed);
    LMotorFor(speed);
}

void TurnAround(unsigned int speed)
{
    LTurn(TURN_SPEED);
    __delay_ms(500);
    LTurn(TURN_SPEED);
    __delay_ms(500);
}

void ClearPos(void)
{
    LClearPos();
    RClearPos();
}

// Test Functions
void TestRQEI(void)
{
    __delay_ms(2000);
    RMOTOR_SPEED = PTPER/8;
    RMotorFor(PTPER/8);
    while(1)
    {
        //printf("Right Motor Count: %d\n", POS1CNT);
        if(abs(POS1CNT)%(6827) == 0)
        {
            printf("Right Motor Count: %d\n", POS1CNT);
            //POS1CNT = 0;
            RMotorStop();
            __delay_ms(1000);
            RMotorFor(PTPER/8);
        }
    }
}
void TestLQEI(void)
{
    __delay_ms(2000);
    LMotorFor(PTPER/32);
    while(1)
    {
        if(POS2CNT%QUARTER_ROT == 0)
        {
            printf("Left Motor Count: %d\n", POS2CNT);
            LMotorStop();
            __delay_ms(1000);
            LMotorFor(PTPER/32);
        }
    }
}
void TestRMotor(void)
{
    while(1)
    {
        printf("PDC1: %d\n", PDC2);
        RMotorStop();
        __delay_ms(2000);
        RMotorFor(PTPER/8);
        __delay_ms(2000);
        RMotorStop();
        __delay_ms(1000);
        RMotorRev(PTPER/16);
        __delay_ms(2000);
    }
}

void TestLMotor(void)
{
    while(1)
    {
        LMotorStop();
        __delay_ms(2000);
        LMotorFor(PTPER/16);
        __delay_ms(2000);
        LMotorStop();
        __delay_ms(1000);
        LMotorRev(PTPER/16);
        __delay_ms(2000);
    }
}


// Right Motor Functions
void RMotorAccel(void)
{
    if(RMOTOR_SPEED < MAX_SPEED)            // If MAX_SPEED not reached, has room to speed up
    {
        RMOTOR_SPEED = RMOTOR_SPEED+25;     // Increase PWM duty cycle
    }
    else
    {
        RMOTOR_SPEED = RMOTOR_SPEED-25;     // Decrease PWM duty cycle
    }
    if(RMOTOR_SPEED > MAX_SPEED)            // Already operating at max speed
        RMOTOR_SPEED = MAX_SPEED;
    if(RMOTOR_SPEED < RSTARTING_SPEED)       // Too slow, set to start speed
        RMOTOR_SPEED = RSTARTING_SPEED;
}
void RMotorRev(unsigned int speed)
{
    RMOTOR_SPEED = speed;
    PWMCON1bits.PEN1L = 0;
    PWMCON1bits.PEN1H = 1;
}
void RMotorFor(unsigned int speed)
{
    RMOTOR_SPEED = speed;
    PWMCON1bits.PEN1L = 1;
    PWMCON1bits.PEN1H = 0;
}
void RMotorStop(void)
{
    RMOTOR_SPEED = 0;       // 0% Duty Cycle
}
void RMotorBrake(void)
{
    // Doesn't work, will run at full speed.
    PTCONbits.PTEN = 0;         // Disable PWM
    PORTBbits.RB14 = 0;         // Lock wheels by supplying
    PORTBbits.RB15 = 0;         // -- to both motor wires.
}
void RClearPos()
{
    POS1CNT = 0;
}

// Left Motor Functions
void LMotorAccel(void)
{
    if(LMOTOR_SPEED < MAX_SPEED)            // If MAX_SPEED not reached, has room to speed up
    {
        LMOTOR_SPEED = LMOTOR_SPEED+25;     // Increase PWM duty cycle
    }
    else
    {
        LMOTOR_SPEED = LMOTOR_SPEED-25;     // Decrease PWM duty cycle
    }
    if(LMOTOR_SPEED > MAX_SPEED)            // Already operating at max speed
        LMOTOR_SPEED = MAX_SPEED;
    if(LMOTOR_SPEED < LSTARTING_SPEED)       // Too slow, set to start speed
        LMOTOR_SPEED = LSTARTING_SPEED;
}
void LMotorRev(unsigned int speed)
{
    LMOTOR_SPEED = speed;
    PWMCON1bits.PEN2L = 1;
    PWMCON1bits.PEN2H = 0;
}
void LMotorFor(unsigned int speed)
{
    LMOTOR_SPEED = speed;
    PWMCON1bits.PEN2L = 0;
    PWMCON1bits.PEN2H = 1;
}
void LMotorStop(void)
{
    LMOTOR_SPEED = 0;       // 0% Duty Cycle
}
void LMotorBrake(void)
{
    PTCONbits.PTEN = 0;         // Disable PWM
    PORTBbits.RB10 = 1;         // Lock
    PORTBbits.RB11 = 1;
}
void LClearPos(void)
{
    POS2CNT = 0;
}


/**************************************************************/
/***************** START OF PD CONTROLLER *********************/
/**************************************************************/

void PDTrack(int RightAverage, int LeftAverage)
{
//    StopMotors();
    if(RightWall())            // Right Wall Avail For Tracking
    {
        PDTrackRight(RightAverage);
    }
//    else if(LeftWall())        // Left Wall Available for Tracking
//    {
//        PDTrackLeft(LeftAverage);
//    }
    else                                // No Walls to track...
    {
        ClearPDError();                      // Reset PD Errors
        RClearAlign();
        LClearAlign();
    }
    //DriveFor();
}

/**************************************************************/
/****************** END OF PD CONTROLLER **********************/
/**************************************************************/

/**************************************************************/
/************ START OF PD CONTROLLER FUNCTIONS ****************/
/**************************************************************/

// Returns PD value for SR sensors based on errors
// If Proportional => pos, pulling right, speed up right motor
// If Proportional => neg, pulling left, speed up left motor
// RTRACKTHRESHOLD accounts for acceptable errors, Error < -5 || Error > 5
// Proportional Term Still Needs To Be Linearize using slope equation
void PDTrackRight(int RightAverage)
{
    CalculatePD(RightAverage, 'R');
    
    if(GetP() > 12)          // Pulling Right, Speed up R Motor
    {
        printf("RW Track, Pulling Right.\n");
        RSetAlign();
        LClearAlign();  // Clear Opposite motor flag to return to proper speed
    }
    else if(GetP() < -12)     // Pulling Left, Speed up L motor
    {
        printf("RW Track, Pulling Left.\n");
        LSetAlign();
        RClearAlign();
    }
    else                                    // No Error, Go Straight
    {
        ClearPDError();                    // Be Sure to clear  PD Error
        RClearAlign();
        LClearAlign();
    }
}

void PDTrackLeft(int LeftAverage)
{
    CalculatePD(LeftAverage, 'L');

    if(GetP() > 12)                 // Pulling Left, Speed up L Motor
    {
        printf("LW Track, Pulling Left.\n");
        LSetAlign();
        RClearAlign();              // Clear Opposite motor flag to return to proper speed
    }
    else if(GetP() < -12)           // Pulling Right, Speed up R motor
    {
        printf("LW Track, Pulling Right.\n");
        RSetAlign();
        LClearAlign();
    }
    else                            // No Error, Go Straight
    {
        ClearPDError();
        RClearAlign();
        LClearAlign();
    }
}

// Move mouse forward until in center, using Front sensors for guide
// LOL
// new function... void MoonWalkToFront()

void AlignToFront()
{
    // Stub function
}

// Controller Calculation Functions
void CalculatePD(int Average, char Side)
{
    SetPrevError(GetP());               // Sets Previous Error For Next Iteration
    Proportional(Average, Side);        // Calculates Proportional Error
    Derivative();                       // Calculate Derivative Error
    SetPDError(GetP() + GetD());
}

void Proportional(int Average, char Side)
{
    if(Side == 'R')
        SetP(Kp*(Average - ReadSR()));
    if(Side == 'L')
        SetP(Kp*Average - ReadSL());
}

void Derivative()
{   SetD(Kd*(GetP() - GetPrevError()));    }

// Initializers
void InitPD()
{
    PID.Derivative = 0;
    PID.PDError = 0;
    PID.ePrev = 0;
    PID.Proportional = 0;
    PID.RFlag = 0;
    PID.LFlag = 0;
}

void ClearPDError()
{
    PID.PDError = 0;
}

// Controller Accessor Functions
int GetPDError()
{   return PID.PDError; };

int GetPrevError()
{   return PID.ePrev;   }

int GetP()
{   return PID.Proportional;   }

int GetD()
{   return PID.Derivative;  }

// Controller Mutator Functions
void SetPrevError(int e)
{   PID.ePrev = e;  }

void SetPDError(int e)
{   PID.PDError = e;    }

void SetP(int P)
{   PID.Proportional = P; }

void SetD(int D)
{  PID.Derivative = D;  }


// Functions for setting tracking flags based on
// wall readings. If flags are set, it will track 
// based on walls available.

// Controller Flags
bool RTrack(void)
{
    return PID.RFlag;
}
bool LTrack(void)
{
    return PID.LFlag;
}

void RClearAlign(void)
{
    PID.RFlag = 0;
}
void LClearAlign(void)
{
    PID.LFlag = 0;
}

void RSetAlign(void)
{
    PID.RFlag = 1;
}
void LSetAlign(void)
{
    PID.LFlag = 1;
}

/**************************************************************/
/************* END OF PD CONTROLLER FUNCTIONS *****************/
/**************************************************************/


/**************************************************************/
/***************** START OF KINEMATICS ************************/
/**************************************************************/

float GetDistance(unsigned int count)
{
    return (float)DIST_PER_STEP*count;
}

// Distance is in mm, Time is in ms, Velocity = m/s
float CalcVelocity(float deltaX, float deltaT)
{
    return deltaX/deltaT;
}

float CalcAccel(float deltaV, float deltaT)
{
    return deltaV/deltaT;
}

void Accel(unsigned int Vf, unsigned int Vo);
/**************************************************************/
/****************** END OF KINEMATICS *************************/
/**************************************************************/
