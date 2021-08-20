# Monitor and Plotting

### read_port_slow_control.py  (formerly plot_slow_control.py)

The script `read_port_slow_control.py` creates the csv input file for `rtd_monitor_slow_control.py` 
which displays in a graph the value of the TOP, MID, BOT and OUT RTDs.

Before running these scripts:
- Make sure the serial Monitor of the Arduino IDE is not in use otherwise you will get the error message "Device or resource busy".
- Set the same name of the csv file in both scripts `read_port_slow_control.py` and `rtd_monitor_slow_control.py`.
- Select by entering the corresponding index of the serial port set in the arduino. On linux, usually is `/dev/ttyUSB0` or `/dev/ttyUSB1`.
```
    index        Port                 Device
---  2      /dev/ttyUSB0         USB2.0-Serial

```

###  rtd_monitor_slow_control.py  (formerly animated_plot_slow_control.py)

Wait a couple of secons ~5 to get suficient data in the input csv file before running this script.
While running the scripts, if you get the message:"Wrong number of columns at line xx", fix the format by editing the corresponding line in the csv file and rerun 
the script `rtd_monitor_slow_control.py` 



### oxygen_monitor_slow_control.py

It monitors the level of molecular oxygen (O2) in the nearby of the O2 sensor, if the O2 level is below a threshold set by the user.
A normal reading is ~3.3 (V) provided a proper supplied voltage.
A notification will be send to all the recipients listed in the file `config.yml` from the email account specified therein. 
The script `sender.py` includes the functionalities for doing this automated task.

Parameters to specify in the script:

Threshold for Oxygen level (float) : o2_threshold 

Set the corresponding credentials in the `config.yml` file before running the script.



`file_name.csv` is just a sample with the following structure: 

```    
    date    time    Oxy        RTDTop RTDBot RTDMid RTDOut 
     Ch0     Ch1    Ch2  Ch3   Ch4    Ch5    Ch6    Ch7
     
17/08/2021 09:15:34 3.33 space 108.88 29.78  110.81 8.64
```

NOTICE that the order of the RTDs depends on how they are located in the cage. this can be fixed in the code if any inconsistency. 





Monitoring scripts are an adaptation of Ilker Parmaksiz's original script 'AnimatedPlot.py'. 

Automated notification code based on GitHub repo RodolfoFerro/arduino-mail-sender.
