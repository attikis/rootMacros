#!/usr/bin/env python

import ROOT
import sys

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default

# Global definitions
fList       = []
stdDivs     = []
colours     = [ROOT.kOrange, ROOT.kYellow, ROOT.kGreen-3]
vLineXval   = []
coverage    = []
areaText    = []
mean        = 0.0
stdDiv      = 1.0
twoPi       = 2*ROOT.TMath.Pi()
xAverage    = []

######################################################################
def main():
    
    a = "1/sqrt(%s)" % (str(twoPi))
    x = "(x)"
    expr = "%s*exp(-0.5*%s^2)" % (a, x)

    # First Create the curve
    f = ROOT.TF1("Standard_Normal_PDF", expr, -4.5 , 4.5 )
    CustomiseTF1(f, ROOT.kBlack, False, 2)
    f.SetNpx(5000)
    f.SetTitle("")
    f.GetXaxis().SetTitle("z")
    f.GetYaxis().SetTitle("f(z)")
    fList.append(f)
    vLineXval.append(0.0)

    # The create the sigma bands
    for i in range(len(colours), 0, -1):
        
        # Get the Standard Deviation multiples
        xMin = -i*1
        xMax = +i*1
        vLineXval.append(xMin)
        vLineXval.append(xMax)

        # Create the function 
        f = ROOT.TF1("f_%0.f" % (i), expr, xMin, xMax)
        f.SetTitle("")        
        # Calculate/Store the required values twice
        stdDivs.append(xMax)

        Integral  = "%0.1f" % (f.Integral(xMin, xMax)*100)
        coverage.append(Integral)

        extraIntegral = "%0.1f" % (f.Integral(mean+(i-1), mean+xMax)*100)
        areaText.extend([extraIntegral]*2)
        xAverage.append(xMax-1+0.2)
        xAverage.append(xMin+0.2)

        # Customize the functions (standard deviation bands)
        CustomiseTF1(f, colours[-i], True)

        # Append to the drawing list
        fList.append(f)

    # Draw function and the sigma bands
    DrawList(fList, areaText, xAverage, 1)
    
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
def DrawList(fList, textList, textXValueList, fNormalisationFactor=None):
    
    # Take care of legend
    myLeg = CreateLegend(0.70, 0.7, 0.9, 0.9, "" )
        
    # Initialise values
    counter = 0
    yMax = 0.0

    # Create Canvas
    #cName = "c%i_" % (counter) + fList[0].GetName()
    cName = fList[0].GetName()
    
    # Replace x-axis bin labels
    fList[0].GetXaxis().SetBinLabel(fList[0].GetXaxis().FindBin( 0.0 ), "#mu")
    fList[0].GetXaxis().SetBinLabel(fList[0].GetXaxis().FindBin( 1.0 ), "+1 #sigma")
    fList[0].GetXaxis().SetBinLabel(fList[0].GetXaxis().FindBin( -1.0 ), "-1 #sigma")
    fList[0].GetXaxis().SetBinLabel(fList[0].GetXaxis().FindBin( 2.0 ), "+2 #sigma")
    fList[0].GetXaxis().SetBinLabel(fList[0].GetXaxis().FindBin( -2.0 ), "-2 #sigma")
    fList[0].GetXaxis().SetBinLabel(fList[0].GetXaxis().FindBin( 3.0 ), "+3 #sigma")
    fList[0].GetXaxis().SetBinLabel(fList[0].GetXaxis().FindBin( -3.0 ), "-3 #sigma")
    fList[0].GetXaxis().SetBinLabel(fList[0].GetXaxis().FindBin( 4.0 ), "+4 #sigma")
    fList[0].GetXaxis().SetBinLabel(fList[0].GetXaxis().FindBin( -4.0 ), "-4 #sigma")

    c = ROOT.TCanvas(cName, cName, 1)

    # Draw histograms
    for h in fList:
        if counter > 0:
            label1 = "#pm %0.1f #sigma (%s" % (stdDivs[counter-1], coverage[counter-1])
            label2 = "%)"
            myLeg.AddEntry(h, label1+label2, "f")

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

    yMax = yMax*1.01
    for h in fList:    
        h.GetYaxis().SetRangeUser(0.0, yMax)

    # Redraw the first histogram
    fList[0].Draw("H9" + "SAME")
    myLeg.Draw()

    # Draw vertical Lines at several x values
    vLines = DrawVLines(fList[0], vLineXval, 0.0)
    vLines[0].Draw("SAME")
    #for l in vLines:
    #    l.Draw("SAME")
        
    DrawText(fList, textList, textXValueList)
    
    txt = ROOT.TLatex()
    txt.DrawLatex(-4.0, 0.35, "#font[42]{Standard-Normal}")
    txt.DrawLatex(-4.0, 0.33, "#font[42]{#mu = 0}")
    txt.DrawLatex(-4.0, 0.31, "#font[42]{#sigma = 1}")

    # Save the canvas
    c.SaveAs(cName+".png")
    c.SaveAs(cName+".pdf")
    c.SaveAs(cName+".eps")
        
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
def DrawText(fList, tList, textXValueList):

    f = fList[0]
    for txt, xVal in zip(tList, textXValueList):
        myText = ROOT.TLatex()
        x = xVal
        #y = f.Eval(x)/4
        y = 0.001
        x = xVal*(1-0.01)
        #print "x = %0.1f, y = %0.2f" % (x, y)
        txt = txt + "%"
        myText.SetTextSize(myText.GetTextSize()*0.6)
        myText.DrawLatex(x, y, "#font[42]{"+ str(txt) + "}")

    return

######################################################################
def CustomiseTF1(f, myColour, fillHisto=True, lineWidth=0):
    
    if fillHisto==True:
        f.SetFillStyle(1001)
    else:
        f.SetFillStyle(0)

    f.SetFillColor(myColour)
    f.SetLineColor(ROOT.kBlack)
    f.SetLineWidth(lineWidth)

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



