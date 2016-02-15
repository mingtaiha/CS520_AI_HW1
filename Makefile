CFLAGS = -std=c++11 -O3
LIBS = -larmadillo -lSDL2
OBJS = astar.o searchstate.o state.o sim.o svec.o maze_gen.o mapcheck.o sim_window.o draw.o heuristic.o

all: $(OBJS) sim

sim: $(OBJS)
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	g++ $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o sim maze_gen
