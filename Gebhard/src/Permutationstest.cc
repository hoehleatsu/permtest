///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	PERMUTAT.CPP  (Permutationtest.cc)
//
//		ZWECK:  Elementefunktionen von PermutationTestApp
//
///////////////////////////////////////////////////////

#include "Permutationstest.h"

extern char *today;

///////////////////////////////////////////////////////
//
//	Der Konstruktor initialisiert einige Daten und
//	ueberprueft die Gueltigkeit der Programmparameter
//	-->		argc, argv (wie in main)
//	<--		OptionsOK
//
PermutationTestApp::PermutationTestApp(int argc, char **argv)
{
	ArgCount=argc;
	Args=argv;
	Options[0]='\0';
	UnknownOptions[0]='\0';
	NrOfDataFiles=0;

	PrintCopyright();

	DataFiles=new char*[argc];
	SetLocalOptions();
}

///////////////////////////////////////////////////////
//
//	Falls die Programmparameter in Ordnung sind, wird
//	der Test fuer die angegebenen Dateien durchgefuehrt
//	-->		OptionsOK, DataFiles[], NrOfDataFiles, Options
//	<--		nichts
//
void PermutationTestApp::Run()
{
	PreProcessMessage();

	if(Algorithmus==Tritchler)
		Test=new TritchlerAlgorithmus();
	else
		Test=new GreenAlgorithmus();

	if(!Test)
	{
		std::cerr<<std::endl<<"Fehler: Kein Arbeitsspeicher!"<<std::endl;
		return;
	}

	if(!Test->HandleOptions(Options,UnknownOptions) || NrOfDataFiles==0)
	{
		Info();
		delete Test;
		return;
	}
	
	for(int i=0;i<NrOfDataFiles;i++)
	{
		if(!(Test->run(DataFiles[i])))
			break;
	}
	delete Test;
	PostProcessMessage();
}

///////////////////////////////////////////////////////
//
//	Optionen, die fuer diese Klasse relevant sind bearbeiten
//	-->		ArgCount, Args
//	<--		Options, UnknownOptions, TeXOutput, Algorithmus
//
void PermutationTestApp::SetLocalOptions()
{	int i;
	Algorithmus=Tritchler;
	TeXOutput=FALSE;
	for(i=1;i<ArgCount;i++)
	{
		if(Args[i][0]!='-')	//	Parameter ist eine Dateiangabe
			DataFiles[NrOfDataFiles++]=Args[i];
		else			   	//	Parameter ist eine oder meherere Option(en)
			strcat(Options,&Args[i][1]);
	}
	for(i=0;i<strlen(Options);i++)
	{
		switch(Options[i])
		{
		case 'g':
		case 'G':
			Algorithmus=Green;
			UnknownOptions[i]='#';
			break;
		case 't':
		case 'T':
			TeXOutput=TRUE;
			UnknownOptions[i]='#';
			break;
		case '{':
			do
			{
				UnknownOptions[i]=Options[i];
				++i;
			}while(Options[i]!='}');
			UnknownOptions[i]='}';
			break;
		default:
			UnknownOptions[i]=Options[i];
			break;
		}
	}
	UnknownOptions[i]='\0';
}

///////////////////////////////////////////////////////
//
//	Meldung ausgeben
//	-->		TeXOutput
//	<--		nichts
//
void PermutationTestApp::PreProcessMessage() const
{
	if(TeXOutput)
	{
		std::cout<<"\\begin{center}"<<std::endl;
		std::cout<<"\\begin{tabular}{|c|c|c|}"<<std::endl;
		std::cout<<"\\hline"<<std::endl;
		std::cout<<"Stichprobenumfang&p-Wert&Dauer in Sek.\\\\"<<std::endl;
		std::cout<<"\\hline\\hline"<<std::endl;
	}
}

///////////////////////////////////////////////////////
//
//	Meldung ausgeben
//	-->		TeXOutput
//	<--		nichts
//
void PermutationTestApp::PostProcessMessage() const
{
	if(TeXOutput)
	{
		std::cout<<"\\end{tabular}"<<std::endl;
		std::cout<<"\\end{center}"<<std::endl;
	}
}

///////////////////////////////////////////////////////
//
//	Hilfetext anzeigen
//	-->		nichts
//	<--		nichts
//
void PermutationTestApp::Info() const
{
	std::cerr<<"\n\npermtest [-pxgnrifso{nptf}] file(s)\n\n";
	std::cerr<<"\t-px: Auf x Dezimalstellen runden\n";
	std::cerr<<"\t-g:  Green-Algorithmus verwenden\n";
	std::cerr<<"\t-n:  Keine Optimierung beim Green-Algorithmus\n";
	std::cerr<<"\t-r:  Rangtest durchfuehren\n";
	std::cerr<<"\t-i:  Datensaetze vertauschen\n";
	std::cerr<<"\t-f:  Vorsichtig runden\n";
	std::cerr<<"\t-s:  Nur zu Testzwecken!!!\n";
	std::cerr<<"\t-o:  Ausgabeformat festlegen\n\n\n";
}

void PermutationTestApp::PrintCopyright() const
{
	std::cerr<<"\n\n********* Permutationstest, Copyright (c) 1993, 94, 95 by Jens Gebhard ********\n\n";
#ifdef BETA_VER
	std::cerr<<"Achtung:    Dies ist eine Testversion. Fehler bzw. falsche"<<std::endl;
	std::cerr<<"            Resultate koennen daher nicht ausgeschlossen werden!"<<std::endl;
	std::cerr<<"Erzeugt am: "<<today<<std::endl<<std::endl; 
#endif
}
