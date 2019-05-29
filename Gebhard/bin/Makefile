COMPILER=$(CXX)
LINKER=$(CXX)

CFLAGS=-c -g -Wall -O2 -DBETA_VER
LDFLAGS=-g
LIBS=-lm

#	Ausgabeverzeichnisse
#

BINDIR=../bin
OUTPUTDIR=../output

#	sed benoetigt \/ statt /
#
SEDOUT=$(subst /,\/,$(OUTPUTDIR))

#	Name des ausfuehrbaren Programms
#
BINNAME=permtest

#	Liste der Source-Dateien
#
SOURCE=\
main.cc \
Pitman.cc \
Pitman.TransformData.cc \
Tritchler.cc \
FFT.cc \
Green.cc \
Timer.cc \
Pitman.DataInput.cc \
Pitman.OptionHandler.cc \
Pitman.CalcValues.cc \
Permutationstest.cc

#	Liste der Objekt-Dateien
#
OBJS=$(patsubst %.cc,$(OUTPUTDIR)/%.o,$(SOURCE))

#	Liste der Dateien mit expliziten Regeln
#	Diese Dateien werden automatisch erzeugt
#	und in der Datei depend zusammengefasst
#
DEP=$(patsubst %.o,%.d,$(OBJS))

all: $(BINDIR)/$(BINNAME) manual

#	Regel fuer Linker
#	Die Datei today.cc enthaelt das aktuelle Datum der Kompilierung (und sonst nichts),
#	muss also vor jedem linken neu kompiliert werden.
#
$(BINDIR)/$(BINNAME): $(OBJS)
	$(COMPILER) $(CFLAGS) -o $(OUTPUTDIR)/today.o today.cc
	$(LINKER) $(LDFLAGS) -o $(BINDIR)/$(BINNAME) $(OBJS) $(OUTPUTDIR)/today.o $(LIBS)

#	explizite Regeln laden
#
include depend

#	implizite Regel fuer Compiler
#
$(OUTPUTDIR)/%.o:%.cc
	$(COMPILER) $(CFLAGS) -o $@ $<

#	explizite Regeln in einer Datei zusammenfassen
#
depend: $(DEP)
	cat $(DEP) > depend

#	explizite Regeln erzeugen
#
$(OUTPUTDIR)/%.d:%.cc
	$(COMPILER) -MM $< | sed "s/.*\.o/$(SEDOUT)\/&/g" > $@

#	Manual formatieren
#
manual: $(BINNAME).man.ps $(BINNAME).man.dvi

$(BINNAME).man.ps: $(BINNAME).1
	groff -man $(BINNAME).1 > $(BINNAME).man.ps

$(BINNAME).man.dvi: $(BINNAME).1
	groff -Tdvi -man $(BINNAME).1 > $(BINNAME).man.dvi

