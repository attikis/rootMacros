#!/usr/bin/env python

import ROOT

ROOT.gROOT.SetStyle("Plain")

def main():

    xMin  =   0.0
    xMax  = 800.0
    const =   1.0
    mean  = 173.21
    
    # Create functions
    f1 = CreateCrystalBall("f1", xMin, xMax, const, mean, sigma=10, n=100, alpha=-0.1, colour=ROOT.kRed)
    f2 = CreateCrystalBall("f2", xMin, xMax, const, mean, sigma=20, n=100, alpha=-0.1, colour=ROOT.kGreen)
    f3 = CreateCrystalBall("f3", xMin, xMax, const, mean, sigma=30, n=100, alpha=-0.2, colour=ROOT.kBlue)

    f4 = CreateCrystalBallMath("f4", xMin, xMax, mean, sigma=1 , n=1, alpha=10, colour=ROOT.kRed-3)
    f5 = CreateCrystalBallMath("f5", xMin, xMax, mean, sigma=10, n=3, alpha=1 , colour=ROOT.kGreen-3)
    f6 = CreateCrystalBallMath("f6", xMin, xMax, mean, sigma=50, n=1, alpha=1 , colour=ROOT.kBlue-3)

    # Append histos to a list
    fList1 = []
    fList1.append(f1)
    fList1.append(f2)
    fList1.append(f3)

    fList2 = []    
    fList2.append(f4)
    fList2.append(f5)
    fList2.append(f6)
    
    # Draw all histograms in hList
    DrawList("crystalball", mean, fList1)
    #DrawList("crystalball_function", fList2)

    return

######################################################################
def CreateCrystalBall(name="name", xMin=-10.0, xMax=4.0, constant=1, mean=0, sigma=1, n=1, alpha=1, colour=ROOT.kRed):
    '''
    Parameters of "crystalball" where "x" is the invariant mass:
    par0 = Constant
    par1 = Mean is the mean value
    par2 = Sigma is the mass resolution
    par3 = Alpha is the Gaussian tail
    par4 = N is the normalization
    '''
    f1 = ROOT.TF1(name, "crystalball", xMin, xMax)
    if 0:
        for i in range(0, 5):
            print f1.GetParName(i)

    f1.SetParameters(constant, mean, sigma, alpha, n)
    f1.SetLineColor(colour)
    f1.SetMaximum(1.0)
    CustomiseTF1(f1, colour)
    return f1

def CreateCrystalBallMath(name="name", xMin=-10.0, xMax=4.0, mean=0, sigma=1, n=1, alpha=1, colour=ROOT.kRed):
    '''
    Crystal Ball (variable x is the  invariant mass)
    mean  = "m" mass mean value 
    sigma = "s" mass resolution 
    alpha = "a" Gaussian tail
    n     = "n" normalization
    '''
    f1 = ROOT.TF1(name, "ROOT::Math::crystalball_function(x, %s, %s, %s, %s)" % (alpha, n, sigma, mean), xMin, xMax)
    f1.SetLineColor(colour)
    f1.SetMaximum(1.0)
    CustomiseTF1(f1, colour)
    return f1

######################################################################
def DrawList(cName, mean, fList):

    canvas = ROOT.TCanvas(cName, cName, 1)
    legend = ROOT.TLegend(0.40, 0.75, 0.90, 0.90);

    for i, f in enumerate(fList):
        if i ==0:
            f.Draw()
        else:
            f.Draw("same")
        legend.AddEntry(f, GetTF1Label(f), "L")
        f.SetTitle("")
        f.GetXaxis().SetTitle("x")
        f.GetYaxis().SetTitle("f(x)")
        
    legend.Draw()

    l = ROOT.TLine(mean, 0, mean, 1)
    l.SetLineStyle(ROOT.kDashed)
    l.SetLineWidth(3)
    l.Draw("same")

    canvas.SaveAs(cName + ".png")        
    return

######################################################################
def GetTF1Label(f):

    paramDict = {}
    paramDict[0] = "C"
    paramDict[1] = "#mu"
    paramDict[2] = "#sigma"
    paramDict[3] = "#alpha"
    paramDict[4] = "N"
    
    #label = f.GetName()
    label = ""
    for i, p in enumerate(f.GetParameters()):
        if i > 4:
            break
        #print f.GetParName(0)
        if i==0:
            label += "%s: %0.1f" % (paramDict[i], p)
        else:
            label += ", %s: %0.1f" % (paramDict[i], p)
    return label

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



