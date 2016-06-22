//
//  main.c
//  integrate
//
//  Created by Дмитрий on 15.06.16.
//  Copyright © 2016 Дмитрий. All rights reserved.
//

#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double integral_pram(function f, double a, double b, unsigned step_count)
{
    double S=.0;
    if (0 == step_count) return S;
    const double h=(b-a)/(1.0*step_count);
    for(int i=0;i<step_count-1;i++)
    {
        double x=a+i*h;
        S=S+f(x);
    }
    S=h*S;
    return S;
}

double integral_trap(function f, double a, double b, unsigned step_count)
{
    double sum = .0;
    if (0 == step_count) return sum;
    
    const double step = (b - a)/(1.0*step_count);
    for (int i = 1;i<step_count;++i) {
        sum += f (a + i * step);
    }
    sum += (f(a) + f(b)) / 2;
    sum *= step;
    return sum;
}

double integral_simp(function f, double a, double b, unsigned step_count)
{
    double sum,x0,x1;
    if (0 == step_count) return sum;
    const double h = (b - a)/(1.0*step_count);
    sum = 0;
    x0 = a;
    x1 = a + h;
    
    for (int i=0; i<=step_count-1; i++) {
        sum += f(x0) + 4*f(x0 + h/2) + f(x1);
        
        x0 += h;
        x1 += h;
    }
    return (h/6)*sum;
}

double integral_monte(function f, double a, double b, unsigned step_count)
{
    double g,x,s = .0;
    const double k=b-a;
    srand(time(NULL));
    for (int i=0; i<=step_count; i++){
        g=rand()%1000;
        x=a+g*(b-a)/1000;
        s=s+f(x);
    }
    return ((1.0/step_count)*k*s);
}

void integral_runge4(dfunction f, double x0, double x1, double y0, double* x, double* y, double h)
{
    double k1,k2,k3,k4;
    const int n=(x1-x0)/h;
    int i=0;
    for(i=x0;i<n;i++)
    {
        x0=i*h;
        k1=h*f(x0, y0);
        k2=h*f(x0+h/2, y0+k1/2);
        k3=h*f(x0+h/2, y0+k2/2);
        k4=h*f(x0+h, y0+k3);
        double d=(k1+2*k2+2*k3+k4)/6;
        y0=y0+d;
    }
    x0=i*h;
    *x=x0;
    *y=y0;
}

void integral_runge5(dfunction f, double x0, double x1, double y0, double* x, double* y, double h)
{
    double k1,k2,k3,k4,k5;
    const int n=(x1-x0)/h;
    int i=0;
    for(i=x0;i<n;i++)
    {
        x0=i*h;
        k1=h*f(x0, y0)/3;
        k2=h*f(x0+h/3, y0+k1)/3;
        k3=h*f(x0+h/3, y0+k1/2+k2/2)/3;
        k4=h*f(x0+h/2, y0+3*k1/8+9*k3/8)/3;
        k5=h*f(x0+h, y0+3*k1/2-9*k3/2+6*k4)/3;
        double d=(k1+4*k4+k5)/2;
        y0=y0+d;
    }
    x0=i*h;
    *x=x0;
    *y=y0;
}

void integral_eiler(dfunction f, double x0, double x1, double y0, double* x, double* y, double h)
{
    const int n=(x1-x0)/h;
    for (int i=x0;i<n;i++)
    {
        y0 += h * f(x0, y0);
        x0 += h;
    }
    //x0=i;
    *x=x0;
    *y=y0;
}