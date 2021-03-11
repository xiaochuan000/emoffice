# INTEL=0
LIBSRC= regcvtr.cc quadrature.cc cvtr.cc vtr.cc tensor.cc ctensor.cc tetra.cc node3d.cc mesh3d.cc edge3d.cc
LIBOBJ= $(subst .cc,.o,$(LIBSRC))
LIBGDBOBJ= $(subst .cc,.go,$(LIBSRC))
LIBFLOARSRC= float_regcvtr.cc float_cvtr.cc float_vtr.cc float_tensor.cc float_ctensor.cc tetra.cc node3d.cc mesh3d.cc edge3d.cc quadrature.cc 
LIBFLOAROBJ = $(subst .cc,.o,$(LIBFLOARSRC))
LIBFLOARGDBOBJ = $(subst .cc,.go,$(LIBFLOARSRC))
GLOBALFILE= makefile EMcomplex.h 
OPT=-O9

ifneq ( $(INTEL) ,1 )
CXX=$(EMoffice_CXX)
INTEL_EXT=
else
CXX=icpc
INTEL_EXT=_intel
endif

all: libEMoffice_Base$(INTEL_EXT).a libEMoffice_Basef$(INTEL_EXT).a
gdb: libEMoffice_Base_gdb$(INTEL_EXT).a libEMoffice_Basef_gdb$(INTEL_EXT).a

#gdb: all
#gdb: OPT:= -O0 -g
%.o: %.cc $(subst .cc,.h,$<) $(GLOBALFILE) 
	$(CXX) -c $(OPT) -I. $< 
%.go: %.cc $(subst .cc,.h,$<) $(GLOBALFILE)
	$(CXX) -c -g -O0 -I. $<  -o $@
libEMoffice_Base$(INTEL_EXT).a: $(LIBOBJ) $(GLOBALFILE)  
	ar rc libEMoffice_Base$(INTEL_EXT).a $(LIBOBJ)
	mv libEMoffice_Base$(INTEL_EXT).a $(EMoffice_HOME)/lib
	cp *.h  $(EMoffice_HOME)/include -f
libEMoffice_Basef$(INTEL_EXT).a: $(LIBFLOAROBJ) $(GLOBALFILE)
	ar rc libEMoffice_Basef$(INTEL_EXT).a $(LIBFLOAROBJ)
	mv libEMoffice_Basef$(INTEL_EXT).a $(EMoffice_HOME)/lib
	cp *.h  $(EMoffice_HOME)/include -f

libEMoffice_Base$(INTEL_EXT)_gdb.a: $(LIBGDBOBJ) $(GLOBALFILE)  
	ar rc libEMoffice_Base$(INTEL_EXT)_gdb.a $(LIBGDBOBJ)
	mv libEMoffice_Base$(INTEL_EXT)_gdb.a $(EMoffice_HOME)/lib
	cp *.h  $(EMoffice_HOME)/include -f
libEMoffice_Basef$(INTEL_EXT)_gdb.a: $(LIBFLOARGDBOBJ) $(GLOBALFILE)
	ar rc libEMoffice_Basef$(INTEL_EXT)_gdb.a $(LIBFLOARGDBOBJ)
	mv libEMoffice_Basef$(INTEL_EXT)_gdb.a $(EMoffice_HOME)/lib
	cp *.h  $(EMoffice_HOME)/include -f


clean:
	rm *.o *.go *~ -rf
.PHONY: clean all
