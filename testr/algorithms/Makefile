PROJ_NAME_1 = main

CC = gcc
CFLAGS = -lm -g -Wall

C_SOURCE = $(wildcard ./src/*.c)

H_SOURCE = $(wildcard ./headers/*.h)

OBJ = $(C_SOURCE:./src/%.c = ./objects/%.o)

all: $(PROJ_NAME_1)

$(PROJ_NAME_1): $(OBJ) ./objects/main.o
	$(CC) -o $@ $^ $(CFLAGS)

./objects/%.o: ./src/%.c ./headers/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main.o: main.c $(H_SOURCE)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LIB): $(OBJ) ./objects/main_deque.o
	ar -rcs $@ $^

clean:
	rm -rf ./objects/*.o $(PROJ_NAME_1)