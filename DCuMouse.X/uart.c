#include "uart.h"
#define _UART1

unsigned int i;

void InitUART(void)
{
    // Configure Oscillator to operate the device at 40 MHz
    // Fosc = Fin * M/(N1 * N2), Fcy = Fosc/2
    // Fosc = 8M * 40(2 * 2) = 80 MHz for 8M input clock
    PLLFBD = 40;                    // M = 40
    CLKDIVbits.PLLPOST = 0;         // N1 = 2
    CLKDIVbits.PLLPRE = 0;          // N2 = 2
    OSCTUN = 0;                     // Tune FRC oscillator, if FRC is used
    RCONbits.SWDTEN = 0;            // Disable Watch Dog Timer
    while(OSCCONbits.LOCK != 1) {}; // Wait for PLL to lock

    /********** RPIN/RPOR Registers  **********/
    // I/O Port mapping for UART Modules

    RPINR18bits.U1RXR = 11;          // UART Receive tied to RP11[Pin8] (U1RXR <4:0>) p.182 Datasheet
    RPOR5bits.RP10R = 3;             // UART Transmit tied to RP10[Pin9] (U1TX <4:0>) p.167 Datasheet

    /********** U1BRG Register  **********/
    // Stores the baud rate value of the transmitted or received data

    U1BRG = BRGVAL;                 // BAUD Rate Setting for 9600

    /********** U1MODE Register  **********/
    // Handles UART Module settings and configuration

    U1MODEbits.STSEL = 0;           // 1 Stop bit
    U1MODEbits.PDSEL = 0;           // No Parity, 8 data bits
    U1MODEbits.ABAUD = 0;           // Auto-Baud Disabled
    U1MODEbits.BRGH = 0;            // Low Speed mode

    U1MODEbits.UARTEN = 1;          // Enable UART

    /********** U1STA Register  **********/
    // Handles status and control register

    U1STAbits.UTXEN = 1;            // Enable UART TX

    /* wait at least 104 usec (1/9600) before sending first char */
    for(i = 0; i < 4160; i++)
    {
        Nop();
    }
}

void TestUART(void)
{
    while(1)
    {
        printf("Testing UART\n");
        __delay_ms(2000);
    }
}


