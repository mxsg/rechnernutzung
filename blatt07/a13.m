(* ::Package:: *)

(* st\[UDoubleDot]ckweise konstantes Potential *)
V[a_, V1_, x_] := Piecewise[{{Infinity, x<-1}, {0, -1<=x<-a},
	{V1,-a<=x<=a}, {0, a<=x<=1}, {Infinity, 1<x}}]


(* Konstanten definieren *)
a = 1/4;
hbar = 1;
m = 1;
L = 2;


SchrGl[En_, x_, V1_] :=
	En*Psi[x] == -hbar^2/(2m)*D[Psi[x], {x, 2}]+V[a, V1, x]*Psi[x]

solution[V1_] := ParametricNDSolve[
	{SchrGl[En, x, V1], Psi[-1]==0, (D[Psi[x], x]/.x->-1)==1}, Psi, {x,-1, 1}, En]


Psi0 = Psi /. solution[0];

Plot[Evaluate[Table[Psi0[Energie][x], {Energie, 0.75, 5, .5}]], {x, -1, 1},
 PlotRange -> All]


E0start = 1.25;
E00 = Energie /. FindRoot[Psi0[Energie][1]==0, {Energie, E0start}]


(* zum Vergleich: analytisches Ergebnis *)
N[hbar^2*Pi^2/(2*m*L^2)*1^2]


E1start =  4.75;
E01 = Energie /. FindRoot[Psi0[Energie][1]==0, {Energie, E1start}]


(* wieder zum Vergleich *)
N[hbar^2*Pi^2/(2*m*L^2)*2^2]


Psip30 = Psi /. solution[30];

Plot[Evaluate[Table[Psip30[Energie][x], {Energie, 5, 7, .4}]], {x, -1, 1},
 PlotRange -> All]


E0start = 6.2;
Ep300 = Energie /. FindRoot[Psip30[Energie][1]==0, {Energie, E0start}]


E1start = 6.6;
Ep301 = Energie /. FindRoot[Psip30[Energie][1]==0, {Energie, E1start}]


Psim30 = Psi /. solution[-30];

Plot[Evaluate[Table[Psi[Energie][x] /. solution[-30], {Energie, -21.73, -21.7, .005}]],
	{x, -1, 1}, PlotRange -> All]


E0start = -21.715;
Em300 = Energie /. FindRoot[Psim30[Energie][1]==0, {Energie, E0start}]


Plot[Evaluate[Table[Psim30[Energie][x], {Energie, -3, -1.2, 0.3}]],
	{x, -1, 1}, PlotRange -> All]


E1start = -2.1;
Em301 = Energie /. FindRoot[Psim30[Energie][1]==0, {Energie, E1start}]


(* Aufgabe 13c) *)

(* Normierung der Wellenfunktion *)
norm[psi_] := NIntegrate[Abs[psi[x]]^2, {x, -1, 1}]

norm0 = Sqrt[norm[Psim30[Em300]]]
norm1 = Sqrt[norm[Psim30[Em301]]]

Plot[{Psim30[Em300][x]/norm0,Psim30[Em301][x]/norm1}, {x, -1, 1}]


norm0 = Sqrt[norm[Psi0[E00]]]
norm1 = Sqrt[norm[Psi0[E01]]]

Plot[{Psi0[E00][x]/norm0,Psi0[E01][x]/norm1}, {x, -1, 1}]


norm0 = Sqrt[norm[Psip30[Ep300]]]
norm1 = Sqrt[norm[Psip30[Ep301]]]

Plot[{Psip30[Ep300][x]/norm0,Psip30[Ep301][x]/norm1}, {x, -1, 1}]



