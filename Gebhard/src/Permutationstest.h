///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	PERMUTAT.H (Permutationtest.h
//
//		ZWECK:  Deklaration der Klasse PermutationTestApp
//
///////////////////////////////////////////////////////

#include "global.h"
#include "pitman.h"
#include "tritchler.h"
#include "green.h"

//////////////////////////////////////////////////////
//
//		Klasse: 		PermutationTestApp
//		Basisklasse: 	keine
//
//		Zweck:			Die Klasse PermutationTestApp
//						ist das Anwendungsobjekt. Normaler-
//						weise wird hiervon nur eine Instanz
//						waehrend des Programmablaufs er-
//						zeugt. PermutationTestApp erzeugt
//						ihrerseits fuer jede angegebene Datei
//						ein ein Objekt vom Typ PermutationTest
//						(genauer gesagt ein Objekt, dass von
//						PermutationTest abgeleitet ist und
//						den jeweiligen Algorithmus implementiert)
//
class PermutationTestApp
{
private:
	int ArgCount;
	char **Args;

	char Options[512];
	char UnknownOptions[512];

	int NrOfDataFiles;

	char **DataFiles;
	PermutationTest *Test;

	BOOL TeXOutput;
	enum tagAlgorithmus{Green, Tritchler}Algorithmus;

	void SetLocalOptions();
	void PrintCopyright() const;
	void PreProcessMessage() const;
	void PostProcessMessage() const;
	void Info() const;

public:
	PermutationTestApp(int argc, char **argv);
	~PermutationTestApp()
	{
		delete[] DataFiles;
	};
	void Run();
};
