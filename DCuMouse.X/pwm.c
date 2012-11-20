#include "pwm.h"

void InitPWM(void)
{
    TRISBbits.TRISB12 = 0;      // PWM1H2 (Pin 10) set as digital output
    TRISBbits.TRISB13 = 0;      // PWM1L2 (Pin 11) set as digital output
    TRISBbits.TRISB14 = 0;      // PWM1H1 (Pin 14) set as digital output
    TRISBbits.TRISB15 = 0;      // PWM1L1 (Pin 15) set as digital output
    
    PORTB = 0x00;               // clear the outputs

    //PTCONbits.PTEN = 1;         // Disable PWM Time Base Timer (PTEN)
    PTCONbits.PTOPS = 0;        // PWM timer 1:1 post-scale  (PTOPS <3:0>)
                                // Decides when to set PWMIF interrupt flag

    PTCONbits.PTCKPS = 0;       // PWM timer 1:1 pre-scale   (PTCKPS <1:0>)

    // PTMR register will count upwards until PTPER is matched
    // PTMR register will reset on the following clock edge
    // Continuously run as long as PTEN is enabled.
    // Prescaled clock is the input to the PWM module

    PTCONbits.PTMOD = 0;        // PWM operates in free-running Mode continuously (PTMOD <1:0>)
    PTMR = 0;                   // PWM counter value, start at 0 (PTMR <14:0>)
    PTPER = 1023;               // PWM Timebase period, determines PWM frequency (PTPER <14:0>)

    /*~~~~~~~~~~~~~~ PWM1 Configuration ~~~~~~~~~~~~~~~~~~~~~~~*/
    /*~~~~~~~~~~~~~~ Page 220 of datasheet ~~~~~~~~~~~~~~~~~~~~*/
    /*                             FCY                         */
    /*       PTPER  = ------------------------------- - 1      */
    /*                     (FPWM) * (PTMR Presclar)            */

    /* FPWM = 40000000/(1023*1) = 39.1 kHz                 */

    PWMCON1bits.PMOD1 = 1;      // PWM1 in complementary mode (inverses PWML1)
    PWMCON1bits.PMOD2 = 1;      // PWM2 in complementary mode (inverses PWML2)

    //PWMCON1bits.PEN1H = 1;      // PWM1H1 pin is enabled
    //PWMCON1bits.PEN2H = 1;      // PWM1H2 pin is enabled
    //PWMCON1bits.PEN3H = 0;      // PWM1H3 pin is disabled

    //PWMCON1bits.PEN3L = 0;      // PWM Low pin disabled (direction control later?)
    //PWMCON1bits.PEN2L = 0;      // PWM Low pin disabled (direction control later?)
    //PWMCON1bits.PEN1L = 0;      // PWM Low pin disabled (direction control later?)

    // The Duty cycle gives the time for which the PWM pulses are active in a given PWM time period.
    //PDC1 = PTPER/16;             // PWM#1 Duty Cycle register (PDC1<15:0>) 25% Active
    //PDC2 = PTPER/16;           // PWM#2 Duty Cycle register (PDC3<15:0>)
    //PDC3 = 0;                 // PWM#3 Duty Cycle register (PDC3<15:0>)

    PTCONbits.PTEN = 1;         // Enable PWM Timer
}

void TestPWM(void)
{
    int i;

    while(1)
    {
        printf("PWM Frequency %d kHz.\n", GetPWMFreq());
        for(i = 0; i < 2*PTPER; i++)
        {
            PDC1++;
            __delay_ms(1);
        }
        PDC1 = 0;           // Reset Duty Cycle
        __delay_ms(500);
    }
}


// Function will Calculate PWM Frequencies
// Integer returned is in kHz, max is 65536 MHz
unsigned int GetPWMFreq()
{
    return (FCY/(P1TPER*Prescalar) - 1)/(1000);
}
