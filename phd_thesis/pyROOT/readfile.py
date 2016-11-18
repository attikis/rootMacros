#!/usr/bin env python
### to execute: |myLinux> python readfile.py testFile.dat

### System imports
import os, sys
from array import array
### ROOT imports
from ROOT import *
### HiggsAnalysis imports
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.dataset import *
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.histograms import *
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.tdrstyle import *
import HiggsAnalysis.HeavyChHiggsToTauNu.tools.styles as styles
### User imports
from bayes import * 
from myArrays import *

### Provide the name of the file to be opened 
if len(sys.argv) > 1:
    file = sys.argv[1]
### Otherwise ose as default the name file.dat
else:
    file = 'file.dat'

### If the file already exists remove it since the script will automatically generate one.
#if os.path.exists(file):
#    os.system('rm %s'%(file))
#os.system('hplusPrintCounters3.py --mode xsect --mainCounterOnly > %s ; echo "EOF" >> %s'%(file,file))

######################################################################################
### Options
verbosity = false ### false to suppress most "print" commands


######################################################################################
### Open file for processing
file = open('%s'%(file), 'r')

### Define lists to be used
DataSetName = []
CutNamesAndValues = []
DataSetAndXSectAndNormFact = []

######################################################################################
### Loop over lines and save the cut-flow info (Cross Section for MC, Events for data)
lim = True
while file:
    line = file.readline()
    # split the line and puts elements in list s as strings
    s = line.split()
    if 'EOF' in s:
        break
    n = len(s)
    # 10 is the number of columns
    ### Investigate lists which have three elements (i.e. 3 is the number of columns of each list)
    if n == 3:
            ### Save the names of the datasets, cross section and normalisation factor
            DataSetAndXSectAndNormFact.append([s[0], s[1], s[2]])
    if n == 10:
        if lim == True:
            for i in range(n):
                DataSetName.append(s[i])
            lim = False
        else:
            #print "CutNamesAndValues\tCut\tValue" 
            for i in range(1,n):
                CutNamesAndValues.append([DataSetName[i],s[0],float(s[i])])
                #print "%s\t%s\t%.0f"%(DataSetName[i],s[0],float(s[i]))

### Print the DataSet Name, Cross Section and MC Normalisation Factor (ib this order)
#print "DataSetAndXSectAndNormFact", DataSetAndXSectAndNormFact
#print "DataSetAndXSectAndNormFact[0][0] = ", DataSetAndXSectAndNormFact[0][0]
#print "DataSetAndXSectAndNormFact[0][1] = ", DataSetAndXSectAndNormFact[0][1]
#print "DataSetAndXSectAndNormFact[0][2] = ", DataSetAndXSectAndNormFact[0][2]

### Define lists that will hold the information (Cut Name and Xsection/Events surviving Cut)
WJets        = []
qcd30to50    = []
qcd50to80    = []
qcd80to120   = []
qcd120to170  = []
qcd170to230  = []
qcd230to300  = []
TTbarJets    = []
TTbar        = []
# hplus90  = []
# hplus100 = []
# hplus120 = []
# hplus140 = []
# hplus160 = []
######################################################################################
### Loop over all cut names and create new lists according to the DataSet Name
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
    if name == 'TTbarJets':
        TTbarJets.append(tmp)
    if name == 'TTbar':
        TTbar.append(tmp)
######################################################################################
### Print lists 
if verbosity == True:
    print
    print "***************************************************"
    print "* Printing cut-flow for each CutNamesAndValuesset *"
    print "***************************************************"
    print 'qcd30to50'
    print qcd30to50
    print
    print 'qcd50to80'
    print qcd50to80
    print
    print 'qcd80to120'
    print qcd80to120
    print
    print 'qcd120to170'
    print qcd120to170
    print
    print 'qcd170to230'
    print qcd170to230
    print
    print 'qcd230to300'
    print qcd230to300
    print
    print 'TTbarJets'
    print TTbarJets
    print
    print 'TTbar'
    print TTbar
    print
    print 'W+Jets'
    print WJets
    print "***************************************************************************************************************"
######################################################################################
### Calculate contamination from EWK
XSectTotalEWK  = TTbar[4][1]+WJets[4][1]
XSectPassedEWK = TTbar[-1][1]+WJets[-1][1]

### Calculations for combined QCD 
XSectTotalQCD  = qcd30to50[4][1]+qcd50to80[4][1]+qcd80to120[4][1]+qcd120to170[4][1]+qcd170to230[4][1]+qcd230to300[4][1]
XSectPassedQCD = qcd30to50[-1][1]+qcd50to80[-1][1]+qcd80to120[-1][1]+qcd120to170[-1][1]+qcd170to230[-1][1]+qcd230to300[-1][1]

### Calculate total QCD purity
QCD_purity = XSectPassedQCD/(XSectPassedEWK+XSectPassedQCD)
QCD_efficiency = XSectPassedQCD/XSectTotalQCD


### Declare (double) arrays to be filled with efficiencies and purities
effArray = array("d",[ ])
purArray = array("d",[ ])
#
purArray_errDown = effArray = array("d",[ ])
purArray_errUp   = effArray = array("d",[ ])
#
effArray_errDown = effArray = array("d",[ ])
effArray_errUp   = effArray = array("d",[ ])
######################################################################################
### Calculate Efficiency using the ROOT class "bayesDivide", for each QCD DataSet
if verbosity == True:
    print
    print "****************************"
    print "* Calculating Efficiencies *"
    print "****************************"
    print "..."
    print "***************************************************************************************************************"

effObj = bayesDivide(qcd30to50[-1][1], qcd30to50[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
### If zero events survive the cut-flow try to get an upper limit for efficiency as: eff = 1 Evt/Total Evts (for xSection 1 Evt = Norm Factor)
if eff == 0:
    eff = float(DataSetAndXSectAndNormFact[1][2])/qcd30to50[4][1]
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[1][0]", DataSetAndXSectAndNormFact[1][0], " eff = ", eff
    effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)

effObj = bayesDivide(qcd50to80[-1][1], qcd50to80[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
### If zero events survive the cut-flow try to get an upper limit for efficiency as: eff = 1 Evt/Total Evts (for xSection 1 Evt = Norm Factor)
if eff == 0:
    eff = float(DataSetAndXSectAndNormFact[2][2])/qcd30to50[4][1]
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[2][0]", DataSetAndXSectAndNormFact[2][0], " eff = ", eff
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)

effObj = bayesDivide(qcd80to120[-1][1], qcd80to120[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
### If zero events survive the cut-flow try to get an upper limit for efficiency as: eff = 1 Evt/Total Evts (for xSection 1 Evt = Norm Factor)
if eff == 0:
    eff = float(DataSetAndXSectAndNormFact[3][2])/qcd30to50[4][1]
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[3][0]", DataSetAndXSectAndNormFact[3][0], " eff = ", eff
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)

effObj = bayesDivide(qcd120to170[-1][1], qcd120to170[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
### If zero events survive the cut-flow try to get an upper limit for efficiency as: eff = 1 Evt/Total Evts (for xSection 1 Evt = Norm Factor)
if eff == 0:
    eff = float(DataSetAndXSectAndNormFact[4][2])/qcd30to50[4][1]
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[4][0]", DataSetAndXSectAndNormFact[4][0], " eff = ", eff
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)

effObj = bayesDivide(qcd170to230[-1][1], qcd170to230[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
### If zero events survive the cut-flow try to get an upper limit for efficiency as: eff = 1 Evt/Total Evts (for xSection 1 Evt = Norm Factor)
if eff == 0:
    eff = float(DataSetAndXSectAndNormFact[5][2])/qcd30to50[4][1]
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[5][0]", DataSetAndXSectAndNormFact[5][0], " eff = ", eff
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)

effObj = bayesDivide(qcd230to300[-1][1], qcd230to300[4][1])
eff = effObj.GetY()[0]
eff_errUp = effObj.GetEYhigh()[0]
eff_errDown = effObj.GetEYlow()[0]
### If zero events survive the cut-flow try to get an upper limit for efficiency as: eff = 1 Evt/Total Evts (for xSection 1 Evt = Norm Factor)
if eff == 0:
    eff = float(DataSetAndXSectAndNormFact[6][2])/qcd30to50[4][1]
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[6][0]", DataSetAndXSectAndNormFact[6][0], " eff = ", eff
effArray.append(eff)
effArray_errDown.append(eff_errDown)
effArray_errUp.append(eff_errUp)
######################################################################################
### Calculate Purity
if verbosity == True:
    print
    print "************************"
    print "* Calculating Purities *"
    print "************************"
    print "..."
    print "***************************************************************************************************************"

purObj = bayesDivide(qcd30to50[-1][1], qcd30to50[4][1]+XSectPassedEWK)
pur = purObj.GetY()[0]
pur_errUp = purObj.GetEYhigh()[0]
pur_errDown = purObj.GetEYlow()[0]
if pur == 0:
    pur = float(DataSetAndXSectAndNormFact[1][2])/(qcd30to50[4][1]+XSectPassedEWK)
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[1][0]", DataSetAndXSectAndNormFact[1][0], " pur = ", pur
purArray.append(pur)
purArray_errDown.append(pur_errDown)
purArray_errUp.append(pur_errUp)

purObj = bayesDivide(qcd50to80[-1][1], qcd50to80[4][1]+XSectPassedEWK)
pur = purObj.GetY()[0]
pur_errUp = purObj.GetEYhigh()[0]
pur_errDown = purObj.GetEYlow()[0]
if pur == 0:
    pur = float(DataSetAndXSectAndNormFact[2][2])/(qcd30to50[4][1]+XSectPassedEWK)
    if verbosity == True:
       print "DataSetAndXSectAndNormFact[2][0]", DataSetAndXSectAndNormFact[2][0], " pur = ", pur
purArray.append(pur)
purArray_errDown.append(pur_errDown)
purArray_errUp.append(pur_errUp)

purObj = bayesDivide(qcd80to120[-1][1], qcd80to120[4][1]+XSectPassedEWK)
pur = purObj.GetY()[0]
pur_errUp = purObj.GetEYhigh()[0]
pur_errDown = purObj.GetEYlow()[0]
if pur == 0:
    pur = float(DataSetAndXSectAndNormFact[3][2])/(qcd30to50[4][1]+XSectPassedEWK)
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[3][0]", DataSetAndXSectAndNormFact[3][0], " pur = ", pur
purArray.append(pur)
purArray_errDown.append(pur_errDown)
purArray_errUp.append(pur_errUp)

purObj = bayesDivide(qcd120to170[-1][1], qcd120to170[4][1]+XSectPassedEWK)
pur = purObj.GetY()[0]
pur_errUp = purObj.GetEYhigh()[0]
pur_errDown = purObj.GetEYlow()[0]
if pur == 0:
    pur = float(DataSetAndXSectAndNormFact[4][2])/(qcd30to50[4][1]+XSectPassedEWK)
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[4][0]", DataSetAndXSectAndNormFact[4][0], " pur = ", pur
purArray.append(pur)
purArray_errDown.append(pur_errDown)
purArray_errUp.append(pur_errUp)

purObj = bayesDivide(qcd170to230[-1][1], qcd170to230[4][1]+XSectPassedEWK)
pur = purObj.GetY()[0]
pur_errUp = purObj.GetEYhigh()[0]
pur_errDown = purObj.GetEYlow()[0]
if pur == 0:
    pur = float(DataSetAndXSectAndNormFact[5][2])/(qcd30to50[4][1]+XSectPassedEWK)
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[5][0]", DataSetAndXSectAndNormFact[5][0], " pur = ", pur
purArray.append(pur)
purArray_errDown.append(pur_errDown)
purArray_errUp.append(pur_errUp)

purObj = bayesDivide(qcd230to300[-1][1], qcd230to300[4][1]+XSectPassedEWK)
pur = purObj.GetY()[0]
pur_errUp = purObj.GetEYhigh()[0]
pur_errDown = purObj.GetEYlow()[0]
if pur == 0:
    pur = float(DataSetAndXSectAndNormFact[6][2])/(qcd30to50[4][1]+XSectPassedEWK)
    if verbosity == True:
        print "DataSetAndXSectAndNormFact[6][0]", DataSetAndXSectAndNormFact[6][0], " pur = ", pur
purArray.append(pur)
purArray_errDown.append(pur_errDown)
purArray_errUp.append(pur_errUp)

# ### Remove/Fix the entries below
# purArray.append(QCD_purity)
# purArray_errDown.append(0.01)
# purArray_errUp.append(0.01)
# effArray.append(QCD_efficiency)
# effArray_errDown.append(0.0001)
# effArray_errUp.append(0.01)
######################################################################################
if verbosity == True:
    print
    print "**************"
    print "* Efficiency *"
    print "**************"
    print "effArray = ", effArray
    print
    print "effArray_errDown = ", effArray_errDown
    print
    print "effArray_errUp = ", effArray_errUp
    print
    print "**********"
    print "* Purity *"
    print "**********"
    print "purArray = ", purArray
    print
    print "purArray_errDown = ", purArray_errDown
    print
    print "purArray_errUp = ", purArray_errDown
###
print
print "--> Info: Total Purity of QCD Sample = ", QCD_purity
print
######################################################################################
### Customise ROOT
gROOT.Reset()
ROOT.gROOT.SetBatch(False)
style = TDRStyle()
style.setPalettePretty()
style.setWide(True)

purArray_alt = array("d",[ ])
purArray_errDown_alt = array("d",[ ])
purArray_errUp_alt   = array("d",[ ])

purObj_alt = bayesDivide(XSectPassedQCD, XSectPassedQCD+XSectPassedEWK)
pur_alt = purObj_alt.GetY()[0]
pur_errUp_alt = purObj_alt.GetEYhigh()[0]
pur_errDown_alt = purObj_alt.GetEYlow()[0]
for i in range(0,6):
    #print i
    purArray_alt.append(pur_alt)
    purArray_errDown_alt.append(pur_errDown)
    purArray_errUp_alt.append(pur_errUp)
# purArray_alt = array("d",[QCD_purity,QCD_purity,QCD_purity,QCD_purity,QCD_purity,QCD_purity ])


### Draw TGraph with Asymmetric Error Bars using Bayesian Statistical Tools
# graph = TGraphAsymmErrors(6, purArray, effArray, purArray_errDown,  purArray_errUp, effArray_errDown, effArray_errUp) ### works
graph = TGraphAsymmErrors(6, purArray_alt, effArray, purArray_errDown_alt,  purArray_errUp_alt, effArray_errDown, effArray_errUp) ### works
graph.Draw("AP")
graph.SetMarkerStyle(kFullCircle)
graph.SetMarkerColor(2)
#graph.GetXaxis().SetRangeUser( 0.0 , 1.0) #???
#graph.GetYaxis().SetRangeUser( 0.0 , 1.0) #???
graph.SetTitle( "#epsilon Vs QCD purities (EWK)" )
graph.GetYaxis().SetTitle("Efficiency (#epsilon) of selection")
graph.GetXaxis().SetTitle("Purity of QCD Sample")
### Customise gPad
gPad.SetLogy(1)
gPad.Update()

# ### Test Histogram with efficiencies only
# hEff=TH1F('efficiencies', '#epsilon', 1000, 0.0, 0.002)
# hEff.Fill(effArray[0])
# hEff.Fill(effArray[1])
# hEff.Fill(effArray[2])
# hEff.Fill(effArray[3])
# hEff.Fill(effArray[4])
# hEff.Fill(effArray[5])
# hEff.Draw()

################
print
raw_input('Press \"Enter\" to exit to terminal ...')
