#!/usr/bin/env python

import ROOT
import sys

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
hList      = []
lambdaVals = [10]
nTrials    = [1000]
#nTrials    = [20, 20, 20, 20]
twoPi      = 2*ROOT.TMath.Pi()
colours    = [ROOT.kOrange, ROOT.kBlack, ROOT.kGreen-3, ROOT.kBlue, ROOT.kRed]
######################################################################
def main():

    counter = 0
    # Loop over all lambda parameters
    for l, colour, n in zip(lambdaVals, colours, nTrials):

        # Create Histograms. Number of bins = 200, Max = 100, Min = -100.
        h = CreateTH1F(hName = "Poisson_%i" % (counter), hTitle = "Poisson_%i" % (counter), binWidthX = 1.0, xMin = -1.0, xMax = 30.0, xMean = None) 
        h.SetTitle("")
        
        # Customise the histograms
        CustomiseTH1(h, colour, True)

        # Fill the histograms using the random number generator "gRandom" 
        for i in range (0, n):
            h.Fill( ROOT.gRandom.Poisson(l) )
            
        # Append histograms to drawing list
        hList.append(h)
        counter += 1

    # Draw the histograms
    DrawHistoList(hList, 1)

    return

######################################################################
def DrawHistoList(hList, fNormalisationFactor=None):
    
    # Take care of legend
    myLeg = CreateLegend(0.6, 0.7, 0.9, 0.9, "" )
    
    counter = 0
    yMax = 0.0

    # Create Canvas
    #cName = "c%i_" % (counter) + hList[0].GetName()
    cName = "c_" + hList[0].GetName()
    c = ROOT.TCanvas(cName, cName, 1)

    # Draw histograms
    for h in hList:
        myLeg.AddEntry(h, "#lambda = %0.0f, n = %i" % (lambdaVals[counter], nTrials[counter]), "l")
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
def CreateLegend(xMin, yMin, xMax, yMax, Header):

    myLeg = ROOT.TLegend(xMin, yMin, xMax, yMax, Header)
    myLeg.SetFillStyle(0)
    myLeg.SetLineWidth(0)
    myLeg.SetBorderSize(0)
    myLeg.SetShadowColor(ROOT.kWhite)
    myLeg.SetTextSize(0.03)
    myLeg.SetTextFont(62)
    
    return myLeg 

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



