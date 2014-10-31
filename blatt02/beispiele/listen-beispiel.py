#!/usr/bin/python
#######################################################################
#
# RECHNERNUTZUNG in der Physik, WS 14/15
#
# Einfuehrung Listen
#
# Ausfuehren dieses Programms: python PROGRAMMNAME
# Dieses Programm ist in der Sprachversion 2 von python geschrieben.

# Ein kleiner Crashkurs zu Listen
# In Python werden "Felder" als sogenannte Listen dargestellt.

#######################################################################
print "--1-- Definition von Listen"
#######################################################################

l1 = [1.1,2,3]    ## Liste mit drei expliziten Elementen
l2 = []           ## eine leere Liste
l3 = list()       ## andere Variante fuer leere Liste
l4 = ["a"] * 12   ## Liste hat 12 Eintraege, alle sind "a"
l5 = range(5,18)  ## Liste mit Einträgen 5...17  
                  ##    (die obere Grenze gehoert nicht dazu!)
print "Liste l5: ",l5

# Es ist weder notwendig eine Listenlaenge noch den Datentyp,
# der in der Liste steht, anzugeben. Listen koennen sogar verschiedene
# Datentypen enthalten.

#######################################################################
print "--2-- Zugriff auf Listen"
#######################################################################

print "Laenge der Liste l1: ", len(l1)
print "Element am Anfang: ",l1[0]  ## Indizierung startet bei Null!
print "Die ganze Liste: ",l1       ## bequem!
# Ausschnitte koennen mit liste[start:stop:step]
# gebildet werden, jedes der Argumente kann auch wegfallen
# (der voreingestellte "step" ist 1)
print l5[3:13:2]

# Schleifen ueber Listen
for element in l1:
  print "Element: ",element
# alternativ: ueber Indizes zugreifen
for i in range(len(l1)):
  print "Index ",i," Element",l1[i]
# noch eine Alternative mit Indizes:
for i,elem in enumerate(l1):
  print "Index ",i," Element",elem
# (dabei wird verwendet, dass python konstrukte der Form
#   a,b = 1,2  erlaubt. Also mehrere Werte gleichzeitig zuweisen)

# negative Argumente werden um die Listenlaenge ergaenzt,
# d.h. liste[-1] steht fuer das letzte Element

#######################################################################
print "--3-- Listen modifizieren"
#######################################################################

# ersetzen:
l1[2] = 3.14159     # ein Element neu setzen
l5[0:3] = range(3)  # eine ganze Teilliste neu setzen
print "l5 ist nun: ",l5

# anhaengen/einfuegen
l1.append(5)               # einzelnes Element anhaengen
l1.extend(range(16,23,2))  # andere Liste anhaengen 
l1.insert(3,4.4)           # an einer Position einfuegen
print "l1 nach anhaengen:",l1
l6 = l5 + l4               # auch so geht aneinanderhaengen von listen
                           # vorsicht aber: bei numpy-arrays ist "+"
                           # element-addition.


# loeschen
del l1[0]        # erstes Element loeschen
del l1[-3:-1]    # letzte drei Elemente loeschen
item = l1.pop(2) # drittes Element ermitteln und loeschen
print "das dritte Element: ",item
print "und l1 nach der Loescherei: ",l1

#######################################################################
print "--4-- Kopien?!"
#######################################################################

l1 = l2 = ["a","b","c"]  ## l1 und l2 sind das gleiche Objekt
   ## Erklaerung: Listen sind durch einen Zeiger auf die Liste vereinbart
   ## Uebrigens: Auch bei Funktionsaufrufen wird der Zeiger uebergeben,
   ##   also keine Kopie der Liste erstellt.
l2[0] = "Ooooooops"
print l1[0]             ## hier der Beleg.

# gleiches passiert auch, wenn 
l3 = l1
# geschrieben wird.

# falls eine echte kopie noetig ist:
lcopy = l1[:]  # dieser "slice" der ganzen liste kopiert!
# dann sind lcopy und l1 unabhaengig
l1[0] = "Ich will das nicht lesen!"
print lcopy[0] 

# Achtung: "for .. in list:" Anweisungen, die die Liste kuerzen/verlaengern:
# Hier muss irgendwann eine Kopie angelegt werden, sonst werden
# Element doppelt oder gar nicht abgegangen.
# schematisches Beispiel
# for object in L[:]:
#   if some-condition:
#     del L[index]
# der "slice" in der ersten Beispielzeile ist noetig!

#######################################################################
print "--5-- Weiteres mit Listen"
#######################################################################

# sortieren:               l1.sort()
# suchen:                  l1.index("q")   (evtl. mit try/except)
# zaehlen:                 l1.count("q")
# umkehren:                l1.reverse()
# index-wertpaar erzeigen: enumerate(l1)
# funktionales programmieren:
#   zahlen = [1, 2, 3, 4, 5]
#   zweierpotenzen = [2 ** n for n in zahlen]

# Hinweis am Rande: Numpy-Felder verhalten sich etwas anders als Listen:
# (1) es kann nur ein identischer Datentyp vorkommen,
# (2) es sind viele Rechenoperationen definiert, die einfach
#     mit dem ganzen Feld arbeiten.
