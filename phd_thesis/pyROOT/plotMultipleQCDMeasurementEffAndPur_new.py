########################################################################
# -*- python -*-
# File Name .....: plotQCDMeasurementEffAndPur.py
# Original Author: Alexandros Attikis
# e-mail ........: attikis@cern.ch
# Institute .....: UCY
# Created .......: Friday, 16 Dec 2010 
# Last Edited ...: Friday, 7 Jan 2011
# Description ...: Python script that takes as input a dat or text file
#                  generated by the hplusPrintCounters.py script and
#                  uses as input the number of events passing specific
#                  cuts. It returns the efficiency and purity of the QCD
#                  samples, based on Bayesian methods.
#                  The efficiency is defined as: e = N/No
#                  where:
#                  N  = Events passing all the cuts
#                  No = Events passing the jet selection
#                  The purity is also calculated for each QCD pT-bin 
#                  by by the use of pseudo-experiments performed using
#                  the binomial distribution. Two parameters are required
#                  for this:
#                  i. the probability to pass the cut flow after jetSelection (fakeMET, Nbjets, e/mu veto, MET)
#                     i.e. the effiiciency of specific sample for the cut flow
#                  ii. the number of starting events (i.e. number of events after the Trigger, tauAntiIsolation and jetSelection)
# Instuctions ...: 
#                  |myLinux> python plotQCDMeasurementEffAndPur.py 
# OR
#                  |myLinux> python plotQCDMeasurementEffAndPur.py testFile.dat
# where testFile.dat is an example dat file provided for testing purposes
########################################################################
#!/usr/bin env python
from __future__ import division
### System imports
import os, sys
from array import array
from math import fabs
### ROOT imports
from ROOT import *
### HiggsAnalysis imports
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.dataset import *
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.histograms import *
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.hplustyle import *
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.FindFirstBinAbove import * 
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.bayes import * 
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.myArrays import *

### Provide the name of the file to be opened 
if len(sys.argv) > 1:
    file = sys.argv[1]
### Otherwise use as default the name counters.dat
else:
    file = 'counters.dat'

### If the file already exists remove it since the script will automatically generate one.
if os.path.exists(file):
    os.system('rm %s'%(file))
os.system('hplusPrintCounters3.py --mainCounterOnly > %s ; echo "EOF" >> %s'%(file,file))
#os.system('hplusPrintCounters3.py --mode xsect --mainCounterOnly > %s ; echo "EOF" >> %s'%(file,file))

######################################################################################
### Options
######################################################################################
bVerbosity = False
bSaveFiles = True
bSaveCanvases = True
style = HPlusStyle()
uniquePath = "/Met00_NJets2/"
#uniquePath = "/Met10_NJets2/"
#uniquePath = "/Met20_NJets2/"
#uniquePath = "/Met30_NJets2/"
#uniquePath = "/Met40_NJets2/"
#uniquePath = "/Met50_NJets2/"
#uniquePath = "/Met60_NJets2/"
#uniquePath = "/Met70_NJets2/"
homePath    = "/afs/cern.ch/user/a/attikis/"
figuresPath = "/scratch0/qcdMeasurementByIsolationVeto/MetCutInvestigation/No_HLT_Emulation/figures/"
FileName_eff = homePath + figuresPath + uniquePath + "efficiencies.dat"
FileName_pur = homePath + figuresPath + uniquePath + "purities.dat"
CanvasSavePath = homePath + figuresPath + uniquePath
######################################################################################
### Open file and get information
######################################################################################
file = open('%s'%(file), 'r')
### Define lists to be used
DataSetName = []
CutNamesAndValues = []
DataSetAndXSectAndNormFact = []
### Loop over lines and save the cut-flow info (Cross Section for MC, Events for data)
lim = True
while file:
    line = file.readline()
    # split the line and puts elements in list s as strings
    s = line.split()
    if 'EOF' in s:
        break
    nColumns = len(s) 
    ### Investigate lists which have three elements (i.e. 3 is the number of columns of each list)
    if nColumns == 3:
        ### Save the names of the datasets, cross section and normalisation factor
        DataSetAndXSectAndNormFact.append([s[0], s[1], s[2]])
    if nColumns == 10:
        if lim == True:
            for i in range(nColumns):
                DataSetName.append(s[i])
            lim = False
        else:
            for i in range(1,nColumns):
                CutNamesAndValues.append([DataSetName[i],s[0],float(s[i])])

######################################################################################
### Print the DataSet Name, Cross Section and MC Normalisation Factor (in this order)
######################################################################################
if bVerbosity == True:
    print
    print "********************************************************************"
    print "* Printing DataSet Name, Cross Section and MC Normalisation Factor *" 
    print "********************************************************************"
    print "DataSetAndXSectAndNormFact = ", DataSetAndXSectAndNormFact
    print "For Wjets  we have ..."
    print "DataSetAndXSectAndNormFact[0][0] = ", DataSetAndXSectAndNormFact[0][0]
    print "DataSetAndXSectAndNormFact[0][1] = ", DataSetAndXSectAndNormFact[0][1]
    print "DataSetAndXSectAndNormFact[0][2] = ", DataSetAndXSectAndNormFact[0][2]
    print "For QCD_Pt30to50 we have ..."
    print "DataSetAndXSectAndNormFact[1][0] = ", DataSetAndXSectAndNormFact[1][0]
    print "DataSetAndXSectAndNormFact[1][1] = ", DataSetAndXSectAndNormFact[1][1]
    print "DataSetAndXSectAndNormFact[1][2] = ", DataSetAndXSectAndNormFact[1][2]
    print "********************************************************************"

######################################################################################
### Declare the Normalisation Factors for each DataSet
######################################################################################
WJets_NormFactor        = float(DataSetAndXSectAndNormFact[0][2])
qcd30to50_NormFactor    = float(DataSetAndXSectAndNormFact[1][2])
qcd50to80_NormFactor    = float(DataSetAndXSectAndNormFact[2][2])
qcd80to120_NormFactor   = float(DataSetAndXSectAndNormFact[3][2])
qcd120to170_NormFactor  = float(DataSetAndXSectAndNormFact[4][2])
qcd170to230_NormFactor  = float(DataSetAndXSectAndNormFact[5][2])
qcd230to300_NormFactor  = float(DataSetAndXSectAndNormFact[6][2])
TTbar_NormFactor        = float(DataSetAndXSectAndNormFact[7][2])
TTbarJets_NormFactor    = float(DataSetAndXSectAndNormFact[8][2])

######################################################################################
### Define lists that will hold the information (Cut Name and Events surviving cuts)
######################################################################################
WJets        = []
qcd30to50    = []
qcd50to80    = []
qcd80to120   = []
qcd120to170  = []
qcd170to230  = []
qcd230to300  = []
TTbarJets    = []
TTbar        = []

######################################################################################
### Loop over all cut names and create new lists according to the DataSet Name
######################################################################################
for item in CutNamesAndValues:
    name = item[0]
    tmp = [item[1],item[2]]
    if name == 'WJets':
        WJets.append(tmp)
    if name == 'QCD_Pt30to50':
        qcd30to50.append(tmp)
    if name == 'QCD_Pt50to80':
        qcd50to80.append(tmp)
    if name == 'QCD_Pt80to120':
        qcd80to120.append(tmp)
    if name == 'QCD_Pt120to170':
        qcd120to170.append(tmp)
    if name == 'QCD_Pt170to230':
        qcd170to230.append(tmp)
    if name == 'QCD_Pt230to300':
        qcd230to300.append(tmp)
    if name == 'TTbar':
        TTbar.append(tmp)
    if name == 'TTbarJets':
        TTbarJets.append(tmp)

######################################################################################
### Print lists 
######################################################################################
if bVerbosity == True:
    print
    print "*******************************************"
    print "* Printing cut-flow for each DataSet Name *"
    print "*******************************************"
    print 'qcd30to50', qcd30to50
    print
    print 'qcd50to80', qcd50to80
    print
    print 'qcd80to120', qcd80to120
    print
    print 'qcd120to170', qcd120to170
    print
    print 'qcd170to230', qcd170to230
    print
    print 'qcd230to300', qcd230to300
    print
    print 'TTbarJets', TTbarJets
    print
    print 'TTbar', TTbar
    print
    print 'W+Jets', WJets
    print "*******************************************"

######################################################################################
### Save xSections before and after cuts (xSection = Evts*NormFactor)
######################################################################################
XSectTotalTTbar  = TTbar[4][1]*TTbar_NormFactor
XSectTotalWJets  = WJets[4][1]*WJets_NormFactor
XSectTotalEWK    = XSectTotalTTbar + XSectTotalWJets

XSectPassedTTbar = TTbar[-1][1]*TTbar_NormFactor
XSectPassedWJets = WJets[-1][1]*WJets_NormFactor
XSectPassedEWK   = XSectPassedTTbar + XSectPassedWJets

XSectTotalQCD  = qcd30to50[4][1]*qcd30to50_NormFactor + qcd50to80[4][1]*qcd50to80_NormFactor + qcd80to120[4][1]*qcd80to120_NormFactor + qcd120to170[4][1]*qcd120to170_NormFactor + qcd170to230[4][1]*qcd170to230_NormFactor + qcd230to300[4][1]*qcd230to300_NormFactor

XSectPassedQCD = qcd30to50[-1][1]*qcd30to50_NormFactor + qcd50to80[-1][1]*qcd50to80_NormFactor + qcd80to120[-1][1]*qcd80to120_NormFactor + qcd120to170[-1][1]*qcd120to170_NormFactor + qcd170to230[-1][1]*qcd170to230_NormFactor + qcd230to300[-1][1]*qcd230to300_NormFactor

######################################################################################
### Save Events before and after cuts
######################################################################################
### Save Events before the Cut-Flow (but after Trigger, Anti-Isolation and Njets cuts)
IntLumi = 40
qcd30to50_EvtsJetSel   = qcd30to50[4][1]
qcd50to80_EvtsJetSel   = qcd50to80[4][1]
qcd80to120_EvtsJetSel  = qcd80to120[4][1]
qcd120to170_EvtsJetSel = qcd120to170[4][1]
qcd170to230_EvtsJetSel = qcd170to230[4][1]
qcd230to300_EvtsJetSel = qcd230to300[4][1]
ttbar_EvtsJetSel       = TTbar[4][1]
wjets_EvtsJetSel       = WJets[4][1]
ewk_EvtsJetSel = ttbar_EvtsJetSel + wjets_EvtsJetSel
qcd_EvtsJetSel = qcd30to50_EvtsJetSel+qcd50to80_EvtsJetSel+qcd80to120_EvtsJetSel+qcd120to170_EvtsJetSel+qcd170to230_EvtsJetSel+qcd230to300_EvtsJetSel

### Save xSections of samples after Jet Selection
qcd30to50_xSectionJetSel   = qcd30to50[4][1]*qcd30to50_NormFactor
qcd50to80_xSectionJetSel   = qcd50to80[4][1]*qcd50to80_NormFactor
qcd80to120_xSectionJetSel  = qcd80to120[4][1]*qcd80to120_NormFactor
qcd120to170_xSectionJetSel = qcd120to170[4][1]*qcd120to170_NormFactor
qcd170to230_xSectionJetSel = qcd170to230[4][1]*qcd170to230_NormFactor
qcd230to300_xSectionJetSel = qcd230to300[4][1]*qcd230to300_NormFactor
ttbar_xSectionJetSel       = TTbar[4][1]*TTbar_NormFactor
wjets_xSectionJetSel       = WJets[4][1]*WJets_NormFactor

ttbar_EvtsAllCuts = TTbar[-1][1]
wjets_EvtsAllCuts = WJets[-1][1]
ewk_EvtsAllCuts   = wjets_EvtsAllCuts + ttbar_EvtsAllCuts 

qcd_EvtsJetSel  = qcd30to50[4][1] + qcd50to80[4][1] + qcd80to120[4][1] + qcd120to170[4][1] + qcd170to230[4][1] + qcd230to300[4][1]
qcd_EvtsAllCuts = qcd30to50[-1][1] + qcd50to80[-1][1] + qcd80to120[-1][1] + qcd120to170[-1][1] + qcd170to230[-1][1] + qcd230to300[-1][1]

######################################################################################
### Calculate Efficiencies
######################################################################################
### QCD combined: Using Standard Efficiency Definition
QCD_efficiency_estimate = XSectPassedQCD/XSectTotalQCD

### QCD combined: Using Bayes
qcdObj_eff = bayesDivide(qcd_EvtsAllCuts, qcd_EvtsJetSel)
QCD_efficiency_bayes = qcdObj_eff.GetY()[0]
QCD_eff_errUp = qcdObj_eff.GetEYhigh()[0]
QCD_eff_errDown = qcdObj_eff.GetEYlow()[0]

### TTbar: Using Bayes
ttbarObj_eff = bayesDivide(ttbar_EvtsAllCuts, ttbar_EvtsJetSel)
TTbar_efficiency_bayes = ttbarObj_eff.GetY()[0]
TTbar_eff_errUp = ttbarObj_eff.GetEYhigh()[0]
TTbar_eff_errDown = ttbarObj_eff.GetEYlow()[0]
### TTbar: Using Standard Efficiency Definition
TTbar_efficiency_estimate = XSectPassedTTbar/XSectTotalTTbar

### WJets: Using Bayes
wjetsObj_eff = bayesDivide(wjets_EvtsAllCuts, wjets_EvtsJetSel)
WJets_efficiency_bayes = wjetsObj_eff.GetY()[0]
WJets_eff_errUp = wjetsObj_eff.GetEYhigh()[0]
WJets_eff_errDown = wjetsObj_eff.GetEYlow()[0]
### WJets: Using Standard Efficiency Definition
WJets_efficiency_estimate = XSectPassedWJets/XSectTotalWJets

######################################################################################
### Calculate Purity of QCD
######################################################################################
### Using Bayes
qcdObj_pur = bayesDivide(qcd_EvtsAllCuts, ewk_EvtsAllCuts+qcd_EvtsAllCuts)
QCD_purity_bayes = qcdObj_pur.GetY()[0]
QCD_pur_errUp = qcdObj_pur.GetEYhigh()[0]
QCD_pur_errDown = qcdObj_pur.GetEYlow()[0]
### Using Standard Purity Definition
QCD_purity_estimate = (XSectPassedQCD/(XSectPassedEWK+XSectPassedQCD))*100
if bVerbosity == True:
    print "*** QCD_purity_estimate = ", QCD_purity_estimate,"%"
    print "*** QCD_purity_bayes = ", QCD_purity_bayes

######################################################################################
### Calculate Efficiency using the ROOT class "bayesDivide", for each QCD DataSet
######################################################################################
### Declare (double) arrays to be filled with efficiencies and purities
effArray         = array("d",[ ])
effArray_errDown =  array("d",[ ])
effArray_errUp   =  array("d",[ ])

### Open efficiencies file
EfficienciesFile = open(FileName_eff,"w")

### Calculate efficiencies and store them in arrays
effObj = bayesDivide(qcd30to50[-1][1], qcd30to50[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)
### Write to file
EfficienciesFile.write(str(eff) + " " + str(eff_errDown) + " " + str(eff_errUp) )
EfficienciesFile.write("\n")

effObj = bayesDivide(qcd50to80[-1][1], qcd50to80[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)
### Write to file
EfficienciesFile.write(str(eff) + " ")
EfficienciesFile.write(str(eff_errDown) + " ")
EfficienciesFile.write(str(eff_errUp) + " ")
EfficienciesFile.write("\n")

effObj = bayesDivide(qcd80to120[-1][1], qcd80to120[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)
### Write to file
EfficienciesFile.write(str(eff) + " ")
EfficienciesFile.write(str(eff_errDown) + " ")
EfficienciesFile.write(str(eff_errUp) + " ")
EfficienciesFile.write("\n")

effObj = bayesDivide(qcd120to170[-1][1], qcd120to170[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)
### Write to file
EfficienciesFile.write(str(eff) + " ")
EfficienciesFile.write(str(eff_errDown) + " ")
EfficienciesFile.write(str(eff_errUp) + " ")
EfficienciesFile.write("\n")

effObj = bayesDivide(qcd170to230[-1][1], qcd170to230[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)
### Write to file
EfficienciesFile.write(str(eff) + " ")
EfficienciesFile.write(str(eff_errDown) + " ")
EfficienciesFile.write(str(eff_errUp) + " ")
EfficienciesFile.write("\n")

effObj = bayesDivide(qcd230to300[-1][1], qcd230to300[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)
### Write to file
EfficienciesFile.write(str(eff) + " ")
EfficienciesFile.write(str(eff_errDown) + " ")
EfficienciesFile.write(str(eff_errUp) + " ")
EfficienciesFile.write("\n")

######################################################################################
### Print efficiency arrays (incl errors)
######################################################################################
if bVerbosity == True:
    print
    print "*****************"
    print "* Efficiencies: *"
    print "*****************"
    print "*** effArray = ", effArray
    print
    print "*** effArray_errDown = ", effArray_errDown
    print
    print "*** effArray_errUp = ", effArray_errUp
    print
    print "*** Efficiency (Bayes) = ", QCD_efficiency_bayes, " + ", QCD_eff_errUp, " - ", QCD_eff_errDown
    print "*** Efficiency (Estimate) = ", QCD_efficiency_estimate
    print
    print "***************"
    print "* QCD Purity: *"
    print "***************"
    print "*** Purity (Bayes) = ", QCD_purity_bayes
    print "*** Purity (Estimate) = ", QCD_purity_estimate, "%"
    print
    print "****************"
    print "* TTbar Sample *"
    print "****************"
    print "*** Efficiency (Bayes) = ", TTbar_efficiency_bayes, " + ", TTbar_eff_errUp, " - ", TTbar_eff_errDown
    print "*** Efficiency (Estimate) = ", TTbar_efficiency_estimate
    print
    print "****************"
    print "* WJets Sample *"
    print "****************"
    print "*** Efficiency (Bayes) = ", WJets_efficiency_bayes, " + ", WJets_eff_errUp, " - ", WJets_eff_errDown
    print "*** Efficiency (Estimate) = ", WJets_efficiency_estimate
    print "*****************************************************************************************************"

######################################################################################
### Efficiencies graph
######################################################################################
print "*** Creating TGraphAsymmErros"

### Create TCanvas and TGraph with Asymmetric Error Bars using Bayesian Statistical Tools
cEff = TCanvas ("QCDMeasurementByIsolation", "QCDMeasurementByIsolation", 1)
cEff.cd()

### Declare arrays with the QCD pT bins 
qcdBin  = array("d",[50, 80, 120, 170, 230, 300 ])
qcdBin_down = array("d",[0, 0, 0, 0, 0, 0 ])
qcdBin_up  = array("d",[0, 0, 0, 0, 0, 0 ])

### Create and customise TGraph 
graph = TGraphAsymmErrors(6, qcdBin, effArray, qcdBin_down,  qcdBin_up, effArray_errDown, effArray_errUp)
graph.Draw("AP")
graph.SetMarkerStyle(kFullCircle)
graph.SetMarkerColor(kRed)
graph.SetMarkerSize(1)
graph.GetYaxis().SetTitle("Efficiency (#epsilon)")
graph.GetXaxis().SetTitle("#hat{p}_{T} [GeV/c]")
### Re-draw graph and update canvas and gPad
graph.Draw("AP")
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 
cEff.Update()

######################################################################################
### Purity pseudo-experiments
######################################################################################
print "*** Creating Histograms"

### Set Options
xMin  = 0.0
xMax  = 1.0
nBins = 500
#
xMinB  = -0.5
xMaxB  = 1000000.5
nBinsB = 1000001
nPseudoExperiments = 10000;
confidenceLevel = 0.683;

### Create Histograms. Number of bins = 200, Max = 100, Min = -100
hBinomial_qcd30to50   =  TH1F("qcd30to50", "qcd30to50", nBinsB, xMinB, xMaxB)
hBinomial_qcd50to80   =  TH1F("qcd50to80", "qcd50to80", nBinsB, xMinB, xMaxB)
hBinomial_qcd80to120  =  TH1F("qcd80to120", "qcd80to120", nBinsB, xMinB, xMaxB)
hBinomial_qcd120to170 =  TH1F("qcd120to170", "qcd120to170", nBinsB, xMinB, xMaxB)
hBinomial_qcd170to230 =  TH1F("qcd170to230", "qcd170to230", nBinsB, xMinB, xMaxB)
hBinomial_qcd230to300 =  TH1F("qcd230to300", "qcd230to300", nBinsB, xMinB, xMaxB)
hBinomial_TTbar  =  TH1F("TTbar", "TTbar", nBinsB, xMinB, xMaxB)
hBinomial_WJets  =  TH1F("WJets", "Wjets", nBinsB, xMinB, xMaxB)
hQCDPurity       =  TH1F("QCDPurity", "QCDPurity", nBins, xMin, xMax)
hWJetsContrib    =  TH1F("WJetsContrib", "WJetsContrib", nBins, xMin, xMax)
   
### Define efficiencies and get values from the efficiency array
qcd30to50_eff   = effArray[0]
qcd50to80_eff   = effArray[1]
qcd80to120_eff  = effArray[2]
qcd120to170_eff = effArray[3]
qcd170to230_eff = effArray[4]
qcd230to300_eff = effArray[5]
ttbar_eff       = TTbar[-1][1]/TTbar[4][1]
wjets_eff       = WJets[-1][1]/WJets[4][1]

### Remember, the efficiency of the cut flow is the probability that the specific series of cuts will be survived by the dataset
qcd30to50_prob   = qcd30to50_eff
qcd50to80_prob   = qcd50to80_eff
qcd80to120_prob  = qcd80to120_eff
qcd120to170_prob = qcd120to170_eff
qcd170to230_prob = qcd170to230_eff
qcd230to300_prob = qcd230to300_eff
ttbar_prob       = ttbar_eff
wjets_prob       = wjets_eff

### Calculate total number of events for binomial distributions
qcd30to50_ntot   = int(qcd30to50_EvtsJetSel)
qcd50to80_ntot   = int(qcd50to80_EvtsJetSel)
qcd80to120_ntot  = int(qcd80to120_EvtsJetSel)
qcd120to170_ntot = int(qcd120to170_EvtsJetSel)
qcd170to230_ntot = int(qcd170to230_EvtsJetSel)
qcd230to300_ntot = int(qcd230to300_EvtsJetSel)
ttbar_ntot       = int(ttbar_EvtsJetSel)
wjets_ntot       = int(wjets_EvtsJetSel)

### For Normal (Gaussian distribution): mean = prob*ntot
qcd30to50_mean   = qcd30to50_prob*qcd30to50_ntot
qcd50to80_mean   = qcd50to80_prob*qcd50to80_ntot
qcd80to120_mean  = qcd80to120_prob*qcd80to120_ntot
qcd120to170_mean = qcd120to170_prob*qcd120to170_ntot
qcd170to230_mean = qcd170to230_prob*qcd170to230_ntot
qcd230to300_mean = qcd230to300_prob*qcd230to300_ntot
ttbar_mean       = ttbar_prob*ttbar_ntot
wjets_mean       = wjets_prob*wjets_ntot

### For Normal (Gaussian distribution): standard div  = sqrt(not*prob*(1-prob))
qcd30to50_standDiv   = sqrt(qcd30to50_ntot*qcd30to50_prob*(1-qcd30to50_prob))
qcd50to80_standDiv   = sqrt(qcd50to80_ntot*qcd50to80_prob*(1-qcd50to80_prob))
qcd80to120_standDiv  = sqrt(qcd80to120_ntot*qcd80to120_prob*(1-qcd80to120_prob))
qcd120to170_standDiv = sqrt(qcd120to170_ntot*qcd120to170_prob*(1-qcd120to170_prob))
qcd170to230_standDiv = sqrt(qcd170to230_ntot*qcd170to230_prob*(1-qcd170to230_prob))
qcd230to300_standDiv = sqrt(qcd230to300_ntot*qcd230to300_prob*(1-qcd230to300_prob))
ttbar_standDiv = sqrt(ttbar_ntot*ttbar_prob*(1-ttbar_prob))
wjets_standDiv = sqrt(wjets_ntot*wjets_prob*(1-wjets_prob))

print "*** Filling Histograms"
### Loop to fill the histograms using the random number generator "gRandom" 
### Note: gRandom->Binomial(Total Number of generated Events for sample, probability that a given event will pass the given cut flow)
### Estimate the number of events that will pass all cut-flow according to the binomial distribution with parameters:
### par1 = Total number of events before cuts, par2 = probability that they will pass selection (i.e. efficiency of cut)
### Using number of events at specific integrated luminosity (IntLumi)
for i in range(nPseudoExperiments):
    percent = float(i)/float(float(nPseudoExperiments)/100.0);
    if( percent%10 == 0):
        print " Progress: ", str(percent), "%"
### Generate distributions for all samples, given the efficiencies of the cut flow.
### Note1: Int_t Int_t Binomial(Int_t ntot, Double_t prob) generates a random integer N according to the binomial law.
###        N is binomially distributed between 0 and ntot inclusive with mean prob*ntot. prob is between 0 and 1.
###        This function should not be used when ntot is large (say >100). The normal approximation is then recommended instead
### Note2: gRandom uses TRandom3 Rndm generator as default (a GOOD Generator)
### Note3: Apply weigths after the distributions are generated, otherwise you artificially increase your statistics.
    if(qcd30to50_ntot > 100):
        qcd30to50_EvtsPseudoExp   = gRandom.Gaus( qcd30to50_mean, qcd30to50_standDiv)
    else:
        qcd30to50_EvtsPseudoExp   = gRandom.Binomial( qcd30to50_ntot, qcd30to50_prob)

    if(qcd50to80_ntot > 100):
        qcd50to80_EvtsPseudoExp   = gRandom.Gaus( qcd50to80_mean, qcd50to80_standDiv)
    else:
        qcd50to80_EvtsPseudoExp   = gRandom.Binomial( qcd50to80_ntot, qcd50to80_prob)

    if(qcd80to120_ntot > 100):    
        qcd80to120_EvtsPseudoExp  = gRandom.Gaus( qcd80to120_mean, qcd80to120_standDiv)
    else: 
        qcd80to120_EvtsPseudoExp  = gRandom.Binomial( qcd80to120_mean, qcd80to120_standDiv)

    if(qcd120to170_ntot > 100):   
        qcd120to170_EvtsPseudoExp = gRandom.Gaus( qcd120to170_mean, qcd120to170_standDiv)
    else:
        qcd120to170_EvtsPseudoExp = gRandom.Binomial( qcd120to170_ntot, qcd120to170_prob)
          
    if(qcd170to230_ntot > 100):   
        qcd170to230_EvtsPseudoExp = gRandom.Gaus( qcd170to230_mean, qcd170to230_standDiv)
    else:
        qcd170to230_EvtsPseudoExp = gRandom.Binomial( qcd170to230_ntot, qcd170to230_prob)   
    if(qcd230to300_ntot > 100):   
        qcd230to300_EvtsPseudoExp = gRandom.Gaus( qcd230to300_mean, qcd230to300_standDiv)
    else:
        qcd230to300_EvtsPseudoExp = gRandom.Binomial( qcd230to300_ntot, qcd230to300_prob)
        
    if( ttbar_ntot > 100):
        ttbar_EvtsPseudoExp       = gRandom.Gaus( ttbar_mean, ttbar_standDiv)
    else:
        ttbar_EvtsPseudoExp       = gRandom.Binomial( int(ttbar_ntot), ttbar_prob)
    if(wjets_ntot > 100):
        wjets_EvtsPseudoExp       = gRandom.Gaus( wjets_mean, wjets_standDiv)
    else:
        wjets_EvtsPseudoExp       = gRandom.Binomial( int(wjets_ntot), wjets_prob)

### Fill Histos with un-weighted numbers taken from the distributions
    hBinomial_qcd30to50.Fill(qcd30to50_EvtsPseudoExp)
    hBinomial_qcd50to80.Fill(qcd50to80_EvtsPseudoExp)
    hBinomial_qcd80to120.Fill(qcd80to120_EvtsPseudoExp)
    hBinomial_qcd120to170.Fill(qcd120to170_EvtsPseudoExp)
    hBinomial_qcd170to230.Fill(qcd170to230_EvtsPseudoExp)
    hBinomial_qcd230to300.Fill(qcd230to300_EvtsPseudoExp)
    hBinomial_TTbar.Fill(ttbar_EvtsPseudoExp)
    hBinomial_WJets.Fill(wjets_EvtsPseudoExp)

### Weight the event numbers of the distributions to calculate the purity
    qcd30to50_EvtsPseudoExp_weighted = qcd30to50_EvtsPseudoExp*IntLumi*qcd30to50_NormFactor
    qcd50to80_EvtsPseudoExp_weighted = qcd50to80_EvtsPseudoExp*IntLumi*qcd50to80_NormFactor
    qcd80to120_EvtsPseudoExp_weighted = qcd80to120_EvtsPseudoExp*IntLumi*qcd80to120_NormFactor
    qcd120to170_EvtsPseudoExp_weighted = qcd120to170_EvtsPseudoExp*IntLumi*qcd120to170_NormFactor
    qcd170to230_EvtsPseudoExp_weighted = qcd170to230_EvtsPseudoExp*IntLumi*qcd170to230_NormFactor
    qcd230to300_EvtsPseudoExp_weighted = qcd230to300_EvtsPseudoExp*IntLumi*qcd230to300_NormFactor
    ttbar_EvtsPseudoExp_weighted = ttbar_EvtsPseudoExp*IntLumi*TTbar_NormFactor
    wjets_EvtsPseudoExp_weighted = wjets_EvtsPseudoExp*IntLumi*WJets_NormFactor

    qcd_EvtsPseudoExp_weighted  = qcd30to50_EvtsPseudoExp_weighted  + qcd50to80_EvtsPseudoExp_weighted  + qcd80to120_EvtsPseudoExp_weighted  + qcd120to170_EvtsPseudoExp_weighted  + qcd170to230_EvtsPseudoExp_weighted  + qcd230to300_EvtsPseudoExp_weighted 
    QCD_Purity = float((float(qcd_EvtsPseudoExp_weighted ))/float((qcd_EvtsPseudoExp_weighted +ttbar_EvtsPseudoExp_weighted +wjets_EvtsPseudoExp_weighted )))
    wjets_Contribution = float(wjets_EvtsPseudoExp_weighted)/float(ttbar_EvtsPseudoExp_weighted+wjets_EvtsPseudoExp_weighted)
    ttbar_Contribution = float(ttbar_EvtsPseudoExp_weighted)/float(ttbar_EvtsPseudoExp_weighted+wjets_EvtsPseudoExp_weighted)

### Fill histos
    hQCDPurity.Fill(QCD_Purity)
    hWJetsContrib.Fill(wjets_Contribution)

######################################################################################
### Create canvases to draw distributions 
######################################################################################    
print "*** Creating Canvases"

cDistr =  TCanvas("distributions", "distributions", 1)
cQCDPurity =  TCanvas("QCD Purity", "QCD Purity", 1)
cWjetsContrib =  TCanvas("WJetsContrib", "WJetsContrib", 1)

### Divide the canvas into 8 parts
cDistr.Divide(2,4)

cDistr.cd(1)
hBinomial_qcd30to50.Draw()
hBinomial_qcd30to50.SetFillColor(kRed+1)
hBinomial_qcd30to50.GetXaxis().SetTitle( "Events" )
binMax = hBinomial_qcd30to50.GetMaximumBin()
### Automate the x-axis range
xMaxNonEmpty = hBinomial_qcd30to50.GetXaxis().GetBinCenter(binMax)
xMinNonEmpty = hBinomial_qcd30to50.GetXaxis().GetBinCenter(FindFirstBinAbove(hBinomial_qcd30to50, 0, 1))
binWidth = hBinomial_qcd30to50.GetBinWidth(1);
if( (xMinNonEmpty <= 0.5 ) & (xMaxNonEmpty <= 0.5)):
    hBinomial_qcd30to50.GetXaxis().SetRangeUser( 0, 10);
else:
    hBinomial_qcd30to50.GetXaxis().SetRangeUser( xMinNonEmpty-(binWidth*100) , xMaxNonEmpty+(binWidth*100))
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 

cDistr.cd(2)
hBinomial_qcd50to80.Draw()
hBinomial_qcd50to80.SetFillColor(kRed+2)
hBinomial_qcd50to80.GetXaxis().SetTitle( "Events" )
### Automate the x-axis range
binMax = hBinomial_qcd50to80.GetMaximumBin()
xMaxNonEmpty = hBinomial_qcd50to80.GetXaxis().GetBinCenter(binMax)
xMinNonEmpty = hBinomial_qcd50to80.GetXaxis().GetBinCenter(FindFirstBinAbove(hBinomial_qcd50to80, 0, 1))
if( (xMinNonEmpty <= 0.5 ) & (xMaxNonEmpty <= 0.5)):
    hBinomial_qcd50to80.GetXaxis().SetRangeUser( 0, 10)
else:
    hBinomial_qcd50to80.GetXaxis().SetRangeUser( xMinNonEmpty-(binWidth*100) , xMaxNonEmpty+(binWidth*100))
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 

cDistr.cd(3)
hBinomial_qcd80to120.Draw()
hBinomial_qcd80to120.SetFillColor(kRed+3)
hBinomial_qcd80to120.GetXaxis().SetTitle( "Events" )
### Automate the x-axis range
binMax = hBinomial_qcd80to120.GetMaximumBin()
xMaxNonEmpty = hBinomial_qcd80to120.GetXaxis().GetBinCenter(binMax)
xMinNonEmpty = hBinomial_qcd80to120.GetXaxis().GetBinCenter(FindFirstBinAbove(hBinomial_qcd80to120, 0, 1))
hBinomial_qcd80to120.GetXaxis().SetRangeUser( xMinNonEmpty-(binWidth*100) , xMaxNonEmpty+(binWidth*100))
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 

cDistr.cd(4)
hBinomial_qcd120to170.Draw()
hBinomial_qcd120to170.SetFillColor(kRed+4)
hBinomial_qcd120to170.GetXaxis().SetTitle( "Events" )
### Automate the x-axis range
binMax = hBinomial_qcd120to170.GetMaximumBin()
xMaxNonEmpty = hBinomial_qcd120to170.GetXaxis().GetBinCenter(binMax)
xMinNonEmpty = hBinomial_qcd120to170.GetXaxis().GetBinCenter(FindFirstBinAbove(hBinomial_qcd120to170, 0, 1))
hBinomial_qcd120to170.GetXaxis().SetRangeUser( xMinNonEmpty-(binWidth*100) , xMaxNonEmpty+(binWidth*100))
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 

cDistr.cd(5)
hBinomial_qcd170to230.Draw()
hBinomial_qcd170to230.SetFillColor(kRed-1)
hBinomial_qcd170to230.GetXaxis().SetTitle( "Events" )
### Automate the x-axis range
binMax = hBinomial_qcd170to230.GetMaximumBin()
xMaxNonEmpty = hBinomial_qcd170to230.GetXaxis().GetBinCenter(binMax)
xMinNonEmpty = hBinomial_qcd170to230.GetXaxis().GetBinCenter(FindFirstBinAbove(hBinomial_qcd170to230, 0, 1))
hBinomial_qcd170to230.GetXaxis().SetRangeUser( xMinNonEmpty-(binWidth*100) , xMaxNonEmpty+(binWidth*100))
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 

cDistr.cd(6)
hBinomial_qcd230to300.Draw()
hBinomial_qcd230to300.SetFillColor(kRed-2)
hBinomial_qcd230to300.GetXaxis().SetTitle( "Events" )
### Automate the x-axis range
binMax = hBinomial_qcd230to300.GetMaximumBin()
xMaxNonEmpty = hBinomial_qcd230to300.GetXaxis().GetBinCenter(binMax)
xMinNonEmpty = hBinomial_qcd230to300.GetXaxis().GetBinCenter(FindFirstBinAbove(hBinomial_qcd230to300, 0, 1))
hBinomial_qcd230to300.GetXaxis().SetRangeUser( xMinNonEmpty-(binWidth*100) , xMaxNonEmpty+(binWidth*100)) 
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 

cDistr.cd(7)
hBinomial_TTbar.Draw()
hBinomial_TTbar.SetFillColor(kBlack)
hBinomial_TTbar.GetXaxis().SetTitle( "Events" )
### Automate the x-axis range
binMax = hBinomial_TTbar.GetMaximumBin()
xMaxNonEmpty = hBinomial_TTbar.GetXaxis().GetBinCenter(binMax)
xMinNonEmpty = hBinomial_TTbar.GetXaxis().GetBinCenter(FindFirstBinAbove(hBinomial_TTbar, 0, 1))
hBinomial_TTbar.GetXaxis().SetRangeUser( xMinNonEmpty-(binWidth*100) , xMaxNonEmpty+(binWidth*100))
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 

cDistr.cd(8)
hBinomial_WJets.Draw()
hBinomial_WJets.SetFillColor(kBlue)
hBinomial_WJets.GetXaxis().SetTitle( "Events" )
### Automate the x-axis range
binMax = hBinomial_WJets.GetMaximumBin()
xMaxNonEmpty = hBinomial_WJets.GetXaxis().GetBinCenter(binMax)
xMinNonEmpty = hBinomial_WJets.GetXaxis().GetBinCenter(FindFirstBinAbove(hBinomial_WJets, 0, 1))
hBinomial_WJets.GetXaxis().SetRangeUser( xMinNonEmpty-(binWidth*100) , xMaxNonEmpty+(binWidth*100))
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 

######################################################################################
### Determine the asymmetric error of the QCD purity distribution
### This is done by minimising the x-axis interval of the QCD purity distribution
### that contains an area greater or equal to the defined confidence level.
### The confidence is by default set the the area enclosed by 1 standard deviation of
### a gaussian function. Once the x-axis interval is determined the asymmetric errors are found
### by evaluating the distance of the two points from the mean value.
######################################################################################
binWidth = hQCDPurity.GetBinWidth(1);  
TotalIntegral = hQCDPurity.Integral( hQCDPurity.FindBin(0.0), hQCDPurity.FindBin(1.0) );
### Define lists to be used for calculating the asymmetric errors
intervals = []
lowBin   = []
upBin    = []

### Determine lowest bin where an entry is found (to minimise the loop iterations)
lowLimitBin = -1
upLimitBin  = -1
for i in range(0,hQCDPurity.GetNbinsX()+1):
    if (hQCDPurity.GetBinContent(i) > 0.0 ):
        lowLimitBin = i
        break

### Determine max bin where an entry is found (to minimise the loop iterations). Reverse (decrement) loop
for j in range(hQCDPurity.GetNbinsX()+1, 0, -1):
    if (hQCDPurity.GetBinContent(j) > 0.0 ):
        upLimitBin = j
        break
### Perform a double loop to determine all the intervals that contain an area which is at least equal to the confidenceLevel
for i in range ( lowLimitBin, hQCDPurity.GetNbinsX()+1, +1 ):
### Second loop index set to first loop index to avoid double (or reverse) calculations
    for j in range ( i, upLimitBin+1, +1 ):
        tmpIntegral = hQCDPurity.Integral(i, j, "")
        #print "tmpIntegral = ", tmpIntegral
        tmpIntegralFraction = tmpIntegral/TotalIntegral
        if(tmpIntegralFraction >= confidenceLevel):
            a = i
            b = j
            interval = b-a
            #print "*** interval = " "b - a = ", b, " - ", a, " = ", interval 
      ### Save all the intervals that contain the area >= confidence level. We will find the minimum later on.
            intervals.append(interval)
            lowBin.append(a)
            upBin.append(b)
            break

### Definition of variables
myMin = 9999999;
k = 0;
index = 0;
QCD_Purity_mean = hQCDPurity.GetMean()

### Loop over stored intervals to find the minimum interval containing an area >= to the confidenceLevel chosen.
for s in range( len(intervals) ):
### Determine the minimum by comparing all values. Store the vector index.
    if( intervals[s] < myMin):
        myMin = intervals[s]
        index = s

### Determine lowError (less than mean) and highError (greater than mean)
result   = QCD_Purity_mean*100
lowError = fabs(QCD_Purity_mean-(lowBin[index]*binWidth))*100
upError  = fabs(QCD_Purity_mean-(upBin[index]*binWidth))*100

######################################################################################
### Wjets Contribution Plot
######################################################################################
cWjetsContrib.cd()
hWJetsContrib.Draw()
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96) 
hWJetsContrib.SetFillColor(kBlue)
hWJetsContrib.GetXaxis().SetTitle( "WJets Contribution" )
hWJetsContrib.GetYaxis().SetTitle( "Pseudo-Experiments" )
hWJetsContrib.GetXaxis().SetRangeUser( 0.0, 1.0)
WJetsContrib = hWJetsContrib.GetMean()*100
TTbarContrib = 100-WJetsContrib

######################################################################################
### QCD Purity plot
######################################################################################

### Create text information to be printed on the QCD Purity histogram
myYCoordinate = hQCDPurity.GetMaximum()
myXCoordinate = (xMax-xMin)*(0.44)

myText1  = "Purity_{p-e} = " + str(format(result, ('.2f'))) + "^{+" + str(format(upError, ('.1f'))) + "}_{-" + str(format(lowError, ('.1f'))) + "}%"
text1 = TLatex(myXCoordinate, myYCoordinate*(1-0.1), myText1)

myText2  = "Purity_{est} = " + str(format(QCD_purity_estimate, ('.2f'))) + "%"
text2 = TLatex(myXCoordinate, myYCoordinate*(1-0.2), myText2)

myText3  = "TTbar is " + str(format(TTbarContrib, ('.1f'))) + "% of EWK"
text3 = TLatex(myXCoordinate, myYCoordinate*(1-0.3), myText3)

myText4  = "WJets is " + str(format(WJetsContrib, ('.1f'))) + "% of EWK"
text4 = TLatex(myXCoordinate, myYCoordinate*(1-0.4), myText4)

cQCDPurity.cd()
hQCDPurity.Draw()
hQCDPurity.SetFillColor(kOrange)
hQCDPurity.GetXaxis().SetTitle( "QCD purity" )
hQCDPurity.GetYaxis().SetTitle( "Pseudo-Experiments" )
hQCDPurity.GetXaxis().SetRangeUser( 0.4, 1.0)
addCmsPreliminaryText(0.72, 0.96)
addEnergyText(0.16, 0.96)
text1.Draw()
text2.Draw()
text3.Draw()
text4.Draw()
#ptstats1 = hQCDPurity.FindObject("stats");
#ptstats1.SetX1NDC(0.8)
#ptstats1.SetX2NDC(0.9) 
#ptstats1.SetY1NDC(0.8)
#ptstats1.SetY2NDC(0.9)
#cQCDPurity.Update()

######################################################################################
### Save information to a ".dat" file
######################################################################################
### Open file in "append" mode and write to it
PuritiesFile = open(FileName_pur,"w")
if bSaveFiles:
    PuritiesFile.write(str(result) + " " + str(lowError) + " " + str(upError))
    PuritiesFile.write("\n")
    PuritiesFile.close()
    EfficienciesFile.close()

######################################################################################
### Save canvases to destination
######################################################################################
if bSaveCanvases:
    cEff.SaveAs(CanvasSavePath+"cEf.png")
    cEff.SaveAs(CanvasSavePath+"cEf.C")
    cEff.SaveAs(CanvasSavePath+"cEf.eps")
    cEff.SaveAs(CanvasSavePath+"cEf.pdf")

    cDistr.SaveAs(CanvasSavePath+"cDistr.png")
    cDistr.SaveAs(CanvasSavePath+"cDistr.C")
    cDistr.SaveAs(CanvasSavePath+"cDistr.eps")
    cDistr.SaveAs(CanvasSavePath+"cDistr.pdf")

    cQCDPurity.SaveAs(CanvasSavePath+"cQCDPurity.png")
    cQCDPurity.SaveAs(CanvasSavePath+"cQCDPurity.C")
    cQCDPurity.SaveAs(CanvasSavePath+"cQCDPurity.eps")
    cQCDPurity.SaveAs(CanvasSavePath+"cQCDPurity.pdf")

    cWjetsContrib.SaveAs(CanvasSavePath+"cWJetsContrib.png")
    cWjetsContrib.SaveAs(CanvasSavePath+"cWJetsContrib.C")
    cWjetsContrib.SaveAs(CanvasSavePath+"cWJetsContrib.eps")
    cWjetsContrib.SaveAs(CanvasSavePath+"cWJetsContrib.pdf")

######################################################################################
raw_input('*** Done! Press \"Enter\" to exit to terminal ...')
######################################################################################
