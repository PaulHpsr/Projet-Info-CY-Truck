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

int compareDrivers();

//--------------------------------------------------------//

//--------------------- TRAITEMENT D2 ---------------------//

//Struct -> stockage données trajets
typedef struct _trajet
{
int routeID;
float totalDistance;
} TrajetData;

int compareTrajets();

//---------------------------------------------------------//


#endif