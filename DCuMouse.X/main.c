#include "common.h"
#include "controller.h"
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
    //InitUART();
    //InitQEI();
    //InitLED();
    //InitPWM();
    //TRISB = 0;

    //TestUART();
    //TestRMotor();
    //TestLMotor();
    //TestRQEI();
    //TestLQEI();
    TRISA = 0;
    TRISB = 0;
    PORTAbits.RA9 = 1;
    PORTAbits.RA4 = 1;
    PORTAbits.RA8 = 1;
    //PORTBbits.RB4 = 1;
    
    while(1);
    printf("Wheel Diameter: %0.01f\n", DIAMETER);
    printf("Circumference: %.01f\n", CIRCUMFERENCE);
    printf("Distance per step: %f\n", DIST_PER_STEP);
    printf("Pulses to cell center: %f\n", ceil(CELL_CENTER));
    if(ceil(CELL_CENTER) == 15116)
        printf("Matches!\n");
    while(1);
}
