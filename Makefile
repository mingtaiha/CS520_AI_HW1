CFLAGS = -std=c++11
LIBS = -larmadilllo -lSDL2
OBJS = heuristic.o maze_gen.o mapcheck.o pqueue.o sim_window.o drawgrid.o sim.o

all: $(OBJS)

%.o: %.cpp
	g++ $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o sim maze_gen
