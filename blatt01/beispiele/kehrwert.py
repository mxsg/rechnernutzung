#!/usr/bin/python
#######################################################################
#
# RECHNERNUTZUNG in der Physik, WS 14/15
#
# Beispiel eines Python-Programmes, Kehrwertberechnung
#
# Ausfuehren dieses Programms: python PROGRAMMNAME
# Dieses Programm ist in der Sprachversion 2 von python geschrieben.

# Ein Beispiel, wie Python-Module eingebunden werden
# Das time-Modul enthaelt den Befehl time.sleep, der unten aufgerufen wird.
import time

#######################################################################
# Beispiel fuer eine Python-Funktion
# Aufgabe: Kehrwert berechnen
# Name der Funktion: "reziprok" (so wird sie aufgerufen)
# Ein Argument, der Name ist "a" (lokaler Variablenname).
# Durch die Einrueckung (hier zwei Leerzeichen) wird vereinbart, 
# bis wohin der Funktionsquelltext reicht. 
# (In vielen anderen Sprachen ist dies durch Klammern geloest.)
def reziprok(a):
  resultat = 1.0/a
  return resultat  ## ok, return 1.0/a waere kuerzer

#######################################################################
# Nun der Hauptprogrammteil.
# Aufgabe: Zahl abfragen, gegebenenfalls Kehrwert berechnen

print "Kehrwert berechnen"
print "------------------"
print 

# Eingabe einer Zahl
a = raw_input("Eine Zahl bitte: ")
# Fasse die Eingabe nun als float auf. Das kann auch schief gehen.
# Moegliche Abhilfe: try/except verwenden... 
wert = float(a)

# Beispiel einer Fallunterscheidung mit if. 
# Beachte auch hier die Einrueckungen!
if (wert != 0):
  print "Der Kehrwert davon ist ",reziprok(wert)
else:
  print "Schwierige Aufgabe ... mal nachdenken ..."
  time.sleep(2)  ## bisschen Wartezeit...
  print "Naja, ich mach' Feierabend."
