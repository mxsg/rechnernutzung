#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Rechnernutzung in der Physik
# WS 2014/2015

# Aufgabe 5 
# Fermifunktionen zeichnen

import math
import numpy as np
import matplotlib.pyplot as plt

def fermi(E, T, kB=1.0, my=0.0):
    return 1/(np.exp((E-my)/(kB*T))+1)


Emin, Emax = -10.0, 10.0
temps = [0.1, 0.5, 1.0, 2.0, 5.0]
pointNum = 512

colors = ["orange", "red", "green", "blue", "violet"]

for i, temp in enumerate(temps):

    xVals = np.linspace(Emin, Emax, pointNum, endpoint=True)

    yVals = fermi(xVals, temp)

    tempLabel = "T = " + str(temp)
    plt.plot(xVals, yVals, color=colors[i], label=tempLabel)


# x-Bereich setzen
plt.xlim(-10.0, 10.0)

plt.xticks(np.linspace(-10, 10, 11, endpoint=True))

plt.xlabel("Energie $E$")
plt.ylabel("Wert der Fermi-Dirac-Funktion $f(E)$")

# Legende unten links
plt.legend(loc='lower left')

plt.grid(True)

plt.show()
