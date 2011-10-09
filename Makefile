CHARMC          = /Users/nikhil/collegestuff/charm/bin/charmc
OPTS            = -O3  -DUSE_SECTION_MULTICAST

all: mol3d

mol3d: Main.o Patch.o Compute.o mol3d.decl.h
        $(CHARMC) $(OPTS) -module CkMulticast -module CommonLBs \
	-language charm++ -o mol3d Main.o Patch.o Compute.o

Main.o: Main.C Main.h mol3d.decl.h physics.h
        $(CHARMC) $(OPTS) -o Main.o Main.C

Patch.o: Patch.C Patch.h mol3d.decl.h physics.h
        $(CHARMC) $(OPTS) -o Patch.o Patch.C

Compute.o: Compute.C Compute.h mol3d.decl.h physics.h
        $(CHARMC) $(OPTS) -o Compute.o Compute.C

mol3d.decl.h:	mol3d.ci
	$(CHARMC) $(OPTS) mol3d.ci

clean:
	rm -f *.decl.h *.def.h *.o mol3d mol3d.prj charmrun