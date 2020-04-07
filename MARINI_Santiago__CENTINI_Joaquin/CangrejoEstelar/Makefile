CC = gcc
OBJS = veinteveinte.o avl_tree.o main.o
BINARY = grafo
CFLAGS = -g -Wall -Wextra -O3 -std=c99

all: program

program: $(OBJS) 
		$(CC) -o $(BINARY) $?

%.o: %.c 
		$(CC) $(CFLAGS) -c $< -o $@

mem_check: 
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BINARY) miles1500.corr


clean:
		@rm -rf $(BINARY) $(OBJS)
