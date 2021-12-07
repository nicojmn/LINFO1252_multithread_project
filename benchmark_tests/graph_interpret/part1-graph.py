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

philosophers_csv = pd.read_csv("time_results/csv/philosophers_posix.csv")

# We get the maximum thread by looking at the last line of the CSV
# We don't use os.cpu_count() because the user can run benchmark test on an pc and make graph on another one
# So to have the same max thread we search in the CSV
thread_column = list(philosophers_csv["nThread"])
max_thread = thread_column[len(thread_column) - 1]

threads = np.unique([i for i in philosophers_csv["nThread"]])
values = []
std = []

for thread in threads:
    sub_dataset = philosophers_csv.loc[philosophers_csv.nThread == thread]
    values.append(np.mean(sub_dataset["time"]))
    std.append(np.std(sub_dataset["time"]))

plt.plot(threads, values, color="red", label="Valeur moyenne")
plt.errorbar(threads, values, color="orange", label="Écart type", yerr=std, fmt='o', capsize=5)

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.xticks(np.linspace(0, max_thread, max_thread + 1))
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.title("Temps d'exécution des threads pour le problème des philosophes")
plt.grid(True)

plt.legend(loc='lower right')

create_dir_if_not_exist("time_results/graphs/images/philosophers_posix.png")
create_dir_if_not_exist("time_results/graphs/pdf/philosophers_posix.pdf")

plt.savefig("time_results/graphs/images/philosophers_posix.png")
plt.savefig("time_results/graphs/pdf/philosophers_posix.pdf")

plt.close()

"""
=================================
||                             ||
|| Producers-consumers problem ||
||                             ||
=================================
"""

producers_consumers_csv = pd.read_csv("time_results/csv/producers-consumers_posix.csv")

# We get the maximum thread by looking at the last line of the CSV
# We don't use os.cpu_count() because the user can run benchmark test on an pc and make graph on another one
# So to have the same max thread we search in the CSV
thread_column = list(producers_consumers_csv["nThread"])
max_thread = thread_column[len(thread_column) - 1]

threads = [i for i in producers_consumers_csv["nThread"]]
values = []
std = []

for thread in threads:
    sub_dataset = producers_consumers_csv.loc[producers_consumers_csv.nThread == thread]
    values.append(np.mean(sub_dataset["time"]))
    std.append(np.std(sub_dataset["time"]))

plt.plot(threads, values, color="red", label="Valeur moyenne")
plt.errorbar(threads, values, color="orange", label="Écart type", yerr=std, fmt='o', capsize=5)

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.xticks(np.linspace(0, max_thread, max_thread + 1))
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.title("Temps d'exécution des threads pour\nle problème des producteurs consommateurs")
plt.grid(True)

plt.legend(loc='lower right')

create_dir_if_not_exist("time_results/graphs/images/producers-consumers_posix.png")
create_dir_if_not_exist("time_results/graphs/pdf/producers-consumers_posix.pdf")

plt.savefig("time_results/graphs/images/producers-consumers_posix.png")
plt.savefig("time_results/graphs/pdf/producers-consumers_posix.pdf")

plt.close()

"""
===========================
||                       ||
|| Reader-writer problem ||
||                       ||
===========================
"""

readers_writers_csv = pd.read_csv("time_results/csv/readers-writers_posix.csv")

# We get the maximum thread by looking at the last line of the CSV
# We don't use os.cpu_count() because the user can run benchmark test on an pc and make graph on another one
# So to have the same max thread we search in the CSV
thread_column = list(philosophers_csv["nThread"])
max_thread = thread_column[len(thread_column) - 1]

threads = [i for i in readers_writers_csv["nThread"]]
values = []
std = []

for thread in threads:
    sub_dataset = readers_writers_csv.loc[readers_writers_csv.nThread == thread]
    values.append(np.mean(sub_dataset["time"]))
    std.append(np.std(sub_dataset["time"]))

plt.plot(threads, values, color="red", label="Valeur moyenne")
plt.errorbar(threads, values, color="orange", label="Écart type", yerr=std, fmt='o', capsize=5)

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.xticks(np.linspace(0, max_thread, max_thread + 1))
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.title("Temps d'exécution des threads pour\nle problème des lecteurs écrivans")
plt.grid(True)

plt.legend(loc='upper right')

create_dir_if_not_exist("time_results/graphs/images/readers-writers_posix.png")
create_dir_if_not_exist("time_results/graphs/pdf/readers-writers_posix.pdf")

plt.savefig("time_results/graphs/images/readers-writers_posix.png")
plt.savefig("time_results/graphs/pdf/readers-writers_posix.pdf")

plt.close()
