from serial.tools.list_ports import comports
from serial.tools import hexlify_codec
import sys

def tempcheck(vdef):    
    if vdef<0 & vdef>2.4:
      send(fromemail,toemail,message)
#function who take cares of emailing
#from send import *
#def send(femail,number,message):
  #  server.sendmail(femail,number,message)
  #  print("Successful Text message")
    
#this function finds available ports
def ask_for_port():
    """\
    Show a list of ports and ask the user for a choice. To make selection
    easier on systems with long device names, also allow the input of an
    index.
    """
    
    print("\n\033[1;31;47m ---  Currently available devices to readout:\033[0m \n")
    ports = []
    global index
    for n, (port, desc, hwid) in enumerate(sorted(comports()), 1):
        sys.stderr.write('    {:7}      {:20} {}\n'.format("index","Port","Device"))
        sys.stderr.write('--- {:2}      {:20} {}\n\n\n\n\n'.format(n, port, desc))
        ports.append(port)
    if(len(ports)==0):
       print("\n\033[1;31;47m --- There are no ports available ---\033[0m \n") 
    while True:
        pr = input('--- Enter port index: ')
        try:
            index = int(pr) - 1
            if not 0 <= index < len(ports):
                sys.stderr.write('--- Invalid index!\n')
                continue
            
        except ValueError:
           ask_for_port()
            
        port=ports[index]
        return port
def name(i):
	if (i == 0):
		name = "Temperature"
	elif (i == 1):
		name = "Presssure"
	else:
		name = "Humidity"
	return name
def tag(i):
	if (i == 0):
		tag = 'left', 'Temperature', 'K'
	elif (i == 1):
		tag = 'left', 'Pressure', 'hPa'
	else:
		tag = 'left', 'Humidity', '%'
	return tag
