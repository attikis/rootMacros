#!/usr/bin env python
import ROOT

def FindFirstBinAbove(TH1, threshold, axis):
    if(axis!=1):
        axis = 1
        print "Warning, Invalid axis number. X-axis will be assumed"
    #nBins = TH1.fXaxis().GetNbins()
    nBins = TH1.GetNbinsX()
    for bin in range (1, nBins+1, +1):
        if(TH1.GetBinContent(bin) > threshold):
            return bin
    return -1
