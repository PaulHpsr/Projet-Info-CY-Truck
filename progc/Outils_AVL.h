#ifndef __Outils_AVL__H__
#define __Outils_AVL__H__

//AVL
// Struct Arbre
typedef struct arbre {
int data;
struct arbre *left;
struct arbre *right;
int eq;
} Arbre;


Arbre *creerArbre();
Arbre *recherche();
Arbre *insertion();
Arbre* suppMinAVL();
Arbre *suppressionAVL();
Arbre* rotationGauche();
Arbre* rotationDroite();
Arbre* rotationDoubleGauche();
Arbre* rotationDoubleDroit();
Arbre* equilibrageAVL();


#endif