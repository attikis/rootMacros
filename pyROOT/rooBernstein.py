#!/usr/bin/env python

import ROOT

ROOT.gROOT.SetStyle("Plain")

def main():

    # Declare variables x,mean,sigma with associated name, title, initial value and allowed range
    x     = ROOT.RooRealVar("x","x", -10, 10)
    mean  = ROOT.RooRealVar("mean","mean of gaussian"   , 1, -10.0, 10.0)
    sigma = ROOT.RooRealVar("sigma","width of gaussian", 1,   0.1, 10.0)

    # Build gaussian p.d.f in terms of x,mean and sigma
    gauss = ROOT.RooGaussian("gauss","gaussian PDF", x, mean, sigma)

   
    # f1 = CreateCrystalBall("f1", xMin= -10.0, xMax = 4.0, constant = 1, mean=0, sigma=1, n=1, alpha=10, colour=ROOT.kRed)
    # f2 = CreateCrystalBall("f2", xMin= -10.0, xMax = 4.0, constant = 1, mean=0, sigma=1, n=3, alpha=1 , colour=ROOT.kGreen)
    # f3 = CreateCrystalBall("f3", xMin= -10.0, xMax = 4.0, constant = 1, mean=0, sigma=1, n=1, alpha=1 , colour=ROOT.kBlue)
    # 
    # f4 = CreateCrystalBallMath("f4", xMin= -10.0, xMax = 4.0, mean=0, sigma=1, n=1, alpha=10, colour=ROOT.kRed-3)
    # f5 = CreateCrystalBallMath("f5", xMin= -10.0, xMax = 4.0, mean=0, sigma=1, n=3, alpha=1 , colour=ROOT.kGreen-3)
    # f6 = CreateCrystalBallMath("f6", xMin= -10.0, xMax = 4.0, mean=0, sigma=1, n=1, alpha=1 , colour=ROOT.kBlue-3)
    # 
    # # Append histos to a list
    # fList1 = []
    # fList1.append(f1)
    # fList1.append(f2)
    # fList1.append(f3)
    # 
    # fList2 = []    
    # fList2.append(f4)
    # fList2.append(f5)
    # fList2.append(f6)
    # 
    # # Draw all histograms in hList
    # DrawList("crystalball", fList1)
    # DrawList("crystalball_function", fList2)

    return

######################################################################
def CreateCrystalBall(name="name", xMin=-10.0, xMax=4.0, constant=1, mean=0, sigma=1, n=1, alpha=1, colour=ROOT.kRed):
    '''
    Crystal Ball
    "x" invariant mass 
    "m" mass mean value 
    "s" mass resolution 
    "a" Gaussian tail
    "n" normalization

    From fit-panel: Set Parameters of "crystalball"
    par0 = Constant
    par1 = Mean
    par2 = Sigma
    par3 = Alpha
    par4 = N
    '''
    f1 = ROOT.TF1(name, "crystalball", xMin, xMax)
    f1.SetParameters(constant, mean, sigma, alpha, n)
    f1.SetLineColor(colour)
    CustomiseTF1(f1, colour)
    return f1

def CreateCrystalBallMath(name="name", xMin=-10.0, xMax=4.0, mean=0, sigma=1, n=1, alpha=1, colour=ROOT.kRed):

    f1 = ROOT.TF1(name, "ROOT::Math::crystalball_function(x, %s, %s, %s, %s)" % (alpha, n, sigma, mean), xMin, xMax)
    f1.SetLineColor(colour)
    CustomiseTF1(f1, colour)
    return f1


def DrawList(cName, fList):

    canvas = ROOT.TCanvas(cName, cName, 1)
    legend = ROOT.TLegend(0.75, 0.75, 0.90, 0.90);

    for i, f in enumerate(fList):
        if i ==0:
            f.Draw()
        else:
            f.Draw("same")
        legend.AddEntry(f, f.GetName(), "L")

    legend.Draw()
    canvas.SaveAs(cName + ".png")
        
    return
######################################################################
def CustomiseTF1(f, myColour, fill=True):
    
    if fill==True:
        f.SetFillColor(myColour)
        
    #f.SetFillStyle(3001)
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



