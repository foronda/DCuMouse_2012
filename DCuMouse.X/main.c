#include "common.h"
#include "controller.h"
#include "sensor.h"
#include "led.h"
#include "uart.h"
#include "interrupts.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~ Configuration Bits ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

_FOSCSEL(FNOSC_FRCPLL);                 //set clock for internal OSC with PLL)

_FOSC(POSCMD_NONE & OSCIOFNC_OFF);    	// Primary Oscillator Source (HS Oscillator Mode)
                                        // OSC2 Pin Function (OSC2 pin has clock out function)

_FWDT(FWDTEN_OFF);                      // Watchdog Timer Off

_FICD(ICS_PGD3 & JTAGEN_OFF);           // Comm Channel Select (Communicate on PGC1/EMUC1 and PGD1/EMUD1)
                                        // JTAG Port Enable (JTAG is Disabled)

int main(void)
{
    TRISA = 0;
    TRISC = 0;
    TRISB = 0;
    
    InitUART();
    //InitLED();
    InitADC();
    //InitQEI();
    //InitPWM();
    //InitPD();
    //InitKinematics();
    //InitKinematicsTimer();
    
    TRISB = 0;

    //TestUART();
    //TestRMotor();
    //TestLMotor();
    //TestRQEI();
    //TestLQEI();
    //RMotorFor();
    //__delay_ms(1000);

    //DriveOneCell();

    while(1)
    {
        CalibrateSensors();
       //printf("POS1CNT: %d\n", abs(POS1CNT));
        //printf("Distance traveled: %f\n", GetDistance(abs(POS1CNT)));
        //printf("Velocity (m/s):%f\n", CalcVelocity(50,250));
    }
    /*
    unsigned int speed;
    speed = PTPER/32;
    while(1)
    {
        DriveFor(speed);
        printf("POS1CNT: %d\n\n", POS1CNT);

        if((8192 <= abs(POS1CNT)) || (8192 <= POS2CNT))
        {
            POS1CNT=0;
            POS2CNT=0;
            //StopMotors();
            //__delay_ms(500);
            //speed = PTPER/32;
        }
        else
        {
            speed=speed+5;
            if(speed >= PTPER/10)
                speed = PTPER/10;
        }

    }
    // Git merge test...
    // Ryan merge test...
    // Sensors merge test...
    while(1);
    printf("Wheel Diameter: %0.01f\n", DIAMETER);
    printf("Circumference: %.01f\n", CIRCUMFERENCE);
    printf("Distance per step: %f\n", DIST_PER_STEP);
    printf("Pulses to cell center: %f\n", ceil(CELL_CENTER));
    if(ceil(CELL_CENTER) == 15116)
        printf("Matches!\n");
    while(1);*/
}
