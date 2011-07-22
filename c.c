#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>


#define N 2 //Dimensions
#define x0 0.0
#define x1 3.0
#define dt 0.01

double *solution[N] = {NULL};

void deriv1 (double x, double y[], double dydt[])
{

	dydt[0] = 1 - y[1];
	dydt[1] = y[0] - x;

}

/* numerical recipies */
void rk4(double y[], double dydx[], int n, double x, double h, double yout[], void (*derivs)(double, double [], double []))
{
	int i;
	double xh, hh, h6;
        double dym[n], dyt[n], yt[n];

	hh = h*0.5;
	h6 = h/6.0;
	xh = x+hh;

	for (i=0;i<n;i++) yt[i] = y[i] + hh*dydx[i];
	(*derivs)(xh,yt,dyt);

	for (i=0;i<n;i++) yt[i] = y[i] + hh*dyt[i];
	(*derivs)(xh,yt,dym);

	for (i=0;i<n;i++) {
		yt[i] = y[i] + h*dym[i];
		dym[i] = dym[i] + dyt[i];
	}

	(*derivs)(x+h,yt,dyt);

	for (i=0;i<n;i++) 
		yout[i] =  y[i] + h6*(dydx[i] + dyt[i] + 2.*dym[i]);
}

/* numerical recipies */
void rkdump(double vstart[], int nvar, double t1, double t2, int nstep, void (*derivs)(double, double[], double[]))
{
	int i,k;
	double x,h;
	double v[nvar], vout[nvar], dv[nvar];

	for (i=0;i<nvar;i++) {
		v[i] = vstart[i];
	}
	x = t1;
	h = (t2-t1)/nstep;
	for (k=0;k<nstep;k++) {
		(*derivs)(x,v,dv);
		rk4(v,dv,nvar,x,h,vout,derivs);
		if ((double)(x+h) == x) printf("Step size too small in routine rkdump\n");
		x += h;
		for (i=0;i<nvar;i++) {
			v[i] = vout[i];
		}
		solution[0][k] = v[0];
		solution[1][k] = v[1];
	}
}


int main (void)
{
	int i;
	int steps; // solution steps
	double starting_v[N]; // Arxiko vector gia tin methodo.

	steps = (x1-x0)/dt;

	for (i=0;i<N;i++)
		solution[i] = (double *)realloc((char *)solution[i], sizeof(double)*steps);

	/* -- arxikes times -- */
	starting_v[0] = 1.0;
	starting_v[1] = 0.0;

	rkdump(starting_v, N, x0, x1, steps, deriv1);

	for (i=0;i<steps;i++) {
		printf("%4f %4f %4f\n", (i+1)*dt, solution[0][i], solution[1][i]);
	}

	return 0;
}
