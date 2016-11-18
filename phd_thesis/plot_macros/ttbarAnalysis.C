 //#######################################################################
// -*- ROOT macro-*-
//
// ttbarAnalysis.C
//
// Original Author:  Alexandros Attikis
//         Created:  14 Dec 2009
//       Institute:  UCY
//          status:  100%
//         e-mail :  attikis@cern.ch
//     description:  To run type: |myLinux> root -l ttbarAnalysis.C 
//             url:  http://root.cern.ch/root/html/TDirectory.html
//#######################################################################

{
  // C++ libraries
#include <vector>
  
  // Customise your gPad, plots etc..
  //********************************************************************//
  // getFormalStyle();
  getMyStyle();
  // LAWStyle();
  
  // Define PATHS here
  //********************************************************************//
  std::cout << "*** PATH Definition ***" << std::endl;  
  
  Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/plots/";
  Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/";
  Char_t  *FileName = "testing_ttbar.root";  
  
  //   Char_t  *SavePath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/HPlusNote09_plots/signal/";
  //   Char_t  *ReadPath = "/afs/cern.ch/user/a/attikis/scratch0/CMSSW_3_1_2/src/analysis/myAnalyzer/AN_5Dec09/res/";
  //   Char_t  *FileName = "merged_grid_analysis.root";
  
  
  // Load ROOT file and Check it
  //********************************************************************//
  std::cout << "*** Load ROOT File ***" << std::endl;
  TFile *f = new TFile(TString(ReadPath) +  TString(FileName) );
  checkTFile( f );
  //myanalyzer->ls();
  
  // Find Histograms
  //********************************************************************//
  std::cout << "*** Find Histograms ***" << std::endl;
  // Go to a directory to retrieve a pointer to the desired histo. Change to the directory where the histograms are located
  Char_t *ttbarDir = ":/myanalyzer/ttbarAnalysis" ;
  TString ttbarPath = (TString(ReadPath) + TString(FileName) + TString(ttbarDir) );
  // std::cout << "\n *** ttbarPath = " << ttbarPath << std::endl;
  f->cd( ttbarPath );
  gDirectory->ls();
  std::cout << "\n " << std::endl;
  
  // Manage Canvases
  //********************************************************************//
   // 3) Create Vectors and Iterators (one for each canvas)
  //********************************************************************//
  std::cout << "*** Manage Canvases ***" << std::endl;
  
  Int_t nCanvas = 39; 
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
      cout << "Dividing Canvas v_myCanvas[" << k << "] "<< endl;
      v_myCanvas[k]->Divide(1);
  } //end of: for( Int_t k = 0; k < nCanvas; k++){
  
  // Plot Histograms
  //*******************
  std::cout << "*** Plot Histograms ***" << std::endl;
  Int_t counter = 0;
  
  v_myCanvas[counter]->cd(1);
  SetHistoStyle( p4_genP_tauFromWPlus_Visible_Pt_Histo , mcColour("pt"), "#tau^{+}_{vis} P_{T} (GeV)", "" , 0.0 , 800.0 )->Draw(); 
  AddTText_PRELIM()->Draw();
  counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( p4_genP_tauFromWPlus_Visible_Eta_Histo , mcColour("eta"), "#tau^{+}_{vis} #eta", "" , -5.5 , 5.5 )->Draw(); 
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_EvtMet_Histo , mcColour("met") , "E_{T}^{miss} (GeV)", "" , 0.0 , 800.0 )->Draw(); 
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle(VCuts:genP_EvtMet_hadrWdecay_Histo ,mcColour("met"), "E_{T}^{miss} (GeV), W #rightarrow hadrons", "" , 0.0 , 800.0 )->Draw(); 
   AddTText_PRELIM()->Draw();
   counter++;  

   v_myCanvas[counter]->cd(1);
   SetHistoStyle(VCuts:genP_EvtMet_leptWdecay_Histo, mcColour("met"), "E_{T}^{miss} (GeV), W #rightarrow leptons", "" , 0.0 , 800.0 )->Draw(); 
   AddTText_PRELIM()->Draw();
   counter++;  

   v_myCanvas[counter]->cd(1); 
   SetHistoStyle( VCuts:MtOfWPlus_tauFromWPlusVis_Met_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+}_{vis} , MET) (GeV)" , "",  0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:MtOfWPlus_tauFromWPlusVis_Met_hadrWdecay_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+}_{vis} , MET), W #rightarrow hadr (GeV)" , ""  , 0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:MtOfWPlus_tauFromWPlusVis_Met_leptWdecay_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+}_{vis} , MET), W #rightarrow lept (GeV)" , ""  , 0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( MtOfWPlus_tauFromWPlus_Met_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+}_{vis} , MET) (GeV)" , "",  0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
    SetHistoStyle( MtOfWPlus_tauFromWPlus_Met_hadrWdecay_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+}_{vis} , MET), W #rightarrow hadr (GeV)" , ""  , 0.0 , 500.0 )->Draw();
    AddTText_PRELIM()->Draw();
    counter++;
   
    v_myCanvas[counter]->cd(1);
    SetHistoStyle(MtOfWPlus_tauFromWPlus_Met_leptWdecay_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+}_{vis} , MET), W #rightarrow lept (GeV)" , ""  , 0.0 , 500.0 )->Draw(); 
    AddTText_PRELIM()->Draw();
    counter++;
   
    v_myCanvas[counter]->cd(1);
    SetHistoStyle(VCuts:p4_genP_beautyFromTop_Pt_Histo, mcColour("pt"), "P_{T} b_{t #rightarrow W^{-}b} (GeV)", "" , 0.0 , 400.0 )->Draw(); 
    AddTText_PRELIM()->Draw();
    counter++;
   
    v_myCanvas[counter]->cd(1);
    SetHistoStyle( VCuts:p4_genP_beautyBarFromTopBar_Pt_Histo, mcColour("pt"), "P_{T} b_{#bar{t} #rightarrow W^{-}#bar{b}} (GeV)", "" , 0.0 , 400.0 )->Draw(); 
    AddTText_PRELIM()->Draw();
    counter++;
     
    v_myCanvas[counter]->cd(1);
    SetHistoStyle( VCuts:DeltaR_tauFromWPlusVis_beautyFromTop_Histo, mcColour("deltaR"), "#Delta R(#tau^{+}_{vis} , b_{t #rightarrow W^{+}b})", "" , 0.0 , 10.0 )->Draw(); 
    AddTText_PRELIM()->Draw();
    counter++;
    
    v_myCanvas[counter]->cd(1);
    SetHistoStyle(  VCuts:p4_genP_topFromWPlusb_Pt_Histo, mcColour("pt"), "P_{T} t_{t #rightarrow W^{+}b} (GeV)", "" , 0.0 , 800.0 )->Draw(); 
    AddTText_PRELIM()->Draw();
    counter++;
     
    v_myCanvas[counter]->cd(1);
    SetHistoStyle(  VCuts:p4_genP_topBarFromWb_Pt_Histo, mcColour("pt"), "P_{T} t_{t #rightarrow W^{-}b} (GeV)", "" , 0.0 , 800.0 )->Draw(); 
    AddTText_PRELIM()->Draw();
    counter++;

    v_myCanvas[counter]->cd(1);
    SetHistoStyle( VCuts:genP_tauFromW_LdgPt_Histo , mcColour("ldgpt"), "#tau^{-}_{Ldg} P_{T} (GeV)", "" , 0.0 , 100.0 )->Draw(); 
    AddTText_PRELIM()->Draw();
    counter++;

    v_myCanvas[counter]->cd(1);
    SetHistoStyle( VCuts:genP_tauFromW_LdgPt_Cha_Histo , mcColour("ldgpt"), "#tau^{-}_{Ldg_Ch} P_{T} (GeV)", "" , 0.0 , 100.0 )->Draw(); 
    AddTText_PRELIM()->Draw();
    counter++;
   
    v_myCanvas[counter]->cd(1);
    SetHistoStyle( VCuts:p4_genP_tauFromW_Visible_Pt_Histo , mcColour("pt"), "#tau^{-}_{vis} P_{T} (GeV)", "" , 0.0 , 800.0 )->Draw(); 
    AddTText_PRELIM()->Draw();
    counter++;
    
    v_myCanvas[counter]->cd(1);
    SetHistoStyle( VCuts:p4_genP_tauFromW_Visible_Eta_Histo , mcColour("eta"), "#tau^{-}_{vis} #eta (GeV)", "" , -5.0 , 5.0 )->Draw(); 
    AddTText_PRELIM()->Draw();  
    counter++;
   
    v_myCanvas[counter]->cd(1);
    SetHistoStyle( p4_genP_tauFromW_Visible_Pt_Histo , mcColour("pt"), "#tau^{-}_{vis} P_{T} (GeV)", "" , 0.0 , 800.0 )->Draw(); 
    AddTText_PRELIM()->Draw();

    v_myCanvas[counter]->cd(1);
    SetHistoStyle( p4_genP_tauFromW_Visible_Eta_Histo , mcColour("eta"), "#tau^{-}_{vis} #eta (GeV)", "" , -5.0 , 5.0 )->Draw(); 
    AddTText_PRELIM()->Draw();  
    counter++;
     
    v_myCanvas[counter]->cd(1);
    SetHistoStyle( MtOfWPlus_tauFromWPlusVis_Met_Histo , mcColour("mt"), "W^{+} M_{T} (#tau^{+}_{vis} , MET) (GeV)", "" , 0.0 , 500.0 )->Draw(); 
    AddTText_PRELIM()->Draw();  
    counter++;
    
    v_myCanvas[counter]->cd(1);
   SetHistoStyle( MtOfWPlus_tauFromWPlus_NuFromWPlusDecay_Histo , mcColour("mt"), "W^{+} M_{T} (#tau^{+}_{vis} , #nu_{W^{+} #rightarrow #tau^{+} #nu}) (GeV)", "" , 0.0 , 500.0 )->Draw(); 
   AddTText_PRELIM()->Draw();  
   counter++;
   
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( MtOfWPlus_tauFromWPlusVis_NuSumFromWPlusDecay_Histo , mcColour("mt") , "W^{+} M_{T} (#tau^{+}_{vis} , #sum #nu_{W^{+} #rightarrow #tau^{+} #nu}) (GeV)", "" , 0.0 , 500.0 )->Draw(); 
   AddTText_PRELIM()->Draw();  
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( p4_nuSumFromWPlusDecay_Pt_Histo ,  mcColour("pt"), "P_{T} ( #nu_{W^{+} #rightarrow #tau^{+} #nu} + #nu_{#tau^{+} #rightarrow hadr #nu}) (GeV)", "" , 0.0 , 800.0 )->Draw(); 
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle(  VCuts:genP_DeltaR_of_tauFromW_and_beautyFromTop_Histo, mcColour("deltaR"), "#DeltaR(#tau^{-}, b_{t #rightarrow bW^{+}} )", " " , 0.0 , 10.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle(  VCuts:genP_DeltaR_of_tauFromW_and_beautyBarFromTopBar_Histo, mcColour("deltaR"), "#DeltaR(#tau^{-}, #bar{b}_{t #rightarrow #bar{b}W^{-}} )", " " , 0.0 , 10.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle(  VCuts:genP_DeltaR_of_tauFromWPlus_and_beautyFromTop_Histo, mcColour("deltaR"), "#DeltaR(#tau^{+}, b_{t #rightarrow bW^{+}} )", " " , 0.0 , 10.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle(  VCuts:genP_DeltaR_of_tauFromWPlus_and_beautyBarFromTopBar_Histo, mcColour("deltaR"), "#DeltaR(#tau^{+}, #bar{b}_{t #rightarrow #bar{b}W^{-}} )", " " , 0.0 , 10.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle( VCuts:genP_DeltaR_of_beautyBarFromTopBar_and_beautyFromTop_Histo, mcColour("deltaR"), "#DeltaR( b_{t #rightarrow bW^{+}}, #bar{b}_{t #rightarrow #bar{b}W^{-}} )", " " , 0.0 , 10.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle(MtOfWPlus_tauFromWPlus_Met_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+} , MET) (GeV)" , "",  0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle(MtOfWPlus_tauFromWPlus_Met_leptOrHadrWdecay_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+} , MET) (GeV)" , "",  0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1);
   SetHistoStyle(MtOfWPlus_tauFromWPlus_Met_leptWdecay_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+} , MET) (GeV)" , "",  0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SetHistoStyle(MtOfWPlus_tauFromWPlus_Met_hadrWdecay_Histo, mcColour("mt"), "W^{+} M_{T} (#tau^{+} , MET) (GeV)" , "",  0.0 , 500.0 )->Draw();
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1);
   SuperImpose4Histos( MtOfWPlus_tauFromWPlus_Met_Histo, MtOfWPlus_tauFromWPlus_Met_hadrWdecay_Histo, MtOfWPlus_tauFromWPlus_Met_leptWdecay_Histo, MtOfWPlus_tauFromWPlus_Met_leptOrHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept+hadr", 0.0 , 500.0, "W^{+} M_{T} (GeV)", "Transverse Mass: #tau^{+} + E_{T}^{miss}");
   AddTText_PRELIM()->Draw();
   counter++;
  
   v_myCanvas[counter]->cd(1); 
   SuperImpose4Histos( MtOfWPlus_tauFromWPlusVis_Met_Histo, MtOfWPlus_tauFromWPlusVis_Met_hadrWdecay_Histo, MtOfWPlus_tauFromWPlusVis_Met_leptWdecay_Histo, MtOfWPlus_tauFromWPlusVis_Met_leptOrHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept+hadr", 0.0 , 500.0, "W^{+} M_{T} (GeV)", "Transverse Mass: #tau^{+}_{vis} + E_{T}^{miss}");
   AddTText_PRELIM()->Draw();
   counter++;

   v_myCanvas[counter]->cd(1); 
   SuperImpose4Histos( VCuts:MtOfWPlus_tauFromWPlusVis_Met_Histo, VCuts:MtOfWPlus_tauFromWPlusVis_Met_hadrWdecay_Histo, VCuts:MtOfWPlus_tauFromWPlusVis_Met_leptWdecay_Histo, VCuts:MtOfWPlus_tauFromWPlusVis_Met_leptOrHadrWdecay_Histo, "W #rightarrow ALL", "W #rightarrow hadrons", "W #rightarrow leptons", "W #rightarrow lept+hadr", 0.0 , 500.0, "W^{+} M_{T} (GeV)", "Transverse Mass: #tau^{+}_{vis} + E_{T}^{miss} (With Cuts)");
   AddTText_PRELIM()->Draw();
   counter++;
   
   v_myCanvas[counter]->cd(1); 
   // SuperImpose4HistosNorm( MtOfWPlus_tauFromWPlus_NuFromWPlusDecay_Histo, MtOfWPlus_tauFromWPlusVis_NuSumFromWPlusDecay_Histo, MtOfWPlus_tauFromWPlus_Met_Histo, MtOfWPlus_tauFromWPlusVis_Met_Histo, "#tau^{+} , #sum #nu_{W^{+} } , #nu_{#tau^{+} #rightarrow hadr #nu_{#tau}}", "#tau^{+} , E_{T}^{miss}" , "#tau^{+}_{vis} , E_{T}^{miss}", 0.0 , 300.0, "W^{+} M_{T} (GeV)", "Transverse Mass: W #rightarrow ALL, #tau #rightarrow ALL");
   AddTText_PRELIM()->Draw();
   counter++;
    
   v_myCanvas[counter]->cd(1); 
   SuperImpose4Histos( MtOfWPlus_tauFromWPlusVis_Met_Histo, MtOfWPlus_tauFromWPlusVisLept_Met_Histo, MtOfWPlus_tauFromWPlusVisHadr_Met_Histo, MtOfWPlus_tauFromWPlusVisHadrAndLept_Met_Histo, "#tau^{+} #rightarrow ALL", "#tau^{+} #rightarrow lept", "#tau^{+} #rightarrow hadr", "#tau^{+} #rightarrow hadr+lept", 0.0 , 300.0, "W^{+} M_{T} (GeV)", "Transverse Mass: #tau^{+}_{vis} , W #rightarrow ALL");
   AddTText_PRELIM()->Draw();
   
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
    for( Int_t k = 0; k < nCanvas-3; k++){
      
      delete v_myCanvas[k];
      it_myCanvas++; // increment iteratorto access next canvas 
      
    } //end of: for( Int_t k = 0; k < nCanvas; k++){
  }//end of: if(DeleteCanvases){ 

} //************************************** end of macro ************************************************//
