#!/usr/bin/env python3

import os

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def create_dir_if_not_exist(filepath):
    directory = os.path.dirname(filepath)
    if not os.path.exists(directory):
        os.makedirs(directory)


"""
==========================
||                      ||
|| Philosophers problem ||
||                      ||
==========================
"""
philosophers_csv_posix = pd.read_csv("time_results/csv/philosophers_posix.csv")
philosophers_csv_quickspin = pd.read_csv("time_results/csv/philosophers_quickspin.csv")

# We get the maximum thread by looking at the last line of the CSV
# We don't use os.cpu_count() because the user can run benchmark test on an pc and make graph on another one
# So to have the same max thread we search in the CSV
thread_column_posix = list(philosophers_csv_posix["nThread"])
max_thread = thread_column_posix[len(thread_column_posix) - 1]

threads_posix = np.unique([i for i in philosophers_csv_posix["nThread"]])
values_posix = []
std_posix = []

for thread in threads_posix:
    sub_dataset_posix = philosophers_csv_posix.loc[philosophers_csv_posix.nThread == thread]
    values_posix.append(np.mean(sub_dataset_posix["time"]))
    std_posix.append(np.std(sub_dataset_posix["time"]))

thread_column_quickspin = list(philosophers_csv_quickspin["nThread"])
max_thread = thread_column_quickspin[len(thread_column_quickspin) - 1]

threads_quickspin = np.unique([i for i in philosophers_csv_quickspin["nThread"]])
values_quickspin = []
std_quickspin = []

for thread in threads_quickspin:
    sub_dataset_quickspin = philosophers_csv_quickspin.loc[philosophers_csv_quickspin.nThread == thread]
    values_quickspin.append(np.mean(sub_dataset_quickspin["time"]))
    std_quickspin.append(np.std(sub_dataset_quickspin["time"]))

plt.plot(threads_posix, values_posix, color="red", label="Valeur moyenne (posix)")
plt.errorbar(threads_posix, values_posix, color="orange", label="Écart type (posix)", yerr=std_posix, fmt='o',
             capsize=5)

plt.plot(threads_quickspin, values_quickspin, color="navy", label="Valeur moyenne (quickspin)")
plt.errorbar(threads_quickspin, values_quickspin, color="cornflowerblue", label="Écart type (quickspin)",
             yerr=std_quickspin, fmt='o', capsize=5)

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.xticks(np.linspace(0, max_thread, max_thread + 1))
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.title("Temps d'exécution des threads pour le problème des philosophes")
plt.grid(True)

plt.legend(loc='lower right')

create_dir_if_not_exist("time_results/graphs/images/philosophers_quickspin.png")
create_dir_if_not_exist("time_results/graphs/pdf/philosophers_quickspin.pdf")

plt.savefig("time_results/graphs/images/philosophers_quickspin.png")
plt.savefig("time_results/graphs/pdf/philosophers_quickspin.pdf")

plt.close()

"""
=================================
||                             ||
|| Producers-consumers problem ||
||                             ||
=================================
"""

producers_consumers_csv_posix = pd.read_csv("time_results/csv/producers-consumers_posix.csv")
producers_consumers_csv_quickspin = pd.read_csv("time_results/csv/producers_consumers_quickspin.csv")

# We get the maximum thread by looking at the last line of the CSV
# We don't use os.cpu_count() because the user can run benchmark test on an pc and make graph on another one
# So to have the same max thread we search in the CSV
thread_column_posix = list(producers_consumers_csv_posix["nThread"])
max_thread = thread_column_posix[len(thread_column_posix) - 1]

threads_posix = [i for i in producers_consumers_csv_posix["nThread"]]
values_posix = []
std_posix = []

for thread in threads_posix:
    sub_dataset_posix = producers_consumers_csv_posix.loc[producers_consumers_csv_posix.nThread == thread]
    values_posix.append(np.mean(sub_dataset_posix["time"]))
    std_posix.append(np.std(sub_dataset_posix["time"]))

thread_column_posix = list(producers_consumers_csv_posix["nThread"])
max_thread = thread_column_posix[len(thread_column_posix) - 1]

threads_quickspin = [i for i in producers_consumers_csv_quickspin["nThread"]]
values_quickspin = []
std_quickspin = []

for thread in threads_quickspin:
    sub_dataset_quickspin = producers_consumers_csv_quickspin.loc[producers_consumers_csv_quickspin.nThread == thread]
    values_quickspin.append(np.mean(sub_dataset_quickspin["time"]))
    std_quickspin.append(np.std(sub_dataset_quickspin["time"]))

plt.plot(threads_posix, values_posix, color="red", label="Valeur moyenne (posix)")
plt.errorbar(threads_posix, values_posix, color="orange", label="Écart type (posix)", yerr=std_posix, fmt='o',
             capsize=5)

plt.plot(threads_quickspin, values_quickspin, color="navy", label="Valeur moyenne (quickspin)")
plt.errorbar(threads_quickspin, values_quickspin, color="cornflowerblue", label="Écart type (quickspin)",
             yerr=std_quickspin, fmt='o', capsize=5)

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.xticks(np.linspace(0, max_thread, max_thread + 1))
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.title("Temps d'exécution des threads pour\nle problème des producteurs consommateurs")
plt.grid(True)

plt.legend(loc='lower right')

create_dir_if_not_exist("time_results/graphs/images/producers-consumers_quickspin.png")
create_dir_if_not_exist("time_results/graphs/pdf/producers-consumers_quickspin.pdf")

plt.savefig("time_results/graphs/images/producers-consumers_quickspin.png")
plt.savefig("time_results/graphs/pdf/producers-consumers_quickspin.pdf")

plt.close()

"""
===========================
||                       ||
|| Reader-writer problem ||
||                       ||
===========================
"""

readers_writers_csv_posix = pd.read_csv("time_results/csv/readers-writers_posix.csv")
readers_writers_csv_quickspin = pd.read_csv("time_results/csv/readers_writers_quickspin.csv")

# We get the maximum thread by looking at the last line of the CSV
# We don't use os.cpu_count() because the user can run benchmark test on an pc and make graph on another one
# So to have the same max thread we search in the CSV
thread_column_posix = list(readers_writers_csv_posix["nThread"])
max_thread = thread_column_posix[len(thread_column_posix) - 1]

threads_posix = [i for i in readers_writers_csv_posix["nThread"]]
values_posix = []
std_posix = []

for thread in threads_posix:
    sub_dataset_posix = readers_writers_csv_posix.loc[readers_writers_csv_posix.nThread == thread]
    values_posix.append(np.mean(sub_dataset_posix["time"]))
    std_posix.append(np.std(sub_dataset_posix["time"]))

thread_column_quickspin = list(readers_writers_csv_quickspin["nThread"])
max_thread = thread_column_quickspin[len(thread_column_quickspin) - 1]

threads_quickspin = [i for i in readers_writers_csv_quickspin["nThread"]]
values_quickspin = []
std_quickspin = []

for thread in threads_quickspin:
    sub_dataset_quickspin = readers_writers_csv_quickspin.loc[readers_writers_csv_quickspin.nThread == thread]
    values_quickspin.append(np.mean(sub_dataset_quickspin["time"]))
    std_quickspin.append(np.std(sub_dataset_quickspin["time"]))

plt.plot(threads_posix, values_posix, color="red", label="Valeur moyenne (posix)")
plt.errorbar(threads_posix, values_posix, color="orange", label="Écart type (posix)", yerr=std_posix, fmt='o',
             capsize=5)

plt.plot(threads_quickspin, values_quickspin, color="navy", label="Valeur moyenne (quickspin)")
plt.errorbar(threads_quickspin, values_quickspin, color="cornflowerblue", label="Écart type (quickspin)",
             yerr=std_quickspin, fmt='o', capsize=5)

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.xticks(np.linspace(0, max_thread, max_thread + 1))
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.title("Temps d'exécution des threads pour\nle problème des lecteurs écrivans")
plt.grid(True)

plt.legend(loc='upper right')

create_dir_if_not_exist("time_results/graphs/images/readers-writers_quickspin.png")
create_dir_if_not_exist("time_results/graphs/pdf/readers-writers_quickspin.pdf")

plt.savefig("time_results/graphs/images/readers-writers_quickspin.png")
plt.savefig("time_results/graphs/pdf/readers-writers_quickspin.pdf")

plt.close()
