/*
 * Rechnernutzung in der Physik
 * WS 2014/2015
 *
 * Aufgabe 25
 * Buffonsches Nadelproblem
 */

// These include statements are needed if the program is
// run as a "stand-alone application", i.e. if it is not
// called from an interactive ROOT session.
#ifndef __CINT_
#include "TRandom.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TCanvas.h"
#include <iostream>

int PiMonteCarlo();

int main() {
  PiMonteCarlo();
  return 0;
}
#endif


double buffon(int N, double needleLength) {
    // This uses the buffon method to estimate Pi.

    // count the number of needles crossing a line
    int count = 0;

    for(int i = 0; i < N; i++) {
        // distance of lower needle end to upper line
        double yDist = gRandom->Rndm();
        // angle between lines and needle
        // because of symmetry, it is sufficient to
        // consider angles in the interval [0, Pi]
        double angle = gRandom->Uniform(TMath::Pi());
        // length of the vertical projection of the needle
        double yLen =
            needleLength*TMath::Sin(angle);

        if(yLen > yDist) count++; // the needle intersects the line
    }

    // return 0 if no needles intersecting s line have been counted,
    // estimation for pi otherwise
    return count ? 2.*needleLength*(double)N/count : 0;
}


double alternative(int N) {
    // count number of points in unit circle
    int count = 0;

    for(int i = 0; i < N; i++) {
        // generate random number in square (-1, 1) x (-1, 1)
        double x = gRandom->Uniform(-1, 1);
        double y = gRandom->Uniform(-1, 1);

        // check whether number is in unit circle
        if(x*x + y*y <= 1) count++;
    }

    // area of unit circle is pi*1^2, square 2*2:
    // probability for uniorm random number from square to be in
    // circle is pi/4
    return 4.*(double)count/N;
}


int PiMonteCarlo () {

    // first we show that the methods are working
    int N = 100000;
    double needleLength = 1.0;

    std::cout << "Proof of Principle." << std::endl;
    std::cout << "Pi is: " << std::endl;
    std::cout << TMath::Pi() << std::endl;

    std::cout << "Buffon Method says: " << std::endl;
    std::cout << buffon (N, needleLength)<< std::endl;

    std::cout << "Alternative Method says: " << std::endl;
    std::cout << alternative(N) << std::endl;

    // Make a double logarithmic plot to estimate the speed of convergence.
    // Unfortunately it turns out the differences are quite small,
    // except for extreme needle length. One method is clearly better than the other.

    static const int lengthSteps = 5;
    static const int ordersOfMag = 40;
    static const int aggregateNum = 100;

    double xList[lengthSteps+1][ordersOfMag];
    double yList[lengthSteps+1][ordersOfMag];
    // number of simulations for each N and needle length
    double yListDeviation[lengthSteps+1][ordersOfMag];
    double temp[aggregateNum];

    // estimation with Buffon's Method
    for (int i = 0; i < lengthSteps; i++) {
        for (int j = 0; j < ordersOfMag; j++) {

            int sampleSize = int(10 * pow(1.2, (j+1)));
            double needleLen = (double)(i+1)/lengthSteps;

            for(int k = 0; k < aggregateNum; k++) {
                temp[k] =
                    TMath::Abs(buffon(sampleSize, needleLen) - TMath::Pi());
            }

            xList[i][j] = sampleSize;
            // take first calculated value as value for single simulation
            yList[i][j] = temp[0];
            // calculate standard deviation of deltas for aggregateNum simulations
            yListDeviation[i][j] = TMath::RMS(aggregateNum, temp);
        }
    }

    // estimation with Alternative Method
    for (int j = 0; j < ordersOfMag; j++) {

        int sampleSize = int(10 * pow(1.2, (j+1)));
        for(int k = 0; k < aggregateNum; k++) {
            temp[k] = TMath::Abs(alternative(sampleSize)- TMath::Pi());
        }

        xList[lengthSteps][j] = sampleSize;
        yList[lengthSteps][j] = temp[0];
        yListDeviation[lengthSteps][j] = TMath::RMS(aggregateNum, temp);
    }

    // canvases to draw on
    TCanvas *canvas = new TCanvas("canv1", "canvas", 1200, 800);
    TCanvas *canvasAgg = new TCanvas("canv2", "canvas aggregate", 1200, 800);

    // use logarithmic scales for both plots
    canvas->SetLogx();
    canvas->SetLogy();
    canvasAgg->SetLogx();
    canvasAgg->SetLogy();

    // declare graph arrays for both plots
    TGraph *myGraphArray[lengthSteps+1];
    TGraph *aggGraphArray[lengthSteps+1];

    for (int i = 0; i <= lengthSteps; i++) {

        myGraphArray[i] = new TGraph(ordersOfMag, xList[i], yList[i]);
        aggGraphArray[i] = new TGraph(ordersOfMag, xList[i], yListDeviation[i]);

        myGraphArray[i]->SetLineColor(i+1);
        myGraphArray[i]->SetLineWidth(2);
        myGraphArray[i]->SetMaximum(10);
        myGraphArray[i]->SetMinimum(0.00001);
        myGraphArray[i]->SetFillColor(kWhite);

        aggGraphArray[i]->SetLineColor(i+1);
        aggGraphArray[i]->SetLineWidth(2);
        aggGraphArray[i]->SetMaximum(10);
        aggGraphArray[i]->SetMinimum(0.00001);
        aggGraphArray[i]->SetFillColor(kWhite);

        char graphTitle[250];
        if(i == 0) {
            canvas->cd();
            sprintf(graphTitle, "Estimate for Pi (Single Simulation);\
                    number of iterations in Monte Carlo methods;\
                    abs. diff. between estimate and exact value");
            myGraphArray[0]->SetTitle(graphTitle);
            myGraphArray[0]->Draw();

            canvasAgg->cd();
            sprintf(graphTitle, "Estimate for Pi (Std Dev. of n = %i Simulations);\
                    number of iterations in Monte Carlo methods;\
                    abs. diff. between estimate and exact value", aggregateNum);
            aggGraphArray[0]->SetTitle(graphTitle);
            aggGraphArray[i]->Draw();
        } else {
            canvas->cd();
            myGraphArray[i]->Draw("same");

            canvasAgg->cd();
            aggGraphArray[i]->Draw("same");
        }
    }

    // create legend
    TLegend leg(0.1, 0.1, 0.4, 0.35);

    char legend[50];
    for(int i = 0; i < lengthSteps; i++) {
        sprintf(legend, "Buffon Method with l = %i/%i x a", i+1, lengthSteps);
        leg.AddEntry(myGraphArray[i], legend);
    }
    leg.AddEntry(myGraphArray[lengthSteps], "Alternative Method");

    canvas->cd();
    leg.Draw("same");
    canvas->SaveAs("single-simulation.root");
    canvas->SaveAs("genplot-single-simulation.pdf");

    canvasAgg->cd();
    leg.Draw("same");
    canvasAgg->SaveAs("std-deviation.root");
    canvasAgg->SaveAs("genplot-std-deviation.pdf");

    return 0;
}
