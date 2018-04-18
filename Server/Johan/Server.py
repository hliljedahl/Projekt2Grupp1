
import urllib2
from functionModule import parseAddress, retrieveWebPage

IP = '192.168.1.184' # write the url here

url = parseAddress(IP)
address = retrieveWebPage(url)

usock = urllib2.urlopen(url)
data = usock.read()
usock.close()

print data

#input.find(":" value)
#print value
