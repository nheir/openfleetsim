#include "simulate.h"
#include "random.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	Flotte* flottes[NombreMaxFlottes] = {NULL};
	Flotte f1, f2;
	int i, j,k,l, tour = 1;
	int nbFlottes = 0;
	Resultat res, rest = {0};
	long sum[2];
	int tech[3] = {0};
	
	initFlotte(&f1);
	initFlotte(&f2);
	f1.nbVaisseaux[Deathstar] = 8;
	f2.nbVaisseaux[Destroyer] = 4000;

	if(argc > 1)
	{
		i = 1;
		for(;i < argc;i++)
		{
			if(argv[i][0] == '-')
			{
				if(argv[i][1] == 'n' && i+1 < argc)
				{
					tour = atoi(argv[i+1]);
					if(tour <= 0) tour = 1;
					i++;
				}
				else if(argv[i][1] == 'd')
				{
					///TODO chercher une flotte battant les autres via algo génétique? 
				}
				else if(argv[i][1] == 'c' && i+1 < argc)
				{
					///TODO cout max 
					i++;
				}
				else if(argv[i][1] == 't' && argv[i][2] == 's' && i+1 < argc)
				{
					///TODO somme des techno fixé 
					i++;
				}
				else if(argv[i][1] == 't' && argv[i][2] == 'f' && i+3 < argc)
				{
					tech[2] = atoi(argv[i+1]);
					tech[1] = atoi(argv[i+2]);
					tech[0] = atoi(argv[i+3]);
					if(tech[2] < 0 || tech[1] < 0 || tech[0] < 0)
						tech[2] = tech[1] = tech[0] = 0;
					i +=3;
				}
			}
			else
			{
				///TODO charger depuis un fichier une flotte
				if( nbFlottes < NombreMaxFlottes)
				{
					if(flottes[nbFlottes] == NULL) 
						flottes[nbFlottes] = nouvelleFlotte();
					if(charger(argv[i], flottes[nbFlottes]))
						nbFlottes++;

				}
			}
		}
	}
	initSimulateur();
	if(nbFlottes > 1)
	{
		if(tech[2] + tech[1] + tech[0] > 0)
		{
			for(k = 0 ; k < nbFlottes ; k++)
			{
				flottes[k]->techno[0] = tech[0];
				flottes[k]->techno[1] = tech[1];
				flottes[k]->techno[2] = tech[2];
			}
		}
		for(k = 0 ; k < nbFlottes ; k++)
		{
			for(l = k+1 ; l < nbFlottes ; l++)
			{
				afficherFlotte(flottes[k]);
				afficherFlotte(flottes[l]);
				rest.pertes[0][0] = rest.pertes[0][1] = rest.pertes[0][2] = rest.pertes[1][0] = rest.pertes[1][1] = rest.pertes[1][2]= 0; 
				for(i = 0 ; i < tour ; i++)
				{
					simuler(*flottes[k], *flottes[l], res.pertes);
					for(j = 0 ; j < 3 ; j++)
					{
						rest.pertes[0][j] += res.pertes[0][j];
						rest.pertes[1][j] += res.pertes[1][j];
					}
				}
				sum[0] = rest.pertes[0][0]/tour + rest.pertes[0][1]/tour + rest.pertes[0][2]/tour;
				sum[1] = rest.pertes[1][0]/tour + rest.pertes[1][1]/tour + rest.pertes[1][2]/tour;
				printf("%d vs %d\n", k+1, l+1);
				printf("%ld\t%ld\t%ld\n", rest.pertes[0][0]/tour, rest.pertes[0][1]/tour, rest.pertes[0][2]/tour);
				printf("%ld\t%ld\t%ld\n", rest.pertes[1][0]/tour, rest.pertes[1][1]/tour, rest.pertes[1][2]/tour);
				printf("%d gagne avec un ecart de %d (%ld%%)\n", (sum[0] > sum[1]) ? l+1 : k+1,  abs(sum[0] - sum[1]), (abs(sum[0] - sum[1])*100)/(sum[0]+sum[0]));
			}
		}
	}
	else 
	{
		afficherFlotte(&f1);
		afficherFlotte(&f2);
		for(i = 0 ; i < tour ; i++)
		{
			simuler(f1, f2, res.pertes);
			for(j = 0 ; j < 3 ; j++)
			{
				rest.pertes[0][j] += res.pertes[0][j];
				rest.pertes[1][j] += res.pertes[1][j];
			}
		}
		printf("%ld %ld %ld\n%ld %ld %ld", rest.pertes[0][0]/tour, rest.pertes[0][1]/tour, rest.pertes[0][2]/tour, rest.pertes[1][0]/tour, rest.pertes[1][1]/tour, rest.pertes[1][2]/tour);
	}
	libererSimulateur();
	
	for(i = 0 ; i < nbFlottes+1 && i < NombreMaxFlottes ; i++)
		if(flottes[i] != NULL)
			free(flottes[i]);

	return 0;
}