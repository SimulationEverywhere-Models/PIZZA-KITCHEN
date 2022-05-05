.SUFFIXES : .cpp .o .c .y

CPP=g++
CC=gcc
AR=ar
YACPP=yacc

DEFINES_CPP=

#============================================================================
# Optimized Code - Requires more virtual memory.
OPTCPPFLAGS=-O3
#----------------------
# Not optimized
#OPTCPPFLAGS=
#============================================================================

# gcc < 2.8.x 
#DEFINES_CPP=-D_G_NO_EXTERN_TEMPLATES
#CPPFLAGS=-fhandle-exceptions 


#============================================================================
# gcc 2.8.x (y superiores):
# -------------------------
# Ver warnings:
CPPFLAGS += -Wall
# Ignorar warnings:
#CPPFLAGS += -w

# Include information for GDB:
#CPPFLAGS += -g

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# The next flag must be actived ONLY if we are compiling under Windows 95 !!!!
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#CPPFLAGS += -D__WINDOWS__
#============================================================================



DEFINES_C=


# If we are compiling for Unix
INCLUDES_CPP=-I/usr/include
# or if we are compiling for Windows 95
#INCLUDES_CPP=


INCLUDES_C=
CFLAGS=
DEBUGFLAGS=
LDFLAGS += -L. -g 

# if we are compiling for Windows 95, comment the last two lines



EXAMPLESOBJS=queue.o main.o generat.o cpu.o transduc.o trafico.o distri.o com.o linpack.o debug.o register.o cola.o pizzero.o admlug.o lugar.o
LIBNAME=simu
LIBS=-lsimu
ALLOBJS=${EXAMPLESOBJS} ${SIMOBJS} 
INIOBJS=initest.o ini.o
ALLSRCS=${ALLOBJS:.o=.cpp} gram.y 

all: simu drawlog

libs: libsimu.a

simu: ${ALLOBJS}  libsimu.a
	g++ ${LDFLAGS} -o $@ ${EXAMPLESOBJS} ${LIBS}

initest: ${INIOBJS} 
	${CPP} ${LDFLAGS} -o $@ ${INIOBJS} 

drawlog: drawlog.o libsimu.a
	g++ ${LDFLAGS} -o $@ drawlog.o ${LIBS}

makerand: makerand.o libsimu.a
	g++ ${LDFLAGS} -o $@ makerand.o ${LIBS}

toMap: toMap.o libsimu.a
	g++ ${LDFLAGS} -o $@ toMap.o ${LIBS}

toCDPP: toCDPP.o libsimu.a
	g++ ${LDFLAGS} -o $@ toCDPP.o ${LIBS}

randEvent: randEvent.o libsimu.a
	g++ ${LDFLAGS} -o $@ randEvent.o ${EXAMPLESOBJS} ${LIBS}

exptest: synnode.o
	g++ ${LDFLAGS} -o $@ synnode.o
	
parser: parser.o gram.o
	g++ ${LDFLAGS} -o $@ parser.o gram.o

libsimu.a: ${SIMOBJS}
	${AR} crs lib${LIBNAME}.a ${SIMOBJS}

clean:
	- rm -f *.o *.a simu core drawlog initest exptest parser makerand toMap

depend:
	makedepend -Y ${ALLSRCS}

backup:
	tar -cvf simu.tar *.cpp *.h *.c *.y makefile* *.ma *.ev *.vpj *.bat *.txt *.val *.inc *.map; gzip simu.tar; mv simu.tar.gz simu.tgz

########################
# Without Optimization
cola.o: cola.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

pizzero.o: pizzero.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

admlug.o: admlug.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

lugar.o: lugar.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

generat.o: generat.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

queue.o: queue.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

cpu.o: cpu.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

transduc.o: transduc.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

trafico.o: trafico.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

register.o: register.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

msgadm.o: msgadm.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

root.o: root.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

parser.o: parser.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

main.o: main.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

toMap.o: toMap.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

toCDPP.o: toCDPP.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

makerand.o: makerand.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

mainsimu.o: mainsimu.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

# Uncomment these lines only for Windows
#macroexp.o: macroexp.cpp
#	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<
#
#flatcoup.o: flatcoup.cpp
#	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<
########################

.cpp.o:
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} ${OPTCPPFLAGS} $<

.c.o:
	${CC} -c ${INCLUDES_C} ${DEFINES_C}  ${DEBUGFLAGS} ${CFLAGS} ${OPTCPPFLAGS} $<

.y.o:
	bison -d -v -o gram.c gram.y
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} ${OPTCPPFLAGS} ${@:.o=.c} 
	rm $*.c
	
# DO NOT DELETE

queue.o: queue.h atomic.h model.h port.h modelid.h time.h portlist.h real.h
queue.o: undefd.h impresion.h tbool.h except.h stringp.h value.h evaldeb.h
queue.o: cellpos.h ntupla.h procadm.h process.h message.h strutil.h
queue.o: mainsimu.h root.h event.h ini.h loader.h ltranadm.h
main.o: stdaload.h loader.h time.h evaldeb.h macroexp.h except.h stringp.h
main.o: netload.h mainsimu.h root.h event.h real.h undefd.h impresion.h
main.o: tbool.h value.h port.h modelid.h process.h procadm.h ini.h ltranadm.h
main.o: cellpos.h ntupla.h portlist.h model.h
generat.o: generat.h atomic.h model.h port.h modelid.h time.h portlist.h
generat.o: real.h undefd.h impresion.h tbool.h except.h stringp.h value.h
generat.o: evaldeb.h cellpos.h ntupla.h procadm.h process.h message.h
generat.o: strutil.h mainsimu.h root.h event.h ini.h loader.h ltranadm.h
generat.o: distri.h
cpu.o: cpu.h atomic.h model.h port.h modelid.h time.h portlist.h real.h
cpu.o: undefd.h impresion.h tbool.h except.h stringp.h value.h evaldeb.h
cpu.o: cellpos.h ntupla.h procadm.h process.h message.h strutil.h distri.h
cpu.o: mainsimu.h root.h event.h ini.h loader.h ltranadm.h
transduc.o: transduc.h atomic.h model.h port.h modelid.h time.h portlist.h
transduc.o: real.h undefd.h impresion.h tbool.h except.h stringp.h value.h
transduc.o: evaldeb.h cellpos.h ntupla.h procadm.h process.h message.h
transduc.o: strutil.h mainsimu.h root.h event.h ini.h loader.h ltranadm.h
trafico.o: time.h trafico.h atomic.h model.h port.h modelid.h portlist.h
trafico.o: real.h undefd.h impresion.h tbool.h except.h stringp.h value.h
trafico.o: evaldeb.h cellpos.h ntupla.h procadm.h process.h message.h
trafico.o: strutil.h
distri.o: time.h distri.h except.h stringp.h strutil.h real.h undefd.h
distri.o: impresion.h tbool.h value.h evaldeb.h
debug.o: debug.h tdcell.h atomcell.h portlist.h real.h undefd.h impresion.h
debug.o: tbool.h except.h stringp.h value.h evaldeb.h port.h modelid.h
debug.o: cellpos.h ntupla.h atomic.h model.h time.h procadm.h process.h
debug.o: neighval.h mylist.h coupcell.h coupled.h ltranadm.h cellstate.h
register.o: modeladm.h mainsimu.h root.h event.h time.h real.h undefd.h
register.o: impresion.h tbool.h except.h stringp.h value.h evaldeb.h port.h
register.o: modelid.h process.h procadm.h ini.h loader.h ltranadm.h cellpos.h
register.o: ntupla.h portlist.h model.h queue.h atomic.h generat.h cpu.h
register.o: transduc.h message.h strutil.h trafico.h cola.h pizzero.h admlug.h
register.o: lugar.h
gram.o: synnode.h tbool.h except.h stringp.h real.h undefd.h impresion.h
gram.o: value.h evaldeb.h realfunc.h ltranadm.h cellpos.h ntupla.h portlist.h
gram.o: port.h modelid.h time.h model.h procadm.h process.h parser.h
cola.o: cola.h atomic.h model.h port.h modelid.h time.h portlist.h real.h
cola.o: undefd.h impresion.h tbool.h except.h stringp.h value.h evaldeb.h
cola.o: cellpos.h ntupla.h procadm.h process.h message.h strutil.h
cola.o: mainsimu.h root.h event.h ini.h loader.h ltranadm.h constpiz.h
pizzero.o: pizzero.h atomic.h model.h port.h modelid.h time.h portlist.h real.h
pizzero.o: undefd.h impresion.h tbool.h except.h stringp.h value.h evaldeb.h
pizzero.o: cellpos.h ntupla.h procadm.h process.h message.h strutil.h
pizzero.o: mainsimu.h root.h event.h ini.h loader.h ltranadm.h constpiz.h
admlug.o: admlug.h atomic.h model.h port.h modelid.h time.h portlist.h real.h
admlug.o: undefd.h impresion.h tbool.h except.h stringp.h value.h evaldeb.h
admlug.o: cellpos.h ntupla.h procadm.h process.h message.h strutil.h
admlug.o: mainsimu.h root.h event.h ini.h loader.h ltranadm.h constpiz.h
lugar.o: lugar.h atomic.h model.h port.h modelid.h time.h portlist.h real.h
lugar.o: undefd.h impresion.h tbool.h except.h stringp.h value.h evaldeb.h
lugar.o: cellpos.h ntupla.h procadm.h process.h message.h strutil.h
lugar.o: mainsimu.h root.h event.h ini.h loader.h ltranadm.h constpiz.h
lugar.o: realfunc.h
