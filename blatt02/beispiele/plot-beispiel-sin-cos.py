#!/usr/bin/python
#######################################################################
#
# RECHNERNUTZUNG in der Physik, WS 14/15
#
# Beispiel fuer Plotten mit matplotlib
#
# Ausfuehren dieses Programms: python PROGRAMMNAME
# Dieses Programm ist in der Sprachversion 2 von python geschrieben.

# numpy-Objekte werden mit prefix "np." aufgerufen
# matplotlib-Objekte werden mit prefix "plt." aufgerufen
import numpy as np
import matplotlib.pyplot as plt

## oder einfacher.... ???
## from pylab import *

## Ein numpy-array, das die Stuetzstellen enthaelt (np.pi ist pi=3.141..)
emin,emax = 0,2*np.pi
npoints=256
X=np.linspace( emin, emax, npoints, endpoint=True)

# Wertetabelle berechnen. np.cos kann mit Feldern arbeiten!
C = np.cos(X)
# np.sin auch. X ist ja ein Feld von Stuetzstellen. 
# Wer es nicht glaubt: Einfach mal ausgeben...
S = np.sin(X)

# Plot des Cosinus. Wird aber noch nicht angezeigt!
plt.plot(X, C, color="blue", label="Cosinus")

# Plot des Sinus.
plt.plot(X, S, color="green", linewidth=3, linestyle="-.", label="Sinus")

# Setze Grenzen der x-Achse des Plots 
plt.xlim(-1.0,8.0)

# Setze in X- und Y-Richtung ein paar Ticks (Achsenpunkte)
# LaTeX-Ausdruecke koennen verwendet werden, r steht fuer "raw-string"
plt.xticks([0, np.pi/2, np.pi, np.pi*2],
       [r'$0$', r'$\pi/2$', r'$\pi$', r'$2\pi$'])
plt.yticks(np.linspace(-1,1,5,endpoint=True))

# Wo soll die Legende hin? (Text dazu ist in den "label" der plot-Anweisungen)
plt.legend(loc='lower left')

# Zeige ein Gitternetz
plt.grid(True)

# Zeige nun alles auf dem Bildschirm an
plt.show()
