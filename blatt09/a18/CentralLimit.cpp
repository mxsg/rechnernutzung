/*
 * Rechnernutzung in der Physik
 * WS 2014/2015
 *
 * Aufgabe 18
 * Zentraler Grenzwertsatz
 */

// These include statements are needed if the program is
// run as a "stand-alone application", i.e. if it is not
// called from an interactive ROOt session.
#ifndef __CINT_
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TMath.h"
#include "TStyle.h"

void CentralLimit();

int main() {
  CentralLimit();
  return 0;
}
#endif                 

Double_t GaussDist(Double_t *x, Double_t *par) {
    Double_t mu = par[0];
    Double_t sigma = par[1];
    return TMath::Exp(-TMath::Power(x[0] - mu, 2.0)/(2.0*TMath::Power(sigma, 2.0)))/
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

void CentralLimit() {

    const int iterations = 100000; // number of iterations for the experiment
    const int histCount = 3; // number of drawn histograms
    const int nVals[] = {2, 3, 20}; // values of n for drawn histograms
    const Double_t limLeft = -5.0;
    const Double_t limRight = 5.0;
    const Double_t width = limRight - limLeft;
    const int binCount = 100;

    // Create vector of pointers to 1D histograms.  
    // Each pointer points to a histogram which holds the distribution
    // of a particular series of experiments.
    TH1F *hlist[histCount]; 

    // book and fill 1D histograms 
    char title[20];
    char id[5];
    for (int i = 0; i < histCount; i++) {
        int n = nVals[i];
        sprintf(title, "Gaussvert./Histogramm mit n=%d", n);
        sprintf(id, "h%d", n);
        hlist[i] = new TH1F(id, title, binCount, limLeft, limRight);

        // fill histogram
        for(int j = 0; j < iterations; j++) {
            hlist[i]->Fill(z(n));
        }
     }

    // generate expected distribution
    TF1 *fgauss = new TF1("f75", GaussDist, -5, 5, 3);
    fgauss->SetParameter(0, 0); // mu
    fgauss->SetParameter(1, 1); // sigma
    fgauss->SetParameter(2, iterations*(width/binCount)); // norm

    // prepare canvas for drawing
    TCanvas *canvas = new TCanvas("canv", "Canvas", 1200, 800);

    char filename[20];
    // iterate over values for n, draw and save histograms
    for(int i = 0; i < histCount; i++) {
        hlist[i]->Draw();
        // show grid lines
        canvas->SetGrid();
        fgauss->Draw("same");
        // generate filename from value of n
        sprintf(filename, "genplot-n%d.pdf", nVals[i]);
        canvas->SaveAs(filename);
    }
}
