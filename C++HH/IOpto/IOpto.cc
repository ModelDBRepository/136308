#include "iostream.h"
#include "../Neuron.h"
#include "../Ionchannel.h"
#include "../HHneuron/HHneuron.h"
#include "modelIOpto.h"
#include"../rk4.h"
#include "IOpto.h"
IOpto::IOpto():Ionchannel(){}
IOpto::IOpto(Neuron *obj2,double a,double b, double type):Ionchannel(obj2,IOpto_DIM,IOpto_PAR)
{
Evalid=Iionvalid=0;
xnew=new double[Dimno];
extra=new double[4];
x=new double[Parno];
dx=new double[Dimno];
parameter=new double[Parno];


double lambda=470,H=0.9,wloss=1.1;
double epsilon1=0.5,epsilon2=0.1,Gd1=0.13,Gd2=0.025,Gr=.004;
double e12=0.053,e21=0.023;
double tauChR=1.3,gamma=0.01;

parameter[14]=type; //This decides whether the optochannel is wild type or modified type- see paper "Ultrafast Optogenetic Control"

if (parameter[14]==1) //corresponds to Opto channel parameters for wild type; the parameters are obtained for H=0.5
{
	Gd1=0.084;Gd2=.1254;e12=.0297;e21=.0184;gamma=.0443;epsilon1=.8535;epsilon2=.025;
	}

if (parameter[14]==2) //corresponds to Opto channel parameters for ET123 mutation; parameters obtained for H=0.5
{
	Gd1=0.1779;Gd2=.2362;e12=.0696;e21=.0268;gamma=.2533;epsilon1=4.6125;epsilon2=2.1969;a=.1416*a/.4555; // (normalization of a based on reproduction of Figure 4a of Ultrafast Optogenetic paper)
	}


x[0]=0;
x[1]=0;
x[2]=0;
x[3]=0;
x[4]=0;

parameter[0]=a; // maximal conductance
parameter[1]=b; //reversal potential 
parameter[2]=H;//Light intensity (in mW/mm2)
parameter[3]=lambda; //light wavelength (in nm)
parameter[4]=wloss; //(no units)
parameter[5]=epsilon1; //quantum efficiency parameter
parameter[6]=epsilon2;
parameter[7]=Gd1;//decay rates (in units of ms-1)
parameter[8]=Gd2;
parameter[9]=Gr;
parameter[10]=e12; //exchange rates (ms-1)
parameter[11]=e21;
parameter[12]=tauChR; //conformational change rate (ms-1)
parameter[13]=gamma; //ratio of conductance of two open states





}
IOpto::IOpto(Neuron *obj2,double *a,double *b):Ionchannel(obj2,IOpto_DIM,IOpto_PAR)
{
Evalid=Iionvalid=0;
int i;
xnew=new double[Dimno];
extra=new double[4];
x=new double[Parno];
dx=new double[Dimno];
parameter=new double[Parno];

for(i=0;i<Dimno;i++)
x[i]=a[i];
for(i=0;i<Parno;i++) 
parameter[i]=b[i];  
}                     
IOpto::~IOpto()
{
delete x;
delete dx;
delete parameter;
delete extra;
delete xnew;
}
void IOpto::setvalues(Neuron *obj2,double *a,double *b)
{
int i;
Evalid=Iionvalid=0;
tar=obj2;
tar->ion.add(this);
Dimno=IOpto_DIM;
Parno=IOpto_PAR;
xnew=new double[Dimno];
extra=new double[2];
x=new double[Parno];
dx=new double[Dimno];
parameter=new double[Parno];
for(i=0;i<Dimno;i++)
x[i]=a[i];
for(i=0;i<Parno;i++) //parameter 0 is the synaptic strength and parameter 1 is
parameter[i]=b[i];
}
void IOpto::update(double timestep)
{

step(timestep,x,dx,parameter,extra,xnew,Dimno,&t,&modelIOpto);
Iionvalid=1;
}
 void IOpto::steptime()
{
assert(Iionvalid);
for(int i=0;i<Dimno;i++)
{
x[i]=xnew[i];
}
Evalid=Iionvalid=0;
}
void IOpto::getvol()
{
if(!Evalid)
{
//extra=new double[2];
extra[1]=tar->E();
}
Evalid=1;
}

void IOpto::Getpulse(double data)
{
	extra[3]=data;
	}
	
double IOpto::Iion()
{
double Iiona;
Iiona=-parameter[0]*(tar->E()-parameter[1])*(x[0]+parameter[13]*x[1]);
return(Iiona);
}

/*
parameter[0]=max conductance of the channel
parameter[1]=reversal potentIOptol of the channel
x[0]=m1 activation varIOptoble
x[1]=m2 activation varIOptoble
x[2]=h1 inactivation varIOptoble
x[3]=h2 inactivation varIOptoble
*/
