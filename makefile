LDFLAGS= -L/lib/ -l:libstdc++.a -static
CFLAGS= -Wall -W -std=c++17 -pedantic
all: mainloop.o game.o

	g++ $(LDFLAGS) $(CFLAGS) -o prog mainloop.o game.o

clean:
	$(RM) prog
