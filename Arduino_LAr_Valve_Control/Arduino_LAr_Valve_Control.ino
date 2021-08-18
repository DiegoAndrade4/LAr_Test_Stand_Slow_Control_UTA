#define Pulse 9 // D9
#define Dir 8   // D8
#define ENG 12  // D12

#define Relay 2 // D2
#define Data 7 // D7 


int SensPinL = A7 ;   // Outter RT for monitoring the Level of LAr


#include "Motor_Control.h"
#include "Sensor_Control.h"
#include "Commands.h" 

Motor_Control Moto  = Motor_Control();
Sensor_Control Sens = Sensor_Control();
Commands Commander = Commands();


int counter = 0;
unsigned long Arduno_time;
unsigned long Last_time = 1;
//unsigned long TimeSinceFill  = 1;

const unsigned long FiveSec = 5000;         //the value is a number of milliseconds
const unsigned long TenSec = 10000;         
const unsigned long OneMinute = 60000;      
const unsigned long TwoMinute = 120000;
const unsigned long ThreeMinute = 180000;   
const unsigned long FiveMinute =  300000;  
const unsigned long TenMinute = 600000;    
const unsigned long FortyMinute = 2400000; 

unsigned long TimeSinceFill  = TenMinute;


bool is_valve_open = false;
bool is_switch_on = false;
bool is_taking_data = false;

float SensVal = 0;

String incoming = "";   // for incoming serial string data

void setup()
{
  Serial.begin(9600);
  pinMode(Pulse,OUTPUT);
  pinMode(Dir,OUTPUT);
  pinMode(ENG,OUTPUT);
  pinMode(Relay,OUTPUT);
  pinMode(Data,OUTPUT);
  digitalWrite(Dir,LOW);
  digitalWrite(ENG,LOW);
  digitalWrite(Relay,LOW);
  digitalWrite(Data,LOW);
}

void loop()
{
  Arduno_time = millis(); // current time
  TimeSinceFill = Arduno_time - Last_time;

//Monitoring LAr Level  
  SensVal = Sens.Measure(SensPinL);
  //Serial.print("LAr Level Sensor Value: ");
 
  Serial.print(SensVal);
   
  delay(50);

  
  incoming = Commander.Check_Serial();
  Serial.println(incoming);

  
  // main function
  if (incoming == "start\n")
  {     
    if ( (SensVal > 25 ) && (TimeSinceFill > ThreeMinute) )
    {
      //Moto.StopData();
      //Moto.EnableRelaySwitch();
      //delay(TenSec);
      is_valve_open = true;
      Serial.print("Starting a fill [time]: ");
      Serial.println(Arduno_time);
      Last_time = Arduno_time;
      is_taking_data = Moto.StopData();
      is_switch_on = Moto.EnableRelaySwitch();
      Moto.Open_Valve();
      Serial.print("Filling...\n");
      delay(FiveMinute); 
      Serial.print("Filling Done.\n");
      is_valve_open = false;
      Moto.Close_Valve();
      is_switch_on = Moto.DisableRelaySwitch();
      is_taking_data = Moto.StartData();
      //delay(FiveSec);
      //Moto.DisableRelaySwith();
      //delay(FiveSec);
      //Moto.StartData();     
    }
  
  }
  // open valve
  else if (incoming == "open\n")
  {
    if (!is_valve_open)
    {
      is_valve_open = true;
      Serial.print("Opening valve [time]: ");
      is_taking_data = Moto.StopData();
      is_switch_on = Moto.EnableRelaySwitch();
      Serial.println(Arduno_time);
      Moto.Open_Valve();   
    }
  }
  // close valve
  else if (incoming == "close\n")
  {
    if (is_valve_open)
    {
      is_valve_open = false;
      Serial.print("Closing valve [time]: ");
      Serial.println(Arduno_time);
      Moto.Close_Valve();
      is_switch_on = Moto.DisableRelaySwitch();
      is_taking_data = Moto.StartData();
      
    }
  }
  // test
  else if (incoming == "test\n")
  {     
      Moto.TEST_MOTOR();
  }
 // status
  else if (incoming == "status\n")
  {     
      if (is_valve_open == true)
        Serial.print("Valve is open\n");
      else
        Serial.print("Valve is closed\n");
      if (is_switch_on == true)
        Serial.print("Switch is ON\n");
      else
        Serial.print("Switch is OFF\n");
      if (is_taking_data == true)
        Serial.print("Data taking in course.\n");
      else
        Serial.print("Not taking data now.\n");
  }
  
  else if (incoming == "valve_status\n")
  {
      if (is_valve_open == true)
       Serial.print("Valve is open\n");
      else
       Serial.print("Valve is closed\n");
  }
  
  else if (incoming == "switch_status\n")
  {
      if (is_switch_on == true)
      Serial.print("Switch is ON\n"); 
      else
      Serial.print("Switch is OFF\n");
  }
  
  else if (incoming == "data_status\n")
  {
   if (is_taking_data == true)
      Serial.print("Data taking in course.\n");
   else
      Serial.print("Not taking data now.\n");
  }
  
  else if (incoming == "switch_on\n")
  {
      is_switch_on = Moto.EnableRelaySwitch();
    
  }
    else if (incoming == "switch_off\n")
  {
      is_switch_on = Moto.DisableRelaySwitch();   

  }

  else if (incoming == "data_start\n")
  {
      Serial.print("Resuming data adquisition.\n");
      is_taking_data = Moto.StartData();
  }

    else if (incoming == "data_stop\n")
  {
      Serial.print("Stopping data adquisition.\n");
      is_taking_data = Moto.StopData();
  }
  
  else 
  {
     Serial.print("Enter a valid command.\n");   
     delay(50);
  }
  
}

//  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
//  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
