#include "constant.h"

typedef struct {
	int nbVaisseaux[NombreDeVaisseaux];
	int nbTotalVaisseaux;
	int techno[3];
} Flotte;

typedef struct {
	char nom[255];
	Flotte flotte;
} Joueur;

void afficherFlotte(Flotte*);
Flotte* nouvelleFlotte();
int initFlotte(Flotte *f);
int charger(char* nomFichier, Flotte *f);