(* ::Package:: *)

VMult[a_, v_] := vec[a*v[[1]], a*v[[2]], a*v[[3]]]
VPlus[v_, w_] := vec[v[[1]]+w[[1]], v[[2]]+w[[2]], v[[3]]+w[[3]]]
VMinus[v_, w_] := VPlus[v, VMult[-1, w]]
Skalarprodukt[v_, w_] := Sum[v[[i]]*w[[i]], {i, 3}]

(* Kreuzprodukt mit Levi-Civita-Tensor: Komponenten mit Table in *)
(* Mathematica-Vektor, dann auspacken und in vec[...] stecken *)
Kreuzprodukt[v_,w_]:= Module[{l},
    l = Table[Sum[LeviCivitaTensor[3][[k,i,j]]*v[[i]]*w[[j]], {i,3}, {j,3}], {k,3}];
    vec[l[[1]],l[[2]],l[[3]]]
]
Kreuzprodukt[vec[a1,a2,a3],vec[b1,b2,b3]]


(* beliebige Vektoren definieren *)
a = vec[a1,a2,a3]; b=vec[b1,b2,b3]; c=vec[c1,c2,c3];


(* Zyklische Invarianz des Kreuzprodukts testen *)
Simplify[Skalarprodukt[a, Kreuzprodukt[b,c]]] === Simplify[Skalarprodukt[c, Kreuzprodukt[a,b]]]


(* BAC-CAB-Regel *)
Simplify[Kreuzprodukt[a, Kreuzprodukt[b,c]] == 
	VMinus[VMult[Skalarprodukt[a,c], b],VMult[Skalarprodukt[a,b],c]]]


LinearAbhaengigQ[u_,v_,w_] := Skalarprodukt[u, Kreuzprodukt[v,w]] === 0


(* teste angegebene Vektoren *)
v1 = vec[1,1,1]; v2 = vec[1,0,-1]; v3=vec[1,2,3];

LinearAbhaengigQ[v1,v2,v3]


v1=vec[1.2,2.0,1.9];v2=vec[0.1,0.1,1.3];v3=vec[0.2,1.6,1.9];

LinearAbhaengigQ[v1,v2,v3]


v1=vec[e,e,f-e];v2=vec[e,f-2e,-e];v3=vec[e,f,e+f];

LinearAbhaengigQ[v1,v2,v3]


Solve[(-e+f) (e f-e (-2 e+f))+e (-e^2-e (e+f))+e (e f+(-2 e+f) (e+f))==0,{e,f}]



