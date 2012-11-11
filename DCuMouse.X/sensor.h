#ifndef SENSOR_H
#define	SENSOR_H

#define TAD 0.000000075 // Minimum ADC Clock Period 75ns

#define ADCFR 0         // AN0 Front Right ADC
#define ADCFL 6         // AN6 Front Left ADC
#define ADCSR 1         // AN1 Side Right ADC
#define ADCSL 7         // AN7 Side Left ADC

struct ADC {
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

// Sensor Accessor Functions
unsigned int ReadFR(void);
unsigned int ReadFL(void);
unsigned int ReadSR(void);
unsigned int ReadSL(void);

// Samples and Convert Emitter Values
void ADCDone(char d);

#endif	/* SENSOR_H */
