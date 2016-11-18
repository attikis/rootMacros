// Author: Rene Brun   03/03/99

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#include <string.h>
#include "Riostream.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TArrow.h"
#include "TBox.h"
#include "TVirtualPad.h"
#include "TF1.h"
#include "TH1.h"
#include "TVector.h"
#include "TVectorD.h"
#include "TClass.h"


void BayesAsymmetricErrors(const int pass, const int total, double conflevel = 0.683, bool b_cout=true){
  //BayesStatsStruc BayesAsymmetricErrors(const int pass, const int total, double conflevel = 0.683, bool b_cout=true){
  
  // BayesStatsStruc s_myStats;  // make a structure to hold the data
  
  // Calculates the Bayesian Asymmetric Errors, using as input the total and passed number of events after a selection TCut.
  
  double mode, low, high; //these will hold the result of the Bayes calculation
  //  double conflevel = 0.683; // The confidence interval as a measure of the uncertainty in the measurement.
  
  if(b_cout){
    std::cout << "\n*** void BayesAsymmetricErrors() *** \nCalculating the Bayesian Asymmetric Errors, using as input the total ("<<total<<") and passed ("<<pass<<") number of events after a selection TCut. The confidence interval " << 100*conflevel << " will be used as a measure of the uncertainty in the measurement." << std::endl;
    cout << "A " << 100*conflevel << "% Confidence Level is used to assign the errors. Warning! You should understand, the errors reported are the shortest ranges containing " << 100*conflevel <<"% of the probability distrubution. The errors are not exactly Gaussian! The Minuit fitting routines will assume that the errors are Gaussian. But this is a reasonable approximation. A fit using the full shape of the error distribution for each point would be far more difficult to perform..." << endl;
  } //end of: if(b_cout){
  
  // This is the Bayes calculation...
  // g1.Efficiency(pass, total, confInterval, mode, low, high);
  
  int N = total;
  int k = pass;
  
  //If there are no entries, then we know nothing, thus return the prior...
  if (0==N) {
    mode = .5; low = 0.0; high = 1.0;
    return;
  }
  
  // Calculate the most probable value for the efficiency: <eff>= k/N 
  double efficiency = (double)k/N;
  
  double low_edge;
  double high_edge;
  
  if (k == 0) {
    low_edge = 0.0;
    high_edge = SearchUpper(low_edge, k, N, conflevel);
  } else if (k == N) {
    high_edge = 1.0;
    low_edge = SearchLower(high_edge, k, N, conflevel);
  } else {
    // GLOBAL_k = k;
    // GLOBAL_N = N;
    // CONFLEVEL = conflevel;
    Brent(0.0, 0.5, 1.0, 1.0e-9, &low_edge, k, N, conflevel);
    high_edge = low_edge + Interval(low_edge, k, N, conflevel);
  }
  
  // return output
  mode = efficiency;
  low = low_edge;
  high = high_edge;
  
  // exclude the poits where result is less < 0
  if (mode < 0) continue;
  
  //These are the low and high error bars
  low = mode-low;
   high = high-mode;
   
   if(b_cout){
     printf("BayesDividePoint: Total Events   = %d  , Events Passed   = %d , efficiency = %f \n", N, k, mode);
     printf("BayesDividePoint: Low Error Bars = %f  , High Error Bars = %f , efficiency = %f \n", low, high);
   } //end of: if(b_cout){

   printf("%f %f %f\n", mode, low, high);

//    s_myStats.Efficiency   = mode; // can be also purity, according to the input.
//    s_myStats.LowErrorBar  = low;
//    s_myStats.HighErrorBar = high;
//    s_myStats.NEvts        = N;
//    s_myStats.NEvtsPassed  = k;
//    s_myStats.NEvtsFailed  = (N-k);  
   // cout << " s_myStats.Efficiency = " << s_myStats.Efficiency << endl;
   // return s_myStats;
   return 0;
}


//______________________________________________________________________________
struct BayesStatsStruc {
  double Efficiency=-1.0; // can be also purity, according to the input.
  double LowErrorBar=-1.0; 
  double HighErrorBar=-1.0; 
  int NEvts=-1; 
  int NEvtsPassed=-1;
  int NEvtsFailed=-1;
};


//______________________________________________________________________________
double SearchUpper(double low, int k, int N, double c) const
{
   // Integrates the binomial distribution with
   // parameters k,N, and determines what is the upper edge of the
   // integration region which starts at low which contains probability
   // content c. If an upper limit is found, the value is returned. If no
   // solution is found, -1 is returned.
   // check to see if there is any solution by verifying that the integral up
   // to the maximum upper limit (1) is greater than c

   double integral = Beta_ab(low, 1.0, k, N);
   if (integral == c) return 1.0;    // lucky -- this is the solution
   if (integral < c) return -1.0;    // no solution exists
   double too_high = 1.0;            // upper edge estimate
   double too_low = low;
   double test;

   // use a bracket-and-bisect search
   // LM: looping 20 times might be not enough to get an accurate precision.
   // see for example bug https://savannah.cern.ch/bugs/?30246
   // now break loop when difference is less than 1E-15
   // t.b.d: use directly the beta distribution quantile

   for (int loop=0; loop<50; loop++) {
      test = 0.5*(too_low + too_high);
      integral = Beta_ab(low, test, k, N);
      if (integral > c)  too_high = test;
      else too_low = test;
      if ( TMath::Abs(integral - c) <= 1.E-15) break;
   }
   return test;
}
//______________________________________________________________________________

double SearchLower(double high, int k, int N, double c) const
{
   // Integrates the binomial distribution with
   // parameters k,N, and determines what is the lower edge of the
   // integration region which ends at high, and which contains
   // probability content c. If a lower limit is found, the value is
   // returned. If no solution is found, the -1 is returned.
   // check to see if there is any solution by verifying that the integral down
   // to the minimum lower limit (0) is greater than c

   double integral = Beta_ab(0.0, high, k, N);
   if (integral == c) return 0.0;      // lucky -- this is the solution
   if (integral < c) return -1.0;      // no solution exists
   double too_low = 0.0;               // lower edge estimate
   double too_high = high;
   double test;

   // use a bracket-and-bisect search
   // LM: looping 20 times might be not enough to get an accurate precision.
   // see for example bug https://savannah.cern.ch/bugs/?30246
   // now break loop when difference is less than 1E-15
   // t.b.d: use directly the beta distribution quantile

   for (int loop=0; loop<50; loop++) {
      test = 0.5*(too_high + too_low);
      integral = Beta_ab(test, high, k, N);
      if (integral > c)  too_low = test;
      else too_high = test;
      if ( TMath::Abs(integral - c) <= 1.E-15) break;
   }
   return test;
}
//______________________________________________________________________________

double Interval(double low, int k, int N, double conflevel) const
{
   // Return the length of the interval starting at low
   // that contains CONFLEVEL of the x^GLOBAL_k*(1-x)^(GLOBAL_N-GLOBAL_k)
   // distribution.
   // If there is no sufficient interval starting at low, we return 2.0

  double high = SearchUpper(low, k, N, conflevel);
   if (high == -1.0) return 2.0; //  so that this won't be the shortest interval
   return (high - low);
}
//______________________________________________________________________________
double Beta_ab(double a, double b, int k, int N) const
{
   // Calculates the fraction of the area under the
   // curve x^k*(1-x)^(N-k) between x=a and x=b

   if (a == b) return 0;    // don't bother integrating over zero range
   int c1 = k+1;
   int c2 = N-k+1;
   return Ibetai(c1,c2,b)-Ibetai(c1,c2,a);
}


//______________________________________________________________________________
double Ibetai(double a, double b, double x) const
{
   // Calculates the incomplete beta function  I_x(a,b); this is
   // the incomplete beta function divided by the complete beta function

   double bt;
   if (x < 0.0 || x > 1.0) {
      Error("Ibetai","Illegal x in routine Ibetai: x = %g",x);
      return 0;
   }
   if (x == 0.0 || x == 1.0)
      bt=0.0;
   else
      bt=TMath::Exp(TMath::LnGamma(a+b)-TMath::LnGamma(a)-TMath::LnGamma(b)+a*log(x)+b*log(1.0-x));

   if (x < (a+1.0)/(a+b+2.0))
      return bt*TMath::BetaCf(x,a,b)/a;
   else
      return 1.0-bt*TMath::BetaCf(1-x,b,a)/b;
}


//______________________________________________________________________________
double Betai(double a, double b, double x) const
{
   // Calculates the incomplete beta function B_x(a,b), as defined
   // in Gradshteyn and Ryzhik (4th edition) 8.391

   // calculates the complete beta function
   double beta = TMath::Exp(TMath::LnGamma(a)+TMath::LnGamma(b)-TMath::LnGamma(a+b));
   return Ibetai(a,b,x)*beta;
}


//______________________________________________________________________________
double Brent(double ax, double bx, double cx, double tol, double *xmin, int k, int N, double conflevel) const
{
   // Implementation file for the numerical equation solver library.
   // This includes root finding and minimum finding algorithms.
   // Adapted from Numerical Recipes in C, 2nd edition.
   // Translated to C++ by Marc Paterno

   const int    kITMAX = 100;
   const double kCGOLD = 0.3819660;
   const double kZEPS  = 1.0e-10;

   int iter;
   double a,b,d=0.,etemp,fu,fv,fw,fx,p,q,r,tol1,tol2,u,v,w,x,xm;
   double e=0.0;

   a=(ax < cx ? ax : cx);
   b=(ax > cx ? ax : cx);
   x=w=v=bx;
   fw=fv=fx=Interval(x, k, N, conflevel);
   for (iter=1;iter<=kITMAX;iter++) {
      xm=0.5*(a+b);
      tol2=2.0*(tol1=tol*TMath::Abs(x)+kZEPS);
      if (TMath::Abs(x-xm) <= (tol2-0.5*(b-a))) {
         *xmin=x;
         return fx;
      }
      if (TMath::Abs(e) > tol1) {
         r=(x-w)*(fx-fv);
         q=(x-v)*(fx-fw);
         p=(x-v)*q-(x-w)*r;
         q=2.0*(q-r);
         if (q > 0.0) p = -p;
         q=TMath::Abs(q);
         etemp=e;
         e=d;
         if (TMath::Abs(p) >= TMath::Abs(0.5*q*etemp) || p <= q*(a-x) || p >= q*(b-x)) d=kCGOLD*(e=(x >= xm ? a-x : b-x));
         else {
            d=p/q;
            u=x+d;
            if (u-a < tol2 || b-u < tol2) d=TMath::Sign(tol1,xm-x);
         }
      } else {
         d=kCGOLD*(e=(x >= xm ? a-x : b-x));
      }
      u=(TMath::Abs(d) >= tol1 ? x+d : x+TMath::Sign(tol1,d));
      fu=Interval(u, k, N, conflevel);
      if (fu <= fx) {
         if (u >= x) a=x; else b=x;
         v  = w;
         w  = x;
         x  = u;
         fv = fw;
         fw = fx;
         fx = fu;
      } else {
         if (u < x) a=u; else b=u;
         if (fu <= fw || w == x) {
            v=w;
            w=u;
            fv=fw;
            fw=fu;
         } else if (fu <= fv || v == x || v == w) {
            v=u;
            fv=fu;
         }
      }
   }
   Error("Brent","Too many interations");
   *xmin=x;
   return fx;
}


// //______________________________________________________________________________
// void ComputeRange(Double_t &xmin, Double_t &ymin, Double_t &xmax, Double_t &ymax) const
// {
//    // Compute Range

//    TGraph::ComputeRange(xmin,ymin,xmax,ymax);

//    for (Int_t i=0;i<fNpoints;i++) {
//       if (fX[i] -fEXlow[i] < xmin) {
//          if (gPad && gPad->GetLogx()) {
//             if (fEXlow[i] < fX[i]) xmin = fX[i]-fEXlow[i];
//             else                   xmin = TMath::Min(xmin,fX[i]/3);
//          } else {
//             xmin = fX[i]-fEXlow[i];
//          }
//       }
//       if (fX[i] +fEXhigh[i] > xmax) xmax = fX[i]+fEXhigh[i];
//       if (fY[i] -fEYlow[i] < ymin) {
//          if (gPad && gPad->GetLogy()) {
//             if (fEYlow[i] < fY[i]) ymin = fY[i]-fEYlow[i];
//             else                   ymin = TMath::Min(ymin,fY[i]/3);
//          } else {
//             ymin = fY[i]-fEYlow[i];
//          }
//       }
//       if (fY[i] +fEYhigh[i] > ymax) ymax = fY[i]+fEYhigh[i];
//    }
// }


// //______________________________________________________________________________
// void CopyAndRelease(Double_t **newarrays,
//                                        Int_t ibegin, Int_t iend, Int_t obegin)
// {
//    // Copy and release.

//    CopyPoints(newarrays, ibegin, iend, obegin);
//    if (newarrays) {
//       delete[] fEXlow;
//       fEXlow = newarrays[0];
//       delete[] fEXhigh;
//       fEXhigh = newarrays[1];
//       delete[] fEYlow;
//       fEYlow = newarrays[2];
//       delete[] fEYhigh;
//       fEYhigh = newarrays[3];
//       delete[] fX;
//       fX = newarrays[4];
//       delete[] fY;
//       fY = newarrays[5];
//       delete[] newarrays;
//    }
// }


// //______________________________________________________________________________
// Bool_t CopyPoints(Double_t **arrays,
//                                      Int_t ibegin, Int_t iend, Int_t obegin)
// {
//    // Copy errors from fE*** to arrays[***]
//    // or to f*** Copy points.

//    if (TGraph::CopyPoints(arrays ? arrays+4 : 0, ibegin, iend, obegin)) {
//       Int_t n = (iend - ibegin)*sizeof(Double_t);
//       if (arrays) {
//          memmove(&arrays[0][obegin], &fEXlow[ibegin], n);
//          memmove(&arrays[1][obegin], &fEXhigh[ibegin], n);
//          memmove(&arrays[2][obegin], &fEYlow[ibegin], n);
//          memmove(&arrays[3][obegin], &fEYhigh[ibegin], n);
//       } else {
//          memmove(&fEXlow[obegin], &fEXlow[ibegin], n);
//          memmove(&fEXhigh[obegin], &fEXhigh[ibegin], n);
//          memmove(&fEYlow[obegin], &fEYlow[ibegin], n);
//          memmove(&fEYhigh[obegin], &fEYhigh[ibegin], n);
//       }
//       return kTRUE;
//    } else {
//       return kFALSE;
//    }
// }


// //______________________________________________________________________________
// Bool_t CtorAllocate(void)
// {
//    // Should be called from ctors after fNpoints has been set

//    if (!fNpoints) {
//       fEXlow = fEYlow = fEXhigh = fEYhigh = 0;
//       return kFALSE;
//    }
//    fEXlow = new Double_t[fMaxSize];
//    fEYlow = new Double_t[fMaxSize];
//    fEXhigh = new Double_t[fMaxSize];
//    fEYhigh = new Double_t[fMaxSize];
//    return kTRUE;
// }


// //______________________________________________________________________________
// void Efficiency(int k, int N, double conflevel,
//       double& mode, double& low, double& high) const
// {
//    // Calculate the shortest central confidence interval containing the required
//    // probability content.
//    // Interval(low) returns the length of the interval starting at low
//    // that contains CONFLEVEL probability. We use Brent's method,
//    // except in two special cases: when k=0, or when k=N
//    // Main driver routine
//    // Author: Marc Paterno

//    //If there are no entries, then we know nothing, thus return the prior...
//    if (0==N) {
//       mode = .5; low = 0.0; high = 1.0;
//       return;
//    }

//    // Calculate the most probable value for the posterior cross section.
//    // This is easy, 'cause it is just k/N
//    double efficiency = (double)k/N;

//    double low_edge;
//    double high_edge;

//    if (k == 0) {
//       low_edge = 0.0;
//       high_edge = SearchUpper(low_edge, k, N, conflevel);
//    } else if (k == N) {
//       high_edge = 1.0;
//       low_edge = SearchLower(high_edge, k, N, conflevel);
//    } else {
//       GLOBAL_k = k;
//       GLOBAL_N = N;
//       CONFLEVEL = conflevel;
//       Brent(0.0, 0.5, 1.0, 1.0e-9, &low_edge);
//       high_edge = low_edge + Interval(low_edge);
//    }

//    // return output
//    mode = efficiency;
//    low = low_edge;
//    high = high_edge;
// }


// //______________________________________________________________________________
// void FillZero(Int_t begin, Int_t end,
//                                  Bool_t from_ctor)
// {
//    // Set zero values for point arrays in the range [begin, end)

//    if (!from_ctor) {
//       TGraph::FillZero(begin, end, from_ctor);
//    }
//    Int_t n = (end - begin)*sizeof(Double_t);
//    memset(fEXlow + begin, 0, n);
//    memset(fEXhigh + begin, 0, n);
//    memset(fEYlow + begin, 0, n);
//    memset(fEYhigh + begin, 0, n);
// }


// //______________________________________________________________________________
// Double_t GetErrorX(Int_t i) const
// {
//    // This function is called by GraphFitChisquare.
//    // It returns the error along X at point i.

//    if (i < 0 || i >= fNpoints) return -1;
//    if (!fEXlow && !fEXhigh) return -1;
//    Double_t elow=0, ehigh=0;
//    if (fEXlow)  elow  = fEXlow[i];
//    if (fEXhigh) ehigh = fEXhigh[i];
//    return TMath::Sqrt(0.5*(elow*elow + ehigh*ehigh));
// }


// //______________________________________________________________________________
// Double_t GetErrorY(Int_t i) const
// {
//    // This function is called by GraphFitChisquare.
//    // It returns the error along Y at point i.

//    if (i < 0 || i >= fNpoints) return -1;
//    if (!fEYlow && !fEYhigh) return -1;
//    Double_t elow=0, ehigh=0;
//    if (fEYlow)  elow  = fEYlow[i];
//    if (fEYhigh) ehigh = fEYhigh[i];
//    return TMath::Sqrt(0.5*(elow*elow + ehigh*ehigh));
// }


// //______________________________________________________________________________
// Double_t GetErrorXhigh(Int_t i) const
// {
//    // Get high error on X.

//    if (i<0 || i>fNpoints) return -1;
//    if (fEXhigh) return fEXhigh[i];
//    return -1;
// }


// //______________________________________________________________________________
// Double_t GetErrorXlow(Int_t i) const
// {
//    // Get low error on X.

//    if (i<0 || i>fNpoints) return -1;
//    if (fEXlow) return fEXlow[i];
//    return -1;
// }


// //______________________________________________________________________________
// Double_t GetErrorYhigh(Int_t i) const
// {
//    // Get high error on Y.

//    if (i<0 || i>fNpoints) return -1;
//    if (fEYhigh) return fEYhigh[i];
//    return -1;
// }


// //______________________________________________________________________________
// Double_t GetErrorYlow(Int_t i) const
// {
//    // Get low error on Y.

//    if (i<0 || i>fNpoints) return -1;
//    if (fEYlow) return fEYlow[i];
//    return -1;
// }


// //______________________________________________________________________________
// double Interval(double low) const
// {
//    // Return the length of the interval starting at low
//    // that contains CONFLEVEL of the x^GLOBAL_k*(1-x)^(GLOBAL_N-GLOBAL_k)
//    // distribution.
//    // If there is no sufficient interval starting at low, we return 2.0

//    double high = SearchUpper(low, GLOBAL_k, GLOBAL_N, CONFLEVEL);
//    if (high == -1.0) return 2.0; //  so that this won't be the shortest interval
//    return (high - low);
// }


// //______________________________________________________________________________
// void Print(Option_t *) const
// {
//    // Print graph and errors values.

//    for (Int_t i=0;i<fNpoints;i++) {
//       printf("x[%d]=%g, y[%d]=%g, exl[%d]=%g, exh[%d]=%g, eyl[%d]=%g, eyh[%d]=%g\n"
//          ,i,fX[i],i,fY[i],i,fEXlow[i],i,fEXhigh[i],i,fEYlow[i],i,fEYhigh[i]);
//    }
// }


// //______________________________________________________________________________
// void SavePrimitive(ostream &out, Option_t *option /*= ""*/)
// {
//     // Save primitive as a C++ statement(s) on output stream out

//    char quote = '"';
//    out<<"   "<<endl;
//    if (gROOT->ClassSaved(Class())) {
//       out<<"   ";
//    } else {
//       out<<"   TGraphAsymmErrors *";
//    }
//    out<<"grae = new TGraphAsymmErrors("<<fNpoints<<");"<<endl;
//    out<<"   grae->SetName("<<quote<<GetName()<<quote<<");"<<endl;
//    out<<"   grae->SetTitle("<<quote<<GetTitle()<<quote<<");"<<endl;

//    SaveFillAttributes(out,"grae",0,1001);
//    SaveLineAttributes(out,"grae",1,1,1);
//    SaveMarkerAttributes(out,"grae",1,1,1);

//    for (Int_t i=0;i<fNpoints;i++) {
//       out<<"   grae->SetPoint("<<i<<","<<fX[i]<<","<<fY[i]<<");"<<endl;
//       out<<"   grae->SetPointError("<<i<<","<<fEXlow[i]<<","<<fEXhigh[i]<<","<<fEYlow[i]<<","<<fEYhigh[i]<<");"<<endl;
//    }

//    static Int_t frameNumber = 0;
//    if (fHistogram) {
//       frameNumber++;
//       TString hname = fHistogram->GetName();
//       hname += frameNumber;
//       fHistogram->SetName(hname.Data());
//       fHistogram->SavePrimitive(out,"nodraw");
//       out<<"   grae->SetHistogram("<<fHistogram->GetName()<<");"<<endl;
//       out<<"   "<<endl;
//    }

//    // save list of functions
//    TIter next(fFunctions);
//    TObject *obj;
//    while ((obj=next())) {
//       obj->SavePrimitive(out,"nodraw");
//       if (obj->InheritsFrom("TPaveStats")) {
//          out<<"   grae->GetListOfFunctions()->Add(ptstats);"<<endl;
//          out<<"   ptstats->SetParent(grae->GetListOfFunctions());"<<endl;
//       } else {
//          out<<"   grae->GetListOfFunctions()->Add("<<obj->GetName()<<");"<<endl;
//       }
//    }

//    const char *l = strstr(option,"multigraph");
//    if (l) {
//       out<<"   multigraph->Add(grae,"<<quote<<l+10<<quote<<");"<<endl;
//    } else {
//       out<<"   grae->Draw("<<quote<<option<<quote<<");"<<endl;
//    }
// }


// //______________________________________________________________________________
// double SearchLower(double high, int k, int N, double c) const
// {
//    // Integrates the binomial distribution with
//    // parameters k,N, and determines what is the lower edge of the
//    // integration region which ends at high, and which contains
//    // probability content c. If a lower limit is found, the value is
//    // returned. If no solution is found, the -1 is returned.
//    // check to see if there is any solution by verifying that the integral down
//    // to the minimum lower limit (0) is greater than c

//    double integral = Beta_ab(0.0, high, k, N);
//    if (integral == c) return 0.0;      // lucky -- this is the solution
//    if (integral < c) return -1.0;      // no solution exists
//    double too_low = 0.0;               // lower edge estimate
//    double too_high = high;
//    double test;

//    // use a bracket-and-bisect search
//    // LM: looping 20 times might be not enough to get an accurate precision.
//    // see for example bug https://savannah.cern.ch/bugs/?30246
//    // now break loop when difference is less than 1E-15
//    // t.b.d: use directly the beta distribution quantile

//    for (int loop=0; loop<50; loop++) {
//       test = 0.5*(too_high + too_low);
//       integral = Beta_ab(test, high, k, N);
//       if (integral > c)  too_low = test;
//       else too_high = test;
//       if ( TMath::Abs(integral - c) <= 1.E-15) break;
//    }
//    return test;
// }


// //______________________________________________________________________________
// double SearchUpper(double low, int k, int N, double c) const
// {
//    // Integrates the binomial distribution with
//    // parameters k,N, and determines what is the upper edge of the
//    // integration region which starts at low which contains probability
//    // content c. If an upper limit is found, the value is returned. If no
//    // solution is found, -1 is returned.
//    // check to see if there is any solution by verifying that the integral up
//    // to the maximum upper limit (1) is greater than c

//    double integral = Beta_ab(low, 1.0, k, N);
//    if (integral == c) return 1.0;    // lucky -- this is the solution
//    if (integral < c) return -1.0;    // no solution exists
//    double too_high = 1.0;            // upper edge estimate
//    double too_low = low;
//    double test;

//    // use a bracket-and-bisect search
//    // LM: looping 20 times might be not enough to get an accurate precision.
//    // see for example bug https://savannah.cern.ch/bugs/?30246
//    // now break loop when difference is less than 1E-15
//    // t.b.d: use directly the beta distribution quantile

//    for (int loop=0; loop<50; loop++) {
//       test = 0.5*(too_low + too_high);
//       integral = Beta_ab(low, test, k, N);
//       if (integral > c)  too_high = test;
//       else too_low = test;
//       if ( TMath::Abs(integral - c) <= 1.E-15) break;
//    }
//    return test;
// }


// //______________________________________________________________________________
// void SetPointError(Double_t exl, Double_t exh, Double_t eyl, Double_t eyh)
// {
//    // Set ex and ey values for point pointed by the mouse.

//    Int_t px = gPad->GetEventX();
//    Int_t py = gPad->GetEventY();

//    //localize point to be deleted
//    Int_t ipoint = -2;
//    Int_t i;
//    // start with a small window (in case the mouse is very close to one point)
//    for (i=0;i<fNpoints;i++) {
//       Int_t dpx = px - gPad->XtoAbsPixel(gPad->XtoPad(fX[i]));
//       Int_t dpy = py - gPad->YtoAbsPixel(gPad->YtoPad(fY[i]));
//       if (dpx*dpx+dpy*dpy < 25) {ipoint = i; break;}
//    }
//    if (ipoint == -2) return;

//    fEXlow[ipoint]  = exl;
//    fEYlow[ipoint]  = eyl;
//    fEXhigh[ipoint] = exh;
//    fEYhigh[ipoint] = eyh;
//    gPad->Modified();
// }


// //______________________________________________________________________________
// void SetPointError(Int_t i, Double_t exl, Double_t exh, Double_t eyl, Double_t eyh)
// {
//    // Set ex and ey values for point number i.

//    if (i < 0) return;
//    if (i >= fNpoints) {
//    // re-allocate the object
//       SetPoint(i,0,0);
//    }
//    fEXlow[i]  = exl;
//    fEYlow[i]  = eyl;
//    fEXhigh[i] = exh;
//    fEYhigh[i] = eyh;
// }


// //______________________________________________________________________________
// void SetPointEXlow(Int_t i, Double_t exl)
// {
//    // Set EXlow for point i

//    if (i < 0) return;
//    if (i >= fNpoints) {
//    // re-allocate the object
//       SetPoint(i,0,0);
//    }
//    fEXlow[i]  = exl;
// }


// //______________________________________________________________________________
// void SetPointEXhigh(Int_t i, Double_t exh)
// {
//    // Set EXhigh for point i

//    if (i < 0) return;
//    if (i >= fNpoints) {
//    // re-allocate the object
//       SetPoint(i,0,0);
//    }
//    fEXhigh[i]  = exh;
// }


// //______________________________________________________________________________
// void SetPointEYlow(Int_t i, Double_t eyl)
// {
//    // Set EYlow for point i

//    if (i < 0) return;
//    if (i >= fNpoints) {
//    // re-allocate the object
//       SetPoint(i,0,0);
//    }
//    fEYlow[i]  = eyl;
// }


// //______________________________________________________________________________
// void SetPointEYhigh(Int_t i, Double_t eyh)
// {
//    // Set EYhigh for point i

//    if (i < 0) return;
//    if (i >= fNpoints) {
//    // re-allocate the object
//       SetPoint(i,0,0);
//    }
//    fEYhigh[i]  = eyh;
// }


// //______________________________________________________________________________
// void Streamer(TBuffer &b)
// {
//    // Stream an object of class TGraphAsymmErrors.

//    if (b.IsReading()) {
//       UInt_t R__s, R__c;
//       Version_t R__v = b.ReadVersion(&R__s, &R__c);
//       if (R__v > 2) {
//          b.ReadClassBuffer(Class(), this, R__v, R__s, R__c);
//          return;
//       }
//       //====process old versions before automatic schema evolution
//       TGraph::Streamer(b);
//       fEXlow  = new Double_t[fNpoints];
//       fEYlow  = new Double_t[fNpoints];
//       fEXhigh = new Double_t[fNpoints];
//       fEYhigh = new Double_t[fNpoints];
//       if (R__v < 2) {
//          Float_t *exlow  = new Float_t[fNpoints];
//          Float_t *eylow  = new Float_t[fNpoints];
//          Float_t *exhigh = new Float_t[fNpoints];
//          Float_t *eyhigh = new Float_t[fNpoints];
//          b.ReadFastArray(exlow,fNpoints);
//          b.ReadFastArray(eylow,fNpoints);
//          b.ReadFastArray(exhigh,fNpoints);
//          b.ReadFastArray(eyhigh,fNpoints);
//          for (Int_t i=0;i<fNpoints;i++) {
//             fEXlow[i]  = exlow[i];
//             fEYlow[i]  = eylow[i];
//             fEXhigh[i] = exhigh[i];
//             fEYhigh[i] = eyhigh[i];
//          }
//          delete [] eylow;
//          delete [] exlow;
//          delete [] eyhigh;
//          delete [] exhigh;
//       } else {
//          b.ReadFastArray(fEXlow,fNpoints);
//          b.ReadFastArray(fEYlow,fNpoints);
//          b.ReadFastArray(fEXhigh,fNpoints);
//          b.ReadFastArray(fEYhigh,fNpoints);
//       }
//       b.CheckByteCount(R__s, R__c, IsA());
//       //====end of old versions

//    } else {
//       b.WriteClassBuffer(Class(),this);
//    }
// }


// //______________________________________________________________________________
// void SwapPoints(Int_t pos1, Int_t pos2)
// {
//    // Swap points.

//    SwapValues(fEXlow,  pos1, pos2);
//    SwapValues(fEXhigh, pos1, pos2);
//    SwapValues(fEYlow,  pos1, pos2);
//    SwapValues(fEYhigh, pos1, pos2);
//    TGraph::SwapPoints(pos1, pos2);
// }
