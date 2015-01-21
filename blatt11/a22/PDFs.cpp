/*
 * Rechnernutzung in der Physik
 * WS 2014/2015
 *
 * Aufgabe 22
 * Zufallszahlen mit beliebiger Verteilungsdichte
 */

/***************************************************************************
 * --------------------------------------------------------------------------
 * generation of arbitrary  probability density functions (PDFs)
 *    - transformation of uniform random numbers 
 *    - accept-reject method
 *    - accept-reject with non-uniform random numbers (importance sampling) 
 *    - histogram method
 * --------------------------------------------------------------------------
 *  adapted from initial version by Klaus Rabbertz from June 2005
 *
 * modification log:
 * kr, 06.07.2006: Removed explicit ex11 naming
 * as, 07.06.2008: Various changes
 * gq, 04.01.2011: some adaptions 
 * gq, 04.01.2014: added importance sampling and histogram template
 ***************************************************************************/

// headers needed for compilation, may be ommitted in interpreter mode
#include "TFile.h" 
#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TRandom.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "TMath.h"

// Function to generically implement the acceptance-rejection method. 
void AcceptReject (TH1F *histo, Float_t (*f)(Float_t x,Float_t p), Float_t p,
	    Float_t xmin, Float_t xmax, Float_t (*t)(Float_t u), int NumRand) {
  /* transform uniform random numbers to numbers following a distribution
   * described by f
   * Input variables: 
   * histo  : ID of histogram to fill
   * f      : function the random numbers should follow
   * p      : parameters of f
   * xmin   : left border of interval
   * xmax   : right border of interval
   * t      : function used to transform uniform random numbers
   * NumRand: number of random numbers to generate 
   */

    // generate random numbers until enough numbers have been accepted
    int i = 0;
    while(i < NumRand) {
        // generate (uniform) random numbers in interval [xmin, xmax]
        Double_t randUniform = (xmax - xmin) * gRandom->Rndm() + xmin;
        // do not transform numbers if transformation function is null pointer
        Double_t randTransf = (t != nullptr) ? t(randUniform) : randUniform;

        // accept generated number with probability f(rand, p)
        // TODO: use while loop inside for loop instead of while loop with outer index
        if(gRandom->Rndm() < f(randTransf, p)) {
            histo->Fill(randTransf);
            i++;
        }
    }
}

// functions:
Float_t f1(Float_t x, Float_t p) {
    return (-1 <= x && x <= 1) ? p*(1 + TMath::Power(x, 2)) : 0;
}
Double_t f1(Double_t x[], Double_t par[]) {
    return f1(x[0], par[0]);
}

Float_t sin2(Float_t x, Float_t omega) {
    return x >= 0 ? TMath::Power(TMath::Sin(omega*x), 2) : 0;   
} // exercise 3

Double_t sin2exp(Double_t *x, Double_t *par) {
    return 5./2. * par[1] * sin2(x[0], par[0]) * TMath::Exp(-x[0]);
}

  // transformations of uniform random numbers
Float_t transform_id(Float_t r) {
    return r;  // identity
}

Float_t transform_exp(Float_t r) {
    //return 5./2.*TMath::Exp(-r);
    return -TMath::Log(r);
} // exponential

Double_t cauchyDistribution(Double_t *x, Double_t *par) {
    return par[0]/TMath::Pi()*1./(1. + TMath::Power(x[0], 2));
}

int PDFs() {
  Int_t NumRand=10000;  // Number of random number to be filled
  

  //------------------------------------------------------------------------

  Float_t pi=TMath::Pi();
  Float_t r=0.;

  //------------------------------------------------------------------------

  // Exercise 1  Fill histogram h100 with 3/8(1+x^2) 
  //             using acceptance/rejection method
  TH1F *h100 = 
      new TH1F("h100", "distribution of random numbers", 50, -1, 1);

  AcceptReject(h100, f1, 3./8., -1, 1, nullptr, 10000);

  TF1 *f100 = new TF1("f1", f1, -1, 1, 1);
  // TODO: make this generic, factor out N and bin width
  f100->SetParameter(0, 10000*2/50.*3./8.);
  //------------------------------------------------------------------------

  // Exercise 2  Fill histogram 200 with Cauchy-distribution 
  //             using the transformation method

  TH1F *h200 = new TH1F("h200", "cauchy distribution", 50, -10, 10);

  for(int i = 0; i < 10000; i++) {
      h200->Fill(-1./TMath::Tan(pi*gRandom->Rndm()));
  }

  TF1 *f200 = new TF1("cauchy", cauchyDistribution, -10, 10, 1);
  f200->SetParameter(0, 10000*20/50); // TODO: see above


  //------------------------------------------------------------------------

  // Exercise 3 Fill histogram h300 with sin2*exp using 
  //              transformation and accept-reject method.
  TH1F *h300 = new TH1F("h300", "sin-exp distribution", 50, 0, 2*pi);

  AcceptReject(h300, sin2, 1., 0, 1, transform_exp, 10000);

  TF1 *f300 = new TF1("f300", sin2exp, 0, 2*pi, 2);
  f300->SetParameter(0, 1.);
  f300->SetParameter(1, 10000*2*pi/50); // TODO:see above

  //------------------------------------------------------------------------


    int N4 = 20000; // number of random numbers to generate

  // Exercise 4: random sample from histogram
   // read histogram data from file
  Float_t hdat[100]={};// an array of sufficient length, initialized to 0
  std::ifstream inp;
  inp.open("elefant.dat");
  float x;  int i=0;
  while ( !(inp >> x ) == 0 ) {
    hdat[i]=x; i++;
  }
  Int_t nbins=i;
  std::cout << "read " << nbins << " numbers" << std::endl;

  // calculate CDF of distribution from file
  Double_t CDFData[nbins];
  Double_t norm = 0;
  for(int i = 0; i < nbins; i++) {
      CDFData[i] = (i == 0) ? hdat[0] : hdat[i] + CDFData[i-1];
      norm += hdat[i];
  }
  // norm
  for(int i = 0; i < nbins; i++) {
      CDFData[i] /= norm;
  }
  // fit all data into histogram
  // CDFData[nbins-1] = 1;

  TH1F *h400 = new TH1F("h400", "empiric distribution", nbins, 0, nbins);
  TH1F *hElefant = new TH1F("hElefant", "empiric distribution", nbins, 0, nbins);
  for(int i = 0; i < nbins; i++) {
      hElefant->SetBinContent(i, N4/norm*hdat[i]);
  }

  std::cout << "norm: " << norm << std::endl;

  // generate random numbers and fill into correct bin (CDF)
  for(int i = 0; i < N4; i++) {
      Double_t rand = gRandom->Rndm();

      int bin = 0;
      // search for appropriate bin
      while(rand > CDFData[bin]) {
          bin++;
      }
      h400->Fill((Double_t)bin - 0.5);
  }



  //------------------------------------------------------------------------

  // finally, draw everything
  TCanvas* c = new TCanvas("c","Canvas",0, 0, 1200, 800);
  c->Divide(2,2);
  c->cd(1);
  h100->DrawCopy();
  f100->Draw("same");
  c->cd(2);
  h200->DrawCopy();
  f200->Draw("same");
  c->cd(3);
  h300->DrawCopy();
  f300->Draw("same");
  c->cd(4);
  h400->DrawCopy();
  hElefant->SetLineColor(kRed);
  hElefant->Draw("same");
  c->Update();

  c->SaveAs("histograms.pdf");
  // eventually, create a ROOT file.
  //TFile hfile("pdfs.root","RECREATE","pdfs");
  // Save desired histograms in the ROOT file and close it.
  //h100->Write();
  //h200->Write();
  //h300->Write();
  //h400->Write();
  //hfile.Close();

  return 0;
}                 

//-------------------------------------------------------------------------------


//______________________________________________________________________________
#ifndef __CINT__      
int main()
{
  PDFs();
  return 0;
}
#endif                 
