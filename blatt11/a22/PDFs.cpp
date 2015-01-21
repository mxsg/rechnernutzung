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


/* Function to generically implement the acceptance-rejection method.
 * Transform uniform random numbers to numbers following a distribution
 * described by f.
 *
 * Input variables:
 * histo:   pointer to histogram to fill
 * f:       function the random numbers should follow
 * p:       parameters of f
 * xmin:    left border of interval
 * xmax:    right border of interval
 * t: 	    function used to transform uniform random numbers,
 *          numbers are not transformed if nullptr is passed
 * NumRand: number of random numbers to generate
 */
void AcceptReject (TH1F *histo, Double_t (*f)(Double_t x, Double_t p), Double_t p,
        Double_t xmin, Double_t xmax, Double_t (*t)(Double_t u), int NumRand) {

    // generate random numbers until enough numbers have been accepted
    int i = 0;
    while(i < NumRand) {
        // generate (uniform) random numbers in interval (xmin, xmax)
		Double_t rand = gRandom->Uniform(xmin, xmax);

		// transform with function t, do not transform if null pointer is passed
		if(t != nullptr) rand = t(rand);

		// accept generated number with probability f(rand, p)
        if(gRandom->Rndm() < f(rand, p)) {
			// number has been accepted, put into histogram
			// and increment count for accepted numbers
            histo->Fill(rand);
            i++;
        }
    }
}


Double_t f1(Double_t x, Double_t p) {
    return (-1 <= x && x <= 1) ? p*(1 + TMath::Power(x, 2)) : 0;
}


Double_t f1(Double_t *x, Double_t *par) {
    return f1(x[0], par[0]);
}


Double_t sin2(Double_t x, Double_t omega) {
    return x >= 0 ? TMath::Power(TMath::Sin(omega*x), 2) : 0;   
}


Double_t sin2exp(Double_t *x, Double_t *par) {
    return 5./2. * par[1] * sin2(x[0], par[0]) * TMath::Exp(-x[0]);
}


Double_t transform_exp(Double_t r) {
    return -TMath::Log(r);
}


Double_t cauchyDistribution(Double_t *x, Double_t *par) {
    return par[0]/TMath::Pi()*1./(1. + TMath::Power(x[0], 2));
}


void PDFs() {
    // Number of random number to be filled
    Int_t NumRand = 10000;
    Int_t NumBins = 50;
  
    Double_t pi = TMath::Pi();


    // Exercise 1: Fill histogram h100 with 3/8(1+x^2)
    //             using acceptance/rejection method

    TH1F *h100 =
        new TH1F("h100", "distribution of random numbers", 50, -1, 1);

    AcceptReject(h100, f1, 3./8., -1, 1, nullptr, NumRand);

    TF1 *f100 = new TF1("f1", f1, -1, 1, 1);
    f100->SetParameter(0, 3./8.*NumRand*2/NumBins);


    // Exercise 2: Fill histogram h200 with Cauchy distribution
    //             using the transformation method

    TH1F *h200 = new TH1F("h200", "cauchy distribution", 50, -10, 10);

    for(int i = 0; i < 10000; i++) {
        h200->Fill(-1./TMath::Tan(pi*gRandom->Rndm()));
    }

    TF1 *f200 = new TF1("cauchy", cauchyDistribution, -10, 10, 1);
    f200->SetParameter(0, NumRand*20/NumBins); // norm


    // Exercise 3: Fill histogram h300 with sin2*exp using
    //             transformation and accept-reject method.

    TH1F *h300 = new TH1F("h300", "sin-exp distribution", 50, 0, 2*pi);

    AcceptReject(h300, sin2, 1., 0, 1, transform_exp, 10000);

    TF1 *f300 = new TF1("f300", sin2exp, 0, 2*pi, 2);
    f300->SetParameter(0, 1.);
    f300->SetParameter(1, NumRand*2*pi/NumBins);


    // Exercise 4: Random sample from histogram
    //             read histogram data from file

    // an array of sufficient length, initialized to 0
    Double_t hdat[100] ={};
    std::ifstream inp;
    inp.open("elefant.dat");
    float x;
    int i = 0;
    while ( !(inp >> x ) == 0 ) {
        hdat[i]=x; i++;
    }

    Int_t nbins = i;
    std::cout << "read " << nbins << " numbers" << std::endl;

    // calculate CDF of distribution from file
    Double_t CDFData[nbins];
    Double_t norm = 0;
    for(int i = 0; i < nbins; i++) {
        CDFData[i] = (i == 0) ? hdat[0] : hdat[i] + CDFData[i-1];
        norm += hdat[i];
    }
    // normalize CDF
    for(int i = 0; i < nbins; i++) {
        CDFData[i] /= norm;
    }

    TH1F *h400 =
        new TH1F("h400", "random numbers with empiric distribution", nbins, 0, nbins);
    TH1F *hElefant = new TH1F("hElefant", "empiric distribution", nbins, 0, nbins);
    for(int i = 0; i < nbins; i++) {
        hElefant->SetBinContent(i, NumRand/norm*hdat[i]);
    }

    std::cout << "norm: " << norm << std::endl;

    // generate random numbers and fill into correct bin (CDF)
    for(int i = 0; i < NumRand; i++) {
        Double_t rand = gRandom->Rndm();

        int bin = 0;
        // search for appropriate bin
        while(rand > CDFData[bin]) {
            bin++;
        }
        h400->Fill((Double_t)bin - 0.5);
    }

    // finally, draw everything
    TCanvas* c = new TCanvas("c","Canvas",0, 0, 1200, 800);
    c->Divide(2,2);

    c->cd(1);
    h100->SetFillColor(18);
    h100->DrawCopy();
    f100->Draw("same");

    c->cd(2);
    h200->SetFillColor(18);
    h200->DrawCopy();
    f200->Draw("same");

    c->cd(3);
    h300->SetFillColor(18);
    h300->DrawCopy();
    f300->Draw("same");

    c->cd(4);
    h400->SetFillColor(18);
    h400->DrawCopy();
    hElefant->SetLineColor(kRed);
    hElefant->Draw("same");

    c->Update();

    c->SaveAs("histograms.pdf");

    // eventually, create a ROOT file.
    TFile hfile("pdfs.root","RECREATE","pdfs");
    // Save desired histograms in the ROOT file and close it.
    h100->Write();
    h200->Write();
    h300->Write();
    h400->Write();
    hfile.Close();
}

#ifndef __CINT__
int main() {
    PDFs();
    return 0;
}
#endif
