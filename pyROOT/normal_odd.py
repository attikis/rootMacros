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
    mean1 = "10"
    variance = "2"
    x = "(x)"
    expr = "%s*%s*exp(-0.5*((%s-%s)/(%s))^2)" % (a, x, x, mean1, variance)
    f1 = ROOT.TF1("f1", expr, -20.0 , 20.0 )
    hList.append(f1)

    mean2 = "10"
    expr2 = "%s*exp(-0.5*((%s-%s)/(%s))^2)" % (a, x, mean2, variance)
    f2 = ROOT.TF1("f2", expr2, -20.0 , 20.0 )
    hList.append(f2)

    mean3 = "0"
    expr3 = "%s*exp(-0.5*((%s-%s)/(%s))^2)" % (a, x, mean3, variance)
    f3 = ROOT.TF1("f3", expr3, -20.0 , 20.0 )
    hList.append(f3)

    mean4 = "0"
    expr4 = "%s*%s*exp(-0.5*((%s-%s)/(%s))^2)" % (a, x, x, mean4, variance)
    f4 = ROOT.TF1("f4", expr4, -20.0 , 20.0 )
    hList.append(f4)

    mean5 = "-10"
    expr5 = "%s*%s*exp(-0.5*((%s-%s)/(%s))^2)" % (a, x, x, mean5, variance)
    f5 = ROOT.TF1("f5", expr5, -20.0 , 20.0 )
    hList.append(f5)

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
    myLeg = ROOT.TLegend(0.2, 0.65, 0.9, 0.90, "" )
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
        formula = str(h.GetExpFormula()).replace("(1/sqrt(6.28318530718))", "#frac{1}{#sqrt{2#pi}}")
        formula = formula.replace("*", " ")
        myLeg.AddEntry(h, "%s" % (formula), "l" ) #"f"
        
        if counter==0:
            h.Draw("H9")
        else:
            h.Draw("H9" + "SAME")

        if h.GetMaximum() >= yMax:
            yMax = h.GetMaximum()        
        counter += 1

    for h in hList:    
        #h.GetYaxis().SetRangeUser(0.0, yMax*1.5)
        h.SetMaximum(yMax*1.5)
        h.SetMinimum(-yMax*1.2)

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



