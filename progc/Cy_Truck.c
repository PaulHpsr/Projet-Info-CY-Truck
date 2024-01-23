#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Headers
#include "Traitements.h"



int main(int argc, char *argv[]) {
  printf("cacaprout\n");
  printf("%d", argc);
  int i =2;

  for(i; i<argv; i++)       //Parcourir pour effectuer chaques traitements
  {
  printf("%s\n", argv[i]);

  }

  if (argc < 2) {                             //Vérifier le C à bien récupéré les arguments donnés par le shell (<3 car -> nom prog + option + chemin csv)
    printf("Erreur, pas assez d'arguments, ou mauvais arguments\n");
    return 1;
  }

  // Récupérer les arguments dans des varr globales ?
  
  char *chemin_csv = argv[1]; 
  //On a arv[1+i] -> sera une option de traitement 

  
  // Traitement des options




//Fin du programme -> time
return 0;
}
