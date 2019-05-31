#include "modelHenrysynapse.h"
#include "math.h"


void modelHenrysynapse(double t,double *x,double *dx,double *parameter,double
*extra)
{
double So,tau,s1;
 tau =parameter[3]-parameter[2]; 
  s1 = parameter[3]/tau;
 So = 1. / 2 * (1 + tanh (120 * (extra[1] - .1)));
//So = 1. / 2 * (1 + tanh (120 * (extra[1] +25)));

dx[0]=(1./tau)*(So-x[0])/(s1-So);
}


//the 'extra' parameter signifies the the ode of the object needs input from other
//object at everytime tims step. 
