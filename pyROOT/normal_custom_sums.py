#!/usr/bin/env python

import ROOT
import sys

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
hList      = []
twoPi      = 2*ROOT.TMath.Pi()
myColours  = [ROOT.kBlue, ROOT.kTeal, ROOT.kOrange, ROOT.kPink]
variance   = [1, 2, 1+2]
mean       = [0, 1, 0+1]
normFactor = [ "1/sqrt(%s*%s)" % (str(twoPi), str(variance[0])),  "1/sqrt(%s*%s)" % (str(twoPi), str(variance[0])),  "1/sqrt(%s*%s)" % (str(twoPi), str(variance[0]))]
######################################################################
def main():


    # Create Functions
    variance[0]     = 1
    mean[0]    = 0
    a1       = "1/sqrt(%s*%s)" % (str(twoPi), str(variance[0]))
    exponent = "-(x-%s)^2/(2*%s)" % (str(mean[0]), str(variance[0]))
    expr1    = "%s*exp(%s)" % (a1, exponent)
    f1       = ROOT.TF1("f1", expr1, -6.0 , 6.0 )
    hList.append(f1)

    #
    variance[1]     = 2
    mean[1]    = 1
    a2       = "1/sqrt(%s*%s)" % (str(twoPi), str(variance[1]))
    exponent = "-(x-%s)^2/(2*%s)" % (str(mean[1]), str(variance[1]))
    expr2    = "%s*exp(%s)" % (a2, exponent)
    f2       = ROOT.TF1("f2", expr2, -6.0 , 6.0 )
    hList.append(f2)

    #
    var3     = variance[0] + variance[1]
    mean3    = mean[0] + mean[1]
    a3       = "1/sqrt(%s*%s)" % (str(twoPi), str(var3))
    exponent = "-(x-%s)^2/(2*%s)" % (str(mean3), str(var3))
    expr3    = "%s*exp(%s)" % (a3, exponent)
    f3       = ROOT.TF1("f3", expr3, -6.0 , 6.0)
    hList.append(f3)

    # This will NOT work, as x and y should be independent but ROOT probably treats them as x=y i.e. one single variable.
    #f4    = ROOT.TF1("f4", "f1*f2", -6.0 , 6.0) 
    #hList.append(f4)

    # Customise Functions
    i = 0
    for f in hList:
        if i in [1, 2, 3]:
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
    myLeg = ROOT.TLegend(0.7, 0.7, 0.9, 0.90, "" )
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
        #formula = str(h.GetExpFormula())
        #myLeg.AddEntry(h, "%s" % (formula) )
        if counter is not 3:
            myLeg.AddEntry(h, "#mu = %s , #sigma = %s" % (str(mean[counter]), str(variance[counter])), "l")
        else:
            myLeg.AddEntry(h, "#mu = ? , #sigma = ?", "l")

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



