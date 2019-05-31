#ifndef _LumpedNeuron_H_
#define _LumpedNeuron_H_

#define HH_DIM 2
#define HH_PAR 12

class LumpedNeuron:public Neuron{

public:
double t,*x,*dx,*parameter,*extra,*xnew;
LumpedNeuron():Neuron(HH_DIM,HH_PAR){}
LumpedNeuron(double,double,double,double,double,int ); //Constructor of LumpedNeuron
~LumpedNeuron()
{
delete []x;delete []dx; delete []parameter,delete []xnew,delete []extra;

}
void setvalues(double *a,double *b);
void update(double timestep);
void steptime();
void intime(double intim){t=intim;}
double time(){return t;}
void Isynintegrate();
double E(){return x[0];}
double sp(){double test; test=0; return(test);};
void AddNoise(double &,double);
void AddInput(double &);
void operator = (LumpedNeuron &test);
double Cain(){}; //ghost function required by the structure of the setup
friend ostream & operator <<(ostream &, LumpedNeuron &);
};



//void Iionintegrate();
//void Icalintegrate();
//void Calintegrate();
//double Cain(){return x[4];}
#endif
