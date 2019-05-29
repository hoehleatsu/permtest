///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	GREEN.CPP (Green.cc)
//
//		ZWECK: 	Implementierung des Green-Algorithmus
//
///////////////////////////////////////////////////////


#include "green.h"

///////////////////////////////////////////////////////
//
//	Permutationstest durchfuehren
//	-->		nichts
//	<--		FoundLowerValues
//
double GreenAlgorithmus::ExecPermutation()
{
	Level=0;
	Summe=0;
	FoundLowerValue=0;
	if(NoOptimization)
		RekNoOptimization(-1);
	else
		Rek(-1);
	return FoundLowerValue;
}

///////////////////////////////////////////////////////
//
//	optimierte Version des Algorithmus (rekursiv)
//	-->		LastIndex, N1, N2, z[]
//	<--		FoundLowerValues
//
void GreenAlgorithmus::Rek(int LastIndex)
{
	int i;

	if(Stop)return;
	Level++;
	for(i=LastIndex+1;i<Level+N2;i++)
	{
		Summe+=z[i];
		if(Level<N1)
		{
			if(Summe+(N1-Level)*z[i+1]>Compare)
			{
				Summe-=z[i];
				break;
			}
			Rek(i);
		}
		else if(Level==N1 && Summe <= Compare)
			FoundLowerValue++;
		Summe-=z[i];
	}
	Level--;
}

///////////////////////////////////////////////////////
//
//	nicht optimierte Version des Algorithmus (rekursiv)
//	-->		LastIndex, N1, N2, z[]
//	<--		FoundLowerValues
//
void GreenAlgorithmus::RekNoOptimization(int LastIndex)
{
	int i;

	if(Stop)return;
	Level++;
	for(i=LastIndex+1;i<Level+N2;i++)
	{
		Summe+=z[i];
		if(Level<N1)
			RekNoOptimization(i);
		else if(Level==N1 && Summe <= Compare)
			FoundLowerValue++;
		Summe-=z[i];
	}
	Level--;
}

///////////////////////////////////////////////////////
//
//	Optionen auf Gueltigkeit ueberpruefen
//	-->		Options
//	<--		TRUE, fall die Optionen von dieser oder der
//			Basisklasse erkannt werden.
//			Options wird geaendert
//
BOOL GreenAlgorithmus::DoYouKnowTheseOptions(char *Options)
{
	BOOL OK=TRUE;
	for(int i=0;i<strlen(Options);i++)
	{
		switch(Options[i])
		{
			case '#':
				break;
			case 'n':
				Options[i]='#';
				break;
		    case 'o':
			    while(Options[++i]!='}'){;}
			default:
				OK=FALSE;
		}
	}
	return (OK || PermutationTest::DoYouKnowTheseOptions(Options));
}

///////////////////////////////////////////////////////
//
//	Optionen bearbeiten
//	-->		Options
//	<--		Precision, NoOptimization
//
void GreenAlgorithmus::SetOptions(char *Options)
{
	Precision=6;
	for(int i=0;i<strlen(Options);i++)
	{
		if(Options[i]=='o')
		   while(Options[++i]!='}'){;}   
		if(Options[i]=='n')
		NoOptimization=TRUE;
	}
	PermutationTest::SetOptions(Options);
}

///////////////////////////////////////////////////////
//
//	kann der Test durchgefuehrt werden?
//	-->		PermutationCount
//	<--		TRUE, falls moeglich, FALSE sonst
//
BOOL GreenAlgorithmus::CanDo()
{
	BOOL OK;
	if(PermutationCount==0xfffffffful)
	{
		std::cerr<<"FEHLER: Zu viele Daten!"<<std::endl;
		OK=FALSE;
	}
	else
		OK=TRUE;
	return OK && PermutationTest::CanDo();
}

///////////////////////////////////////////////////////
//
//	Meldung ausgeben
//	-->		NoOptimization
//	<--		nichts
//
void GreenAlgorithmus::PreProcessMessage() const
{
	PermutationTest::PreProcessMessage();
	if(!Quiet)
		std::cerr<<"Algorithmus:\tGreen "<<(NoOptimization ? "ohne " : "mit ")<<"Optimierung"<<std::endl;
}

///////////////////////////////////////////////////////
//
//	Meldung ausgeben
//	-->		nichts
//	<--		nichts
//
void GreenAlgorithmus::PostProcessMessage() const
{
	PermutationTest::PostProcessMessage();
}
