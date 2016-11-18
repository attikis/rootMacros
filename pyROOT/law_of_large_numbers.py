#!/usr/bin/env python

import ROOT
import sys
import math

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
hList = []
mean  = [10]
mean.extend([10]*5)
var         = [2.0]
var.extend([2.0]*5)


stdDiv      = []
for i in range(0, len(var)): 
    stdDiv.append(math.sqrt(var[i]))

nFillPoints = 20
twoPi       = 2*ROOT.TMath.Pi()
colours     = [ROOT.kBlue, ROOT.kOrange, ROOT.kBlack, ROOT.kRed, ROOT.kPink, ROOT.kBlue-3, ROOT.kOrange-3, ROOT.kTeal, ROOT.kRed-4, ROOT.kMagenta]

######################################################################
def main():

    print "*** WARNING! This is NOT complete yet.."
    sys.exit()

    for i in range(0, len(var)):
        # Create Histograms
        h = CreateTH1F(hName = "Normal_%i" % (i), hTitle = "Normal_%i" % (i), binWidthX = 1.0, xMin = 0.0, xMax = 20.0, xMean = None) 
        hList.append(h)

    # Loop over all histograms and fill them using the random number generator "gRandom" 
    counter = 0
    for h, colour, mu, sigma in zip(hList, colours, mean, stdDiv):
        for j in range (0, nFillPoints):
            h.Fill( ROOT.gRandom.Gaus(mu, sigma) )

        # Customise histos
        CustomiseTH1(h, colour, False)

    # Draw histos
    DrawHistoList(hList, None )

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
        #if h is not hList[-1]:
        myLeg.AddEntry(h, "#mu = %0.2f , #sigma = %0.2f" % (mean[counter], stdDiv[counter]))

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



