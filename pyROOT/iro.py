#!/usr/bin/env python

'''
Instructions:
Launch this python ROOT (pyROOT) script with:
./iro.py 

Examine the resultant output with:
open iro.png

'''

#================================================================================================
# Imports
#================================================================================================
import ROOT
import numpy
import re


#================================================================================================
# Definitions
#================================================================================================
batchMode      = True
includeMaxLine = True
includeTypLine = False
addDayLines    = False
addWeekLines   = True
addMonthLines  = True
xMin           =   0
yMin           =   0
yMax           = 1000
babyMass       = 5.0 # kg
dailyMinPerKg  = 100 # ml per kg per day
dailyMaxPerKg  = 150 # ml per kg per day

#================================================================================================
# Variable Definition
#================================================================================================
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) # Default is: 000001111
ROOT.gROOT.SetBatch(batchMode)


#================================================================================================
# Function Definition
#================================================================================================
def main():

    # Dictioary mapping timestamp to milk volume
    timeToVolumeDict = {}
    timeToVolumeDict["0:11:00"]  = 50
    timeToVolumeDict["0:14:40"]  = 60
    timeToVolumeDict["0:18:00"]  = 65
    timeToVolumeDict["0:21:00"]  = 60
    timeToVolumeDict["0:24:00"]  = 65

    timeToVolumeDict["1:03:00"]  = 65
    timeToVolumeDict["1:06:00"]  = 60
    timeToVolumeDict["1:09:00"]  = 65
    timeToVolumeDict["1:12:00"]  = 40
    timeToVolumeDict["1:14:30"]  = 35
    timeToVolumeDict["1:16:50"]  = 30
    timeToVolumeDict["1:20:00"]  = 50
    timeToVolumeDict["1:23:00"]  = 50

    timeToVolumeDict["2:02:15"]  = 50
    timeToVolumeDict["2:05:15"]  = 25
    timeToVolumeDict["2:09:42"]  = 30
    timeToVolumeDict["2:12:00"]  = 25
    timeToVolumeDict["2:15:50"]  = 40
    timeToVolumeDict["2:19:00"]  = 50
    timeToVolumeDict["2:22:50"]  = 60

    timeToVolumeDict["3:02:00"]  = 52
    timeToVolumeDict["3:05:00"]  = 45
    timeToVolumeDict["3:07:30"]  = 55
    timeToVolumeDict["3:10:30"]  = 50
    timeToVolumeDict["3:13:15"]  = 40
    timeToVolumeDict["3:15:45"]  = 50 #* vomited about 5-10 ml
    timeToVolumeDict["3:18:45"]  = 40
    timeToVolumeDict["3:21:45"]  = 55 #* vomited about 10-15 ml

    timeToVolumeDict["4:00:45"]  = 30
    timeToVolumeDict["4:03:45"]  = 50
    timeToVolumeDict["4:06:25"]  = 40
    timeToVolumeDict["4:09:20"]  = 40
    timeToVolumeDict["4:11:50"]  = 40
    timeToVolumeDict["4:15:15"]  = 50
    timeToVolumeDict["4:17:45"]  = 30
    timeToVolumeDict["4:20:20"]  = 40
    timeToVolumeDict["4:23:15"]  = 30

    timeToVolumeDict["5:02:15"]  = 35
    timeToVolumeDict["5:04:45"]  = 35    
    timeToVolumeDict["5:07:25"]  = 25
    timeToVolumeDict["5:08:40"]  = 50
    timeToVolumeDict["5:11:00"]  = 30
    timeToVolumeDict["5:14:00"]  = 30 #* vomited about 10-15 ml (actually drunk ~40 ml)
    timeToVolumeDict["5:17:00"]  = 50
    timeToVolumeDict["5:20:00"]  = 50
    timeToVolumeDict["5:22:00"]  = 35

    timeToVolumeDict["6:00:30"]  = 30
    timeToVolumeDict["6:03:00"]  = 30
    timeToVolumeDict["6:05:00"]  = 30
    timeToVolumeDict["6:07:30"]  = 40
    timeToVolumeDict["6:14:00"]  = 30 # taxi & airport & flight (~ 30ml)
    timeToVolumeDict["6:17:30"]  = 45
    timeToVolumeDict["6:23:00"]  = 45

    timeToVolumeDict["7:02:00"]  = 60
    timeToVolumeDict["7:06:00"]  = 60
    timeToVolumeDict["7:09:30"]  = 25
    timeToVolumeDict["7:12:30"]  = 30
    timeToVolumeDict["7:14:30"]  = 30
    timeToVolumeDict["7:17:00"]  = 50
    timeToVolumeDict["7:19:00"]  = 10
    timeToVolumeDict["7:20:50"]  =  7
    timeToVolumeDict["7:23:00"]  = 20
    
    timeToVolumeDict["8:00:50"]  = 55
    timeToVolumeDict["8:04:00"]  = 40
    timeToVolumeDict["8:06:20"]  = 10
    timeToVolumeDict["8:07:30"]  = 10
    timeToVolumeDict["8:09:00"]  = 40
    timeToVolumeDict["8:10:40"]  = 30
    timeToVolumeDict["8:12:05"]  = 25
    timeToVolumeDict["8:14:25"]  = 50
    timeToVolumeDict["8:16:20"]  = 55
    timeToVolumeDict["8:18:15"]  = 30
    timeToVolumeDict["8:22:20"]  = 40
    
    timeToVolumeDict["9:01:15"]  = 20
    timeToVolumeDict["9:04:00"]  = 60
    timeToVolumeDict["9:07:15"]  = 30
    timeToVolumeDict["9:10:15"]  = 20
    timeToVolumeDict["9:12:00"]  = 35
    timeToVolumeDict["9:15:00"]  = 25
    timeToVolumeDict["9:16:15"]  = 35
    timeToVolumeDict["9:17:00"]  = 40
    timeToVolumeDict["9:19:45"]  = 45
    timeToVolumeDict["9:22:15"]  = 40
    
    timeToVolumeDict["10:01:00"] = 80
    timeToVolumeDict["10:05:15"] = 30
    timeToVolumeDict["10:07:45"] = 25
    timeToVolumeDict["10:10:45"] = 60
    timeToVolumeDict["10:13:30"] = 35
    timeToVolumeDict["10:15:15"] = 25
    timeToVolumeDict["10:16:50"] = 90
    timeToVolumeDict["10:20:00"] = 25
    timeToVolumeDict["10:22:30"] = 55
    
    timeToVolumeDict["11:01:30"] = 30
    timeToVolumeDict["11:04:00"] = 80
    timeToVolumeDict["11:08:00"] = 110
    timeToVolumeDict["11:14:00"] = 35
    timeToVolumeDict["11:18:00"] = 50
    timeToVolumeDict["11:20:30"] = 65
    
    timeToVolumeDict["12:00:30"] = 40
    timeToVolumeDict["12:04:00"] = 80
    timeToVolumeDict["12:08:30"] = 50
    timeToVolumeDict["12:09:20"] = 10
    timeToVolumeDict["12:10:20"] = 35
    timeToVolumeDict["12:11:10"] = 10
    timeToVolumeDict["12:13:30"] = 60
    timeToVolumeDict["12:16:30"] = 65
    timeToVolumeDict["12:18:00"] = 25
    timeToVolumeDict["12:21:30"] = 55
    
    timeToVolumeDict["13:00:30"] = 30
    timeToVolumeDict["13:04:00"] = 90
    timeToVolumeDict["13:07:30"] = 30
    timeToVolumeDict["13:08:00"] = 50
    timeToVolumeDict["13:11:15"] = 60
    timeToVolumeDict["13:14:00"] = 50
    timeToVolumeDict["13:18:00"] = 60
    timeToVolumeDict["13:20:20"] = 65
    
    timeToVolumeDict["14:01:15"] = 50
    timeToVolumeDict["14:01:40"] = 20
    timeToVolumeDict["14:04:20"] = 70
    timeToVolumeDict["14:07:20"] = 85
    timeToVolumeDict["14:10:45"] = 80 # vomitted about 15 ml
    timeToVolumeDict["14:15:30"] = 70 # vomitted about 10 ml
    timeToVolumeDict["14:16:30"] = 50
    timeToVolumeDict["14:17:30"] = 10
    timeToVolumeDict["14:19:15"] = 30
    timeToVolumeDict["14:21:35"] = 40
    
    timeToVolumeDict["15:00:30"] = 60
    timeToVolumeDict["15:02:00"] = 45
    timeToVolumeDict["15:05:40"] = 50
    timeToVolumeDict["15:08:20"] = 40
    timeToVolumeDict["15:09:20"] = 30
    timeToVolumeDict["15:10:30"] = 25
    timeToVolumeDict["15:14:00"] = 70
    timeToVolumeDict["15:17:30"] = 55
    timeToVolumeDict["15:18:30"] = 35
    timeToVolumeDict["15:21:20"] = 45
    
    timeToVolumeDict["16:01:15"] = 40
    timeToVolumeDict["16:03:30"] = 50
    timeToVolumeDict["16:07:20"] = 50
    timeToVolumeDict["16:09:00"] = 20
    timeToVolumeDict["16:10:00"] = 30
    timeToVolumeDict["16:11:30"] = 60
    timeToVolumeDict["16:15:00"] = 40
    timeToVolumeDict["16:18:00"] = 60
    timeToVolumeDict["16:20:40"] = 40
    
    timeToVolumeDict["17:00:00"] = 60
    timeToVolumeDict["17:00:45"] = 25
    timeToVolumeDict["17:03:30"] = 60
    timeToVolumeDict["17:07:45"] = 35
    timeToVolumeDict["17:08:30"] = 30
    timeToVolumeDict["17:09:30"] = 45
    timeToVolumeDict["17:13:30"] = 65
    timeToVolumeDict["17:15:30"] = 60
    timeToVolumeDict["17:19:00"] = 60
    timeToVolumeDict["17:21:30"] = 50
    
    timeToVolumeDict["18:00:15"] = 55
    timeToVolumeDict["18:03:30"] = 60
    timeToVolumeDict["18:04:30"] = 25
    timeToVolumeDict["18:07:15"] = 60
    timeToVolumeDict["18:10:00"] = 40
    timeToVolumeDict["18:11:15"] = 55
    timeToVolumeDict["18:15:00"] = 70
    timeToVolumeDict["18:16:00"] = 40
    timeToVolumeDict["18:18:00"] = 60
    timeToVolumeDict["18:19:30"] = 50
    timeToVolumeDict["18:21:10"] = 40
    
    timeToVolumeDict["19:03:20"] = 55
    timeToVolumeDict["19:06:15"] = 40
    timeToVolumeDict["19:08:45"] = 40
    timeToVolumeDict["19:10:20"] = 40
    timeToVolumeDict["19:12:05"] = 55
    timeToVolumeDict["19:15:00"] = 20
    timeToVolumeDict["19:17:00"] = 45
    timeToVolumeDict["19:21:45"] = 60
    timeToVolumeDict["19:22:20"] = 40
    
    timeToVolumeDict["20:01:00"] = 50
    timeToVolumeDict["20:04:00"] = 60
    timeToVolumeDict["20:06:50"] = 40
    timeToVolumeDict["20:09:50"] = 65
    timeToVolumeDict["20:10:50"] = 40
    timeToVolumeDict["20:13:25"] = 40
    timeToVolumeDict["20:15:30"] = 40
    timeToVolumeDict["20:16:30"] = 50
    timeToVolumeDict["20:21:00"] = 70
    timeToVolumeDict["20:22:00"] = 10
    
    timeToVolumeDict["21:01:50"] = 60
    timeToVolumeDict["21:03:00"] = 20
    timeToVolumeDict["21:05:00"] = 40
    timeToVolumeDict["21:07:45"] = 55
    timeToVolumeDict["21:08:45"] = 15
    timeToVolumeDict["21:11:00"] = 45
    timeToVolumeDict["21:14:30"] = 50
    timeToVolumeDict["21:15:30"] = 20
    timeToVolumeDict["21:16:30"] = 40
    timeToVolumeDict["21:18:20"] = 30
    timeToVolumeDict["21:22:30"] = 40
    
    timeToVolumeDict["22:02:15"] = 75
    timeToVolumeDict["22:06:00"] = 25
    timeToVolumeDict["22:08:45"] = 45
    timeToVolumeDict["22:10:00"] = 30
    timeToVolumeDict["22:12:20"] = 70
    timeToVolumeDict["22:16:00"] = 70
    timeToVolumeDict["22:20:15"] = 40
    timeToVolumeDict["22:00:00"] = 50
    
    timeToVolumeDict["23:03:30"] = 80
    timeToVolumeDict["23:05:30"] = 50
    timeToVolumeDict["23:08:30"] = 90
    timeToVolumeDict["23:10:45"] = 40
    timeToVolumeDict["23:12:30"] = 30
    timeToVolumeDict["23:16:00"] = 60
    timeToVolumeDict["23:17:45"] = 20
    timeToVolumeDict["23:19:15"] = 40
    timeToVolumeDict["23:23:15"] = 45
    
    timeToVolumeDict["24:02:20"] = 60
    timeToVolumeDict["24:04:15"] = 20
    timeToVolumeDict["24:06:30"] = 10
    timeToVolumeDict["24:10:30"] = 60
    timeToVolumeDict["24:13:00"] = 70
    timeToVolumeDict["24:17:00"] = 70
    timeToVolumeDict["24:20:30"] = 20
    timeToVolumeDict["24:23:45"] = 20
    
    timeToVolumeDict["25:05:30"] = 55
    timeToVolumeDict["25:08:30"] = 40
    timeToVolumeDict["25:10:45"] = 25
    timeToVolumeDict["25:13:00"] = 55
    timeToVolumeDict["25:15:00"] = 50
    timeToVolumeDict["25:17:15"] = 55
    timeToVolumeDict["25:19:45"] = 65
    timeToVolumeDict["25:20:30"] = 10
    timeToVolumeDict["25:22:30"] = 40
    timeToVolumeDict["25:23:15"] = 10
    
    timeToVolumeDict["26:04:00"] = 55
    timeToVolumeDict["26:06:00"] = 50
    timeToVolumeDict["26:08:45"] = 70
    timeToVolumeDict["26:11:30"] = 40
    timeToVolumeDict["26:13:00"] = 30
    timeToVolumeDict["26:13:30"] = 30
    timeToVolumeDict["26:14:15"] = 20
    timeToVolumeDict["26:17:20"] = 70
    timeToVolumeDict["26:19:30"] = 65
    timeToVolumeDict["26:22:30"] = 50

    timeToVolumeDict["27:04:00"] = 70
    timeToVolumeDict["27:07:00"] = 65
    timeToVolumeDict["27:09:00"] = 10
    timeToVolumeDict["27:10:00"] = 40
    timeToVolumeDict["27:10:45"] = 30
    timeToVolumeDict["27:13:30"] = 40
    timeToVolumeDict["27:15:30"] = 60
    timeToVolumeDict["27:16:30"] = 40
    timeToVolumeDict["27:18:00"] = 65
    timeToVolumeDict["27:20:40"] = 45
    
    timeToVolumeDict["28:01:20"] = 65
    timeToVolumeDict["28:05:00"] = 60
    timeToVolumeDict["28:07:30"] = 70
    timeToVolumeDict["28:09:45"] = 50
    timeToVolumeDict["28:10:30"] = 20
    timeToVolumeDict["28:12:30"] = 50
    timeToVolumeDict["28:15:30"] = 70
    timeToVolumeDict["28:16:30"] = 30
    timeToVolumeDict["28:17:30"] = 15
    timeToVolumeDict["28:20:30"] = 70
    timeToVolumeDict["28:21:30"] = 30
    
    timeToVolumeDict["29:02:00"] = 65
    timeToVolumeDict["29:05:20"] = 60
    timeToVolumeDict["29:08:10"] = 70
    timeToVolumeDict["29:11:00"] = 45
    timeToVolumeDict["29:12:45"] = 70
    timeToVolumeDict["29:14:25"] = 50
    timeToVolumeDict["29:17:30"] = 60
    timeToVolumeDict["29:21:30"] = 70
    timeToVolumeDict["29:22:30"] = 40
    timeToVolumeDict["29:21:30"] = 70
    
    timeToVolumeDict["30:00:15"] = 55
    timeToVolumeDict["30:04:00"] = 40
    timeToVolumeDict["30:06:00"] = 70
    timeToVolumeDict["30:09:00"] = 70
    timeToVolumeDict["30:10:30"] = 50
    timeToVolumeDict["30:14:45"] = 50
    timeToVolumeDict["30:18:00"] = 70
    timeToVolumeDict["30:19:15"] = 30
    timeToVolumeDict["30:20:45"] = 65
    timeToVolumeDict["30:23:45"] = 50
    
    timeToVolumeDict["31:02:40"] = 70
    timeToVolumeDict["31:03:40"] = 30
    timeToVolumeDict["31:06:20"] = 45
    timeToVolumeDict["31:06:40"] = 25
    timeToVolumeDict["31:09:15"] = 70
    timeToVolumeDict["31:11:15"] = 40
    timeToVolumeDict["31:12:30"] = 40
    timeToVolumeDict["31:14:30"] = 70
    timeToVolumeDict["31:17:30"] = 100
    timeToVolumeDict["31:20:00"] = 80
    timeToVolumeDict["31:21:00"] = 40
    
    timeToVolumeDict["32:03:00"] = 70
    timeToVolumeDict["32:06:00"] = 30
    timeToVolumeDict["32:07:00"] = 60
    timeToVolumeDict["32:10:00"] = 70
    timeToVolumeDict["32:12:00"] = 80
    timeToVolumeDict["32:14:10"] = 60
    timeToVolumeDict["32:18:30"] = 70
    timeToVolumeDict["32:20:30"] = 90
    timeToVolumeDict["32:22:25"] = 60

    timeToVolumeDict["33:02:00"] = 55 #04 July 2016
    timeToVolumeDict["33:05:30"] = 45
    timeToVolumeDict["33:07:30"] = 65
    timeToVolumeDict["33:09:45"] = 40
    timeToVolumeDict["33:11:15"] = 30
    timeToVolumeDict["33:11:45"] = 45
    timeToVolumeDict["33:14:30"] = 100
    timeToVolumeDict["33:18:15"] = 60
    timeToVolumeDict["33:19:45"] = 20
    timeToVolumeDict["33:20:00"] = 55
    timeToVolumeDict["33:22:15"] = 55
    timeToVolumeDict["33:22:50"] = 30
    timeToVolumeDict["33:23:45"] = 15

    timeToVolumeDict["34:03:00"] = 35 #05 July 2016
    timeToVolumeDict["34:05:30"] = 40
    timeToVolumeDict["34:07:20"] = 50
    timeToVolumeDict["34:10:15"] = 70
    timeToVolumeDict["34:11:30"] = 40
    timeToVolumeDict["34:13:00"] = 80
    timeToVolumeDict["34:15:20"] = 50
    timeToVolumeDict["34:19:00"] = 70
    timeToVolumeDict["34:20:35"] = 70
    timeToVolumeDict["34:21:35"] = 80

    timeToVolumeDict["35:02:50"] = 70 #06 July 2016
    timeToVolumeDict["35:05:15"] = 20
    timeToVolumeDict["35:07:15"] = 50
    timeToVolumeDict["35:11:40"] = 70
    timeToVolumeDict["35:11:45"] = 25
    timeToVolumeDict["35:14:00"] = 50
    timeToVolumeDict["35:15:00"] = 30
    timeToVolumeDict["35:16:30"] = 70
    timeToVolumeDict["35:20:20"] = 60
    timeToVolumeDict["35:22:25"] = 50
    
    timeToVolumeDict["36:01:45"] = 70
    timeToVolumeDict["36:04:40"] = 70
    timeToVolumeDict["36:07:10"] = 55
    timeToVolumeDict["36:09:30"] = 70
    timeToVolumeDict["36:11:40"] = 50
    timeToVolumeDict["36:14:15"] = 55
    timeToVolumeDict["36:17:00"] = 70
    timeToVolumeDict["36:18:45"] = 30
    timeToVolumeDict["36:20:30"] = 50
    
    timeToVolumeDict["37:01:00"] = 65 #07 July 2016
    timeToVolumeDict["37:04:50"] = 40
    timeToVolumeDict["37:07:15"] = 50
    timeToVolumeDict["37:08:45"] = 20
    timeToVolumeDict["37:10:00"] = 70
    timeToVolumeDict["37:13:00"] = 70
    timeToVolumeDict["37:14:00"] = 20
    timeToVolumeDict["37:15:20"] = 50
    timeToVolumeDict["37:16:20"] = 10
    timeToVolumeDict["37:19:00"] = 70
    timeToVolumeDict["37:20:40"] = 70
    timeToVolumeDict["37:22:20"] = 45
    timeToVolumeDict["37:23:15"] = 40

    timeToVolumeDict["38:03:40"] = 65  #08 July 2016
    timeToVolumeDict["38:06:40"] = 70
    timeToVolumeDict["38:09:00"] = 45
    timeToVolumeDict["38:09:30"] = 25
    timeToVolumeDict["38:10:40"] = 30
    timeToVolumeDict["38:11:40"] = 40
    timeToVolumeDict["38:13:20"] = 70
    timeToVolumeDict["38:14:00"] = 60
    timeToVolumeDict["38:18:00"] = 60
    timeToVolumeDict["38:18:40"] = 30
    timeToVolumeDict["38:20:00"] = 80
    timeToVolumeDict["38:21:00"] = 60
    
    timeToVolumeDict["39:01:00"] = 50  #09 July 2016
    timeToVolumeDict["39:04:55"] = 30
    timeToVolumeDict["39:07:00"] = 70
    timeToVolumeDict["39:11:00"] = 70
    timeToVolumeDict["39:13:00"] = 50
    timeToVolumeDict["39:15:10"] = 60
    timeToVolumeDict["39:18:35"] = 65
    timeToVolumeDict["39:20:00"] = 45
    timeToVolumeDict["39:22:00"] = 70
    timeToVolumeDict["39:23:30"] = 70
    
    timeToVolumeDict["40:01:00"] = 30  #10 July 2016
    timeToVolumeDict["40:05:00"] = 65
    timeToVolumeDict["40:08:30"] = 70
    timeToVolumeDict["40:11:00"] = 70
    timeToVolumeDict["40:12:20"] = 25
    timeToVolumeDict["40:12:35"] = 45
    timeToVolumeDict["40:15:45"] = 80
    timeToVolumeDict["40:16:30"] = 40
    timeToVolumeDict["40:20:05"] = 85
    
    timeToVolumeDict["41:00:40"] = 70  #11 July 2016
    timeToVolumeDict["41:05:30"] = 50
    timeToVolumeDict["41:08:15"] = 70
    timeToVolumeDict["41:10:20"] = 70
    timeToVolumeDict["41:13:00"] = 40
    timeToVolumeDict["41:14:00"] = 30
    timeToVolumeDict["41:18:00"] = 70
    timeToVolumeDict["41:19:00"] = 60
    timeToVolumeDict["41:20:30"] = 60
    timeToVolumeDict["41:21:30"] = 45
    
    timeToVolumeDict["42:02:00"] = 65  #12 July 2016
    timeToVolumeDict["42:05:30"] = 70
    timeToVolumeDict["42:07:30"] = 55
    timeToVolumeDict["42:09:45"] = 60
    timeToVolumeDict["42:12:15"] = 70
    timeToVolumeDict["42:13:30"] = 50
    timeToVolumeDict["42:15:00"] = 20
    timeToVolumeDict["42:18:00"] = 70
    timeToVolumeDict["42:20:45"] = 80
    timeToVolumeDict["42:22:15"] = 30

    timeToVolumeDict["43:05:35"] = 70  #13 July 2016
    timeToVolumeDict["43:08:30"] = 70
    timeToVolumeDict["43:09:45"] = 55
    timeToVolumeDict["43:11:15"] = 20
    timeToVolumeDict["43:14:30"] = 120
    timeToVolumeDict["43:17:30"] = 55
    timeToVolumeDict["43:19:00"] = 100
    timeToVolumeDict["43:21:25"] = 20
    timeToVolumeDict["43:22:45"] = 80

    timeToVolumeDict["44:03:30"] = 80  #14 July 2016
    timeToVolumeDict["44:06:40"] = 50
    timeToVolumeDict["44:08:20"] = 55
    timeToVolumeDict["44:10:10"] = 85
    timeToVolumeDict["44:12:00"] = 80
    timeToVolumeDict["44:17:00"] = 80
    timeToVolumeDict["44:19:00"] = 70
    timeToVolumeDict["44:20:40"] = 80
    timeToVolumeDict["44:22:45"] = 50

    timeToVolumeDict["45:04:30"] = 70  #15 July 2016
    timeToVolumeDict["45:06:45"] = 25
    timeToVolumeDict["45:08:30"] = 90
    timeToVolumeDict["45:10:30"] = 85
    timeToVolumeDict["45:13:30"] = 110
    timeToVolumeDict["45:15:30"] = 30
    timeToVolumeDict["45:17:00"] = 30
    timeToVolumeDict["45:20:40"] = 70

    timeToVolumeDict["46:00:10"] = 45  #16 July 2016
    timeToVolumeDict["46:04:00"] = 70
    timeToVolumeDict["46:04:40"] = 35
    timeToVolumeDict["46:08:30"] = 70
    timeToVolumeDict["46:09:00"] = 30
    timeToVolumeDict["46:11:00"] = 70
    timeToVolumeDict["46:13:00"] = 70
    timeToVolumeDict["46:15:10"] = 75
    timeToVolumeDict["46:19:00"] = 70
    timeToVolumeDict["46:20:10"] = 50
    timeToVolumeDict["46:21:30"] = 30
    timeToVolumeDict["46:23:00"] = 80

    timeToVolumeDict["47:04:00"] = 55  #17 July 2016
    timeToVolumeDict["47:06:00"] = 70
    timeToVolumeDict["47:08:00"] = 70
    timeToVolumeDict["47:10:15"] = 70
    timeToVolumeDict["47:13:30"] = 100
    timeToVolumeDict["47:15:00"] = 70
    timeToVolumeDict["47:17:00"] = 80
    timeToVolumeDict["47:18:00"] = 40
    timeToVolumeDict["47:21:30"] = 60

    timeToVolumeDict["48:05:00"] = 45 #18 July 2016
    timeToVolumeDict["48:07:30"] = 45
    timeToVolumeDict["48:09:30"] = 50
    timeToVolumeDict["48:11:30"] = 70
    timeToVolumeDict["48:13:30"] = 35
    timeToVolumeDict["48:14:30"] = 95
    timeToVolumeDict["48:18:00"] = 70
    timeToVolumeDict["48:20:00"] = 60
    timeToVolumeDict["48:21:30"] = 65

    timeToVolumeDict["49:02:00"] = 50 #19 July 2016
    timeToVolumeDict["49:05:20"] = 40
    timeToVolumeDict["49:07:20"] = 70
    timeToVolumeDict["49:09:00"] = 70
    timeToVolumeDict["49:12:10"] = 70
    timeToVolumeDict["49:14:30"] = 70
    timeToVolumeDict["49:17:00"] = 40
    timeToVolumeDict["49:18:00"] = 70
    timeToVolumeDict["49:20:30"] = 70
    timeToVolumeDict["49:21:00"] = 30

    timeToVolumeDict["50:03:15"] = 50 #20 July 2016
    timeToVolumeDict["50:05:10"] = 50
    timeToVolumeDict["50:07:00"] = 70
    timeToVolumeDict["50:09:00"] = 50
    timeToVolumeDict["50:10:20"] = 60
    timeToVolumeDict["50:12:10"] = 70
    timeToVolumeDict["50:17:00"] = 70
    timeToVolumeDict["50:19:00"] = 70
    timeToVolumeDict["50:21:00"] = 70

    timeToVolumeDict["51:03:20"] = 50 #21 July 2016
    timeToVolumeDict["51:06:15"] = 70
    timeToVolumeDict["51:08:30"] = 70
    timeToVolumeDict["51:09:40"] = 40
    timeToVolumeDict["51:11:30"] = 80
    timeToVolumeDict["51:13:30"] = 70
    timeToVolumeDict["51:14:45"] = 80
    timeToVolumeDict["51:15:40"] = 40
    timeToVolumeDict["51:19:30"] = 120
    timeToVolumeDict["51:20:30"] = 70
    timeToVolumeDict["51:21:30"] = 70

    timeToVolumeDict["52:05:00"] = 50 #22 July 2016
    timeToVolumeDict["52:06:30"] = 15
    timeToVolumeDict["52:08:30"] = 55
    timeToVolumeDict["52:10:00"] = 70
    timeToVolumeDict["52:11:00"] = 50
    timeToVolumeDict["52:12:30"] = 70
    timeToVolumeDict["52:16:00"] = 65
    timeToVolumeDict["52:18:40"] = 70
    timeToVolumeDict["52:20:00"] = 80
    timeToVolumeDict["52:21:40"] = 70
    timeToVolumeDict["52:23:00"] = 70
    
    timeToVolumeDict["53:06:00"] = 60 #23 July 2016
    timeToVolumeDict["53:08:00"] = 70
    timeToVolumeDict["53:10:00"] = 70
    timeToVolumeDict["53:11:15"] = 60
    timeToVolumeDict["53:14:20"] = 110
    timeToVolumeDict["53:17:20"] = 75
    timeToVolumeDict["53:18:40"] = 40
    timeToVolumeDict["53:21:10"] = 110

    timeToVolumeDict["54:05:30"] = 70  #24 July 2016
    timeToVolumeDict["54:08:30"] = 65
    timeToVolumeDict["54:10:20"] = 70
    timeToVolumeDict["54:13:15"] = 70
    timeToVolumeDict["54:16:00"] = 95
    timeToVolumeDict["54:19:25"] = 60
    timeToVolumeDict["54:19:55"] = 40

    timeToVolumeDict["55:02:54"] = 60  #25 July 2016
    timeToVolumeDict["55:06:00"] = 70
    timeToVolumeDict["55:07:45"] = 45
    timeToVolumeDict["55:10:00"] = 75
    timeToVolumeDict["55:12:15"] = 70
    timeToVolumeDict["55:15:30"] = 60
    timeToVolumeDict["55:19:00"] = 100
    timeToVolumeDict["55:20:00"] = 50

    timeToVolumeDict["56:01:30"] = 70  #26 July 2016
    timeToVolumeDict["56:03:50"] = 40
    timeToVolumeDict["56:06:30"] = 70
    timeToVolumeDict["56:08:00"] = 70
    timeToVolumeDict["56:10:00"] = 80
    timeToVolumeDict["56:12:00"] = 60
    timeToVolumeDict["56:14:30"] = 75
    timeToVolumeDict["56:17:30"] = 80
    timeToVolumeDict["56:19:00"] = 40
    timeToVolumeDict["56:19:40"] = 40
    timeToVolumeDict["56:22:00"] = 100

    timeToVolumeDict["57:02:20"] = 50  #27 July 2016
    timeToVolumeDict["57:06:45"] = 70
    timeToVolumeDict["57:07:30"] = 70
    timeToVolumeDict["57:08:00"] = 60
    timeToVolumeDict["57:10:00"] = 60
    timeToVolumeDict["57:14:00"] = 70
    timeToVolumeDict["57:16:00"] = 70
    timeToVolumeDict["57:17:00"] = 50
    timeToVolumeDict["57:18:30"] = 30
    timeToVolumeDict["57:19:55"] = 80
    timeToVolumeDict["57:21:00"] = 70
    timeToVolumeDict["57:22:30"] = 70 # not 100% certain of quantity - missing entry

    timeToVolumeDict["58:04:30"] = 40  #28 July 2016
    timeToVolumeDict["58:06:00"] = 70
    timeToVolumeDict["58:08:00"] = 70
    timeToVolumeDict["58:10:00"] = 80
    timeToVolumeDict["58:10:30"] = 40
    timeToVolumeDict["58:13:00"] = 80
    timeToVolumeDict["58:16:30"] = 140
    timeToVolumeDict["58:19:10"] = 75
    timeToVolumeDict["58:20:00"] = 80

    timeToVolumeDict["59:03:45"] = 60  #29 July 2016
    timeToVolumeDict["59:06:40"] = 50
    timeToVolumeDict["59:08:00"] = 70
    timeToVolumeDict["59:10:20"] = 80
    timeToVolumeDict["59:11:40"] = 75
    timeToVolumeDict["59:13:45"] = 80
    timeToVolumeDict["59:15:40"] = 55
    timeToVolumeDict["59:16:50"] = 70
    timeToVolumeDict["59:18:30"] = 80
    timeToVolumeDict["59:20:30"] = 80
    timeToVolumeDict["59:21:45"] = 50

    timeToVolumeDict["60:04:40"] = 50  #30 July 2016
    timeToVolumeDict["60:08:00"] = 40
    timeToVolumeDict["60:09:40"] = 70
    timeToVolumeDict["60:11:25"] = 70
    timeToVolumeDict["60:13:20"] = 80
    timeToVolumeDict["60:15:10"] = 40
    timeToVolumeDict["60:18:00"] = 80
    timeToVolumeDict["60:19:10"] = 100
    timeToVolumeDict["60:20:30"] = 90

    timeToVolumeDict["61:04:50"] = 55  #31 July 2016
    timeToVolumeDict["61:06:30"] = 15
    timeToVolumeDict["61:09:30"] = 70
    timeToVolumeDict["61:10:45"] = 80
    timeToVolumeDict["61:12:05"] = 80
    timeToVolumeDict["61:14:00"] = 45
    timeToVolumeDict["61:17:00"] = 80
    timeToVolumeDict["61:18:45"] = 80
    timeToVolumeDict["61:20:00"] = 80
    timeToVolumeDict["61:20:35"] = 5
    timeToVolumeDict["61:21:30"] = 75

    timeToVolumeDict["62:03:15"] = 100  #01 August 2016
    timeToVolumeDict["62:07:00"] = 50
    timeToVolumeDict["62:08:35"] = 90
    timeToVolumeDict["62:10:15"] = 70
    timeToVolumeDict["62:13:00"] = 70
    timeToVolumeDict["62:14:45"] = 80
    timeToVolumeDict["62:15:00"] = 35
    timeToVolumeDict["62:18:00"] = 90
    timeToVolumeDict["62:18:50"] = 40
    timeToVolumeDict["62:19:40"] = 40
    timeToVolumeDict["62:21:45"] = 40

    timeToVolumeDict["63:03:10"] = 70  #02 August 2016
    timeToVolumeDict["63:05:40"] = 70
    timeToVolumeDict["63:08:00"] = 70
    timeToVolumeDict["63:09:30"] = 40
    timeToVolumeDict["63:10:30"] = 40
    timeToVolumeDict["63:13:00"] = 110
    timeToVolumeDict["63:14:30"] = 80
    timeToVolumeDict["63:16:30"] = 45
    timeToVolumeDict["63:18:00"] = 75
    timeToVolumeDict["63:20:05"] = 65
    timeToVolumeDict["63:21:30"] = 70
    timeToVolumeDict["63:23:00"] = 50

    timeToVolumeDict["64:04:30"] = 70  #03 August 2016
    timeToVolumeDict["64:06:30"] = 70
    timeToVolumeDict["64:08:00"] = 50
    timeToVolumeDict["64:11:30"] = 80
    timeToVolumeDict["64:13:50"] = 100
    timeToVolumeDict["64:15:10"] = 60
    timeToVolumeDict["64:17:00"] = 60
    timeToVolumeDict["64:19:00"] = 40
    timeToVolumeDict["64:20:10"] = 60
    timeToVolumeDict["64:21:00"] = 50

    timeToVolumeDict["65:02:40"] = 70  #04 August 2016
    timeToVolumeDict["65:06:45"] = 50
    timeToVolumeDict["65:08:00"] = 60
    timeToVolumeDict["65:11:00"] = 40
    timeToVolumeDict["65:11:40"] = 35
    timeToVolumeDict["65:14:00"] = 80
    timeToVolumeDict["65:15:15"] = 45
    timeToVolumeDict["65:16:10"] = 70
    timeToVolumeDict["65:17:15"] = 80
    timeToVolumeDict["65:19:40"] = 80
    timeToVolumeDict["65:21:30"] = 80

    timeToVolumeDict["66:05:00"] = 60  #05 August 2016
    timeToVolumeDict["66:07:15"] = 35
    timeToVolumeDict["66:08:00"] = 45
    timeToVolumeDict["66:09:00"] = 55
    timeToVolumeDict["66:11:00"] = 80
    timeToVolumeDict["66:12:30"] = 60
    timeToVolumeDict["66:13:30"] = 70
    timeToVolumeDict["66:16:00"] = 40
    timeToVolumeDict["66:17:20"] = 55
    timeToVolumeDict["66:18:15"] = 90
    timeToVolumeDict["66:22:00"] = 120

    timeToVolumeDict["67:05:00"] = 60  #06 August 2016
    timeToVolumeDict["67:07:15"] = 60
    timeToVolumeDict["67:09:00"] = 55
    timeToVolumeDict["67:10:30"] = 40
    timeToVolumeDict["67:11:15"] = 40
    timeToVolumeDict["67:11:00"] = 40
    timeToVolumeDict["67:13:00"] = 60
    timeToVolumeDict["67:14:00"] = 60
    #timeToVolumeDict["67:???:??"] = 400 # did not keep time!
    timeToVolumeDict["67:16:00"] = 100 # fictitious time
    timeToVolumeDict["67:17:00"] = 100 # fictitious time
    timeToVolumeDict["67:19:00"] = 100 # fictitious time
    timeToVolumeDict["67:22:00"] = 100 # fictitious time    

    timeToVolumeDict["68:05:30"] = 60  #07 August 2016
    timeToVolumeDict["68:07:30"] = 65
    timeToVolumeDict["68:09:00"] = 60
    timeToVolumeDict["68:10:35"] = 70
    timeToVolumeDict["68:12:00"] = 70
    timeToVolumeDict["68:13:20"] = 50
    timeToVolumeDict["68:14:15"] = 70
    timeToVolumeDict["68:17:00"] = 70
    timeToVolumeDict["68:18:00"] = 70
    timeToVolumeDict["68:19:20"] = 60
    timeToVolumeDict["68:20:30"] = 90

    timeToVolumeDict["69:02:15"] = 65  #08 August 2016
    timeToVolumeDict["69:06:20"] = 65
    timeToVolumeDict["69:08:30"] = 90
    timeToVolumeDict["69:10:20"] = 95
    timeToVolumeDict["69:13:30"] = 40
    timeToVolumeDict["69:14:45"] = 50
    timeToVolumeDict["69:15:50"] = 55
    timeToVolumeDict["69:16:50"] = 45
    timeToVolumeDict["69:18:00"] = 60
    timeToVolumeDict["69:19:40"] = 50
    timeToVolumeDict["69:20:30"] = 70
    timeToVolumeDict["69:22:40"] = 100
    
    timeToVolumeDict["70:00:24"] = 45  #09 August 2016
    timeToVolumeDict["70:07:15"] = 70
    timeToVolumeDict["70:09:10"] = 70
    timeToVolumeDict["70:11:00"] = 110
    timeToVolumeDict["70:13:00"] = 70
    timeToVolumeDict["70:15:00"] = 80
    timeToVolumeDict["70:15:30"] = 50
    timeToVolumeDict["70:17:40"] = 80
    timeToVolumeDict["70:20:00"] = 75
    timeToVolumeDict["70:21:10"] = 50

    timeToVolumeDict["71:04:40"] = 70  #10 August 2016
    timeToVolumeDict["71:06:30"] = 50
    timeToVolumeDict["71:09:45"] = 70
    timeToVolumeDict["71:11:20"] = 75
    timeToVolumeDict["71:15:00"] = 75
    timeToVolumeDict["71:18:30"] = 70
    timeToVolumeDict["71:19:50"] = 70
    timeToVolumeDict["71:20:20"] = 50

    timeToVolumeDict["72:02:00"] = 50  #11 August 2016
    timeToVolumeDict["72:05:00"] = 60
    timeToVolumeDict["72:06:30"] = 65
    timeToVolumeDict["72:09:15"] = 80
    timeToVolumeDict["72:11:30"] = 80
    timeToVolumeDict["72:14:30"] = 95
    timeToVolumeDict["72:16:45"] = 45
    timeToVolumeDict["72:17:45"] = 50
    timeToVolumeDict["72:18:30"] = 100
    timeToVolumeDict["72:20:45"] = 80
    
    timeToVolumeDict["73:03:50"] = 60  #12 August 2016
    timeToVolumeDict["73:07:15"] = 65
    timeToVolumeDict["73:08:50"] = 70
    timeToVolumeDict["73:10:10"] = 70
    timeToVolumeDict["73:12:20"] = 70
    timeToVolumeDict["73:16:00"] = 90
    timeToVolumeDict["73:17:20"] = 45
    timeToVolumeDict["73:18:20"] = 90
    timeToVolumeDict["73:19:40"] = 40
    timeToVolumeDict["73:22:15"] = 80

    timeToVolumeDict["74:04:15"] = 70  #13 August 2016
    timeToVolumeDict["74:06:00"] = 50
    timeToVolumeDict["74:08:00"] = 50
    timeToVolumeDict["74:10:15"] = 70
    timeToVolumeDict["74:11:15"] = 30
    timeToVolumeDict["74:15:00"] = 115
    timeToVolumeDict["74:16:15"] = 45
    timeToVolumeDict["74:17:00"] = 60
    timeToVolumeDict["74:18:30"] = 60
    timeToVolumeDict["74:20:00"] = 70
    timeToVolumeDict["74:21:00"] = 35
    timeToVolumeDict["74:22:20"] = 5  # yes, just 5 (left-overs)
    
    timeToVolumeDict["75:03:45"] = 50  #14 August 2016
    timeToVolumeDict["75:07:25"] = 70
    timeToVolumeDict["75:08:45"] = 60
    timeToVolumeDict["75:11:00"] = 70
    timeToVolumeDict["75:12:00"] = 60
    timeToVolumeDict["75:13:30"] = 70
    timeToVolumeDict["75:15:15"] = 50
    timeToVolumeDict["75:17:15"] = 70
    timeToVolumeDict["75:18:20"] = 50
    timeToVolumeDict["75:20:30"] = 90
    timeToVolumeDict["75:22:00"] = 85

    timeToVolumeDict["76:07:00"] = 60  #15 August 2016
    timeToVolumeDict["76:07:40"] = 30
    timeToVolumeDict["76:08:40"] = 40
    timeToVolumeDict["76:09:45"] = 75
    timeToVolumeDict["76:11:15"] = 40
    timeToVolumeDict["76:12:00"] = 50
    timeToVolumeDict["76:13:00"] = 80
    timeToVolumeDict["76:14:30"] = 70
    timeToVolumeDict["76:15:20"] = 40
    timeToVolumeDict["76:16:30"] = 70
    timeToVolumeDict["76:18:30"] = 70
    timeToVolumeDict["76:20:30"] = 60
    timeToVolumeDict["76:21:30"] = 90
    
    timeToVolumeDict["77:06:00"] = 70 #16 August 2016
    timeToVolumeDict["77:08:20"] = 70
    timeToVolumeDict["77:09:45"] = 70
    timeToVolumeDict["77:11:10"] = 70
    timeToVolumeDict["77:13:00"] = 70
    timeToVolumeDict["77:14:30"] = 100
    timeToVolumeDict["77:17:00"] = 80
    timeToVolumeDict["77:18:30"] = 60
    timeToVolumeDict["77:17:45"] = 40
    timeToVolumeDict["77:21:30"] = 80
    timeToVolumeDict["77:22:30"] = 30
    timeToVolumeDict["77:23:00"] = 50
        
    timeToVolumeDict["78:06:20"] = 40  #17 August 2016
    timeToVolumeDict["78:08:45"] = 70
    timeToVolumeDict["78:10:15"] = 50
    timeToVolumeDict["78:12:40"] = 70
    timeToVolumeDict["78:15:00"] = 70
    timeToVolumeDict["78:17:30"] = 80
    timeToVolumeDict["78:19:30"] = 100
    timeToVolumeDict["78:21:20"] = 130

    timeToVolumeDict["79:02:00"] = 70 #18 August 2016
    timeToVolumeDict["79:06:00"] = 50
    timeToVolumeDict["79:08:30"] = 65
    timeToVolumeDict["79:10:00"] = 65
    timeToVolumeDict["79:12:00"] = 70
    timeToVolumeDict["79:16:00"] = 60
    timeToVolumeDict["79:18:00"] = 60
    timeToVolumeDict["79:19:20"] = 40
    timeToVolumeDict["79:19:50"] = 40
    timeToVolumeDict["79:21:00"] = 70
    
    timeToVolumeDict["80:04:30"] = 60 #19 August 2016
    timeToVolumeDict["80:07:00"] = 70
    timeToVolumeDict["80:08:00"] = 70
    timeToVolumeDict["80:09:30"] = 50
    timeToVolumeDict["80:11:30"] = 75
    timeToVolumeDict["80:13:40"] = 50
    timeToVolumeDict["80:14:45"] = 70
    timeToVolumeDict["80:16:50"] = 70
    timeToVolumeDict["80:17:30"] = 55
    timeToVolumeDict["80:18:30"] = 30
    timeToVolumeDict["80:19:00"] = 40
    timeToVolumeDict["80:19:35"] = 15
    timeToVolumeDict["80:20:25"] = 55
    timeToVolumeDict["80:20:50"] = 10
    
    timeToVolumeDict["81:06:00"] = 65 #20 August 2016
    timeToVolumeDict["81:07:45"] = 65
    timeToVolumeDict["81:09:00"] = 40
    timeToVolumeDict["81:10:30"] = 70
    timeToVolumeDict["81:11:40"] = 35
    timeToVolumeDict["81:12:20"] = 15
    timeToVolumeDict["81:18:00"] = 100
    timeToVolumeDict["81:19:10"] = 80
    timeToVolumeDict["81:20:15"] = 60
    
    timeToVolumeDict["82:06:25"] = 70 #21 August 2016
    timeToVolumeDict["82:07:30"] = 70
    timeToVolumeDict["82:08:00"] = 20
    timeToVolumeDict["82:10:00"] = 50
    timeToVolumeDict["82:10:05"] = 40
    timeToVolumeDict["82:11:00"] = 80
    timeToVolumeDict["82:12:20"] = 60
    timeToVolumeDict["82:13:30"] = 60
    timeToVolumeDict["82:15:40"] = 70
    timeToVolumeDict["82:16:30"] = 55
    timeToVolumeDict["82:18:00"] = 70
    timeToVolumeDict["82:19:00"] = 45
    timeToVolumeDict["82:20:30"] = 95
    timeToVolumeDict["82:21:30"] = 30
        
    timeToVolumeDict["83:06:10"] = 40 #22 August 2016
    timeToVolumeDict["83:07:40"] = 60
    timeToVolumeDict["83:09:00"] = 65
    timeToVolumeDict["83:09:50"] = 60
    timeToVolumeDict["83:11:30"] = 90
    timeToVolumeDict["83:14:30"] = 120
    timeToVolumeDict["83:15:50"] = 30
    timeToVolumeDict["83:16:30"] = 70
    timeToVolumeDict["83:18:30"] = 80
    timeToVolumeDict["83:19:30"] = 30
    timeToVolumeDict["83:21:30"] = 50
    timeToVolumeDict["83:22:00"] = 50
    
    timeToVolumeDict["84:00:30"] = 75 #23 August 2016
    timeToVolumeDict["84:07:40"] = 110
    timeToVolumeDict["84:10:00"] = 70
    timeToVolumeDict["84:12:00"] = 80
    timeToVolumeDict["84:14:00"] = 80
    timeToVolumeDict["84:16:00"] = 80
    timeToVolumeDict["84:18:00"] = 40
    timeToVolumeDict["84:19:00"] = 50
    timeToVolumeDict["84:20:15"] = 80
    timeToVolumeDict["84:21:50"] = 50
    timeToVolumeDict["84:21:50"] = 50
        
    timeToVolumeDict["85:05:30"] = 70 #24 August 2016
    timeToVolumeDict["85:07:15"] = 70
    timeToVolumeDict["85:10:00"] = 70
    timeToVolumeDict["85:11:30"] = 85
    timeToVolumeDict["85:13:30"] = 80
    timeToVolumeDict["85:14:30"] = 60
    timeToVolumeDict["85:16:00"] = 55
    timeToVolumeDict["85:17:00"] = 25
    timeToVolumeDict["85:17:30"] = 20
    timeToVolumeDict["85:19:15"] = 90
    timeToVolumeDict["85:21:00"] = 80
    timeToVolumeDict["85:23:00"] = 60
    
    timeToVolumeDict["86:05:15"] = 70 #25 August 2016
    timeToVolumeDict["86:07:15"] = 30
    timeToVolumeDict["86:09:30"] = 80
    timeToVolumeDict["86:10:45"] = 70
    timeToVolumeDict["86:12:20"] = 80
    timeToVolumeDict["86:13:20"] = 50
    timeToVolumeDict["86:15:00"] = 80
    timeToVolumeDict["86:16:50"] = 80
    timeToVolumeDict["86:18:10"] = 50
    timeToVolumeDict["86:19:00"] = 40
    timeToVolumeDict["86:20:50"] = 145
    
    timeToVolumeDict["87:04:10"] = 75 #26 August 2016
    timeToVolumeDict["87:07:30"] = 70
    timeToVolumeDict["87:08:45"] = 80
    timeToVolumeDict["87:10:00"] = 85
    timeToVolumeDict["87:11:40"] = 70
    timeToVolumeDict["87:14:00"] = 70
    timeToVolumeDict["87:15:15"] = 60
    timeToVolumeDict["87:16:15"] = 80
    timeToVolumeDict["87:17:45"] = 30
    timeToVolumeDict["87:19:00"] = 60
    timeToVolumeDict["87:20:00"] = 50
    timeToVolumeDict["87:20:15"] = 80
    
    timeToVolumeDict["88:05:40"] = 80 #27 August 2016
    timeToVolumeDict["88:09:30"] = 70
    timeToVolumeDict["88:10:50"] = 80
    timeToVolumeDict["88:12:00"] = 80
    timeToVolumeDict["88:12:50"] = 60
    timeToVolumeDict["88:13:40"] = 100
    timeToVolumeDict["88:15:20"] = 60
    timeToVolumeDict["88:17:00"] = 85
    timeToVolumeDict["88:18:00"] = 70
    timeToVolumeDict["88:19:30"] = 65
    timeToVolumeDict["88:20:40"] = 80
    timeToVolumeDict["88:20:55"] = 25
    
    timeToVolumeDict["89:03:30"] = 80 #28 August 2016
    timeToVolumeDict["89:06:50"] = 60
    timeToVolumeDict["89:08:00"] = 50
    timeToVolumeDict["89:08:50"] = 30
    timeToVolumeDict["89:09:40"] = 80
    timeToVolumeDict["89:11:00"] = 55
    timeToVolumeDict["89:12:15"] = 50
    timeToVolumeDict["89:13:30"] = 80
    timeToVolumeDict["89:14:30"] = 60
    timeToVolumeDict["89:16:00"] = 60
    timeToVolumeDict["89:17:33"] = 75
    timeToVolumeDict["89:19:05"] = 35
    timeToVolumeDict["89:20:24"] = 45
    timeToVolumeDict["89:21:00"] = 80
    
    timeToVolumeDict["90:04:00"] = 80 #29 August 2016
    timeToVolumeDict["90:08:30"] = 70
    timeToVolumeDict["90:10:20"] = 150
    timeToVolumeDict["90:12:20"] = 80
    timeToVolumeDict["90:13:40"] = 80
    timeToVolumeDict["90:15:20"] = 90
    timeToVolumeDict["90:16:10"] = 60
    timeToVolumeDict["90:17:30"] = 40
    timeToVolumeDict["90:18:10"] = 55
    timeToVolumeDict["90:20:15"] = 80
    timeToVolumeDict["90:21:30"] = 80
        
    timeToVolumeDict["91:07:30"] = 80 #30 August 2016
    timeToVolumeDict["91:08:50"] = 80
    timeToVolumeDict["91:11:00"] = 90
    timeToVolumeDict["91:12:10"] = 60
    timeToVolumeDict["91:14:15"] = 50
    timeToVolumeDict["91:16:00"] = 100
    timeToVolumeDict["91:17:20"] = 60
    timeToVolumeDict["91:18:00"] = 70
    timeToVolumeDict["91:19:00"] = 95
    timeToVolumeDict["91:20:25"] = 80
    
    timeToVolumeDict["92:05:10"] = 80 #31 August 2016
    timeToVolumeDict["92:08:00"] = 80
    timeToVolumeDict["92:09:10"] = 70
    timeToVolumeDict["92:11:30"] = 90
    timeToVolumeDict["92:14:00"] = 85
    timeToVolumeDict["92:15:40"] = 120
    timeToVolumeDict["92:16:30"] = 40
    timeToVolumeDict["92:17:30"] = 40
    timeToVolumeDict["92:19:00"] = 35
    timeToVolumeDict["92:20:15"] = 65
    timeToVolumeDict["92:20:50"] = 80
        
    timeToVolumeDict["93:04:00"] = 75 #01 September 2016
    timeToVolumeDict["93:06:10"] = 50
    timeToVolumeDict["93:08:10"] = 40
    timeToVolumeDict["93:09:20"] = 75
    timeToVolumeDict["93:10:10"] = 40
    timeToVolumeDict["93:12:00"] = 120
    timeToVolumeDict["93:13:20"] = 60
    timeToVolumeDict["93:14:30"] = 70
    timeToVolumeDict["93:16:00"] = 75
    timeToVolumeDict["93:19:00"] = 100
    timeToVolumeDict["93:21:05"] = 95
    
    timeToVolumeDict["94:03:10"] = 80 #02 September 2016
    timeToVolumeDict["94:07:00"] = 50
    timeToVolumeDict["94:08:00"] = 50
    timeToVolumeDict["94:09:00"] = 60
    timeToVolumeDict["94:10:40"] = 100
    timeToVolumeDict["94:13:40"] = 120
    timeToVolumeDict["94:15:10"] = 60
    timeToVolumeDict["94:16:15"] = 65
    timeToVolumeDict["94:17:45"] = 90
    timeToVolumeDict["94:18:30"] = 60
    timeToVolumeDict["94:19:45"] = 60
    timeToVolumeDict["94:21:35"] = 50
    
    timeToVolumeDict["95:05:30"] = 60 #03 September 2016
    timeToVolumeDict["95:08:00"] = 60
    timeToVolumeDict["95:09:00"] = 80
    timeToVolumeDict["95:11:30"] = 70
    timeToVolumeDict["95:13:30"] = 100
    timeToVolumeDict["95:14:30"] = 60
    timeToVolumeDict["95:16:00"] = 50
    timeToVolumeDict["95:17:00"] = 50
    timeToVolumeDict["95:18:40"] = 70
    timeToVolumeDict["95:21:00"] = 115
    
    timeToVolumeDict["96:03:35"] = 80 #04 September 2016
    timeToVolumeDict["96:06:00"] = 50
    timeToVolumeDict["96:08:15"] = 60
    timeToVolumeDict["96:08:15"] = 85
    timeToVolumeDict["96:10:15"] = 130
    timeToVolumeDict["96:11:45"] = 50
    timeToVolumeDict["96:12:45"] = 70
    timeToVolumeDict["96:14:15"] = 80
    timeToVolumeDict["96:15:15"] = 90
    timeToVolumeDict["96:16:50"] = 65
    timeToVolumeDict["96:21:00"] = 225 # merge of multiple feeds
    
    timeToVolumeDict["97:02:15"] = 80 #05 September 2016
    timeToVolumeDict["97:05:30"] = 60
    timeToVolumeDict["97:06:50"] = 45
    timeToVolumeDict["97:08:45"] = 95
    timeToVolumeDict["97:10:00"] = 80
    timeToVolumeDict["97:11:10"] = 80
    timeToVolumeDict["97:14:30"] = 75
    timeToVolumeDict["97:15:20"] = 75
    timeToVolumeDict["97:16:30"] = 65
    timeToVolumeDict["97:18:30"] = 85
    timeToVolumeDict["97:20:30"] = 120
    
    timeToVolumeDict["98:00:00"] = 80 #06 September 2016
    timeToVolumeDict["98:03:30"] = 75
    timeToVolumeDict["98:07:30"] = 80
    timeToVolumeDict["98:09:00"] = 80
    timeToVolumeDict["98:10:00"] = 90
    timeToVolumeDict["98:11:00"] = 100
    timeToVolumeDict["98:13:15"] = 100
    timeToVolumeDict["98:15:15"] = 80
    timeToVolumeDict["98:15:45"] = 50
    timeToVolumeDict["98:19:30"] = 65
    timeToVolumeDict["98:20:15"] = 70
    timeToVolumeDict["98:21:15"] = 70
    
    timeToVolumeDict["99:05:00"] = 80 #07 September 2016
    timeToVolumeDict["99:07:05"] = 60
    timeToVolumeDict["99:08:30"] = 80
    timeToVolumeDict["99:10:45"] = 100
    timeToVolumeDict["99:13:30"] = 100
    timeToVolumeDict["99:15:00"] = 70
    timeToVolumeDict["99:15:45"] = 60
    timeToVolumeDict["99:16:45"] = 75
    timeToVolumeDict["99:18:20"] = 60
    timeToVolumeDict["99:19:40"] = 90
    timeToVolumeDict["99:21:30"] = 50
    timeToVolumeDict["99:22:00"] = 70
    
    timeToVolumeDict["100:07:30"] = 80 #08 September 2016
    timeToVolumeDict["100:09:00"] = 100
    timeToVolumeDict["100:10:10"] = 70
    timeToVolumeDict["100:12:00"] = 80
    timeToVolumeDict["100:13:00"] = 65
    timeToVolumeDict["100:14:45"] = 120
    timeToVolumeDict["100:16:50"] = 120
    timeToVolumeDict["100:21:00"] = 170 # merged possibly
    
    timeToVolumeDict["101:06:00"] = 80 #09 September 2016
    timeToVolumeDict["101:08:00"] = 80
    timeToVolumeDict["101:09:10"] = 75
    timeToVolumeDict["101:11:30"] = 200 #merged possibly
    timeToVolumeDict["101:14:00"] = 130
    timeToVolumeDict["101:16:00"] = 75
    timeToVolumeDict["101:18:00"] = 80
    timeToVolumeDict["101:20:30"] = 175
    timeToVolumeDict["101:22:00"] = 45
    
    timeToVolumeDict["102:06:15"] = 80 #10 September 2016
    timeToVolumeDict["102:08:45"] = 70
    timeToVolumeDict["102:10:20"] = 60
    timeToVolumeDict["102:11:00"] = 70
    timeToVolumeDict["102:11:00"] = 70
    timeToVolumeDict["102:13:00"] = 90
    timeToVolumeDict["102:14:10"] = 85
    timeToVolumeDict["102:16:30"] = 90
    timeToVolumeDict["102:19:00"] = 90
    timeToVolumeDict["102:21:00"] = 180
    
    timeToVolumeDict["103:04:45"] = 50 #11 September 2016
    timeToVolumeDict["103:08:10"] = 75
    timeToVolumeDict["103:10:30"] = 80
    timeToVolumeDict["103:11:00"] = 30
    timeToVolumeDict["103:14:45"] = 200
    timeToVolumeDict["103:16:20"] = 60
    timeToVolumeDict["103:17:40"] = 60
    timeToVolumeDict["103:20:00"] = 140
    timeToVolumeDict["103:21:00"] = 100
    timeToVolumeDict["103:21:20"] = 50
    
    timeToVolumeDict["104:06:35"] = 80 #12 September 2016
    timeToVolumeDict["104:09:00"] = 65
    timeToVolumeDict["104:10:00"] = 80
                            
    
    
    # Create list of Time & Volume
    volume  = [] # Volume of Milk Fed
    time    = [] # Time of Feeding (day:hour:minute). A day starts/ends after midnight 24:00
    minutes = []
    hours   = []
    days    = []
    # For-loop: All timestamps
    for t in timeToVolumeDict:
        volume.append(timeToVolumeDict[t])
        time.append(t)
        minutes.append( GetMinutes(t) )
        hours.append( GetHours(t) )
        days.append( GetDays(t) )


    # Get cumulative volumes of milk consumed
    dayToCumulative = {}
    # For-loop: All timestamps
    for time in timeToVolumeDict:

        day = time.split(":")[0]
        vol = timeToVolumeDict[time]

        if day not in dayToCumulative:
            dayToCumulative[day] = 0

        # Add same-day entries to get cumulative
        dayToCumulative[day] += vol

        
    #================================================================================================
    # Numpy arrays (x=Time, y=Volume)
    #================================================================================================
    nEntries  = len(volume)
    xHours    = numpy.ndarray( [nEntries] )
    yVolume   = numpy.ndarray( [nEntries] )
    # For-loop: All hours
    for counter, h in enumerate(hours):
        xHours[counter]  = h
        yVolume[counter] = volume[counter]

        
    # x=Time, y=Cumulative Volume
    nDays    = len(dayToCumulative)+1
    xDays    = numpy.ndarray( [nDays] )
    yTotal24 = numpy.ndarray( [nDays] )
    # For-loop: All days
    xDays[0]    = 0
    yTotal24[0] = 0

    # For-loop: All day-cumulative pairs
    for counter, day in enumerate(dayToCumulative):        
        xDays[counter+1]    = ConvertDayToHours(day)
        yTotal24[counter+1] = dayToCumulative[day]
        
        
    #================================================================================================
    # TGraphs
    #================================================================================================
    # Create
    g1 = ROOT.TGraph(nDays   , xDays , yTotal24)
    g2 = ROOT.TGraph(nEntries, xHours, yVolume)

    # Customise
    CustomiseTGraph(g1, ROOT.kFullCross , 1.2, ROOT.kBlue-4, "", "#Deltat (hours)", "Milk Volume (ml)", False)
    CustomiseTGraph(g2, ROOT.kFullCircle, 0.3, ROOT.kBlack , "", "#Deltat (hours)", "Milk Volume (ml)", False) #ROOT.kOpenCircle
    
    #================================================================================================
    # TLines
    #================================================================================================
    # Horizontal 
    xMax     = max(xHours)+10 #last point not visible without the "+10"
    dailyMin = babyMass * dailyMinPerKg
    dailyMax = babyMass * dailyMaxPerKg

    # Min/max range of milk intakes according to baby's weights
    minLine  = GetLine(dailyMin, dailyMin, 0.0, xMax, 3, ROOT.kSolid, ROOT.kRed-3)
    maxLine  = GetLine(dailyMax, dailyMax, 0.0, xMax, 3, ROOT.kSolid, ROOT.kGreen-3)

    # Typical range of milk intakes is 19-30 oz per day (570-900 mL per day).
    typicalMin = GetLine(570.0, 570.0, 0.0, xMax, 3, ROOT.kDashed, ROOT.kRed-3)
    typicalMax = GetLine(900.0, 900.0, 0.0, xMax, 3, ROOT.kDashed, ROOT.kGreen-3)

    # Vertical
    vLines = []
    if addDayLines:
        # For-loop: All days
        for d in range(1, nDays):
            hour = d*24
            vLines.append( GetLine(0.0, yMax, hour, hour, 1, ROOT.kDotted, ROOT.kBlack) )

    if addWeekLines:
        # For-loop: All weeks
        for d in range(1, nDays):
            if (d % 7 == 0):
                hour = d*24
                vLines.append( GetLine(0.0, yMax, hour, hour, 1, ROOT.kDotted, ROOT.kGray) )

    if addMonthLines:
        # For-loop: All weeks
        for d in range(1, nDays):
            if (d % 28 == 0):
                hour = d*24
                vLines.append( GetLine(0.0, yMax, hour, hour, 1, ROOT.kDotted, ROOT.kBlack) )

    
    #================================================================================================
    # TLegend
    #================================================================================================
    # Create
    myLeg = GetLegend(0.11, 0.60, 0.38, 0.88)

    # Add entries
    myLeg.AddEntry(g1     , "24h Total (00:00 #rightarrow 23:59)", "P")
    myLeg.AddEntry(g2     , "Single Feeding"   , "P")
    myLeg.AddEntry(minLine, "Daily Min (%s kg) " % babyMass, "L")

    if includeMaxLine:
        myLeg.AddEntry(maxLine, "Daily Max (%s kg) " % babyMass, "L")

    if includeTypLine:
        myLeg.AddEntry(typicalMin, "Typical Min (570 mL)" , "L")
        myLeg.AddEntry(typicalMax, "Typical Max (900 mL)" , "L")

        
    #================================================================================================    
    # Canvas
    #================================================================================================
    canvas = ROOT.TCanvas("iro", "iro", 1)


    #================================================================================================
    # Draw objects
    #================================================================================================
    g1.Draw("AP")
    g1.GetXaxis().SetRangeUser(xMin, xMax)
    g1.SetMinimum(yMin)
    g1.SetMaximum(yMax)
    g2.Draw("P,SAME")
    minLine.Draw()
    if includeMaxLine:
        maxLine.Draw()

    if includeTypLine:
        typicalMin.Draw()
        typicalMax.Draw()

    for l in vLines:
        l.Draw()
    myLeg.Draw()

    # Re-draw the TGraphs (to get data points in-front-of hLines drawn)
    g1.Draw("P, same")
    g2.Draw("P,same")
    canvas.Update()

    #================================================================================================    
    # Text
    #================================================================================================
    import datetime
    today = datetime.date.today()
    t = ROOT.TText()
    t.SetTextSize(0.03)
    t.SetTextAngle(0.0) #30.0)
    t.DrawTextNDC(0.72, 0.85, "updated %s " % str(today) )
    #t.DrawTextNDC(0.72, 0.80, "started 2016-06-18") #?

    
    #================================================================================================
    # Save 
    #================================================================================================
    canvas.SaveAs(canvas.GetName() + ".png")

    return


#================================================================================================
# Auxiliary Functions
#================================================================================================
def GetSeconds(time):
    t    = time.split(':')
    secs = int(t[0]) * 86400 + int(t[1]) * 3600 + int(t[2]) * 60 # [0] = days, [1] = hours, [2] = minutes
    return secs


def GetMinutes(time):
    secs    = GetSeconds(time)
    convert = 60
    minutes = secs/convert
    return minutes


def GetHours(time):
    secs  = GetSeconds(time)
    convert = 60*60
    hours   = secs/convert
    return hours


def GetDays(time):
    secs  = GetSeconds(time)
    convert = 60*60*24
    days = secs/convert
    return days


def ConvertDayToHours(days):
    ''' 
    1 day has 24 hours. So the day with index 0 will return 24, not 0.
    '''
    return (int(days)+1) * 24


def GetLine(yMin, yMax, xMin, xMax, lWidth=3, lStyle=ROOT.kSolid, lColour=ROOT.kBlack):
    '''
    '''
    hLine = ROOT.TLine(xMin, yMin, xMax, yMax)
    hLine.SetLineWidth(lWidth)
    hLine.SetLineStyle(lStyle)
    hLine.SetLineColor(lColour)
    return hLine


def GetLegend(xMin, yMin, xMax, yMax):
    '''
    '''
    myLeg = ROOT.TLegend(xMin, yMin, xMax, yMax)
    myLeg.SetFillStyle(3001)
    # myLeg.SetFillColor(ROOT.kOrange)
    myLeg.SetTextSize(0.03)
    myLeg.SetLineWidth(2)
    myLeg.SetLineColor(ROOT.kBlack)
    myLeg.SetBorderSize(0)
    return myLeg


def CustomiseTGraph(graph, markerStyle, markerSize, myColour, gTitle, xTitle, yTitle, fillGraph=True):

    # General 
    graph.SetTitle(gTitle)
    graph.GetXaxis().SetTitle(xTitle)
    graph.GetYaxis().SetTitle(yTitle)
    graph.GetYaxis().SetTitleOffset(1.20)

    # Marker Style
    graph.SetMarkerStyle(markerStyle)
    graph.SetMarkerSize(markerSize)
    graph.SetMarkerColor(myColour)

    # Line Style
    graph.SetLineWidth(3);
    graph.SetLineColor(myColour)


    if fillGraph==True:
        graph.SetFillColor(myColour)
    graph.SetFillStyle(3001)

    return


#================================================================================================
# Main Function
#================================================================================================
if __name__ == "__main__":

    main()
    
    if not batchMode:
        raw_input("\n*** DONE! Press \"ENTER\" key exit session: ")
    
