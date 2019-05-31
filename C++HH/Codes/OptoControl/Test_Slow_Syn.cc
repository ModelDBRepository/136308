#include "defineOpto.h"#include "Neur_ClassOpto.h"
#include "Neur_Class.h"#include "Corr_Stat.h"#include <time.h>
//./run_slow_compute 1 8000 -30 .5 0 0.15 0 2 .1 -75 0 0 2 Temp.dat Raster.dat 0.75 0 .01 1 1 100 2 3.92 5.5 0.1125 0.1125 .01
double
MIN(double a, double b)
{
	double          Out;
	if (a >= b)
		Out = b;
	else
		Out = a;
	return Out;
}

double
MAX(double a, double b)
{
	double          Out;
	if (a <= b)
		Out = b;
	else
		Out = a;
	return Out;
}
int           main(int ac, char **av) {
	time_t start, end1, end2;
time(&start);
int32 seed = time(NULL);
TRandomMersenne rg(seed);
string s1, s2, s3, s4, s5;

if (ac <= 27) {			puts("NN");
		puts("endtime");
		puts("Heterogeneity in the drive onto the pre synaptic neuron");				puts("Baseline current which is kept fixed, to decide the regime Idc post neuron");
		puts("percentage of feedback coupling (MCI network)");
		puts("mutual inhibition strength");
		puts("electrical coupling strength");
		puts("decay constant for inhibition");
		puts("Tau Rise time");
		puts("Reversal Potential of Inhibitory synapse");
		puts("Delay in synaptic input");
		puts("Is Learning Present");
		puts("do you want the time series data");
		puts("output file name");
		puts("Spike Time File to store the spike times");
		puts("Conductance of Opto Current");
		puts("Reversal Potential of Opto Current");
		puts("Max Light Intensity");
		puts("Num Light pulse");
		puts("Width of pulse");
		puts("Duty Cycle");
		puts("Channel Type");
		puts("Default Width");
		puts("Default Delay");
		puts("feedk1");
		puts("feedk2");
		puts("StirctCond");
		exit(0);
		
	} 		int          NN = atoi(av[1]);
		double         endtime = atof(av[2]);
		double         heter = atof(av[3]);
		double         Idc = atof(av[4]);
		double         percentgmutual = atof(av[5]);
		double         gmutual = atof(av[6]);
		double          gelec = atof(av[7]);
		double         tauD = atof(av[8]);
		double          tauR = atof(av[9]);
		double          ERever = atof(av[10]);
		double          TDelay = atof(av[11]);
		int             Learnpresent = atoi(av[12]);
		int            scale = atoi(av[13]);			string out = av[14];
		string          SpikeTimeFile = av[15];
		double         gOpto = atof(av[16]);
		double          EROpto = atof(av[17]);
		double 	        defaultintensity = atof(av[18]);
		int             Numpulse = atoi(av[19]);
		double          Width = atof(av[20]);
		double          DutyCycle = atof(av[21]);
		int             ChType = atoi(av[22]);
		//The parameter below are to test control of synchrony strategy
		double         Width2=atof(av[23]);
		double         Delay2=atof(av[24]);
		double         feedk1=atof(av[25]);
		double         feedk2=atof(av[26]);
		double         StrictCond=atof (av[27]);
		
		double          tim = 0.0, timestep = epsilon, Threshold = 0;
		double gself=0.0;
	/*******Opto variables***********/
	vector < double >TON, TOFF;
	double          starttime = 200;
	GeneratePulseData(Numpulse, starttime, Width, DutyCycle, TON, TOFF);
	double          pulse = 0,pulse0=0, pulse1=0;	vector < double >x1, x2, w, *T;
	vector < double >x1p, x2p, wp, *TP;
	T = new vector < double >[3000];
	TP = new vector < double >[3000];
	int          *bol, *bolp;
	bol = new int  [NN + 10];
	bolp = new int [NN + 10];
	
	for (int i = 0; i < NN; i++) {
	x1.push_back(0.);
	x2.push_back(0.);
	w.push_back(0.);
	x1p.push_back(0.);
	x2p.push_back(0.);
	wp.push_back(0.);
		} 	ofstream Outfile, Outfile1, Outfile2;
//	Outfile.open(out.c_str(), ios::app);
	
HHneuron ** neurpre, **neurpost;
	neurpre = new HHneuron *[NN];
	neurpost = new HHneuron *[NN];

double Inivariable=-75+ 10 * rg.Random();
	for (int i = 0; i < NN; i++) {
		neurpre[i] = new HHneuron(0.0, 3);
		neurpre[i]->parameter[11] = -65;
		neurpre[i]->parameter[7] = 0.;
		neurpre[i]->x[0] = Inivariable;
		neurpost[i] = new HHneuron(0.0, 3);
		neurpost[i]->parameter[11] = -65;
		neurpost[i]->parameter[7] = 0;
		neurpost[i]->x[0] = -65;
		} IOpto ** OptoCurr;
	OptoCurr = new IOpto *[2 * NN];
	for (int i = 0; i < NN; i++) {
		OptoCurr[2 * i] = new IOpto(neurpre[i], 1.0 * gOpto, EROpto, ChType);
		OptoCurr[2 * i]->parameter[2] = defaultintensity;
		OptoCurr[2 * i + 1] = new IOpto(neurpost[i], 1.0 * gOpto, EROpto, ChType);
		OptoCurr[2 * i + 1]->parameter[2] = defaultintensity;
	}
	Insynapse ** Inputpre, **Inputpost;
	Inputpre = new Insynapse *[NN];
	Inputpost = new Insynapse *[NN];
		for (int i = 0; i < NN; i++) {
	Inputpre[i] = new Insynapse(neurpre[i], 0.0);
	Inputpost[i] = new Insynapse(neurpost[i], 0.0);
	} Couplingcurrent *** coupAB, ***coupBA;
	coupAB = new Couplingcurrent **[NN];
	coupBA = new Couplingcurrent **[NN];
	for (int i = 0; i < NN; i++) {
	coupAB[i] = new Couplingcurrent *[NN];
	coupBA[i] = new Couplingcurrent *[NN];
	
	for (int j = 0; j < NN; j++) {
	coupAB[i][j] = new Couplingcurrent(neurpre[i], neurpost[j], gelec / NN);
	coupBA[i][j] = new Couplingcurrent(neurpost[i], neurpre[j], gelec / NN);
			} 	} TwoDsynapse *** slowself, ***slowselfA, ***slowmutual, ***slowmutualA;
	slowself = new TwoDsynapse **[NN];
	slowselfA = new TwoDsynapse **[NN];
	slowmutual = new TwoDsynapse **[NN];
	slowmutualA = new TwoDsynapse **[NN];
	for (int i = 0; i < NN; i++) {
	slowself[i] = new TwoDsynapse *[NN];
	slowselfA[i] = new TwoDsynapse *[NN];
	slowmutual[i] = new TwoDsynapse *[NN];
	slowmutualA[i] = new TwoDsynapse *[NN];
	slowself[i][i] = new TwoDsynapse(neurpre[i], neurpre[i], gself, 0., 0);
	slowselfA[i][i] = new TwoDsynapse(neurpost[i], neurpost[i], gself, 0., 0);
	slowself[i][i]->parameter[1] = ERever;
	slowselfA[i][i]->parameter[1] = ERever;
	slowself[i][i]->parameter[2] = tauR;
	slowself[i][i]->parameter[3] = tauD;
	slowselfA[i][i]->parameter[2] = tauR;
	slowselfA[i][i]->parameter[3] = tauD;
				for (int j = 0; j < NN; j++) {
		slowmutual[i][j] = new TwoDsynapse(neurpre[i], neurpost[j], 1.0 * gmutual / NN, 0., 0);
		slowmutualA[i][j] = new TwoDsynapse(neurpost[i], neurpre[j], (percentgmutual/100) * gmutual / NN, 0., 0);
		slowmutual[i][j]->parameter[1] = ERever;
		slowmutualA[i][j]->parameter[1] = ERever;
		slowmutual[i][j]->parameter[2] = tauR;
		slowmutual[i][j]->parameter[3] = tauD;
		slowmutualA[i][j]->parameter[2] = tauR;
		slowmutualA[i][j]->parameter[3] = tauD;
				} 
	} 
	
	int          count = 0;
	double       *curr_pre, *curr_post, sumprecur = 0, sumpostcur = 0,Het;
			curr_pre = new double[NN + 10];
		curr_post = new double[NN + 10];
		for (int i = 0; i < NN; i++) {
		curr_pre[i] = Idc + (heter * Idc) / 100 + 0.0 * rg.Random();
		curr_post[i] = Idc + 0.0 * rg.Random();
		sumprecur += curr_pre[i];
		sumpostcur += curr_post[i];
		} 

	/*************Set up for delay conductance ************/
		//double        TDelay = 30;
	double          ConDelInt[NN];
	double          DelayFeedPre[NN], DelayFeedPost[NN];
	for (int i = 0; i < NN; i++)
		ConDelInt[i] = ceil(0.0);
	vector< vector<double> > DelayMatrixPre(NN, vector<double>(NN,0)); 
	 	 vector< vector<double> > DelayMatrixPost(NN, vector<double>(NN,0)); 

		for (int i = 0; i < NN; i++) {
		for (int k = 0; k < ConDelInt[i]; k++)
			DelayMatrixPre[i].push_back(0);
			DelayMatrixPost[i].push_back(0);
	}
	 /*******************parameters for the TwoDsynapse to work********************/ 	double *ref_time_pre,*ref_time_post;
	double        *vnew_pre, *vnew_post, *vold_pre, *vold_post;
	double        *diff_pre, *diff_post;
	int           *bol_pre, *bol_post, *bol_postpre, *bol_prepost;
	ref_time_pre = new double[NN];
	ref_time_post = new double[NN];
	vnew_pre = new double[NN];
	vnew_post = new double[NN];
	vold_pre = new double[NN];
	vold_post = new double[NN];
	diff_pre = new double[NN];
	diff_post = new double[NN];
	bol_pre = new int[NN];
	bol_post = new int[NN];
	bol_prepost = new int[NN];
	bol_postpre = new int[NN];
		for (int i = 0; i < NN; i++) {
	vnew_pre[i] = 0;
	vnew_post[i] = 0;
	vold_pre[i] = neurpre[i]->x[0];
	vold_post[i] = neurpost[i]->x[0];
	bol_pre[i] = bol_post[i] = 0;
	bol_prepost[i] = bol_postpre[i] = 0;	
	}  /*****************************************************************************/ ofstream VoltFile;VoltFile.open(out.c_str(), ios::out);
	
	int             szpreold = 0, szpostold = 0;
	double          sumcurr = 0, sumcurrpost = 0;
	vector < double >PreCurr, PostCurr;
	double          RuleNoise = 0;

	/************************defining variables for learning****************************/
	double          dG, dT, gmutualoldpre, gmutualnewpre, gmutualoldpost,gmutualnewpost;
	int            maxsz, minsz;
	int            maxold = 0, maxnew, minold = 0, minnew;
	int             bul = 0;
	double          tref, tend, phasediff1, phasediff2, phasediff;
	gmutualoldpre = gmutual;
	gmutualnewpre = gmutual;
	gmutualoldpost = gmutual;

double MaxPd=-100;
double MinPd=100;


int bulpdiff=0;

double phasediffold=0,phasediffnew=0;
vector<double>phasevect;
double sumphase=0;
double Delay1=0,Width1=0;
//double feedk1=.5,feedk2=0.1;
double feedWidth=Width2;
double feedDelay=Delay2;

double pold=0;
double DynPeriod;
double expfactor=1;
int SumHist;
double DynResponse;
double feedk1Mod,feedk2Mod;
double bulfeed=0;
int phasevectsize=0;
double nonlinphasefunc=0;
int bullog=0;
	while (tim < endtime) {
		

		pulse = 0;
		pulse0=0;
		pulse1=0;

		if (T[0].size() >2  && TP[0].size() >2)
		{
			DynPeriod=T[0][T[0].size()-1]-T[0][T[0].size()-2];
			DynResponse=TP[0][TP[0].size()-1]-TP[0][TP[0].size()-2];
			feedk1Mod=feedk1;
			feedk2Mod=feedk2;
						
         if (T[0][T[0].size()-1]>TP[0][TP[0].size()-1])
			{        
		 phasediff1=T[0][T[0].size()-1]-TP[0][TP[0].size()-1];
		 pold=phasediff1; bullog=0;		
			}
    	   else
       		{
       		phasediff1=pold;bullog=1;
       		}
		}
phasediffnew=phasediff1;

if (tim>1000)
{
if (abs(phasediffnew-phasediffold)>.1 )
{
sumphase=expfactor*sumphase+1.0*nonlinphasefunc;
}
}
phasediffold=phasediffnew;
nonlinphasefunc=phasediffnew*(sin(2*2*3.14*(phasediffnew)/(DynPeriod+DynResponse)));
	




if (tim<1000)
{
feedk2Mod=0;
feedk1Mod=0;
}

	
	feedDelay=Delay2+.25*feedk1Mod*(phasediffnew+sumphase);
	feedWidth=Width2+0.1*feedk2Mod*(phasediffnew+sumphase);

	if (feedDelay>15)
	feedDelay=15;
	if (feedWidth>15)
	feedWidth=15;
	if (feedDelay<0)
	feedDelay=0;
	if (feedWidth<0)
	feedWidth=0;
	


if (ERever==-75)
{		
			OptoCurr[1]->parameter[2] = 0;
			OptoCurr[0]->parameter[2] = defaultintensity;

		if (T[0].size() >2  && TP[0].size() >2)
		{
		 if (tim>500&tim > T[0][T[0].size() - 1] + feedDelay & tim < T[0][T[0].size() - 1] + feedDelay + feedWidth )
		 {pulse=1;pulse0=1;}
		}
}	

if (ERever==-55)
{		
			OptoCurr[0]->parameter[2] = 0;
			OptoCurr[1]->parameter[2] = defaultintensity;

		if (T[0].size() >2  && TP[0].size() >2)
		{
		 if (tim>500&tim > TP[0][TP[0].size() - 1] + Delay2 & tim < TP[0][TP[0].size() - 1] + Delay2 + Width2 &bulpdiff==0)
		 {pulse=1;pulse1=1;}
		}
}	





//	if (tim>2000 &&tim<4000){
//		for (int i = 0; i < NN; i++) {
//			curr_pre[i]=0.3788;
//		 } 
//	}
//
//	if (tim>=4000 &&tim<6000){
//		for (int i = 0; i < NN; i++) {
//			curr_pre[i]=0.325;
//		 } 
//	}
//	if (tim>=6000 &&tim<8000){
//		for (int i = 0; i < NN; i++) {
//			curr_pre[i]=0.35;
//		 } 
//	}
	
 if (tim > 0 && tim < endtime) {
		for (int i = 0; i < NN; i++) {
		Inputpre[i]->set_I(curr_pre[i]);
		Inputpost[i]->set_I(curr_post[i]);
		 } 
	} for (int i = 0; i < NN; i++) {
			
				DelayFeedPre[i] = DelayBuff(DelayMatrixPre[i], neurpre[i]->x[0]);
				DelayFeedPost[i] = DelayBuff(DelayMatrixPost[i], neurpost[i]->x[0]);
				HH_Run(&tim, neurpre[i], timestep);
				HH_Run(&tim, neurpost[i], timestep);
				IOpto_Run(&tim, OptoCurr[2 * i], pulse0, timestep);
				IOpto_Run(&tim, OptoCurr[2 * i + 1], pulse1, timestep);
				TwoD_Run(&tim, slowself[i][i], neurpre[i]->x[0], timestep);
				TwoD_Run(&tim, slowselfA[i][i], neurpost[i]->x[0], timestep);
			for (int j = 0; j < NN; j++) {
				TwoD_Run(&tim, slowmutual[i][j], DelayFeedPre[i], timestep);
				TwoD_Run(&tim, slowmutualA[i][j], DelayFeedPost[i], timestep);
			} 
		} if (tim > 0) {
			for (int i = 0; i < NN; i++) {
			spiketimes(&tim, &neurpre[i]->x[0], Threshold, bol[i], T[i]);
			spiketimes(&tim, &neurpost[i]->x[0], Threshold, bolp[i], TP[i]);
				
			} 
		}
		
		if (szpreold != T[0].size()) {
			PreCurr.push_back(sumcurr);
			sumcurr = 0;
		}
		sumcurr += Idc + (heter * Idc) / 100 + slowself[0][0]->Isyn() + slowmutualA[0][0]->Isyn();
		szpreold = T[0].size();

		if (szpostold != TP[0].size()) {
			PostCurr.push_back(sumcurrpost);
			sumcurrpost = 0;
		}
		sumcurrpost += Idc + slowselfA[0][0]->Isyn() + slowmutual[0][0]->Isyn();
		szpostold = TP[0].size();
		if (Learnpresent == 1) {
			dG = 0;
			for (int u = 0; u < NN; u++)
			for (int v = 0; v < NN; v++) {
			maxsz = max(T[u].size(), TP[v].size());
			minsz = min(T[u].size(), TP[v].size());
			maxnew = maxsz;
			minnew = minsz;
		if (maxnew != maxold || minnew != minold) {
		if (TP[v].size() > 0 && T[u].size() > 0)
			dT = TP[v][TP[v].size() - 1] - T[u][T[u].size() - 1];
		else
			dT = -1000;
			dG = RuleInhib(dT, 10, 1, 10, 1, .005);
					} 		gmutualnewpre = gmutualoldpre - dG;
	if (gmutualnewpre < 0)
	gmutualnewpre = 0;
	gmutualnewpost = gmutualoldpost + dG;
	if (gmutualnewpost < 0)
	gmutualnewpost = 0;
	slowmutual[u][v]->parameter[0] = gmutualnewpre;
	slowmutualA[u][v]->parameter[0] = 0.0 * gmutualnewpost;
				} 	maxold = maxnew;
	minold = minnew;
		} else;
		gmutualoldpre = gmutualnewpre;
		gmutualoldpost = 0.0 * gmutualnewpost;
		count += 1;
		
		if (tim>1500)
		{
		MaxPd=MAX(phasediff1,MaxPd);
		MinPd=MIN(phasediff1,MinPd);
		}
		if (scale == 2) {
			if (tim > 1000)
			VoltFile << tim << " " << neurpre[0]->x[0] << " " << neurpost[0]->x[0] << " " << sumphase << " " << pulse0 << " " <<  phasediff1<<" "<<nonlinphasefunc<<" "<<feedDelay<<" "<<feedWidth<<" "<<DynPeriod<<" "<<DynResponse<<" "<<.25*feedk2Mod*(phasediffnew)+.25*feedk1Mod*(sumphase)<<" "<<Inivariable<<endl;
			}
				tim += epsilon;
	} 

		VoltFile.close();
	int             SzNum = MIN(T[0].size(), TP[0].size());
	Outfile1.open((char *) SpikeTimeFile.c_str(), ios::out);
	for (int i = 0; i < T[0].size(); i++)
	Outfile1 << T[0][i] << endl;
	Outfile1 << -1000 << endl;
	for (int i = 0; i < TP[0].size(); i++)
	Outfile1 << TP[0][i] << endl;
	Outfile1.close();
	
		vector < double >Periodpre, Periodpost;
		double Avgperiodpre, Avgperiodpost;
		double sumpree = 0, sumposte = 0;
		for (int i = 0; i < NN; i++) {
		Periodpre.push_back(ISI(T[i],1000.0));
		Periodpost.push_back(ISI(TP[i],1000.0));
		}
	for (int i = 0; i < NN; i++) {
	sumpree += Periodpre[i];
	sumposte += Periodpost[i];
	} 	Avgperiodpre = sumpree / NN;
	Avgperiodpost = sumposte / NN;	

double Finalphase=MIN(phasediff1,fabs(Avgperiodpre-phasediff1));

time(&end1);
	double         diff = difftime(end1, start);
	delete         *neurpre; delete *neurpost;delete *Inputpre;delete *Inputpost;delete **coupAB;	   delete           **coupBA; delete **slowself; delete **slowselfA; delete **slowmutual;	      delete        **slowmutualA;	delete[] neurpre;	delete[] neurpost;	delete[] Inputpre;	delete[] Inputpost;	delete[] coupAB;	delete[] coupBA;	delete[] slowself;	delete[] slowselfA;	delete[] slowmutual;	delete[] slowmutualA;	delete[] ref_time_pre;	delete[] ref_time_post;	delete[] vnew_pre;	delete[] vnew_post;	delete[] vold_pre;	delete[] vold_post;	delete[] diff_pre;	delete[] diff_post;	delete[] bol_pre;	delete[] bol_post;	delete[] bol_postpre;	delete[] bol_prepost;        delete[] T;        delete []TP;        delete []bol;        delete []bolp;			return 0;}
