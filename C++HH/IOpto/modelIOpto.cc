#include "modelIOpto.h"
#include "math.h"

void modelIOpto(double t,double *x,double *dx,double *parameter,double
*extra)
{

double F,So;
F=0.0006*parameter[2]*parameter[3]/parameter[4];
So=0.5*(1+tanh(120*(extra[3]-0.1)));


dx[0]=parameter[5]*F*x[3]*(1-x[0]-x[1]-x[2])-(parameter[7]+parameter[10])*x[0]+parameter[11]*x[1];
dx[1]=parameter[6]*F*x[3]*x[2]-(parameter[8]+parameter[11])*x[1]+parameter[10]*x[0];
dx[2]=parameter[8]*x[1]-(parameter[6]*F*x[3]+parameter[9])*x[2];
dx[3]=(So-x[3])/parameter[12];


//if (parameter[14]==1) //discarded the use of 3 state model in favour of 4 state model-MAy 6th 2010
//{
//	dx[0]=parameter[5]*F*(1-x[0]-x[1])-parameter[7]*x[0];
//	dx[1]=parameter[7]*x[0]-parameter[9]*x[1];
//	
//	}


}

/*m1=1./(1+exp(-(v+60)/8.5));
m2=1./(1+exp(-(v+36)/20));
tma=(1./(exp((v+35.82)/19.69)+exp(-(v+79.69)/12.7))+.37);
h1=1./(1+exp((v+78)/6));
tadef=1./(exp((v+46.05)/5.)+exp(-(v+238.4)/37.45));
if(v<-63)
ta1=tadef;
else
ta1=19;
if(v<-73)
ta2=tadef;
else
ta2=60;

dx[0]=(m1-x[0])/tma;
dx[1]=(m2-x[1])/tma;
dx[2]=(h1-x[2])/ta1;
dx[3]=(h1-x[3])/ta2;*/
