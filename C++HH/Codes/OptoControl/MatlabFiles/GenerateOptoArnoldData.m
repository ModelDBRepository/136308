
%options=optimset('TolFun',1e-10,'MaxFunEvals',1000,'MaxIter',100,'PlotFcns',@optimplotfval);
options=optimset('TolFun',1e-10,'MaxFunEvals',1000,'MaxIter',100);
SyncFile='./Data/Data-Fig7/Sync_Mod_E123T.dat';
%S=load(SyncFile);
for g=0.15:.01:.15
    for Heter=-50:1:0
%         Test=[g Heter]
% a1=5+3*rand(1,1);
% a2=5+3*rand(1,1);
% x=[a1 a2];
% 
% x=fminsearch(@(x)CostFnForSync(x,g,-75,Heter),x,options); 
% if (min(x)<0)
%     lb=[0 0];
%     ub=[20 20];
%     x=[a1 a2];
%     x=fminsearchbnd(@(x)CostFnForSync(x,g,-75,Heter),x,lb,ub); 
% end
% ind=find(S(:,2)==Heter);
% x=[S(ind,3) S(ind,4)]; %x(1)=W; x(2)=tau

x=[3.92 5.5];
RasterFile=strcat('./Data/Data-Fig7/Raster_E123T_',num2str(g),'_',num2str(Heter),'.dat');
%RasterFile='Raster.dat';
cmd=sprintf('%s %s %s %s %s %s %s %s %s %s %s\n','./run_slow_compute 1 7000',num2str(Heter),'.5 0',num2str(g),'0 2 .1 -75 0 0 0',...
SyncFile,RasterFile,'0.75 0 .01 1 1 100 2',num2str(x(1)),num2str(x(2)),'0. 0. .01');
disp(cmd)
system(cmd);
    end
end



