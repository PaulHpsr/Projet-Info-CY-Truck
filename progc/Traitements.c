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

  if(strcmp(chemin_fichier, "./data/") == 0)
  {
    strcat(chemin_fichier,fichier);
    strcat(chemin_fichier, ".csv");
  }

      FILE* file = fopen(chemin_fichier, "r");
      if (file == NULL)
      {
        perror("ERREUR : impossible d'ouvrir le fichier csv original");
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
        perror("ERREUR : impossible d'ouvrir le fichier csv data d1");
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


  if(strcmp(chemin_fichier, "./data/") == 0)
  {
    strcat(chemin_fichier,fichier);
    strcat(chemin_fichier, ".csv");
  }

  printf("Chemin d2 : %s\n", chemin_fichier);
    FILE* file = fopen(chemin_fichier, "r");
    if (file == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv original (-d2)");
      exit(EXIT_FAILURE);
    }


    //Ignorer la première ligne -> présentation des colones
    fgets(ligne, ligne_taille_max, file);

  while(fgets(ligne, ligne_taille_max, file) != NULL)
    {
      //
      sscanf(ligne, "%*[^;];%*[^;];%*[^;];%*[^;];%f;%s %s", &nbDistance ,driverNom, driverPrenom);
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

  
    //Créer un fichier .txt temporaire pour stocker les infos traitées
    FILE* fichier_temp;
    fichier_temp = fopen("./temp/data_d2.txt", "w");
    if (fichier_temp == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv data_d2 ");
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
//Struct -> stockage données trajets
typedef struct _trajet
{
int routeID;
float totalDistance;
} TrajetData;


void traitement_l(char *fichier) {

  TrajetData trajet[300];
  int nbTrajet = 0;

   int currentID = 0;
   float currentDistance = 0;
  
  char ligne[ligne_taille_max];

  if(strcmp(chemin_fichier, "./data/") == 0)
  {
    strcat(chemin_fichier,fichier);
    strcat(chemin_fichier, ".csv");
  }

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


      sscanf(ligne, "%d;%*[^;];%*[^;];%*[^;];%f;%*[^;]", &currentID, &currentDistance);
      
      trajet[nbTrajet].routeID = currentID;
      trajet[nbTrajet].totalDistance = currentDistance;
      nbTrajet++;
  }

    fclose(file);


    //Créer un fichier .txt temporaire pour stocker les infos traitées
    FILE* fichier_temp;
    fichier_temp = fopen("./temp/data_l.txt", "w");
    if (fichier_temp == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv");
      exit(EXIT_FAILURE);
    }

    //On met les infos dans le fichier .txt temporaire
    for(int i=0; i<nbTrajet; i++)
      {
        fprintf(fichier_temp, "%d;%f\n", trajet[i].routeID, trajet[i].totalDistance);
      }

    fclose(fichier_temp); 
}

//----------------------------------------------------------------//


//------------------------------ Traitement t ---------------------//

void traitement_t(char *fichier) 
{

  if(strcmp(chemin_fichier, "./data/") == 0)
  {
    strcat(chemin_fichier,fichier);
    strcat(chemin_fichier, ".csv");
  }

  FILE* file = fopen(chemin_fichier, "r");
  if (file == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }
  
  char ligne[ligne_taille_max];
  
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
  if(strcmp(chemin_fichier, "./data/") == 0)
  {
    strcat(chemin_fichier,fichier);
    strcat(chemin_fichier, ".csv");
  }

  FILE* file = fopen(chemin_fichier, "r");
  if (file == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  char ligne[ligne_taille_max];

  //Ignorer la première ligne -> présentation des colones
  fgets(ligne, ligne_taille_max, file);

  Trajet trajetCurrent;

  int *h = 0;
  Arbre *node = NULL;
  while (fgets(ligne, ligne_taille_max, file) != NULL)
    {
      sscanf(ligne, "%d;%*[^;];%*[^;];%*[^;];%f;%*[^;]", &trajetCurrent.id, &trajetCurrent.distance);
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