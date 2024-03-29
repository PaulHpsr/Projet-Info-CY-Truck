#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Headers
#include "Outils_AVL_T.h"
#include "Outils_AVL_S.h"



int main(int argc, char *argv[]) {
    // d1 d2  -> nom_prog + chemin + d1 + d2
  int i =2;
  
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
      printf("Traitement s en cours\n");
      traitement_s(chemin_csv);
    }
  }
//Fin du programme -> time
return 0;
}
