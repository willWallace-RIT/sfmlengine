CXX=x86_64-w64-mingw32-g++

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
all: rungame

game.o: game.cpp 
	$(WCXX) $(LDFLAGS) $(WINC) -c game.cpp -o game.o  $(LDLIBS) $(LDWIN) $(WLIBS)

mainloop.o: mainloop.cpp 
	$(WCXX) $(LDFLAGS) $(WINC) -c mainloop.cpp -o mainloop.o  $(LDLIBS) $(LDWIN) $(WLIBS)
wondows: $(OBJS)
	$(WCXX) $(LDFLAGS) $(WINC) -o winGame $(OBJS)  $(LDLIBS) $(LDWIN) $(WLIBS)

rungame: $(OBJS)
	$(CXX) $(LDFLAGS)  -o rungame $(OBJS) $(LDLIBS) $(LDLINUX)


clean:
	$(RM) $(OBJS)

distclean:
	$(RM) rungame
