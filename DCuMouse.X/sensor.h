/* 
 * File:   sensor.h
 * Author: Brylian Foronda
 *
 * Created on November 2, 2012, 2:41 PM
 */

#ifndef SENSOR_H
#define	SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

class Sensor
{
public:
    Sensor();
    ~Sensor();

    // ADC Constructor
    void InitADC();
    
    // Accessors
    // Get sensor ADC Values
    unsigned int GetFR();
    unsigned int GetFL();
    unsigned int GetSR();
    unsigned int GetSL();

    // Mutators
    // Set sensor values from ADC
    SetFR(unsigned int s);
    SetFL(unsigned int s);
    SetSR(unsigned int s);
    SetSL(unsigned int s);

private:
    // Private variables for storing ADC Values
    unsigned int FrontRight;
    unsigned int FrontLeft;
    unsigned int SideRight;
    unsigned int SideLeft;
    
    const int EmitterDelay;
}

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */
