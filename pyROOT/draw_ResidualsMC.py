#!/usr/bin/env python

import ROOT

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat("")
#ROOT.gStyle.SetOptStat("mrn")

### Binomial Distribution Parameters for Limit Binomial -> Poisson
scaleFactor   = 5
nTrials       = 100000*scaleFactor
w_4hits       = 0.10
w_3hits       = 1-w_4hits
nTrials_3hits = int(nTrials*w_3hits)
nTrials_4hits = int(nTrials*w_4hits)
mu_4hits      = 0.0
mu_3hits      = 0.0
sigma_3hits   = 2.0
sigma_4hits   = sigma_3hits*0.5


### Global definitions
hList     = []
xMin      = -6.0
xMax      = +6.0
yMin      = +0.0
yMax      = +0.07
binWidthX =   0.2
textList  = ["#mu = #mu_{c}, #sigma = #sigma_{c}",
             "#mu = %s, #sigma = %s (w = %s)" % (mu_4hits, sigma_4hits, w_4hits), "#mu = %s, #sigma = %s (w = %s)" % (mu_3hits, sigma_3hits, w_3hits)]
xPosList  = [xMax*0.3, xMax*0.3, xMax*0.3]
yPosList  = [0.06, 0.05, 0.04] #4000.0*scaleFactor, 3000.0*scaleFactor, 2000.0*scaleFactor]
colList   = [ROOT.kBlack, ROOT.kOrange+8, ROOT.kBlue]

    
def main():                    

    ### Create Histograms. Number of bins = 200, Max = 100, Min = -100.
    hGaussian_AllHits = CreateTH1F("Residual_MC"   , ""              , binWidthX, xMin, xMax, mu_3hits) 
    hGaussian_3hits   = CreateTH1F("Gaussian_3hits", "Residual_3hits", binWidthX, xMin, xMax, mu_3hits)
    hGaussian_4hits   = CreateTH1F("Gaussian_4hits", "Residual_4hits", binWidthX, xMin, xMax, mu_4hits)
    hGaussian_Sum     = CreateTH1F("Gaussian_Sum"  , "Residual_Sum"  , binWidthX, xMin, xMax, mu_3hits) # Sum of 2 ind. random variables: mu = m1+m2, var = var1+var2
    
    ### Loop to fill the histograms using the random number generator "gRandom" 
    for i in range (0, nTrials_4hits):
    
        hGaussian_4hits.Fill(ROOT.gRandom.Gaus(mu_4hits, sigma_4hits))
        hGaussian_Sum.Fill( ROOT.gRandom.Gaus(mu_4hits, sigma_4hits) + ROOT.gRandom.Gaus(mu_3hits, sigma_3hits) )
        

    ### Loop to fill the histograms using the random number generator "gRandom" 
    for i in range (0, nTrials_3hits):
    
        hGaussian_3hits.Fill(ROOT.gRandom.Gaus(mu_3hits, sigma_3hits))
        hGaussian_Sum.Fill( ROOT.gRandom.Gaus(mu_4hits, sigma_4hits) + ROOT.gRandom.Gaus(mu_3hits, sigma_3hits) )
        

    ### Add two distributions to get the combined one
    hGaussian_AllHits.Add( hGaussian_3hits )
    hGaussian_AllHits.Add( hGaussian_4hits )
    

    ### Customise histos
    CustomiseTH1(hGaussian_AllHits, colList[0], False, 1)
    CustomiseTH1(hGaussian_3hits  , colList[2], True)
    CustomiseTH1(hGaussian_4hits  , colList[1], True)
    #CustomiseTH1(hGaussian_Sum, ROOT.kOrange)


    ### Append histos to a list
    hList.append(hGaussian_AllHits)
    hList.append(hGaussian_3hits)
    hList.append(hGaussian_4hits)
    #hList.append(hGaussian_Sum)

    
    ### Draw all histograms in hList
    DrawHistoList(hList, "_w" + str(w_4hits).replace(".", "p") )
   
    return

######################################################################
def DrawHistoListNormalised(hList, ext=""):
    
    for h in hList:
        cName = "c%i_" %(counter) + h.GetName()
        c = ROOT.TCanvas(cName, cName, 1)
        h.DrawNormalized("HIST9")
        c.SaveAs(cName+ext+".png")
        c.SaveAs(cName+ext+".pdf")
        
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
def DrawHistoList(hList, saveExt):

    counter = 0
    cName = hList[0].GetName()
    c = ROOT.TCanvas(cName, cName, 1)

    for h in hList:
        if (counter == 0):
            opts = "HIST9"
        else:
            opts = "HIST9same"
        h.Scale(1.0/nTrials)
        h.SetMaximum(yMax)        
        h.Draw(opts)
        counter = counter + 1        

    ### Fit Gaussian
    fitOpts     = "Q S 0"
    fitFunc     = ROOT.TF1("fitted_gaus", "gaus", xMin, xMax)
    graphicOpts = ""
    h = hList[0]
    r = h.Fit(fitFunc, fitOpts, graphicOpts, xMin, xMax)
    f = fitFunc.Clone("fitFunc_clone")
    f.SetLineWidth(4)
    f.SetLineStyle(ROOT.kDashed)
    f.SetRange(h.GetXaxis().GetXmin(), h.GetXaxis().GetXmax())
    #f.SetMaximum(yMax)
    f.Draw("same")

    ### Get the fit function parameters
    const = f.GetParameter(0)
    mean  = f.GetParameter(1)
    sigma = f.GetParameter(2)
    

    ### Update mu and sigma for combined histo
    mu = "#mu = %0.1f" % (mean)    
    textList[0] = str(mu).replace("-","") + ", #sigma = %0.2f" % (sigma)

    ### Draw text
    DrawText(textList, xPosList, yPosList, colList)
           
    ### Save canvas
    c.SaveAs(cName+saveExt+".png")
    c.SaveAs(cName+saveExt+".pdf")
        
    return

######################################################################
def CustomiseTH1(histo, myColour, fillHisto=True, lineWidth=2):
    
    histo.SetFillStyle(3001)
    histo.SetLineColor(myColour)
    histo.SetLineWidth(lineWidth)

    if fillHisto==True:
        histo.SetFillColor(myColour)

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



