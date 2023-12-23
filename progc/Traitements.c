#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Traitements.h"

//Taille maximum d'une ligne à gérer
#define ligne_taille_max 5000 

//----------------------------- Traitement d1 ---------------------//
void traitement_d1(char *fichier, char* chemin_temp) {

  DriverInfos drivers[300000];
  int nbDrivers = 0;
  char ligne[1024];
  
  FILE* file = fopen(fichier, "r");
  if (file == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  //Ignorer la première ligne -> présentation des colones
  fgets(ligne, ligne_taille_max, file);

  
  while (fgets(ligne, ligne_taille_max, file) != NULL)
    {
      char driverNom[50];
      int nbTrajets = 0;
      
      sscanf(ligne, "%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%s", driverNom);
      //Recherche si le driver existe déjà
       int existingDriverIndex = -1;
      for (int i = 0; i < nbDrivers; i++) {
          if (strcmp(drivers[i].driverNom, driverNom) == 0) {
              existingDriverIndex = i;
              break;
          }
      }
      if (existingDriverIndex == -1) 
      {
          // Le conducteur n'existe pas encore, ajout au tableau
          strcpy(drivers[nbDrivers].driverNom, driverNom);
          drivers[nbDrivers].nbTrajets = 1;
          nbDrivers++;
      } 
      else 
      {
          // Le conducteur existe déjà, incrémente le nombre de trajets
          drivers[existingDriverIndex].nbTrajets++;
      }
    }

  // Tri du tableau en ordre décroissant du nombre de trajets
  qsort(drivers, nbDrivers, sizeof(DriverInfos), compareDrivers);
  fclose(file);
  //Créer un fichier .txt temporaire pour stocker les infos traitées
  FILE* fichier_temp;
  fichier_temp = fopen("chemin_temp/temp/data_d1.txt", "w");
  if (fichier_temp == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  //On met les infos dans le fichier .txt temporaire
  for(int i=0; i<nbDrivers; i++)
    {
      fprintf(fichier_temp, "%s %d", drivers[i].driverNom, drivers[i].nbTrajets);
    }
  fclose(fichier_temp);
}

//Afin de trier les conducteurs par ordre décroissant
int compareDrivers(DriverInfos *a, DriverInfos *b)
{
  return (b->nbTrajets - a->nbTrajets);
}
//-----------------------------------------------------------------//


void traitement_d2(char *fichier) {
    // Code spécifique pour le traitement -d2
    printf("Traitement pour -d2\n");
}

void traitement_l(char *fichier) {
    // Code spécifique pour le traitement -l
    printf("Traitement pour -l\n");
}

void traitement_t(char *fichier) {
    // Code spécifique pour le traitement -t
    printf("Traitement pour -t\n");
}

void traitement_s(char *fichier) {
    // Code spécifique pour le traitement -s
    printf("Traitement pour -s\n");
}