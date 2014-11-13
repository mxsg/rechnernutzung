#!/usr/bin/python -tt
import numpy as np
import matplotlib.pyplot as plt
import math


# define a function (Gauss distribution)
def fgauss(x,mu,sigma):
    return (np.exp(-(x-mu)**2/2/sigma**2)/np.sqrt(2*np.pi)/sigma)

def normalDist(n, mean, sigma):
    return np.random.normal(mean, sigma, n)


# generate some Gaussion distributed Data and save to file

n = 1000
mu1, sigma1 = 1.5, 0.5
mu2, sigma2 = 0.6, 0.15

normal1 = normalDist(n, mu1, sigma1)
normal2 = normalDist(n, mu2, sigma2)

rdata = np.divide(normal1, normal2)

rmu = mu1/mu2
rsigma = rmu*math.sqrt((sigma1/mu1)**2 + (sigma2/mu2)**2)
print "Aus Fehlerfortpflanzung:"
print "rmu =", rmu
print "rsigma =", rsigma

print "\nAus Daten direkt:"
print np.mean(rdata)
print np.std(rdata)

np.savetxt('gaussian_numbers.dat', rdata)

leftEdge = rmu - 4*rsigma
rightEdge = rmu + 4*rsigma

# plot data as histogram
rbins = np.arange(leftEdge, rightEdge, (rightEdge-leftEdge)/30)
n, bins, patches = plt.hist(rdata,rbins,normed=1,facecolor='g',log=False,alpha=0.5) #plot data
#     make plot nicer:
plt.xlabel('x') # axis labels
plt.ylabel('probability density')
plt.title('Histogram of Gauss distribution') # title

# plot Gauss distribution
x = np.arange(leftEdge, rightEdge, 0.01)
plt.plot(x, fgauss(x, rmu, rsigma), 'r-')             # plot function 
#plt.xlim(rmu - 3*rsigma, rmu + 3*rsigm)
plt.text(1,0.4, \
r'$f(x) = \frac{1}{\sqrt{2\,\pi}\sigma}\,\exp{\left(\frac{-(x-\mu)^2}{2\sigma^2}\right)}$', \
fontsize=14, color='b') # a nicely type-set formula of the function

plt.grid(True) # show a grid for orientation 
plt.show()  # now display everything on the screen
