
import urllib2
from functionModule import parseAddress, retrieveWebPage
from time import sleep

IP = '192.168.1.221' # write the url here

url = parseAddress(IP)
address = retrieveWebPage(url)

usock = urllib2.urlopen(url)
data = usock.read()
usock.close()

dataArray = data.split(":")

temp = dataArray[1]
hum = dataArray[3]
heat = dataArray[5]
temp2 = dataArray[7]

print "Temperature : " + temp +"C"
print "Humidity : " + hum +"%"
print "Heat index : "+ heat + "C"
print "Temperature 2 : "+ temp2 + "C"

urlTemp = "http://www.lonelycircuits.se/data/add_value.php?name=JohanTemp&value=" + temp
urlHumi = "http://www.lonelycircuits.se/data/add_value.php?name=JohanHumi&value=" + hum
urlTemp2 = "http://www.lonelycircuits.se/data/add_value.php?name=JohanHumi&value=" + temp2

HumiSend = urllib2.urlopen(urlHumi)
HumiSend.close()
sleep(1)
TempSend = urllib2.urlopen(urlTemp)
TempSend.close()
sleep(1)
TempSend2 = urllib2.urlopen(urlTemp2)
TempSend2.close()
sleep(1)
