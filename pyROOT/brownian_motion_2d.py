#!/usr/bin/env python
import ROOT
import numpy

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
gList  = []
Mean   = 0
Var    = 1
cList  = [ROOT.kBlue, ROOT.kOrange, ROOT.kRed, ROOT.kBlack, ROOT.kTeal]
nSteps = 500
xVals  = numpy.ndarray( [nSteps] )
yVals  = numpy.ndarray( [nSteps] )

######################################################################
def main():

    # Create random number with new seed each time
    t1 = ROOT.TRandom(65534)
    t2 = ROOT.TRandom(00002)

    # Loop over the pre-defined number of steps
    for i in range(0, nSteps):
        x = t1.Gaus(Mean, Var)
        y = t2.Gaus(Mean, Var)
        # Fill the arrays for 2D-Brownian motion
        if i>0:
            xVals[i] = x + xVals[i-1]
            yVals[i] = y + yVals[i-1]
        else:
            xVals[i] = x
            yVals[i] = y

    # Create TGraph
    g = ROOT.TGraph(nSteps, xVals, yVals)
    gList.append(g)
    CustomiseTGraph(g, ROOT.kBlue, "", "#Deltat", "W(t)", False)
        
    # Draw TGraph
    DrawGrapgList(gList)

    return

######################################################################
def DrawGrapgList(gList):
    
    # Take care of legend
    myLeg = ROOT.TLegend(0.70, 0.7, 0.9, 0.9, "" )
    myLeg.SetFillStyle(0)
    myLeg.SetLineWidth(0)
    myLeg.SetBorderSize(0)
    myLeg.SetShadowColor(ROOT.kWhite)
    myLeg.SetTextSize(0.03)
    myLeg.SetTextFont(62)
    
    counter = 0
    yMax = 0.0

    # Create Canvas
    cName = gList[0].GetName()
    c = ROOT.TCanvas(cName, cName, 1)

    # Draw graph
    for h in gList:
        h.Draw("APL")
        
        if h.GetMaximum() >= yMax:
            yMax = h.GetMaximum()

    myLeg.Draw()
    c.SaveAs(cName+".png")
        
    return
######################################################################
def CustomiseTGraph(graph, myColour, gTitle, xTitle, yTitle, fillGraph=True):
    
    graph.SetTitle(gTitle)
    graph.GetXaxis().SetTitle(xTitle)
    graph.GetYaxis().SetTitle(yTitle)

    if fillGraph==True:
        graph.SetFillColor(myColour)

    graph.SetFillStyle(3001)
    graph.SetLineColor(myColour)
    graph.SetMarkerColor(myColour)
    graph.SetMarkerStyle(ROOT.kFullCircle)
    graph.SetMarkerSize(0.2)
    graph.SetLineWidth(2)

    return

######################################################################
if __name__ == "__main__":

    main()

    #raw_input("\n*** DONE! Press \"ENTER\" key exit session: ")



