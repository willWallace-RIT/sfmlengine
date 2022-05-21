LDFLAGS= -L/lib/ -l:libstdc++.a -static
CFLAGS= -Wall -W -std=c++14 -pedantic
all: mainloop.o game.o

	g++ $(LDFLAGS) $(CFLAGS) -o prog mainloop.o game.o

clean:
	$(RM) prog
