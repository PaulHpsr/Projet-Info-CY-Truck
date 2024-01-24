#ifndef __Outils_AVL_S__H__
#define __Outils_AVL_S__H__

// Structure pour l'AVL_S
typedef struct _node 
{
  int id;
  float max;
  float min;
  struct _node *left;
  struct _node *right;
  int eq;
} Node;


// Structure pour stocker les données d'un trajet
typedef struct 
{
  int id;
  float distance;
} Trajet;

typedef struct
{
int id;
float max;
float min;
float moy;
} TrajetFinal;


//
Node *newNode();
Node *insertionS();
Node* rotationGaucheS();
Node* rotationDroiteS();
Node* rotationDoubleGaucheS();
Node* rotationDoubleDroitS();
Node* equilibrageAVLS();
void postfixeFilsDroitS();
void freeTreeS();



#endif