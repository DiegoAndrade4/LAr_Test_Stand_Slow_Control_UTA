from serial import Serial # import Serial Library
import numpy  # Import numpy
import re
import glob
import matplotlib.pyplot as plt #import matplotlib library
#from drawnow import *
from functions import *
from datetime import datetime

#file=open("RTD_Nitrogen_Test_04_06_21.csv","a+")
file=open("file_name.csv","a+")

RTD=[]
show=0
arduinoData = Serial(ask_for_port() , 9600,timeout=None) #Creating our serial object named arduinoData
plt.ion() #Tell matplotlib you want interactive mode to plot live data
cnt=0
#responsible for graphing
def makeFig(): #Create a function that makes our desired plot
    plt.title('RTD Plotting')      #Plot the title
    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('Voltage (V)')                            #Set ylabels
    plt.xlabel('Time(s)')
    plt.legend()                    #plot the legend
count=0

while True: # While loop that loops forever
    try:
       while (arduinoData.inWaiting()==0): #Wait here until there is data
          if(show==0):
             print("\n\033[1;31;40m Waiting to Receive Data from Arduino....\033[0m \n")
             print("\033[1;31;47m Press CTRL+C to CANCEL waiting\033[0m  \n")
             show=1
          pass
    except KeyboardInterrupt:
       file.close()
       break

    now= datetime.now()
    DataFromArduino=arduinoData.readline().decode("ascii")
    Splited=DataFromArduino.split(" ")

    dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
    arduinoString = dt_string +" "+ str(DataFromArduino) #read the line of text from the serial port
    if(len(Splited)>=3 and DataFromArduino!=None):
      file.write(arduinoString)
      file.write("\n")
      file.flush()
      print (arduinoString)
       #dataArray = arduinoString.split(' ')  #Split it into an array called dataArray

     
       #drawnow(makeFig)                       #Call drawnow to update our live graph
     
