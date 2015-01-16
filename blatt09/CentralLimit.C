/***************************************************************************
 * --------------------------------------------------------------------------
 * Template to exercise Random Numbers and CLT
 * -> Book and fill a histogram with 10000 uniform random numbers
 * --------------------------------------------------------------------------
 * adapted from Klaus Rabberts, vers. of 4.7.2006
 *
 * modification log:
 * GQ, 1.12.2013: some adjustments and cosmetics 
 ***************************************************************************/

/* Note that this file can be either used as a compiled program
 * or as a ROOT macro.
 * If it is used as a compiled program, additional include statements
 * and the definition of the main program have to be made. This is 
 * not needed if the code is used as a macro.
 */

#ifndef __CINT__      // These include-statements are needed if the program is
#include "TFile.h"    // run as a "stand-alone application", i.e. if it is not 
#include "TCanvas.h"
#include "TH1.h"      // called from an interactive ROOT session
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TMath.h"
#include "TStyle.h"
#include <math.h>


// Here we declare the functions we are goin to use later.
// Each function corresponds to one subexercise
void CentralLimit();

//______________________________________________________________________________
int main()
{
  CentralLimit();
  return 0;
}
#endif                 

Double_t GaussDist(Double_t *x, Double_t *par) {
    Double_t mu = par[0];
    Double_t sigma = par[1];
    return TMath::Exp(-TMath::Power(x[0]-mu, 2.0)/(2.0*TMath::Power(sigma, 2.0)))/
            (TMath::Sqrt(2.0*TMath::Pi())*TMath::Power(sigma, 2.0))*par[2];
}

Double_t y(int n) {
    Double_t result = 0.0;
    for(int i = 0; i < n; i++) {
        result += gRandom->Rndm();
    }
    return result;
}

Double_t z(int n) {
    return (y(n)-n/2.0)/TMath::Sqrt(n/12.0);
} 
//______________________________________________________________________________

// from here on, the code can also be used as a macro

void CentralLimit()
{
  // Create a new ROOT file.
  TFile hfile("CentraLimit.root","RECREATE","CentralLimit");

  // Create vector of pointers to 1D histograms.  
  // Each pointer points to a histogram which holds the distribution
  // of a particular series of experiments
  TH1F *hlist[21]; 

  // Book 1D histograms 
  char title[20];
  char id[5];
  for (int i=2; i<=20; i++) {
    sprintf(title, "Gaussvert./Histogramm mit n= %d",i);
    sprintf(id, "h%d", i);
    hlist[i] = new TH1F(id,title,100,-5.0,5.0);
  }

  // Define and initialize needed variables
  //Float_t random=0.0;
  //Float_t y=0.0;
  //Float_t z=0.0;

    int iterations = 100000;
    // Loop over different values of n.
    int n = 3;

    for(int i = 0; i < iterations; i++) {
        hlist[n]->Fill(z(n));
    }
    
    TF1 *fgauss = new TF1("f75", GaussDist, -5, 5, 3);
    fgauss->SetParameter(0, 0); // mu
    fgauss->SetParameter(1, 1); // sigma
    fgauss->SetParameter(2, iterations/10); // iter

    // Plots erzeugen
    TCanvas *canvas1 = new TCanvas("canv1", "n2", 1200, 800);
    // Histogramm und Verteilung einzeichnen
    hlist[n]->Draw();
    // Rasterlinien anzeigen
    canvas1->SetGrid();
    fgauss->Draw("same");
    canvas1->SaveAs("genplot-n3.pdf");

  // Save all objects in the ROOT file and close it.
  //hfile.Write();
  //hfile.Close();
}
