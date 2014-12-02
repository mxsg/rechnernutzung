xminPP = 0;
xmaxPP = Infinity;
gewichtPP[x_]:=( 1/(E^x^2*(1 + x^2))
);
PP[0,x_] := (
1.220195878886191
);
PP[1,x_] := (
-1.5483605140346672 + 3.4877365517724708*x
);
PP[2,x_] := (
1.7322203342518872 - 8.771480290137703*x + 6.766627946443705*x^2
);
PP[3,x_] := (
-1.864038994079164 + 15.577161598366573*x - 25.637075951218772*x^2 + 
 10.447028495800772*x^3
);
PP[4,x_] := (
1.9696783867847234 - 23.769902712620375*x + 62.10402443652294*x^2 - 
 53.02261854204128*x^3 + 13.738466636944548*x^4
);
PP[5,x_] := (
-2.059116939981774 + 33.25780733085797*x - 121.87203078780995*x^2 + 
 162.7929951569804*x^3 - 87.52457007273279*x^4 + 15.977554186230362*x^5
);
PP[6,x_] := (
2.137381654355897 - 43.97295517527161*x + 210.84855344998294*x^2 - 
 390.3014352861658*x^3 + 325.64073917374003*x^4 - 122.58740633501627*x^5 + 
 16.824506766201914*x^6
);
PP[7,x_] := (
-2.204434730905681 + 55.80004233497451*x - 334.8243090341446*x^2 + 
 802.9960341098415*x^3 - 922.114973447993*x^4 + 535.8967660543783*x^5 - 
 151.03882583301052*x^6 + 16.30127890360759*x^7
);
PP[8,x_] := (
2.4482372587792223 - 73.40775046752573*x + 528.2226646534164*x^2 - 
 1555.1300890533962*x^3 + 2276.2149711063544*x^4 - 1794.1652118259835*x^5 + 
 770.091426609525*x^6 - 168.49935972230364*x^7 + 14.63680175661116*x^8
);
PP[9,x_] := (
1.961741536607288 - 58.044093960234854*x + 408.7565511285052*x^2 - 
 1163.0448777212878*x^3 + 1610.7117258425708*x^4 - 1152.8790957084184*x^5 + 
 406.68271884947313*x^6 - 48.91375441447545*x^7 - 6.447918010262493*x^8 + 
 1.536183476393726*x^9
);
PP[10,x_] := (
-2.5721229717051304 + 77.92880890167186*x - 566.5419923318949*x^2 + 
 1684.4349203362715*x^3 - 2485.2896295064784*x^4 + 1962.4121180172745*x^5 - 
 825.9283421323927*x^6 + 161.60430730223223*x^7 - 3.9652248778845767*x^8 - 
 2.8631441889293625*x^9 + 0.2543511505157706*x^10
);
