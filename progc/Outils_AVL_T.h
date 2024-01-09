#ifndef __Outils_AVL_T__H__
#define __Outils_AVL_T__H__

//AVL
typedef struct _avl_t
{
char nomVille[50]; //nom ville
int nbrTrajets; //nombre d'itération de la ville
int nbrDepart; //nombre de fois ou la ville est départ
struct _avl_t* left;
struct _avl_t* right;
int eq; //equilibre
} Arbre;


Arbre *creerArbre();
Arbre *insertion();
Arbre* rotationGauche();
Arbre* rotationDroite();
Arbre* rotationDoubleGauche();
Arbre* rotationDoubleDroit();
Arbre* equilibrageAVL();

//
void postfixeFilsDroit(); 
void freeTree();

#endif