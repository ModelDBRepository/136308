/*Role of IOpto currents */

/*
IOpto currents play role in getting continuous gain function for spiking neuron...
Also in there presence there is significant delay between firing of neuron in
response to a depolarizing dc current pulse
*/

#ifndef _IOptocurrent_H_
#define _IOptocurrent_H_
#define IOpto_DIM 6
#define IOpto_PAR 15
class IOpto:public Ionchannel{

public:
double t,*x,*dx,*xnew,*parameter,*extra;
IOpto();
IOpto(Neuron *,double a,double b, double type );
IOpto(Neuron *,double *a,double *b );
~IOpto();
void setvalues(Neuron *,double *a,double *b);
void update(double timestep);
void steptime();
void intime(double intim){t=intim;}
void getvol();
void Getpulse(double);
virtual double Iion();
};
#endif
