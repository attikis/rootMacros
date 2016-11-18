#!/usr/bin/env python

import ROOT
import sys
import math

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
hList       = []
mean        = [10.0, 0.0, 0.0+10.0] # means add
var         = [4.0, 2.0, 2.0+4.0] # variances add, stdDiv must be added quadratically
stdDiv      = []
for i in range(0, len(var)): 
    stdDiv.append(math.sqrt(var[i]))

nFillPoints = 100000
twoPi       = 2*ROOT.TMath.Pi()
myColours   = [ROOT.kBlue, ROOT.kOrange, ROOT.kBlack, ROOT.kRed, ROOT.kPink]

######################################################################
def main():

    # Create Histograms. Number of bins = 200, Max = 100, Min = -100.
    h1 = CreateTH1F(hName = "Normal1", hTitle = "Normal1", binWidthX = 0.1, xMin = -10.0, xMax = 20.0, xMean = None) 
    hList.append(h1)

    h2 = CreateTH1F(hName = "Normal2", hTitle = "Normal2", binWidthX = 0.1, xMin = -10.0, xMax = 20.0, xMean = None)
    hList.append(h2)

    h3 = CreateTH1F(hName = "Normal3", hTitle = "Normal3", binWidthX = 0.1, xMin = -10.0, xMax = 20.0, xMean = None)
    hList.append(h3)

    h4 = CreateTH1F(hName = "Normal4", hTitle = "Normal4", binWidthX = 0.1, xMin = -10.0, xMax = 20.0, xMean = None)
    hList.append(h4)

    # Loop to fill the histograms using the random number generator "gRandom" 
    counter = 0
    for h in hList:
        for j in range (0, nFillPoints):
            if h == hList[-1]:
                h.Fill( ROOT.gRandom.Gaus(mean[0], stdDiv[0]) + ROOT.gRandom.Gaus(mean[1], stdDiv[1]) )
            else:
                h.Fill( ROOT.gRandom.Gaus(mean[counter], stdDiv[counter]) )
        CustomiseTH1(h, myColours[counter], False)
        counter += 1
    
    DrawHistoList(hList, 1 )

    return

######################################################################
def DrawHistoList(hList, fNormalisationFactor=None):
    
    # Take care of legend
    myLeg = ROOT.TLegend(0.65, 0.7, 0.9, 0.9, "" )
    myLeg.SetFillStyle(0)
    myLeg.SetLineWidth(0)
    myLeg.SetBorderSize(0)
    myLeg.SetShadowColor(ROOT.kWhite)
    myLeg.SetTextSize(0.03)
    myLeg.SetTextFont(62)
    
    counter = 0
    yMax = 0.0

    # Create Canvas
    cName = "c%i_" % (counter) + hList[0].GetName()
    c = ROOT.TCanvas(cName, cName, 1)
    
    # Draw histograms
    for h in hList:
        if h is not hList[-1]:
            myLeg.AddEntry(h, "#mu = %0.2f , #sigma = %0.2f" % (mean[counter], stdDiv[counter]))
        else:
            myLeg.AddEntry(h, "#mu = ? , #sigma = ?")

        if isinstance(h, ROOT.TH1):
            nBinsX = h.GetNbinsX()

        if fNormalisationFactor is not None and isinstance(h, ROOT.TH1):
            h.Scale(1/h.Integral())
            
        if counter==0:
            h.Draw("H9")
        else:
            h.Draw("H9" + "SAME")

        if h.GetMaximum() >= yMax:
            yMax = h.GetMaximum()
        
        counter += 1


    for h in hList:    
        h.GetYaxis().SetRangeUser(0.0, yMax*1.2)

    myLeg.Draw()
    c.SaveAs(cName+".png")
        
    return
######################################################################
def CustomiseTH1(histo, myColour, fillHisto=True):
    
    if fillHisto==True:
        histo.SetFillColor(myColour)

    histo.SetFillStyle(3001)
    histo.SetLineColor(myColour)
    histo.SetLineWidth(2)

    return

######################################################################
def CreateTH1F(hName, hTitle, binWidthX, xMin, xMax, xMean):
    
    if xMin == None:
        xMin  =  xMean*(-5)
    if xMax == None:
        xMax  =  xMean*(+5)
    nBinsX = int((xMax-xMin)/binWidthX)

    h = ROOT.TH1F(hName, hTitle, nBinsX, xMin, xMax)
    
    return h

######################################################################
if __name__ == "__main__":

    main()

    #raw_input("\n*** DONE! Press \"ENTER\" key exit session: ")



