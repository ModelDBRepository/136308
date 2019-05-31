
#include "modelMinneuron.h"
#include "math.h"
#include "iostream.h"
void
modelMinneuron (double t, double *x, double *dx, double *parameter,
		 double *extra)
{
  double gna,gk,vna,vk,gl,vl,iapp,v,vm1,vn1,km1,kn1,CM,tn,vmslow,kmslow,gslow;
  double minf,ninf,mslowinf,tinf,taumslow;
 
 gna=parameter[0];
 vna=parameter[1];
 gk=parameter[2];
 vk=parameter[3];
 gl=parameter[4];
 vl=parameter[5];
 iapp=parameter[6];
vm1=parameter[7];
km1=parameter[8];
vn1=parameter[9];
kn1=parameter[10];
CM=parameter[11];
tn=parameter[12];
/*setting the slow current parameters fixed for now*/

gslow=5;
vmslow=-20;
kmslow=5;
taumslow=20;

 v=x[0];

minf=1./(1+exp((vm1-v)/km1));
ninf=1./(1+exp((vn1-v)/kn1));
tinf=tn;

mslowinf=1./(1+exp(vmslow-v)/kmslow);

dx[0] =(-gna*minf*(v-vna)-gk*x[1]*(v-vk)-gslow*x[2]*(v-vk)-gl*(v-vl)+iapp+extra[1])/CM;
dx[1]=(ninf-x[1])/tinf;
dx[2]=(mslowinf-x[2])/taumslow;
  

}
