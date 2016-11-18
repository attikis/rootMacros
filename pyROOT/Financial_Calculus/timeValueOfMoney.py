#!/usr/bin/env python

import ROOT
import sys

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
hList      = []
twoPi      = 2*ROOT.TMath.Pi()
myColours  = [ROOT.kBlue, ROOT.kTeal, ROOT.kOrange, ROOT.kBlack, ROOT.kMagenta, ROOT.kPink]
vLinesXval = [0]

######################################################################
def main():

    # Create Functions
    r = "0.05"
    #expr = "0.5*exp(+%s*x)" % (r)
    s1 = "1.0"   #price at t = 0
    s2 = "0.5" #price at t = dt (down step)
    s3 = "2.0"   #price at t = dt (up step)
    expr = "(%s*exp(+%s*x) - %s)/(%s-%s)" % (s1, r, s2, s3, s2)

    f1 = ROOT.TF1("Exponential_1", expr, -10.0 , 10.0 )
    f1.SetTitle("")
    f1.GetXaxis().SetTitle("time (t)")
    #f1.GetYaxis().SetTitle("Bond Price")
    f1.GetYaxis().SetTitle("Price of 1/2 Bond Unit")
    hList.append(f1)

    # Create Functions
    #expr = "0.5*exp(+%s*x)" % (r)
    #f2 = ROOT.TF1("Exponential_2", expr, 0.0 , 20.0 )
    #hList.append(f2)

    i = 0
    for f in hList:
        # Customise Functions
        if i==0:
            CustomiseTF1(f, myColours[i], fillHisto=True)
        else:
            CustomiseTF1(f, myColours[i], fillHisto=False)
        i += 1

    # Draw Functions
    DrawHistoList(hList, vLinesXval)

    return

######################################################################
def DrawVLines(f, vLineXval, yMin):
    vLines = []
    for x in vLineXval:
        yMax = f.Eval(x)
        #print "xMin = %i, xMax = %i, yMin = %0.2f, yMax=%0.5f" % (x, x, yMin, yMax)
        line = ROOT.TLine(x, yMin, x, yMax)
        line.SetLineWidth(3)
        line.SetLineStyle(ROOT.kDashDotted)
        line.SetLineColor(ROOT.kBlack)
        vLines.append(line)

    return vLines

######################################################################
def DrawHistoList(hList, vLinesXval):
    
    # Take care of legend
    myLeg = ROOT.TLegend(0.2, 0.65, 0.9, 0.90, "Now at t=0:" )
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
        myLeg.AddEntry(h, "%s" % (formula), "l" )
        
        if counter==0:
            h.Draw("H9")
        else:
            h.Draw("H9" + "SAME")

        if h.GetMaximum() >= yMax:
            yMax = h.GetMaximum()        
        counter += 1


    for f in hList:    
        f.GetYaxis().SetRangeUser(0.0, yMax*1.2)
    
    vLines = DrawVLines(f, vLinesXval, 0.0)
    for l in vLines:
        l.Draw("SAME")

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



