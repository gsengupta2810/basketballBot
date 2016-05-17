CC = g++
CFLAGS = -g 
PROG=executable
OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

all:main.cpp worldState.cpp motion.cpp
	$(CC) $(CFLAGS) -o $(PROG) main.cpp worldState.cpp motion.cpp $(LIBS)
clean:
	rm -rf executable