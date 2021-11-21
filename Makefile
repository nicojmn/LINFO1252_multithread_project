CC = gcc
CFLAGS = -Wall -Werror -g -std=gnu99
LIBS = -lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders

all: philosophers/src/philosophers.c producers_consumers/src/prod_cons.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@.o $^ $(LIBS)

philosophers: philosophers/src/philosophers.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@.o $^ $(LIBS)

producer_consumer: producers_consumers/src/prod_cons.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@.o $^ $(LIBS)

# This command take a C source file and compile it to return a .o file
%.o: %.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

# This command clean the project by deleting output file
clean:
	rm -f *.o
	rm -f ./philosophers/src/*.o

.PHONY: philosophers clean