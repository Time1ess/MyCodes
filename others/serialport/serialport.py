import serial
import thread
import urllib2
import sys
import time

ser=serial.Serial('COM3',38400)
#i=1
while True:
    data=ser.readline()
    #print i
    #i=i+1
    print data
    temp=data[5:12]
    humidity=data[22:29]
    val='http://1.time1esswx.sinaapp.com/updatedata.php?nowtemp=%s&&nowhumidity=%s'%(temp,humidity)
    #print val
    #add data to U in php get way,and simulate to access
    try:
        urllib2.urlopen(val)
    except KeyboardInterrupt:
        sys.exit('\nMission aborted.')
