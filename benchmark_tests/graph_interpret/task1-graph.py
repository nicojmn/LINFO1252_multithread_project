import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

"""
==========================
||                      ||
|| Philosophers problem ||
||                      ||
==========================
"""

philosophers_csv = pd.read_csv("time_results/csv/philosophers.csv")

threads = np.unique([i for i in philosophers_csv["nThread"]])
values = []

for thread in threads:
    sub_dataset = philosophers_csv.loc[philosophers_csv.nThread == thread]
    values.append(np.mean(sub_dataset["time"]))

plt.plot(threads, values, color="blue", label="Valeur moyenne")

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.ylim(bottom=0)

plt.title("Temps d'exécution des threads pour le problème des philosophes")
plt.grid(True)

plt.legend(loc='upper right')

plt.savefig("benchmark_tests/philosophers.png")
plt.savefig("benchmark_tests/philosophers.pdf")

plt.close()

"""
=================================
||                             ||
|| Producers-consumers problem ||
||                             ||
=================================
"""

producers_consumers_csv = pd.read_csv("time_results/csv/producers-consumers.csv")

threads = [i for i in producers_consumers_csv["nThread"]]
values = []

for thread in threads:
    sub_dataset = producers_consumers_csv.loc[producers_consumers_csv.nThread == thread]
    values.append(np.mean(sub_dataset["time"]))

plt.plot(threads, values, color="blue", label="Valeur moyenne")

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.ylim(bottom=0)

plt.title("Temps d'exécution des threads pour le problème des producteurs consommateurs")
plt.grid(True)

plt.legend(loc='upper right')

plt.savefig("benchmark_tests/producers-consumers.png")
plt.savefig("benchmark_tests/producers-consumers.pdf")

plt.close()

"""
===========================
||                       ||
|| Reader-writer problem ||
||                       ||
===========================
"""
# Todo : reader-writer
