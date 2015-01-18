/*
 * Rechnernutzung in der Physik
 * WS 2014/2015
 *
 * Aufgabe 23
 * Zufaellige Ereignisse und Poisson-Verteilung
 */

// These include statements are needed if the program is
// run as a "stand-alone application", i.e. if it is not
// called from an interactive ROOT session.
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

void EventsPoisson();

int main() {
  EventsPoisson();
  return 0;
}
#endif

// Exponential distribution
Double_t NormExponential(Double_t *val, Double_t *par) {
    return par[1] * par[0] * TMath::Exp(-par[0] * val[0]);
}
// Poisson distribution
Double_t NormPoisson(Double_t *x, Double_t *par) {
    int k = x[0] + 0.5;
    double norm = par[1], mu = par[0]; 
    return norm*TMath::Poisson(k, mu);
}

Double_t GetExponentialRandom(Double_t R = 1.) {
    // transform uniformly distributed random numbers
    // to obtain exponential distribution
    return -TMath::Log(gRandom->Rndm())/R;
}

void GenerateTimes(Double_t times[], int n, Double_t R = 1., Double_t t0 = 0.) {
    Double_t prevTime = t0;
    for(int i = 0; i < n; i++) {
        times[i] = prevTime;
        prevTime += GetExponentialRandom(R);
    }
}

void EventsPoisson() {

    const Int_t N = 50000; // total number of events
    const Int_t binsDelays = 50;
    const Int_t binsTimeframes = 500;
    const Double_t limRightDelays = 5.;
    const Int_t binsEventNo = 60;

    // create canvas to draw on
    TCanvas *canvas = new TCanvas("canv", "canvas", 1920, 1080);
    
    // make and fill array for generated points of time when the events occur
    Double_t events[N];
    GenerateTimes(events, N);

    // create histograms for 
    TH1F *histDelays = 
        new TH1F("delays", "distribution of delays between events", binsDelays, 0, limRightDelays);
    TH1F *histTimes = 
        new TH1F("times", "distribution of event times", binsTimeframes, 0, events[N-1]);

    // generate histogram for delays and absolute times
    for(int i = 0; i < N-1; i++) {
        histDelays->Fill(events[i+1] - events[i]);
        histTimes->Fill(events[i]);
    }
    // add last event (skipped in loop)
    histTimes->Fill(events[N-1]);

    // generate exponential function
    TF1 *exp = new TF1("exp", NormExponential, 0, 5, 2);
    exp->SetParameter(0, 1.0); // R
    exp->SetParameter(1, N*(limRightDelays/binsDelays)); // norm

    histDelays->SetFillColor(18); // gray fill for histogram
    histDelays->Draw();
    exp->Draw("same");
    canvas->SaveAs("genplot-delays.pdf");

    histTimes->SetFillColor(18); // gray fill for histogram
    histTimes->SetLineWidth(0); // show thinner lines in pdf export
    histTimes->Draw();
    canvas->SaveAs("genplot-times.pdf");

    // compute expectation values for bin contents
    Double_t expEventCount = N/(Double_t)binsTimeframes;
    Double_t dev = TMath::Sqrt(expEventCount);
    Double_t limLeftEvents = expEventCount - 3*dev - 0.5;
    Double_t limRightEvents = expEventCount + 3*dev - 0.5;
    TH1I *histBinContents =
        new TH1I("binCounts", "distribution of number of events in bins", binsEventNo,
                 limLeftEvents, limRightEvents);

    // iterate over bins from previous histogram, fill histogram with
    // number of events in each bin
    for(int i = 1; i <= binsTimeframes; i++) {
        histBinContents->Fill(histTimes->GetBinContent(i));
    }

    TF1 *poisson = new TF1("poisson", NormPoisson, limLeftEvents, limRightEvents, 2);
    poisson->SetParameter(0, expEventCount); // mu
    // TODO: figure out real norm
    // poisson->SetParameter(1, N*(limRightEvents-limLeftEvents)/binsTimeframes); // norm  
    poisson->SetParameter(1, 500);
    poisson->SetNpx(2000); // draw poisson distribution with sharp edges

    histBinContents->SetFillColor(18);
    histBinContents->Draw();
    poisson->Draw("same");
    canvas->SaveAs("genplot-bin-contents.pdf");

    // TODO: part d): simulate detector that does not count all events,
    // but misses events based on the time since the last detected event
    // model this in a separate class?
}
