#!/usr/bin/env python

import ROOT

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
hList = []
mean  = []
cList = [ROOT.kBlue, ROOT.kOrange, ROOT.kRed, ROOT.kBlack, ROOT.kTeal]
nTrials = [30, 60, 30+60]
p       = [0.5, 0.5, 0.5]
for i in range(0, len(nTrials)):
    mean.append(nTrials[i]*p[i])
nFillPoints = 100000

######################################################################
def main():

    # Create Histograms. Number of bins = 200, Max = 100, Min = -100.
    nHistos  = len(nTrials)
    for i in range(0, nHistos):
        h = CreateTH1F(hName = "Binomial_Sums" + str(i), hTitle = "Binomial_Sums" + str(i), binWidthX = 1, xMin = -5.0, xMax = 80.0, xMean = mean[i]) 
        hList.append(h)

    # Loop to fill the histograms using the random number generator "gRandom" 
    counter = 0
    for h in hList:
        for i in range (0, nFillPoints):
            h.Fill(ROOT.gRandom.Binomial(nTrials[counter], p[counter]))
        counter += 1

    counter = 0
    for h, colour in zip(hList, cList):
        CustomiseTH1(h, colour, False)
        counter+=1

    # Draw all histograms in hList
    DrawHistoList(hList, 1)

    return

######################################################################
def DrawHistoList(hList, fNormalisationFactor=None):
    
    # Take care of legend
    myLeg = ROOT.TLegend(0.55, 0.7, 0.9, 0.9, "" )
    myLeg.SetFillStyle(0)
    myLeg.SetLineWidth(0)
    myLeg.SetBorderSize(0)
    myLeg.SetShadowColor(ROOT.kWhite)
    myLeg.SetTextSize(0.03)
    myLeg.SetTextFont(62)
    
    counter = 0
    yMax    = 0.0

    # Create Canvas
    cName = "c%i_" % (counter) + hList[0].GetName()
    c = ROOT.TCanvas(cName, cName, 1)

    # Draw histograms
    for h in hList:
        nBinsX = h.GetNbinsX()
        myLeg.AddEntry(h, "p = %s , n = %s , np = %s" % (str(p[counter]), str(nTrials[counter]), str(p[counter]*nTrials[counter])))

        if fNormalisationFactor is not None:
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



