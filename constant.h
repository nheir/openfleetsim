/*
Constantes du jeu
	- RF
	- Caracteristiques
	- Couts
*/
#ifndef CONSTANTES_H
#define CONSTANTES_H

#define NombreMaxDeVaisseaux	5000000
#define NombreMaxFlottes		10

#define SmallCargoShip	0
#define LargeCargoShip	1
#define LightFighter	2
#define HeavyFighter	3
#define Cruiser			4
#define Battleship		5
#define ColonyShip		6
#define Recycler		7
#define EspionageProbe	8
#define Bomber			9
#define Destroyer		10
#define Deathstar		11
#define Battlecruiser	12

#define NombreDeVaisseaux 13

const int TirRapide[NombreDeVaisseaux][NombreDeVaisseaux];

const int Caracteristiques[NombreDeVaisseaux][3];

const int Couts[NombreDeVaisseaux][3];

typedef struct {
	int vainqueur;
	long pertes[2][3];
} Resultat;

#endif