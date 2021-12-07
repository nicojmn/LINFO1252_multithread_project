## MAIN VARIABLES
CC = gcc
# The flag -D_NOLOGS disable the logs generate by "log.h"
CFLAGS = -Wall -Werror -g -std=gnu99
# Used to colorize the output. Remove if we need to extracts logs
CFLAGS += -D_COLOR
LIBS = -lpthread
INCLUDE_HEADERS_DIRECTORY = -Iheaders

## SECONDS VARIABLES
T1 = 2
T2 = 2

## PATHS
# BUILD
POSIX = implem_c/posix
QUICKSPIN = implem_c/quickspin
MUTEX = implem_c/active_locks/mutex
SEM = implem_c/active_locks/semaphore
PHILO = philosophers
PC = producers_consumers
RW = readers_writers

# RUN
PHILO_POS = philo_posix
PC_POS = pc_posix
RW_POS = rw_posix
PHILO_QS = philo_quickspin
PC_QS = pc_quickspin
RW_QS = rw_quickspin
TS = ts
TTS = tts

# ZIP
DIR_NAME = groupe50_Jadin_Jeanmenne
ZIP_NAME = ./$(DIR_NAME).zip
FILES = benchmark_tests implem_c Makefile README.md


## TOOLS
# This command take a C source file and compile it to return a .o file
%.o: %.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<


## BUILDERS
build_$(PHILO_POS): $(POSIX)/$(PHILO)/src/philosophers.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $(POSIX)/$(PHILO)/$(PHILO_POS).o $^ $(LIBS)

build_$(PC_POS): $(POSIX)/$(PC)/src/prod_cons.c $(POSIX)/$(PC)/src/buffer_implem.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $(POSIX)/$(PC)/$(PC_POS).o $^ $(LIBS)

build_$(RW_POS): $(POSIX)/$(RW)/src/read_write.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $(POSIX)/$(RW)/$(RW_POS).o $^ $(LIBS)

build_$(PHILO_QS): $(QUICKSPIN)/$(PHILO)/src/philosophers.c $(SEM)/src/semaphore.c $(MUTEX)/$(TTS)/src/test_and_test_and_set.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $(QUICKSPIN)/$(PHILO)/$(PHILO_QS).o $^ $(LIBS)

build_$(PC_QS): $(QUICKSPIN)/$(PC)/src/prod_cons.c $(POSIX)/$(PC)/src/buffer_implem.c $(SEM)/src/semaphore.c $(MUTEX)/$(TTS)/src/test_and_test_and_set.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $(QUICKSPIN)/$(PC)/$(PC_QS).o $^ $(LIBS)

build_$(RW_QS): $(QUICKSPIN)/$(RW)/src/read_write.c $(SEM)/src/semaphore.c $(MUTEX)/$(TTS)/src/test_and_test_and_set.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $(QUICKSPIN)/$(RW)/$(RW_QS).o $^ $(LIBS)

build_$(TS): $(MUTEX)/$(TS)/src/test_and_set.c $(MUTEX)/$(TS)/src/test_mutex_ts.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $(MUTEX)/$(TS)/$(TS).o $^ $(LIBS)

build_$(TTS): $(MUTEX)/$(TTS)/src/test_and_test_and_set.c $(MUTEX)/$(TTS)/src/test_mutex_tts.c
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $(MUTEX)/$(TTS)/$(TTS).o $^ $(LIBS)

build_all_posix: build_$(PHILO_POS) build_$(PC_POS) build_$(RW_POS)
build_all_quickspin: build_$(PHILO_QS) build_$(PC_QS) build_$(RW_QS)
build_all_locks: build_$(TS) build_$(TTS)

build_all: build_all_posix build_all_quickspin build_all_locks
all: build_all


## RUNNERS
$(PHILO_POS):
	./$(POSIX)/$(PHILO)/$(PHILO_POS).o $(T1)
$(PC_POS):
	./$(POSIX)/$(PC)/$(PC_POS).o $(T1) $(T2)
$(RW_POS):
	./$(POSIX)/$(RW)/$(RW_POS).o $(T1) $(T2)

$(PHILO_QS):
	./$(QUICKSPIN)/$(PHILO)/$(PHILO_QS).o $(T1)
$(PC_QS):
	./$(QUICKSPIN)/$(PC)/$(PC_QS).o $(T1) $(T2)
$(RW_QS):
	./$(QUICKSPIN)/$(RW)/$(RW_QS).o $(T1) $(T2)

$(TS):
	./$(MUTEX)/$(TS)/$(TS).o $(T1)
$(TTS):
	./$(MUTEX)/$(TTS)/$(TTS).o $(T1)


## TESTS
# Test for memory leak
mem-check: CFLAGS += -D_NOLOGS
mem-check: clean all
	@printf "\n\n============================================\n||  Memory test for philosophers problem (POSIX)  ||\n============================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./$(POSIX)/$(PHILO)/$(PHILO_POS).o 20

	@printf "\n\n===================================================\n||  Memory test for producers-consumers problem (POSIX)  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./$(POSIX)/$(PC)/$(PC_POS).o 6 6

	@printf "\n\n===================================================\n||  Memory test for readers-writers problem (POSIX)  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./$(POSIX)/$(RW)/$(RW_POS).o 3 6

	@printf "\n\n============================================\n||  Memory test for philosophers problem (QUICKSPIN)  ||\n============================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./$(QUICKSPIN)/$(PHILO)/$(PHILO_QS).o 20

	@printf "\n\n===================================================\n||  Memory test for producers-consumers problem (QUICKSPIN)  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./$(QUICKSPIN)/$(PC)/$(PC_QS).o 6 6

	@printf "\n\n===================================================\n||  Memory test for readers-writers problem (QUICKSPIN)  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./$(QUICKSPIN)/$(RW)/$(RW_QS).o 3 6

	@printf "\n\n===================================================\n||  Memory test for test_and_set algorithm  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./$(MUTEX)/$(TS)/$(TS).o 4

	@printf "\n\n===================================================\n||  Memory test for test_and_test_and_set algorithm  ||\n===================================================\n\n"
	valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./$(MUTEX)/$(TTS)/$(TTS).o 4

# Performs helgrind (safe threads check) test
threads-check: CFLAGS += -D_NOLOGS
threads-check: clean all
	@printf "\n\n============================================\n||  Thread test for philosophers problem (POSIX)  ||\n============================================\n\n"
	valgrind --tool=helgrind -s ./$(POSIX)/$(PHILO)/$(PHILO_POS).o 10

	@printf "\n\n===================================================\n||  Thread test for producers-consumers problem (POSIX)  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./$(POSIX)/$(PC)/$(PC_POS).o 2 3

	@printf "\n\n===================================================\n||  Thread test for readers-writers problem (POSIX)  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./$(POSIX)/$(RW)/$(RW_POS).o 2 3

	@printf "\n\n============================================\n||  Thread test for philosophers problem (QUICKSPIN)  ||\n============================================\n\n"
	valgrind --tool=helgrind -s ./$(QUICKSPIN)/$(PHILO)/$(PHILO_QS).o 10

	@printf "\n\n===================================================\n||  Thread test for producers-consumers problem (QUICKSPIN)  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./$(QUICKSPIN)/$(PC)/$(PC_QS).o 2 3

	@printf "\n\n===================================================\n||  Thread test for readers-writers problem (QUICKSPIN)  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./$(QUICKSPIN)/$(RW)/$(RW_QS).o 2 3

	@printf "\n\n===================================================\n||  Thread test for test_and_set algorithm  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./$(MUTEX)/$(TS)/$(TS).o 4

	@printf "\n\n===================================================\n||  Thread test for test_and_test_and_set algorithm  ||\n===================================================\n\n"
	valgrind --tool=helgrind -s ./$(MUTEX)/$(TTS)/$(TTS).o 4


## RUN PERF EVAL
perf_posix:
	/usr/bin/bash ./benchmark_tests/perf_evals/philosophers_pe_posix.sh ./time_results/csv/philosophers_posix.csv
	/usr/bin/bash ./benchmark_tests/perf_evals/producers_consumers_pe_posix.sh ./time_results/csv/producers-consumers_posix.csv
	/usr/bin/bash ./benchmark_tests/perf_evals/readers_writers_pe_posix.sh ./time_results/csv/readers-writers_posix.csv

perf_quickspin:
	/usr/bin/bash ./benchmark_tests/perf_evals/philosophers_pe_quickspin.sh ./time_results/csv/philosophers_quickspin.csv
	/usr/bin/bash ./benchmark_tests/perf_evals/producers_consumers_pe_quickspin.sh ./time_results/csv/producers_consumers_quickspin.csv
	/usr/bin/bash ./benchmark_tests/perf_evals/readers_writers_pe_quickspin.sh ./time_results/csv/readers_writers_quickspin.csv

perf_all: perf_posix perf_quickspin

## GRAPHS
# Produce graph
graph:
	/usr/bin/python3 ./benchmark_tests/graph_interpret/part1-graph.py
	/usr/bin/python3 ./benchmark_tests/graph_interpret/part2-graph.py


## CLEAN
# This command clean the project by deleting output file
clean:
	@cd implem_c
	@rm -f `find . -type f -name '*.o'`
	@printf "All '*.o' files cleaned in the 'implem_c' directory\n"

## ZIP
zip: clean
	@mkdir ${DIR_NAME}
	@$(foreach file,${FILES},cp -r ${file} ${DIR_NAME}/${file};)
	@git log --stat > ${DIR_NAME}/gitlog.stat
	zip -r ${ZIP_NAME} ${DIR_NAME}
	@rm -r -d ${DIR_NAME}

.PHONY: clean all zip