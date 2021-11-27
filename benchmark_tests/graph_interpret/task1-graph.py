import matplotlib.pyplot as plt
import pandas

# Philosopher problem

# Todo : philosopher

# Producers-consumers problem

csv = pandas.read_csv("time_results/csv/producers-consumers.csv")

threads = [i for i in csv["nthread"]]
values = [i for i in csv[" time"]]

plt.plot(threads, values, color="blue", label="Time execution")

plt.xlabel("Nombre de threads")
plt.ylabel("Temps d'exécution (en secondes)")

plt.title("Temps d'exécution des threads pour le problème des producteurs consommateurs")
plt.grid(True)

plt.legend(loc='upper right')

plt.savefig("./benchmark_tests/philosophers.png")
plt.savefig("./benchmark_tests/philosophers.pdf")

plt.close()

# Todo : reader-writer
