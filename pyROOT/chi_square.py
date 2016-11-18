#!/usr/bin/env python

import ROOT
import sys

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default
ROOT.gSystem.Load("libMathCore");

# Global definitions
hList     = []
colours   = [ROOT.kOrange, ROOT.kBlack, ROOT.kGreen-3, ROOT.kBlue, ROOT.kRed, ROOT.kTeal]
DOF       = [1, 2, 4, 6, 10] #100
startFrom = 0.0

######################################################################
def main():

    counter = 0
    for nu, colour in zip(DOF, colours):
        # Define my chiSquare function
        chiSquare = ROOT.TF1("pdf_%i" % (nu), "ROOT::Math::chisquared_pdf(x, [0], [1])", 0, 20)
        chiSquare.SetParameters(nu, startFrom)
        CustomiseTH1(chiSquare, colour, False)
        chiSquare.GetXaxis().SetTitle("#chi_{#nu}^{2}")
        chiSquare.GetYaxis().SetTitle("p_{#nu}^{2}(S)") # S = chi^{2}/nu

        # Append histograms to drawing list
        hList.append(chiSquare)

        counter+= 1

    # Draw the histograms
    DrawHistoList(hList, 1)

    return

######################################################################
def DrawHistoList(hList, fNormalisationFactor=None):
    
    # Take care of legend
    myLeg = CreateLegend(0.75, 0.7, 0.9, 0.9, "" )
    
    counter = 0
    yMax = 0.0

    # Create Canvas
    #cName = "c%i_" % (counter) + hList[0].GetName()
    cName = "c_" + hList[0].GetName()
    c = ROOT.TCanvas(cName, cName, 1)

    # Draw histograms
    for h in hList:
        myLeg.AddEntry(h, "DOF = %i" % (DOF[counter]), "l")
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
        #h.GetYaxis().SetRangeUser(0.0, yMax*1.2)
        h.GetYaxis().SetRangeUser(0.0, 0.5)

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

    histo.SetTitle("")
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
