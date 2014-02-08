#include "player.h"
#include <stdio.h>
#include <stdlib.h>

void afficherFlotte(Flotte* f)
{
	int i;
	printf("Total:\t%d\n", f->nbTotalVaisseaux);
	printf("Techo:\t%d/%d/%d\n", f->techno[2],f->techno[1],f->techno[0]);
	for(i = 0 ; i < NombreDeVaisseaux ; i++)
	{
		if(f->nbVaisseaux[i] > 0) 
			printf("%d:\t%d\n", i, f->nbVaisseaux[i]);
	}
}

Flotte* nouvelleFlotte()
{
	Flotte* f = malloc(sizeof(Flotte));
	initFlotte(f);
	return f;
}

int initFlotte(Flotte *f)
{
	int i;
	if(f == NULL)
		return 0;
	f->nbTotalVaisseaux = 0;
	f->techno[2]=f->techno[1]=f->techno[0] = 0;
	for(i = 0 ; i < NombreDeVaisseaux ; i++)
	{
		f->nbVaisseaux[i] = 0;
	}
	return 1;
}

int charger(char* nomFichier, Flotte *f)
{
	int i,j, n;
	char ligne[20];
	FILE *fichier = fopen(nomFichier, "r");
	if(fichier == NULL)
		return 0;
	f->nbTotalVaisseaux = 0;
	f->techno[0] = f->techno[1] =f->techno[2] = 0;
	if(fgets(ligne, 20, fichier) && sscanf(ligne, "%d %d %d\n", &i, &j, &n) == 3)
	{
		f->techno[0] = n;
		f->techno[1] = j;
		f->techno[2] = i;
	}
	else 
		fseek(fichier, 0, SEEK_SET);
	for(i = 0 ; i < NombreDeVaisseaux ; i++)
		f->nbVaisseaux[i] = 0;
	while(fgets(ligne, 20, fichier))
	{
		if(sscanf(ligne, "%d:%d\n", &i, &n) == 2)
			if( i >= 0 && i < NombreDeVaisseaux && n > 0)
			{
				f->nbVaisseaux[i] = n;
			}
	}
	for(i = 0 ; i < NombreDeVaisseaux ; i++)
		f->nbTotalVaisseaux += f->nbVaisseaux[i];
	fclose(fichier);

	return f->nbTotalVaisseaux <= NombreMaxDeVaisseaux;
}