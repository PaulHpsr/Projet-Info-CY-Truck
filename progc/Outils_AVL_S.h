#ifndef __Outils_AVL_S__H__
#define __Outils_AVL_S__H__


// Structure pour l'AVL_S
typedef struct _node 
{
  int id;
  float max;
  float min;
  struct _node* left;
  struct _node* right;
  int eq;
}Node;

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
}TrajetFinal;


//--------------------- TRAITEMENT S ---------------------//

void traitement_s(char *);

//---------------------------------------------------------//

//--------------------- TRAITEMENT S ---------------------//
Node* newNode(Trajet*);
Node* insertionS(Node*,Trajet*, int*);
Node* rotationGaucheS(Node*);
Node* rotationDroiteS(Node*);
Node* rotationDoubleGaucheS(Node*);
Node* rotationDoubleDroitS(Node*);
Node* equilibrageAVLS(Node*);
void postfixeFilsDroitS(Node*, TrajetFinal*, int* );
void freeTreeS(Node*);

//---------------------------------------------------------//

#endif