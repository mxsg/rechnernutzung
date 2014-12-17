(* ::Package:: *)

ClearAll["Global`*"]


SkPr[Pn_, Pm_, g_, {x_, a_, b_}] := Integrate[Pn*Pm*g, {x, a, b}]


(* Polynom 0. Ordnung ist konstant, aber normiert *)
ONPoly[g_, 0, {x_, a_, b_}] := 1/Sqrt[SkPr[1, 1, g, {x, a, b}]]
(* h\[ODoubleDot]here Ordnungen werden nur einmal berechnet, dann gecachet *)
ONPoly[g_, n_Integer?Positive, {x_, a_, b_}] :=
ONPoly[g, n, {x, a, b}] = Module[{startPoly, projektion, Pnext, Polyi, PTilde},
	Pnext = x^n;

	projektion =
		Sum[ONPoly[g, i, {x, a, b}]*
		SkPr[ONPoly[g, i, {x, a, b}], x^n, g, {x, a, b}], {i, 0, n-1}];
	PTilde = x^n - projektion;
	Expand[PTilde/Sqrt@SkPr[PTilde, PTilde, g, {x, a, b}]]
]


TestOrthonorm[nmax_, polySys_, g_, {x_, a_, b_}] :=
	MatrixForm@Table[SkPr[polySys[i], polySys[j], g[x], {x, a, b}], {i, 0, nmax}, {j, 0, nmax}]

VglMath[nmax_, polySys_, polyMath_, g_, {x_, a_, b_}] :=
	Table[Simplify[polySys[n]/polyMath[n]], {n, 0, nmax}]

(* maximale Polynomordnung *)
nmax = 5;


(* Legendre-Polynome *)

gLeg[x] := 1; aLeg = -1; bLeg = 1;
NLegendre[n_] := ONPoly[gLeg[x], n, {x, aLeg, bLeg}]

Table[NLegendre[n], {n, 0, nmax}]


(* Teilen selbst erzeugter Polynome durch die Mathematica-Polynome *)
VglMath[5, NLegendre, LegendreP[#, x]&, gLeg, {x, aLeg, bLeg}]


(* Orthonormierung \[UDoubleDot]berpr\[UDoubleDot]fen *)
TestOrthonorm[5, NLegendre, gLeg, {x, aLeg, bLeg}]


(* Chebyshev-Polynome *)

gCheby[x] := 1/Sqrt[1-x^2]; aCheby = -1; bCheby = 1;
NChebyshev[n_] := ONPoly[gCheby[x], n, {x, aCheby, bCheby}]

Table[NChebyshev[n], {n, 0, nmax}]


(* Teilen selbst erzeugter Polynome durch die Mathematica-Polynome *)
VglMath[5, NChebyshev, ChebyshevT[#, x]&, gCheby, {x, aCheby, bCheby}]


(* Orthonormierung \[UDoubleDot]berpr\[UDoubleDot]fen *)
TestOrthonorm[5, NChebyshev, gCheby, {x, aCheby, bCheby}]


(* Laguerre-Polynome *)

gLag[x] := Exp[-x]; aLag = 0; bLag = Infinity;
NLaguerre[n_] := ONPoly[gLag[x], n, {x, aLag, bLag}]

Table[NLaguerre[n], {n, 0, nmax}]


(* Teilen selbst erzeugter Polynome durch die Mathematica-Polynome *)
VglMath[5, NLaguerre, LaguerreL[#, x]&, gLag, {x, aLag, bLag}]


(* Orthonormierung \[UDoubleDot]berpr\[UDoubleDot]fen *)
TestOrthonorm[5, NLaguerre, gLag, {x, aLag, bLag}]


(* Hermite-Polynome *)

gHerm[x] := Exp[-x^2]; aHerm = -Infinity; bHerm = Infinity;
NHermite[n_] := ONPoly[gHerm[x], n, {x, aHerm, bHerm}]

Table[NHermite[n], {n, 0, nmax}]


(* Teilen selbst erzeugter Polynome durch die Mathematica-Polynome *)
VglMath[5, NHermite, HermiteH[#, x]&, gHerm, {x, aHerm, bHerm}]


(* Orthonormierung \[UDoubleDot]berpr\[UDoubleDot]fen *)
TestOrthonorm[5, NHermite, gHerm, {x, aHerm, bHerm}]


(* Q-Polynome *)

gQ[x] := 1/(1+x^2); aQ = -1; bQ = 1;
NQ[n_] := ONPoly[gQ[x], n, {x, aQ, bQ}]

Table[NQ[n], {n, 0, nmax}]


(* Orthonormierung \[UDoubleDot]berpr\[UDoubleDot]fen *)
TestOrthonorm[5, NQ, gQ, {x, aQ, bQ}]
