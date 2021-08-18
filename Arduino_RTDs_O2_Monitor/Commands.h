#ifndef Commands_h
#define Commands_h 1
#include <Arduino.h>

//===============================================
// Class for controling the sensor
class Commands
{
private:
    //====================================================
    String readString;
    String returnString;
    
public:
    //====================================================
    String Check_Serial();
    
  
};

#endif