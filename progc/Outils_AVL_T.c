#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Outils_AVL_T.h"



//------------------------------ Traitement t ---------------------//

#define ligne_taille_max 5000 
char chemin_fichierT[50] ="./data/";


void traitement_t(char *fichier) 
{


  if(strcmp(chemin_fichierT, "./data/") == 0)
  {
    strcat(chemin_fichierT,fichier);
    strcat(chemin_fichierT, ".csv");
  }

  FILE* file = fopen(chemin_fichierT, "r");
  if (file == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  char ligne[ligne_taille_max];

  //Ignorer la première ligne -> présentation des colones
  fgets(ligne, ligne_taille_max, file);

  char* TownA = malloc(sizeof(char)*50);
  char* TownB = malloc(sizeof(char)*50);

  int* h = malloc(sizeof(int));
  *h=0;
  Arbre* node = NULL;

  while (fgets(ligne, ligne_taille_max, file) != NULL) {
    char *token = strtok(ligne, ";");
    if (token != NULL) {
      // Skip les deux premiers champs 
      token = strtok(NULL, ";");
      token = strtok(NULL, ";");

      // Les prochains deux champs contiennent les noms de ville
      if (token != NULL) {
        // Vérif que la chaîne est correctement copiée et finie par le caractère nul
        strcpy(TownA, token);
      }

      token = strtok(NULL, ";");
      if (token != NULL) {
        // Vérif que la chaîne est correctement copiée et finie par le caractère nul
        strcpy(TownB, token);
      }
      node = insertion(node, TownA, h, 0); 
      node = insertion(node, TownB, h, 1); 
    }
  }
  node = equilibrageAVL(node); 
  fclose(file);
  free(TownA);
  free(TownB);
  // Avoir les 10 villes les + visitées

  // On met les infos dans le fichier .txt temporaire
  FILE* fichier_temp;
  fichier_temp = fopen("./temp/data_t.txt", "w");
  if (fichier_temp == NULL) {
    perror("ERREUR : impossible d'ouvrir le fichier temporaire");
    exit(EXIT_FAILURE);
  }

  
 postfixeFilsDroit(node, fichier_temp);  


  fclose(fichier_temp);
  
  freeTree(node);
  free(h);
 
}



//----------------------------------------------------------------//





//
// Creer arbre
Arbre* creerArbre(char* nomVille) {
  Arbre *node = malloc(sizeof(Arbre));
  if (node == NULL) 
  {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }

  strcpy(node->nomVille, nomVille);
  node->left = NULL;
  node->right = NULL;
  node->nbrTrajets = 0;
  node->nbrDepart = 0;
  node->eq = 0;
  return node;
}


//                              Operations

// Obtenir les 10 plus grandes villes:
void postfixeFilsDroit(Arbre* node, FILE* fichier_temp) 
{

if(node != NULL)
{
  fprintf(fichier_temp, "%s;%d;%d\n", node->nomVille, node->nbrTrajets, node->nbrDepart);


  if(node->right != NULL){
    postfixeFilsDroit(node->right, fichier_temp); 
  }
  if(node->left != NULL){
    postfixeFilsDroit(node->left, fichier_temp); 
  }
}
  
}


// Insertion
Arbre* insertion(Arbre* node, char* nomVille, int* h, int depart) 
{
  if(node == NULL)
  {
    *h = 1;
    node = creerArbre(nomVille);
    node->nbrTrajets =1;
    node->nbrDepart =1;
    return node;
  }
  int comparaison = strcmp(nomVille, node->nomVille);

  if (comparaison != 0)
  {
    if(node->nbrTrajets >= 1){
    node->left = insertion(node->left, nomVille, h, depart);
    *h = -*h;
    }
    else if (node->nbrTrajets < 1)
    {
      node->right = insertion(node->right, nomVille, h, depart);
    }
  }
  else{
    *h=0;
    //La ville existe déjà -> +1 nbr de fois ou elle est traversée
    node->nbrTrajets++;
    if(depart == 1)
    {
      node->nbrDepart++;
    }
  }

  if(*h != 0)
  {
    node->eq = node->eq + *h;
    if(node->eq == 0)
    {
      *h = 0;
    }
    else{
      *h = 1;
    }
  }
  return node;
}


//                         Equilibrage

// Cas 1 : ele. aj. tt a droite
Arbre* rotationGauche(Arbre* a)
{
  Arbre* pivot;
  int eq_a, eq_p;

  pivot = a->right;
  a->right = pivot->left;
  pivot->left = a;
  eq_a = a->eq;
  eq_p = pivot->eq;
  a->eq = eq_a - fmax(eq_p, 0) - 1;
  pivot->eq = fmin(fmin(eq_a - 2 , eq_a+eq_p-2), eq_p - 1);
  a = pivot;
  return a;
}

//Cas 2: ele. aj. tt a gauche
Arbre* rotationDroite(Arbre* a)
{
  Arbre* pivot;
  int eq_a, eq_p;

  pivot = a->left;
  a->left = pivot->right;
  pivot->right = a;
  eq_a = a->eq;
  eq_p = pivot->eq;
  a->eq = eq_a - fmin(eq_p, 0) + 1;
  pivot->eq = fmax(fmax(eq_a + 2 , eq_a+eq_p+2), eq_p + 1);
  a = pivot;
  return a;
}

//Rota double
Arbre* rotationDoubleGauche(Arbre* a)
{
  a->right = rotationDroite(a->right);
  return rotationGauche(a);
}

Arbre* rotationDoubleDroit(Arbre* a)
{
  a->left = rotationGauche(a->left);
  return rotationDroite(a);
}

// Equilibrage
Arbre* equilibrageAVL(Arbre* a)
{
  if(a!= NULL)
  {

    // Équilibrer les sous-arbres
    if (a->left != NULL)
      a->left = equilibrageAVL(a->left);
    if (a->right != NULL)
      a->right = equilibrageAVL(a->right);

  if(a->eq >= 2)
  {
    if(a->right->eq >= 0)
    {
      return rotationGauche(a);
    }
    else{
      return rotationDoubleGauche(a);
    }
  }

  else if(a-> eq <= -2)
  {
    if(a->left->eq <= 0){
      return rotationDroite(a);
    }
    else{
      return rotationDoubleDroit(a);
    }
  }
  }
  return a;
}
//


// Fonction pour libérer la mémoire occupée par les nœuds de l'AVL
void freeTree(Arbre *root) {
  if (root == NULL)
  {
     return;
  }

  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

