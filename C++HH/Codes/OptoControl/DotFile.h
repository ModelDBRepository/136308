#ifndef _CreateDotFile_
#define _CreateDotFile_
#include "define.h"

void CreateGraphDotFile(string output,int NN,Connectivity &CC,double gself,double gcoup, string Type)
{
ofstream Z;
vector<string> DotText;
string A, B,C,label;
string gselfcond=DoubleToStdStr(gself);
string gcoupcond=DoubleToStdStr(gcoup);
Z.open((char *)output.c_str(),ios::out);
DotText.push_back("Digraph {");
for (int i=0;i<NN;i++)
for (int j=0;j<NN;j++)
{
if (CC.Twodarray[i][j]==1 )
{
A=IntToStdStr(i);
B=IntToStdStr(j);
if (i==j)
{
if (Type=="Synapse")
label=" [label=\""+gselfcond+"\"] ";
else if (Type=="Elec")
label=" [arrowhead=none,label=\""+gselfcond+"\"] ";
else;
C=A+" -> "+B+label+";";
}
else
{
if (Type=="Synapse")
label=" [label=\""+gcoupcond+"\"] ";
else if (Type=="Elec")
label=" [arrowhead=none,label=\""+gcoupcond+"\"] ";
else;
C=A+" -> "+B+label+";";
	
	
	}

//else if (Type=="Elec")
//C=A+" -> "+B+" [arrowhead=none];";
DotText.push_back(C);
}
}

DotText.push_back("}");

for (unsigned int i=0;i<DotText.size();i++)
Z<<DotText[i]<<endl;
Z.close();

string outfile="Graph_"+Type+".png";
string cmd="dot -Tpng "+output+ " -o "+outfile;
system((char *)cmd.c_str());

}
#endif