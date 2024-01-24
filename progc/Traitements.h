#ifndef __Traitements__H__
#define __Traitements__H__

#include "Outils_AVL_T.h"
#include "Outils_AVL_S.h"

//Fonct° Traitements Générales

void traitement_d2();
void traitement_l();
void traitement_t();
void traitement_s();


//--------------------- TRAITEMENT D1 ---------------------//

void traitement_d1();

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


//---------------------------------------------------------//

//--------------------- TRAITEMENT S ---------------------//






//---------------------------------------------------------//

#endif