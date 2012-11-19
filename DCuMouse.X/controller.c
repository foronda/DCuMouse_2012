#include "controller.h"
#include "common.h"
#include "pwm.h"

void TestRMotor(void)
{
    while(1)
    {
        printf("PDC1: %d\n", PDC1);
        StopRMotor();
        __delay_ms(2000);
        PDC1 = PTPER/16;
        ForwardRMotor();
        __delay_ms(2000);
        StopRMotor();
        __delay_ms(1000);
        //__delay_ms(2000);
        PDC1 = PTPER/16;
        ReverseRMotor();
        __delay_ms(2000);
    }
}

void ForwardRMotor(void)
{
    PWMCON1bits.PEN1L = 0;
    PWMCON1bits.PEN1H = 1;
}

void ReverseRMotor(void)
{
    PWMCON1bits.PEN1L = 1;
    PWMCON1bits.PEN1H = 0;
}

void StopRMotor(void)
{
    PDC1 = 0;
}

void SetRMotorSpeed(unsigned int s)
{
    PDC1 = PTPER/32;
}
