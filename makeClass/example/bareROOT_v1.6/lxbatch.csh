#!/bin/tcsh
echo "################################### START OF FILE ###################################"
echo "\myTerm> echo $SHELL"
#echo $SHELL
#### Create shortcut for current working directory (tcsh script)
set curdir=`pwd`  
echo "\myTerm> $curdir"
#echo $curdir
### OR, if using SHELL script:
# curdir=`pwd`
# echo $curdir
###

###########################
### Set some variables: ###
###########################
echo ""
echo "------ Set some variables ------"
echo ""
### Input
set tmpDirName=alphaT
set macroName=runLXBATCH
### Output
set logFile=${macroName}.log
set castorPath=/castor/cern.ch/user/a/attikis/testing/
set lxplusPath=/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/alpha/bareROOT/
### Set DataSet to be used (test , hplus80 , hplus140 , hplus160 , qcd30 , qcd80 , qcd170 , qcd300 , ttbar , ttbar-jets)
#set DataSetName=HPlus_M80
#set DataSetName=HPlus_M140
#set DataSetName=HPlus_M160
#set DataSetName=QCD_Pt30
#set DataSetName=QCD_Pt80
#set DataSetName=QCD_Pt170
#set DataSetName=QCD_Pt300
#set DataSetName=TTbar
set DataSetName=TTbarJets
##set DataSetName=test

###########################
### Executing job steps ###
###########################
echo ""
echo "------ Executing job steps ------"
echo ""
### Create a working directory
echo "\myTerm> mkdir $tmpDirName"
mkdir $tmpDirName
### Get to the source directory on my local area
echo "\myTerm> cd $lxplusPath"
cd $lxplusPath
echo "ls"
ls
echo "\myTerm> cp *.* ${curdir}/${tmpDirName}/."
cp *.* ${curdir}/${tmpDirName}/.
### Go back to home directory on LXBATCH
echo "\myTerm> cd ${curdir}/${tmpDirName}"
cd ${curdir}/${tmpDirName}
echo "\myTerm> pwd"
pwd
echo "\myTerm> ls"
ls
echo ""
###########################################################################
### Instructions                                                        ###
### Suppose a macro myscript.C with a function myscript(int i, float x) ###
### you can execute this macro in batch, with eg:                       ###
### \myTerm> root -b -q "myscript.C(5,3.14)"                            ###
### If one of the arguments is a string, you must use the following way ###
###  \"a string\"                                                       ###
### R. Brun, ROOT Forum                                                 ###
###########################################################################
echo "\myTerm> root -l -b -q runLXBATCH.C($DataSetName) \"
root -l -b -q "runLXBATCH.C("\"$DataSetName") "
echo ""
echo "\myTerm> ls"
ls

##############################################
### Copy output files to CASTOR and LXPLUS ###
##############################################
echo ""
echo "------ Copying output files to CASTOR and LXPLUS ------"
echo ""
### CASTOR
echo "\myTerm> rfcp $DataSetName.root $castorPath"
rfcp $DataSetName.root $castorPath
### LXPLUS
echo "\myTerm> cp $DataSetName.root $lxplusPath"
cp $DataSetName.root $lxplusPath

#####################
### Clean up work ###
#####################
echo ""
echo "------ Cleaning up the working directory ------"
echo ""
cd $curdir
rm -rf $tmpDirName
echo "--> Current Working Directory is:"
pwd
echo "--> Listing files in Current Directory"
ls
echo "################################### END OF FILE ###################################"

