/*

 DownDyadLo.C	Sample .MEX file corresponding to DownDyadLo.m
		Dyadic Downsampling Transform

  The calling syntax is:

			wc = DownDyadLo(signal,lpf)


  David Donoho
  Copyright (c) 1993  David Donoho
  All Rights Reserved

*/

#include <math.h>
#include "mex.h"
#include "wavelab.h"

#define DOUBLE		double
#define INT			int

/* Input Arguments */

#define	 Sig_IN	prhs[0]
#define  LPF_IN prhs[1]

/* Output Arguments */

#define	LP_OUT	plhs[0]

#define	max(A, B)	((A) > (B) ? (A) : (B))
#define	min(A, B)	((A) < (B) ? (A) : (B))


INT nlhs, nrhs;
mxArray *plhs[], *prhs[];

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	DOUBLE	*lpp, *lpf, *sig;
	unsigned int	m,n,nn,mm;
	int nr,nc,J,kk,lenfil;

	/* Check for proper number of arguments */

	if (nrhs != 2) {
		mexErrMsgTxt("DownDyadLo requires two input arguments.");
	} else if (nlhs != 1) {
		mexErrMsgTxt("DownDyadLo requires one output argument.");
	}


	/* Check the dimensions of signal.  signal can be n X 1 or 1 X n. */

	m = mxGetM(Sig_IN);
	n = mxGetN(Sig_IN);
	if(m == 1){
		nr = (int) n;
		nc = 1;
		nn = n/2;
		mm = 1;
	} else {
		nr = (int) m;
		nc = (int) n;
		nn = 1;
		mm = m/2;
	}

	J = 0;
	for( kk = 1; kk < nr;  kk *= 2 )  
		 J ++;
	if(  kk  !=  nr){
		mexErrMsgTxt("DownDyadLo requires dyadic length");
	}


	/* Create a matrix for the return argument */
	LP_OUT = mxCreateDoubleMatrix(mm,nn, mxREAL);


	/* Assign pointers to the various parameters */

	lpp = mxGetPr(LP_OUT);

	sig = mxGetPr(Sig_IN);
	lpf = mxGetPr(LPF_IN);
    lenfil = (int) (mxGetM(LPF_IN) * mxGetN(LPF_IN));   /* should check this */

	/* Do the actual computations in a subroutine */

	downlo(sig,nr,lpf,lenfil,lpp);
}


#include "downlo.c"
