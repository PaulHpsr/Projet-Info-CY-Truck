#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Headers
#include "Traitements.h"



int main(int argc, char *argv[]) {
  if (argc < 3) {                             //Vérifier le C à bien récupéré les arguments donnés par le shell (<3 car -> nom prog + option + chemin csv)
    fprintf(stderr, "Erreur, pas assez d'arguments, ou mauvais arguments\n");
    return 1;
  }

  // Récupérer les arguments dans des varr globales ?
  char *chemin_csv = argv[1]; 
  char *option_traitement = argv[2];
  char *chemin_temp = argv[3];
  
  //Diviser les options en plusieurs tokens
  char *token = strtok(option_traitement, " "); //Ainsi on récupère les options séparées par des espaces
  
  // Traitement des options
  while(token != NULL)         //Parcourir token pour effectuer chaques traitements
    {
      if(strcmp(token, "-d1") == 0)
      {
        traitement_d1(chemin_csv, chemin_temp);
      }
      if(strcmp(token, "-d2") == 0)
      {
        traitement_d2(chemin_csv, chemin_temp);
      }
      if(strcmp(token, "-l") == 0)
      {
        traitement_l(chemin_csv, chemin_temp);
      }
      if(strcmp(token, "-t") == 0)
      {
        traitement_t(chemin_csv, chemin_temp);
      }
      if(strcmp(token, "-s") == 0)
      {
        traitement_s(chemin_csv, chemin_temp);
      }

      token = strtok(NULL, " ");  //On passe au token suivant
    }



//Fin du programme -> time
return 0;
}
