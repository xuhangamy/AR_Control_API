# makefile for fly_recv demo

OUTDIR = bin
INCDIR = ../../include
src = ../fly_recv.cpp
srcf = fly_recv
extlib = ../../lib/ARDrone.lib

all: "$(OUTDIR)\$(srcf)

$(OUTDIR)\$(src).obj: $(src)
	cl.exe -c /GS /analyze- /W3 /Zc:wchar_t /ZI /Gm /sdl /fp:precise /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_LIB" /D "_UNICODE" /D "UNICODE" /errorReport:prompt /WX- /Zc:forScope /RTC1 /Gd /Oy- /MDd /EHsc /nologo /I $(INCDIR) /Fo"$(OUTDIR)\\" /Fd"$(OUTDIR)\\" /Fp"$(OUTDIR)\\" $(src)

$(OUTDIR)\$(srcf):$(OUTDIR)\$(src)
	link.exe /OUT:$(srcf).exe $(OUTDIR)\$(srcf).obj $(extlib)

clean:
	$(CLEANUP)
