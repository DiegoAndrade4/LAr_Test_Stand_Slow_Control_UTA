// Motor include
#include "Sensor_Control.h"
//#define SensPinO A0  // Outer RTD
//#define SensPinT 6  // Inner Top RTD
//#define SensPinM 5  // Inner Mid RTD
//#define SensPinB 4  // Inner Bot RTD


// Arduino specific includes
#include <Arduino.h>

//====================================================
float Sensor_Control::Read_Value(int pin)
{
    raw = analogRead(pin);
    buffer = raw * Vin;
    Vout = (buffer)/1024.0;
    buffer = (Vin/Vout) - 1;
    R2= R1 * buffer;
    return R2;
}

//====================================================
float Sensor_Control::Measure(int pin)
{
    int count = 0;
    float Value = 0.0;
    for (int i=0; i<10; i++)
    {
        count += 1;
        Value += Read_Value(pin);
        delay(100);
    }
    Value /= count;
    return Value;
}
