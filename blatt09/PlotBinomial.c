/* 
 * Gibt aus n Versuchen Anzahl der Treffer mit Wt. prob zurück
 */
Int_t randomBinom(Int_t n, Double_t prob) {
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

void binomialDist(Double_t *values, Double_t *parameters) {
    Int_t k = values[0];
    Int_t n = parameters[0];
    Double_t prob = parameters[1];
    Int_t iter = parameters[2];

    // Verteilung berechnen und zurückgeben
    return TMath::Binomial(n, k) * TMath::Power(prob, k) * TMath::Power(1-prob, n-k) * iter;
}

void PlotBinomial() {

    Int_t n = 100;
    Int_t iter = 100000;
    Double_t prob1 = 0.75;
    Double_t prob2 = 0.98;

    // Bins erzeugen
    TH1I *binom75 = new TH1I("binom75", "binomial distribution from random numbers", n, 0, 100);
    TH1I *binom98 = new TH1I("binom98", "binomial distribution from random numbers", n, 0, 100);

    for(int i = 0; i < iter; i++) {
        binom75->Fill(randomBinom(n, prob1));
        binom98->Fill(randomBinom(n, prob2));
    }

    // Funktionen erstellen
    TF1 *f75 = new TF1("f75", binomialDist, 0, 100, 3);
    f75->SetParameter(0, n);
    f75->SetParameter(1, prob1);
    f75->SetParameter(2, iter);
    TF1 *f98 = new TF1("f98", binomialDist, 0, 100, 3);
    f98->SetParameter(0, n);
    f98->SetParameter(1, prob2);
    f98->SetParameter(2, iter);

    // stats deaktivieren, damit sie nicht das Histogramm verdecken
    binom75->SetStats(false);
    binom98->SetStats(false);

    // Plots erzeugen
    TCanvas *canvas1 = new TCanvas("canv1", "binom75", 1200, 800);
    // Histogramm und Verteilung einzeichnen
    binom75->Draw();
    f75->Draw("same");
    canvas1.SaveAs("genplot-binom-75.png");

    TCanvas *canvas2 = new TCanvas("canv2", "binom98", 1200, 800);
    binom98->Draw();
    f98->Draw("same");
    canvas2.SaveAs("genplot-binom-98.png");
}
