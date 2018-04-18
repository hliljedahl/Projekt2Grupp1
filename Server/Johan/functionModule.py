import sre, urllib2, sys, BaseHTTPServer

def parseAddress(input):
        if input[:7] != "http://":
                if input.find("://") != -1:
                        print "Error: Cannot retrive URL, address must be HTTP"
                        sys.exit(1)
                else:
                        input = "http://" + input

        return input

def retrieveWebPage(address):
        try:
                web_handle = urllib2.urlopen(address)
        except urllib2.HTTPError, e:
                error_desc = BaseHTTPServer.BaseHTTPRequestHandler.responses[e.code][0]
                #print "Cannot retrieve URL: " + str(e.code) + ": " + error_desc
                print "Cannot retrieve URL: HTTP Error Code", e.code
                sys.exit(1)
        except urllib2.URLError, e:
                print "Cannot retrieve URL: " + e.reason[1]
                sys.exit(1)
        except:
                print "Cannot retrieve URL: unknown error"
                sys.exit(1)
        return web_handle
