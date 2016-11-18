#!/usr/bin/env python

import ROOT
import sys

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(000000000) #(000001111) is default
ROOT.gSystem.Load("libMathCore");

### Global definitions
hList     = []
colours   = [ROOT.kWhite, ROOT.kBlack, ROOT.kOrange+8]
DOF       = [6, 6, 6]
alpha     = 20-8
xMin      = [ 0.0, 0.0  , 0.95*alpha]
xMax      = [20.0, 20.0, 20.0]
yMax      = 0.2
#textList  = ["", "#alpha", "1-#alpha = P(#chi^{2} #geq #chi^{2}_{#nu, 1-#alpha})"]
textList  = ["", "1-#alpha", "#alpha = P(#chi^{2} #geq #chi^{2}_{#nu, #alpha})"]
xPosList  = [0.0, xMax[0]/6, alpha*1.1]
yPosList  = [0.0, yMax/10, yMax/10]


######################################################################
def main():

    counter = 0
    for nu, colour in zip(DOF, colours):

        ### Define my chiSquare function
        chiSquare = ROOT.TF1("ChiSqUpperQuantile", "ROOT::Math::chisquared_pdf(x, [0], [1])", xMin[counter], xMax[counter])

        ### Set Parameters
        startFrom = 0.0
        chiSquare.SetParameters(nu, startFrom)

        ### Customise Histograms
        if counter==len(colours)-1:
            CustomiseTH1(chiSquare, colour, True, 0)
        else:
            CustomiseTH1(chiSquare, colour, False)
        
        ### y-axis
        chiSquare.GetYaxis().SetTitle("P #left(#chi^{2}#right)")
        chiSquare.GetYaxis().SetTitleOffset(0.60)
        chiSquare.GetYaxis().SetTitleSize(0.06)
        ### Set bin labels for y
        chiSquare.GetYaxis().SetLabelSize(0);
        chiSquare.GetYaxis().SetTickSize(0);
        
        ### x-axis
        chiSquare.GetXaxis().SetTitle("#chi^{2}")
        chiSquare.GetXaxis().SetTitleSize(0.07)
        chiSquare.GetXaxis().SetTitleOffset(0.5)
        ### Set bin labels at x=alpha (horizontal mode)
        chiSquare.GetXaxis().SetBinLabel(alpha*5, "#chi^{2}_{#nu, #alpha}")
        chiSquare.GetXaxis().LabelsOption("h")
        chiSquare.GetXaxis().SetLabelSize(0.08)
        
        ### Append histograms to drawing list
        hList.append(chiSquare)

        ### Increment counter
        counter+= 1

    ### Draw the histograms
    DrawHistoList(hList, 1)
    
    return

######################################################################
def DrawHistoList(hList, fNormalisationFactor=None):
    
    ### Take care of legend
    myLeg = CreateLegend(0.75, 0.7, 0.9, 0.9, "" )
    
    counter = 0
    yMax = 0.0

    ### Create Canvas
    cName = hList[0].GetName()
    c = ROOT.TCanvas(cName, cName, 1)

    # Draw histograms
    for h in hList:
        #if counter == len(hList)-1:
        #    myLeg.AddEntry(h, "#nu = %i" % (DOF[counter]), "l")
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

        ### Set max value of y-axis
        h.GetYaxis().SetRangeUser(0.0, yMax*1.2)
        
        ### Increment Counter
        counter += 1


    ### Draw Legend
    myLeg.Draw()
    DrawText(hList, textList, xPosList, yPosList)

    ### Save Canvas
    hList[1].Draw("same")
    c.SaveAs(cName + ".png")
    c.SaveAs(cName + ".pdf")
        
    return

######################################################################
def DrawText(fList, tList, xList, yList):

    f = fList[0]
    for txt, xVal, yVal, colour in zip(tList, xList, yList, colours):
        myText = ROOT.TLatex()
        x = xVal
        y = yVal
        #print "x = %0.1f, y = %0.2f" % (x, y)

        ### Customise font
        myText.SetTextSize(myText.GetTextSize()*0.6)
        myText.SetTextColor( colour )
        myText.SetTextSize( 0.05 )
        myText.DrawLatex(x, y, "#font[42]{"+ str(txt) + "}")

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
def CustomiseTH1(histo, myColour, fillHisto=True, lineWidth=2):

    histo.SetTitle("")
    if fillHisto==True:
        histo.SetFillColor(myColour)
        histo.SetFillStyle(3002)

    histo.SetLineColor(myColour)
    histo.SetLineWidth(lineWidth)

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
