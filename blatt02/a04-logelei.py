#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Rechnernutzung in der Physik
# WS 2014/2015

# Aufgabe 4 
# Logelei

def checkNumber(a):
    numbers = [a, 2*a]
    # flags for each digit
    digits = [False] * 10

    for elem in numbers:
        while elem != 0:
            lastDigit, elem = elem % 10, elem // 10

            if digits[lastDigit]:
                return False
            else:
                digits[lastDigit] = True

    return digits.count(True) == 10


print "Logelei: \n"

for i in range(10000, 49999):
    if checkNumber(i):
        print "gefunden:", i, "(=", 2*i, "/ 2)"
