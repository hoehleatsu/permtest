#include <stdlib.h>
#include <math.h>
#include "tritchler.h"



/**************************************************************************/
/*                       FAST FOURIER TRANSFORM                           */
/*                                                                        */
/*    Algorithmus: nach Cooley-Tukey                                      */
/*                                                                        */
/*    Input:   COMPLEX huge *phi   :  Zeiger auf die Daten                */
/*             const unsigned NU   :  Zweierlogarithmus der Datenanzahl   */
/*             const unsigned Hin  : 1 = Hintrans  exp( -i*2*pi*n*k/N )   */
/*                                   0 = R�cktrans exp( +i*2*pi*n*k/N )   */
/*                                                                        */
/*    Output:  phi[].re wird vorlaeufig mit dem Realteil der              */
/*             Ruecktransformierten gefuellt.                             */
/*                                                                        */
/*    Autor: Michael Termathe                                             */
/*    Anpassung an Tritchler-Algorithmus von Jens Gebhard                 */
/*    Datum: Jan. '93                                                     */
/*                                                                        */
/**************************************************************************/

void TritchlerAlgorithmus::fft_rueck(unsigned NU)
{
/* ---------------------------------------------------------------------
	Es wird ausgenutzt, dass der Imaginaerteil der Ruecktransformierten
	Null ist. Daher kann das N halbiert werden. Zum Gelingen dieses Tricks
	muessen die Daten allerdings vorher noch aufbereitet werden (s.u.)

	Das Datenarray phi[].re -.im braucht so nur bis k = N/2 gef�llt sein
	phi[k].re,phi[k].im:  0 <= k <= N/2 !!!
-------------------------------------------------------------------------*/
	unsigned i,k,l;

	unsigned n2,nu1,p,kn;
	double treal, timag, c,s, xrm, xip;

	const unsigned Nu = NU-1;	/* !!! Reihenfolge der Deklarationen beachten !!!! */
	const unsigned N  = 1u<<Nu;  	// !!!  1<<Nu liefert falsches Ergebnis falls
								// !!!  Nu >= 16. Daher 1ul
	const double M_PI_N		=M_PI/N;

/* ------------------------------------------------------------------*/


	n2 = N >> 1;
	nu1 = Nu-1;

	phi[n2].re*=2.0;
	phi[n2].im*=2.0;
	for(i=0;i<n2 && !Stop;i++)
	{
		c=cos(i*M_PI_N);
		s=sin(i*M_PI_N);
		xrm = phi[i].re - phi[N-i].re;
		xip = phi[i].im + phi[N-i].im;
		phi[i].re = -c*xip + s*xrm + phi[i].re + phi[N-i].re ;
		phi[i].im =  c*xrm + s*xip + phi[i].im - phi[N-i].im ;

		phi[N-i].re=phi[i].re+2*(c*xip-s*xrm);
		phi[N-i].im=-phi[i].im+2*(c*xrm+s*xip);
	}


	for(k=0; k<N && !Stop; k++) /* Datensaetze nach den Bit-Reverse Algorithmus vertauschen */
	{
		i = bitrev(k, Nu);
		if( i>k )
		{
			treal = phi[k].re;
			timag = phi[k].im;
			phi[k].re = phi[i].re;
			phi[k].im = phi[i].im;
			phi[i].re = treal;
			phi[i].im = timag;

		}
	}

	/*******            Start der eigentlichen FFT                *****/
	n2=1;
	nu1 = Nu -1;
	k=0;
	for(l=1; l<=Nu && !Stop; l++)
	{
		do
		{
			for(i=1; i<= n2; i++)
			{
				p = (k<<nu1) & (N-1);	/* hier gilt stets: p < N/2 ! */
				c = cos(p*2*M_PI_N);
				s = sin(p*2*M_PI_N);

				kn = k + n2;
				treal = phi[kn].re*c + phi[kn].im*s;
				timag = phi[kn].im*c - phi[kn].re*s;
				phi[kn].re = phi[k].re - treal;
				phi[kn].im = phi[k].im - timag;
				phi[k].re += treal;
				phi[k].im += timag;
				k++;
			}
			k += n2;

		} while ( k<N && !Stop );

		k=0;
		nu1--;
		n2 <<= 1;
	}	/* naechstes l */


	{  /***************			 Daten ins Zielarray schreiben *******/
		double _2Ndouble = 2.0*N;
		for(k=0;k<N;k++)
		{
			phi[k].re/=_2Ndouble;
			phi[k].im/=_2Ndouble;
		}
	}
}
/****************************************************************/


unsigned TritchlerAlgorithmus::bitrev(unsigned wert, unsigned Nu)	/* dreht die unteren Nu Bits von wert um */
{
	unsigned i,k,j2;

	k=0;
	for(i=1; i<=Nu; i++)
	{
		 j2 = wert>>1;
		 k = k*2 + wert-2*j2;
		 wert =j2;
	}
	return k;
}
/****************************************************************/

