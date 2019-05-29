///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	PITMAN.H
//
//		ZWECK:  Deklaration der Klasse PermutationTest
//
///////////////////////////////////////////////////////

#if !defined(__PITMAN_H)
#define __PITMAN_H

#include <stdlib.h>
#include <string.h>
#include <strstream>
#include <fstream>
#include <iostream>

#include "timer.h"
#include "global.h"

#define MAXPATH 1024

int v_fkt(const void *,const void *);
int fv_fkt(const void *,const void *);

//////////////////////////////////////////////////////
//
//		Klasse: 		PermutationTest
//		Basisklasse: 	keine
//
//		Zweck:			Die Klasse PermutationTest ist
//						abstrakt und dient als Basisklasse
//						fuer weitere Klassen, die spezielle
//						Algorithmen implementieren. Ein
//						einfaches Beispiel hierfuer ist die
//						Klasse GreenAlgorithmus.
//
class PermutationTest
{
public:
	static volatile BOOL Stop; 
//   Speicherplatz wird in pitman.h reserviert
protected:
	unsigned N1;
	unsigned N2;
	unsigned N;                // Stichprobenumfang
	unsigned long *z;          // Daten im Integer-Format
	double *fz;                // Daten im Fliesskomma-Format
	unsigned long Compare;     // Summe der ersten N1 Werte (Integer)
	double fCompare;           // Summe der ersten N1 Werte (Fliesskomma)
	double fPermutationCount;  // Anzahl aller Permutationen (N ueber N1)
	unsigned long PermutationCount; // dito aber Integer
	double TimeDiff;           // Dauer der Berechnung in Sekunden
	int Precision;             // Anzahl signifikanter Dezimalstellen
	enum tagOutputStyle{OSNone=0, OSSize=1, OSpValue=2, OSTime=4, OSFile=8};
	int OutputStyle;
	BOOL Quiet;
private:
	BOOL TeXOutput;            // TeX-Tabelle erzeugen
	BOOL OptionsOK;            // alle Optionen in Ordnung
	BOOL Invert;
	double FoundLowerValues;   // Anzahl der Permut., die zu kleinen Summen fuehren
	Timer Time;                // die Stopuhr (ziemlich primitiv!!!)
	double StartTime,EndTime;
	char FileName[MAXPATH];
	enum tagCutMode{standard, fuzzy, sloppy} CutMode;	
	BOOL UseRanks;             // Messwerte auf Raenge reduzieren
	BOOL NoFile;
	double MaxVal;             // 10^Precision
public:
	PermutationTest();
	virtual ~PermutationTest(){};
		
	BOOL IllegalOption()
	{
		return !OptionsOK;
	}
	BOOL run(char *File);
	BOOL HandleOptions(char*, char*);

protected:
	virtual void SetOptions(char*);
	virtual BOOL DoYouKnowTheseOptions(char*);
	virtual double ExecPermutation()=0;
	virtual BOOL CanDo();
	virtual void DisplayResult() const;
	virtual void PreProcessMessage() const;
	virtual void PostProcessMessage() const;

private:
	void SetMaxVal();

	void ReadData();
	void GetCount();
	void GetData();
	void FreeData(){
		if(z)
			delete[] z;
		if(fz)
			delete[] fz;
		z=NULL;
		fz=NULL;
	};

	void TransformData();
	void CutValues();
	void MakeRanks();

	void CalcValues();
	double Fak(double);
	void SortArray();
	void fSortArray();
	int IsZero() const;
	static void IntHandler(int);
};

class StepIndikator
{
	unsigned i,Steps;
	unsigned long Range;
public:
	StepIndikator(unsigned theSteps, unsigned long upper, unsigned long lower=0)
	{
		Steps=theSteps;
		Range=upper-lower;
		i=0;
	}
	~StepIndikator()
	{
	  std::cerr<<std::endl;
	}
	void Step()
	{
		if(++i*Steps>Range)
		{
			i=0;
			std::cerr<<'.';
		}
	}
};

#endif	//__PITMAN_H


