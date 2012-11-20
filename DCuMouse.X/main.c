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

int main(void)
{
    InitUART();
    InitQEI();
    //InitLED();
    InitPWM();
    //TRISB = 0;

    //TestUART();
    //TestRMotor();
    //TestLMotor();
    //TestRQEI();
    TestLQEI();
}
