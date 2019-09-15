SOURCE	= $(wildcard *.cpp) $(wildcard *.c)
OBJS	= main.o glad.o
HEADER	= head.h shader.hpp
OUT	= fractal
CC	 = g++
FLAGS	 = -c -O3 -Wall -std=c++17
LFLAGS	 = -lGL -lGLU -lglfw -ldl

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

glad.o: glad.c
	$(CC) $(FLAGS) glad.c

clean:
	rm -f $(OBJS)

cleanall:
	rm -f $(OBJS) $(OUT)