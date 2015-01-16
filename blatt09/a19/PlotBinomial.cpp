/*
 * Rechnernutzung in der Physik
 * WS 2014/2015
 *
 * Aufgabe 19
 * Binomialverteilung und Nachweiseffizienz
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

void PlotBinomial();

int main() {
  PlotBinomial();
  return 0;
}
#endif


// Gibt aus n Versuchen Anzahl der Treffer mit Wt. prob zurueck.
Int_t RandomBinom(Int_t n, Double_t prob) {
    Int_t result = 0;

    for(int i = 0; i < n; i++) {
        // globalen prg verwenden
        // Mersenne-Twister aus TRandom3
        if(gRandom->Rndm() < prob) {
            result++;
        }
    }
    return result;
}

Double_t BinomialDist(Double_t *values, Double_t *parameters) {
    Int_t k = values[0];
    Int_t n = parameters[0];
    Double_t prob = parameters[1];
    Int_t iter = parameters[2];

    // Verteilung berechnen und zurückgeben
    return TMath::Binomial(n, k) * TMath::Power(prob, k) * TMath::Power(1-prob, n-k) * iter;
}

void PlotBinomial() {

    const int n = 100;
    const int iter = 100000;
    const int nBins = 100;
    Double_t prob1 = 0.75;
    Double_t prob2 = 0.98;

    // Bins erzeugen
    TH1I *binom75 = new TH1I("binom75", "binomial distribution from random numbers", n, 0, 100);
    TH1I *binom98 = new TH1I("binom98", "binomial distribution from random numbers", n, 0, 100);

    for(int i = 0; i < iter; i++) {
        binom75->Fill(RandomBinom(n, prob1));
        binom98->Fill(RandomBinom(n, prob2));
    }

    // Funktionen erstellen
    TF1 *f75 = new TF1("f75", BinomialDist, 0, 100, 3);
    f75->SetParameter(0, n);
    f75->SetParameter(1, prob1);
    f75->SetParameter(2, iter);
    TF1 *f98 = new TF1("f98", BinomialDist, 0, 100, 3);
    f98->SetParameter(0, n);
    f98->SetParameter(1, prob2);
    f98->SetParameter(2, iter);

    // Statistiken deaktivieren, damit sie nicht das Histogramm verdecken
    binom75->SetStats(false);
    binom98->SetStats(false);

    // Plots erzeugen
    TCanvas *canvas = new TCanvas("canv", "binomial", 1200, 800);
    // Histogramm und Verteilung einzeichnen
    binom75->SetFillColor(18);
    binom75->Draw();
    f75->SetNpx(5000);
    f75->Draw("same");
    canvas->SaveAs("genplot-binom-75.pdf");

    binom98->SetFillColor(18);
    binom98->Draw();
    f98->SetNpx(5000);
    f98->Draw("same");
    canvas->SaveAs("genplot-binom-98.pdf");
}
