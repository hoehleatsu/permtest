///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	TRITCHLER.H
//
//		ZWECK:  Deklaration der Klasse TritchlerAlgorithmus
//
///////////////////////////////////////////////////////

#if !defined(__TRIT_H)
#define __TRIT_H

#include <math.h>
/* 
   hoehle: already defined in math.h
   #define	M_PI	3.14159265358979323846
*/
#include <stdio.h>
#include "pitman.h"
#include "global.h"

struct COMPLEX
{
	double re;
	double im;
};

//////////////////////////////////////////////////////
//
//		Klasse: 		TritchlerAlgorithmus
//		Basisklasse: 	PermutationTest
//
//		Zweck:			Implementierung des Tritchler-
//						algorithmus
//
class TritchlerAlgorithmus: public PermutationTest
{
	unsigned Q;      // maximale Summe von N1 Werten (bzw. die naechst groessere Zweierpotenz)
	unsigned LogQ;   // Logarithmus zur Basis 2 von Q
	COMPLEX **psi;   // temporaeres Array
	COMPLEX *Alpha;  // exp(i*theta*z[j+k])
	COMPLEX *phi;    // siehe Paper
	int MemError;    // Fehler bei Speicherreservierung

public:
	TritchlerAlgorithmus():
		PermutationTest(){}
	~TritchlerAlgorithmus(){}
protected:
	virtual double ExecPermutation();
	virtual BOOL DoYouKnowTheseOptions(char *Options)
	{
		return PermutationTest::DoYouKnowTheseOptions(Options);
	}
	virtual void SetOptions(char *Options)
	{
		Precision=3; // Standardpraezision
		PermutationTest::SetOptions(Options);
	}
	virtual void PreProcessMessage() const;
	virtual void PostProcessMessage() const;
private:
	void fft_rueck(unsigned NU);
	unsigned bitrev(unsigned wert,unsigned Nu);
	void GetAlpha(double);
	void rek();
	void GetQ();
};
#endif	//__TRIT_H












































