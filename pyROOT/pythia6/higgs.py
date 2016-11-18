#!/usr/bin/env python
'''
NB: The original PYTHIA6 files (Hgaga.dat  and GammaGamma.dat) can be found on lxplus at:
attikis@lxplus.cern.ch:/afs/cern.ch/work/a/attikis/pythia6/


http://hadron.physics.fsu.edu/~skpark/document/ROOT/RootLecture/RootLecture290305.pdf
root [1] TF1 *f = new TF1("myfunc", "TMath::BreitWigner(x,0,1)", -3, 3)
root [2] f->Draw()

https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookHowToFit

For unknown reason I could not get this to work (although it looks ok:
bw_formula = "[0]* [1]/((115.0-[2])*(115.0-[2]) + ([1]*[1])/4.0)" #bw_formula = "[0] * [1]/((115.0-[2])*(115.0-[2]) + ([1]*[1])/4.0)"
bw         = ROOT.TF1("bw", bw_formula, bw_xMin, bw_xMax) #mean=2, Gamma=1

bw.SetParameter(0, Lumi*99.3)
bw.SetParName  (0, "const")


bw.SetParameter(1, 5.0)
bw.SetParName  (1, "gamma")

bw.SetParameter(2, 115.0)
bw.SetParName  (2, "mean")

Standalone formula for Breit-Wigner fit:
bw_formula = "[0]*TMath::BreitWigner(x, [1], [2])"
bw         = ROOT.TF1("bw", bw_formula, bw_xMin, bw_xMax) #mean=0, Gamma=1
bw.SetParameter(0, Lumi*99.3)
bw.SetParName  (0, "const")
bw.SetParameter(1, 115.0)
bw.SetParName  (1, "mean")
bw.SetParameter(2, 5.0)
bw.SetParName  (2, "gamma")

'''

#------------------------------------------------------------------------
# Import files
#------------------------------------------------------------------------
import ROOT
import csv
import math
import os

#------------------------------------------------------------------------
# ROOT Settings
#------------------------------------------------------------------------
ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat("") # "mrn"
pi = 4*math.atan(1)

#------------------------------------------------------------------------
# Global Variables/Options
#------------------------------------------------------------------------
bRunFull   = False
bRunSkim   = not bRunFull
Lumi       =  1.0 # fb-1
#Lumi       = 30.0 # fb-1
xBinWidth  =  1.0 # GeV
xMin       = 100.0
xMax       = 150.0 #150.0
xTitle     = "m_{#gamma#gamma} (GeV)"
yTitle     = "Events / %0.1f GeV" % (xBinWidth)

# Setup Background (B) Fit Function
polN_formula = "[0] + [1]/x + [2]/pow(x, 2) + [3]/pow(x, 3) + [4]/pow(x, 4)"  #Note: "expo" #also works
polN         = ROOT.TF1("polN", polN_formula, xMin, xMax)

# Setup Signal (S) Fit Function
bw_xMin      = 105.0
bw_xMax      = 125.0
bw_formula   = "[0]*TMath::BreitWigner(x, [1], [2])"
bw           = ROOT.TF1("bw", bw_formula, bw_xMin, bw_xMax)
bw.SetParameter(0, Lumi*99.3)
bw.SetParName  (0, "bw: constx")
bw.SetParameter(1, 115.0)
bw.SetParName  (1, "bw: mean")
bw.SetParameter(2, 5.0)
bw.SetParName  (2, "bw: gamma")

# Setup the Data (S+B) Fit Function
sb_formula   = "[0] + [1]/x + [2]/pow(x, 2) + [3]/pow(x, 3) + [4]/pow(x, 4) + [5]*TMath::BreitWigner(x, [6], [7])"
sb           = ROOT.TF1("sb", sb_formula, xMin, xMax)
sb.SetParameter(5, Lumi*20000)
sb.SetParName  (5, "bw: constx")
sb.SetParameter(6, 115.0)
sb.SetParName  (6, "bw: mean")
sb.SetParameter(7, 5.0)
sb.SetParName  (7, "bw: gamma")
                      

#------------------------------------------------------------------------
# Functions
#------------------------------------------------------------------------
def AddText(xPos, yPos, text, bNDC=True, *args, **kwargs):
    '''
    Draws the custom text to the specific coordinates. If the relative
    coordinates are disables (NDC=False) then absolute axis values are
    used for the x- and y- coordinates of positioning the text.
    '''
    
    t = ROOT.TLatex()
    #t.SetTextFont(43)
    #t.SetTextSize(20)
    t.SetNDC(bNDC)
    t.DrawLatex(xPos, yPos, text)
    return


def CreateLegend(xMin, yMin, xMax, yMax, Header):
    '''
    Create a legend of custom dimensions + header.
    '''
    myLeg = ROOT.TLegend(xMin, yMin, xMax, yMax, Header)
    myLeg.SetFillStyle(0)
    myLeg.SetLineWidth(0)
    myLeg.SetBorderSize(0)
    myLeg.SetShadowColor(ROOT.kWhite)
    myLeg.SetTextSize(0.03)
    myLeg.SetTextFont(62)    
    return myLeg 


def DrawFitFunction(h, fitFunction, xRangeMin, xRangeMax, myLeg):
    '''
    '''
    
    # Fit function to histogram
    if fitFunction==None:
        return

    if h.GetEntries() < 1:
        return
    
    # Fit Options: "Q"= Quiet mode (minimum printing) "S" = The result of the fit is returned in the TFitResultPtr
    fitOpts = "S 0"
    f = fitFunction
    r = h.Fit(f, fitOpts, "", xRangeMin, xRangeMax)

    # Adde legent enty & draw function
    myLeg.AddEntry(f, str(f.GetName()), "l")
    f.Draw("same")

    # Get Fit Results:
    # chiSq   = r.Chi2()
    # dof     = r.Ndf()
    # chiSqN  = chiSq/dof;
    # p0Value = r.Parameter(0)
    # p0Error = r.ParError(0)
    # p1Value = r.Parameter(1)
    # p1Error = r.ParError(1)
    # p2Value = r.Parameter(2)
    # p2Error = r.ParError(2)
    return 
                       
def DrawHistoList(hList, colours, markerStyles, markerSizes, lineWidths, lineStyles, fillStyles, drawOpts,
                  legNames, legStyles, fitFunctions, xRangeMin, xRangeMax, xTitle, yTitle, bLogY=False):
    '''
    Draws all histograms in the histogram list (hList) 
    on the same canvas and saves it to local disk, under 
    the current working directory
    '''
    # Create a legend
    myLeg = CreateLegend(0.70, 0.70, 0.90, 0.90, "" )       

    # Create a canvas
    cName = hList[0].GetName()
    c     = ROOT.TCanvas(cName, cName, 1)

    # For-loop: All histograms in hList
    for i, h in enumerate(hList):

        # Customise histogram
        CustomiseTH1(h, colours[i], markerStyles[i], markerSizes[i], lineWidths[i], lineStyles[i], fillStyles[i], xTitle, yTitle)

        # Draw histogram
        if drawOpts[i] != "HIST9Same":
            h.Draw( drawOpts[i] )

        # Add legend entry
        if legStyles[i] != None:
            myLeg.AddEntry(h, legNames[i], legStyles[i])

        # Draw fit function
        DrawFitFunction(h, fitFunctions[i], xRangeMin[i], xRangeMax[i], myLeg)

    # Draw Legend
    myLeg.Draw()

    # Re-draw "data" histo
    hList[0].SetMinimum(1.0)
    if bLogY:
        hList[0].SetMaximum(hList[0].GetMaximum()*10)
    else:
        hList[0].SetMaximum(hList[0].GetMaximum()*1.2)
    hList[0].Draw( drawOpts[0] + "same" )

    # Add text
    AddText(0.66, 0.92, "#font[62]{%s fb^{-1} (10 TeV)}" % (str(Lumi)) )
    AddText(0.12, 0.85, "#font[62]{CMS}")
    AddText(0.12, 0.80, "#font[42]{H #rightarrow #gamma #gamma}")
    
    # Save canvas
    if bLogY:
        c.SetLogy(True)
    c.SaveAs(cName + ".png")
    c.SaveAs(cName + ".pdf")

    return


def CustomiseTF1(f, fName, lineColour, lineWidth, lineStyle):
    '''
    Customises a TF1 object
    '''
    # Fill
    f.SetName(fName)
    f.SetLineColor(lineColour)
    f.SetLineWidth(lineWidth)
    f.SetLineStyle(lineStyle)

    return

def CustomiseTH1(histo, colour, markerStyle, markerSize, lineWidth=2, lineStyle=1, fillStyle=1001, xTitle="x-Axis", yTitle="y-Axis"):
    '''
    Customises a TH1 object
    '''

    # Fill
    histo.SetFillColor(colour)
    histo.SetFillStyle(fillStyle)

    # Marker
    histo.SetMarkerStyle(markerStyle)
    histo.SetMarkerColor(colour)
    histo.SetMarkerSize(markerSize)
    
    # Line
    histo.SetLineColor(colour)
    histo.SetLineWidth(lineWidth)
    histo.SetLineStyle(lineStyle)

    # X-Axis
    histo.GetXaxis().SetTitle(xTitle)
    histo.GetXaxis().SetTitleOffset(1.2)

    # Y-Axis
    histo.GetYaxis().SetTitle(yTitle)
    histo.GetYaxis().SetTitleOffset(1.3)
    histo.SetMinimum(0.0);
    return

def CreateTH1F(hName, hTitle, binWidthX, xMin, xMax):
    '''
    Creates a custom histogram of type 1-dimenstion, float.
    '''
    nBinsX = int((xMax-xMin)/binWidthX)
    h = ROOT.TH1F(hName, hTitle, nBinsX, xMin, xMax)
    
    return h


def GetFile(filePath, fileName, mode='r+'):
    '''
    Opens a file in a given mode.
    '''
    if filePath.endswith("/")==False:
        filePath = filePath + "/"

    f = open(filePath + fileName, mode)
    return f


def GetP4(px, py, pz, energy):
    '''
    Takes as argument px, py, pz, energy of a particle.
    Returns it 4-momentum in a ROOT.TLorentzVector object
    '''
    p4 = ROOT.TLorentzVector()
    p4.SetPxPyPzE( px, py, pz, energy)
    return p4


def GetSmearedPt(p4):
    '''
    Takes as argument a TLorentzVector object. Applies gaussian resolution smearing (pT) 
    and returns it.
    '''
    r       = ROOT.gRandom.Gaus(0,1)
    sigmaPt = p4.Pt()*0.01
    smearedPt = p4.Pt() + r*sigmaPt
    #print "pT = %s, r = %s, sigmaPt = %s, pT_smeared = %s" % (p4.Pt(), r, sigmaPt, smearedPt)
    return smearedPt

def GetSmearedPhi(p4):
    ''' 
    Takes as argument a TLorentzVector object. Applies gaussian resolution smearing (phi) 
    and returns it.
    '''
    r          = ROOT.gRandom.Gaus(0,1)
    sigmaPhi   = 0.02 #mrads
    smearedPhi = p4.Phi() + r*sigmaPhi
    #print "phi = %s, r = %s, sigmaPhi = %s, phi_smeared = %s" % (p4.Phi(), r, sigmaPhi, smearedPhi)
    return smearedPhi

def GetSmearedTheta(p4):
    '''
    Takes as argument a TLorentzVector object. Applies gaussian resolution smearing (theta) 
    and returns it.
    '''
    r            = ROOT.gRandom.Gaus(0,1)
    sigmaTheta   = 0.02
    smearedTheta = p4.Theta() + r*sigmaTheta
    #print "theta = %s, r = %s, sigmaTheta = %s, theta_smeared = %s" % (p4.Theta(), r, sigmaTheta, smearedTheta)

    # Protection against problematic values (re-smear. very vew cases)
    while smearedTheta <= 0.0 or smearedTheta >= pi:
        r            = ROOT.gRandom.Gaus(0,1)
        sigmaTheta   = 0.02
        smearedTheta = p4.Theta() + r*sigmaTheta

    return smearedTheta

def GetSmearedEta(p4):
    '''
    Takes as argument a TLorentzVector object. Applies gaussian resolution smearing (theta) 
    but returns eta.
    '''
    smearedTheta = GetSmearedTheta(p4)
    smearedEta   = -math.log(math.tan(smearedTheta/2))
    #print "eta = %s, eta_smeared = %s" % (p4.Eta(), smearedEta)
    return smearedEta

def GetSmearedP4(p4):
    '''
    Takes as argument a TLorentzVector object. Applies gaussian resolution smearing (pT, eta, phi) 
    and returns it.
    '''
    pt  = GetSmearedPt (p4)
    eta = GetSmearedEta(p4)
    phi = GetSmearedPhi(p4)
    m   = p4.M()
    smearedp4 = ROOT.TLorentzVector()
    smearedp4.SetPtEtaPhiM( pt, eta, phi, m)
    return smearedp4

def ApplyTrgAndKinematics(evtToIndexDict, pIndexList, pdgIdList, motherList, pxList, pyList, pzList, energyList, massList, bVerbose=False):
    '''
    Apply trigger and kinematics cuts.
    '''
    trg_evtToIndexDict = {}

    print "\n=== higgs.py:\n\t Applying Trigger & Event Selection to \"%s\" events" % ( len(evtToIndexDict.keys()) )
    # For-loop: All events (only photons at this point)
    for evt in evtToIndexDict:
        indexList      = evtToIndexDict[evt]
        nPhotons       = 0
        nPhotons_35GeV = 0
        nPhotons_40GeV = 0

        # For-loop: All particles
        for i in indexList:
            pIndex = pIndexList[i]
            px    = pxList[i]
            py    = pyList[i]
            pz    = pzList[i]
            e     = energyList[i]
            pdgId = pdgIdList[i]
            p4    = GetP4( px, py, pz, e)
            mom   = motherList[i]
            momId = pdgIdList[mom]

            # Apply the trigger thresholds to the smeared pt/eta
            smearedP4 = GetSmearedP4(p4)
            if (smearedP4.Pt() > 30) and (abs(smearedP4.Eta()) < 2.5):
                nPhotons = nPhotons+1
                if (smearedP4.Pt() > 35):
                    nPhotons_35GeV = nPhotons_35GeV + 1                    
                if (smearedP4.Pt() > 40):
                    nPhotons_40GeV = nPhotons_40GeV + 1

        # Apply trigger at end of particle loop
        if (nPhotons >= 2):
            # Apply offline selections
            if ( (nPhotons_35GeV >= 2) and (nPhotons_40GeV >= 1) ):
                trg_evtToIndexDict[evt] = indexList
        
    PrintEvtToIndexDict(trg_evtToIndexDict, pIndexList, pdgIdList, motherList, pxList, pyList, pzList, energyList, massList, bVerbose)

    # Calculate Trigger efficiency
    N_all = len(evtToIndexDict.keys())
    N_trg = len(trg_evtToIndexDict.keys())
    eff   = float(N_trg)/float(N_all)
    len(trg_evtToIndexDict.keys())/len(evtToIndexDict.keys())
    #print "\n=== higgs.py:\n\t Trigger & Event Selection efficiency = %s" % (eff)
    print "\t Trigger & Event Selection efficiency = %s" % (eff)
    
    return trg_evtToIndexDict


def EvtAnalysis(evtToIndexDict, pIndexList, pdgIdList, motherList, pxList, pyList, pzList, energyList, massList, bVerbose=False):
    '''
    Reconstructs invariant mass using highest pT photons. 
    '''
    print "\n=== higgs.py:\n\t Saving combined 4-momenta of photons for \"%s\" events" % ( len(evtToIndexDict.keys()) )
    
    
    if bVerbose:
        print "="*40
        print '{:<15} {:<15}'.format("Event", "Invariant Mass [GeV]")
        print "="*40

    # Variable declaration
    p4List = []
    
    # For-loop: All events (only photons at this point)
    for evt in evtToIndexDict:

        # Initilise variables
        indexList = evtToIndexDict[evt]
        p4_Sum   = ROOT.TLorentzVector()
        p4_Sum.SetPxPyPzE( 0, 0, 0, 0)


        # For-loop: All particles
        for i in indexList:
            pIndex = pIndexList[i]
            px     = pxList[i]
            py     = pyList[i]
            pz     = pzList[i]
            e      = energyList[i]
            pdgId  = pdgIdList[i]
            p4     = GetSmearedP4( GetP4( px, py, pz, e) )
            mom    = motherList[i]
            momId  = pdgIdList[mom]
            p4_Sum = p4_Sum + p4

        # Sum-up 4-momenta
        p4List.append(p4_Sum)

        # Print invariant mass particle and print info
        if bVerbose:
            print '{:<15} {:<15}'.format(evt, p4_Sum.M())
            
    return p4List


def FilterParticles(myPdgId, eventList, pIndexList, pdgIdList, motherList, pxList, pyList, pzList, energyList, massList, bVerbose=False):
    '''
    '''

    # Variable declaration
    evtToIndexDict = {}
    indexList      = []
    p4List         = []
    evt_tmp        = -1
    PrintInfoTitle(bVerbose)

    print "\n=== higgs.py:\n\t Filtering list of length \"%s\" for particle with pdgId = \"%s\"" % (len(eventList), myPdgId)
    # For-loop: All events
    for i, evt in enumerate(eventList):
        # Get Variables
        pIndex = pIndexList[i]
        px    = pxList[i]
        py    = pyList[i]
        pz    = pzList[i]
        e     = energyList[i]
        pdgId = pdgIdList[i]
        p4    = GetP4( px, py, pz, e)
        mom   = motherList[i]
        momId = pdgIdList[mom]
            
        # Reset variables when new event is processed
        if evt!= evt_tmp:
            if len(indexList)>0:
                evtToIndexDict[evt_tmp] = indexList
            evt_tmp   = evt
            p4List    = []
            indexList = []
            
        # Skip if not a photon
        if pdgId != myPdgId:
            continue

        # Dump v. low pT particles (for bkg)
        if p4.Pt() < 5:
            continue
        
        # Ensure that each photon is considered just once
        dRmin = 9990.9
        for p4_tmp in p4List:
            dR = DeltaR(p4_tmp, p4)
            if dR < dRmin:
                dRmin = dR
        if dRmin <= 0.1:
            continue

        # Save particle and print info
        PrintInfo(evt, pIndex, p4, pdgId, mom, momId, bVerbose)
        p4List.append(p4)
        
        # Append evt to list
        indexList.append(i)

    #PrintEvtToIndexDict(evtToIndexDict, pIndexList, pdgIdList, motherList, pxList, pyList, pzList, energyList, massList, bVerbose)
    return evtToIndexDict


def PrintEvtToIndexDict(evtToIndexDict, pIndexList, pdgIdList, motherList, pxList, pyList, pzList, energyList, massList, bVerbose=True):
    '''
    '''
    PrintInfoTitle(bVerbose)
    
    # For-loop: All events (only photons at this point)
    for evt in evtToIndexDict:
        indexList = evtToIndexDict[evt]

        # For-loop: All particles
        for i in indexList:
            pIndex = pIndexList[i]
            px     = pxList[i]
            py     = pyList[i]
            pz     = pzList[i]
            e      = energyList[i]
            pdgId  = pdgIdList[i]
            p4     = GetP4( px, py, pz, e)
            mom    = motherList[i]
            momId  = pdgIdList[mom]
            PrintInfo(evt, pIndex, p4, pdgId, mom, momId, bVerbose)

    return


def DeltaR(p4_1, p4_2):
    '''
    Distance in eta-phi space.
    '''
    import math
    
    deltaPhi  = p4_1.Phi() - p4_2.Phi()
    deltaEta  = p4_1.Eta() - p4_2.Eta()
    deltaR_Sq = deltaPhi*deltaPhi + deltaEta*deltaEta
    deltaR    = math.sqrt(deltaR_Sq)    
    return deltaR


def IsOwnMother(pdgId, momId):
    '''
    The information for the position of the mother particle was added to avoid the problem
    of using a duplicate particle from PYTHIA. For example, in the decay of the Higgs boson to two photons the decay information
    is written twice by PYTHIA because it requires so corrections to be made in the centre of mass of the final products.
    However, you don't want to select the same particle twice. For this reason, you must check that the particle you are using has its self as a mother.
    Therefore, you need th check that the pdgId that corresponds to the mother is the same as the particle under investigation.
    '''
    if pdgId == momId:
        return True
    else:
        return False


def PrintInfo(evt, pIndex, p4, pdgId, mom, momId, bVerbose=True):
    '''
    '''
    if (bVerbose==False):
        return
    
    pInfo = '{:<15} {:<15} {:>15}  {:>15}  {:>15} {:>15} {:>15} {:>15} {:>15}'.format(evt, pIndex, "%0.3f" %p4.Pt(), "%0.3f" %p4.Eta(), "%0.3f" %p4.Phi(), "%0.3f" %p4.Energy(), pdgId, mom, momId)
    print pInfo
            
    return


def PrintInfoTitle(bVerbose=True):
    '''
    '''
    if (bVerbose==False):
        return

    title = '{:<15} {:<15} {:>15}  {:>15}  {:>15} {:>15} {:>15} {:>15} {:>15}'.format( "Event", "PIndex", "Pt [GeV/c]", "Eta", "Phi [rads]", "Energy [GeV]", "PdgId", "Mother", "MomId")
    print "="*150
    print title
    print "="*150
            
    return


def GetDataFromFile(inputFile, maxEvents= -1, bVerbose=False):
    '''
    '''

    # Declare lists
    eventList  = []
    pIndexList = []
    pdgIdList  = []
    motherList = []
    pxList     = []
    pyList     = []
    pzList     = []
    energyList = []
    massList   = []    
    
    # Declarations
    PrintInfoTitle(bVerbose)
    counter = 0
    p4 = ROOT.TLorentzVector()

    print "\n=== higgs.py:\n\t Reading file \"%s\"" % (inputFile.name)    
    # For-loop: Lines in file (signal)
    for line in inputFile.xreadlines():
        row = line.split()

        # Some errors in writing the ".dat" files result in pIndex > 999 to be '***'
        if "***" in line:
            continue
        #  Safety
        if len(row) < 9:
            continue
        
        # Get the variables
        evt    = int( row[0] )
        pIndex = int( row[1] )
        pdgId  = int( row[2] )
        mom    = int( row[3] )
        px     = float( row[4] )
        py     = float( row[5] )
        pz     = float( row[6] )
        energy = float( row[7] )
        mass   = float( row[8] )
        p4.SetPxPyPzE( px, py, pz, energy)
        
        # Append to list
        eventList .append( evt    )
        pIndexList .append( pIndex  )
        pdgIdList .append( pdgId  )
        motherList.append( mom    ) 
        pxList    .append( px     )
        pyList    .append( py     )
        pzList    .append( pz     )
        energyList.append( energy )
        massList  .append( mass   )
        
        # Increment counter
        counter = counter + 1
        if pdgId != 2212:
            PrintInfo(evt, pIndex, p4, pdgId, mom, -1, bVerbose)

        # Apply limit on number of events ?
        if (maxEvents > 0) and (counter >= maxEvents):
            break

    return eventList, pIndexList, pdgIdList, motherList, pxList, pyList, pzList, energyList, massList


def WriteDataToFile(filePath, fileName, rowsList):
    '''
    '''

    if filePath.endswith("/")==False:
        filePath = filePath + "/"

    print "\n=== higgs.py:\n\t Writing \"%s\" rows to file \"%s\"" % (len(rowsList), filePath + fileName)

    # Open file
    f = open(filePath + fileName, mode='w+')
    
    # For-loop: All rows
    for r in rowsList:
        #print "type(%s) = %s", (r, type(r))

        rowType = type(r)
        row     = ""
        if rowType == ROOT.TLorentzVector:
            row = str(r.M()) + "\n"
        elif rowType not in ["int", "float"]:
            row = str(r) + "\n"
        else:
            print "\n=== higgs.py:\n\t Cannot write unknown variable of type \"%s\" to file \"%s\". EXIT" % (rowType, filePath + fileName)
            exit(0)
        f.write(row)

    return f


def GetColumnFromFile(filePath, fileName, columnNumber=0):
    '''
    '''

    if filePath.endswith("/")==False:
        filePath = filePath + "/"

    # Open file
    f = open(filePath + fileName, "r")
    rowsList = []
    
    for line in f.xreadlines():
        row = line.split()

        if (columnNumber > len(row)-1):
            print "\n=== higgs.py:\n\t Cannot read column number \"%s\" from file \"%s\". EXIT" % (columnNumbrer, filePath + fileName)
            exit(0)
            
        rowsList.append(row[columnNumber])

    return rowsList


def GetFilledAndWeightedHisto( hName, hTitle, xBinWidth, xMin, xMax, p4List=[], weight=1.0):
    '''
    '''

    # Book the histogram
    histo = CreateTH1F( hName, hTitle, xBinWidth, xMin, xMax)

    # Sanity check
    if len(p4List) < 1:
        return histo
    
    # Fill the histogram
    for p4 in p4List:

        if type(p4) == ROOT.TLorentzVector:
            histo.Fill ( p4.M() )
        elif type(p4) not in ["int", "float"]:
            M = float(p4)
            histo.Fill(M)
        else:
            print "\n=== higgs.py:\n\t Cannot write unknown variable of type \"%s\" to histogram with name \"%s\". EXIT" % (rowType, hName)
            exit(0)
                
    # Normalise to luminosity
    histo.Scale( weight )

    return histo


def GetNEvtsGenerated(eventList):
    '''
    '''
    print "\n=== higgs.py:\n\t Calculating number of events from list of length \"%s\"" % (len(eventList))
    
    evt_tmp = eventList[0]    
    nEvts   = 0
    # For-loop: All events
    for i, evt in enumerate(eventList):

        # Reset variables when new event is processed
        if evt!= evt_tmp:
            nEvts   = nEvts +1 
            evt_tmp = evt

    return nEvts

    
#------------------------------------------------------------------------
if __name__ == "__main__":

    # Variable declaration
    s_p4List = []
    b_p4List = []

    if bRunFull:
        # Get the files
        signalFile = GetFile("/Users/attikis/hltaus/pyROOT/otherScripts/pythia6/", "Hgaga.dat"     , "r")
        bkgFile    = GetFile("/Users/attikis/hltaus/pyROOT/otherScripts/pythia6/", "GammaGamma.dat", "r")
        
        # Get the data from the signal/bkg file
        s_eventList, s_pIndexList, s_pdgIdList, s_motherList, s_pxList, s_pyList, s_pzList, s_energyList, s_massList = GetDataFromFile(signalFile, -1, False )
        b_eventList, b_pIndexList, b_pdgIdList, b_motherList, b_pxList, b_pyList, b_pzList, b_energyList, b_massList = GetDataFromFile(bkgFile   , -1, False )
        
        
        # Get the number of events generated & read
        s_NGen = GetNEvtsGenerated(s_eventList)
        b_NGen = GetNEvtsGenerated(b_eventList)
        
        # Create a skim file containing only triggered events and containing just photons
        WriteDataToFile(os.getcwd(), "Hgaga_NGen.dat"     , [s_NGen] )
        WriteDataToFile(os.getcwd(), "GammaGamma_NGen.dat", [b_NGen] )
        
        # Remove all events/entries which does not involve a photon (after radiation)
        s_EvtToIndexDict = FilterParticles(22, s_eventList, s_pIndexList, s_pdgIdList, s_motherList, s_pxList, s_pyList, s_pzList, s_energyList, s_massList, False )
        b_EvtToIndexDict = FilterParticles(22, b_eventList, b_pIndexList, b_pdgIdList, b_motherList, b_pxList, b_pyList, b_pzList, b_energyList, b_massList, False )
        
        # Apply trigger and event selection
        s_trgEvtToIndexDict = ApplyTrgAndKinematics( s_EvtToIndexDict, s_pIndexList, s_pdgIdList, s_motherList, s_pxList, s_pyList, s_pzList, s_energyList, s_massList, False )
        b_trgEvtToIndexDict = ApplyTrgAndKinematics( b_EvtToIndexDict, b_pIndexList, b_pdgIdList, b_motherList, b_pxList, b_pyList, b_pzList, b_energyList, b_massList, False )

        # Perform the invariant mass analysis
        s_p4List = EvtAnalysis( s_trgEvtToIndexDict, s_pIndexList, s_pdgIdList, s_motherList, s_pxList, s_pyList, s_pzList, s_energyList, s_massList, False )
        b_p4List = EvtAnalysis( b_trgEvtToIndexDict, b_pIndexList, b_pdgIdList, b_motherList, b_pxList, b_pyList, b_pzList, b_energyList, b_massList, False )

        # Create a skim file containing only triggered events and containing just photons
        WriteDataToFile(os.getcwd(), "Hgaga_Skim.dat"     , s_p4List)
        WriteDataToFile(os.getcwd(), "GammaGamma_Skim.dat", b_p4List)

        
    if bRunSkim:
        # Get the data from the signal/bkg file
        s_p4List = GetColumnFromFile(os.getcwd(), "Hgaga_Skim.dat"     , columnNumber=0)
        b_p4List = GetColumnFromFile(os.getcwd(), "GammaGamma_Skim.dat", columnNumber=0)
        
        # Get the data from the signal/bkg file
        s_NGenList = GetColumnFromFile(os.getcwd(), "Hgaga_NGen.dat"     , columnNumber=0)
        b_NGenList = GetColumnFromFile(os.getcwd(), "GammaGamma_NGen.dat", columnNumber=0)
        s_NGen     = float(s_NGenList[0])
        b_NGen     = float(b_NGenList[0])
    
    # Customise fitting functions    
    CustomiseTF1(bw  , "S"           , ROOT.kBlue, 1, ROOT.kSolid  )
    CustomiseTF1(sb  , "S+B"         , ROOT.kRed   , 3, ROOT.kSolid  )
    CustomiseTF1(polN, "B Component" , ROOT.kRed   , 3, ROOT.kDashed )

    ### Custom histogram settings
    colours      = [ROOT.kBlack     , ROOT.kRed           , ROOT.kRed             ]
    markerStyles = [ROOT.kFullCircle, ROOT.kFullTriangleUp, ROOT.kFullTriangleDown]
    markerSizes  = [1.0             , 0.0                 , 0.0                   ] 
    lineWidths   = [0               , 0                   , 0                     ]
    lineStyles   = [ROOT.kSolid     , ROOT.kSolid         , ROOT.kDotted          ]
    fillStyles   = [3001            , 0000                , 0000                  ]
    drawOpts     = ["PE1"           , "HIST9Same"         , "HIST9Same"           ]
    legNames     = ["Data"          , "Signal"            , "Bkg"                 ]
    legStyles    = ["PE1"           , None                , None                  ]
    fitFunctions = [sb              , bw                  , polN                  ]
    xRangeMin    = [xMin            , xMin                , xMin                  ]
    xRangeMax    = [xMax            , xMax                , xMax                  ]

    
    # Calculate the weights:
    '''
    N    = sigma * L     [Eq. 1]
    N_mc = sigma * L_mc  [Eq. 2]
    
    Divide the two:
    N/N_mc = L/L_mc
    => N   = L/L_mc * N_mc [w = L/L_mc]
    => N   = w * N_mc
    where:
    w = L/L_mc
    '''
    s_xSection =    99.3 # fb
    b_xSection = 20000.0 # fb
    s_weight   = Lumi * (1.0/s_NGen) * s_xSection #Lumi * (1.0/s_NGen) * s_xSection
    b_weight   = Lumi * (1.0/b_NGen) * b_xSection

    
    # Fill & Weight the S and B histograms
    hInvMass_SB = GetFilledAndWeightedHisto( "InvMass_%0.0ffb" % Lumi, "", xBinWidth, xMin, xMax)
    hInvMass_S  = GetFilledAndWeightedHisto( "InvMass_S" , "", xBinWidth, xMin, xMax, s_p4List, s_weight )
    hInvMass_B  = GetFilledAndWeightedHisto( "InvMass_B" , "", xBinWidth, xMin, xMax, b_p4List, b_weight )
    hInvMass_SB.Add(hInvMass_S)
    hInvMass_SB.Add(hInvMass_B)

    
    # Append to Histogram list & Draw
    hList = []
    hList.append(hInvMass_SB)    
    hList.append(hInvMass_S)
    hList.append(hInvMass_B)
    DrawHistoList(hList, colours, markerStyles, markerSizes, lineWidths, lineStyles, fillStyles, drawOpts, legNames, legStyles, fitFunctions, xRangeMin, xRangeMax, xTitle, yTitle)

    for b in range(0, hInvMass_SB.GetNbinsX()+1):
        h = hInvMass_SB
        N = h.GetBinContent(b)
        h.SetBinError( b, math.sqrt(N) )
        h.SetBinError( b, math.sqrt(N) )
        

    # Get Statistical Significance
    #nS  = hInvMass_S.Integral( hInvMass_S.FindBin(bw_xMin) , hInvMass_S.FindBin(bw_xMax) )
    nB  = hInvMass_B.Integral ( hInvMass_B .FindBin(bw_xMin), hInvMass_B .FindBin(bw_xMax) )
    nSB = hInvMass_SB.Integral( hInvMass_SB.FindBin(bw_xMin), hInvMass_SB.FindBin(bw_xMax) )
    nS  = nSB-nB
    #print "nSB = %s, nB = %s, nS = %s" % (nSB, nB, nS)


    # Calculate Statistical Significance of peak
    if nB > 0:
        significance = nS / math.sqrt(nB)
        print "\n*** Significance = S/sqrt(B) = %0.1f/sqrt(%0.1f) = %0.1f" % (nS, nB, significance)
    else:
        print "\n*** Significance = nan"
