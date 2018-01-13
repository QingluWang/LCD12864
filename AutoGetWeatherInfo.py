#!/usr/bin/env python

import urllib
import urllib2
import json

url = "http://www.weather.com.cn/data/cityinfo/101120201.html"
req = urllib2.Request(url)
req_data = urllib2.urlopen(req)
res = req_data.read()
weatherObj = json.loads(res)
temp1Str = weatherObj["weatherinfo"]["temp1"]
temp2Str = weatherObj["weatherinfo"]["temp2"]
temp1RealStr = temp1Str[0:len(temp1Str) - 1]
temp2RealStr = temp2Str[0:len(temp2Str) - 1]
print temp1RealStr
print temp2RealStr
print len(weatherObj["weatherinfo"]["weather"])