//#######################################################################
// -*- ROOT macro-*-
//
// eff_pur_plots.C
//
// Original Author:  Alexandros Attikis
//         Created:  13 Oct 2009
//       Institute:  UCY
//          status:  100%
//         e-mail :  attikis@cern.ch
//     description:  macro to perform the tauVeto MC analysis
//                   To run type: |myLinux> root -l tauVetoAnalysis.C 
//        comments:  create a function that determines how to divide a canvas
//                   see eff_pur_plots.C for hint
//             url:  http://root.cern.ch/root/html/TDirectory.html
//#######################################################################

{
  // C++ libraries
#include <vector>
  
  // Customise your gPad, plots etc..
  //********************************************************************//
  getFormalStyle();
  getMyStyle();
  // LAWStyle();
  
  // Define PATHS here
  //********************************************************************//
  std::cout << "*** PATH Definition ***" << std::endl;  
  
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/plots/";
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/";
  Char_t  *FileName = "PYTHIA6_Tauola_TTbar_WtoTauNu_7TeV_cff_py_GEN_MC_analysis.root";
  
  Char_t  *SavePathHplusNote09 = "/afs/cern.ch/user/a/attikis/w0/HPlusNote09/figures/";
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_plots/";

  Char_t  *ReadPath_signal_80 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_80_new/res/";
  Char_t  *FileName_signal_80 = "merged_grid_analysis.root";  

  Char_t  *ReadPath_signal_140 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_140_new/res/";
  Char_t  *FileName_signal_140 = "merged_grid_analysis.root";  

  Char_t  *ReadPath_signal_160 = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_signal_160_new/res/";
  Char_t  *FileName_signal_160 = "merged_grid_analysis.root";  
  
  Char_t  *ReadPath_ttbar = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_ttbar/res/";
  Char_t  *FileName_ttbar = "merged_grid_analysis.root";   

  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Load ROOT File ***" << std::endl;
  TFile *f = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( f );
  myanalyzer->ls();
  
  // Find Histograms
  //********************************************************************//
  std::cout << "*** Find Histograms ***" << std::endl;
  // Go to a directory to retrieve a pointer to the desired histo. Change to the directory where the histograms are located
  Char_t *tauVetoDir = ":/myanalyzer/tauVetoAnalysis" ;
  TString tauVetoPath = (TString(ReadPath) + TString(FileName) + TString(tauVetoDir) );
  // std::cout << "\n *** tauVetoPath = " << tauVetoPath << std::endl;
  // f->cd( tauVetoPath );
  signalFile_140->cd( tauVetoPath ); 
  gDirectory->ls();
  std::cout << "\n " << std::endl;
  
  // Manage Canvases
  //********************************************************************//
   // 3) Create Vectors and Iterators (one for each canvas)
  //********************************************************************//
  std::cout << "*** Manage Canvases ***" << std::endl;
  
  Int_t nCanvas = 41;
  Char_t myCanvasTitles[nCanvas][100];
  vector <TString> v_myCanvasNames;  
  vector <TCanvas*> v_myCanvas;  
  vector <TCanvas*>::iterator it_myCanvas;
  
  // Loop over the filenames to be added to the chain
  for(Int_t j = 0; j < nCanvas; j++){
    
    {sprintf(myCanvasTitles[j], "canvas_%d", j);
    cout << "Created " << myCanvasTitles[j] << endl;
    }
    TCanvas *myCanvas = new TCanvas(TString( myCanvasTitles[j] ),  TString( myCanvasTitles[j] ), 100, 100, 1000, 1000);
    v_myCanvasNames.push_back(TString( myCanvasTitles[k] ));  
    v_myCanvas.push_back(myCanvas);
  } // //end of: for(Int_t j=0; j < nCanvas; j++){
  
  // loop over Canvases and divide them
  for( Int_t k = 0; k < nCanvas; k++){
    v_myCanvas[k]->Divide(1);
  }
  
  // Plot Histograms
  //*******************
  std::cout << "*** Plot Histograms ***" << std::endl;
  Int_t counter = 0;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_tauFromW_VisibleEt_Vcut_Histo, mcColour("et"), "#tau^{-}_{visible} E_{T} (GeV)", "" , 0.0 , 300.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_tauFromW_VisibleEta_Vcut_Histo, mcColour("eta"), "#tau^{-}_{visible} #eta", "" , -5.0 , 5.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_tauFromW_LdgPt_Vcut_Histo, mcColour("ldgpt"), "#tau^{-}_{visible} Ldg P_{T} (GeV)", "" , 0.0 , 300.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_tauFromW_Visible_LdgPt_DeltaR_Vcut_Histo, mcColour("deltaR"), "#DeltaR( #tau^{-}_{visible} Axis , #tau^{-}_{visible} Ldg P_{T} (GeV) )" , "" , 0.0 , 2.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle_TH2D( VCuts:genP_tauFromW_VisibleEt_Vs_genP_nuFromWDecay_et_Histo, "#tau^{-}_{visible} E_{T} (GeV)", "#bar{#nu}_{#tau^{-}} E_{T} (GeV)" , 0.0 , 200.0, 0.0 , 200.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle_TH2D( VCuts:genP_tauFromW_VisibleEt_Vs_genP_nuFromWtauDecay_et_Histo, "#tau^{-}_{visible} E_{T} (GeV)" , "#nu_{#tau^{-}} E_{T} (GeV)"  , 0.0 , 200.0, 0.0 , 200.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;  

   v_myCanvas[counter]->cd(1);
   SetHistoStyle_TH2D(  VCuts:genP_tauFromW_VisibleEt_Vs_DeltaR_nuFromW_nuFromWtau_Histo, "#tau^{-}_{visible} E_{T} (GeV)" , "#DeltaR(#nu_{#tau^{-}}, #bar{#nu}_{#tau^{-}})"  , 0.0 , 300.0, 0.0 , 5.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
   
//    v_myCanvas[counter]->cd(1);
//    SetHistoStyle( VCuts:DeltaPhi_Visible_Htau_MET_Histo, mcColour("deltaPhi"), "#Delta#phi(#tau^{+}_{visible} , E_{T}^{miss} )" , ""  , 0.0 , 3.2 )->Draw();
//    AddTText_PRELIM()->Draw();
//    counter++;

//    v_myCanvas[counter]->cd(1);
//    SetHistoStyle( VCuts:DeltaPhi_Visible_Htau_MET_H_Histo, mcColour("deltaPhi"), "#Delta#phi(#tau^{+}_{visible} , E_{T_{H^{+}}}^{miss} )" , ""  , 0.0 , 3.2 )->Draw();
//    AddTText_PRELIM()->Draw();
//    counter++;
   
//    v_myCanvas[counter]->cd(1);
//    SetHistoStyle_TH2D( VCuts:alpha1H_Vs_alpha2H_Histo, "#alpha_{1} = #Delta#phi(#tau^{+}_{visible} , E_{T}^{miss} )" , "#alpha_{2} = #Delta#phi(#tau^{+}_{visible} , E_{T_{H^{+}}}^{miss})"  , 0.0 , 3.2, 0.0 , 3.2 )->Draw();
//    AddTText_PRELIM()->Draw();
//    counter++;  

   v_myCanvas[counter]->cd(1);
   SetHistoStyle_TH2D( genP_tauFromW_VisibleEt_Vs_genP_tauFromH_VisibleEt_Histo, "#tau^{W^{-}}_{visible} E_{T} (GeV)" , "#tau^{H^{+}}_{visible} E_{T} (GeV)"  , 0.0 , 300.0, 0.0, 300.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle_TH2D( VCuts:genP_tauFromW_VisibleEt_Vs_genP_tauFromH_VisibleEt_Histo, "#tau^{W^{-}}_{visible} E_{T} (GeV)" , "#tau^{H^{+}}_{visible} E_{T} (GeV)", 0.0 , 300.0, 0.0 , 300.0  )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:DeltaPhi_Visible_Htau_nuFromHDecay_Histo, mcColour("deltaPhi"), "#Delta#phi( #tau^{+}_{visible} , #nu_{H^{+} #rightarrow #tau^{+} + #nu_{#tau}} )", "", 0.0 , 3.2 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle_TH2D( VCuts:DeltaPhi_Visible_Htau_MET_Vs_DeltaPhi_Visible_Wtau_MET_Histo, "#Delta#phi( #tau^{+}_{visible} , E_{T}^{miss} )","#Delta#phi( #tau^{-}_{visible} , E_{T}^{miss} )", 0.0 , 3.2, 0.0 , 3.2 )->Draw("COLZ");
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_DeltaPhi_of_tauJets_Histo , mcColour("deltaPhi"), "#Delta#phi(#tau^{-}, #tau^{+} )", " " , 0.0 , 3.2 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_DeltaEta_of_tauJets_Histo , mcColour("deltaEta"), "#Delta#eta(#tau^{-}, #tau^{+} )", " " , 0.0 , 10.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_DeltaR_of_tauJets_Histo , mcColour("deltaR"), "#DeltaR(#tau^{-}, #tau^{+} )", " " , 0.0 , 10.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

  
  //*********************************
  std::cout << "*** Change path ***" << std::endl;
  // Go to a directory to retrieve a pointer to the desired histo. Change to the directory where the histograms are located
  Char_t *tauVetoExtraDir = ":/myanalyzer/tauVetoAnalysisExtra" ;
  TString tauVetoExtraPath = (TString(ReadPath) + TString(FileName) + TString(tauVetoExtraDir) );
  std::cout << "\n *** tauVetoExtraPath = " << tauVetoExtraPath << std::endl;
  //f->cd( tauVetoExtraPath );
  signalFile_140->cd( tauVetoExtraPath );
  gDirectory->ls();
  std::cout << "\n " << std::endl;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_tauFromW_et_Vcut_Histo , mcColour("et"), "#tau^{-}  E_{T} (GeV)", " " , 0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_tauFromW_eta_Vcut_Histo , mcColour("eta"), "#tau^{-} #eta", "" , -5.0 , 5.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_tauFromW_LdgEta_Vcut_Histo , mcColour("eta"), "#tau^{-} Ldg #eta", "" , -5.0 , 5.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1); 
   SetHistoStyle(VCuts:DeltaPhi_Visible_Wtau_MET_Histo , mcColour("met"), "#Delta#phi(#tau^{-}_{visible}, E_{T}^{miss} ) ", "" , 0.0 , 3.2 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1); 
   SetHistoStyle( VCuts:mcMET_Histo , mcColour("met"), "E_{T}^{miss}", " " , 0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();  
   counter++;
  
   v_myCanvas[counter]->cd(1); 
   SetHistoStyle( VCuts:genP_nuFromWDecay_et_Histo , mcColour("et"), "#bar{#nu}_{#tau^{-}} E_{T} (GeV)", " " , 0.0 , 300.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_nuFromWDecay_eta_Histo , mcColour("eta"), "#bar{#nu}_{#tau^{-}} #eta", " " , -5.0 , 5.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_nuFromWtauDecay_et_Histo , mcColour("et"), "#nu_{#tau^{-}} E_{T} (GeV)", " " , 0.0 , 300.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_nuFromWtauDecay_eta_Histo , mcColour("eta"), "#nu_{#tau^{-}} #eta", " " , -5.0 , 5.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1); 
   SetHistoStyle(  VCuts:DeltaPhi_Visible_Wtau_MET_Histo , mcColour("deltaPhi"), "#Delta#phi(#tau^{-}_{visible}, E_{T}^{miss} )", " " , 0.0 , 3.2 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle(  VCuts:DeltaPhi_Visible_Wtau_MET_W_Histo , mcColour("met"), "#Delta#phi(#tau^{-}_{visible}, E_{T_{W^{-}}}^{miss} )", " " , 0.0 , 3.2 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle_TH2D( VCuts:DeltaPhi_Visible_Htau_MET_W_Vs_DeltaPhi_Visible_Wtau_MET_Histo, "#Delta#phi(#tau^{+}_{visible}, E_{T}^{miss} )" , "#Delta#phi(#tau^{-}_{visible}, E_{T}^{miss} )"  , 0.0 , 3.2, 0.0 , 3.2 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   // Go to a directory to retrieve a pointer to the desired histo
  //********************************************************************//
  // change to the directory where the histograms are located
  Char_t *metDir = ":/myanalyzer/genP_Met" ;
  TString metPath = (TString(ReadPath) + TString(FileName) + TString(metDir) );
  // std::cout << "\n *** MetPath = " << MetPath << std::endl;
  // f->cd( metPath );
  signalFile_140->cd( metPath );
  gDirectory->ls();
  std::cout << "\n " << std::endl;
  
  // Rebin histos
  genP_leptWdecayMET_Histo->Rebin(2);
  genP_hadrWdecayMET_Histo->Rebin(2);
  genP_leptAndHadrWdecayMET_Histo->Rebin(2);
     
  v_myCanvas[counter]->cd(1);
  SetHistoStyle( genP_Neutrino_Multiplicity_Histo , 1, "Neutrino Evt Multiplicity", "" , 0.0 , 20.0 )->Draw();
  AddTText_PRELIM()->Draw();
  counter++;

  v_myCanvas[counter]->cd(1);
  SetHistoStyle( genP_Neutrino_Multiplicity_Lept_Histo , 1, "Neutrino Evt Multiplicity (W #rightarrow lept)", "" , 0.0 , 20.0 )->Draw();
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  SetHistoStyle( genP_Neutrino_Multiplicity_Hadr_Histo , 1, "Neutrino Evt Multiplicity (W #rightarrow hadr)", "" , 0.0 , 20.0 )->Draw();
  AddTText_PRELIM()->Draw();
  counter++;
 
  v_myCanvas[counter]->cd(1);
  SetHistoStyle( genP_Neutrino_Multiplicity_LeptAndHadr_Histo , 1, "Neutrino Evt Multiplicity (W #rightarrow lept+hadr)", "" , 0.0 , 20.0 )->Draw();
  AddTText_PRELIM()->Draw();
  counter++;
 
  v_myCanvas[counter]->cd(1);
  SetHistoStyle( genP_Event_Met_Histo, mcColour("met"), "E_{T}^{miss} (GeV)", "" , 0.0 , 500.0 )->Draw();
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  SetHistoStyle( genP_Event_MetAngle_Histo , mcColour("phi"), "E_{T}^{miss} Angle (rads)" , "" , 0.0 , 3.2 )->Draw();
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  SetHistoStyle( genP_hadrWdecayMET_Histo, mcColour("met"), "E_{T}^{miss} (GeV), W^{-} #rightarrow hadrons " , "" , 0.0 , 500.0 )->Draw();
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  SetHistoStyle( genP_leptWdecayMET_Histo, mcColour("met"), "E_{T}^{miss} (GeV), W^{-} #rightarrow leptons" , "" , 0.0 , 500.0 )->Draw();
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  SetHistoStyle( genP_leptAndHadrWdecayMET_Histo, mcColour("met"), "E_{T}^{miss} (GeV)" , "" , 0.0 , 500.0 )->Draw();
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  SuperImpose4Histos( genP_Event_Met_Histo, genP_leptWdecayMET_Histo, genP_hadrWdecayMET_Histo, genP_leptAndHadrWdecayMET_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept+hadr", 0.0 , 300.0, "E_{T}^{miss} (GeV)", "mcMET");
  AddTText_PRELIM()->Draw();
  counter++;
  
  v_myCanvas[counter]->cd(1);
  SuperImpose4Histos( genP_Neutrino_Multiplicity_Histo, genP_Neutrino_Multiplicity_Lept_Histo, genP_Neutrino_Multiplicity_Hadr_Histo, genP_Neutrino_Multiplicity_LeptAndHadr_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept+hadr", 0.0 , 15.0, "Neutrino Evt Multiplicity", "Neutrino Multiplicity");
  AddTText_PRELIM()->Draw();
  counter++;

  v_myCanvas[counter]->cd(1);
  SuperImpose4Histos( genP_Neutrino_Multiplicity_Et5_Histo, genP_Neutrino_Multiplicity_Lept_Et5_Histo, genP_Neutrino_Multiplicity_Hadr_Et5_Histo, genP_Neutrino_Multiplicity_LeptAndHadr_Et5_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept+hadr", 0.0 , 15.0, "Neutrino Evt Multiplicity", "Neutrino Multiplicity");
  AddTText_PRELIM()->Draw();
  counter++;
  
   // update gPad
   gPad->Update();
   
   // Save canvases to a file?
   Bool_t SavePlot = kFALSE; // kTRUE or kFALSE
   if(SavePlot){ 
     it_myCanvas = v_myCanvas.begin(); //initialize iterator
     
     // loop over all canvases
     for( Int_t k = 0; k < nCanvas; k++){
       
       // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".ps" );  // Is NOT compatible with PDFLaTeX
       // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".pdf" ); // IS compatible with PDFLaTeX
       (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".eps" ); // Is NOT compatible with PDFLaTeX
       // (*it_myCanvas)->SaveAs( TString(SavePath) + TString(myCanvasTitles[k]) + ".png" ); // IS compatible with PDFLaTeX
       it_myCanvas++; // increment iteratorto access next canvas
       
     } //end of: for( Int_t k = 0; k < nCanvas; k++){
   } // end of: if(SavePlot){ 
   
   // Delete canvases?
   Bool_t DeleteCanvases = kFALSE; // kTRUE or kFALSE
   if(DeleteCanvases){ 
     it_myCanvas = v_myCanvas.begin(); //initialize iterator
     // loop over all canvases
     for( Int_t k = 0; k < nCanvas-5; k++){
       
       delete v_myCanvas[k];
       it_myCanvas++; // increment iteratorto access next canvas 
       
     } //end of: for( Int_t k = 0; k < nCanvas; k++){
   }//end of: if(DeleteCanvases){ 
   
} //************************************** end of macro ************************************************//
