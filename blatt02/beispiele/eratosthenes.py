#!/usr/bin/python
#######################################################################
#
# RECHNERNUTZUNG in der Physik, WS 14/15
#
# Beispiel fuer Listen: Sieb des Eratosthens
#
# Ausfuehren dieses Programms: python PROGRAMMNAME
# Dieses Programm ist in der Sprachversion 2 von python geschrieben.

from math import sqrt

def sieb(limit):
  """ Sieb des Eratosthenes bis zur Grenze limit. Liefert Primzahlliste """
  ## Liste der Laenge limit mit "True" initialisieren
  is_prime = [True] * limit
  ## 0 und 1 sind nicht prim
  is_prime[0] = is_prime[1] = False
  ## gehe das Feld ab, per "if" dabei nur die verbliebenen Primzahlen
  for i in xrange(2, int(sqrt(limit) + 1)):
    if is_prime[i]:
      ## markiere die Vielfachen dieser Primzahl i im Feld mit "false"
      for j in range(i * i, limit, i):
        is_prime[j] = False
  ## Erzeuge eine liste, die nur noch die Primzahlen enthaelt.
  ## Hier: funktioniales Programmieren: Schleife ueber das Feld,
  ## die auch die Indizes erhaelt. Gib nur diejenigen Indizes zurueck,
  ## bei denen noch "True" im Feld steht.
  return [ind for ind, ispr in enumerate(is_prime) if ispr]

print "Primazhlen per Sieb des Eratosthenes"
print sieb(100)
