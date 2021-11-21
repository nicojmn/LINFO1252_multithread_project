#ifndef LINFO1252_PROJET_PHILOSOPHERS_H
#define LINFO1252_PROJET_PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void eat(int id);

void think(int id);

int main(int argc, char *argv[]);

#endif //LINFO1252_PROJET_PHILOSOPHERS_H
