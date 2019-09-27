SOURCE	= $(wildcard *.cpp) $(wildcard *.c)
OBJS	= main.o glad.o
HEADER	= head.h shader.hpp
OUT	= fractal
CC	 = g++

FLAGS	 = -c -O3 -Wall -std=c++17

macLFLAGS     = -framework openGL -lglfw
linuxLFLAGS	 = -lGL -lGLU -lglfw -ldl

OS := $(shell uname)


all: $(OBJS)
ifeq ($(OS), Darwin)
	$(CC) $(OBJS) -o $(OUT) $(macLFLAGS)
else
	$(CC) $(OBJS) -o $(OUT) $(linuxLFLAGS)
endif

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

glad.o: glad.c
	$(CC) $(FLAGS) glad.c

clean:
	rm -f $(OBJS)

cleanall:
	rm -f $(OBJS) $(OUT)

test:
	echo $(OS)