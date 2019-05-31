#include "define.h"
//#include "gd.h"
#include "Neur_Class_PRC.h"
#include "Corr_Stat.h"
#include <time.h>
int MIN(int a, int b)
{
	double Out;
	if(a>=b)
	Out=b;
	else
	Out=a;
	return Out;
	}

int
main(int ac, char **av)
{

ofstream OutFile,OutFile1;
ifstream InFile;


	time_t          start, end1, end2;
	int             increment = 0;
	time(&start);
	int32           seed = time(NULL);
	TRandomMersenne rg(seed);
	string          s1, s2, s3, s4, s5;

	if (ac <= 11) {
		puts("endtime");
		puts("Iinput external current");
		puts("self inhibition strength");
		puts("mutual inhibition strength");
		puts("strength of mutual electrical coupling");
		puts("decay constant for inhibition");
		puts("Tau Rise time");
		puts("Reversal potential of inhibitory synapse");
		puts("Delta pulse time of first input");
		puts("Delta pulse time of second input");
		puts("Outfile");
		exit(0);
		
	}
	int             NN = 4, count = 0;

	double          endtime = atof(av[1]);
	double          I_ext = atof(av[2]);
	double          gself = atof(av[3]);
	double          gmutual=atof(av[4]);
	double          gelectrical=atof(av[5]);
	double          tauD = atof(av[6]);
	double          tauR = atof(av[7]);
	double          ERever=atof(av[8]);
    double          deltapulse=atof(av[9]);
    double          deltapulse2=atof(av[10]);

    string          PRCOut=av[11];



double Curr,Temp,Period=0;
string StringtauD=DoubleToStdStr(tauD);
string StringtauR=DoubleToStdStr(tauR);
//string Read="Files/ISI_"+StringtauD+"_"+StringtauR+".dat";

OutFile1.open("./PRCData/TempData.dat",ios::out);


	double          tim=0, timestep = epsilon, Threshold = 0;

double Rec_Time=0;
int bolrec=0;

	vector < double >*T;
	vector <int>bolneur;
	T = new vector < double >[3000];
	for (int i = 0; i < NN; i++)
		bolneur.push_back(0);


	HHneuron      **neur;
	neur = new HHneuron *[NN];

	for (int i = 0; i < NN; i++) {
		neur[i] = new HHneuron(0.0, 3);
		neur[i]->parameter[11] = -65;
		neur[i]->parameter[7] = 0.;
		neur[i]->x[0] = -65;

	}

	Insynapse     **Input, *Ext;
	Input = new Insynapse *[NN];

     Ext=new Insynapse(neur[2],0.0);

	for (int i = 0; i < NN; i++)
		Input[i] = new Insynapse(neur[i], 0.0);

Couplingcurrent ***coupAB,***coupBA,***couprefAB,***couprefBA;	coupAB = new Couplingcurrent **[NN];	coupBA = new Couplingcurrent **[NN];	couprefAB=new Couplingcurrent **[NN];
	couprefBA=new Couplingcurrent **[NN];
	
   coupAB[0]=new Couplingcurrent *[NN];
   coupBA[0]=new Couplingcurrent *[NN];
   couprefAB[0]=new Couplingcurrent *[NN];
   couprefBA[0]=new Couplingcurrent *[NN];
   
   coupAB[0][0] =new Couplingcurrent(neur[1], neur[2], 0.0*gelectrical);
   coupBA[0][0] =new Couplingcurrent(neur[2], neur[1], gelectrical);
   couprefAB[0][0] =new Couplingcurrent(neur[3], neur[0], gelectrical);
   couprefBA[0][0] =new Couplingcurrent(neur[0], neur[3], 0.0*gelectrical);
   
	TwoDsynapse  ***slowself,***slowmutual;
	slowself = new TwoDsynapse **[NN];
    slowmutual=new TwoDsynapse **[NN];
    
    slowmutual[0]=new TwoDsynapse*[NN];
    slowmutual[0][0]=new TwoDsynapse(neur[2], neur[1], gmutual, 0., 0); //connecting through mutual synapse
    
        slowmutual[0][0]->parameter[1] = ERever;
		slowmutual[0][0]->parameter[2] = tauR;
		slowmutual[0][0]->parameter[3] = tauD;
    
    
    for (int i = 0; i < NN; i++) {
		slowself[i] = new TwoDsynapse *[NN];

		slowself[i][i] = new TwoDsynapse(neur[i], neur[i], gself, 0., 0);
		slowself[i][i]->parameter[1] = -82;
		slowself[i][i]->parameter[2] = tauR;
		slowself[i][i]->parameter[3] = tauD;
	}

	/*******************parameters for the TwoDsynapse to work********************/

	double         *ref_time;
	double         *vnew, *vold;
	double         *diff;
	int            *bol;
	ref_time = new double[NN];
	vnew = new double[NN];
	vold = new double[NN];
	diff = new double[NN];
	bol = new int   [NN];

    
    double ref_pre_post;
    double diff_pre_post;
    int bol_pre_post=0;
    double vold_pre_post=0,vnew_pre_post=0;
    

	for (int i = 0; i < NN; i++) {
		vnew[i] = 0;
		bol[i] = 0;
	}

	/*****************************************************************************/
	
//	cout<<tim<< " "<<endtime << " "<<epsilon<<" "<<I_ext<<" "<<gself<<" "<<tauR<<" "<<tauD<<endl;
	//variables to determine the coupling coefficient of the electrical synapse
	double v2Mod,v1Mod,v2Ref,v1Ref;
	
	while (tim < endtime) {

		for (int i = 0; i < NN; i++)
			Input[i]->set_I(0);
			
		if (tim > 200 ) {
			for (int i = 0; i < 2; i++)
				Input[i]->set_I(I_ext);
		}
		
		
		if (T[0].size()>=10 && bolrec==0)
	    {
	    Rec_Time=T[0][10-1];
	//	cout<<"Recorded this tim "<<Rec_Time<<endl;
		bolrec=1;
		}
		
	
		
		if (Rec_Time!=0)
		{
		if (tim>Rec_Time+deltapulse && tim<Rec_Time+deltapulse+.5)
		  Input[2]->set_I(50);
		
		if (tim>Rec_Time+deltapulse2 && tim<Rec_Time+deltapulse2+.5)
		  Input[2]->set_I(50);
		
		}
			

		for (int i = 0; i < NN; i++) {
			HH_Run(&tim, neur[i], timestep);
			TwoD_Run(&tim, slowself[i][i],neur[i]->x[0], timestep);
		}
		TwoD_Run(&tim, slowmutual[0][0],neur[2]->x[0], timestep);

		if (tim > 200) {
			for (int i = 0; i < NN; i++) {
				spiketimes(&tim, &neur[i]->x[0], Threshold, bolneur[i], T[i]);
			}
		}
				
		/*******************************************************/


		count += 1;
//		if (neur[0]->x[0]>0)
//OutFile1<<tim<<" "<<slowmutual[0][0]->Isyn()<<endl;
// OutFile1<<tim<<" "<<neur[0]->x[0]<<" "<<neur[1]->x[0]<<" "<<neur[2]->x[0]<<" "<<neur[3]->x[0]<<endl;
		tim += epsilon;
	}
	
	//cout<<tim<<" "<<neur[0]->x[0]<<" "<<neur[1]->x[0]<<" "<<neur[2]->x[0]<<" "<<neur[3]->x[0]<<endl;
OutFile1.close();

OutFile.open((char *)PRCOut.c_str(),ios::out);
/*
v2Ref=neur[2]->x[0];
v1Ref=neur[1]->x[0];
double CS=(v1Mod-v1Ref)/(v2Mod-v2Ref);
OutFile<<gelectrical<<" "<<CS<<endl;
*/

/*
string gString=DoubleToStdStr(gmutual);
string Istring=DoubleToStdStr(I_ext);
string Deltastring=DoubleToStdStr(deltapulse);
string Store="PRC_B_"+Deltastring+".dat";
*/



int Sz=int(MIN(double(T[0].size()),double(T[1].size())));

double sum=0;
int countdiff=0;
for (int i=0;i<Sz;i++)
{
	//cout<<T[1][i]<< " "<<T[0][i]<<" "<<T[1][i]-T[0][i]<<endl;
if (fabs(T[1][i]-T[0][i])>.001)
{
sum=sum+T[1][i]-T[0][i];
countdiff+=1;
}
}

double RefPeriod=T[0][T[0].size()-1]-T[0][T[0].size()-2];
double AsympPhase=T[1][Sz-1]-T[0][Sz-1];
OutFile.precision(10);
//OutFile<<I_ext<<" "<<RefPeriod<<endl;
//OutFile<<deltapulse<<" "<<T[1][10]-T[0][10]<<" "<<RefPeriod<<" "<<AsympPhase<<endl;
OutFile<<deltapulse<<" "<<T[1][10]-T[1][9]<<" "<<T[1][11]-T[1][10]<<" "<<T[1][12]-T[1][11]<<" "<<T[1][13]-T[1][12]<<" "<<RefPeriod<<" "<<AsympPhase<<endl;
//OutFile<<I_ext<<" "<<T[0][T[0].size()-1]-T[0][T[0].size()-2]<<endl;
cout.precision(4);
//cout<<I_ext<<" "<<T[0][20]-T[0][19]<<endl;

delete []ref_time;
delete []vnew;
delete []vold;
delete []bol;
delete []T;
delete *Input;
delete **slowself;
delete *neur;
delete []Input;
delete []neur;
delete []slowself;

OutFile.close();

	return 0;
}
