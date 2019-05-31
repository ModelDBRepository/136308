#include "defineOpto.h"#include "Neur_ClassOpto.h"#include "Corr_Stat.h"#include "DotFile.h"#include <time.h>

inline double MaxVal(double A,double B)
{
	double Out;
	if (A>=B)
	Out=A;
	else
	Out=B;
	return(Out);
	}

inline int MinVal(int A,int B)
{
	int Out;
	if (A<=B)
	Out=A;
	else
	Out=B;
	return(Out);
	}

intmain(int ac, char **av){
	time_t          start, end1;	time(&start);	int32           seed = time(NULL);	TRandomMersenne rg(seed); double          tim=0.0, timestep = epsilon, Threshold = -10;	int counttime=0;
	
double	timsyncestimate=700.0; //the time from which sync estimates will be determined
double timinitial=200;// the time of run without turning on the synapses
	
		if (ac <=12) {	    puts("endtime: Total Simulation Time");
   		puts("IdcI: DC current into inhibitory neurons");
   		puts("Conductance of Opto Current");
   		puts("Reversal Potential of Opto Current");
   		puts("Max Light Intensity");
   		puts("Num Light pulse");
   		puts("Width of pulse");
   		puts("Duty Cycle");
        puts("Channel Type");
   		puts("OutData file");
 		puts("Deltapulse time to calculate PRC");
 		puts("Second delta pulse time");
		exit(0);	}	string TYPE="HH";
	string HOME="/nfs/homes/stalathi/Work/Neuron_Model_1.2/C++HH/Codes/";
		double          endtime = atof(av[1]);
    double          IdcI=atof(av[2]);
    double          gOpto = atof(av[3]);
    double          EROpto=atof(av[4]);
    double defaultintensity=atof(av[5]);
	 int Numpulse=atoi(av[6]);
	 double Width=atof(av[7]);
	 double DutyCycle=atof(av[8]);
	 int ChType=atoi(av[9]);
    string OutDataFile=av[10];    
double deltapulse=atof(av[11]);
double deltapulse2=atof(av[12]);

ofstream OutFile;
OutFile.open((char *)OutDataFile.c_str(),ios::out);

 /**************/       
    vector< vector<double> > TI(3, vector<double>(0,0)); 
//    vector < double > *TI;//	TI = new vector < double >[3000];
	int            *bolI; 	bolI = new int   [10];
 	


 vector<double> TON,TOFF;
vector<double> TPoissOn,TPoissOff;
seed=100;//rg.IRandom(0,1000000000);
GeneratePoisson(endtime,40,1,TPoissOn,seed);
for (int i=0;i<TPoissOn.size();i++)
{
TPoissOff.push_back(TPoissOn[i]+Width);
//cout<<TPoissOn[i]<<" "<<TPoissOff[i]<<endl;
}

 double starttime=200;
 GeneratePulseData(Numpulse,starttime, Width, DutyCycle,TON,TOFF);
 double pulse=0;
 	
	 HHneuron     **neurHHI;
	neurHHI = new HHneuron *[1];
	
	for (int i=0;i<2;i++)
	{
	neurHHI[i] = new HHneuron(0.0,3);
	neurHHI[i]->x[0] = -65;
	neurHHI[i]->parameter[7] = IdcI;
	neurHHI[i]->parameter[11]=-55;
	neurHHI[i]->parameter[5]=-65;
	}
	
	
	IOpto **OptoCurr;
	OptoCurr = new IOpto *[0];
	OptoCurr[0] = new IOpto(neurHHI[0],gOpto,EROpto,ChType); //ChType=1 is WT OptoChannel; ChType=2 is ET123 OptoChannel
	OptoCurr[0]->parameter[12]=1.3;
	OptoCurr[0]->parameter[2]=defaultintensity;


double Bottom=-67;
double Top=-50;
 int count=0;
double modintensity=0;

double MaxVolt=-200,MaxCurr=-200;
double OptoCurrVal;

double Rec_Time=0,Rec_Time2=0;
int bolrec=0,bolrec2=0;

double tref,tend;
int bultest;

	while (tim < endtime) {
		pulse=0;
		
      if(tim>200)
      {
      if (tim>TI[0][TI[0].size()-1]+deltapulse &tim<=TI[0][TI[0].size()-1]+deltapulse+Width)
      pulse=1;
      }

        for (int i=0;i<2;i++)
		HH_Run(&tim,neurHHI[i],timestep);	
		IOpto_Run(&tim,OptoCurr[0],pulse,timestep);
		
			        		if (tim > 100) 
		{
			for (int i=0;i<2;i++)
		spiketimes(&tim, &neurHHI[i]->x[0], Threshold, bolI[i], TI[i]);
		}
		
		MaxVolt=MaxVal(MaxVolt,neurHHI[0]->x[0]);
		MaxCurr=MaxVal(MaxCurr,OptoCurr[0]->Iion());		
		tim += epsilon;
		count=count+1;
			}
double RefPeriod=TI[1][TI[1].size()-1]-TI[1][TI[1].size()-2];
OutFile<<IdcI<<" "<<ChType<<" "<<defaultintensity<<" "<<Width<<" "<<deltapulse<<" "<<deltapulse2<<" "<<RefPeriod<<" "<<RefPeriod<<" "<<TI[0][TI[0].size()-1]-TI[0][TI[0].size()-2]<<endl;
OutFile.close();

	vector < double >PeriodI;	
	time(&end1);	double TotalTime = difftime (end1, start);
	delete *neurHHI;	delete []neurHHI;
	delete *OptoCurr;    delete[] OptoCurr;		delete []bolI;			return 0;}