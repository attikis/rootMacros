//#######################################################################
// -*- C++ -*-
//       File Name:  myFunctions.h
// Original Author:  Alexandros Attikis
//         Created:  04 Aug 2010
//     Description:  Common functions used for ROOT
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//        Comments:  
//#######################################################################
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
//
#include <vector>
#include <TMath.h>
#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <iostream>
#include <Math/Vector3D.h>
#include <Math/Point3D.h>

// Function to Sort a jet 3vector according to Et (Pt essentially)
//***************************************************************
std::vector< ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > sortCaloJets(std::vector< ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > caloJetsToSort, Int_t caloJetSize) {
  
  // Declare variables
  ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> myTmpLdgJet;
  ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> myTmpLdgJet_new;
  std::vector< ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > caloJetsSorted;
  
  Float_t caloJetsToSort_Et  ;
  Float_t caloJetsToSort_Eta ;
  
  // Store the "first" N jets [wrt energy).
  for ( Int_t i = 0; i < caloJetSize; i++) {
    
    for ( Int_t  myJet = caloJetsToSort.begin(); myJet != caloJetsToSort.end(); ++myJet) {
      std::cout << "HEREEE" << std::endl;    
    }
  }
  /*    
  //caloJetsToSort_Et   = sqrt( caloJetsToSort.Perp2() );
  //	caloJetsToSort_Eta  = caloJetsToSort.Eta(); 
  //	std::cout << " myTmpLdgJet.Perp2() = " <<  myTmpLdgJet.Perp2() << std::endl;
  //	std::cout << " caloJetsToSort_Et = " <<  caloJetsToSort_Et << std::endl;
  //if( caloJetsToSort_Et > myTmpLdgJet.Perp2() ){ 
  //	  myTmpLdgJet = (*myJet);
  //	} else{}
  }
  // Store myJet as ith-LdgJet (descending order in Energy)
  //      caloJetsSorted.push_back(myTmpLdgJet);
  // Delete myJet from vector list
  //      caloJetsToSort = eraseVectorElement(caloJetsToSort, myTmpLdgJet);
  //      myTmpLdgJet = myTmpLdgJet_new;
  }//eof: for ( size_t i = 0; i < caloJetsToSort.size(); i++) {
  */
  return caloJetsSorted;
  
}//eof: 



//void sortCaloJets(vector< ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > caloJetsToSort, Int_t caloJetSize) {
void sortCaloJets(Int_t caloJetSize) {  
  // Declare variables
  ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> myTmpLdgJet;
  ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> myTmpLdgJet_new;
  vector< ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> > caloJetsSorted;
  
  Float_t caloJetsToSort_Et  ;
  Float_t caloJetsToSort_Eta ;
   /* 
  // Store the "first" N jets [wrt energy).
  for ( Int_t i = 0; i < caloJetSize; i++) {
    
    for ( Int_t  myJet = caloJetsToSort.begin(); myJet != caloJetsToSort.end(); ++myJet) {
      std::cout << "HEREEE" << std::endl;    
    }
  }
 `    
  //caloJetsToSort_Et   = sqrt( caloJetsToSort.Perp2() );
  //	caloJetsToSort_Eta  = caloJetsToSort.Eta(); 
  //	std::cout << " myTmpLdgJet.Perp2() = " <<  myTmpLdgJet.Perp2() << std::endl;
  //	std::cout << " caloJetsToSort_Et = " <<  caloJetsToSort_Et << std::endl;
  //if( caloJetsToSort_Et > myTmpLdgJet.Perp2() ){ 
  //	  myTmpLdgJet = (*myJet);
  //	} else{}
  }
  // Store myJet as ith-LdgJet (descending order in Energy)
  //      caloJetsSorted.push_back(myTmpLdgJet);
  // Delete myJet from vector list
  //      caloJetsToSort = eraseVectorElement(caloJetsToSort, myTmpLdgJet);
  //      myTmpLdgJet = myTmpLdgJet_new;
  }//eof: for ( size_t i = 0; i < caloJetsToSort.size(); i++) {
  */
  return 0;
  
}//eof: 
