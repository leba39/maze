CXX = gcc
CXXFLAGS = -g

SONAME 	= laberinto
SRC	= src/main.c        \
	  src/maze.c        \
	  src/stack.c	    \
	  src/location.c    \




#individual objects
OBJS	= $(SRC:.c=.o)
.c.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS) 

#compilation:
$(SONAME): $(OBJS) $(SRC)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(SONAME)

.PHONY: all clean

clean:
	rm -f $(OBJS) $(SONAME) 
all: clean $(SONAME)
