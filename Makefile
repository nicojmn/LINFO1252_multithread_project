CC = gcc
# The flag -D_NOLOGS disable the logs generate by "log.h"
CFLAGS = -Wall -Werror -g -std=gnu99
# Used to colorize the output. Remove if we need to extracts logs_implem
CFLAGS += -D_COLOR
LIBS = -lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders

## COMPILATIONS
philosophers: philosophers/src/philosophers.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o "philosophers/"$@.o $^ $(LIBS)

producers_consumers: producers_consumers/src/prod_cons.c producers_consumers/src/buffer_implem.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o "producers_consumers/"$@.o $^ $(LIBS)

readers_writers: readers_writers/src/read_write.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o "readers_writers/"$@.o $^ $(LIBS)

all: philosophers producers_consumers readers_writers

# This command take a C source file and compile it to return a .o file
%.o: %.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<


## RUN PERF EVAL
perf_philo:
	./benchmark_tests/perf_evals/philosophers_pe.sh ./time_results/csv/philosophers.csv

perf_prod_cons:
	./benchmark_tests/perf_evals/producers_consumers_pe.sh ./time_results/csv/producers-consumers.csv


## TESTS
# Test for memory leak (
mem-check: CFLAGS += -D_NOLOGS
mem-check: clean all
	@printf "\n\n============================================\n||  Memory test for philosophers problem  ||\n============================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./philosophers/philosophers.o 20

	@printf "\n\n===================================================\n||  Memory test for producers-consumers problem  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./producers_consumers/producers_consumers.o 6 6

	@printf "\n\n===================================================\n||  Memory test for readers-writers problem  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./readers_writers/readers_writers.o 3 6

# Performs helgrind (safe threads check) test
threads-check: CFLAGS += -D_NOLOGS
threads-check: clean all
	@printf "\n\n============================================\n||  Memory test for philosophers problem  ||\n============================================\n\n"
	valgrind --tool=helgrind -s ./philosophers/philosophers.o 10

	@printf "\n\n===================================================\n||  Memory test for producers-consumers problem  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./producers_consumers/producers_consumers.o 2 3

	@printf "\n\n===================================================\n||  Memory test for readers-writers problem  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./readers_writers/readers_writers.o 2 3



## GRAPHS

# Produce graph
graph:
	/usr/bin/python3 ./benchmark_tests/graph_interpret/task1-graph.py


## CLEAN
# This command clean the project by deleting output file
clean:
	rm -f *.o
	rm -f ./philosophers/*.o
	rm -f ./producers_consumers/*.o
	rm -f ./readers_writers/*.o

.PHONY: clean philosophers producers_consumers readers_writers graph