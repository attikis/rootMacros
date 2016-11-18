#!/usr/bin/env python

import ROOT

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat("miouren")

def main():
    
    ### Global definitions
    hList = []

    ### Poisson Distribution Parameters
    lambdaPoisson    = 3

    ### Binomial Distribution Parameters for Limit Binomial -> Poisson
    nTrials    = 100000
    nTrials_1  = int(nTrials*0.8)
    mu_1       = 0.1
    sigma_1    = 5.0

    nTrials_2  = nTrials-nTrials_1
    mu_2       = 0.1
    sigma_2    = sigma_1*1.2


    ### Create Histograms. Number of bins = 200, Max = 100, Min = -100.
    hGaussian_1   = CreateTH1F(hName = "Gaussian_1"   , hTitle = "Gaussian_1"   , binWidthX = 0.5, xMin = -20.0, xMax = 20.0, xMean = mu_1)
    hGaussian_2   = CreateTH1F(hName = "Gaussian_2"   , hTitle = "Gaussian_2"   , binWidthX = 0.5, xMin = -20.0, xMax = 20.0, xMean = mu_2)
    hGaussian_Sum = CreateTH1F(hName = "Gaussian_Sum" , hTitle = "Gaussian_Sum" , binWidthX = 0.5, xMin = -20.0, xMax = 20.0, xMean = mu_2)
    hGaussian_Add = CreateTH1F(hName = "Gaussian_Add" , hTitle = "Gaussian_Add" , binWidthX = 0.5, xMin = -20.0, xMax = 20.0, xMean = mu_2)    

    ### Loop to fill the histograms using the random number generator "gRandom" 
    for i in range (0, nTrials_1):
    
        hGaussian_1.Fill(ROOT.gRandom.Gaus(mu_1, sigma_1))
        hGaussian_Sum.Fill( ROOT.gRandom.Gaus(mu_1, sigma_1) + ROOT.gRandom.Gaus(mu_2, sigma_2) )
        
    ### Loop to fill the histograms using the random number generator "gRandom" 
    for i in range (0, nTrials_2):
    
        hGaussian_2.Fill(ROOT.gRandom.Gaus(mu_2, sigma_2))
        hGaussian_Sum.Fill( ROOT.gRandom.Gaus(mu_1, sigma_1) + ROOT.gRandom.Gaus(mu_2, sigma_2) )

    hGaussian_Add.Add( hGaussian_1 )
    hGaussian_Add.Add( hGaussian_2 )
    
    ### Customise histos
    CustomiseTH1(hGaussian_1  , ROOT.kRed)
    CustomiseTH1(hGaussian_2  , ROOT.kBlue)
    CustomiseTH1(hGaussian_Sum, ROOT.kOrange)
    CustomiseTH1(hGaussian_Add, ROOT.kBlack)

    ### Append histos to a list
    hList.append(hGaussian_1)
    hList.append(hGaussian_2)
    hList.append(hGaussian_Sum)
    hList.append(hGaussian_Add)

    ### Draw all histograms in hList
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



