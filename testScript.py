import urllib2
import os

def sendDataToServer():
	 temperature = 23
	 humidity = 12
	 id23 = 2

    temp= "%.1f" %temperature
	hum ="%.1f" %humidity
	id2 = "%" %id23

	urllib2.urlopen("http://www.lonelycircuits.se/add_data.php?temp="+temp+"&humi="+humi+"&id="+id2).read()

sendDataToServer()
