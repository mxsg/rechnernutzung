#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Rechnernutzung in der Physik
# WS 2014/2015

# Aufgabe 5 
# Berechnung statistischer Größen

import numpy as np

# write your own implementation of the statistical functions

def mean(a):
    return np.sum(a)/len(a)

def variance(a):
    listMean = mean(a)
    # list comprehension: generator for list with square deviations
    # return sum((listMean - value)**2 for value in a) / len(a)
    # simpler:
    return mean((a - mean(a))**2)

def sigma(a):
    return np.sqrt(variance(a))

# read data from text file
a = np.loadtxt('numbers.dat', dtype=float)
N = len(a)
print N, " numbers read \n", a

# print same statistical quantities using numpy functions
print "\n*==* result with numpy functions:"
print "median is:", np.median(a)
print "mean is", np.mean(a)
print "variance is", np.var(a) 
print "standard deviation sigma=", np.std(a)
print "unbiased sigma =", np.std(a)*np.sqrt(float(N)/float(N-1))

# calculate and print some statistical quantities on raw data

print "\n*==* result with user-defined functions:"
print "mean is", mean(a)
print "variance is", variance(a) 
print "standard deviation sigma=", sigma(a)
print "unbiased sigma =", sigma(a)*np.sqrt(float(N)/float(N-1))

# histogram data
print "\n*==* histogram of data:"
binValues, bins = np.bincount(a.astype(int)), np.arange(10)
print binValues

# calculate mean and sigma from histogram and print
binsMean = np.average(bins, weights=binValues)
binsVariance = np.average((bins - binsMean)**2, weights=binValues)

print "mean:", binsMean
print "variance:", binsVariance
print "sigma:", np.sqrt(binsVariance)
