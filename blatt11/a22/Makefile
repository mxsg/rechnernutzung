# /***************************************************************************
# --------------------------------------------------------------------------
# Sample Makefile for the computer exercises
# --------------------------------------------------------------------------
# modification log:
#
# 24.12.2010, G. Quast  general version - program to make as 
#              defined in variable SOURCE
# ***************************************************************************/

# ----------------------------------------------
# >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# >>>>>>> define program to compile here  <<<<<<
SOURCE  :=  PDFs

# ----------------------------------------------

# >>> Begin of generic make file for ROOT applications
# Get the correct root configuration
ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

# Set the compiler options
CXX           = g++               #use g++ as compiler
CXXFLAGS      = -g -O -Wall -fPIC #set compiler options
	                          #-g compile with debug information
                                  #-O optimize
                                  #-Wall show warnings for everything
                                  #-fPIC compile source file as sharable object  	
# Set the linker options
LD            = g++               #use g++ for linking
LDFLAGS       = -O           
SOFLAGS       = -shared

#######################
CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------

# By default, compile template
default : $(SOURCE)

# Compile solution as well
all: $(SOURCE) $(SOURCE)_lsg

#------------------------------------------------------------------------------
# Template
$(SOURCE).o: $(SOURCE).cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -c $(SOURCE).cpp -o bin/$(SOURCE).o

$(SOURCE): $(SOURCE).o
	$(LD) $(LDFLAGS) bin/$(SOURCE).o $(LIBS) -o bin/$(SOURCE)

#------------------------------------------------------------------------------
# Solution
$(SOURCE)_lsg.o: $(SOURCE)_lsg.C
	$(CXX) $(CXXFLAGS) -c $(SOURCE)_lsg.C -o $(SOURCE)_lsg.o

$(SOURCE)_lsg: $(SOURCE)_lsg.o
	$(LD) $(LDFLAGS) $(SOURCE)_lsg.o $(LIBS) -o $(SOURCE)_lsg	

#------------------------------------------------------------------------------
#clean up
clean:
	@rm -rf bin/
