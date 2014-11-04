#!/usr/bin/python -tt
import numpy as np
import matplotlib.pyplot as plt
 
#generate some Gaussion distributed Data and save to file
data=np.random.normal(size=100)  
np.savetxt('gaussian_numbers.dat',data)

