{
#include "TChain.h"
  gROOT->Reset();
  gROOT->LoadMacro("alpha_T.C");
  //gSystem->CompileMacro("alpha_T.C");
  TChain myChain("Events");

  // myChain->Add("/afs/cern.ch/user/a/attikis/scratch0/AnalysisPack/test/alpha/HPlusOut_M80.root");
  std::cout << "--> Adding TFiles to TChain ..." << std::endl;
  // Signal
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/signal/HPlusOut_M80.root");
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/signal/HPlusOut_M140.root");
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/signal/HPlusOut_M160.root");
  // QCD_Pt30
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt30_1_1_BPw.root");
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt30_2_2_xsb.root/Events");
  // QCD_Pt80
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt80_1_3_YhA.root/Events");
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt80_2_2_qoK.root/Events");
  // QCD_Pt170
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt170_1_2_WlY.root/Events");
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt170_2_1_1GY.root/Events");
  // QCD_Pt300
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt300_1_2_9P2.root/Events");
  myChain->Add("rfio:/castor/cern.ch/user/a/attikis/Ntuples/bkg/HPlusOut_QCD_Pt300_2_1_68n.root/Events");
  //myChain->Print();
  std::cout << "\n--> TChain has " << myChain->GetEntries() << " entries." << std::endl;
  alpha_T obj(&myChain);
  obj.Loop();
}
