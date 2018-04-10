import urllib2
#import os
#import requests

def sendDataToServer():
	#temp = "23"
	#humi = "12"
	#id2 = "2"

	temp = input("Enter Temperature: ")
	humi = input("Enter Humidity: ")
	id2 = input("Enter ID: ")

	temp = str(temp)
	humi = str(humi)
	id2 = str(id2)

	#temp= "%.1f" %temperature:
	#hum ="%.1f" %humidity
	#id2 = "%" %id23
	string = "http://www.lonelycircuits.se/data/add_data.php?temp="+temp+"&humi="+humi+"&id="+id2
	#print (string)
	#requests.get("http://www.lonelycircuits.se/data/add_data.php?temp="+temp+"&humi="+humi+"&id="+id2)
	urllib2.urlopen(string)
					#http://www.lonelycircuits.se/data/add_data.php?temp=XX&humi=XX&id=XX

sendDataToServer()
print ("OK")
