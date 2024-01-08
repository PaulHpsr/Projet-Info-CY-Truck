#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Traitements.h"
#include "Outils_AVL_T.h"

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


//---------------------- Traitement d2 -----------------------------//

//On reprend globallement le traitement d1
void traitement_d2(char *fichier, char* chemin_temp) 
{

  DriverInfosD2 drivers[300000];
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
      float nbDistance = 0;

      sscanf(ligne, "%*[^;];%*[^;];%*[^;];%*[^;];%f;%s", driverNom, nbDistance);
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
          drivers[nbDrivers].nbDistance += nbDistance;
        nbDrivers++;
      } 
    }

  // Tri du tableau en ordre décroissant du nombre de trajets
  qsort(drivers, nbDrivers, sizeof(DriverInfosD2), compareDriversD2);
  fclose(file);
  //Créer un fichier .txt temporaire pour stocker les infos traitées
  FILE* fichier_temp;
  fichier_temp = fopen("chemin_temp/temp/data_d2.txt", "w");
  if (fichier_temp == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  //On met les infos dans le fichier .txt temporaire
  for(int i=0; i<nbDrivers; i++)
    {
      fprintf(fichier_temp, "%s %d", drivers[i].driverNom, drivers[i].nbDistance);
    }
  fclose(fichier_temp);
  
}

int compareDriversD2(DriverInfosD2 *a, DriverInfosD2 *b)
{
  return (b->nbDistance - a->nbDistance);
}

//------------------------------------------------------------------//


//------------------------------ Traitement l ---------------------//
void traitement_l(char *fichier, char* chemin_temp) {


  FILE* file = fopen(fichier, "r");
  if (file == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  TrajetData trajet[300000];
  int nbTrajet = 0;
  char ligne[1024];


  //Ignorer la première ligne -> présentation des colones
  fgets(ligne, ligne_taille_max, file);


  while (fgets(ligne, ligne_taille_max, file) != NULL)
    {

      int* currentID;
      float currentDistance;
      
      sscanf(ligne, "%d;%*[^;];%*[^;];%*[^;];%f;%*[^;]", currentID, currentDistance);
      trajet[nbTrajet].routeID = currentID;
      trajet[nbTrajet].totalDistance = currentDistance;
      nbTrajet++;
    }

  // Tri du tableau en ordre décroissant du nombre de trajets
  qsort(trajet, nbTrajet, sizeof(TrajetData), compareTrajets);
  fclose(file);
  //Créer un fichier .txt temporaire pour stocker les infos traitées
  FILE* fichier_temp;
  fichier_temp = fopen("chemin_temp/temp/data_l.txt", "w");
  if (fichier_temp == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  //On met les infos dans le fichier .txt temporaire
  for(int i=0; i<nbTrajet; i++)
    {
      fprintf(fichier_temp, "%d %f", trajet[i].routeID, trajet[i].totalDistance);
    }
  fclose(fichier_temp);
  
}

//On reprend globallement le code du traitement d1
//Fonct° comparer les distances
int compareTrajets(TrajetData* a, TrajetData* b) 
{
  return (b->totalDistance - a->totalDistance);
}
//----------------------------------------------------------------//


//------------------------------ Traitement t ---------------------//
void traitement_t(char *fichier, char* chemin_temp) 
{
  FILE* file = fopen(fichier, "r");
  if (file == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }
  
  char ligne[1024];
  
  //Ignorer la première ligne -> présentation des colones
  fgets(ligne, ligne_taille_max, file);

  char TownA[50];
  char TownB[50];

  int *h = 0;
  Arbre *node = NULL;
  while (fgets(ligne, ligne_taille_max, file) != NULL)
    {
      sscanf(ligne, "%*[^;];%*[^;];%s;%s;%*[^;];%*[^;]", TownA, TownB);
      node = insertion(node, TownA, h, 0); 
      node = insertion(node, TownB, h, 1); 
    }

  fclose(file);
  //Avoir les 10 villes les + visités
  Ville* tableau[10];
  int i = 0;
  postfixeFilsDroit(node,tableau ,i);

  //On met les infos dans le fichier .txt temporaire
    FILE* fichier_temp;
    fichier_temp = fopen("chemin_temp/temp/data_t.txt", "w");
    if (fichier_temp == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv");
      exit(EXIT_FAILURE);
    }

    //On met les infos dans le fichier .txt temporaire
    for(int y=0; y<10; y++)
      {
        fprintf(fichier_temp, "%s %d %d", tableau[y]->nomVille, tableau[y]->nbTrajets, tableau[i]->nbDepart);
      }
    fclose(fichier_temp);

}


  
//----------------------------------------------------------------//



void traitement_s(char *fichier) 
{

}