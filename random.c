#include "random.h"
#include "stdlib.h"
#include "time.h"

void randInit()
{
	srand(time(NULL));
}
int randInt(int N)
{
	return rand()%N;
}
int bern(int num, int den)
{
	return rand()%(den*100) < num*100;
}
int bernI(int num, int den)
{
	return bern(den-num, den);
}