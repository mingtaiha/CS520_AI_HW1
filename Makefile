CFLAGS = -std=c++11
LIBS = -larmadillo -lSDL2
OBJS = heuristic.o maze_gen.o mapcheck.o pqueue.o sim_window.o draw.o sim.o astar.o

all: $(OBJS) sim

sim: $(OBJS)
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	g++ $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o sim maze_gen
