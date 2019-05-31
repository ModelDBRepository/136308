*******************README FOR Control of Neural Synchrony Using Channelrhodopsin-2, article tobe published in JCNS 2010*********************
Date 11/30/10 :

This directory contains all the source codes and other aasociated file for implementing the code and generating figures reported in the JCNS-2010 article titled:
Control of Neural Synchrony Using Channelrhodopsin-2-A Computational Study

The two main folders containing all the essential libraried are ./C++HH and ./simul_lrn (Do not change or touch any of the libraries in these folders)

The main codes are in directory ./C++HH/Codes/OptoControl/
This folder also includes the folder MatlabFiles containing all the relevant matlab scripts as well as the data that was used to generate the figures

There are 3 main C++ files. 
1)HHOpto.cc
2)PRC.cc
3)Test_Slow_Syn.cc

The corresponding executables are
1) runOpto
2) run_PRC
3) run_slow_compute

The Makefiles used to create the above executables (compiled on IMAC running i686-apple-darwin10-gcc-4.2.1) are 
1) MakeOpto.f
2) Make_PRC.f
3) Make_Inhib_Slow.f

All the functions required in above above C++ codes are in define.h and defineOpto.h file.

The key Matlabfiles to generate the figures are

1) PlayTemp.m -Creates the Phaseplots of time evolution of delta_n as function of H for various cases presented in the paper
2) CloseLoopTest.m- Does the nonlinear map calculations for closedloop control


The full differential equation for the UCI network in the presence of the closed loop control is implemented in Test_Slow_Syn.cc


-Sachin S Talathi
Assistant Professor
Dept of Pediatrics, Biomedical Engineering and Neuroscience
Univ of Florida

