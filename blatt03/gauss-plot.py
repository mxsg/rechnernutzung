#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

# Rechnernutzung in der Physik
# WS 2014/2015

# Aufgabe 7
# Fehlerfortpflanzung: Verhaeltnis von Zufallszahlen

import numpy as np
import matplotlib.pyplot as plt
import math

# define a function (gauss distribution)
def fgauss(x,mu,sigma):
    return (np.exp(-(x-mu)**2/2/sigma**2)/np.sqrt(2*np.pi)/sigma)

# read data from a text file
rdata = np.loadtxt('gaussian_numbers.dat',dtype=float)

n = 1000
mu1, sigma1 = 1.5, 0.5
mu2, sigma2 = 0.6, 0.15

rmu = mu1/mu2
# calculate sigma with propagation of error
rsigma = rmu*math.sqrt((sigma1/mu1)**2 + (sigma2/mu2)**2)

print "Aus Fehlerfortpflanzung:"
print "mean =", rmu
print "sigma =", rsigma

print "\nAus Daten direkt:"
print "mean =", np.mean(rdata)
print "sigma =", np.std(rdata)

# configure bins (not used right now)
leftEdge = rmu - 4*rsigma
rightEdge = rmu + 4*rsigma
rbins = np.arange(leftEdge, rightEdge, (rightEdge-leftEdge)/30)

# plot data as histogram
n, bins, patches = plt.hist(rdata,40,normed=1,facecolor='g',log=False,alpha=0.5) #plot data

# format plot
plt.xlabel('r')
plt.ylabel('probability density')
plt.title('histogram of ratio distribution')

# plot Gauss distribution
x = np.arange(leftEdge, rightEdge, 0.01)
plt.plot(x, fgauss(x, rmu, rsigma), 'r-')

plt.text(5,0.3, \
r'$f(x) = \frac{1}{\sqrt{2\,\pi}\sigma}\,\exp{\left(\frac{-(x-\mu)^2}{2\sigma^2}\right)}$', \
fontsize=14, color='b') # a nicely type-set formula of the function

plt.grid(True) # show a grid for orientation 
plt.show()  # now display everything on the screen
