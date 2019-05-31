
#include "modelLumpedNeuron.h"
#include "math.h"
#include "iostream.h"
void modelLumpedNeuron(double t,double *x,double *dx,double *parameter,double *extra)
{
//extra[1]: sum total of all Lumped synaptic input
//extra[2]: The weiner noise term also represented synaptic input from unknown source

// m and sig are the mean and varaince terms for noise input through unknown synaptic sources
//A, a are the parameters for the linear filter
double A,a,m,sig,gs,Sigmoid;
a=parameter[0];
A=parameter[1];
m=parameter[2];
sig=parameter[3];
gs=parameter[4];

//Sigmoid=parameter[4]*2*parameter[6]/(1+exp(parameter[7]*(parameter[8]-extra[1])));


//dx[1]=A*a*(gs*Sigmoid+m+sig*extra[2])-2*a*x[1]-a*a*x[0];
//cout<<extra[3]<<" "<<x[0]<<" "<<x[1]<<" "<<extra[2]<<endl;
dx[0]=x[1];
dx[1]=A*a*(extra[3]+m+sig*extra[2])-2*a*x[1]-a*a*x[0];
}
