/*
 * Rechnernutzung in der Physik
 * WS 2014/2015
 *
 * Aufgabe 21
 * Transformierte Zufallszahlen
 */

// These include statements are needed if the program is
// run as a "stand-alone application", i.e. if it is not
// called from an interactive ROOt session.
#ifndef __CINT__d
#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TMath.h"
#include "TStyle.h"

void PlotTransformationen();

int main() {
    PlotTransformationen();
    return 0;
}
#endif                 

// gegebene Verteilungsfunktionen definieren
Double_t t1(Double_t r) { return TMath::Power(r, 2); }
Double_t t2(Double_t r) { return TMath::Exp(r); }
Double_t t3(Double_t r) { return TMath::Tan(r); }
Double_t t4(Double_t r) { return TMath::Log(1.0 + r); }

// alle vier Funktionen abhängig von Parameter kombinieren
Double_t t(Int_t k, Double_t x) {
    switch(k) {
        case 1: return t1(x);
        case 2: return t2(x);
        case 3: return t3(x);
        case 4: return t4(x);
        default: return 0.0;
    }
}

// Verteilungsdichten
Double_t d1(Double_t *val, Double_t *par) {
    Double_t x = val[0];
    Double_t norm = par[1];
    return norm/(2.0*TMath::Sqrt(x));
}

Double_t d2(Double_t *val, Double_t *par) {
    Double_t x = val[0];
    Double_t norm = par[1];
    return norm*(1.0/x);
}

Double_t d3(Double_t *val, Double_t *par) {
    Double_t x = val[0];
    Double_t norm = par[1];
    return norm/(TMath::Power(x, 2)+1);
}

Double_t d4(Double_t *val, Double_t *par) {
    Double_t x = val[0];
    Double_t norm = par[1];
    return norm*TMath::Exp(x);
}

// d-Funktionen mit Parameter kombinieren
Double_t d(Double_t *val, Double_t *par) {
    switch((int)par[0]) {
        case 1: return d1(val, par);
        case 2: return d2(val, par);
        case 3: return d3(val, par);
        case 4: return d4(val, par);
        default: return 0.0;
    }
}

void PlotTransformationen() {
    Int_t bins = 50;
    Int_t n = 100000;
    
    // Canvas zum Zeichnen
    TCanvas *canvas = new TCanvas("canvas", "", 1200, 800);
    canvas->Divide(2, 2);

    char id[20];
    char title[20];

    // ueber die Funktionen iterieren, zeichnen
    for(int i = 1; i <= 4; i++) {
        sprintf(id, "vert%d", i);
        sprintf(title, "Verteilung t%d", i);
        TH1F *hist = new TH1F(id, title, bins, t(i, 0.0), t(i, 1.0));

        for(int j = 0; j < n; j++) {
            hist->Fill(t(i, gRandom->Rndm()));
        }

        sprintf(id, "func%d", i);
        TF1 *func = new TF1(id, d, t(i, 0), t(i, 1), 2);
        func->SetParameter(0, i);
        func->SetParameter(1, n*(TMath::Abs(t(i, 1) - t(i, 0)))/bins);
    
        canvas->cd(i);
        hist->SetFillColor(18);
        hist->Draw();
        func->Draw("same");
    }
    canvas->SaveAs("genplot-a21.pdf");
}
