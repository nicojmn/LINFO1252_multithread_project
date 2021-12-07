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
======================================
||                                  ||
|| test_and_set + test_and_test_set ||
||                                  ||
======================================
"""

ts_csv = pd.read_csv("time_results/csv/ts.csv")
tts_csv = pd.read_csv("time_results/csv/tts.csv")

# We get the maximum thread by looking at the last line of the CSV
# We don't use os.cpu_count() because the user can run benchmark test on an pc and make graph on another one
# So to have the same max thread we search in the CSV
thread_column_ts = list(ts_csv["nThread"])
max_thread = thread_column_ts[len(thread_column_ts) - 1]

threads_ts = np.unique([i for i in ts_csv["nThread"]])
values_ts = []
std_ts = []

for thread in threads_ts:
    sub_dataset_ts = ts_csv.loc[ts_csv.nThread == thread]
    values_ts.append(np.mean(sub_dataset_ts["time"]))
    std_ts.append(np.std(sub_dataset_ts["time"]))

thread_column_tts = list(tts_csv["nThread"])
max_thread = thread_column_tts[len(thread_column_tts) - 1]

threads_tts = np.unique([i for i in ts_csv["nThread"]])
values_tts = []
std_tts = []

for thread in threads_tts:
    sub_dataset_tts = tts_csv.loc[tts_csv.nThread == thread]
    values_tts.append(np.mean(sub_dataset_tts["time"]))
    std_tts.append(np.std(sub_dataset_tts["time"]))

plt.plot(threads_ts, values_ts, color="red", label="Valeur moyenne (test_and_set)")
plt.errorbar(threads_ts, values_ts, color="orange", label="Écart type (test_and_set)", yerr=std_ts, fmt='o', capsize=5)

plt.plot(threads_tts, values_tts, color="navy", label="Valeur moyenne (test_and_test_and_set)")
plt.errorbar(threads_tts, values_tts, color="cornflowerblue", label="Écart type (test_and_test_and_set)", yerr=std_tts,
             fmt='o', capsize=5)

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.xticks(np.linspace(0, max_thread, max_thread + 1))
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.title("Temps d'exécution pour les verrous actifs")
plt.grid(True)

plt.legend(loc='upper left')

create_dir_if_not_exist("time_results/graphs/images/ts_tts.png")
create_dir_if_not_exist("time_results/graphs/pdf/ts_tts.pdf")

plt.savefig("time_results/graphs/images/ts_tts.png")
plt.savefig("time_results/graphs/pdf/ts_tts.pdf")

plt.close()
