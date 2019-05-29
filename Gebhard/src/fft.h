#ifndef __FFT_H
	#define __FFT_H
typedef unsigned int uint;
typedef unsigned long ulong;

#ifdef LONG_DOUBLE
typedef long double dprec;  				/* Praezision der Transfo-Daten */
#else
typedef double dprec;
#endif
typedef ulong iprec;                /* Praezision der Integerwerte */

typedef struct
{
	dprec re;
	dprec im;
} COMPLEX;


#endif
