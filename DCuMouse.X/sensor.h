#ifndef SENSOR_H
#define	SENSOR_H

#define TAD 0.000000075 // Minimum ADC Clock Period 75ns
#define TCONV 12*TAD    // ADC Conversion Time

#define ADCFR 0         // AN0 Front Right ADC
#define ADCFL 6         // AN6 Front Left ADC
#define ADCSR 1         // AN1 Side Right ADC
#define ADCSL 7         // AN7 Side Left ADC

#define Front PORTA
#define EmFR 0
#define EmFL 6
#define EmSR 1
#define EmSL 7

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
void StartSamp(void);
void StopSamp(void);

// Sensor Accessor Functions
unsigned int ReadFR(void);
unsigned int ReadFL(void);
unsigned int ReadSR(void);
unsigned int ReadSL(void);

// Emitter Functions
void OnFR(void);
void OnFL(void);
void OnSR(void);
void OnSL(void);

// Samples and Convert Emitter Values
void ADCDone(char d);

#endif	/* SENSOR_H */
