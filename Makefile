CC = gcc
CFLAGS = -Wall -Werror -g -std=gnu99
LIBS = -lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders

philosophers: philosophers/src/philosophers.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o "philosophers/"$@.o $^ $(LIBS)

producers_consumers: producers_consumers/src/prod_cons.c producers_consumers/src/buffer_implem.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o "producers_consumers/"$@.o $^ $(LIBS)

all: philosophers producers_consumers

# This command take a C source file and compile it to return a .o file
%.o: %.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

# This command clean the project by deleting output file
clean:
	rm -f *.o
	rm -f ./philosophers/*.o
	rm -f ./producers_consumers/*.o

.PHONY: clean philosophers producers_consumers