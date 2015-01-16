/*
 * Rechnernutzung in der Physik
 * WS 2014/2015
 *
 * Aufgabe 20
 * Korrelationen
 */

// These include statements are needed if the program is
// run as a "stand-alone application", i.e. if it is not
// called from an interactive ROOt session.
#ifndef __CINT_
#include <iostream>
#include "TFile.h"    
#include "TH1.h"      
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TF1.h"
#include "TStyle.h"
#include "TText.h"
#include <math.h>

void Covariance();

int main() {
  Covariance();
  return 0;
}
#endif                 

// Binomial distribution
Double_t NormBinomial(Double_t *x, Double_t *par) { 
    int n = par[1];
    int k = x[0] + 0.5;;
    double p = par[0];
    double norm = par[2];;
    return norm*TMath::Binomial(n,k)*TMath::Power(p,k)*TMath::Power(1-p,n-k);
}

// Poisson distribution
Double_t NormPoisson(Double_t *x, Double_t *par) {
    int k = x[0] + 0.5;
    double norm = par[1], mu=par[0]; 
    return norm*TMath::Poisson(k, mu);
}

void Covariance() {
    const int Nrndm=10000;
    const int nBins = 5;
    const int nAggregateBins = 50;
    const int nEach = 100;
    const Double_t limLeft = -0.5;
    const Double_t limRight = 49.5;
    const Double_t width = limRight - limLeft;
    const int fillColor = 18;

    // Book a 1D histogram holding 100 random numbers between 0 and 1.
    TH1F *hran = new TH1F("hran", "n=100, nBins=5", nBins, 0, 1);

    // Create vector of pointers to 1D histograms. 
    // Each pointer points to a histogram which holds the content of a 
    // specific bin.
    TH1F *hlist[nBins]; 
  
    // Book 1D histograms for content of each bin of the above histogram
    // integer numbers in bin centres! 
    char id[20];
    char title[20];
    for(int i = 0; i < nBins; i++) {
        sprintf(id, "hran%d", i+1);
        sprintf(title, "bin %d", i+1);
        hlist[i] = new TH1F(id, title, 50, -0.5, 49.5);
        hlist[i]->SetFillColor(fillColor);
    }


    /* Exercise 20 a) */

    // fill hran with values, repeat Nrndm times, each time filling bins in list
    for(int i = 0; i < Nrndm; i++) {
        // empty bins for next iteration
        hran->Reset();
        
        for(int j = 0; j < nEach; j++) {
            hran->Fill(gRandom->Rndm());
        }

        // Unpack histogram into array content.
        Float_t *binContent = hran->GetArray();
        /* Note that the array "binCcontent" is organised as follows:
         * content[0]   = number of underflows
         * content[1]   = number of entries in first bin
         * content[2]   = number of entries in second bin
         * ...
         * content[n]   = number of entries last bin (assuming that the histogram has n bins)
         * content[n+1] = number of overflows
         */
        for(int j = 0; j < nBins; j++) {
            // [0] for underflows, [nBins+1] for overflows are not used
            hlist[j]->Fill(binContent[j+1]);
        }
    }

    TF1 *binom = new TF1("binomial", NormBinomial, limLeft, limRight, 3);
    binom->SetParameter(0, 1.0/nBins); // p
    binom->SetParameter(1, nEach); // n
    binom->SetParameter(2, (width/nAggregateBins)*Nrndm); // norm
    // draw function smoothly
    binom->SetNpx(1000);

    // draw
    TCanvas *canvas = new TCanvas("canv", "canvas", 1920, 1080);
    canvas->Divide(2, 3);
    
    for(int i = 0; i < nBins; i++) {
        canvas->cd(i+1);
        hlist[i]->Draw();
        binom->Draw("same");
    }
    canvas->SaveAs("genplot-a-all-bins.pdf");
    canvas->Divide();
    canvas->cd();
    // draw histogram for bin 2 as example
    hlist[1]->Draw();
    binom->Draw("same");
    canvas->SaveAs("genplot-a-bin2.pdf");


    /* Exercise 20 b) */
  
    /* book a 2D histogram for the scatter plot
     * TH2F is a ROOT class for 2D histograms hscat in an instance of that class
     * Arguments: TH2F("identifier", "some title", NumberBinsX, XMin, XMax, 
     *                                             NumberBinsY, YMin, YMax);
     */
    TH2F * bin2d = new TH2F("hist2d", "2D-Histogramm", 40, 0.0, 40.0, 40, 0.0, 40.0);

    /* Book a profile histogram
     * TProfile is a ROOT class for profile histograms.
     *
     * Arguments:
     * TProfile("identifier", "some title", NumberBins, XMin, XMax, YMin, YMax, Option);
     *
     * Note that YMin and YMax can be left blank.
     * The Option sets the treatment of errors (refer to the ROOT manual).
     * It can also be left blank.
     */
    TProfile *profile = new TProfile("histprofile", "Profile-Plot", 40, 0.0, 40.0);
    
    for(int i = 0; i < Nrndm; i++) {
        hran->Reset();
        for(int j = 0; j < 100; j++) {
            hran->Fill(gRandom->Rndm());
        }
        bin2d->Fill(hran->GetBinContent(2), hran->GetBinContent(4));
        profile->Fill(hran->GetBinContent(2), hran->GetBinContent(4));
    }
    cout << "correlation factor for bins 2 and 4: " 
        << bin2d->GetCorrelationFactor() << endl;

    bin2d->SetFillColor(kBlack);
    bin2d->Draw("box");;
    canvas->SaveAs("genplot-b-hist2d.pdf");

    profile->Draw();
    canvas->SaveAs("genplot-b-profile.pdf");


    /* Exercise 20 c) */

    TH1F *hranc = new TH1F("hranc", "n=2000, nBins=100", 100, 0, 1);
    TH1F *binc = new TH1F("binc", "Histogramm", 50, limLeft, limRight);

    for(int i = 0; i < Nrndm; i++) {
        hranc->Reset();
        for(int j = 0; j < 2000; j++) {
            hranc->Fill(gRandom->Rndm());
        }
        binc->Fill(hranc->GetBinContent(2));
    }
    binc->SetFillColor(fillColor);

    TF1 *funccbinom = new TF1("Binomialvert", NormBinomial, limLeft, limRight, 3);
    funccbinom->SetParameter(0, 1.0/100); // p
    funccbinom->SetParameter(1, 2000); // n
    funccbinom->SetParameter(2, (width/50.0)*Nrndm); // norm;
    // draw function smoothly
    funccbinom->SetNpx(1000);
    
    TF1 *funccpoisson = new TF1("Poissonvert", NormPoisson, limLeft, limRight, 2);
    funccpoisson->SetParameter(0, 20);
    funccpoisson->SetParameter(1, (width/50.0)*Nrndm); // norm
    // draw function smoothly
    funccpoisson->SetNpx(1000);
    funccpoisson->SetLineColor(3);

    binc->Draw();
    funccbinom->Draw("same");
    funccpoisson->Draw("same");
    canvas->BuildLegend();
    canvas->SaveAs("genplot-c-bin2.pdf");


    /* Exercise 20 d) */
    
    TH1F *hrand = new TH1F("hrand", "n=2000, nBins=100", nBins, 0, 1);
    TH1F *bind = new TH1F("bind", "Histogramm Bin 2", 50, limLeft, limRight);
    TH2F *bin2dd = new TH2F("bin2dd", "2D-Histogramm", 40, 0.0, 40.0, 40, 0.0, 40.0);
    for(int i = 0; i < Nrndm; i++) {
        hrand->Reset();
        int N = gRandom->Poisson(100);
        for(int j = 0; j < N; j++) {
            hrand->Fill(gRandom->Rndm());
        }
        bind->Fill(hrand->GetBinContent(2));
        bin2dd->Fill(hrand->GetBinContent(2), hrand->GetBinContent(4));
    }
    bind->SetFillColor(fillColor);
    cout << "correlation coefficient for bins 2 and 4: "
        << bin2dd->GetCorrelationFactor() << endl;
    
    funccpoisson->SetParameter(0, 20);
    funccpoisson->SetParameter(1, (width/50.0)*Nrndm); // norm
    bind->Draw();
    funccpoisson->Draw("same");
    canvas->SaveAs("genplot-d-bin2.pdf");

    bin2dd->SetFillColor(kBlack);
    bin2dd->Draw("box");
    canvas->SaveAs("genplot-d-hist2d.pdf");
}
