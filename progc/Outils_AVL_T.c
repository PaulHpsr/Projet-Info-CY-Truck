#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Outils_AVL_T.h"
#include "Traitements.h"

//AVL

// Creer arbre
Arbre *creerArbre(char* nomVille) {
  Arbre *node = malloc(sizeof(Arbre));
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
void postfixeFilsDroit(Arbre *node, Ville* tableau , int *i) 
{
  if (node == NULL || *i>=10)
  {
    return;
  }
  //Parcourir tt les fils droit (plus grande valeure)
  postfixeFilsDroit(node->right, tableau, i);

  //Pareil mais avec le fils gauche 
  postfixeFilsDroit(node->left, tableau, i);

  tableau[*i].nbDepart = node->nbrDepart;
  tableau[*i].nbTrajets = node->nbrTrajets;
  strcpy(tableau[*i].nomVille,node->nomVille);
  (*i)++;
}

// Insertion
Arbre *insertion(Arbre *node, char* nomVille, int* h, int depart) 
{
  if(node == NULL)
  {
    *h = 1;
    return creerArbre(nomVille);
  }

  int comparaison = strcmp(nomVille, node->nomVille);
  
  if (comparaison < 0)
  {
    node->left = insertion(node->left, nomVille, h, depart);
    *h = -*h;
  }
  else if (comparaison > 0)
  {
    node->right = insertion(node->right, nomVille, h, depart);
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


// Fonction pour libérer la mémoire occupée par les nœuds de l'AVL
void freeTree(Arbre *root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

