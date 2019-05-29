///////////////////////////////////////////////////////
//
//		Copyright � 1994 Jens Gebhard
//
//      DATEI:	TRITCHLER.CPP (Tritchler.cc)
//
//		ZWECK:	Implementierung des Tritchler-Algorithmus
//
///////////////////////////////////////////////////////

#include "tritchler.h"

///////////////////////////////////////////////////////
//
//	Charakteristische Funktion der Summenverteilung
//	berechnen.
//	-->		psi[][], Q, N1, N
//	<--		phi[]
//
void TritchlerAlgorithmus::rek()
{
	StepIndikator *Show;
	unsigned i,j,k;
	unsigned l;
	if(!Quiet)
		Show=new StepIndikator(50,Q/2);
	for(l=0;l<=Q/2 && !Stop;l++)
	{
		if(!Quiet)
			Show->Step();
		GetAlpha(2*M_PI*l/Q);
		psi[0][0].re=1.0; psi[0][0].im=0.0;
		for(i=1;i<=N;i++)
		{
			psi[0][i].re=1.0;
			psi[0][i].im=0.0;
		}
		for(i=1;i<=N1;i++)
		{
			psi[i][i].re=psi[i-1][i-1].re*Alpha[i].re-psi[i-1][i-1].im*Alpha[i].im;
			psi[i][i].im=psi[i-1][i-1].re*Alpha[i].im+psi[i-1][i-1].im*Alpha[i].re;
		}
		for(k=2;k<=N && !Stop;k++)
			for(j=1;j<k && j<=N1 && !Stop;j++)
			{
				psi[j][k].re=Alpha[k].re*psi[j-1][k-1].re-Alpha[k].im*psi[j-1][k-1].im+psi[j][k-1].re;
				psi[j][k].im=Alpha[k].re*psi[j-1][k-1].im+Alpha[k].im*psi[j-1][k-1].re+psi[j][k-1].im;
			}
		phi[l].re=psi[N1][N].re;
		phi[l].im=psi[N1][N].im;
	}
	if(!Quiet)
		delete Show;
}

///////////////////////////////////////////////////////
//
//	Alpha berechnen
//	-->		theta, fz[], N
//	<--		Alpha
//
void TritchlerAlgorithmus::GetAlpha(double theta)
{
	unsigned i;
	for(i=0;i<N;i++)
	{
		Alpha[i+1].re=cos(theta*fz[i]);
		Alpha[i+1].im=sin(theta*fz[i]);
	}
}

///////////////////////////////////////////////////////
//
//	Q berechnen
//	-->		N1, N, fz[]
//	<--		Q, LogQ
//
void TritchlerAlgorithmus::GetQ()
{
	unsigned i,j;

	j=1u;
	Q=10;

	for(i=0;i<N1;i++)
		Q+=(unsigned)fz[N-1-i];
	for(i=0;j<Q;i++)
		j<<=1;
	Q=j;
	LogQ=i;
}

///////////////////////////////////////////////////////
//
//	Permutationstest durchfuehren
//	-->		nichts
//	<--		FoundLowerValues (Rueckgabewert)
//
double TritchlerAlgorithmus::ExecPermutation()
{
	unsigned i,j;
	double FoundLowerValues=0.0;

	Alpha=new COMPLEX[N+1];

	GetQ();

	phi=new COMPLEX[Q/2+1];
	psi=new COMPLEX*[N1+1];
	MemError=(psi==NULL);

	for(i=0;i<=N1;i++)
	{
		if(!MemError)
			psi[i]=new COMPLEX[N+1];
		MemError=MemError||(psi[i]==NULL);
	}

	if(!MemError && !Stop)
		rek();

	for(i=0;i<=N1;i++)
		if(psi && psi[i])
			delete[] psi[i];
	if(psi)
		delete[] psi;

	if(Alpha)delete[] Alpha;

	if(!MemError && !Stop)
		fft_rueck(LogQ);
	FoundLowerValues=0.0;
	if(!MemError && !Stop)
		for(i=0,j=0;j<fCompare+0.1;i++)
		{
			if(j++>=fCompare+0.1)break;
			FoundLowerValues+=phi[i].re;
			if(j++>=fCompare+0.1)break;
			FoundLowerValues+=phi[i].im;
		}
	if(phi) delete[] phi;
	if(MemError)
		std::cerr<<"Fehler: Kein Speicher!!"<<std::endl<<std::endl;
	return FoundLowerValues;
}

///////////////////////////////////////////////////////
//
//	Meldung ausgeben
//	-->		nichts
//	<--		nichts
//
void TritchlerAlgorithmus::PreProcessMessage() const
{
	PermutationTest::PreProcessMessage();
	if(!Quiet)
		std::cerr<<"Algorithmus:\tTritchler"<<std::endl;
}

///////////////////////////////////////////////////////
//
//	Meldung ausgeben
//	-->		nichts
//	<--		nichts
//
void TritchlerAlgorithmus::PostProcessMessage() const
{
	PermutationTest::PostProcessMessage();
}


