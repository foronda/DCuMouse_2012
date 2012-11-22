#include "sensor.h"
#include "common.h"
/***************************************/
/******* START SENSOR FUNCTIONS ********/
/***************************************/

// Initialize ADC Struct for Sensors
struct ADC Sensors = {0, 0, 0, 0};

void InitADC(void)
{
    /********** ADxCON1: ADCx Control Register 16.1 (p.7) **********/
    AD1CON1bits.ADON = 0;       // ADC Module Must be disable prior to config
    AD1CON1bits.AD12B = 0;      // 10-bit 4-Channel ADC Operation Mode
    AD1CON1bits.FORM = 0;       // Unsigned Integer Output (FORM <1:0>)
    AD1CON1bits.ASAM = 0;       // Automatic sampling disabled, controlled by software

    /********** ADxCON2: ADCx Control Register 16.2 (p.9) **********/
    AD1CON2bits.VCFG = 0;       // VREFH=Avdd, VREFL=Avss (VCFG <2:0>)
    AD1CON2bits.CHPS = 0;       // Samples on CH0 (CHPS <1:0>)
    //AD1CON2bits.SMPI = 1;       // Interrupts on 1st Sample (SMPI <3:0>)
    AD1CON2bits.ALTS = 0;       // Always use MUXA Input Select
    AD1CON2bits.BUFM = 1;       // Dual 16-bit Buffer

    /********** ADxCON3: ADCx Control Register 16.3 (p.11) **********/
    // ADC Configuration for 1.1 Msps
    // ADC Clock Period (TAD) = TCY(ADCS + 1) = 75ns
    // ADCS = TAD/TCY - 1
    AD1CON3bits.ADRC = 0;           // Use Instruction Clock Cycle (ADRC <0>)
    AD1CON3bits.ADCS = 2;           // Set ADCS Control bits (ADCS <7:0>)

    /********** ADxCHS0: ADCx Input Channel 0 Select Register 16.6 (p.14) **********/
    // ANx Channel Input Select
    // Can be changed using SetChanIn()

    // AD1PCFGH/AD1PCFGL: Port Configuration Register
    AD1PCFGL = 0xFFFF;          // Clear all Ports
    AD1PCFGL = 0xFF3C;          // AN0,AN1,AN6,AN7 => Analog Input
                                // Rest Digital

    /********** Configure ADC Interrupts ***********/
    //IFS0bits.AD1IF = 0;         // Clear A/D Interrupt Flag Bit
    //IEC0bits.AD1IE = 1;         // Set the A/D Interrupt Enable Bit
}

void SetCH0In(char c)
{   
    AD1CHS0bits.CH0SA = c;
}

void EnableADC(void)
{   
    AD1CON1bits.ADON = 1;
}

void DisableADC(void)
{   
    AD1CON1bits.ADON = 0;
}

void StartSamp(void)
{
    AD1CON1bits.SAMP = 1;       // Start Sampling
}

void StopSamp(void)
{
    AD1CON1bits.SAMP = 0;       // Stop Sampling, Start Conversion
}

// Sensor Accessor Functions
unsigned int ReadFR(void)
{
    Sensors.FRNoise = SampNoise(FR_DET);
    FR_EMI = ON;
    return SampEmi(FR_DET)-Sensors.FRNoise;
}

unsigned int ReadFL(void)
{
    Sensors.FLNoise = SampNoise(FL_DET);
    FL_EMI = ON;
    return SampEmi(FL_DET)-Sensors.FLNoise;
}

unsigned int ReadSR(void)
{
    Sensors.FLNoise = SampNoise(SR_DET);
    SR_EMI = ON;
    return SampEmi(SR_DET)-Sensors.SRNoise;
}

unsigned int ReadSL(void)
{
    Sensors.SLNoise = SampNoise(SL_DET);
    SL_EMI = ON;
    return SampEmi(SL_DET)-Sensors.SLNoise;
}

unsigned int SampEmi(char chan)
{
    SetCH0In(chan);             // Set which Analog port to sample
    StartSamp();               
    __delay_ms(10);             // Sample Emitter for 10ms
    StopSamp();                 // Stop sampling, start conversion
    while(!AD1CON1bits.DONE);   // Wait for Conversion to finish
    return ADCBUF0;             // Return Sample Emitter
}

unsigned int SampNoise(char chan)
{
    SetCH0In(chan);              // Set which Analog port to sample
    EnableADC();                 // Enable ADC Module
    StartSamp();                 // Start Sampling
    __delay_us(10);              // Sample for 10us
    StopSamp();                 // Stop sampling, start conversion
    while(!AD1CON1bits.DONE);
    return ADCBUF0;             // Return Sampled Noise
}


/***************************************/
/******** END SENSOR FUNCTIONS *********/
/***************************************/


/***************************************/
/******** START ADC INTERRUPTS *********/
/***************************************/

// Converts Two Sets of Inputs Using Alternate Input Selections (Section 16 p.58)
// *Sampling and Converting a Single Channel Multiple Times (Section 16 p.52)

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
    //Clear the A/D Interrupt flag bit or else the CPU will
    //keep vectoring back to the ISR
    IFS0bits.AD1IF = 0;
}

/***************************************/
/********* END ADC INTERRUPTS **********/
/***************************************/



