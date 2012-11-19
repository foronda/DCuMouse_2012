#include "common.h"
#include "led.h"
#include "uart.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Configuration Bits ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

_FOSCSEL(FNOSC_FRCPLL);                 //set clock for internal OSC with PLL)

_FOSC(POSCMD_NONE & OSCIOFNC_OFF);    	// Primary Oscillator Source (HS Oscillator Mode)
                                        // OSC2 Pin Function (OSC2 pin has clock out function)

_FWDT(FWDTEN_OFF);                      // Watchdog Timer Off

_FICD(ICS_PGD3 & JTAGEN_OFF);           // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
                                        // JTAG Port Enable (JTAG is Disabled)

// FPOR
#pragma config FPWRT = PWR1             // POR Timer Value (Disabled)
#pragma config ALTI2C = OFF             // Alternate I2C  pins (I2C mapped to SDA1/SCL1 pins)
#pragma config LPOL = OFF               // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-low output polarity)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)

int main(void)
{
    InitUART();
    //InitQEI();
    //InitLED();
    InitPWM();
    //TRISB = 0;
    //TestUART();

    TestRMotor();
}
