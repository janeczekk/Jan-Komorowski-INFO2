#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rk4.cpp"
void rhs_fun(double t, double *X,double *F);
int n =3;
double g = 9.81;
double l = 1.0;
double m = 10;
double s = 1;
double c = 0.9;
double e0 = 0;
double v0= 3;
double ro= 1.2;


int main()
{
    FILE*f;
    f=fopen("wartosci.txt","w");
    double t,tk,h,a0,w0;
    double *ALFA,*ALFA1;
    ALFA=(double*)malloc(n * sizeof(double));
    ALFA1=(double*)malloc(n * sizeof(double));
    printf("Podaj a0\n");
    scanf("%lf",&a0);
    printf("Podaj w0\n");
    scanf("%lf",&w0);
    printf("Podaj h\n");
    scanf("%lf",&h);
    printf("Podaj tk\n");
    scanf("%lf",&tk);
    ALFA[0]= a0;
    ALFA[1]= w0;
    ALFA[2]= e0;
    double Emech;
    for(t=0;t<=tk; t = t+h)
    {

        vrk4(t, ALFA, h, n, rhs_fun, ALFA1);
        fprintf(f, "%lf\t%lf\t%lf\n",t,ALFA[0], ALFA[1]);
        ALFA[0] = ALFA1[0];
        ALFA[1] = ALFA1[1];
        ALFA[2] = ALFA[2];
        Emech= 1/2m*pow(ALFA[1])-m*ALFA[0]*g;
    }
    return 0;
}


void rhs_fun(double t, double *X,double *F)

{
    F[0] = t*X[1];
    F[1] = (-g*sin(X[0])+v0*sin(t))/l;
    F[2]= (g-ro/2*(g*g+v0*sin(t)*v0*sin(t))*s*c)/m*l;
}
