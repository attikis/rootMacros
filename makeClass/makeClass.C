//################################################################################
// -*- ROOT macro-*-                                                             #
//                                                                               #
// Original Author:  Alexandros Attikis                                          #
//         Created:  1 Aug 2010                                                  #
//       Institute:  UCY                                                         #
//     Description:  This macro when executed will create two files:             #
//                   a "bareROOTmacro.h" and a "bareROOTmacro.C" files           #
//                   which will enable one to manipulate the data/variables      #
//                   stored on a given Ntuple using C++/ROOT.                    #
//    Instructions:  1) Launch root, 2) Execute macro.                           #
//                   |user> root -l                                              #
//                   root [0].x makeClass.C                                      #
//                   Normally, the main part of the code should be placed in the #
//                   "bareROOTmacro.C" file, within the bareROOTmacro::Loop()    #
//                   function.Once this is done edit and execute the macro       #
//                   "runBareROOTmacro.C".                                       #
//       Important:  Make sure you :                                             #
//                   1) Comment out EVERY instance of "EventAuxiliary"           #
//                   2) #include <iostream>                                      #
//                   3) #include <vector>                                        #
//                   in the "bareROOTmacro.h" file, otherwise won't compile!     #
//         e-mail :  attikis@cern.ch                                             #
//################################################################################
{
  // Choose ROOT file for which a Class will be created
  Char_t *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/";
  Char_t *FileName = "HPlusOut_M80.root";
  TFile  *myFile   = new TFile(TString(ReadPath) +  TString(FileName) );
  // Choose choice of Tree
  TTree *myTree = (TTree *)myFile->Get("Events"); 
  myTree->Print(); //optional
  // Execute command to create the class
  myTree->MakeClass("bareROOTmacro");
}

