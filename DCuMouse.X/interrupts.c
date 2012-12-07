#include "interrupts.h"
#include "controller.h"

struct Kinematics K;

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

// Kinematics timer operates in 16-Bit timer mode
void InitKinematicsTimer()
{
    T3CONbits.TON = 0;      // Disable Timer
    T3CONbits.TCS = 0;      // Select internal instruction cycle clock
    T3CONbits.TGATE = 0;    // Disable Gated Timer mode
    T3CONbits.TCKPS = 0b11; // Select 1:256 Prescaler

    TMR3 = 0x00;            // Clear timer register
    PR3 =  0x3D09;          // Period = Desired Time/TCY, TCY = 1/(FCY/Prescalar)
                            // Resolution of 250 ms = 1/4 sec

    IPC2bits.T3IP = 7;      // Set Timer3 Interrupt Priority Level
    IFS0bits.T3IF = 0;      // Clear Timer3 Interrupt Flag
    IEC0bits.T3IE = 1;      // Enable Timer3 interrupt
    T3CONbits.TON = 1;      // Start Timer
}

// Motor Interrupt Functions
// Currently just have basic timer configuration
// Will need to implement PD controller into interrupts

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;  //Clear the INT1 interrupt flag or else
                        //the CPU will keep vectoring back to the ISR
}

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;  //Clear the INT3 interrupt flag or else
                        //the CPU will keep vectoring back to the ISR
}

// In this interrupt, kinematic equations will be used to calculate velocity and acceleration.
void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T3Interrupt(void)
{
    ReadSR();
    
    //T3CONbits.TON = 0;      // Disable Timer
    PDTrack(76, 81);
    //printf("P Term: %d\n", GetP());
    //printf("D Term: %d\n", GetD());
    //printf("PDError:%d.\n\n", GetPDError()/4);
    // Speed up right motor
    if(RTrack())
    {
        RMOTOR_SPEED = RMOTOR_SPEED + abs(GetPDError())/6;
        LMOTOR_SPEED = LSTARTING_SPEED;
        //LMOTOR_SPEED = LMOTOR_SPEED - abs(GetPDError())/6;
        if(RMOTOR_SPEED > MAX_SPEED)
            RMOTOR_SPEED = MAX_SPEED;
        //if(LMOTOR_SPEED < STARTING_SPEED)
          //  LMOTOR_SPEED = STARTING_SPEED;
    }
    // Speed up left motor
    else if(LTrack())
    {
        LMOTOR_SPEED = LMOTOR_SPEED + abs(GetPDError())/6;
        RMOTOR_SPEED = RSTARTING_SPEED;
        if(LMOTOR_SPEED > MAX_SPEED)
            LMOTOR_SPEED = MAX_SPEED;
    }
    else
    {
        RMOTOR_SPEED = RSTARTING_SPEED;
        LMOTOR_SPEED = LSTARTING_SPEED;
    }
    //TMR3 = 0x00;            // Clear timer register
    //T3CONbits.TON = 1;      // Enable Timer
    
    IFS0bits.T3IF = 0;  //Clear the INT3 interrupt flag or else
                        //the CPU will keep vectoring back to the ISR
}

void InitKinematics(void)
{
    K.Dnew = 0;
    K.Dold = 0;
    K.Vnew = 0;
    K.Vold = 0;
    K.Accel = 0;
}

