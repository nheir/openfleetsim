#include "simulate.h"
#include "random.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* degat1 = NULL;
int* degat2 = NULL;
int* bouclier1 = NULL;
int* bouclier2 = NULL;

void initEtat()
{
	if(degat1 == NULL) degat1 = malloc(NombreMaxDeVaisseaux*sizeof(int));
	if(degat2 == NULL) degat2 = malloc(NombreMaxDeVaisseaux*sizeof(int));
	if(bouclier1 == NULL) bouclier1 = malloc(NombreMaxDeVaisseaux*sizeof(int));
	if(bouclier2 == NULL) bouclier2 = malloc(NombreMaxDeVaisseaux*sizeof(int));
}

void libererEtat()
{
	if(degat1 != NULL) free(degat1);
	if(degat2 != NULL) free(degat2);
	if(bouclier1 != NULL) free(bouclier1);
	if(bouclier2 != NULL) free(bouclier2);
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


void simuler(Flotte f1, Flotte f2, long pertes[2][3], Flotte *fr1, Flotte *fr2)
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
		{
			degat1[j] = (Caracteristiques[typeCible][0] * (10+f1.techno[0])) / 10;;
			bouclier1[j] = Caracteristiques[typeCible][1] * (10+f1.techno[1]);//(Caracteristiques[typeCible][0] * (10+f1.techno[0])) / 10; 
		}
		for( ; k < fl2[i] ; k++)
		{
			degat2[k] = (Caracteristiques[typeCible][0] * (10+f2.techno[0])) / 10;;
			bouclier2[k] = Caracteristiques[typeCible][1] * (10+f2.techno[1]);//(Caracteristiques[typeCible][0] * (10+f2.techno[0])) / 10;
		}
	}

	for(i = 0; i < 6; i++)
	{
		if(fl1[NombreDeVaisseaux-1] == 0 || fl2[NombreDeVaisseaux-1] == 0)
			break;

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
				bouclier2[cible] -= tirer(typeTir, f1.techno, bouclier2[cible]);
				coque = (Caracteristiques[typeCible][0] * (10+f2.techno[0])) / 10;
				if(bouclier2[cible] < 0)
				{
					degat2[cible] += bouclier2[cible];
					bouclier2[cible] = 0;
				}
				if(estDetruit(coque, degat2[cible])) 
					degat2[cible] = 0;
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
				bouclier1[cible] -= tirer(typeTir, f2.techno, bouclier1[cible]);
				coque = (Caracteristiques[typeCible][0] * (10+f1.techno[0])) / 10;
				if(bouclier1[cible] < 0)
				{
					degat1[cible] += bouclier1[cible];
					bouclier1[cible] = 0;
				}
				if(estDetruit(coque, degat1[cible])) 
					degat1[cible] = 0;
				continuer = bernI(1,TirRapide[typeTir][typeCible]);
			}
		}
		// Pertes
		n = fl1[NombreDeVaisseaux-1];
		k = 0;
		for(j = 0 ; j < n ; j++)
		{
			typeCible = getType(j,fl1);
			if(degat1[j] <= 0)
			{
				pertes[0][0] += Couts[typeCible][0];
				pertes[0][1] += Couts[typeCible][1];
				pertes[0][2] += Couts[typeCible][2];
				bouclier1[j] = 0;
			}
			else
			{
				bouclier = Caracteristiques[typeCible][1] * (10+f1.techno[1]);
				bouclier1[j] = bouclier;
			}
		}
		n = fl2[NombreDeVaisseaux-1];
		k = 0;
		for(j = 0 ; j < n ; j++)
		{
			typeCible = getType(j,fl2);
			if(degat2[j] <= 0)
			{
				pertes[1][0] += Couts[typeCible][0];
				pertes[1][1] += Couts[typeCible][1];
				pertes[1][2] += Couts[typeCible][2];
				bouclier2[j] = 0;
			}
			else
			{
				bouclier = Caracteristiques[typeCible][1] * (10+f2.techno[1]);
				bouclier2[j] = bouclier;
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
				if(bouclier1[j] == 0)
					l++;
				else
				{
					degat1[k] = degat1[j];
					bouclier1[k] = bouclier1[j];
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
				if(bouclier2[j] == 0)
					l++;
				else
				{
					degat2[k] = degat2[j];
					bouclier2[k] = bouclier2[j];
					k++;
				}
			}
			fl2[n] -= l;
		}
	}
	if(fr1 != NULL)
	{
		fr1->nbTotalVaisseaux = fl1[NombreDeVaisseaux-1];
		fr1->nbVaisseaux[0] = fl1[0];
		for(i = 1 ; i < NombreDeVaisseaux ; i++)
		{
			fr1->nbVaisseaux[i] = fl1[i] - fl1[i-1];
		}
	}
	if(fr2 != NULL)
	{
		fr2->nbTotalVaisseaux = fl2[NombreDeVaisseaux-1];
		fr2->nbVaisseaux[0] = fl2[0];
		for(i = 1 ; i < NombreDeVaisseaux ; i++)
		{
			fr2->nbVaisseaux[i] = fl2[i] - fl2[i-1];
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

int tirer(int t1, int tech1[3], int bouclier)
{
	int force;
	force = Caracteristiques[t1][2] * (10+tech1[2]);
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
