#include "qei.h"

void InitQEI(void)
{
    InitQEI1();
    InitQEI2();
}
void InitQEI1(void)
{
    /********** QEI1CON 16-bit Register (Section 15. p.5) **********/
    // Controls QEI operation and provide status flags for state modules

    QEI1CONbits.QEISIDL = 0;        // Continue module operation in idle mode
    QEI1CONbits.CNTERR = 0;         // Clear any count errors
    QEI1CONbits.UPDN = 1;           // Position Counter Direction is positive (+)
    QEI1CONbits.SWPAB= 0;           // QEA and QEB not swapped, A leads B
    QEI1CONbits.INDX = 1;           // Read only - Index pin state status pin.
    QEI1CONbits.POSRES = 0;         // No index pulse reset
    QEI1CONbits.QEIM = 7;           // Use 4x Update mode with reset on MAXxCNT match (QEIM <2:0>)
    QEI1CONbits.PCDOUT = 0;         // Counter Direction of Status Output (Normal I/O pin operation)

    /********** DFLT1CON 16-bit Register (Section 15. p.7) **********/
    // Digital filter used to filter spikes in QEI signals

    DFLT1CONbits.CEID = 1;          // Interrupts for count erros are disabled
    DFLT1CONbits.QEOUT = 0;         // Digital Output filter disabled
    DFLT1CONbits.QECK = 0;          // 1:1 Digital Filter Clock Divide (QECK <2:0>)

    /********** POS1CNT 16-bit Register  **********/
    // Allows reading and writing of the position counter

    POS1CNT = 0;                    // Initialize Position Counter => 0

    /********** MAX1CNT 16-bit Register  **********/
    // Register associated with a comparator for comparing POS1CNT counter

    MAX1CNT = 64;                   // Sets maximum count to 16x4 = 64 resolution for HES164a encoder

    /********** Interrupt Registers Configuration **********/
    IFS3bits.QEI1IF = 0;            // Clears QEI1 Interrupt Flag
    IPC14bits.QEI1IP = 7;           // Interrupt Has the highest priority (QEI1IP <2:0>)
    IEC3bits.QEI1IE = 1;            // Enables Interrupt for QEI, occurs when POS1CNT == MAX1CNT

    /********** RPINR14 Register  **********/
    // I/O Port mapping for QEI Modules

    RPINR14bits.QEA1R = 22;         // QEIA Input tied to RP22 (QEA1R<4:0> Pin 2)
    RPINR14bits.QEB1R = 23;         // QEIB Input tied to RP23 (QEB1R<4:0> Pin 3)
    //TRISBbits.TRISB6 = 0;
    //TRISBbits.TRISB7 = 1;
}
void InitQEI2(void)
{
     /********** QEI2CON 16-bit Register (Section 15. p.5) **********/
    // Controls QEI operation and provide status flags for state modules

    QEI2CONbits.QEISIDL = 0;        // Continue module operation in idle mode
    QEI2CONbits.CNTERR = 0;         // Clear any count errors
    QEI2CONbits.UPDN = 1;           // Position Counter Direction is positive (+)
    QEI2CONbits.SWPAB= 0;           // QEA and QEB not swapped, A leads B
    QEI2CONbits.INDX = 1;           // Read only - Index pin state status pin.
    QEI2CONbits.POSRES = 0;         // No index pulse reset
    QEI2CONbits.QEIM = 7;           // Use 4x Update mode with reset on MAXxCNT match (QEIM <2:0>)
    QEI2CONbits.PCDOUT = 0;         // Counter Direction of Status Output (Normal I/O pin operation)

    /********** DFLT1CON 16-bit Register (Section 15. p.7) **********/
    // Digital filter used to filter spikes in QEI signals

    DFLT2CONbits.CEID = 1;          // Interrupts for count erros are disabled
    DFLT2CONbits.QEOUT = 0;         // Digital Output filter disabled
    DFLT2CONbits.QECK = 0;          // 1:1 Digital Filter Clock Divide (QECK <2:0>)

    /********** POS1CNT 16-bit Register  **********/
    // Allows reading and writing of the position counter

    POS2CNT = 0;                    // Initialize Position Counter => 0

    /********** MAX1CNT 16-bit Register  **********/
    // Register associated with a comparator for comparing POS1CNT counter

    MAX2CNT = 64;                   // Sets maximum count to 16x4 = 64 resolution for HES164a encoder

    /********** Interrupt Registers Configuration **********/
    IFS4bits.QEI2IF = 0;            // Clears QEI2 Interrupt Flag
    IPC18bits.QEI2IP = 7;           // Interrupt Has the highest priority (QEI2IP <2:0>)
    IEC4bits.QEI2IE = 1;            // Enables Interrupt for QEI, occurs when POS2CNT == MAX2CNT

    /********** RPINR14 Register  **********/
    // I/O Port mapping for QEI Modules

    RPINR16bits.QEA2R = 24;         // QEI2A Input tied to RP24 (QEA2R<4:0> Pin 4)
    RPINR16bits.QEB2R = 25;         // QEI2B Input tied to RP25 (QEB2R<4:0> Pin 5)
    //TRISBbits.TRISB6 = 0;
    //TRISBbits.TRISB7 = 1;
}


void __attribute__((__interrupt__, no_auto_psv)) _QEI1Interrupt (void)
{
    IFS3bits.QEI1IF = 0;        // Clears QEI1 Interrupt Flag
    printf("QEI Interrupt has occured.\n\n");
    PDC1 = 0;
}

void __attribute__((__interrupt__, no_auto_psv)) _QEI2Interrupt (void)
{
    IFS4bits.QEI2IF = 0;        // Clears QEI2 Interrupt Flag
    printf("QEI Interrupt has occured.\n\n");
    PDC2 = 0;
}

void TestQEI(void)
{
    while(POS1CNT != MAX1CNT || POS2CNT != MAX2CNT)
    {
        printf("Position Count 1: %d\n", POS1CNT);
        printf("Position Count 2: %d\n", POS2CNT);
    }
    //PDC1 = 1;       // 0% Duty cyle for Motor PWM
}

