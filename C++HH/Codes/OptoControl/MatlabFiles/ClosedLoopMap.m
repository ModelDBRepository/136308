function [delta x u0 v0 f TA TB]=ClosedLoopMap(delta0,deltaold,x0,c,Heter)
%d0->Initidal Phase difference
%x0->Initial value of PI controller parameter
%u0-> Initial delay value for light stim
%v0-> Initial width of light stim pulse
%a,b,c,d->Closed loop control parameters
%ginhib->UCI network synaptic strength
%ER->UCI network reversal potential
%Heter->Heterogeneity in UCI network
%Note: In  simulation at the command prompt the values a=b=c=d=2.35
delta=[];x=[];u0=[];v0=[];f=[];TA=[];TB=[];


ginhib=0.15;
ER=-75;

tau_star=5.5;
W_star=3.92;
%alpha=0.995;
alpha=1;
IA0=0.5;
IB0=IA0*(1+Heter/100);
%load('./MatlabFiles/GainFn.mat');
load('GainFn.dat');

%TA0=GF(IA0);
TA0=31.038;
ind=find(GainFn==Heter);

TB0=GainFn(ind,3);

u0=tau_star+0.25*c*(delta0+x0);
v0=W_star+0.1*c*(delta0+x0);

% if (delta0>TA0)
%     delta0=TA0-delta0;
% end

% if (delta0>TA0)
%     bul=0;
% else
%     bul=1;
% end
% 
% if (bul==0)
%     delta=0;
%     x=0;
%     TA=0;
%     TB=0;
%     f=0;
% end
% 
% if (bul==1)

    if (u0>15)
        u0=15;
    end

    if (u0<0)
        u0=0;
    end
    if (v0>15)
        v0=15;
    end

    if (v0<1)
        v0=1;
    end

   if (ER==-75)
        %     [cp1 cp2 cp3 Phi flag]=GetSTRCFit(ginhib,IA0,ER,2,1);
        %        load ./MatlabFiles/Phi_ER-75_g0.15_Idc0.5.mat
        %     File=strcat('./MatlabFiles/Phi_ER-75_g',num2str(ginhib),'_Idc',num2str(IA0),'.mat');
        %     load (File);
        %     TA=TA0*(1+cp1(delta0)+cp2(deltaold));
        %
          cmd_prc=sprintf('%s %s %s %s %s %s %s %s %s\n','./run_PRC 1200',num2str(IA0),'0',num2str(ginhib),'0 2 .1',num2str(ER),num2str(delta0),'1600 TempPRC.dat');
        system(cmd_prc);
        DataPRC=load('./TempPRC.dat');
        P1=(DataPRC(:,2)-DataPRC(:,6))./DataPRC(:,6);
        P2=(DataPRC(:,3)-DataPRC(:,6))./DataPRC(:,6);
        TA=TA0*(1+P1+P2)-.05;
        
        cmd=sprintf('%s %s %s %s %s %s %s\n','./runOpto 1500',num2str(IB0),'.75 0 0.01 1',num2str(v0),'100 2 ./Temp.dat',num2str(u0),num2str(u0));
        %cmd=sprintf('%s %s %s %s %s %s %s\n','../OptoStimProject/runOpto 1500',num2str(IB0),'.75 0 0.01 1',num2str(x(1)),'100 2 ../OptoStimProject/Temp.dat',num2str(tau),num2str(tau));
        system(cmd);
        Data=load('./Temp.dat');
        TB=Data(:,9);

        delta=delta0+TB-TA;
        f=delta0*sin((4*pi*delta0)/(TB+TA));

%       if (abs(delta0)>0.125)    
        x=alpha*x0+f;
        %else
         %  x=x0;
       %end
        
        %else
         %   x=x0;
        %end

    end
%end