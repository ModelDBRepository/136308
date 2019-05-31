#include "iostream.h"
//#include "../define.h"
#include "../Neuron.h"
#include "../Synapse.h"
#include "../LumpedNeuron/LumpedNeuron.h"
#include "modelLumpedsynapse.h"
#include"../rk4.h"
#include "Lumpedsynapse.h"
Lumpedsynapse::Lumpedsynapse():Synapse(){}
Lumpedsynapse::Lumpedsynapse(Neuron *obj1,Neuron *obj2,double gs,int s ):Synapse(obj1,obj2,Two_DIM,Two_PAR)
{
	Dimno=Two_DIM;
Parno=Two_PAR;

Evalid=Isynvalid=0;

steptransfer=s;
xnew=new double[Dimno];
extra=new double[3]; 
x=new double[Parno]; 
dx=new double[Dimno]; 
parameter=new double[Parno]; 
extra[0]=double(steptransfer);
extra[1]=0;
extra[2]=0;
x[0]=0.0;
parameter[0]=gs;
parameter[1]=s;
}
                  //parameter 3 is synaptic timescale for synapse  
Lumpedsynapse::~Lumpedsynapse()
{
delete x;
delete dx;
delete parameter;
delete extra;
delete xnew;
}

void Lumpedsynapse::update(double timestep)
{
	Dimno=Two_DIM;
Parno=Two_PAR;

step(timestep,x,dx,parameter,extra,xnew,Dimno,&t,&modelLumpedsynapse);
Isynvalid=1;
}

 void Lumpedsynapse::steptime()
{
assert(Isynvalid);
for(int i=0;i<Dimno;i++)
{
x[i]=xnew[i];
}
Evalid=Isynvalid=0;
}

void Lumpedsynapse::getvol()
{
if(!Evalid)
{
extra[1]=source->E();
}
Evalid=1;
}
double Lumpedsynapse::Isyn()
{
double Isync;
if (parameter[1]>0)
Isync=parameter[0]*extra[1];
else
Isync=-parameter[0]*extra[1];

return(Isync);
}


double Lumpedsynapse::Calcium()
{
double Isync;
}

