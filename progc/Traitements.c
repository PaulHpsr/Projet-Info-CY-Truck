#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Traitements.h"


//Taille maximum d'une ligne à gérer
#define ligne_taille_max 5000 
char chemin_fichier[50] ="./data/";


//----------------------------- Traitement d1 ---------------------//

//Structure Infos
typedef struct _driverinfos {
char driverNom[100];
int nbTrajets;
} DriverInfos;



void traitement_d1(char *fichier) {
    char driverNom[100];
    char driverPrenom[100];

      DriverInfos drivers[200];
      int nbDrivers = 0;

      char ligne[ligne_taille_max];

    strcat(chemin_fichier,fichier);
    strcat(chemin_fichier, ".csv");

      FILE* file = fopen(chemin_fichier, "r");
      if (file == NULL)
      {
        perror("ERREUR : impossible d'ouvrir le fichier csv");
        exit(EXIT_FAILURE);
      }


      //Ignorer la première ligne -> présentation des colones
      fgets(ligne, ligne_taille_max, file);

    while(fgets(ligne, ligne_taille_max, file) != NULL)
      {
        //
        sscanf(ligne, "%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%s %s", driverNom, driverPrenom);
        //Obtenir Prenom + NOM
        strncat(driverNom, " ", 1);
        strcat(driverNom, driverPrenom);
        //Ajouter le premier driver sinon bug
        if(nbDrivers == 0)
        {
          nbDrivers++; 
          strcpy(drivers[0].driverNom, driverNom);
          drivers[0].nbTrajets = 1; 
        }

       //Rechercher si le conducteur existe 
        else
        {
          int driverExists = 0;
          for (int i = 0; i < nbDrivers; i++)
          {
              if (strcmp(drivers[i].driverNom, driverNom) == 0)
              {
                  drivers[i].nbTrajets++;
                  driverExists = 1;
                  break; // Break out of the loop since driver is found
              }
          }

          // Si le conducteur n'existe pas, l'ajouter
          if (driverExists !=1)
          {
              strcpy(drivers[nbDrivers].driverNom, driverNom);
              drivers[nbDrivers].nbTrajets = 1;
              nbDrivers++;
          }
      }
    }
  
      fclose(file);

      //Créer un fichier .txt temporaire pour stocker les infos traitées
      FILE* fichier_temp;
      fichier_temp = fopen("./temp/data_d1.txt", "w");
      if (fichier_temp == NULL)
      {
        perror("ERREUR : impossible d'ouvrir le fichier csv");
        exit(EXIT_FAILURE);
      }

      //On met les infos dans le fichier .txt temporaire
      for(int i=0; i<nbDrivers; i++)
        {
          fprintf(fichier_temp, "%s;%d\n", drivers[i].driverNom, drivers[i].nbTrajets);
        }
      fclose(fichier_temp); 


}

//-----------------------------------------------------------------//


//---------------------- Traitement d2 -----------------------------//


//Structure Infos
typedef struct _driverinfosD2 {
char driverNom[100];
float nbDistance;
} DriverInfosD2;


//On reprend globallement le traitement d1
void traitement_d2(char *fichier) 
{

  float nbDistance = 0;
  char driverNom[100];
  char driverPrenom[100];

  DriverInfosD2 drivers[200];
  int nbDrivers = 0;

  char ligne[ligne_taille_max];

  strcat(chemin_fichier,fichier);
  strcat(chemin_fichier, ".csv");

    FILE* file = fopen(chemin_fichier, "r");
    if (file == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv");
      exit(EXIT_FAILURE);
    }


    //Ignorer la première ligne -> présentation des colones
    fgets(ligne, ligne_taille_max, file);

  while(fgets(ligne, ligne_taille_max, file) != NULL)
    {
      //
      sscanf(ligne, "%*[^;];%*[^;];%*[^;];%*[^;];%f;%s %s", &nbDistance ,driverNom, driverPrenom);
      printf("Distance : %f\n", nbDistance);
      //Obtenir Prenom + NOM
      strncat(driverNom, " ", 1);
      strcat(driverNom, driverPrenom);
      //Ajouter le premier driver sinon bug
      if(nbDrivers == 0)
      {
        nbDrivers++; 
        strcpy(drivers[0].driverNom, driverNom);
        drivers[0].nbDistance = drivers[0].nbDistance + nbDistance; 
      }

     //Rechercher si le conducteur existe 
      else
      {
        int driverExists = 0;
        for (int i = 0; i < nbDrivers; i++)
        {
            if (strcmp(drivers[i].driverNom, driverNom) == 0)
            {
                drivers[i].nbDistance = drivers[i].nbDistance + nbDistance;
                driverExists = 1;
                break; // Break out of the loop since driver is found
            }
        }

        // Si le conducteur n'existe pas, l'ajouter
        if (driverExists !=1)
        {
            strcpy(drivers[nbDrivers].driverNom, driverNom);
            drivers[nbDrivers].nbDistance = nbDistance;
            nbDrivers++;
        }
    }
    nbDistance = 0;
  }

    fclose(file);


  for(int i=0; i<nbDrivers; i++)
    {
      printf("Tableau : %s;%f\n", drivers[i].driverNom, drivers[i].nbDistance);
    }
  
    //Créer un fichier .txt temporaire pour stocker les infos traitées
    FILE* fichier_temp;
    fichier_temp = fopen("./temp/data_d2.txt", "w");
    if (fichier_temp == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv");
      exit(EXIT_FAILURE);
    }

    //On met les infos dans le fichier .txt temporaire
    for(int i=0; i<nbDrivers; i++)
      {
        fprintf(fichier_temp, "%s;%f\n", drivers[i].driverNom, drivers[i].nbDistance);
      }
  
    fclose(fichier_temp); 

  
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
  fTemp = fopen("../temp/data_l.txt", "w");
  if (fTemp == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  //On met les infos dans le fichier .txt temporaire
  for(int i=0; i<nbTrajet; i++)
    {
      fprintf(fTemp, "%d;%f", trajet[i].routeID, trajet[i].totalDistance);
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
  fichier_temp = fopen("../temp/data_t.txt", "w");
    if (fichier_temp == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv");
      exit(EXIT_FAILURE);
    }

    //On met les infos dans le fichier .txt temporaire
    for(int y=0; y<10; y++)
      {
        fprintf(fichier_temp, "%s;%d;%d", tableau[y]->nomVille, tableau[y]->nbTrajets, tableau[y]->nbDepart);
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
  fichier_temp = fopen("../temp/data_s.txt", "w");
    if (fichier_temp == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv");
      exit(EXIT_FAILURE);
    }

    //On met les infos dans le fichier .txt temporaire
    for(int y=0; y<=i; y++)
      {
        fprintf(fichier_temp, "%d;%f;%f;%f", tableau[y]->id, tableau[y]->min, tableau[y]->max, tableau[y]->moy);
      }
    fclose(fichier_temp);

}

//----------------------------------------------------------------//