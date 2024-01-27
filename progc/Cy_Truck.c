#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Headers
#include "Traitements.h"
#include "Outils_AVL_T.h"
#include "Outils_AVL_S.h"



int main(int argc, char *argv[]) {
    // d1 d2  -> nom_prog + chemin + d1 + d2
  int i =2;
  int y=2;
  for(y; y<argc;y++)
    {
  printf("%s\n", argv[y]);    
    }

  
  // Récupérer les arguments dans des varr globales ?
  char *chemin_csv = argv[1]; 
  //On a arv[1+i] -> sera une option de traitement 
  // Traitement des options
  for(i; i<argc; i++)       //Parcourir pour effectuer chaques traitements
  {
    if(strcmp(argv[i], "-d1") == 0)
    {
      printf("Traitement d1 en cours\n");
      traitement_d1(chemin_csv);
    }

    if(strcmp(argv[i], "-d2") == 0)
    {
      printf("Traitement d2 en cours\n");
      traitement_d2(chemin_csv);
    }

    if(strcmp(argv[i], "-l") == 0)
    {
      traitement_l(chemin_csv);
    }

    if(strcmp(argv[i], "-t") == 0)
    {
      traitement_t(chemin_csv);
    }

    if(strcmp(argv[i], "-s") == 0)
    {
      traitement_s(chemin_csv);
    }
  }
//Fin du programme -> time
return 0;
}
