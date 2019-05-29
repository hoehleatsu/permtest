///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	GREEN.H
//
//		ZWECK: 	Deklaration der Klasse GreenAlgorithmus
//
///////////////////////////////////////////////////////

#if !defined(__GREEN_H)
#define __GREEN_H

#include <iostream>
#include "pitman.h"

//////////////////////////////////////////////////////
//
//		Klasse: 		GreenAlgorithmus
//		Basisklasse: 	PermutationTest
//
//		Zweck:			Implementierung des Green-
//						algorithmus
//
class GreenAlgorithmus: public PermutationTest
{
public:
	GreenAlgorithmus():
		PermutationTest()
	{	
		NoOptimization=FALSE;
	}
protected:
	virtual BOOL CanDo();
	double ExecPermutation();
	void Rek(int);
	void RekNoOptimization(int);
	virtual BOOL DoYouKnowTheseOptions(char*);
	virtual void SetOptions(char*);
	virtual void PreProcessMessage() const;
	virtual void PostProcessMessage() const;

private:
	unsigned long FoundLowerValue;
	unsigned long Summe;
	int Level;
	BOOL NoOptimization;
};
#endif	//__GREEN_H


