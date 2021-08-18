int SensPinT = A1 ; // Inner Top RTD- black
int SensPinB = A2 ; // Inner Bot RTD- orange
int SensPinM = A3 ; // Inner Mid RTD- brown //purple cable is 5V
int SensPinOut = A5 ; //Outer RTD reading it through a jumper from the other board, no resistor needed

int SensPinOxy = A7 ; //Oxygen Sensor  


#include "Sensor_Control.h" 
#include "Commands.h"

Sensor_Control Sens = Sensor_Control();
Commands Commander = Commands();


int counter = 0;
float SensValTop = 0; // For Inner RTDs
float SensValMid = 0;
float SensValBot = 0;
float SensValOut = 0;// For Outer RTD
float SensValOxy = 0;
 
String incoming = "";   // for incoming serial string data

void setup()
{
  Serial.begin(9600);
  /*pinMode(Pulse,OUTPUT);
  pinMode(Dir,OUTPUT);
  pinMode(ENG,OUTPUT);
  digitalWrite(Dir,LOW);
  digitalWrite(ENG,LOW);
  */
}

void loop()
{

//Analog Reading
  SensValOxy = analogRead(SensPinOxy);
  SensValOxy=(5*SensValOxy)/1024; //Converting to voltage 3.2V normal O2 level provided 5V suplied
  //Serial.print("Oxygen Sensor Value (Normal 3.3 V): ");
  Serial.print(SensValOxy);
  Serial.print(" ");


  
//Monitoring Inner RTD's
  SensValTop = Sens.Measure(SensPinT);
  //Serial.print("Top RTD Sensor Value: ");
  Serial.print(" ");
  Serial.print(SensValTop);
  Serial.print(" ");
  SensValMid = Sens.Measure(SensPinM);
  //Serial.print("Mid RTD Sensor Value: ");
  Serial.print(SensValMid);
  Serial.print(" ");
  SensValBot = Sens.Measure(SensPinB);
  //Serial.print("Bot RTD Sensor Value: ");
  Serial.print(SensValBot);
  Serial.print(" ");
  
  //Monitoring Outer RTD
  SensValOut = Sens.Measure(SensPinOut);
  Serial.println(SensValOut);

  
  delay(50);

  
  incoming = Commander.Check_Serial();
  Serial.println(incoming);

}

//  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
//  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
