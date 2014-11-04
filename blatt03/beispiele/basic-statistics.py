#!/usr/bin/env python
#     (the first line allows execution directly from the linux shell) 
#
# --- sinmple python exercise 
# Author:        G. Quast   Oct. 2013
# dependencies:  PYTHON v2.7, numpy
# last modified: 
#--------------------------------------------------------------
import numpy as np

# write here your own implementation of the stistical funcions

def mean(a):
  return np.sum(a)/len(a)

#def variance(a):
#  return ???

#def sigma(a):
#  return ???

# --- main program
#
# read data from text file
a=np.loadtxt('numbers.dat',dtype=float)
N=len(a)
print N, " numbers read \n", a

#     print same statistical quantities using numpy functions
print "\n*==* result with numpy functions:"
print "median is:",np.median(a)
print "mean is",np.mean(a)
print "variance is",np.var(a) 
print "standard deviation sigma=",np.std(a)
print "unbiased sigma =",np.std(a)*np.sqrt(float(N)/float(N-1))


# ---> your code starts here ....

# calculate and print some statistical quantities on raw data

# histogram data

# calculate mean and sigma from histogram and print
