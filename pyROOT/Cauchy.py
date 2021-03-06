#!/usr/bin/env python

import ROOT
import sys

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
hList      = []
twoPi      = 2*ROOT.TMath.Pi()
myColours  = [ROOT.kBlue, ROOT.kTeal, ROOT.kOrange, ROOT.kBlack, ROOT.kMagenta, ROOT.kPink]
######################################################################
def main():

    # Create Functions
    #a = "ROOT.TMath.Pi()" #"3.14159265359"
    a = "3.142"
    expr = "(1/%s)*1/(1+x^2)" % (a)
    print expr
    f1 = ROOT.TF1("Cauchy", expr, -5.0 , 5.0 )
    hList.append(f1)

    i = 0
    for f in hList:
        # Customise Functions
        if i==0:
            CustomiseTF1(f, myColours[i], fillHisto=True)
        else:
            CustomiseTF1(f, myColours[i], fillHisto=False)
        i += 1

    # Draw Functions
    DrawHistoList(hList)

    return

######################################################################
def DrawHistoList(hList):
    
    # Take care of legend
    myLeg = ROOT.TLegend(0.65, 0.75, 0.90, 0.90, "" )
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
        formula = str(h.GetExpFormula()).replace("3.142", "#pi")
        formula = formula.replace("*", " ")
        myLeg.AddEntry(h, "%s" % (formula) )
        
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
def CustomiseTF1(f, myColour, fillHisto=True):
    
    if fillHisto==True:
        f.SetFillStyle(3001)
    else:
        f.SetFillStyle(0)

    f.SetFillColor(myColour)
    f.SetLineColor(myColour)
    f.SetLineWidth(2)

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



