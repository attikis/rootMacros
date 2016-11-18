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
    a = "1/sqrt(%s)" % (str(twoPi))
    x = "(x)"
    expr = "%s*exp(-0.5*%s^2)" % (a, x)
    f1 = ROOT.TF1("f1", expr, 0.01 , 10.0 )
    hList.append(f1)

    a = "1/sqrt(%s)" % (str(twoPi))    
    y = "(log(x))"
    expr = a + "*exp(-0.5*%s^2)" % (y)
    f2 = ROOT.TF1("f2", expr, 0.01 , 10.0 )
    hList.append(f2)

    a = "1/x*sqrt(%s)" % (str(twoPi))
    z = "(log(x))"
    expr = a + "*exp(-0.5*%s^2)" % (z)
    f3 = ROOT.TF1("f3", expr, 0.01 , 10.0 )
    hList.append(f3)

    i = 0
    for f in hList:
        # Customise Functions
        if i in [1, 2]:
            #print i
            CustomiseTF1(f, myColours[i], fillHisto=False)
        else:
            CustomiseTF1(f, myColours[i], fillHisto=True)
        i += 1

    # Draw Functions
    DrawHistoList(hList)

    return

######################################################################
def DrawHistoList(hList):
    
    # Take care of legend
    myLeg = ROOT.TLegend(0.6, 0.65, 0.9, 0.90, "" )
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
    c.SetLogx(True)
    #c.SetLogy(True)

    # Draw histograms
    for h in hList:
        formula = str(h.GetExpFormula()).replace("(1/sqrt(6.28318530718))", "#frac{1}{#sqrt{2#pi}}")
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
        h.GetYaxis().SetRangeUser(0.0, yMax*1.5)
        
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



