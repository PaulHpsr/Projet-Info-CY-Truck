#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Traitements.h"
#include "Outils_AVL_T.h"
#include "Outils_AVL_S.h"

//Taille maximum d'une ligne à gérer
#define ligne_taille_max 5000 

//----------------------------- Traitement d1 ---------------------//
void traitement_d1(char *fichier) {

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
  fichier_temp = fopen("../temp/monFichierTemp.txt", "w");
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
float compareDrivers(DriverInfos *a, DriverInfos *b)
{
  return ((float)((DriverInfos*)b)->nbTrajets - ((DriverInfos*)a)->nbTrajets);
}
//-----------------------------------------------------------------//


//---------------------- Traitement d2 -----------------------------//

//On reprend globallement le traitement d1
void traitement_d2(char *fichier) 
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
  fichier_temp = fopen("../temp/monFichierTemp.txt", "w");
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

float compareDriversD2(DriverInfosD2 *a, DriverInfosD2 *b)
{
  return ((float)((DriverInfosD2*)b)->nbDistance - ((DriverInfosD2*)a)->nbDistance);
}

//------------------------------------------------------------------//


//------------------------------ Traitement l ---------------------//
void traitement_l(char *fichier) {


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
  FILE* fTemp;
  fTemp = fopen("../temp/monFichierTemp.txt", "w");
  if (fTemp == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  //On met les infos dans le fichier .txt temporaire
  for(int i=0; i<nbTrajet; i++)
    {
      fprintf(fTemp, "%d %f", trajet[i].routeID, trajet[i].totalDistance);
    }
  fclose(fTemp);
  
}

//On reprend globallement le code du traitement d1
//Fonct° comparer les distances
float compareTrajets(TrajetData* a, TrajetData* b) 
{
  ((float)((TrajetData*)b)->totalDistance - ((TrajetData*)a)->totalDistance);
}
//----------------------------------------------------------------//


//------------------------------ Traitement t ---------------------//
void traitement_t(char *fichier) 
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
      node = equilibrageAVL(node);
      node = insertion(node, TownB, h, 1); 
      node = equilibrageAVL(node);
    }

  fclose(file);
  //Avoir les 10 villes les + visités
  Ville* tableau[10];
  int i = 0;
  postfixeFilsDroit(node,tableau ,i);

  freeTree(node);

  //On met les infos dans le fichier .txt temporaire
  FILE* fichier_temp;
  fichier_temp = fopen("../temp/monFichierTemp.txt", "w");
    if (fichier_temp == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv");
      exit(EXIT_FAILURE);
    }

    //On met les infos dans le fichier .txt temporaire
    for(int y=0; y<10; y++)
      {
        fprintf(fichier_temp, "%s %d %d", tableau[y]->nomVille, tableau[y]->nbTrajets, tableau[y]->nbDepart);
      }
    fclose(fichier_temp);

}


  
//----------------------------------------------------------------//


//------------------------------ Traitement S ---------------------//


//
void traitement_s(char *fichier) 
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

  Trajet trajetCurrent;

  int *h = 0;
  Arbre *node = NULL;
  while (fgets(ligne, ligne_taille_max, file) != NULL)
    {
      sscanf(ligne, "%d;%*[^;];%*[^;];%*[^;];%f;%*[^;]", trajetCurrent.id, trajetCurrent.distance);
      node = insertionS(node, trajetCurrent, h); 
//Mettre équilibrage AVL
node = equilibrageAVLS(node);
    }

  fclose(file);
  //Avoir les 10 villes les + visités
  TrajetFinal* tableau[300];
  int i = 0;
  postfixeFilsDroitS(node,tableau ,i);

  freeTreeS(node);

  //On met les infos dans le fichier .txt temporaire
  FILE* fichier_temp;
  fichier_temp = fopen("../temp/monFichierTemp.txt", "w");
    if (fichier_temp == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv");
      exit(EXIT_FAILURE);
    }

    //On met les infos dans le fichier .txt temporaire
    for(int y=0; y<=i; y++)
      {
        fprintf(fichier_temp, "%d %f %f %f", tableau[y]->id, tableau[y]->min, tableau[y]->max, tableau[y]->moy);
      }
    fclose(fichier_temp);

}

//----------------------------------------------------------------//