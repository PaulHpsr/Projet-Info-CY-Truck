#ifndef __HEADER__H__
#define __HEADER__H__

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



//

//Fonct°
void traitement_d1();
void traitement_d2();
void traitement_l();
void traitement_t();
void traitement_s();



#endif