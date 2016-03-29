
#EXTRA_DIST = Makefile.mak

#INCLUDES = -I$(top_srcdir)/include

bin_PROGRAMS = synthts_vr

synthts_vr_SOURCES = synthts_vr.cpp 

synthts_vr_LDFLAGS = -pthread

synthts_vr_LDADD = ../lib/etana/libEtAna.a ../lib/fsc/libFsc.a ../lib/engine/libHTSEngine.a ../lib/label/libEtLab.a

DISTCLEANFILES = *.log *.out *~

MAINTAINERCLEANFILES = Makefile.in
