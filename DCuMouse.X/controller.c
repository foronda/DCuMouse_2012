#include "controller.h"
#include "common.h"
#include "pwm.h"

struct Controller PID;

// Controller Gain Constants
#define Kp 8 //5
#define Kd 1 //1

int RTRACKTHRESHOLD = 5;
int LTRACKTHRESHOLD = 3;
int FRONTCENTER = 200;

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

void DriveFor(unsigned int speed)
{
    PDC2 = speed;
    PDC1 = speed;
    RMotorFor();
    LMotorFor();
}

void StopMotors(void)
{
    RMotorStop();
    LMotorStop();
}

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
    RMOTOR_SPEED = 0;
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
    LMOTOR_SPEED = 0;
}
