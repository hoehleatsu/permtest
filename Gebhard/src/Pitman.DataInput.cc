///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	PITMANXD.CPP  (Pitman.DataInput.cc)
//
//		ZWECK:  Daten einlesen
//
///////////////////////////////////////////////////////

#include "pitman.h"

///////////////////////////////////////////////////////
//
//	Anzahl der Werte ermitteln
//	-->		FileName
//	<--		N1, N2, N
//
void PermutationTest::GetCount()
{
	char c, c2=' ';

	BOOL first=TRUE;
	BOOL ende=FALSE;

	N1=N2=0;
	std::ifstream File(FileName);
	if(!File)
	{
		std::cerr<<"\nFehler: "<<FileName<<" konnte nicht geoeffnet werden\n";
		Stop=TRUE;
		return;
	}
	while(!ende && File.get(c))
	{
		switch(c)
		{
			case ';':
			case '\t':
			case ' ':
				if(c2!=';' && c2!='\t' && c2!=' ')
					first ? N1++ : N2++;
				break;
			case '\n':
				if(first && c2!=';' && c2!='\t' && c2!=' ')
					N1++;
				if(!first && c2!=';' && c2!='\t' && c2!=' ')
				{
					N2++;
					ende=TRUE;
				}
				first=FALSE;
				break;
		}
		c2=c;
	}
	N=N1+N2;
}

///////////////////////////////////////////////////////
//
//	Daten einlesen
//	-->		FileName, N, N1
//	<--		fz, fz[], z, z[];
//
void PermutationTest::GetData()
{
	int i;
	char c;

	if(Stop)
		return;
	z=new unsigned long[N+1];
	fz=new double[N+1];
	if(!z || !fz)
	{
		std::cerr<<std::endl<<"Fehler: Kein Arbeitsspeicher!"<<std::endl;
		Stop=TRUE;
		return;
	}

	std::ifstream File(FileName);
	if(!File)
	{
		std::cerr<<"\nFehler: "<<FileName<<" konnte nicht geoeffnet werden\n";
		Stop=TRUE;
		return;
	}
	for(i=0;i<N1;i++)
	{
		File>>fz[i];
		File.get(c);
	}
	if(c!='\n')
		File.get(c);
	File>>fz[N1];
	for(i=N1+1;i<N;i++)
	{
		File.get(c);
		File>>fz[i];
	}
}
