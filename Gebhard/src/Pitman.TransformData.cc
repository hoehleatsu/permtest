///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	PITMANXT.CPP  (Pitman.TransformData.cc)
//
//		ZWECK:  Daten auf geforderte Anzahl an Dezimalstellen
//				runden; Rangzahlen berechnen.
//
///////////////////////////////////////////////////////

#include "pitman.h"
#include <math.h>

///////////////////////////////////////////////////////
//
//	Daten runden
//	-->		fz[], N, N1, MaxVal
//	<--		fz[]
//
void PermutationTest::CutValues()
{                   				//TransformData() transformiert die
	int i;                          //Arrays z[] und fz[] auf Integer-Format
	double MinVal=fz[0];           //Die Werte werden gegebenenfalls auf
	int MaxValIndex=0;              //log(MaxVal) Stellen Genauigkeit
									//gerundet.

	SetMaxVal();
	if(Invert)
		for(i=0; i<N; i++)
			fz[i]*=-1;
	for(i=1;i<N;i++)
	{
		MinVal=(fz[i]<MinVal) ? fz[i] : MinVal;
		MaxValIndex=(fz[i]>fz[MaxValIndex]) ? i : MaxValIndex;
	}
	for(i=0;i<N;i++)            	//kleinsten Wert von allen Werten sub-
		fz[i]-=MinVal;              	//trahieren
	while(fz[MaxValIndex]<MaxVal && fz[MaxValIndex] != 0.0)
		for(i=0;i<N;i++)
			fz[i]*=10;

	while(fz[MaxValIndex]>=MaxVal*10)	//Werte auf maximale Stellenzahl
		for(i=0;i<N;i++)			//bringen
			fz[i]/=10;


	for(i=0; i<N; i++)
	{
		fz[i] = CutMode==standard ? rint(fz[i]) :
                       (CutMode==fuzzy ? (i<N1 ? ceil(fz[i]) : floor(fz[i])) :
						(i<N1 ? floor(fz[i]) : ceil(fz[i])));
		z[i]=(unsigned long)(fz[i]+0.5);
	}
	while(IsZero())                    	//unn�tige Nullen entfernen
		for (i=0;i<N;i++)
		{
			fz[i]/=10;
			z[i]=(unsigned long)(0.5+fz[i]);
		}
}

///////////////////////////////////////////////////////
//
//	MaxVal berechnen
//	-->		Precision
//	<--		MaxVal
//
void PermutationTest::SetMaxVal()
{
		int i;
		double Help=1.0;
		for(i=1;i<Precision;i++)
			Help*=10.0;
		MaxVal=Help;
}

///////////////////////////////////////////////////////
//
//	gibt es ueberfluessige Nullen?
//	-->		z[], N
//	<--		TRUE, wenn ja, sonst FALSE
//
int PermutationTest::IsZero() const
{
	int i;
	int Zero=1;
	int AllZero=1;
	unsigned long a;
	for(i=0;i<N;i++)
	{
		a=z[i]/10;
		Zero = Zero && (z[i]==a*10);
		AllZero=AllZero && (z[i]==0);
	}
	return(Zero && !AllZero);
}

///////////////////////////////////////////////////////
//
//	Daten auf Rangzahlen transformieren
//	-->		fz[], N
//	<--		fz[]
//
void PermutationTest::MakeRanks()
{
	double *Rank;
	int i,j;
	BOOL HasTies=FALSE;

	Rank=new double[N];
	for(i=0;i<N;i++)
	{
		Rank[i]=0;
		for(j=0;j<N;j++)
		{
			if(fz[j]<fz[i])
				Rank[i]++;
			else if(fz[j]==fz[i] && i!=j)
			{
				Rank[i]+=0.5;
				HasTies=TRUE;
			}
		}
	}
	for(i=0;i<N;i++)
		fz[i]=(HasTies) ? (2*Rank[i]):(Rank[i]);
	delete[] Rank;
}
