///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	PITMAN.CPP (Pitman.cc)
//
//		ZWECK:  Implementierung der Basisfunktionalitaet
//				der Klasse Permutationtest
//
///////////////////////////////////////////////////////

#include "pitman.h"
#include <signal.h>

///////////////////////////////////////////////////////
//
//	Der Konstruktor von Permutationtest
//	
PermutationTest::PermutationTest()
{
	Precision=3;
	UseRanks=FALSE;
	TeXOutput=FALSE;
	Invert=FALSE;
	OutputStyle=OSSize|OSpValue|OSTime;
	CutMode=standard;
	Quiet=FALSE;
	Stop=FALSE;
	z=NULL;
	fz=NULL;
	OptionsOK=TRUE;
}

BOOL PermutationTest::HandleOptions(char *Options, char *UnknownOptions)
{
	OptionsOK=DoYouKnowTheseOptions(UnknownOptions);
	if(!OptionsOK)
		Stop=TRUE;
	else
		SetOptions(Options);
	return OptionsOK;
}

///////////////////////////////////////////////////////
//
//	Diese Elementefunktion erledigt alle Arbeiten:
//      0)  Dateinamen ermitteln
//		1)	Daten einlesen
//		2)	Daten runden
//		3)	diverse Initialisierungsaufgaben
//		4)	Permutationstest durchfuehren
//		5)	Ergebnisse ausgeben
//	-->		NoFile
//	<--		FoundLowerValues
//
BOOL PermutationTest::run(char *File)
{
	if(Stop)
		return FALSE;
	strcpy(FileName,File);
	signal(SIGINT, SIG_IGN);
	ReadData();
	if(Stop)
	{
		FreeData();
		return FALSE;
	}
	TransformData();
	CalcValues();
	if(CanDo())
	{
		PreProcessMessage();
		Time.start();
		signal(SIGINT,IntHandler);
		FoundLowerValues=ExecPermutation();
		signal(SIGINT,SIG_IGN);
		Time.stop();
		TimeDiff=Time.time();
		if(Stop)
		{
			FreeData();
			return FALSE;
		}
		DisplayResult();
		PostProcessMessage();
	}
	FreeData();
	return !Stop;
}

///////////////////////////////////////////////////////
//
//	Aktionen:
//		1)	Anzahl der Daten (N, N1, N2) bestimmen
//		2)  Daten einlesen
//	-->		NoFile
//	<--		nichts
//
void PermutationTest::ReadData()
{
	if(NoFile)
		return;
	GetCount();
	GetData();
}

///////////////////////////////////////////////////////
//
//	Daten runden, auf Raenge transformieren
//	-->		NoFile, UseRanks
//	<--		nichts
//
void PermutationTest::TransformData()
{
	if(NoFile)
		return;
	if(UseRanks)
		MakeRanks();
	CutValues();
}

///////////////////////////////////////////////////////
//
//	Kann der Test durchgefuehrt werden?
//	-->		Stop, N1, N2
//	<--		TRUE, falls moeglich, sonst FALSE
//
BOOL PermutationTest::CanDo()
{
	return (!Stop && N1>0 && N2>0);
}

///////////////////////////////////////////////////////
//
//	Ergebnisse anzeigen
//	-->		FoundLowerValues, fPermutationCount, TeXOutput
//	<--		nichts
//
void PermutationTest::DisplayResult() const
{
	if(NoFile)
		return;
	char oldfill;
	int oldwd;


	if(!TeXOutput && !Quiet)
	{
	  std::cerr<<std::endl;
	  if(OutputStyle & OSSize) std::cerr<<"N1+N2\t";
	  if(OutputStyle & OSpValue) std::cerr<<"p-Wert\t";
	  if(OutputStyle & OSTime) std::cerr<<"Dauer [s]\t";
	  if(OutputStyle & OSFile) std::cerr<<"Datei\t";
	  std::cerr<<std::endl;
	}
	
	if(OutputStyle & OSSize)
	  std::cout<<N<<(TeXOutput ? "&" : "\t");
	if(OutputStyle & OSpValue)
	  std::cout<<FoundLowerValues/fPermutationCount<<(TeXOutput ? "&" : "\t");
	if(OutputStyle & OSTime)
	{	
	  std::cout<<Time.time()<<'.';
	  oldfill=std::cout.fill('0');
	  oldwd=std::cout.width(3);
	  std::cout<<Time.millitime()<<(TeXOutput ? "&" : "\t");
	  std::cout.fill(oldfill);
	  std::cout.width(oldwd);
	}
	if(OutputStyle & OSFile)
	  std::cout<<FileName<<(TeXOutput ? "&" : "\t");
	std::cout<<(TeXOutput ? "\\\\\n\\hline\n" : "\n");
}

///////////////////////////////////////////////////////
//
//	Meldung ausgeben (vorher)
//	-->		UseRanks, Precision, FileName
//	<--		nichts
//
void PermutationTest::PreProcessMessage() const
{
	if(Quiet) return;
	std::cerr<<"Datei:\t\t"<<FileName<<std::endl;
	if(UseRanks)
	  std::cerr<<"Rangtest"<<std::endl;
	else
	  std::cerr<<"Rundung:\t"<<Precision<<" Dezimal-Stellen"<<std::endl;
}

///////////////////////////////////////////////////////
//
//	Meldung ausgeben (nachher)
//	-->		nichts
//	<--		nichts
//
void PermutationTest::PostProcessMessage() const
{
	if(!Quiet)
		std::cerr<<"-----------------------------------------------------"<<std::endl;
}

///////////////////////////////////////////////////////
//
//	Signalbearbeitung
//	-->		nichts
//	<--		Stop
//
void PermutationTest::IntHandler(int)
{
	std::cerr<<"\n\n*****  Programmabbruch  *****\n\n";
	Stop=TRUE;
}

volatile BOOL PermutationTest::Stop=FALSE;
