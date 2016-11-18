#!/usr/bin/env python

import ROOT
from decimal import *
# Set the precision you want for python calculations
getcontext().prec = 100

bBatchMode = True
ROOT.gROOT.SetStyle("Plain")
ROOT.gROOT.SetBatch(bBatchMode)

def main():
    
    # Global definitions
    nFills   = +50
    nSamples = +100 # expect sigma_{s} = sigma/sqrt(nSamples)
    xmin     = -40
    xmax     = +80

    # Declaration
    hList     = []
    meanList  = []
    twoPi     = 2*ROOT.TMath.Pi()

    # Create nSamples x histograms in total
    for s in range(1, nSamples+1):

        # Create and customise histos
        h = CreateTH1D(hName = "h_%s" % (str(s)), hTitle = "h_%s" % (str(s)), binWidthX = 1.0, xMin = xmin, xMax = xmax, xMean = None)
        CustomiseTH1(h, ROOT.kRed)

        # Loop to fill the histograms using the random number generator "gRandom" 
        for i in range (0, nFills):
            h.Fill(ROOT.gRandom.Gaus(20, 40))
            #h.Fill(ROOT.gRandom.Uniform(xmin, xmax))
            #h.Fill(ROOT.gRandom.Exp(float(xmin+xmax)/2))
            #h.Fill(ROOT.gRandom.Binomial(100, 0.2))
            #h.Fill(ROOT.gRandom.Poisson(3))

        # Get histo mean andd append to a list of means
        meanList.append(h.GetMean())

        # Append histo to hList for drawing
        hList.append(h)

    # Create and customise the histogram of the means
    hMean = CreateTH1D(hName = "Central_Limit_Theorem", hTitle = "Central_Limit_Theorem", binWidthX = 1.0, xMin = xmin, xMax = xmax, xMean = None)
    CustomiseTH1(hMean, ROOT.kBlue+2)

    # Loop over all means in the meanList and fill the Central_Limit_Theorem histogram
    for mean in meanList:
        hMean.Fill(mean)
        
    # Fit a gaussian function to it
    hMean.Fit("gaus", "Q", "", 10, 30)
    hList.append(hMean)
    print "*** Fitted function parameters:\n", hMean.GetFunction("gaus").Print()

    # Draw all histograms in hList
    DrawHistoList(hList)

    return

######################################################################
def GetMyMean(h):
    
    nBinsX   = h.GetNbinsX()+1 
    integral = h.Integral(1, nBinsX-1)
    mean     = 0.0
    val      = 0.0

    # Sum over all bins and get the mean using: mean = Sum_i (x_i * prob_i)
    print "="*50
    print "bin | x_i | p_i | x_i*p_i | mean | h.GetMean()"
    print "="*50
    for i in range(0, nBinsX+1):
        x_i  = h.GetBinCenter(i)
        p_i  = h.GetBinContent(i)/integral
        mu_i = x_i*p_i
        mean += mu_i
        print "%i | %0.2f | %0.2f | %0.2f | %0.5f | " % (i, x_i, p_i, mu_i, mean)
    print "%s | %s | %s | %s | %0.5f | " % (" "*2, " "*4, " "*4, " "*4,  mean)
    print "%s | %s | %s | %s | %s | %0.5f" % (" "*2, " "*4, " "*4, " "*4, " "*8, h.GetMean())

    return mean

######################################################################
def DrawHistoList(hList):
    
    counter = 0

    for h in hList:
        cName = "c%i_" %(counter) + h.GetName()
        c = ROOT.TCanvas(cName, cName, 1)
        h.Draw() #DrawNormalized("HIST9")
        c.Update()
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
        xMin  =  xMean*(-3)
    if xMax == None:
        xMax  =  xMean*(+3)
    nBinsX = int((xMax-xMin)/binWidthX)

    h = ROOT.TH1F(hName, hTitle, nBinsX, xMin, xMax)
    
    return h

######################################################################
def CreateTH1D(hName, hTitle, binWidthX, xMin, xMax, xMean):
    
    if xMin == None:
        xMin  =  xMean*(-3)
    if xMax == None:
        xMax  =  xMean*(+3)
    nBinsX = int((xMax-xMin)/binWidthX)

    h = ROOT.TH1D(hName, hTitle, nBinsX, xMin, xMax)
    
    return h

######################################################################
if __name__ == "__main__":

    main()

    if bBatchMode == False:
        raw_input("\n*** DONE! Press \"ENTER\" key exit session: ")



