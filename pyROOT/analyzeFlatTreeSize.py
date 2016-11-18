#!/usr/bin/env python
# http://wlav.web.cern.ch/wlav/pyroot/
###############################################################
### All imported modules
###############################################################
import ROOT
import os
import sys
import numpy
import math

###############################################################
### Options here
###############################################################
filePath    = "~/Desktop/"
inFileName  = "miniAOD2FlatTree.root"
outFileName = "treeInfo.log"
treeName    = "Events"

def GetObjectByName(fileIn, objectName):
    '''
    '''

    # For-loop: Over all keys in file
    for key in fileIn.GetListOfKeys():    

        # Skip if object name is wrong
        keyName = key.GetName()
        if (keyName!= treeName):
            continue
        else:
            o = fileIn.Get(keyName)
            return o
    raise Exception("Could not find object with name '%s' in input ROOT file with name '%s'." % ( objectName, fileIn.GetName() ) )


def OpenTFile(filePath, fileName, mode):
    '''
    '''
    return ROOT.TFile.Open( filePath + fileName, mode, fileName, 1, 0)
            

def CreateFile(filePath, fileName, fileMode, titleLines, ):
    '''
    '''
    if (filePath.endswith("/") == False):
        filePath = filePath + "/"

    # Create the file
    f = open(filePath + fileName , fileMode)

    # Write the title lines (if any)
    for l in titleLines:
        f.write(l)

    return f



###############################################################
if __name__ == "__main__":


    # Open ROOT file
    fileIn = OpenTFile(filePath, inFileName, "READ")

    # Get the TTree    
    treeIn = GetObjectByName(fileIn, treeName) #treeIn = fileIn.Get(treeName)
    
    # For-loop: All TBranches in the TTree
    treeBranches   = treeIn.GetListOfBranches()
    bName_to_bSize = {}
    bNames         = []
    bSizes         = []
    totalSize_MB   = 0;
    basketSize_MB  = 0;

    # For-loop: All TTree branches
    for b in treeBranches:
        bName = b.GetName()
        bSize = b.GetTotalSize()
        bNames.append(bName)
        bSizes.append(bSize)
        totalSize_MB  += b.GetTotalSize() * 1e-06
        basketSize_MB += b.GetBasketSize() * 1e-06
        bName_to_bSize[bName] = bSize
        
    # Sort the two lists according to the bSizes list (descding order)
    from operator import itemgetter
    bSizes, bNames = [list(x) for x in zip(*sorted(zip(bSizes, bNames), key=itemgetter(0), reverse=True))]

    # Create a txt file
    title     = []
    hLine     = '='*75
    titleLine = '\n{:<55}  {:>10}  {:<5}'.format("TBranch", "Size", "Units\n")
    title.append(hLine)
    title.append(titleLine)
    title.append(hLine)
    fileOut = CreateFile(os.getcwd(), "treeSize.txt", "w", title)

    # For-loop: All dictionary keys/values
    for bName, bSize in zip(bNames, bSizes):
        bSize = bName_to_bSize[bName]
        
        # Convert to kilo-bytes before saving and Keep only two decimals
        bSize   = '%0.2f' % (bSize * 1.0e-03)
        newLine = '\n{:<55}  {:>10}  {:<5}'.format(bName, bSize, "kB")

        # Write line to file
        fileOut.write(newLine)


    # Write final lines
    lastLine   = '\n{:<55}  {:>10}  {:<5}'.format("Total (Total) Size"  , totalSize_MB , "MB (uncompressed file size)")
    lastLine_2 = '\n{:<55}  {:>10}  {:<5}'.format("Total (Basket) Size ", basketSize_MB, "MB (compressed file size)  ")
    fileOut.write(lastLine)
    fileOut.write(lastLine_2)
    fileOut.write("\n" + hLine)
    
    # Close file
    fileOut.close()

    
