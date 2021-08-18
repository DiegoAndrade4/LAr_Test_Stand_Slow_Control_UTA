# Arduino_LAr_Valve_Control


Supported commands on Arduino IDE Serial Monitor (lower-case) 

General
	- start         -- Open/close the valve according to RTD feedback
	- status        -- Status of the valve, switch and data adquisition
	- test 		-- Debugging purposes
Valve
	- open
	- close
	- valve_status
Switch
	- switch_on
	- switch_off
	- switch_status
DAQ
	- data_start
	- data_stop
	- data_status



switch_on -> Enable the relay -> closes the circuit to power supply the motor
switch_off-> Opens the circuit-> no power supply

data_stop -> Set to HIGH digital pin -> Oscilloscope stops data aquisition  
data_start-> Set to LOW  digital pin -> Oscilloscope resumes data adquisition


Input voltage and resistor values must be set in the Sensor_Control.h 













This project is based on the GitHub repo AustinMcDonald/ LAr_Valve_Control
