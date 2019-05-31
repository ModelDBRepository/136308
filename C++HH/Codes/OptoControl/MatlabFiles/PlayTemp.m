clear
count=1;
countTher=1;
%figure(1);
%hold on;
load('./MatlabFiles/GainFn.mat');
NumPhase=[];
NumHet=[];

ER=-75;
Delay=0;
countH=0;
figure;

for H=-50:0
    H
    countH=countH+1;
     File=strcat('./Data/Data-Fig6D/Raster_E123T_0.15_',num2str(H),'.dat');%case 1
    % File=strcat('./Data/Data-Fig7/Raster_E123T_0.15_',num2str(H),'.dat');% case 2
     %File=strcat('./Data/Data-Fig5/FastUniDirecER',num2str(ER),'_g0.15_Delay',num2str(Delay),num2str(H),'.dat');%case 3
    %File=strcat('./Data/Data-Fig12/Raster-Set2_H-30_c0.3',num2str(H),'.dat'); %case 4
    Z=load(File);
    
    [D Period]=Phase_PPK(Z,6000);
    
    if (std(D)<.3)
     NumPhase(count)=D(1);
     NumHet(count)=H;
     count=count+1;
    end

    Phase(countH).D=D;
    Period_Rec(countH,:)=Period;
    HetRec(countH)=H;
        if (~isempty(D))
    if (std(D)<.2 )
        if (D(1)<2)
        D(1)=0.1*rand(1,1);
        end
 plot(H,D(1),'.k','markersize',25)
    else
 plot(H,D,'.k')
    end        
    end
    hold on
  plot(HetRec(countH),10.*Period_Rec(countH,2)./Period_Rec(countH,1),'.r','markersize',20);
%        % plot((TB-31.05)./31.05,D,'.r')
%     FP=ShuntingMapFP(0.5,H,0.15,-75,2,0);
%     if (FP~=-1000)
%     TherPhase(countTher)=FP;
%     HetTher(countTher)=H;
%     countTher=countTher+1;
%     end

end
% hold on
% plot(HetTher,TherPhase,'.r','markersize',25)
% axis tight
% set(gca,'fontsize',25,'fontweight','bold')



% figure;
% for i=2:length(Phase)
%     H=-51+i
%     if (max(Phase(i).D)<=1)
%         Data=min(Phase(i).D)-.2;
%         if (Data<0)
%             Data=0.1;
%         end
%     plot(H,Data,'.k','markersize',25)
%     else
%         plot(H,Phase(i).D,'.k')
%     end
%     hold on
% end
% count=0;
% for H=-50:0
% FP=ShuntingMapFP(0.5,H,0.15,-75,2,0);
% if (FP~=-1000)
%     count=count+1;
%     TherPhase(count)=FP;
%     TherHet(count)=H;
% end
% end
