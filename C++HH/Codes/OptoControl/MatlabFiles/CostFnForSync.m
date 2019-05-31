function [Err L R]=CostFunForSync(x,ginhib,ER,Heter)
%[Err L R]=CostFunForSync(x,ginhib,ER,Heter)
%x=[Width Tau]

%New: Trying to Use PRCs to design the controller

%Network B->A

Err=[];
%Heter=35;
IA0=0.5;
IB0=IA0*(1+Heter/100);
% load('./MatlabFiles/GainFn.mat');
% TA0=GF(IA0);
% TB0=GF(IB0);

IA0=0.5;
IB0=IA0*(1+Heter/100);
%load('./MatlabFiles/GainFn.mat');
load('GainFn.dat');

%TA0=GF(IA0);
TA0=31.038;
ind=find(GainFn==Heter);

TB0=GainFn(ind,3);



%[cp1 cp2 cp3 Phi]=GetSTRCFit(0.15,0.5,-75,2,0); %The neurons coupled unidirectionally with inhibitory synapse with g=0.15;ER=-75

if (ER==-75)
% [cp1 cp2 cp3 Phi flag]=GetSTRCFit(ginhib,IA0,ER,2,1);
%    load ./MatlabFiles/Phi_ER-75_g0.15_Idc0.5.mat
% File=strcat('./MatlabFiles/Phi_ER-75_g',num2str(ginhib),'_Idc',num2str(IA0),'.mat');
% load (File);
% R=TA0/TB0*(1+cp1(0)+cp2(0))-1;

cmd_prc=sprintf('%s %s %s %s %s %s %s %s %s\n','./run_PRC 1200',num2str(IA0),'0',num2str(ginhib),'0 2 .1',num2str(ER),num2str(0),'1600 TempPRC.dat');
    system(cmd_prc);
    DataPRC=load('./TempPRC.dat');
    P1=(DataPRC(:,2)-DataPRC(:,6))./DataPRC(:,6);
    P2=(DataPRC(:,3)-DataPRC(:,6))./DataPRC(:,6);
    TA=TA0*(1+P1+P2);
R=TA/TB0-1;


cmd=sprintf('%s %s %s %s %s %s %s\n','./runOpto 1500',num2str(IB0),'.75 0 0.01 1',num2str(x(1)),'100 2 ./Temp.dat',num2str(x(2)),num2str(x(2)));
%cmd=sprintf('%s %s %s %s %s %s %s\n','./runOpto 1500',num2str(IB0),'.75 0 0.01 1',num2str(x(1)),'100 2 ./Temp.dat',num2str(tau),num2str(tau));
system(cmd);
Data=load('../OptoStimProject/Temp.dat');
L=(Data(:,9)-Data(:,7))./Data(:,7);

end

if (ER==-55)
load ./MatlabFiles/Phi_ER-55_g0.15_Idc0.5.mat
R=TB0/TA0*(1+cp1(0)+cp2(0))-1;
cmd=sprintf('%s %s %s %s %s %s %s\n','./runOpto 1500',num2str(IA0),'.75 0 0.01 1',num2str(x(1)),'100 2 ./Temp.dat',num2str(x(2)),num2str(x(2)))
system(cmd);
Data=load('./Temp.dat');
L=(Data(:,9)-Data(:,7))./Data(:,7);


end

%TestOut=[TB0*(R+1) Data(:,9)]


Err=abs(L-R); 



