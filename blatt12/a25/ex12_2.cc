

float buffon(int N, float needleLength){
    // This should implement the buffon method to estimate Pi.
    // you can use gRandom->Uniform(0,1) to get uniformly distributed numbers.
    int count = 0;

    for(int i = 0; i < N; i++) {
        double rand = gRandom->Rndm();

        double ylen =
            needleLength*TMath::Sin(gRandom->Uniform(2*TMath::Pi()));

        if(-ylen > rand || ylen > 1 - rand) count++;
    }

    return 2.*needleLength*(double)N/count;
}


float alternative(int N){
  // This should implement the alternative Version.
  int count = 0;

  for(int i = 0; i < N; i++) {
      // generate random numbers
      Double_t x = gRandom->Rndm();
      Double_t y = gRandom->Rndm();

      if(x*x + y*y <= 1) count++;
  }

  return 4.*(Double_t)count/N;
}


int ex12_2 (){
  //First we show, that the principle is working
  int N = 100000;
  float needleLength = 1.;

  cout << "Proof of Principle." << endl;
  cout << "Pi is : " << endl;
  cout << TMath::Pi() << endl;

  cout << "Buffon Method says: " << endl;
  cout << buffon (N, needleLength)<< endl;

  cout << "Alternative Method says: " << endl;
  cout << alternative(N) << endl;

  //Now lets make some double logarithmic plot to guess the speed of conversion.
  //Unfortunately it turns out the differences are quite small, except for extreme needle length and one method is clearly better than the other...
  static const int lengthSteps = 5;
  static const int ordersOfMag = 40;
  float xList[lengthSteps+1][ordersOfMag];
  float yList[lengthSteps+1][ordersOfMag];
  for (int ii = 0; ii < lengthSteps; ii++){
    for (int jj = 0; jj < ordersOfMag; jj++){
      xList[ii][jj] = int(10 * pow(1.2, (jj+1)));
      yList[ii][jj] = fabs(buffon(int(10 * pow(1.2, (jj+1))), 1. - 0.2* ii)- TMath::Pi());
    }
  }

  for (int jj = 0; jj < ordersOfMag; jj++){
    xList[lengthSteps][jj] = int(10 * pow(1.2, (jj+1)));
    yList[lengthSteps][jj] = fabs(alternative(int(10 * pow(1.2, (jj+1))))- TMath::Pi());
  }

  TCanvas mycan;
  mycan.cd();
  mycan.SetLogx();
  mycan.SetLogy();

  TGraph* myGraphArray [lengthSteps + 1];
  for (int ii = 0; ii < lengthSteps + 1; ii++){
    myGraphArray[ii] = new TGraph(ordersOfMag, xList[ii], yList[ii]);
    myGraphArray[ii]->SetLineColor(ii+1);
    myGraphArray[ii]->SetLineWidth(6);
    myGraphArray[ii]->SetMarkerStyle(ii);
    myGraphArray[ii]->SetMaximum(10);
    myGraphArray[ii]->SetMinimum(0.00001);
    if(ii ==0) {
      myGraphArray[ii]->Draw("AC*");
    }
    else {myGraphArray[ii]->Draw("same");
    }
  }
  mycan.SaveAs("Graph.root");
  mycan.SaveAs("graph.pdf");

  return 0;

}
