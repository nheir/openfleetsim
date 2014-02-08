#include "simulate.h"
#include "random.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* etat1 = NULL;
int* etat2 = NULL;

void initEtat()
{
	if(etat1 == NULL) etat1 = malloc(NombreMaxDeVaisseaux*sizeof(int));
	if(etat2 == NULL) etat2 = malloc(NombreMaxDeVaisseaux*sizeof(int));
}

void libererEtat()
{
	if(etat1 != NULL) free(etat1);
	if(etat2 != NULL) free(etat2);
}

void initSimulateur()
{
	initEtat();
	randInit();
}

void libererSimulateur()
{
	libererEtat();
}


void simuler(Flotte f1, Flotte f2, long pertes[2][3])
{
	int fl1[NombreDeVaisseaux] = {0};
	int fl2[NombreDeVaisseaux] = {0};
	int i,j,k,l,n, continuer;

	int cible;
	int typeTir, typeCible;
	
	int coque, bouclier;

	initEtat();

	pertes[0][0] = pertes[0][1] = pertes[0][2] = pertes[1][0] = pertes[1][1] = pertes[1][2] = 0;

	fl1[0] = f1.nbVaisseaux[0];
	fl2[0] = f2.nbVaisseaux[0];
	for(i = 1 ; i < NombreDeVaisseaux ; i++)
	{
		fl1[i] = fl1[i-1] + f1.nbVaisseaux[i];
		fl2[i] = fl2[i-1] + f2.nbVaisseaux[i];
	}

	j = 0;
	k = 0;
	for(i = 0 ; i < NombreDeVaisseaux ; i++)
	{
		typeCible = i;
		for( ; j < fl1[i] ; j++)
			etat1[j] = (Caracteristiques[typeCible][0] * (10+f1.techno[0])) / 10; 
		for( ; k < fl2[i] ; k++)
			etat2[k] = (Caracteristiques[typeCible][0] * (10+f2.techno[0])) / 10;
	}

	for(i = 0; i < 6; i++)
	{
		if(fl1[NombreDeVaisseaux-1] == 0 || fl2[NombreDeVaisseaux-1] == 0)
			return;

		//Tir
		// f1 -> f2
		for(j = 0 ; j < fl1[NombreDeVaisseaux-1] ; j++)
		{
			typeTir = getType(j,fl1);
			continuer = 1;
			while(continuer)
			{
				cible = randInt(fl2[NombreDeVaisseaux-1]);
				typeCible = getType(cible, fl2);
				//printf("%d de type %d tire sur %d de type %d\n", j, typeTir, cible, typeCible);
				etat2[cible] -= tirer(typeTir, f1.techno, typeCible, f2.techno);
				coque = (Caracteristiques[typeCible][0] * (10+f2.techno[0])) / 10;
				bouclier = Caracteristiques[typeCible][1] * (10+f2.techno[1]);
				if(estDetruit(coque, etat2[cible]+bouclier)) 
					etat2[cible] = -bouclier;
				continuer = bernI(1,TirRapide[typeTir][typeCible]);
			}
		}
		// f2 -> f1
		for(j = 0 ; j < fl2[NombreDeVaisseaux-1] ; j++)
		{
			typeTir = getType(j,fl2);
			continuer = 1;
			while(continuer)
			{
				cible = randInt(fl1[NombreDeVaisseaux-1]);
				typeCible = getType(cible, fl1);
				//printf("%d de type %d tire %d sur de type %d\n", j, typeTir, cible, typeCible);
				etat1[cible] -= tirer(typeTir, f2.techno, typeCible, f1.techno);
				coque = (Caracteristiques[typeCible][0] * (10+f1.techno[0])) / 10;
				bouclier = Caracteristiques[typeCible][1] * (10+f1.techno[1]);
				if(estDetruit(coque, etat1[cible]+bouclier)) 
					etat1[cible] = -bouclier;
				continuer = bernI(1,TirRapide[typeTir][typeCible]);
			}
		}
		// Pertes
		n = fl1[NombreDeVaisseaux-1];
		k = 0;
		for(j = 0 ; j < n ; j++)
		{
			typeCible = getType(j,fl1);
			bouclier = Caracteristiques[typeCible][1] * (10+f1.techno[1]);
			etat1[j] += bouclier;
			if(etat1[j] <= 0)
			{
				pertes[0][0] += Couts[typeCible][0];
				pertes[0][1] += Couts[typeCible][1];
				pertes[0][2] += Couts[typeCible][2];
				etat1[j] = 0;
			}
		}
		n = fl2[NombreDeVaisseaux-1];
		k = 0;
		for(j = 0 ; j < n ; j++)
		{
			typeCible = getType(j,fl2);
			bouclier = Caracteristiques[typeCible][1] * (10+f2.techno[1]);
			etat2[j] += bouclier;
			if(etat2[j] <= 0)
			{
				pertes[1][0] += Couts[typeCible][0];
				pertes[1][1] += Couts[typeCible][1];
				pertes[1][2] += Couts[typeCible][2];
				etat2[j] = 0;
			}
		}
		// Nettoyage
		j = k = 0;
		l = 0;
		for(n = 0 ; n < NombreDeVaisseaux ; n++)
		{
			typeCible = n;
			for( ; j < fl1[n] ; j++)
			{
				if(etat1[j] == 0)
					l++;
				else
				{
					etat1[k] = etat1[j];
					k++;
				}
			}
			fl1[n] -= l;
		}
		j = k = 0;
		l = 0;
		for(n = 0 ; n < NombreDeVaisseaux ; n++)
		{
			typeCible = n;
			for( ; j < fl2[n] ; j++)
			{
				if(etat2[j] == 0)
					l++;
				else
				{
					etat2[k] = etat2[j];
					k++;
				}
			}
			fl2[n] -= l;
		}
	}
}

int estDetruit(int coque, int reste)
{
	int r;
	if(10*reste > 7*coque)
		return 0;
	r = bernI(reste, coque);
	return r > 0;
}

int tirer(int t1, int tech1[3], int t2, int tech2[3])
{
	int force, bouclier;
	force = Caracteristiques[t1][2] * (10+tech1[2]);
	bouclier = Caracteristiques[t2][1] * (10+tech2[1]);
	if(bouclier > force*100)
		return 0;
	return force;
}

int getType(int n, int f[NombreDeVaisseaux])
{
	int i;
	for(i = 0 ; i < NombreDeVaisseaux ; i++)
		if(f[i] > n)
			return i;
	return i;
}
