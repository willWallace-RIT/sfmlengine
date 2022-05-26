CXX=g++
WCXX=x86_64-w64-mingw32-g++
LDFLAGS=-g -Wall -Wextra -Wpedantic
CPPFLAGS=-g -Wall -Wextra -Wpedantic 
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system 
LDLINUX= -lGL
LDWIN= -lopengl32
WINC=-I../SFML-2.5.1/include/
WLIBS=-L../SFML-2.5.1/lib/
RM=rm -f

SRCS=game.cpp mainloop.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
all:linux

wondows: EXX=$(WCXX)
wondows: OUTP=wingame
wondows: LDOPTS = $(LDLIBS) $(LDWIN) $(WLIBS)
wondows: INC = $(WINC)

linux: EXX=$(CXX)
linux: INC=
linux: LDOPTS = $(LDLIBS) $(LDWIN)
linux: rungame
game.o: game.cpp
	

	$(EXX) $(LDFLAGS) $(INC) -c game.cpp -o game.o  $(LDOPTS)

mainloop.o: mainloop.cpp 
	$(EXX) $(LDFLAGS) $(INC) -c mainloop.cpp -o mainloop.o  $(LDOPTS)
wondows: $(OBJS)
	$(EXX) $(LDFLAGS) $(INC) -o $(OUTP) $(OBJS)  $(LDOPTS)

rungame: $(OBJS)
	$(EXX) $(LDFLAGS)  -o rungame $(OBJS) $(LDLIBS) $(LDLINUX)


clean:
	$(RM) $(OBJS)

distclean:
	$(RM) rungame
