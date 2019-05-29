///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	PITMANXO.CPP  (Pitman.OptionHandler.cc)
//
//		ZWECK:  Optionen bearbeiten
//
///////////////////////////////////////////////////////

#include "pitman.h"
#include <string.h>
///////////////////////////////////////////////////////
//
//	ueberpruefen, ob die Optionen von dieser Klasse
//	bearbeitet werden koennen
//	-->		Options
//	<--		TRUE, falls moeglich, sonst FALSE
//
BOOL PermutationTest::DoYouKnowTheseOptions(char *Options)
{
	char c;
	BOOL OK=TRUE;
	for(int i=0;i<strlen(Options);i++)
	{
		switch(Options[i])
		{
		case '#':
		case 't':
		case 'r':
		case 'g':
		case 'f':
		case 's':
		case 'i':	
		case 'q':
			break;
		case 'o':
			if(Options[++i]!='{')
				return FALSE;
			while(strchr("nptf",Options[++i]));
			if(Options[i]=='}')
				break;
			else return FALSE;
		case 'p':
			c=Options[++i];
			if(c>='1' && c<='9')
				break;
		default:
			OK=FALSE;
		}
	}
	return OK;
}

///////////////////////////////////////////////////////
//
//	Optionen, die fuer diese Klasse relevant sind bearbeiten
//	-->		Options
//	<--		Precision, UseRanks, TeXOutput
//
void PermutationTest::SetOptions(char *Options)
{
	for(int i=0;i<strlen(Options);i++)
	{
		switch(Options[i])
		{
		case '#':
			break;
		case 'p':
			Precision=Options[++i]-'0';
			break;
		case 't':
			TeXOutput=TRUE;
			break;
		case 'r':
			UseRanks=TRUE;
			break;
		case 'o':
			OutputStyle=OSNone;
			++i;
			while(Options[++i]!='}')
				switch(Options[i])
				{
				case 'n':
					OutputStyle |= OSSize;
					break;
				case 'p':
					OutputStyle |= OSpValue;
					break;
				case 't':
					OutputStyle |= OSTime;
					break;
				case 'f':
					OutputStyle |= OSFile;
					break;
				}
			break;
		case 'f':
			CutMode=fuzzy;
			break;
		case 's':
			CutMode=sloppy;
			break;
		case 'i':
			Invert=TRUE;
			break;
		case 'q':
			Quiet=TRUE;
			break;
		}
	}
	if(UseRanks)
		Precision=6;
}

