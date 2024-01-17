#ifndef __Traitements__H__
#define __Traitements__H__


//Fonct° Traitements Générales
void traitement_d1();
void traitement_d2();
void traitement_l();
void traitement_t();
void traitement_s();


//--------------------- TRAITEMENT D1 ---------------------//

//Structure Infos
typedef struct _driverinfos {
char driverNom[50];
int nbTrajets;
} DriverInfos;

float compareDrivers();

//--------------------------------------------------------//

//--------------------- TRAITEMENT D2 ---------------------//
//Structure Infos
typedef struct _driverinfosD2 {
char driverNom[50];
float nbDistance;
} DriverInfosD2;

float compareDriversD2();
//---------------------------------------------------------//

//--------------------- TRAITEMENT L ---------------------//

//Struct -> stockage données trajets
typedef struct _trajet
{
int routeID;
float totalDistance;
} TrajetData;

float compareTrajets();

//---------------------------------------------------------//


//--------------------- TRAITEMENT T ---------------------//

//Outil_AVL_T -> fonct° + struct AVL pour traitement T
typedef struct VilleStats
{
char nomVille[50];
int nbTrajets;
int nbDepart;
}Ville;

//---------------------------------------------------------//

//--------------------- TRAITEMENT S ---------------------//

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





//---------------------------------------------------------//

#endif