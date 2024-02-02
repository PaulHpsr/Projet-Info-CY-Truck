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

  Trajet* trajetCurrent = malloc(sizeof(Trajet));

  int* h =malloc(sizeof(int));
  *h=0;
  Node* node = NULL;
  
   while (fgets(ligne, ligne_taille_max, file) != NULL)
    {
      sscanf(ligne, "%d;%*[^;];%*[^;];%*[^;];%f;%*[^;]", &trajetCurrent->id, &trajetCurrent->distance);
      
      node = insertionS(node,trajetCurrent, h); 
      //Mettre équilibrage AVL
    }
  node = equilibrageAVLS(node);
  fclose(file);
  

  //On met les infos dans le fichier .txt temporaire
  FILE* fichier_temp;
  fichier_temp = fopen("./temp/data_s.txt", "a");
  if (fichier_temp == NULL)
  {
    perror("ERREUR : impossible d'ouvrir le fichier csv");
    exit(EXIT_FAILURE);
  }
    postfixeFilsDroitS(node, fichier_temp);  

  fclose(fichier_temp);
  
  freeTreeS(node);
  free(h);


}

//----------------------------------------------------------------//



//Outils AVL_S:
//Créa node :
Node* newNode(Trajet* data) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) 
  {
    fprintf(stderr, "Erreur d'allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  node->id = data->id;
  node->max=data->distance;
  node->min=data->distance;
  node->left = NULL;
  node->right = NULL;
  node->eq = 0;
  return node;
}

Node* insertionS(Node* node, Trajet* data, int* h) 
{
  if(node == NULL)
  {
    *h = 1;
    node =  newNode(data);
    return node;
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
  pivot->eq = fmin(fmin(eq_a - 2 , eq_a+eq_p-2), eq_p - 1);
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
  pivot->eq = fmax(fmax(eq_a + 2 , eq_a+eq_p+2), eq_p + 1);
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
  return rotationDroiteS(a);
}

// Equilibrage
Node* equilibrageAVLS(Node* a)
{
  if(a!= NULL)
  {

    // Équilibrer les sous-arbres
    a->left = equilibrageAVLS(a->left);
    a->right = equilibrageAVLS(a->right);
  if(a->eq >= 2)
  {
    if(a->right->eq >= 0)
    {
      return rotationGaucheS(a);
    }
    else
    {
      return rotationDoubleGaucheS(a);
    }
  }
  else if(a-> eq <= -2)
  {

    if(a->left->eq <= 0)
    {
      a = rotationDroiteS(a);
      return a;
    }
    else
    {
      return rotationDoubleDroitS(a);
    }
  }
  }
  return a;
}

void postfixeFilsDroitS(Node* node, FILE* fichier_temp) 
{

  if(node != NULL)
  {
    float moyenne = (node->min + node->max) / 2.0;
    float min_max = (node->max-node->min);

    
    fprintf(fichier_temp, "%d;%f;%f;%f;%f\n", node->id, node->min, moyenne, node->max, min_max);

    if(node->right != NULL){
      postfixeFilsDroitS(node->right, fichier_temp); 
    }
    if(node->left != NULL){
      postfixeFilsDroitS(node->left, fichier_temp); 
    }

  }

}

void freeTreeS(Node* root) {
  if (root == NULL)
  {
    return;
  }

  freeTreeS(root->left);
  freeTreeS(root->right);
  free(root);
}