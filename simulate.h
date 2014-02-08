#include "player.h"

void simuler(Flotte f1, Flotte f2, long pertes[2][3]);

int tirer(int t1, int tech1[3], int t2, int tech2[3]);

int getType(int n, int f[NombreDeVaisseaux]);

int estDetruit(int, int);

void initSimulateur();

void libererSimulateur();