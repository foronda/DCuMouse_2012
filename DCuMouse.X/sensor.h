#ifndef SENSOR_H
#define	SENSOR_H

#define TAD 0.000000075 // Minimum ADC Clock Period 75ns
#define TCONV 12*TAD    // ADC Conversion Time

#define ON 1
#define OFF 0

#define FR_DET 0         // AN0 Front Right ADC
#define FL_DET 7         // AN7 Front Left ADC
#define SR_DET 1         // AN1 Side Right ADC
#define SL_DET 6         // AN6 Side Left ADC

#define Front PORTA
#define SR_EMI PORTAbits.RA9
#define SL_EMI PORTAbits.RA4
#define FL_EMI PORTBbits.RB4
#define FR_EMI PORTAbits.RA8 

struct ADC {
    unsigned int FRNoise; // Front Right Detector
    unsigned int FLNoise; // Front Left Detector
    unsigned int SRNoise; // Side Right Detector
    unsigned int SLNoise; // Side Left Detector

    unsigned int FR; // Front Right Detector
    unsigned int FL; // Front Left Detector
    unsigned int SR; // Side Right Detector
    unsigned int SL; // Side Left Detector
};

// ADC Configuration
void InitADC(void);
void SetCH0In(char c); // Sets which AN port to sample on CH0
void EnableADC(void);
void DisableADC(void);
void StartSamp(void);
void StopSamp(void);

// Sensor Accessor Functions
unsigned int ReadFR(void);
unsigned int ReadFL(void);
unsigned int ReadSR(void);
unsigned int ReadSL(void);

// Sensor Mutator Functions
unsigned int LinearizeFR(unsigned int adc);
float LinearizeSR(unsigned int adc);
float LinearizeFL(unsigned int adc);
float LinearizeSL(unsigned int adc);

// Emitter Helper Functions
unsigned int SampNoise(char chan);
unsigned int SampEmi(char chan);
void CalibrateSensors(void);

// Samples and Convert Emitter Values
void ADCDone(char d);


#endif	/* SENSOR_H */
