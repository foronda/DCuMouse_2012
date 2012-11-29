#include "interrupts.h"
#include "controller.h"

// Initialize Motor Interrupts
void InitRMotorTimer()
{
    T1CONbits.TON = 0;      // Disable Timer1 Module
    T1CONbits.TCS = 0;      // Select internal clock cycle
    T1CONbits.TGATE=0;      // Disable Gated timer mode
    T1CONbits.TCKPS=0b10;   // Prescaler 1:256, 1x iteration/cycle
                            // 1, 8, 64, 256 Prescalers

    TMR1=0x00;              // Clears Timer1 register
    PR1=0xFFFF;             // Sets max period, 65535

    IPC0bits.T1IP=7;        // Sets highest priority 7
    IFS0bits.T1IF=0;        // Clear Timer1 Interrupt Flag
    IEC0bits.T1IE=1;        // Enable Timer1 Interrupt*/
    T1CONbits.TON=1;        // Starts Timer1
}

void InitLMotorTimer()
{
    T2CONbits.TON = 0;      // Disable Timer2 Module
    T2CONbits.TCS = 0;      // Select internal clock cycle
    T2CONbits.TGATE=0;      // Disable Gated timer mode
    T2CONbits.TCKPS=0b10;   // Prescaler 1:256, 1x iteration/cycle
                            // 1, 8, 64, 256 Prescalers

    TMR2=0x00;              // Clears Timer1 register
    PR2=0xFFFF;             // Sets max period, 65535

    IPC1bits.T2IP=7;        // Sets highest priority 7
    IFS0bits.T2IF=0;        // Clear Timer2 Interrupt Flag
    IEC0bits.T2IE=1;        // Enable Timer2 Interrupt*/
    T2CONbits.TON=1;        // Starts Timer2
}

// Motor Interrupt Functions
// Currently just have basic timer configuration
// Will need to implement PD controller into interrupts

void __attribute__((__interrupt__)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;  //Clear the INT1 interrupt flag or else
                        //the CPU will keep vectoring back to the ISR
}

void __attribute__((__interrupt__)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;  //Clear the INT1 interrupt flag or else
                        //the CPU will keep vectoring back to the ISR
}

