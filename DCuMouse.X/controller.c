#include "controller.h"
#include "common.h"
#include "pwm.h"

// Test Functions
void TestRQEI(void)
{
    __delay_ms(2000);
    RMOTOR_SPEED = PTPER/32;
    RMotorFor();
    while(1)
    {
        if(POS1CNT%QUARTER_ROT == 0)
        {
            printf("Right Motor Count: %d\n", POS1CNT);
            RMOTOR_SPEED = 0;
            __delay_ms(1000);
            RMOTOR_SPEED = PTPER/32;
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
        RMOTOR_SPEED = PTPER/16;
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
void RMotorFor(void)
{
    PWMCON1bits.PEN1L = 0;
    PWMCON1bits.PEN1H = 1;
}
void RMotorRev(void)
{
    PWMCON1bits.PEN1L = 1;
    PWMCON1bits.PEN1H = 0;
}
void RMotorStop(void)
{
    RMOTOR_SPEED = 0;
}

// Left Motor Functions
void LMotorFor(void)
{
    PWMCON1bits.PEN2L = 1;
    PWMCON1bits.PEN2H = 0;
}

void LMotorRev(void)
{
    PWMCON1bits.PEN2L = 0;
    PWMCON1bits.PEN2H = 1;
}

void LMotorStop(void)
{
    LMOTOR_SPEED = 0;
}
