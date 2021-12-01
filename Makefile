CC = gcc
# The flag -D_NOLOGS disable the logs generate by "log.h"
CFLAGS = -Wall -Werror -g -std=gnu99
# Used to colorize the output. Remove if we need to extracts logs_implem
CFLAGS += -D_COLOR
LIBS = -lcunit -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders

## COMPILATIONS
philosophers_posix: part1/philosophers/src/philosophers.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o "part1/philosophers/"$@.o $^ $(LIBS)

producers_consumers_posix: part1/producers_consumers/src/prod_cons.c part1/producers_consumers/src/buffer_implem.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o "part1/producers_consumers/"$@.o $^ $(LIBS)

readers_writers_posix: part1/readers_writers/src/read_write.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o "part1/readers_writers/"$@.o $^ $(LIBS)

test_and_set: active_lock/src/active_lock.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o "active_lock/"$@.o $^ $(LIBS)


compile_posix: philosophers_posix producers_consumers_posix readers_writers_posix

all: philosophers_posix producers_consumers_posix readers_writers_posix test_and_set

# This command take a C source file and compile it to return a .o file
%.o: %.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<


## RUN PERF EVAL

perf_posix:
	/usr/bin/bash ./benchmark_tests/perf_evals/philosophers_pe.sh ./time_results/csv/philosophers_posix.csv
	/usr/bin/bash ./benchmark_tests/perf_evals/producers_consumers_pe.sh ./time_results/csv/producers-consumers_posix.csv
	/usr/bin/bash ./benchmark_tests/perf_evals/readers_writers_pe.sh ./time_results/csv/readers-writers_posix.csv

## TESTS
# Test for memory leak
mem-check: CFLAGS += -D_NOLOGS
mem-check: clean all
	@printf "\n\n============================================\n||  Memory test for philosophers problem  ||\n============================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./part1/philosophers/philosophers_posix.o 20

	@printf "\n\n===================================================\n||  Memory test for producers-consumers problem  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./part1/producers_consumers/producers_consumers_posix.o 6 6

	@printf "\n\n===================================================\n||  Memory test for readers-writers problem  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./part1/readers_writers/readers_writers_posix.o 3 6

	@printf "\n\n===================================================\n||  Memory test for test_and_set algorithm  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./active_lock/test_and_set.o 4

# Performs helgrind (safe threads check) test
threads-check: CFLAGS += -D_NOLOGS
threads-check: clean all
	@printf "\n\n============================================\n||  Memory test for philosophers problem  ||\n============================================\n\n"
	valgrind --tool=helgrind -s ./part1/philosophers/philosophers_posix.o 10

	@printf "\n\n===================================================\n||  Memory test for producers-consumers problem  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./part1/producers_consumers/producers_consumers_posix.o 2 3

	@printf "\n\n===================================================\n||  Memory test for readers-writers problem  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./part1/readers_writers/readers_writers_posix.o 2 3

	@printf "\n\n===================================================\n||  Memory test for test_and_set algorithm  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./active_lock/test_and_set.o 4


## GRAPHS

# Produce graph
graph:
	/usr/bin/python3 ./benchmark_tests/graph_interpret/part1-graph.py


## CLEAN
# This command clean the project by deleting output file
clean:
	rm -f *.o
	rm -f ./part1/philosophers/*.o
	rm -f ./part1/producers_consumers/*.o
	rm -f ./part1/readers_writers/*.o
	rm -f ./part1/active_lock/*.o

.PHONY: clean philosophers_posix producers_consumers_posix readers_writers_posix test_and_set graph