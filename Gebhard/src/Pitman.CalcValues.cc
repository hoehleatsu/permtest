///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	PITMANXC.CPP  (Pitman.CalcValues.cc)
//
//		ZWECK:  Anzahl der moeglichen Permutationen
//				bestimmen; Arrays sortieren
//
///////////////////////////////////////////////////////

#include "pitman.h"

///////////////////////////////////////////////////////
//
//	Pruefgroesse und Anzahl der moeglichen Permutationen
//	bestimmen; Arrays sortieren
//	-->		z[], fz[], N1, N
//	<--		Compare, fCompare, PermutationCount, fPermutationCount
//
void PermutationTest::CalcValues()
{
	int i;
	Compare=0,fCompare=0.0;
	for(i=0;i<N1;i++)
	{
		Compare+=z[i];
		fCompare+=fz[i];
	}
	fPermutationCount=1.0;
	for(i=1;i<=N1;i++)
		fPermutationCount*=((double)(N-i+1))/i;
	PermutationCount=(fPermutationCount<0xfffffffful)?(unsigned long)fPermutationCount : 0xfffffffful;
	SortArray();
	fSortArray();
}

///////////////////////////////////////////////////////
//
//	Fakultaet berechnen
//	-->		k
//	<--		k!
//
double PermutationTest::Fak(double k)
{
	double i,j=1;
	for(i=1;i<=k;i++)
		j*=i;
	return(j);
}

///////////////////////////////////////////////////////
//
//	Arrays sortieren
//	-->		z[], fz[], N
//	<--		z[], fz[]
//
void PermutationTest::SortArray()
{
	qsort(z,(size_t)(N),sizeof(z[0]),v_fkt);
}
int v_fkt(const void *a,const void *b)
{
	if(*((unsigned long*)a)>*((unsigned long*)b))return(1);
	return(-1);
}
void PermutationTest::fSortArray()
{
	qsort(fz,(size_t)(N),sizeof(fz[0]),fv_fkt);
}
int fv_fkt(const void *a,const void *b)
{
	if(*((double*)a)>*((double*)b))return(1);
	return(-1);
}
