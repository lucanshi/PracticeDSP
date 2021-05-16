#ifndef __ANALOGSENSOR_H__
#define __ANALOGSENSOR_H__
#include <Arduino.h>

enum measurement
{
    DIGITAL_LEVEL,
    SENSOR_MEASUREMENT
};

class AnalogSensor
{
private:
    
    uint8_t _pin;
    float(*_equation)(float,float[],uint8_t);
    float *_coeff;
    uint8_t _num_coeff;

public:
    AnalogSensor();
    ~AnalogSensor();
    void setup(const uint8_t pin, float(*equation)(float,float[],uint8_t),float coeff[], uint8_t num_coeff);
    float read();
    float getMeasurement(measurement type=DIGITAL_LEVEL);

protected:
    uint16_t _digital_level;
    float _sensor_measurement;
};

#endif // __ANALOGSENSOR_H__