#include "led.h"

void InitLED(void)
{
    TRISC = 0;      // Set PORTC as digital outputs

    DEBUG_LED = BLUE1|BLUE2|RED1|RED2;
    __delay_ms(2000);
    DEBUG_LED = 0;
}
