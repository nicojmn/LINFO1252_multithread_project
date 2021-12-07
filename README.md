# [LINFO1252] Systèmes Informatiques - Projet Multithread & Spinlock
---

## **Membres:**

* Guillaume Jadin
* Nicolas Jeanmenne


L'utilisation de ce programme s'effectue en plusieurs phases:

## Compilation du projet:

Ce projet se compile grâce à un **Makefile**. Il supporte les commandes suivantes:

- `make build_philo_posix` => Compile le problème des philosophes grâce aux primitives de synchronisation POSIX

- `make build_pc_posix` => Compile le problème des producteurs-consomateurs grâce aux primitives de synchronisation POSIX

- `make build_rw_posix` => Compile le problème des lecteurs et écrivains grâce aux primitives de synchronisation POSIX



- `make build_philo_quickspin` => Compile le problème des philosophes grâce aux primitives de synchronisation d'attente active (QUICKSPIN)

- `make build_pc_quickspin` => Compile le problème des producteurs-consomateurs grâce aux primitives de synchronisation d'attente active (QUICKSPIN)

- `make build_rw_quickspin` => Compile le problème des lecteurs et écrivains grâce aux primitives de synchronisation d'attente active (QUICKSPIN)



- `make build_ts` => Compile le verrou par attente active grâce à l'algorithme test_and_set

- `make build_tts` => Compile le verrou par attente active grâce à l'algorithme test_and_test_and_set



- `make build_all_posix` => Compile tout les programmes POSIX

- `make build_all_quickspin` => Compile tout les programmes QUICKSPIN

- `make build_all_locks` => Compile tout les verrous par attente active



- `make all`/`make build_all` => Compile l'entièreté des différentes algorithmes.
    
    
## Commandes permettant d'exécuter les programmes supportées par le Makefile (par défaut: T1=2 et T2=2):

- `make philo_posix T1=N` => Exécute le problème des philosophes (POSIX) [où N = #threads]

- `make pc_posix T1=N T2=M` => Exécute le problème des producteurs-consomateurs (POSIX) [où N = #threads_producteurs & M = #threads_consommateurs]

- `make rw_posix T1=N T2=M` => Exécute le problème des lecteurs et écrivains (POSIX) [où N = #threads_écrivains & M = #threads_lecteurs]



- `make philo_quickspin T1=N` => Exécute le problème des philosophes (QUICKSPIN) [où N = #threads]

- `make pc_quickspin T1=N T2=M` => Exécute le problème des producteurs-consomateurs (QUICKSPIN) [où N = #threads_producteurs & M = #threads_consommateurs]

- `make rw_quickspin T1=N T2=M` => Exécute le problème des lecteurs et écrivains (QUICKSPIN)



- `make ts T1=N` => Exécute le verrou par attente active grâce à l'algorithme test_and_set [où N = #threads]

- `make build_tts T1=N` => Exécute le verrou par attente active grâce à l'algorithme test_and_test_and_set [où N = #threads]


## Commandes permettant d'exécuter les tests des programmes supportées par le Makefile:

- `make mem-check` => Vérifie les fuites de mémoire des différents programmes

- `make threads-check` => Vérifie l'existence de raised-conditions et de deadlocks des différents programmes


## Commandes permettant d'exécuter les tests de performances des programmes supportées par le Makefile:

- `make perf_posix` => Génère des fichiers _*.csv_ des performances des programmes utilisant POSIX

- `make graph` => Génère les graphes des programmes POSIX et QUICKSPIN


## Autres commandes supportées par le Makefile:

    - `make clean` => Supprime les fichiers "_*.o_" qui ont été créés lors de la compilation,
    
    - `make zip` => Crée un fichier .zip avec les logs des différents commits.


