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
}Arbre;

//Outil_AVL_T -> fonct° + struct AVL pour traitement T
typedef struct VilleStats
{
char nomVille[50];
int nbTrajets;
int nbDepart;
}Ville;
//--------------------- TRAITEMENT T ---------------------//

void traitement_t(char *);

//---------------------------------------------------------//


//--------------------- AVL T ---------------------//
Arbre* creerArbre(char*);
Arbre* insertion(Arbre*, char*, int*, int);
Arbre* rotationGauche(Arbre*);
Arbre* rotationDroite(Arbre*);
Arbre* rotationDoubleGauche(Arbre*);
Arbre* rotationDoubleDroit(Arbre*);
Arbre* equilibrageAVL(Arbre*);

//
void postfixeFilsDroit(Arbre* node, Ville tableau[], int *i);
void freeTree(Arbre*);

//---------------------------------------------------------//

#endif