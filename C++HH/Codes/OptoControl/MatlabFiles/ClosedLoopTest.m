%close all
delta0=5;x0=0;u0=3.;v0=1;
deltaold=delta0;
Heter=-24.25;
c=0.3
count=0;


IA0=0.5;
%load('./MatlabFiles/GainFn.mat');
%TA0=GF(IA0);
TA0=31.038;

for i=1:150
%         if (i>75)
%             Heter=-24.25;
%         end
%         if (i>150)
%             Heter=-35;
%         end
%         if (i>225)
%             Heter=-30;
%         end

    figure(2);
    if (delta0>-.1 & delta0<=TA0)
    [delta x u v f TA TB]=ClosedLoopMap(delta0,deltaold,x0,c,Heter);
    deltaold=delta0;
    
    delta0=delta;
    if (delta<0)
        delta0=TA0+delta;
    end
    if (delta>TA0)
        delta0=delta-TA0;
    end
    
    end
    
%     if (delta0<0.125)
%         delta0=0.05;
%     end
    
    x0=x;
Dis(i,:)=[i delta x f u v TA TB]


    subplot(2,1,1);plot(i,abs(min(delta,TA-delta)),'.b','markersize',20);
    %set(gca,'fontsize',20,'fontweight','bold','xtick',[ ],'ytick',[0:7.5:30]);
    %axis tight
    hold on
    subplot(2,1,2);plot(i,x,'.k','markersize',20);
    %set(gca,'fontsize',20,'fontweight','bold','xtick',[ ]);
   % axis tight
    hold on

%     subplot(4,1,3); plot(i,TA,'.r','markersize',20);
%     hold on
%     plot(i,TB,'.b','markersize',15);
%    set(gca,'fontsize',20,'fontweight','bold','xtick',[ ],'ylim',[30 50]);
%     axis tight
% 
%     subplot(4,1,4);plot(i,u,'.b','markersize',20);
%     hold on
%     plot(i,v,'.g','markersize',15);
%    set(gca,'fontsize',20,'fontweight','bold','ylim',[3 6],'ytick',[3:1.5:6],'xtick',[0:40:160]);
%     
    
end