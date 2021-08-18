#ifndef Sensor_Control_h
#define Sensor_Control_h 1

//===============================================
// Class for controling the sensor
class Sensor_Control
{
private:
    //====================================================
    int raw = 0;
    int Vin = 5; // Volts
    float Vout = 0;
    float R1 = 220; //Ohms
    float R2 = 0;
    float buffer = 0;
    
public:
    //====================================================
    float Read_Value();
    float Measure();

    float Read_Value(int pin);
    float Measure(int pin);

};

#endif
