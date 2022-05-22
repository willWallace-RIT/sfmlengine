CXX=g++
LDFLAGS=-g -Wall -Wextra -Wpedantic
CPPFLAGS=-g -Wall -Wextra -Wpedantic
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -lGL
RM=rm -f

SRCS=game.cpp mainloop.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
all: rungame

rungame: $(OBJS)
	$(CXX) $(LDFLAGS) -o rungame $(OBJS) $(LDLIBS)


clean:
	$(RM) $(OBJS)

distclean:
	$(RM) rungame
