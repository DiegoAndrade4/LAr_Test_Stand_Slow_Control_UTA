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


### Make a figure ###
fig1 = plt.figure()

#localtime = time.localtime(time.time())
#localtime = time.asctime( time.localtime(time.time()) )
###ax2 = plt.subplots(1)


#these are subplot grid parameters encoded as a single integer. 
#For example, "111" means "1x1 grid, first subplot" and "234" means "2x3 grid, 4th subplot".
ax1 = fig1.add_subplot(111)
#ax2 = fig1.add_subplot(222)
#ax3 = fig1.add_subplot(223)
#ax4 = fig1.add_subplot(224)
fig1.autofmt_xdate()
def animate(i):
#---------------------------------------------------------------------------------------------------------------
	
	
	#RangeData = np.loadtxt('RTD_Data_NitrogenTest.csv', delimiter=' ', skiprows=2, dtype=str)
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
	### Load the distance (in cm) into an array ###
	Ch0 = RangeData[:,4].astype(float) # Inner RTD's
	Ch1 = RangeData[:,5].astype(float)
	Ch2 = RangeData[:,6].astype(float)
	Ch3 = RangeData[:,2].astype(float) # Oxygen sensor readout
	Ch4 = RangeData[:,7].astype(float) # Outer RTD, the input is taken from the other arduino board
	
	### Convert the range from a string to a float ###
	#Ch0 = Ch0.astype(np.float)
	ax1.clear()
	ax1.set_xlabel('time')
	#ax1.set_ylim([0,1000])
	ax1.set_ylabel('RTD value')
	ax1.set_title('RTDs readout')
	
	xfmt = mdates.DateFormatter("%d/%m/%Y %H:%M:%S")
	minuets = mdates.MinuteLocator(interval = 10)
	ax1.xaxis.set_major_formatter(xfmt)
	#ax1.xaxis.set_major_locator(minuets)
	
	plt.gcf().autofmt_xdate()
	
	ax1.plot(xRange, Ch0, label="TOP", marker='o')
	ax1.plot(xRange, Ch2, label="MID", marker='o')
	ax1.plot(xRange, Ch1, label="BOT", marker='o')
	ax1.plot(xRange, Ch4, label="OUT", marker='o')
	
	ax1.legend(loc='upper right')
	
	
	
	
	
ani = animation.FuncAnimation(fig1, animate, interval = 5000)

mng = plt.get_current_fig_manager()
#mng.window.showMaximized()

plt.show()

	

