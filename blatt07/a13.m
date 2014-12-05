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


(* Buchstabe E f\[UDoubleDot]r Energie richtig darstellen *)
Format[Energie, TraditionalForm] := "E"


Psi0 = Psi /. solution[0];

EnRange0 = Range[0.75, 5, .5];
Plot[Evaluate[Table[Psi0[Energie][x], {Energie, EnRange0}]], {x, -1, 1},
	PlotRange -> All, PlotLegends->(StringForm["E = ``", #]&/@EnRange0),
	PlotLabel->"V = 0",
	AxesLabel->{x, Subscript[\[Psi],Energie][x]}]
(* StringForm formatiert String in angegebener Form,
   hier als anonyme Funktion (&) und mit Map (/@), um jeden Wert einzeln zu formatieren *)


E0start = 1.25;
E00 = Energie /. FindRoot[Psi0[Energie][1]==0, {Energie, E0start}]


(* zum Vergleich: analytisches Ergebnis *)
N[hbar^2*Pi^2/(2*m*L^2)*1^2]


E1start =  4.75;
E01 = Energie /. FindRoot[Psi0[Energie][1]==0, {Energie, E1start}]


(* wieder zum Vergleich *)
N[hbar^2*Pi^2/(2*m*L^2)*2^2]


Psip30 = Psi /. solution[30];

EnRangep30 = Range[5, 7, .4];
Plot[Evaluate[Table[Psip30[Energie][x], {Energie, EnRangep30}]], {x, -1, 1},
	PlotRange -> All, PlotLegends->(StringForm["E = ``", #]&/@EnRangep30),
	PlotLabel->"V = 30",
	AxesLabel->{x, Subscript[\[Psi],Energie][x]}]


E0start = 6.2;
Ep300 = Energie /. FindRoot[Psip30[Energie][1]==0, {Energie, E0start}]


E1start = 6.6;
Ep301 = Energie /. FindRoot[Psip30[Energie][1]==0, {Energie, E1start}]


Psim30 = Psi /. solution[-30];

EnRangem300 = Range[-21.73, -21.7, .005];
Plot[Evaluate[Table[Psi[Energie][x] /. solution[-30], {Energie, EnRangem300}]],
	{x, -1, 1}, PlotRange -> All, PlotLegends->(StringForm["E = ``", #]&/@EnRangem300),
	PlotLabel->"V = -30",
	AxesLabel->{x, Subscript[\[Psi],Energie][x]}]


E0start = -21.715;
Em300 = Energie /. FindRoot[Psim30[Energie][1]==0, {Energie, E0start}]


EnRangem301 = Range[-3, -1.2, 0.3];

Plot[Evaluate[Table[Psim30[Energie][x], {Energie, EnRangem301}]],
	{x, -1, 1}, PlotRange -> All, PlotLegends->(StringForm["E = ``", #]&/@EnRangem301),
	PlotLabel->"V = -30",
	AxesLabel->{x, Subscript[\[Psi],Energie][x]}]


E1start = -2.1;
Em301 = Energie /. FindRoot[Psim30[Energie][1]==0, {Energie, E1start}]


(* Aufgabe 13c) *)

(* Normierung der Wellenfunktion *)
norm[psi_] := NIntegrate[Abs[psi[x]]^2, {x, -1, 1}]


norm0 = Sqrt[norm[Psim30[Em300]]]
norm1 = Sqrt[norm[Psim30[Em301]]]

plotm30 = Plot[{Psim30[Em300][x]/norm0,Psim30[Em301][x]/norm1}, {x, -1, 1},
	PlotLegends->{StringForm["`` = ``", Subscript[energie,0], Em300],
	StringForm["`` = ``", Subscript[energie,1], Em301]},
	PlotLabel->"V = -30",
	AxesLabel->{x, Subscript[\[Psi],Energie][x]}]


norm0 = Sqrt[norm[Psi0[E00]]]
norm1 = Sqrt[norm[Psi0[E01]]]

plot0 = Plot[{Psi0[E00][x]/norm0,Psi0[E01][x]/norm1}, {x, -1, 1},
	PlotLegends->{StringForm["`` = ``", Subscript[energie,0], E00],
	StringForm["`` = ``", Subscript[energie,1], E01]},
	PlotLabel->"V = 0",
	AxesLabel->{x, Subscript[\[Psi],Energie][x]}]


norm0 = Sqrt[norm[Psip30[Ep300]]]
norm1 = Sqrt[norm[Psip30[Ep301]]]

plotp30 = Plot[{Psip30[Ep300][x]/norm0,Psip30[Ep301][x]/norm1}, {x, -1, 1},
	PlotLegends->{StringForm["`` = ``", Subscript[energie,0], Ep300],
	StringForm["`` = ``", Subscript[energie,1], Ep301]},
	PlotLabel->"V = 30",
	AxesLabel->{x, Subscript[\[Psi],Energie][x]}]


SetDirectory[NotebookDirectory[]];
Export["plot-m30.pdf", plotm30]
Export["plot-0.pdf", plot0]
Export["plot-p30.pdf", plotp30]
ResetDirectory[];



