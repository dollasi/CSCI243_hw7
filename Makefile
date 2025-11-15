#
# Created by gmakemake (Ubuntu Apr 19 2024) on Sat Nov 15 12:03:03 2025
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

# Note the addition of -Werror, which tells the compiler to treat
# all warning messages as fatal errors
CFLAGS=	-std=c99 -Wall -pedantic -Wextra -ggdb -Werror
CLIBFLAGS= -lm


########## End of flags from header.mak


CPP_FILES =	
C_FILES =	KStream.c mcrypt.c
PS_FILES =	
S_FILES =	
H_FILES =	KStream.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	KStream.o 

#
# Main targets
#

all:	mcrypt 

mcrypt:	mcrypt.o $(OBJFILES)
	$(CC) $(CFLAGS) -o mcrypt mcrypt.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

KStream.o:	KStream.h
mcrypt.o:	KStream.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) mcrypt.o core

realclean:        clean
	-/bin/rm -f mcrypt 
