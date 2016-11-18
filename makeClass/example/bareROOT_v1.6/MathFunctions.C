//#######################################################################
// -*- C++ -*-
//       File Name:  commonFunctions.h
// Original Author:  Alexandros Attikis
//         Created:  Fri 25 Sep 2009
//     Description:  Several functions that are bound to be called often
//                   for calculation. e.g.: deltaEta, deltaR, trueMom ..
//       Institute:  UCY
//         e-mail :  attikis@cern.ch
//          Status:  50% complete
//        Comments:  
//#######################################################################

#include <iostream>
#define MathFunctions_cxx
#include "MathFunctions.h"


int MathFunctions::Factorial (int num){
  if (num==1 || num == 0)
    return 1;
  return Factorial(num-1)*num; // recursive call
} //eof: int factorial (int num){




float MathFunctions::getTransverseMass( TLorentzVector v1, TLorentzVector v2, bool b_cout ){

  if(b_cout){ cout << " +++ commonFunctions, getTransverseMass()  +++ Entering Function" << endl; }
 
  float transverseMass = 0.0; 
  float et1 = v1.Et();
  float et2 = v2.Et();
  float pt1 = v1.Pt();
  float pt2 = v2.Pt();
  // copy the 4-vectors
  TLorentzVector v1dash = v1; 
  TLorentzVector v2dash = v2;
  
  // zero the z-component of the 4-Vectors and the energy.
  v1.SetPz(0.0);
  v2.SetPz(0.0);
  float m1 = v1dash.Mag();
  float m2 = v2dash.Mag();

  // transverseMass =  sqrt ( m1*m1 + m2*m2 + 2*(et1*et2 - v1.Vect().Dot(v2.Vect()) ) );
  transverseMass =  sqrt ( m1*m1 + m2*m2 + 2*(et1*et2 - v1.Vect().Dot(v2.Vect()) ) );
  
  if(b_cout){ 
    cout << " +++ commonFunctions, getTransverseMass()  +++ m1  = " <<  m1 << endl;
    cout << " +++ commonFunctions, getTransverseMass()  +++ m2  = " <<  m2 << endl;
    cout << " +++ commonFunctions, getTransverseMass()  +++ et1 = " << et1 << endl; 
    cout << " +++ commonFunctions, getTransverseMass()  +++ et2 = " << et2 << endl; 
    cout << " +++ commonFunctions, getTransverseMass()  +++ v1.Px() = " << v1.Px() << endl;
    cout << " +++ commonFunctions, getTransverseMass()  +++ v2.Px() = " << v2.Px() << endl;
    cout << " +++ commonFunctions, getTransverseMass()  +++ v1.Py() = " << v1.Py() << endl;
    cout << " +++ commonFunctions, getTransverseMass()  +++ v2.Py() = " << v2.Py() << endl;
    cout << " +++ commonFunctions, getTransverseMass()  +++ pt1 = " << pt1 << endl;
    cout << " +++ commonFunctions, getTransverseMass()  +++ pt2 = " << pt2 << endl;
    cout << " +++ commonFunctions, getTransverseMass()  +++ v1.Vect().Dot( v2.Vect() ) = " << v1.Vect().Dot( v2.Vect() ) << endl;
    cout << " +++ commonFunctions, getTransverseMass()  +++ transverseMass = " << transverseMass << endl;
  } //eof: if(b_cout){
 
  if(b_cout){ cout << " +++ commonFunctions, getTransverseMass()  +++ Leaving Function" << endl; }
  
  return transverseMass;

} //eof: float getTransverseMass(float m1, float m2, TLorentzVector v1, TLorentzVector v2, bool b_cout){




float MathFunctions::getDeltaPhi( float PhiOfObjectOne , float PhiOfObjectTwo){

  float deltaPhi = fabs ( PhiOfObjectOne - PhiOfObjectTwo );
  
  // Apply 2*pi effect correction on DeltaPhi
  if( deltaPhi >  6.283185308 ) deltaPhi = 6.283185308;
  if( deltaPhi >  3.141592654 ) deltaPhi = ( 6.283185308 - deltaPhi ); 
   
  return deltaPhi;

} //eof: float getDeltaPhi( float PhiOfObjectOne , float PhiOfObjectTwo){



float MathFunctions::getDeltaEta( float EtaOfObjectOne , float EtaOfObjectTwo){

  float deltaEta = fabs ( EtaOfObjectOne - EtaOfObjectTwo );
     
  return deltaEta;

} //eof: float getDeltaEta( float EtaOfObjectOne , float EtaOfObjectTwo){



float MathFunctions::getDeltaR( float DeltaPhi , float DeltaEta ){

  float deltaR = sqrt( pow( DeltaPhi , 2) + pow( DeltaEta , 2) );
  
  return deltaR;

} //eof: float getDeltaR( float DeltaPhi , float DeltaEta ){



int MathFunctions::getArrayIndexOfMin( float Array[] , int ArrayLength ){

  // Set the minimum as the first element of the array
  float MinimumValue = Array[0]; 
  int ArrayIndexForMinimum = 0;   
  
     // loop over all array elements and compare to get the true minimum
     for( int i = 0; i < ArrayLength; i++){
       
       if( Array[i] < MinimumValue ){
	 MinimumValue = Array[i];      
	 ArrayIndexForMinimum = i;
       }

     }
     return ArrayIndexForMinimum;

} //eof: int getArrayIndexOfMin( float Array[] , int ArrayLength ){



float MathFunctions::getArrayMin( float Array[] ,	int ArrayLength ){
					      
  // Set the minimum as the first element of the array
  float MinimumValue = Array[0]; 
  int ArrayIndexForMinimum=0; 
  
  // loop over all array elements and compare to get the true minimum
  for( int i = 0; i < ArrayLength; i++){
    
    if( Array[i] < MinimumValue ){
      MinimumValue = Array[i];      
      ArrayIndexForMinimum = i;
    }
    
  }
  
  // return Array[ArrayIndexForMinimum];
  return MinimumValue;
  
} //eof: float getArrayMin( float Array[] , int ArrayLength){



float MathFunctions::getArrayMax( float Array[] ,	int ArrayLength ){
  
  // Set the minimum as the first element of the array
  float MaximumValue = Array[0]; 
  int ArrayIndexForMaximum=0; 
  
  // std::cout << " ArrayLength " << ArrayLength << std::endl;
  
  // loop over all array elements and compare to get the true minimum
  for( int i = 0; i < ArrayLength; i++){
    
    if( Array[i] < MaximumValue ){
      MaximumValue = Array[i];      
      ArrayIndexForMaximum = i;
    }
    
  }
  
  // return Array[ArrayIndexForMaximum];
  return MaximumValue;
     
} //eof: float getArrayMax( float Array[] , int ArrayLength){



int MathFunctions::getVectorIndexOfMin( vector<float> InputVector ){
  
  // Set the minimum as the first element of the vector
  float MinimumValue = InputVector[0];
  int VectorIndexForMinimum = 0;   
  
  // loop over all vector elements and compare to get the true minimum
  for( unsigned int i = 0; i < InputVector.size(); i++){
    
    if( InputVector[i] < MinimumValue ){
      MinimumValue = InputVector[i];      
      VectorIndexForMinimum = i;
    }
    
  }
     return VectorIndexForMinimum;

} //eof: int getVectorIndexOfMin( vector<int> ){



float MathFunctions::getVectorMin( vector<float> InputVector ){
					      
  // Set the minimum as the first element of the vector
  float MinimumValue = InputVector[0]; 
  int VectorIndexForMinimum=0; 
  
  // loop over all vector elements and compare to get the true minimum
  for( unsigned int i = 0; i < InputVector.size(); i++){
    
    if( InputVector[i] < MinimumValue ){
      MinimumValue = InputVector[i];      
      VectorIndexForMinimum = i;
    }
    
  }
  
  // return InputVector[VectorIndexForMinimum];
  return MinimumValue;
  
} //eof: float getVectorMin( vector<float> InputVector ){



float MathFunctions::getVectorMax( vector<float> InputVector ){
  
  // Set the minimum as the first element of the vector
  float MaximumValue = InputVector[0]; 
  unsigned int VectorIndexForMaximum=0; 
  
  // loop over all vector elements and compare to get the true minimum
  for( unsigned int i = 0; i < InputVector.size(); i++){
    
    if( InputVector[i] < MaximumValue ){
      MaximumValue = InputVector[i];      
      VectorIndexForMaximum = i;
    }
    
  }
  
  // return InputVector[VectorIndexForMaximum];
  return MaximumValue;
     
} //eof: float getVectorMax( vector<float> InputVector ){




void MathFunctions::coutVector( vector<int> v_myIntsVector ){

  // create iterator
  vector<int>::iterator it_myIntsVector;
  cout << " *** void coutVector( vector<int> v_myIntsVector ) *** " << endl;
  for( it_myIntsVector = v_myIntsVector.begin(); it_myIntsVector < v_myIntsVector.end(); it_myIntsVector++){
    cout << (*it_myIntsVector) << endl;
  }
} //eof: void coutVector( vector<int> v_myIntsVector ){




void MathFunctions::coutVector( vector<float> v_myFloatsVector ){

  // create iterator
  vector<float>::iterator it_myFloatsVector;
  cout << " *** void coutVector( vector<float> v_myFloatsVector ) *** " << endl;
  for( it_myFloatsVector = v_myFloatsVector.begin(); it_myFloatsVector < v_myFloatsVector.end(); it_myFloatsVector++){
    cout << (*it_myFloatsVector) << endl;
  }
} //eof: void coutVector( vector<float> v_myFloatsVector ){




void MathFunctions::coutVector( vector<double> v_myDoublesVector ){

  // create iterator
  vector<double>::iterator it_myDoublesVector;
  cout << " *** void coutVector( vector<double> v_myDoublesVector ) *** " << endl;
  for( it_myDoublesVector = v_myDoublesVector.begin(); it_myDoublesVector < v_myDoublesVector.end(); it_myDoublesVector++){
    cout << (*it_myDoublesVector) << endl;
  }
} //eof: void coutVector( vector<double> v_myDoublesVector ){



void MathFunctions::coutVector( vector<char> v_myCharsVector ){

  // create iterator
  vector<char>::iterator it_myCharsVector;
  cout << " *** void coutVector( vector<char> v_myCharsVector ) *** " << endl;
  for( it_myCharsVector = v_myCharsVector.begin(); it_myCharsVector < v_myCharsVector.end(); it_myCharsVector++){
    cout << (*it_myCharsVector) << endl;
  }
} //eof: void coutVector( vector<char> v_myCharsVector ){



void MathFunctions::coutVector( vector<string> v_myStringsVector ){

  // create iterator
  vector<string>::iterator it_myStringsVector;
  cout << " *** void coutVector( vector<string> v_myStringsVector ) *** " << endl;
  for( it_myStringsVector = v_myStringsVector.begin(); it_myStringsVector < v_myStringsVector.end(); it_myStringsVector++){
    cout << (*it_myStringsVector) << endl;
  }
} //eof: void coutVector( vector<string> v_myStringsVector ){

//#########################################// eof file //#########################################//
