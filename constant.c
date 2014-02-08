#include "constant.h"

const int TirRapide[NombreDeVaisseaux][NombreDeVaisseaux] = {
/* SmallCargoShip	*/ 	{1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1},
/* LargeCargoShip	*/	{1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1},
/* LightFighter		*/ 	{1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1},
/* HeavyFighter		*/	{3,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1},
/* Cruiser			*/ 	{1,	1,	6,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1},
/* Battleship		*/ 	{1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1},
/* ColonyShip		*/ 	{1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1},
/* Recycler			*/ 	{1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1},
/* EspionageProbe	*/ 	{1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1},
/* Bomber			*/ 	{1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	1},
/* Destroyer		*/ 	{1,	1,	1,	1,	1,	1,	1,	1,	5,	1,	1,	1,	2},
/* Deathstar		*/ 	{250,	250,	200,	100,	33,	30,	250,	250,	1250,	25,	1250,	1,	15},
/* Battlecruiser	*/ 	{3,	3,	1,	4,	4,	7,	1,	1,	5,	1,	1,	1,	1}};

const int Caracteristiques[NombreDeVaisseaux][3] = {
/* SmallCargoShip 	*/	{4000,	10,	5},
/* LargeCargoShip 	*/	{12000,	25,	5},
/* LightFighter 	*/ 	{4000,	10,	50},
/* HeavyFighter 	*/ 	{10000,	25,	150},
/* Cruiser 			*/ 	{27000,	50,	400},
/* Battleship 		*/ 	{60000,	200,	1000},
/* ColonyShip 		*/ 	{30000,	100,	50},
/* Recycler 		*/ 	{16000,	10,	1},
/* EspionageProbe 	*/ 	{1000,	0,	0},
/* Bomber 			*/ 	{75000,	500,	1000},
/* Destroyer 		*/ 	{110000,	500,	2000},
/* Deathstar 		*/ 	{9000000,	50000,	200000},
/* Battlecruiser 	*/ 	{70000,	400,	700}};

const int Couts[NombreDeVaisseaux][3] = {
/* SmallCargoShip 	*/	{2000,	2000,	0},
/* LargeCargoShip 	*/	{6000, 6000, 0},
/* LightFighter 	*/	{3000,	1000,	0},
/* HeavyFighter 	*/	{6000,	4000,	0},
/* Cruiser 			*/	{20000,	7000,	2000},
/* Battleship 		*/	{45000,	15000,	0},
/* ColonyShip 		*/	{10000,	20000,	10000},
/* Recycler 		*/	{10000,	6000,	2000},
/* EspionageProbe 	*/	{0,	1000,	0},
/* Bomber 			*/	{50000,	25000,	15000},
/* Destroyer 		*/	{60000,	50000,	15000},
/* Deathstar 		*/	{5000000,	4000000,	1000000},
/* Battlecruiser 	*/	{30000,	40000,	15000}};