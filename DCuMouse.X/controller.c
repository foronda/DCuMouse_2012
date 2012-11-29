#include "controller.h"
#include "common.h"
#include "pwm.h"

struct Controller PID;

int RTRACKTHRESHOLD = 5;
int LTRACKTHRESHOLD = 3;
int FRONTCENTER = 200;

// Motor Functions
void DriveFor(unsigned int speed)
{
    PDC2 = speed;
    PDC1 = speed;
    RMotorFor();
    LMotorFor();
}

void DriveRev(unsigned int speed)
{
    PDC1 = speed;
    PDC2 = speed;
    RMotorRev();
    LMotorRev();
}

void StopMotors(void)
{
    RMotorStop();
    LMotorStop();
}

void LTurn(unsigned int speed)
{
    RMOTOR_SPEED = speed;
    LMOTOR_SPEED = speed;
    POS1CNT = 0;
    POS2CNT = 0;
    PTCONbits.PTEN = 1;         // Disable PWM

    RMotorFor();
    LMotorRev();
    printf("Starting turn.\n");

    while(1024 <= abs(POS1CNT) || (1024 <= POS2CNT))
    {
        printf("POS2CNT: %d \n", POS2CNT);
        RMOTOR_SPEED = speed+20;
        LMOTOR_SPEED = speed+20;
        if(speed >= PTPER/2)
            speed = PTPER/2;
    }
    printf("Done turn.\n");
    RMotorStop();
    LMotorStop();
}

void RTurn(unsigned int speed);
void TurnAround(unsigned int speed);

// Test Functions
void TestRQEI(void)
{
    __delay_ms(2000);
    RMOTOR_SPEED = PTPER/8;
    RMotorFor();
    while(1)
    {
        //printf("Right Motor Count: %d\n", POS1CNT);
        if(abs(POS1CNT)%(6827) == 0)
        {
            printf("Right Motor Count: %d\n", POS1CNT);
            //POS1CNT = 0;
            RMOTOR_SPEED = 0;
            __delay_ms(1000);
            RMOTOR_SPEED = PTPER/8;
        }
    }
}
void TestLQEI(void)
{
        __delay_ms(2000);
    LMOTOR_SPEED = PTPER/32;
    LMotorFor();
    while(1)
    {
        if(POS2CNT%QUARTER_ROT == 0)
        {
            printf("Left Motor Count: %d\n", POS2CNT);
            LMOTOR_SPEED = 0;
            __delay_ms(1000);
            LMOTOR_SPEED = PTPER/32;
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
        RMOTOR_SPEED = PTPER/8;
        RMotorFor();
        __delay_ms(2000);
        RMotorStop();
        __delay_ms(1000);
        //__delay_ms(2000);
        RMOTOR_SPEED = PTPER/16;
        RMotorRev();
        __delay_ms(2000);
    }
}

void TestLMotor(void)
{
    while(1)
    {
        LMotorStop();
        __delay_ms(2000);
        LMOTOR_SPEED = PTPER/16;
        LMotorFor();
        __delay_ms(2000);
        LMotorStop();
        __delay_ms(1000);
        //__delay_ms(2000);
        LMOTOR_SPEED = PTPER/16;
        LMotorRev();
        __delay_ms(2000);
    }
}


// Right Motor Functions

void RMotorRev(void)
{
    PWMCON1bits.PEN1L = 0;
    PWMCON1bits.PEN1H = 1;
}
void RMotorFor(void)
{
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
    PORTBbits.RB14 = 1;         // Lock wheels by supplying
    PORTBbits.RB15 = 1;         // ++ to both motor wires.
}

// Left Motor Functions
void LMotorRev(void)
{
    PWMCON1bits.PEN2L = 1;
    PWMCON1bits.PEN2H = 0;
}

void LMotorFor(void)
{
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


/**************************************************************/
/***************** START OF PD CONTROLLER *********************/
/**************************************************************/

void PDTrack(int RightAverage, int LeftAverage)
{

//    StopMotors();
//    if(RightTrack())            // Right Wall Avail For Tracking
//    {
//        PDTrackRight(RightAverage);
//    }
//    else if(LeftTrack())        // Left Wall Available for Tracking
//    {
//        PDTrackLeft(LeftAverage);
//    }
//    else                                // No Walls to track...
//    {
//        ClearPDError();                      // Reset PD Errors
//        RClearAlignFlag();
//        LClearAlignFlag();
//    }
//    DriveFor(DRIVE_SPEED);
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
//
//    if(GetP() > 5)          // Pulling Right, Speed up R Motor
//    {
//        RSetAlignFlag();
//        LClearAlignFlag();  // Clear Opposite motor flag to return to proper speed
//    }
//    else if(GetP() < -5)     // Pulling Left, Speed up L motor
//    {
//        LSetAlignFlag();
//        RClearAlignFlag();
//    }
//    else                                    // No Error, Go Straight
//    {
//        ClearPDError();                    // Be Sure to clear  PD Error
//        RClearAlignFlag();
//        LClearAlignFlag();
//    }
}

void PDTrackLeft(int LeftAverage)
{
    CalculatePD(LeftAverage, 'L');
//
//    if(GetP() > 5)                 // Pulling Left, Speed up L Motor
//    {
//        LSetAlignFlag();
//        RClearAlignFlag();                          // Clear Opposite motor flag to return to proper speed
//    }
//    else if(GetP() < -5)           // Pulling Right, Speed up R motor
//    {
//        RSetAlignFlag();
//        LClearAlignFlag();
//    }
//    else                                            // No Error, Go Straight
//    {
//        ClearPDError();
//        RClearAlignFlag();
//        LClearAlignFlag();
//    }
}

// Move mouse forward until in center, using Front sensors for guide
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
        SetP(Kp*(ReadSR() - Average));
    if(Side == 'L')
        SetP(Kp*(ReadSL() - Average));
}

void Derivative()
{   SetD((abs(GetP()) - GetPrevError())/Kd);    }

// Initializers

void InitPD()
{
    PID.Derivative = 0;
    PID.PDError = 0;
    PID.ePrev = 0;
    PID.Proportional = 0;
}

void ClearPDError()
{
    SetPrevError(0);
    SetPDError(0);
    SetP(0);
    SetD(0);
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

/**************************************************************/
/************* END OF PD CONTROLLER FUNCTIONS *****************/
/**************************************************************/
