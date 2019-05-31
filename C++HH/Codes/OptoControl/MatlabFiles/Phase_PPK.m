function [D Period]=Phase_PPK(Z,Transient)
%[H D Period]=Phase_Het(Z) 
%Z is the Raster Data for two neurons in format 
%Spikes from Neuron 1- Seperator (-1000)- Spikes from Neuron 2

%[H D Period]=Phase_Het(H,ER,Delay,DecayTime)-Old Call
%function [g meandG]=Phase_Het(g,Learn)

D=[];
Pre=[];
Post=[];
TPost=0;
TPre=0;



% %File=strcat('./PhaseCalc/Phase',num2str(H),'.dat');
%  
% %This is done for case of ER=-60 my first calculations
% %{
% if (Delay==0)
% File=strcat('./PhaseCalc/Old/SlowUniDirec_g0.15_NoDelay',num2str(H),'.dat');
% else
%     File=strcat('./PhaseCalc/Old/SlowUniDirec_g0.15_Delay',num2str(Delay),num2str(H),'.dat');
% end
% %}
% if (DecayTime==8)
%     File=strcat('./PhaseCalc/SlowUniDirecER',num2str(ER),'_g0.15_Delay',num2str(Delay),num2str(H),'.dat');
% elseif (DecayTime==2)
%     File=strcat('./PhaseCalc/FastUniDirecER',num2str(ER),'_g0.15_Delay',num2str(Delay),num2str(H),'.dat');
% else
% end
% 
% 
% fid=fopen(File);

% if (fid~=-1)
%     fclose(fid);
%     Z=load(File);


    ind=find(Z==-1000);
    Pre=Z(1:ind-1);
    Post=Z(ind+1:end);

    ind=find(Pre>Transient);
    Pre=Pre(ind);

    ind=find(Post>Transient);
    Post=Post(ind);
    TPost=mean(diff(Post));
    TPre=mean(diff(Pre));
% end

Period=[TPre TPost];

%if (TPost<=TPre)

        for i=1:length(Post)-1
            ind=find(Pre>=Post(i)&Pre<Post(i+1));
          
            if(~isempty(ind))
           % D(i)=Pre(ind)-Post(i);
                D(i)=(Pre(ind(1))-Post(i))/(Post(i+1)-Post(i));
           if (D(i)>0.5)
               D(i)=1-D(i);
           end
         D(i)=TPre.*D(i); 
            

            end
            end
   % end

%     if (TPost>TPre)
% 
%         for i=1:length(Pre)-1
% 
%             ind=find(Post>=Pre(i)&Post<Pre(i+1));
%          
%             if (~isempty(ind))
%             %D(i)=Pre(ind)-Post(i);                
%             D(i)=mod((-Post(ind(1))+Pre(i))/(Pre(i+1)-Pre(i)),1.0);
%             if (D(i)>0.5)
%                D(i)=1-D(i);
%             end
%             D(i)=TPost.*D(i);
%             end
%            end
%    end


    %meandG=mean(dGOut);

