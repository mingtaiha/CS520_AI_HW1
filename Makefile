CFLAGS = -std=c++11 -g `pkg-config --cflags opencv`
LIBS = -larmadillo -lSDL2 `pkg-config --libs opencv`
OBJS = astar.o searchtree.o load_maze.o state.o sim.o svec.o maze_gen.o mapcheck.o sim_window.o draw.o heuristic.o

all: $(OBJS) sim

sim: $(OBJS)
	g++ $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	g++ $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o sim maze_gen
