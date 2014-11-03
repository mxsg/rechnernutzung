#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Rechnernutzung in der Physik
# WS 2014/2015

# Aufgabe 3
# Exponentialfunktion

import math

def exponential(p):
    return math.exp(p)

print "Exponentialfunktion berechnen:"
print

a = raw_input("Bitte eine Zahl eingeben: ")

try:
    value = float(a)
    
    print exponential(value)

except OverflowError:
    print "Overflow, bitte eine kleinere Zahl eingeben."

except ValueError:
    print "Bitte eine gültige Zahl eingeben."
