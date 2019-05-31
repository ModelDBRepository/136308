#include "iostream.h"
#include "modelLumpedNeuron.h"
#include "../rk4.h"
#include "../Neuron.h"
#include "LumpedNeuron.h"

LumpedNeuron::LumpedNeuron(double a,double A,double gs,double m,double sig, int type):Neuron(HH_DIM,HH_PAR)
{

int i;
Evalid=0;
Isynvalid=0;
Iionvalid=0;
t=0;
extra=new double[7];
for(i=0;i<7;i++)
extra[i]=0;
xnew=new double[Parno];
parameter=new double[Parno];
x=new double[Dimno];
dx=new double[Dimno];

double e0=2.5; //parameters for sigmoid function from Jansen et.al.,
double r=0.56;
double v0=6;

parameter[0]=a;// filter time scale term
parameter[1]=A;  //filter amplitude scaling term
parameter[2]=m;
parameter[3]=sig;
parameter[4]=gs;
parameter[5]=type; //label to distinguish interneuron from excitatory  population: Convection 1: Excitatory; -1: Interneuron
parameter[6]=e0;
parameter[7]=r;
parameter[8]=v0;


x[0]=0;
x[1]=0;

}
void LumpedNeuron::update(double timestep)
{
step(timestep,x,dx,parameter,extra,xnew,Dimno,&t,&modelLumpedNeuron);
Evalid=1;
}
void LumpedNeuron::steptime()
{
assert(Evalid);
for(int i=0;i<Dimno;i++)
{
x[i]=xnew[i];
}
Evalid=0;
Isynvalid=0;
Iionvalid=0;
Icalvalid=0;
Calvalid=0;
}
void LumpedNeuron::Isynintegrate()
{
if(!Isynvalid)
{
extra[1]=0;
forall(den_it) extra[1]+= den_it->c_value()->Isyn();
}
Isynvalid=1;
}

void LumpedNeuron::AddNoise(double &data,double timestep) //N(0,1) gaussian random no generated from main source code
{

extra[2]=sqrt(1./timestep)*data;
//extra[2]=1*data;
}

void LumpedNeuron::AddInput(double &data)
{
	extra[3]=data; //Synaptic input added from main source code
	}

void LumpedNeuron::operator =(LumpedNeuron &b)
{
t=b.t;
x=new double[HH_DIM];
dx=new double[HH_DIM];
xnew=new double[HH_DIM];
extra=new double[5];
parameter=new double[HH_PAR];
for (int i=0;i<HH_DIM;i++)
{
x[i]=b.x[i];
dx[i]=b.dx[i];
xnew[i]=b.xnew[i];
}
extra[1]=b.extra[1];
for(int i=0;i<HH_PAR;i++)
parameter[i]=b.parameter[i];
}
ostream &operator <<(ostream & dout, LumpedNeuron &b) //defining '<<' operator for class
                                               //output 
{
dout<<b.x[0];
return(dout);
}

/*
void LumpedNeuron::Iionintegrate()
{
if(!Iionvalid)
{
extra[2]=0;
forall(ion_it) extra[2]+= ion_it->c_value()->Iion();
}
Iionvalid=1;
}
void LumpedNeuron::Icalintegrate()
{
if(!Icalvalid)
{
extra[3]=0;
forall(cal_it) extra[3]+= cal_it->c_value()->Icalcium();
}
Icalvalid=1;
}

void LumpedNeuron::Calintegrate()
{
if(!Calvalid)
{
extra[4]=0;
forall(cal_it) extra[4]+= cal_it->c_value()->Calcium();
forall(calden_it)extra[4]+=calden_it->c_value()->Calcium();
//cout<<extra[4]<<endl;
}
Calvalid=1;
}
*/

