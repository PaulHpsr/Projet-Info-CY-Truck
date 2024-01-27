#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Outils_AVL_S.h"





//------------------------------ Traitement S ---------------------//


#define ligne_taille_max 5000 
char chemin_fichierS[50] ="./data/";

//
void traitement_s(char *fichier) 
{
  if(strcmp(chemin_fichierS, "./data/") == 0)
  {
    strcat(chemin_fichierS,fichier);
    strcat(chemin_fichierS, ".csv");
  }

  FILE* file = fopen(chemin_fichierS, "r");
  if (file == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }

  char ligne[ligne_taille_max];

  //Ignorer la première ligne -> présentation des colones
  fgets(ligne, ligne_taille_max, file);

  Trajet* trajetCurrent;

  int *h = 0;
  Node* node = NULL;
  while (fgets(ligne, ligne_taille_max, file) != NULL)
    {
      sscanf(ligne, "%d;%*[^;];%*[^;];%*[^;];%f;%*[^;]", trajetCurrent->id, trajetCurrent->distance);
      node = insertionS(node,trajetCurrent, h); 
//Mettre équilibrage AVL
node = equilibrageAVLS(node);
    }

  fclose(file);
  //Avoir les 10 villes les + visités
  TrajetFinal* tableau[10];
  int i = 0;
  postfixeFilsDroitS(node,tableau ,i);

  freeTreeS(node);

  //On met les infos dans le fichier .txt temporaire
  FILE* fichier_temp;
  fichier_temp = fopen("./temp/data_s.txt", "w");
    if (fichier_temp == NULL)
    {
      perror("ERREUR : impossible d'ouvrir le fichier csv");
      exit(EXIT_FAILURE);
    }

    //On met les infos dans le fichier .txt temporaire
    for(int y=0; y<10; y++)
      {
        fprintf(fichier_temp, "%d;%f;%f;%f", tableau[y]->id, tableau[y]->min, tableau[y]->max, tableau[y]->moy);
      }
    fclose(fichier_temp);

}

//----------------------------------------------------------------//



//Outils AVL_S:
//Créa node :
Node* newNode(Trajet* data) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->id = data->id;
  node->max=data->distance;
  node->min=0;
  node->left = NULL;
  node->right = NULL;
  return node;
}

Node* insertionS(Node* node, Trajet* data, int* h) 
{
  if(node == NULL)
  {
    *h = 1;
    return newNode(data);
  }

  if (data->id < node->id)
  {
    node->left = insertionS(node->left, data, h);
    *h = -*h;
  }
  else if (data->id > node->id)
  {
    node->right = insertionS(node->right, data, h);
  }
  else if (data->id == node->id)
  {
    *h=0;
    //L'id trajet est déjà présent dans l'arbre -> on va vérif si distance > ou <

    //Verif max
    if (data->distance > node->max)
    {
    node->max = data->distance;

    }


    if(data->distance<node->min)
    {
      node->min = data->distance;
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
Node* rotationGaucheS(Node* a)
{
  Node* pivot;
  int eq_a, eq_p;

  pivot = a->right;
  a->right = pivot->left;
  pivot->left = a;
  eq_a = a->eq;
  eq_p = pivot->eq;
  a->eq = eq_a - fmax(eq_p, 0) - 1;
  pivot->eq = eq_p - fmin(fmin(eq_a - 2 , eq_a+eq_p-2), eq_p - 1);
  a = pivot;
  return a;
}

//Cas 2: ele. aj. tt a gauche
Node* rotationDroiteS(Node* a)
{
  Node* pivot;
  int eq_a, eq_p;

  pivot = a->left;
  a->left = pivot->right;
  pivot->right = a;
  eq_a = a->eq;
  eq_p = pivot->eq;
  a->eq = eq_a - fmin(eq_p, 0) + 1;
  pivot->eq = eq_p - fmax(fmax(eq_a + 2 , eq_a+eq_p+2), eq_p + 1);
  a = pivot;
  return a;
}

//Rota double
Node* rotationDoubleGaucheS(Node* a)
{
  a->right = rotationDroiteS(a->right);
  return rotationGaucheS(a);
}

Node* rotationDoubleDroitS(Node* a)
{
  a->left = rotationGaucheS(a->left);
  return rotationGaucheS(a);
}

// Equilibrage
Node* equilibrageAVLS(Node* a)
{
  if(a!=NULL)
  { // Équilibrer les sous-arbres
    a->left = equilibrageAVLS(a->left);
    a->right = equilibrageAVLS(a->right);
    
   if(a->eq >= 2)
    {
      if(a->right->eq >= 0)
      {
       return rotationGaucheS(a);
     }
     else{
        return rotationDoubleGaucheS(a);
     }
    }

    else if(a-> eq <= -2)
    {
      if(a->left->eq <= 0){
        return rotationDroiteS(a);
      }
      else{
        return rotationDoubleDroitS(a);
      }
    }
  }
  return a;
}

void postfixeFilsDroitS(Node* node, TrajetFinal* tableau, int* i) 
{
  if (node == NULL || *i>=10)
  {
    return;
  }

  //Parcourir tt les fils droit (plus grande valeure)
  postfixeFilsDroitS(node->right, tableau, i);

  //Pareil mais avec le fils gauche 
  postfixeFilsDroitS(node->left, tableau, i);

  tableau[*i].id= node->id;
  tableau[*i].max = node->max;
  tableau[*i].min = node->min;
  tableau[*i].moy = (node->max - node->min)/2;
  (*i)++;
}

void freeTreeS(Node* root) {
    if (root == NULL)
        return;

    freeTreeS(root->left);
    freeTreeS(root->right);
    free(root);
}