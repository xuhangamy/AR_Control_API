#makefile for msvc using nmake

#!include <Win32.Mak>

OUTDIR = lib
INCDIR = include
SRC = src\*.cpp
OBJFILES = lib\*.obj
TARGET = lib\ARDrone.lib

all: $(OUTDIR) $(OUTDIR)\$(TARGET)

$(OUTDIR):
	if not exitst "$(OUTDIR)/$(NULL)" mkdir $(OUTDIR)

$(OUTDIR)\*.obj: $(SRC)
	cl.exe -c /GS /analyze- /W3 /Zc:wchar_t /ZI /Gm /Od /sdl /fp:precise /D "WIN32" /D "_DEBUG" /D "_LIB" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /EHsc /nologo  /I $(INCDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /Fp"$(OUTDIR)\\"  $(SRC)

$(OUTDIR)\$(TARGET): $(OUTDIR)\*.obj
	lib.exe /VERBOSE /MACHINE:X86  /OUT:$(TARGET)  $(OBJFILES)

clean:
	$(CLEANUP)
