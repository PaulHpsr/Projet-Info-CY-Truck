#include <stdio.h>
#include <stdlib.h>
#include "header.h"

//AVL

// Creer arbre
Arbre *creerArbre(int data) {
  Arbre *node = malloc(sizeof(Arbre));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->eq = 0;
  return node;
}


//                              Operations

// Recherche
Arbre *recherche(Arbre *node, int data) {
  if(node == NULL)
  {
    return NULL;
  }
  else if(node->data == data)
  {
    return node;
  }
  else if(node->data > data)
  {
    return recherche(node->left, data);
  }
  else{
    return recherche(node->right , data);
  }
}

// Insertion
Arbre *insertion(Arbre *node, int data, int* h) 
{
  if(node == NULL)
  {
    *h = 1;
    return creerArbre(data);
  }
  else if (data < node->data)
  {
    node->left = insertion(node->left, data, h);
    *h = -*h;
  }
  else if (data > node->data)
  {
    node->right = insertion(node->right, data, h);
  }
  else{
    *h=0;
    return node;
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

// Suppression
Arbre* suppMinAVL(Arbre* a, int* h, int* pe)
{
  Arbre* tmp;
  if(a->left == NULL)
  {
    *pe = a->data;
    *h = -1;
    tmp = a;
    a = a->right;
    free(tmp);
    return a;
  }
  else{
    a->left = suppMinAVL(a->left, h, pe);
    if(*h != 0)
  }

  if(*h == -0)
  {
    a->eq = a->eq + *h;
    if(a->eq == 0){
      *h = -1;
    }
    else{
      *h = 0;
    }
  }
  return a;
}

 Arbre *suppressionAVL(Arbre *node, int data, int* h)
{
  if(node == NULL)
  {
    *h = 1;
    return node;
  }
  else if(data > node->data)
  {
    node->right = suppressionAVL(node->right, data, h);
  }
  else if(data< node->data)
  {
    node->left = suppressionAVL(node->left, data, h);
    *h = -*h;
  }
  else if(node->right != NULL)
  {
    node->left = suppMinAVL(node->left, h, node->data);
  }
  else{
    Arbre *temp = node;
    node = node->left;
    free(temp);
    *h= -*h;
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
  pivot->eq = eq_p - fmin(fmin(eq_a - 2 , eq_a+eq_p-2), eq_p - 1);
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
  pivot->eq = eq_p - fmax(fmax(eq_a + 2 , eq_a+eq_p+2), eq_p + 1);
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
  return rotationGauche(a);
}

// Equilibrage
Arbre* equilibrageAVL(Arbre* a)
{
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
  return a;
}
//


void traitement_d1() {
    // Code spécifique pour le traitement -d1
    printf("Traitement pour -d1\n");
}

void traitement_d2() {
    // Code spécifique pour le traitement -d2
    printf("Traitement pour -d2\n");
}

void traitement_l() {
    // Code spécifique pour le traitement -l
    printf("Traitement pour -l\n");
}

void traitement_t() {
    // Code spécifique pour le traitement -t
    printf("Traitement pour -t\n");
}

void traitement_s() {
    // Code spécifique pour le traitement -s
    printf("Traitement pour -s\n");
}



