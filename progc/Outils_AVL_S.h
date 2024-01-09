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