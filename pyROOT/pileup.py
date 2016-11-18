#!/usr/bin/env python

import ROOT

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat("")
#ROOT.gStyle.SetOptStat("mrn")

### Binomial Distribution Parameters for Limit Binomial -> Poisson
nTrials       = 100000
mu_Poisson    = 20.0
x1_Flat       =  0.0
x2_Flat       = 10.0


### Global definitions
hList     = []
xMin      =  +0.0
xMax      = +50.0
yMin      =  +0.0
yMax      =  +0.07
binWidthX =  +1.0
xPosList  = [xMax*0.3, xMax*0.3, xMax*0.3]
yPosList  = [0.06, 0.05, 0.04] #4000.0*scaleFactor, 3000.0*scaleFactor, 2000.0*scaleFactor]
colList   = [ROOT.kBlack, ROOT.kOrange+8, ROOT.kBlue]

    
def main():                    

    ### Create Histograms
    hPoisson   = CreateTH1F("Poisson", "Poisson", binWidthX, xMin, xMax)
    hFlat      = CreateTH1F("Flat"   , "Flat"   , binWidthX, xMin, xMax)
    hStack     = ROOT.THStack("pile-up", "pile-up")
    
    ### Loop to fill the histograms using the random number generator "gRandom" 
    for i in range (0, nTrials):
    
        hFlat.Fill(ROOT.gRandom.Uniform(x1_Flat, x2_Flat))
        hPoisson.Fill(ROOT.gRandom.Poisson(mu_Poisson))


    ### Normalise Histograms
    hFlat.Scale(1.0/2*nTrials)
    hPoisson.Scale(1.0/2*nTrials)

    
    ### Customise histos
    CustomiseTH1(hPoisson, colList[1], True)
    CustomiseTH1(hFlat   , colList[2], True)

    
    ### Add two distributions to get the combined one
    hStack.Add(hPoisson)
    hStack.Add(hFlat)

    ### Draw all histograms in hList
    c = ROOT.TCanvas(hStack.GetName(), hStack.GetName(), 1)
    hStack.Draw("AP,STACK,E1")
    #hStack.Draw("HIST9, STACK")
    #hStack.Draw("HIST9, STACK")
    c.SaveAs(hStack.GetName() + ".png")
   
    return


######################################################################
def DrawText(textList, xPosList, yPosList, colList):

    for txt, xVal, yVal, colour in zip(textList, xPosList, yPosList, colList):
        myText = ROOT.TLatex()
        myText.SetTextSize(myText.GetTextSize()*0.6)
        myText.SetTextColor( colour )
        myText.SetTextSize( 0.04 )
        #print "x= %s, y= %s" % (xVal, yVal)
        myText.DrawLatex(xVal, yVal, "#font[42]{"+ str(txt) + "}")

    return

######################################################################
def CustomiseTH1(histo, myColour, lineWidth=2):
    
    histo.SetFillStyle(3001)
    histo.SetLineColor(myColour)
    histo.SetLineWidth(lineWidth)
    histo.SetFillColor(myColour)

    return

######################################################################
def CreateTH1F(hName, hTitle, binWidthX, xMin, xMax):
    
    nBinsX = int((xMax-xMin)/binWidthX)
    h = ROOT.TH1F(hName, hTitle, nBinsX, xMin, xMax)
    
    return h

######################################################################
if __name__ == "__main__":

    main()

    #raw_input("\n*** DONE! Press \"ENTER\" key exit session: ")
