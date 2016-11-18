#!/usr/bin/env python

import ROOT

ROOT.gROOT.SetStyle("Plain")

def main():
    
    # Global definitions
    hList = []

    # Poisson Distribution Parameters
    lambdaPoisson    = 3
    # Binomial Distribution Parameters for Limit Binomial -> Poisson
    nTrialsBinomial  = 1000
    pBinomial        = 0.005
    meanBinomial     = nTrialsBinomial*pBinomial

    # Create Histograms. Number of bins = 200, Max = 100, Min = -100.
    hPoisson  = CreateTH1F(hName = "Poisson" , hTitle = "Poisson" , binWidthX = 1, xMin = 0.0, xMax = None, xMean = lambdaPoisson)
    hBinomial = CreateTH1F(hName = "Binomial", hTitle = "Binomial", binWidthX = 1, xMin = 0.0, xMax = None, xMean = 100*0.5) 
    hBinomialPoissonLimit = CreateTH1F(hName = "Binomial_To_Poisson_Limit", hTitle = "Binomial_To_Poisson_Limit", binWidthX = 1, xMin = 0.0, xMax = None, xMean = meanBinomial) 

    # Loop to fill the histograms using the random number generator "gRandom" 
    for i in range (0, 100000):
    
        hPoisson.Fill(ROOT.gRandom.Poisson(lambdaPoisson))
        hBinomial.Fill(ROOT.gRandom.Binomial(100, 0.5))
        hBinomialPoissonLimit.Fill(ROOT.gRandom.Binomial(nTrialsBinomial, pBinomial))
    
    # Customise histos
    CustomiseTH1(hPoisson, ROOT.kRed)
    CustomiseTH1(hBinomial, ROOT.kBlue)
    CustomiseTH1(hBinomialPoissonLimit, ROOT.kOrange)

    # Append histos to a list
    hList.append(hPoisson)
    hList.append(hBinomial)
    hList.append(hBinomialPoissonLimit)

    # Draw all histograms in hList
    DrawHistoList(hList)

    return

######################################################################
def DrawHistoList(hList):
    
    counter = 0

    for h in hList:
        cName = "c%i_" %(counter) + h.GetName()
        c = ROOT.TCanvas(cName, cName, 1)
        h.DrawNormalized("HIST9")
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



