PROJ_NAME_1 = main_deque
PROJ_NAME_2 = main_hash
PROJ_NAME_3 = main_heap
PROJ_NAME_4 = main_algorithms

CC = gcc
CFLAGS = -lm -g -Wall

C_SOURCE = $(wildcard ./src/*.c)

H_SOURCE = $(wildcard ./headers/*.h)

OBJ = $(C_SOURCE:./src/%.c = ./objects/%.o)

all: $(PROJ_NAME_1) $(PROJ_NAME_2) $(PROJ_NAME_3) $(PROJ_NAME_4)

$(PROJ_NAME_1): $(OBJ) ./objects/main_deque.o
	$(CC) -o $@ $^ $(CFLAGS)

$(PROJ_NAME_2): $(OBJ) ./objects/main_hash.o
	$(CC) -o $@ $^ $(CFLAGS)

$(PROJ_NAME_3): $(OBJ) ./objects/main_heap.o
	$(CC) -o $@ $^ $(CFLAGS)

$(PROJ_NAME_4): $(OBJ) ./objects/main_algorithms.o
	$(CC) -o $@ $^ $(CFLAGS)

./objects/%.o: ./src/%.c ./headers/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main_deque.o: main_deque.c $(H_SOURCE)
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main_hash.o: main_hash.c $(H_SOURCE)
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main_heap.o: main_heap.c $(H_SOURCE)
	$(CC) -c -o $@ $< $(CFLAGS)

./objects/main_algorithms.o: main_algorithms.c $(H_SOURCE)
	$(CC) -c -o $@ $< $(CFLAGS)

$(LIB): $(OBJ) ./objects/main_deque.o ./objects/main_hash.o ./objects/main_heap.o ./objects/main_algorithms.o
	ar -rcs $@ $^

clean:
	rm -rf ./objects/*.o $(PROJ_NAME_1) $(PROJ_NAME_2) $(PROJ_NAME_3) $(PROJ_NAME_4)