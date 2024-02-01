#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Headers
#include "Outils_AVL_T.h"
#include "Outils_AVL_S.h"



int main(int argc, char *argv[]) {
    // d1 d2  -> nom_prog + chemin + d1 + d2
  int i =2;

  printf("NOMBRE ARG : %d\n", argc);
for (int y=0; y<argc; y++)
  {
    printf("ARG %d = %s\n", y, argv[y]);
  }
  
  // Récupérer les arguments dans des varr globales ?
  char *chemin_csv = argv[1]; 
  //On a arv[1+i] -> sera une option de traitement 
  // Traitement des options
  for(i; i<argc; i++)       //Parcourir pour effectuer chaques traitements
  {
    if(strcmp(argv[i], "-t") == 0)
    {
      printf("Traitement t en cours\n");
      traitement_t(chemin_csv);
    }

    if(strcmp(argv[i], "-s") == 0)
    {
      traitement_s(chemin_csv);
    }
  }
  printf("Seg Fault fin prog\n");
//Fin du programme -> time
return 0;
}
