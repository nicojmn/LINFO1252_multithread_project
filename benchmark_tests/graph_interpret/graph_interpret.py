#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
import csv

graph = plt.figure()

# Use boxplot avec écart type
# time => y
# nthread => x
#TODO
with open("test.csv", mode='r') as file:
    for line in csv.reader(file, delimiter=","):
        print(line)

plt.xlabel("")
plt.ylabel("")
plt.title("")
plt.show()
