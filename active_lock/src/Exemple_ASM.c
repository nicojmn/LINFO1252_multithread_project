#include<stdlib.h>
#include<stdio.h>
/*
Author : Charles-Henry Bertrand Van Ouytsel
Date : 17/11/2021

Voici un exemple simple d'utilisation de l'assembleur inline.
On veut incrementer une variable 'counter', d'une certaine valeur 'increment' en assembleur.
L'assembleur utilise ici pourrait evidemment etre simplifie en moins d'instructions.

N'hesitez pas a modifier le code pour essayer d'autres instructions, ne plus utiliser le registre eax,...
Dans le cadre du projet, il sera important d'effectuer des actions atomiques : a vous de trouver l'instruction adaptee !

Pour plus d'informations, sur l'inline et beaucoup d'autres exemples :
https://dmalcolm.fedorapeople.org/gcc/2015-08-31/rst-experiment/how-to-use-inline-assembly-language-in-c-code.html
*/


int main(int argc, char* argv[])
{
    int counter = 40; 
    int increment = 2;

    printf("Valeur de counter avant ASM : %d\n",counter);
    
    asm ("mov %0, %%eax\n"      // Mov la valeur 'counter' dans eax
         "add %1, %%eax\n"      // add la valeur 'increment' a eax
         "mov %%eax, %0"        // Mov le resultat de l'addition dans 'counter'
    : "=m" (counter)            // output operands : liste des variables C modifiees par l'ASM
    : "m" (increment)           // input operands : liste des variables C lues par l'ASM
    : "eax");                   // registres utilise, attention de bien mettre à jour si vous utilisez d'autres registres !

    printf("Valeur de counter apres ASM : %d\n",counter);
}
