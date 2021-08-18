
// Motor include
#include "Motor_Control.h"
#define Pulse 9
#define Dir 8
#define ENG 12

#define Relay 2 
#define Data 7 

// Arduino specific includes
#include <Arduino.h>




//===============================================
// Class for controling the stepper

//====================================================
double Motor_Control::Step_Time()
{
    return (Seconds_Per_Turn/Steps_Per_Turn)*1000; // in ms
}

//====================================================
void Motor_Control::Set_Steps_Per_Turn(double Steps_Per_Turn_)
{
    Steps_Per_Turn = Steps_Per_Turn_;
}
//====================================================
void Motor_Control::Set_Seconds_Per_Turn(double Seconds_Per_Turn_)
{
    Seconds_Per_Turn = Seconds_Per_Turn_;
}

//=======================================================
bool Motor_Control::EnableRelaySwitch()
{    
   digitalWrite(Relay,HIGH);
   delay(3000);
   Serial.print("Switch enabled, closed circuit, pin status ");
   Serial.println(digitalRead(Relay));
   
   return true ; // it answers to is_switch_on
}

//=======================================================
bool Motor_Control::DisableRelaySwitch()
{    
   digitalWrite(Relay,LOW);
   delay(3000);
   Serial.print("Switch disabled, open circuit, pin status ");
   Serial.println(digitalRead(Relay));

   return false ; // it answers to is_switch_on
  
  
}
//=======================================================
bool Motor_Control::StopData()
{    
   digitalWrite(Data,HIGH);
   Serial.print("Data taking stopped, pin status ");
   Serial.println(digitalRead(Data));

   return false;  //it answers to is_taking_data 
  
}
//=======================================================
bool Motor_Control::StartData()
{    
   digitalWrite(Data,LOW);
   Serial.print("Resuming Data taking, pin status ");
   Serial.println(digitalRead(Data));

   return true;  //it answers to is_taking_data 
}
//=======================================================


//====================================================
void Motor_Control::LeftyLoosy()
{
    digitalWrite(Dir,LOW);
    for (int i=0; i<Steps_Per_Turn; i++)
    {
        digitalWrite(Pulse,HIGH);
        delay(Step_Time());
        digitalWrite(Pulse,LOW);
    }
}

//====================================================
void Motor_Control::RightyTighty()
{   
    digitalWrite(Dir,HIGH);
    for (int i=0; i<Steps_Per_Turn; i++)
    {
        digitalWrite(Pulse,HIGH);
        delay(Step_Time()); 
        digitalWrite(Pulse,LOW);
        
    }
}


//====================================================
void Motor_Control::Open_Valve()
{
    //StopData();
   // EnableRelaySwitch();
   // delay(10000);   
    Serial.print("Opening the valve...\n");
    LeftyLoosy();
    delay(250);
    LeftyLoosy();
    delay(250);
    LeftyLoosy();
    Serial.print("Valve open.\n");
    
}

//====================================================
void Motor_Control::Close_Valve()
{
    Serial.print("Closing the valve...\n");
    RightyTighty();
    delay(250);
    RightyTighty();
    delay(250);
    RightyTighty();
    Serial.print("Valve Closed.\n");
  //  delay(5000);
  //  DisableRelaySwitch();
  //  delay(5000);
  //  StartData();    
   
}

void Motor_Control::TEST_MOTOR()
{ 
  /*  delay(250);
    LeftyLoosy();
    delay(500);
    RightyTighty();
    delay(250);
    */
      Serial.print("Starting the test.\n");
/*    Open_Valve();
    delay(7000);
    Close_Valve();
*/    Serial.print("End of the test.\n");

digitalWrite(Pulse,HIGH);
digitalWrite(Dir,HIGH);
digitalWrite(Relay,HIGH);
digitalWrite(Data,HIGH);
delay(2000);
digitalWrite(Pulse,LOW);
digitalWrite(Dir,LOW);
digitalWrite(Relay,LOW);
digitalWrite(Data,LOW);

    
}

//======================================================
void Motor_Control::TEST_MOTOR_Lefty()
{
    delay(1000);
    LeftyLoosy();
    delay(1000);
 
}

//======================================================
void Motor_Control::TEST_MOTOR_Righty()
{
    delay(1000);
    RightyTighty();
    delay(1000);
}
//=====================================================

  
