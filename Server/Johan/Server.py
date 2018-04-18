
import urllib2, functions.self

IP = '192.168.1.184' # write the url here

url = parseAddress(IP)

usock = urllib2.urlopen(url)
data = usock.read()
usock.close()

print data

#input.find(":" value)
#print value
