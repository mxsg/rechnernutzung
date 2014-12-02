(* ::Package:: *)

GaussIntegration[f_, trans_, a_, b_, poly_, w_, n_] := Module[{normn, ftilde, xk, coeff, Gk},
	(* Polynom-Normierung *)
	normn = NIntegrate[poly[n,x]^2*w[x], {x, a, b}];
	ftilde[x_] := f[trans[x]]*(D[trans[z],z]/.z->x)/w[trans[x]];
	(* Nullstellen bestimmen *)
	xk = x /. NSolve[poly[n,x]==0,x];
	(* fuehrende Koeffizienten *)
	coeff[j_] := Coefficient[poly[j, x], x, j];
	Gk[k_] := coeff[n]/(coeff[n-1]*(D[poly[n,x],x]/.x->xk[[k]])*poly[n-1,xk[[k]]] / normn);
	(* numerisches Ergebnis *)
	N[Sum[Gk[k]*ftilde[xk[[k]]], {k, n}]]
]



(* Aufgabe 12a) *)


(* transformiert Def.bereich der zu integrierenden Funktion auf [-1,1] *)
trans[x_, a_, b_] := (b-a)/2*x+(a+b)/2

f1[x_] := Exp[-(x-1)^2]+Exp[-(x+1)^2]
trans1[x_] := trans[x, -10, 10]

f2[x_]:=(((1-Sin[x])^2+Cos[x])^2-Sin[x])^2
trans2[x_] := trans[x, 0, 1]

(* Bei Legendre-Polynomen ist die Gewichtung =1 *)
w[x_] := 1

(* integriere mit Gauss-Quadratur *)
gInt1[n_] := GaussIntegration[f1, trans1, -1, 1, LegendreP, w, n]
gInt2[n_] := GaussIntegration[f2, trans2, -1, 1, LegendreP, w, n]

gInt1[10]
gInt2[10]


(* gleiche Integrale numerisch berechnen *)
nInt1 = NIntegrate[f1[x], {x, -10, 10}]
nInt2 = NIntegrate[f2[x], {x, 0, 1}]


(* Plotten *)
(* f1 *)
Show[ListPlot[Table[gInt1[n], {n, 1, 8}]], Plot[nInt1, {n, 0, 8}, PlotStyle->Blue], 
	PlotRange->{{0, 8}, {0, 6}}]



(* f1 *)
Show[ListPlot[Table[gInt2[n], {n, 1, 8}]], Plot[nInt2, {n, 0, 8}, PlotStyle->Blue], 
	PlotRange->{{0, 8}, {0, 6}}]


(* Aufgabe 12b) *)

f3[x_] := Exp[-x^2]*(Sin[x+1]+Cos[x])/(1+x^2)


(* mit den Laguerre-Polynomen ist keine Transformation notwendig *)
trans3[x_] := x
w[x_] := Exp[-x]

gInt3[n_] := GaussIntegration[f3, trans3, 0, Infinity, LaguerreL, w, n]

gInt3[10]


(* Vergleich mit numerischer Integration *)
nInt3 = NIntegrate[f3[x], {x, 0, Infinity}]


(* Plot f1 *)
Show[ListPlot[Table[gInt3[n], {n, 1, 8}]], Plot[nInt3, {n, 0, 8}, PlotStyle->Blue], 
	PlotRange->{{0, 8}, {0, 2}}]



(* Aufgabe 12c) *)

(* Datei einlesen *)
<< "/Users/msg/studium/rechnernutzung/blatt06/ortho.m"

w[x_] := gewichtPP[x]

gInt3c[n_] := GaussIntegration[f3, trans3, 0, Infinity, PP, w, n]

gInt3c[8]


(* wieder zum Vergleich: numerisch *)
nInt3


(* Plot f3 (mit Polynomen aus c) *)
Show[ListPlot[Table[gInt3c[n], {n, 1, 8}]], Plot[nInt3, {n, 0, 8}, PlotStyle->Blue], 
	PlotRange->{{0, 8}, {0, 2}}, AxesOrigin->{0,0}]
