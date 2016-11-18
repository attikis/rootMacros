#!/usr/bin/env python

import ROOT
import sys

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
hList  = []
mean   = 0.0
stdDiv = 1.0
nFillPoints = 100000
twoPi = 2*ROOT.TMath.Pi()

######################################################################
def main():

    # Create Histograms. Number of bins = 200, Max = 100, Min = -100.
    h = CreateTH1F(hName = "Normal", hTitle = "Normal", binWidthX = 0.1, xMin = -5.0, xMax = 5.0, xMean = mean) 
    hList.append(h)

    # Loop to fill the histograms using the random number generator "gRandom" 
    for i in range (0, nFillPoints):
        h.Fill( ROOT.gRandom.Gaus(mean, stdDiv) )

    CustomiseTH1(h, ROOT.kBlue, False)
    DrawHistoList(hList, 1)

    return

######################################################################
def DrawHistoList(hList, fNormalisationFactor=None):
    
    # Take care of legend
    myLeg = ROOT.TLegend(0.70, 0.7, 0.9, 0.9, "" )
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
        myLeg.AddEntry(h, "#mu = %s , #sigma = %s" % (str(mean), str(stdDiv)))

        if isinstance(h, ROOT.TH1):
            nBinsX = h.GetNbinsX()

        if fNormalisationFactor is not None and isinstance(h, ROOT.TH1):
            h.Scale(1/h.Integral(0, nBinsX+1))
            
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



