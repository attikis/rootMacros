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
nSteps = 5000
x1Vals  = numpy.ndarray( [nSteps] )
y1Vals  = numpy.ndarray( [nSteps] )
x2Vals  = numpy.ndarray( [nSteps] )
y2Vals  = numpy.ndarray( [nSteps] )

######################################################################
def main():

    # Create random number with new seed each time
    t1 = ROOT.TRandom(65534)
    t2 = ROOT.TRandom(21234)

    # Loop over the pre-defined number of steps
    for i in range(0, nSteps):
        x = i
        y1 = t1.Gaus(Mean, Var)
        y2 = t2.Gaus(Mean, Var)
        # Fill the arrays
        x1Vals[i] = x
        x2Vals[i] = x
        if i>0:
            y1Vals[i] = y1 + y1Vals[i-1]
            y2Vals[i] = y2 + y2Vals[i-1]
        else:
            y1Vals[i] = y1
            y2Vals[i] = y2

    # Create TGraph
    g1 = ROOT.TGraph(nSteps, x1Vals, y1Vals)
    g2 = ROOT.TGraph(nSteps, x2Vals, y2Vals)
    CustomiseTGraph(g1, ROOT.kRed, "1", "#Deltat", "W(t)", False)
    CustomiseTGraph(g2, ROOT.kBlue, "2", "#Deltat", "W(t)", False)
    gList.append(g1)
    gList.append(g2)
        
    # Draw TGraph
    DrawGraphList(gList)

    return

######################################################################
def DrawHLines(yVal, xMin, xMax):
    hLine = ROOT.TLine(xMin, yVal, xMax, yVal)
    hLine.SetLineWidth(3)
    hLine.SetLineStyle(ROOT.kDashDotted)
    hLine.SetLineColor(ROOT.kBlack)
    return hLine


######################################################################
def DrawGraphList(gList):
    
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
    cName = "c%i_" % (counter) + gList[0].GetName()
    c = ROOT.TCanvas(cName, cName, 1)

    # Draw graph
    for h in gList:
        if counter == 0:
            h.Draw("APL")
        else:
            h.Draw("SAME")
        
        if h.GetMaximum() >= yMax:
            yMax = h.GetMaximum()
        counter+= 1

    hLine = DrawHLines(0.0, 0.0, float(nSteps))
    hLine.Draw("SAME")
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
    graph.SetMarkerSize(0.1)
    graph.SetLineWidth(2)

    return

######################################################################
if __name__ == "__main__":

    main()

    raw_input("\n*** DONE! Press \"ENTER\" key exit session: ")



