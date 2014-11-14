#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

# Rechnernutzung in der Physik
# WS 2014/2015

# Aufgabe 7
# Fehlerfortpflanzung: Verhältnis von Zufallszahlen

import numpy as np
import matplotlib.pyplot as plt

def normalDist(n, mean, sigma):
    return np.random.normal(mean, sigma, n)

# distribution parameters
n = 1000
mu1, sigma1 = 1.5, 0.5
mu2, sigma2 = 0.6, 0.15

normal1 = np.random.normal(mu1, sigma1, n)
normal2 = np.random.normal(mu2, sigma2, n)

# create ratio distribution and save values to file
data = np.divide(normal1, normal2)
np.savetxt('gaussian_numbers.dat', data)
