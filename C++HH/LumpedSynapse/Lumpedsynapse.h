#ifndef _Lumpedsynapse_H_
#define _Lumpedsynapse_H_
#define Two_DIM 2
#define Two_PAR 7
class Lumpedsynapse:public Synapse{
public:
double t,*x,*dx,*parameter,*extra,*xnew;
int steptransfer;
Lumpedsynapse();
Lumpedsynapse(Neuron *,Neuron *,double,int s);
~Lumpedsynapse();
void update(double timestep);
 void steptime();
void intime(double intim){t=intim;}
double Recordtime(double intime){double out=intime;return out;}
double synapse(){return x[0];}
void getvol();
virtual double Isyn();
virtual double Calcium();

};
#endif
