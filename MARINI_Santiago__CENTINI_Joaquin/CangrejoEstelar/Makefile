CC = gcc
OBJS = veinteveinte.o avl_tree.o main.o
BINARY = grafo
CFLAGS = -g -Wall -Wextra -O0 -std=c99

all: program

program: $(OBJS) 
		@$(CC) -o $(BINARY) $?

%.o: %.c 
		$(CC) $(CFLAGS) -c $< -o $@

mem_check: program	
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BINARY) anna.txt

clean:
		@rm -rf $(BINARY) $(OBJS)
