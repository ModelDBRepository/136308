#ifndef _define_h_
#define _define_h_
#include<iostream.h>
#include<iomanip.h>
#include<fstream.h>
#include<math.h>
#include <vector>
#include<string>
#include<cstring>
#include<sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../../Neuron.h"
#include "../../Synapse.h"
#include "../../rk4.h"
#include "../../Insynapse/Insynapse.h"
#include "../../Insynapse/Insynapse.cc"
#include "../../HHneuron/HHneuron.h"
#include "../../Izhineuron/Izhineuron.h"
#include "../../Rose/Rose.h"
#include "../../TwoDsynapse/TwoDsynapse.h"
#include "../../Henrysynapse/Henrysynapse.h"
#include "../../Ihcurrent/Ih.h"
#include "../../IAcurrent/IA.h"
#include "../../IMcurrent/IM.h"
#include "../../matrix.h"
#include "../../Calciumchannel.h"
#include "../../ITcalcium/IT.h"
#include "../../randomc.h"
#include "../../PDrule/PD.h"
#include "../../Couplingcurrent/Couplingcurrent.h"
#include "../../Connectivity.h"
#include "../../IOpto/IOpto.h"

#include <time.h>

#include <algorithm>
#include <vector>
#define N 4

#ifndef _NO_NAMESPACE
using namespace std;
using namespace math;
#define STD std
#else
#define STD
#endif

#ifndef _NO_TEMPLATE
typedef matrix < double >Matrix;
#else
typedef matrix Matrix;
#endif




/*
Function Spikecount : Stores the times, in the dynamics when v>vpeak..
Basically stores the ISI for Izhikevich type models where u have resetting of the function
when it exceeds certian peak.

Function ISI, computes the average interspike interval from the data generated out of spikecount  

Function Max_vect, Min_vect computes the max and min from vector

Function Entropy : Divides the entire range of frequencies, into N bins, and computes the
probability of each bin. From that determines the std informatio entropy. The output is the
Relative entropy which is the Entropy computed divided by the max entropy=log(Nbins)

Function Complexity: Takes in the computed Relative Entropy and spits out, the Complexity
measure: Which  characterises the amount of order and disorder in the network.
*/

string IntToStdStr(const int d)
{
   std::ostringstream     ostr;
   ostr << d;
   return ostr.str();
} 



string DoubleToStdStr(const double d)
{
   std::ostringstream     ostr;
   ostr << d;
   return ostr.str();
} 

void GeneratePulseData(int Num,double StartTime, double Width, double DutyCycle,vector<double> &TON,vector<double>&TOFF)
{
	for (int i=0;i<Num;i++)
	{
	TON.push_back(StartTime+i*(Width+DutyCycle));
	TOFF.push_back(StartTime+Width+i*(Width+DutyCycle));	
	}
	}

double Heaviside(double x)
{
	double Out;
	if (x>=0)
	Out=1;
	else
	Out=0;
	return(Out);
	}

double GetPulse(vector<double> TON,vector<double> TOFF,double &tim)
{
double pulse=0;
	
for (int i=0;i<TON.size();i++)	
pulse=pulse+Heaviside(tim-TON[i])*Heaviside(TOFF[i]-tim);	
	return pulse;
}


double GetPhaseDiff(double &Ref,vector<double>&B)
{
	vector<double> Diff;
	double Temp;
	int bul=0;
	int start=0;
	if (B.size()<20)
	start=0;
	else
	start=B.size()-20;
	
    for (int i=start;i<B.size();i++)
	Diff.push_back(Ref-B[i]);
	
	sort(Diff.begin(),Diff.end());
    for (int i=0;i<Diff.size();i++)
    {

    if (Diff[i]>0 && bul==0)
     {
     	Temp=Diff[i];
     	bul=1;
      }
    }
	return Temp;
}




double
ISI (vector < double >&y,double Time)
{
  vector < double >s;
  double average, sum;
int sze;
sze=y.size();  
sum = 0;
if (sze>=2)
{
  for (unsigned int i = 1; i < y.size (); i++)
  {
  	if (y[i-1]>Time) //eliminates the transient upto 200 msec
    s.push_back (y[i] - y[i - 1]);
  } 
  for (unsigned int i = 0; i < s.size (); i++)
    sum = sum + s[i];
    
  average = sum / (s.size ());
 // cout<<sum<<" "<<s.size()<<" "<<y.size()<<" "<<average<<endl;
} 
else
{
cout<<"insufficient spike increase duration of time or the neuron did not spike "<<endl;
average=0;
}
 s.clear();
 return (average);
}

double
max_vect (vector < double >&y)
{
  double val = 0;
  for (unsigned int i = 0; i < y.size (); i++)
    {
      val = max (y[i], val);

    }
  return (val);
}

double
min_vect (vector < double >&y)
{
  double val = 0;
  for (unsigned int i = 0; i < y.size (); i++)
    {
      if (val != 0)
	val = min (y[i], val);

    }
  return (val);
}



double
Spikepresent (double *tim, double *v, double threshold, double spikewidth,
	      double vpeak, int &boolean, double *spiketrigger)
{
  double spike = 0;
  if (*tim > 0 && *v > threshold && boolean == 0)
    {
      boolean = 1;
      spiketrigger[0] = *tim;
    }

  if (*tim >= spiketrigger[0] && *tim <= spiketrigger[0] + spikewidth)
    {
      spike = 1;
    }
  if (*v > vpeak)
    boolean = 0;
  return (spike);
}

void
Fread (char *y, Matrix & M, int Ntotal)
{

  ifstream fread;
  vector < double >read (Ntotal, 0);
  int row = 0;
  fread.open (y, ios::in);
  for (int i = 0; i < Ntotal; i++)
    fread >> read[i];
  if (!fread)
    {
      cerr << "error in opening" << endl;
      exit (0);
    }
  while (!fread.eof ())
    {
      for (int j = 0; j < Ntotal; j++)
	{
	  M (row, j) = read[j];

	}
      for (int j = 0; j < Ntotal; j++)
	fread >> read[j];
      row += 1;
    }

}

/****Function to compute spike times for any given spike train****/

void
spiketimes (double *tim, double *v, double Th, int &bol, vector < double >&y)
{
  if (*v > Th && bol == 0)
  {
  	    y.push_back (*tim);
		  bol=1;
  }
  if (*v <= Th)
    bol = 0;
}

double
RuleInhib (double x, double a, double b, double c, double d,double strength)
{
  double out, outmax, outmax1;
  outmax = pow (a / b, a) * exp (-a);
  outmax1 = pow (c / d, c) * exp (-c);


  if (x > 0)
    out = strength * (pow (x, 1. * a) * exp (-b * fabs (x))) / outmax;
  else
    {
      if (fmod (c, 2.0) == 0)
	{
	  out = -strength * (pow (x, c) * exp (-d * fabs (x))) / (1 * outmax1);
	}
      else
	{
	  out = strength * (pow (x, c) * exp (-d * fabs (x))) / (1 * outmax1);
	}
    }
  return out;
}


double RuleExcite(double x,double ap,double ad,double bp,double bd,double eta,double strength)
{
double out, A,B;	
	A=strength*ap*pow(ad,eta)/(bp+eta*bd);
	B=strength*ad*pow(ap,eta)/(eta*bp+bd);
	if (x>=0)
	out=A*exp(-bp*x)-B*exp(-eta*bp*x);
	else
	out=A*exp(eta*bd*x)-B*exp(bd*x);
	
	return out;
	}
                  

double box_muller (double m, double s, int32 seed)	/* normal random variate generator */
{
  /* mean m, standard deviation s */
  double y1,y2,x1,x2,w=2;
	TRandomMersenne rg(seed);
do{
	x1=2*rg.Random()-1;
	x2=2*rg.Random()-1;
	w=x1*x1+x2*x2;
}while(w>=1);
w = sqrt( (-2.0 * log( w ) ) / w );         y1 = x1 * w;         y2 = x2 * w;
  return (m + y1 * s);
}

double
Average (vector < double >y)
{
  double result;
  double sum = 0;
  int k = y.size ();
  if (k != 0)
    {
      for (int i = 0; i < k; i++)
	sum = sum + y[i];
      result = sum / k;
    }
  else
    result = 0.0;
  return (result);
}

double Variance(vector <double>y)
{
	double result,Temp,Avg;
	double sum=0;
	for (int i=0;i<y.size();i++)
	sum=sum+y[i]*y[i];
	Temp=sum/y.size();
	Avg=Average(y);
	result=Temp-Avg*Avg;
	return(result);
	}

void
Raster (ofstream & Outfile, double &tim, int &bul, double &volt,
	double threshold, int &i)
{
//rastercomputation
  //takes in the outfile file, tim, bul: a boolean number, volt the neurons spiking, the threshold to detect spike, and spits out the time of neuron "i" firing
  bul = 0;
  if (volt > threshold && bul == 0)
    {
      Outfile << tim << " " << i + 1 << endl;
      bul = 1;
    }
  else;
}

void
alpha_syn (double *tim, double g, double alph, vector < double >&Tspk,
	   vector < double >&sum, int &i)
{
  double *x;
  x = new double[1000];
  for (unsigned int j = 0; j < Tspk.size (); j++)
    {
      x[j] = *tim - Tspk[j];
      if (x[j] > 0)
	{
	  sum[i] = sum[i] + g * x[j] * alph * alph * exp (-alph * x[j]);
	}

    }
  delete x;
}

double
Maprule (vector < double >Tpre, vector < double >Tpost, double a, double b,
	 double c, double d)
{
  double out = 0;
  double diff;

  vector < double >Result;
  int sizeTpost = Tpost.size ();
  if (sizeTpost == 1)
    {
      for (unsigned int j = 0; j < Tpre.size (); j++)
	{
	  diff = Tpost[0] - Tpre[j];
	  Result.push_back (diff);
	}
    }

  if (sizeTpost==2||sizeTpost>2)
     {
     for (unsigned int j=0;j<Tpre.size();j++)
     {
     if (Tpre[j]<Tpost[0])
     diff=Tpost[0]-Tpre[j];
     else if(Tpre[j]>Tpost[1])
     diff=Tpost[1]-Tpre[j];
     else if (Tpre[j]>=Tpost[0] && Tpre[j]<=Tpost[1])
     {
     diff=Tpost[0]-Tpre[j];
     Result.push_back(diff);
     diff=Tpost[1]-Tpre[j]; 
     } 
     else;  
     Result.push_back(diff); 
     } 
     }
  
 /* double wold = 1000;
  if (sizeTpost >= 2)
    {
      for (int j = 1; j < Tpre.size (); j++)
	{
            wold=1000;
	  for (int i = 0; i < sizeTpost; i++)
	    {
        	      double u = Tpost[i] - Tpre[j];
	  //    cout << " " << sizeTpost << " " << Tpre.
	//	size () << " " << u << endl;
      	    
  if (fabs (u) >= 3 && fabs (u) < fabs (wold))
             wold=u;	
	else;
	    
}
	  diff = wold;
	//  cout << diff << endl;
	  Result.push_back (diff);
	}
    }
*/

  for (unsigned int j = 0; j < Result.size (); j++)
    out += RuleInhib (Result[j], a, b, c, d,.5);
//out+=Rule(Result[j],3.0,.5,5.0,.25);

  return (out);
}

void
Pulsedetect (double *tim, vector < double >&Tspike, int &count, double &pulse)
{
  for (unsigned int j = 0; j < Tspike.size (); j++)
    {
      if (*tim > Tspike[count] + .5)
	count += 1;
      if (*tim > Tspike[count] && *tim < Tspike[count] + .5)
	pulse = 1;
      else
	pulse = 0;
    }

}

double Kuramoto(vector<double> &Tpre,vector<double> &Tpost,double period)
{
double phaseterm, costerm, sinterm, cossum = 0, sinsum = 0, kura;
double size=min(Tpre.size(),Tpost.size());
 for (int i = 0; i < size; i++)
	{			
   phaseterm = fmod (fabs (Tpost[i] - Tpre[i]), period);
	  costerm = cos (phaseterm);
	  sinterm = sin (phaseterm);
	  cossum += costerm;
	  sinsum += sinterm;
	}
      kura = sqrt (cossum * cossum + sinsum * sinsum) / size;
return(kura);
}
void
SlowRise (double &tim,double Threshold, double &volt, int &bul, double tauR,double &ref_time, double &out)
{
  
  if (volt > Threshold && bul==0)
     {    ref_time=tim;
      // cout<<ref_time<<endl;
        }
    if (volt>Threshold) 
    bul = 1;
else bul=0;
    if (tim >= ref_time && tim < ref_time + tauR)
    {out = 1.0;}
  else
    out = 0.0;

}
double Phase_Compute(double pre,double post,double period)
{
double phase,inter;
inter=fabs((pre-post));
phase=fmod(inter,period);
//phase=(pre-post)-floor(inter)*period;
return(phase);
}

void ReadNetwork(string Y,int row,int column,double **A)
{
	
	ifstream DataFile;
DataFile.open((char *)Y.c_str(),ios::in);
int Man,Nan;
double Temp;

	while(!DataFile.eof())
	{
		DataFile>>Man>>Nan>>Temp;
		A[Man-1][Nan-1]=Temp/Temp;

		}

DataFile.close();
	}
	
void SumMatrixColumn(double **A,int NN,int MM,vector<double>&ColumnSum)
{
		
	double sum;
	for (int i=0;i<NN;i++)
	{
		sum=0;
	for (int j=0;j<MM;j++)
	{sum=sum+A[i][j];}
	
  ColumnSum.push_back(sum);

	}

}	

void SumMatrixRow(double **A,int NN,int MM,vector<double>&RowSum)
{
	double sum;
	for (int j=0;j<MM;j++)
	{
		sum=0;
	for (int i=0;i<NN;i++)
	sum=sum+A[i][j];
RowSum.push_back(sum);
	}
  
}	

void GeneratePoisson(double endtime,double Rate,double Refrac,vector<double>&Poisson,int32 seed)
{
	//int32     seed = time(NULL);
	double Temp,Exp;
	double sum=0;
	TRandomMersenne rg(seed);
	while(sum<endtime)
	{
		Temp=rg.Random();
		Exp=(1000/Rate)*log(1/(1-Temp));
        
        if (Exp>Refrac) //account for refractory period;
        {
    	sum=sum+Exp;
		Poisson.push_back(sum);
		
        }
	}
}

double HenrySpikeGen(double tim, vector<double>Poisson,int *count)
{
	double Out=0;
	if (tim>Poisson[*count])
	 {
	 	if (tim<Poisson[*count]+.75)
	 	Out=1;
        else if (tim>=Poisson[*count]+.75& tim<Poisson[*count]+.75+.02)
	 	*count+=1;
	 	
	 	}
	return Out;
	}

double DelayBuff(vector<double>&Data,double volt)
{
	double out;
	if (Data.size()==0)
	out=volt;
	else
	{
	Data.erase(Data.begin());
	Data.push_back(volt);
    out=Data[0];	
	}
return out;
}

int ActiveNeurons(vector<double>*y,int MM,double Tim)
{
	int Out=0;
	int count;
	for (int i=0;i<MM;i++)
	{
		count=0;
		while(count<y[i].size())
		{
			if (y[i][count]>=Tim)
			{
			count=y[i].size();
		      Out=Out+1;	
			}
			else
			{
				count=count+1;
				}
		}
		
	 }
	return (Out);
	}

void IniConditionForDelay(int Num,vector<double>&PhiIniSpikes,int32 seed)
{
	int BulSp=1;
	int RanOld=0;
int RanNew=0;
	TRandomMersenne rg(seed);
	double Siz=PhiIniSpikes.size();
	while(Siz<Num)
	{
		if (BulSp)
   {
	RanNew=rg.IRandom(1,50);
	if (fabs(double(RanNew)-double(RanOld))>=2)
	BulSp=0;
	}
	if (~BulSp)
	{
	PhiIniSpikes.push_back(RanNew/epsilon);
	BulSp=1;
    }
    Siz=PhiIniSpikes.size();
		}
	sort(PhiIniSpikes.begin(),PhiIniSpikes.end());
}

#endif
