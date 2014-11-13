#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

# Rechnernutzung in der Physik
# WS 2014/2015

# Aufgabe 7
# Fehlerfortpflanzung: Verhaeltnis von Zufallszahlen

import numpy as np
import matplotlib.pyplot as plt

def normalDist(n, mean, sigma):
    return np.random.normal(mean, sigma, n)


# generate some Gaussion distributed Data and save to file

n = 1000
mu1, sigma1 = 1.5, 0.5
mu2, sigma2 = 0.6, 0.15

normal1 = normalDist(n, mu1, sigma1)
normal2 = normalDist(n, mu2, sigma2)

rdata = np.divide(normal1, normal2)

np.savetxt('gaussian_numbers.dat', rdata)
