#!/usr/bin/python 

# -------- Gauss.py ------------------------------------------
# Description: example showing 
#              - how to define a function
#              - read data from text file
#              - generate a histogram
#              - use matplotlib to plot histogram and function
# Author:      G. Quast   Oct. 2013
# dependencies: PYTHON v2.7, numpy, matplotlib.pyplot 
# last modified: 
#--------------------------------------------------------------
import numpy as np
import matplotlib.pyplot as plt
 
# define a function (Gauss distribution)
def fgauss(x,mu,sigma):
    return (np.exp(-(x-mu)**2/2/sigma**2)/np.sqrt(2*np.pi)/sigma)
 
# read data from a text file
data =np.loadtxt('gaussian_numbers.dat',dtype=float)
 
#set parameters for Gaussdistribtion
mu=0
sigma=1

# plot data as histogram 
n,bins,patches=plt.hist(data,30,normed=1,facecolor='g',log=False,alpha=0.5) #plot data
#     make plot nicer:
plt.xlabel('x') # axis labels
plt.ylabel('probability density')
plt.title('Histogram of Gauss distribution') # title

# plot Gauss distribution
x = np.arange(-4., 4., 0.1)
plt.plot(x, fgauss(x,mu,sigma), 'r-')             # plot function 
plt.text(1,0.4, \
r'$f(x) = \frac{1}{\sqrt{2\,\pi}\sigma}\,\exp{\left(\frac{-(x-\mu)^2}{2\sigma^2}\right)}$', \
fontsize=14, color='b') # a nicely type-set formula of the function

plt.grid(True) # show a grid for orientation 
plt.show()  # now display everything on the screen

