#ifndef _Neur_Class_h
#define _Neur_Class_h
#include "define.h"
void HH_Run(double *tim,HHneuron *neur,double timestep)
{
          neur->intime (*tim);
	  neur->Isynintegrate ();
	  neur->Iionintegrate ();
	  neur->Icalintegrate ();
    neur->Calintegrate();
	  neur->update (timestep);
	  neur->steptime ();
}


void TwoD_Run(double *tim,TwoDsynapse *TwoD,double V,double timestep)
{          
          TwoD->getvol (V);
	  TwoD->update (timestep);
	  TwoD->steptime ();
}
void Henry_Run(double *tim,Henrysynapse *Hen,double timestep)
{          
          Hen->getvol ();
	  Hen->update (timestep);
	  Hen->steptime ();
}

//void IOpto_Run(double *tim,IOpto *iopto,double Data,double timestep)
//{
//iopto->getvol();
//iopto->update(timestep);
//iopto->steptime(); 
//iopto->Getpulse(Data);
//}

/* 
void Izhi_Run(double *tim,Izhineuron *neur,double timestep)
{
          neur->intime (*tim);
         neur->Isynintegrate ();
	     neur->update (timestep);
	     neur->steptime ();
}
void Rose_Run(double *tim,Rose *neur,double timestep)
{
          neur->intime (*tim);
	  neur->Isynintegrate ();
	  neur->update (timestep);
	  neur->steptime ();
}
void IA_Run(double *tim,IA *ia,double timestep)
{
ia->getvol();
ia->update(timestep);
ia->steptime(); 
}
void IM_Run(double *tim,IM *im,double timestep)
{
im->getvol();
im->update(timestep);
im->steptime(); 
}
*/
/*


void HH_Quadratic_Run(double *tim,QuadraticNeuron *neur,double timestep)
{
          neur->intime (*tim);
	  neur->Isynintegrate ();
	  neur->update (timestep);
	  neur->steptime ();
}



void HHmin_Run(double *tim,Minneuron *neur,double timestep)
{
          neur->intime (*tim);
	  neur->Isynintegrate ();
	  neur->update (timestep);
	  neur->steptime ();
}



void IL_Run(double *tim,IL *il,double timestep)
{
il->getvol();
il->update(timestep);
il->steptime(); 
}

void IAHP_Run(double *tim,IAHP *iahp,double timestep)
{
iahp->getvol();
iahp->update(timestep);
iahp->steptime(); 
}


void PD_Run(double *tim,double &pre,double &post,double &diff,PD *Pd,double timestep)
{

Pd->intime(*tim);
Pd->getcal(pre,post);
Pd->getdiff(diff);
Pd->update(timestep);
Pd->steptime();
}
*/
#endif
