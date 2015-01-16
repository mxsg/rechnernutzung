#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Rechnernutzung in der Physik
# WS 2014/2015

# Aufgabe 20b) 
# Berechnung von Kovarianz und Korrelationskoeffizient

import numpy as np

# returns the mean of a numpy array
def mean(a):
    return np.sum(a)/len(a)


# returns the variance of a numpy array
def variance(a):
    # difference of array and a single number is defined for numpy arrays
    return mean((a - mean(a))**2)


# returns the standard deviation of a numpy array
def sigma(a):
    return np.sqrt(variance(a))


# returns the covariance of two numpy arrays of equal length
def covariance(a, b):
    if len(a) != len(b):
        raise ValueError("different array lengths")

    meanA = mean(a)
    meanB = mean(b)

    return mean((a[i] - meanA)(b[i] - meanB) for i in range(len(a)))


# returns the correlation factor (scaled covariance) for two numpy arrays
def correlationFactor(a, b):
    # scale covariance of two arrays
    return covariance(a, b) / (mean(a) * mean(b))
