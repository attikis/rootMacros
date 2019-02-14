#!/usr/bin/env python
'''
DESCRIPTION:


USAGE:
./draw_GoF.py [opts]


EXAMPLES:
./draw_GoF.py


LAST USED:
./draw_GoF.py 

'''

#================================================================================================ 
# Imports
#================================================================================================ 
import os
import sys
from optparse import OptionParser

import ROOT
ROOT.gROOT.SetBatch(True)
import tdrstyle as tdrstyle

#================================================================================================ 
# Definitions
#================================================================================================ 
chiSqObs  = 10
alpha     = 5e-2 #0.05 #20-8
hList     = []
colours   = [ROOT.kWhite, ROOT.kBlack, ROOT.kOrange+8]
xMin      = [ 0.0, 0.0, chiSqObs]
xMax      = [20.0, 20.0, 20.0]
yMax      = 0.2
textList  = ["", "1-#alpha", "#alpha = f(#chi^{2} #geq #chi^{2}_{data})"]
#textList  = ["", "1-#alpha", "#alpha=#int^{#infty}_{#chi^{2}_{obs}} f(#chi^{2}) d#chi^{2}"]
xPosList  = [0.0, xMax[0]/6, chiSqObs*1.0]
yPosList  = [0.0, yMax/10, yMax/10]


#================================================================================================ 
# Function definition
#================================================================================================ 
def DrawHistoList(hList, opts, fNormalisationFactor=None):
    
    # Take care of legend
    myLeg = CreateLegend(0.75, 0.7, 0.9, 0.9, "" )
    
    counter    = 0
    yMax       = 0.0
    yMaxFactor = 1.2
    
    # Create Canvas
    cName = hList[0].GetName()
    c = ROOT.TCanvas(cName, cName, 1)

    # Draw histograms
    for h in hList:

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

        # Set max value of y-axis
        h.GetYaxis().SetRangeUser(0.0, yMax*yMaxFactor)
        
        # Increment Counter
        counter += 1

    # Draw Legend
    if 0:
        myLeg.Draw()
    DrawText(hList, textList, xPosList, yPosList)

    # Draw the histogram
    hList[1].Draw("same")

    # Customise arrow indicating data-observed
    arr = ROOT.TArrow(chiSqObs, 0.0001, chiSqObs, hList[0].GetMaximum()/9, 0.02, "<|")
    arr.SetLineColor(ROOT.kBlue)
    arr.SetFillColor(ROOT.kBlue)
    arr.SetFillStyle(1001)
    arr.SetLineWidth(3)
    arr.SetLineStyle(1)
    arr.SetAngle(60)
    arr.Draw("<|same")

    # p-value
    pvalText = ROOT.TLatex()
    pvalText.SetNDC()
    pvalText.SetTextFont(43)
    pvalText.SetTextSize(22)
    pvalText.SetTextAlign(31)
    pvalText.DrawLatex(0.92, 0.84, "#alpha=#int^{#infty}_{#chi^{2}_{obs}} f(#chi^{2}) d#chi^{2}")

    # Add data observed value
    left = ROOT.TLatex()
    left.SetTextFont(43)
    left.SetTextSize(22)
    left.SetTextAlign(11)
    # left.DrawLatex(chiSqObs*0.92, (hList[0].GetMaximum()/8.0)*1.05, "#color[4]{obs}")

    # Save the canvas
    for i, ext in enumerate(opts.saveFormats, 1):
        saveName = cName + ext
        Print("Canvas saved as \"%s\"" % (saveName), i==1)
        c.SaveAs(saveName)
        
    return


def Print(msg, printHeader=False):
    fName = __file__.split("/")[-1]
    if printHeader==True:
        print "=== ", fName
        print "\t", msg
    else:
        print "\t", msg
    return


def Verbose(msg, printHeader=True, verbose=False):
    if not opts.verbose:
        return
    aux.Print(msg, printHeader)
    return


def DrawText(fList, tList, xList, yList):

    f = fList[0]
    for txt, xVal, yVal, colour in zip(tList, xList, yList, colours):
        myText = ROOT.TLatex()
        x = xVal
        y = yVal

        ### Customise font
        myText.SetTextSize(myText.GetTextSize()*0.6)
        myText.SetTextColor( colour )
        myText.SetTextSize( 0.05 )
        #myText.DrawLatex(x, y, "#font[42]{"+ str(txt) + "}")
        #myText.DrawLatex(x, y, "#font[42]{%s}" % (txt) )
        myText.DrawLatex(x, y, "%s" % (txt) )
    return


def CreateLegend(xMin, yMin, xMax, yMax, Header):

    myLeg = ROOT.TLegend(xMin, yMin, xMax, yMax, Header)
    myLeg.SetFillStyle(0)
    myLeg.SetLineWidth(0)
    myLeg.SetBorderSize(0)
    myLeg.SetShadowColor(ROOT.kWhite)
    myLeg.SetTextSize(0.03)
    myLeg.SetTextFont(62)
    return myLeg 


def CustomiseTH1(histo, myColour, fillHisto=True, lineWidth=2):

    histo.SetTitle("")
    if fillHisto==True:
        histo.SetFillColor(myColour)
        histo.SetFillStyle(3001) #3002)

    histo.SetLineColor(myColour)
    histo.SetLineWidth(lineWidth)
    return


def CreateTH1F(hName, hTitle, binWidthX, xMin, xMax, xMean):
    
    if xMin == None:
        xMin  =  xMean*(-5)
    if xMax == None:
        xMax  =  xMean*(+5)
    nBinsX = int((xMax-xMin)/binWidthX)

    h = ROOT.TH1F(hName, hTitle, nBinsX, xMin, xMax)
    return h


def main(opts):

    # Apply TDR style
    style = tdrstyle.TDRStyle()
    style.setGridX(opts.gridX)
    style.setGridY(opts.gridY)
    style.setOptStat(False)
    ROOT.gErrorIgnoreLevel = ROOT.kFatal #kPrint = 0,  kInfo = 1000, kWarning = 2000, kError = 3000, kBreak = 4000, kSysError = 5000, kFatal = 6000

    # For-loop: DOF
    for counter, colour in enumerate(colours, 0):

        # Define my chiSquare function
        chiSquare = ROOT.TF1("GoF", "ROOT::Math::chisquared_pdf(x, [0], [1])", xMin[counter], xMax[counter])

        # Set parameters
        startFrom = 0.0
        chiSquare.SetParameters(opts.dof, startFrom)

        # Customise histograms
        if counter==len(colours)-1:
            CustomiseTH1(chiSquare, colour, True, 0)
        else:
            CustomiseTH1(chiSquare, colour, False)
        
        # y-axis
        #chiSquare.GetYaxis().SetTitle("f #left(#chi^{2}#right)")
        chiSquare.GetYaxis().SetTitle("f (#chi^{2})")
        chiSquare.GetYaxis().SetLabelSize(0)
        chiSquare.GetYaxis().SetTickSize(0)
        
        # x-axis
        chiSquare.GetXaxis().SetTitle("#chi^{2}")
        chiSquare.GetXaxis().SetBinLabel(chiSquare.GetXaxis().FindBin(chiSqObs), "#color[4]{#chi^{2}_{obs}}")
        chiSquare.GetXaxis().LabelsOption("h")
        #chiSquare.GetXaxis().SetLabelSize(0)
        #chiSquare.GetXaxis().SetTickSize(0)

        # Append histograms to drawing list
        hList.append(chiSquare)

    # Draw the histograms
    DrawHistoList(hList, opts, 1)

    return


#================================================================================================ 
# Main
#================================================================================================ 
if __name__ == "__main__":
    '''
    https://docs.python.org/3/library/argparse.html
 
    name or flags...: Either a name or a list of option strings, e.g. foo or -f, --foo.
    action..........: The basic type of action to be taken when this argument is encountered at the command line.
    nargs...........: The number of command-line arguments that should be consumed.
    const...........: A constant value required by some action and nargs selections.
    default.........: The value produced if the argument is absent from the command line.
    type............: The type to which the command-line argument should be converted.
    choices.........: A container of the allowable values for the argument.
    required........: Whether or not the command-line option may be omitted (optionals only).
    help............: A brief description of what the argument does.
    metavar.........: A name for the argument in usage messages.
    dest............: The name of the attribute to be added to the object returned by parse_args().
    '''
    
    # Default Settings
    VERBOSE      = False
    BATCHMODE    = True
    SAVEDIR      = None    
    GRIDX        = False
    GRIDY        = False
    DOF          = 6
    SAVEFORMATS  = [".C", ".png", ".pdf"]
    
    # Define the available script options
    parser = OptionParser(usage="Usage: %prog [options]")

    parser.add_option("-v", "--verbose", dest="verbose", action="store_true", default=VERBOSE, 
                      help="Enables verbose mode (for debugging purposes) [default: %s]" % VERBOSE)

    parser.add_option("-b", "--batchMode", dest="batchMode", action="store_false", default=BATCHMODE, 
                      help="Enables batch mode (canvas creation does NOT generate a window) [default: %s]" % BATCHMODE)

    parser.add_option("--saveDir", dest="saveDir", type="string", default=SAVEDIR, 
                      help="Directory where all pltos will be saved [default: %s]" % SAVEDIR)
    
    parser.add_option("--gridX", dest="gridX", action="store_true", default=GRIDX, 
                      help="Enable x-axis grid? [default: %s]" % (GRIDX) )

    parser.add_option("--gridY", dest="gridY", action="store_true", default=GRIDY, 
                      help="Enable y-axis grid? [default: %s]" % (GRIDY) )

    parser.add_option("--dof", dest="dof", type="int", default=DOF, 
                      help="Number of degrees-of-freedom (DOF) [default: %d]" % (DOF) )

    parser.add_option("--saveFormats", dest="saveFormats", default=SAVEFORMATS, 
                      help="List of file formats to savethe canvas as [default: %s]" % (", ".join(SAVEFORMATS)) )

    (opts, parseArgs) = parser.parse_args()

    # Sanity check
    if opts.saveDir == None:
        opts.saveDir = os.getcwd()

    # Call the main function
    main(opts)

    if not opts.batchMode:
        raw_input("=== draw_ChiSqUpperQuantily.py: Press any key to quit ROOT ...")
