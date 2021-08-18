import matplotlib as pl
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.dates import datestr2num
import matplotlib.ticker as plticker
import matplotlib.animation as animation
from matplotlib import style
import matplotlib.dates as mdates

import os
import time
import datetime as dt

from sender import Notify #To notify

#style.use('fivethirtyeight')
#O2 sensor parameters 
o2_threshold = 1.00
print(o2_threshold)

### Make a figure ###
fig2 = plt.figure()

###ax2 = plt.subplots(1)

#these are subplot grid parameters encoded as a single integer. 
#For example, "111" means "1x1 grid, first subplot" and "234" means "2x3 grid, 4th subplot".
ax1 = fig2.add_subplot(111)
#ax2 = fig1.add_subplot(222)
#ax3 = fig1.add_subplot(223)
#ax4 = fig1.add_subplot(224)
fig2.autofmt_xdate()
def animate(i):
#---------------------------------------------------------------------------------------------------------------
	last_time = 0.
	notification_interval = 120. #It must be a float number given in seconds
	time_since_notification = notification_interval+ 1.
	aux_time_since_notification = 122.
	
	RangeData = np.loadtxt('file_name.csv', delimiter=' ', skiprows=14, dtype=str)
	#last_time =1.0 
	### Load the time stamp into an array ####
	xRange = np.arange(len(RangeData[:,0]))
	dates=[]
	for i in range(len(RangeData[:,0])):
		curr = RangeData[:,0][i]+' '+RangeData[:,1][i]  
		tmp = dt.datetime.strptime(curr, '%d/%m/%Y %H:%M:%S')
		dates.append(tmp)
	dates = np.array(dates)
	xRange = dates
	

	#xRange = [dt.datetime.strptime(M,"%d/%m/%Y %H:%M:%S").date() for M in dates]
	print(RangeData)

	Ch3 = RangeData[:,2].astype(float) # Oxygen sensor readout
	
	### Convert the range from a string to a float ###
	#Ch0 = Ch0.astype(np.float)
	ax1.clear()
	ax1.set_xlabel('time')
	#ax1.set_ylim([0,1000])
	ax1.set_title('Oxygen Level')
	ax1.set_ylabel('Oxygen sensor readout (V)')
	
	xfmt = mdates.DateFormatter("%d/%m/%Y %H:%M:%S")
	minuets = mdates.MinuteLocator(interval = 10)
	ax1.xaxis.set_major_formatter(xfmt)
	#ax1.xaxis.set_major_locator(minuets)
	
	plt.gcf().autofmt_xdate()
	
	ax1.plot(xRange, Ch3, label="Oxygen")
	
	
	ax1.legend(loc='upper right')
	
	
	
	#localtime=time.asctime(time.localtime(time.time()))

	if Ch3[i] < o2_threshold and time_since_notification > notification_interval :
		print("i = ", i ," Alert-Low Oxigen Level")
		Notify()# Send notification by email 
		last_time=time.time()
		time.sleep(1)
		aux_time_since_notification = time.time()-last_time
		

ani = animation.FuncAnimation(fig2, animate, interval = 5000)

mng = plt.get_current_fig_manager()
#mng.window.showMaximized()

plt.show()

	

