#include <stdio.h>
#include <math.h>
#include "rk4.cpp"//Zmodyfikowana
double lambda=2;
double funkcja_prawa(double t,double y);
double funkcja_prawdziwa(double t0, double y, double t);
double euler(double y0, double t0, double h, double (*fun)(double,double), double t);
double blad(double numerycznie, double analitycznie);
int main()
{
    int a;
    double y0,t0,h,t,fp,eu,rk,bleu,blrk;
    FILE *f;
    printf("podaj wartosc y0\n");
    scanf("%lf",&y0);
    printf("podaj wartosc t0\n");
    scanf("%lf",&t0);
    printf("Wybierz tryb działania\n0-normalny\t1-ulepszony\n");
    scanf("%d",&a);
    switch (a){
        case 0:
            printf("podaj skok h\n");
            scanf("%lf",&h);
            printf("podaj t\n");
            scanf("%lf",&t);
             fp = funkcja_prawdziwa(t0, y0, t);
             eu = euler(y0, t0, h, funkcja_prawa, t);
             rk = rk4(t0, y0, h, funkcja_prawa,t);
             bleu = blad(eu, fp);
             blrk = blad(rk,fp);
            printf("fp=%lf\neu=%lf\tbleu=%lf\nrk=%lf\tblrk=%lf\n", fp, eu, bleu,rk,blrk);

            break;
        case 1:
            printf("Podaj chwile tk\n");
            scanf("%lf",&t);
            fp = funkcja_prawdziwa(t0, y0, t);
            f=fopen("dane.txt","w");
            fprintf(f,"N\t\th\t\tbleu\t\tblrk\n");
            for (int i = 0; i < 10; ++i) {
                double N = pow(2,i);
                h=(t-t0)/N;
                eu = euler(y0, t0, h, funkcja_prawa, t);
                rk = rk4(t0, y0, h, funkcja_prawa,t);
                bleu = blad(eu, fp);
                blrk = blad(rk,fp);
                printf("N=%lf\th=%lf\tbleu=%lf\tblrk=%lf\n",N,h,bleu,blrk);
                fprintf(f,"%lf\t%lf\t%lf\t%lf\n",N,h,bleu,blrk);
            }
            fclose(f);
            break;

    }
    return 0;
}
double funkcja_prawa(double t, double y)
{
    return lambda*y;
}
double funkcja_prawdziwa(double t0, double y, double t)
{
    double power = lambda*(t-t0);
    return y*exp(power);
}
double euler(double y0, double t0, double h, double (*fun)(double,double), double t)
{
    double t1,y1;
    double q = fabs((t-t0)/h);
    for (int i = 0; i <q; ++i) {
        t1=t0+h;
        y1=y0+h*fun(t0,y0);
        t0=t1;
        y0=y1;
    }
    return y1;
}
double blad(double numerycznie, double analitycznie)
{
    return fabs(analitycznie - numerycznie) / fabs(analitycznie);
}

