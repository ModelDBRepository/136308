#--------------------------------------------------------------------------
# Author: Sachin Talathi
#
#--------------------------------------------------------------------------

C++ = g++
RM= rm -rf
HOME= ../../../simul_lrn
HOMECC=../../../C++HH/
INCLUDE= -I$(HOME)/numlib -I$(HOME)/datalib
INCLUDE1=-I$(HOMECC)
IN=-I$(HOMECC)runOpto
runOpto:  HHOpto.o rk4.o Rose.o modelRose.o Connectivity.o Neuron.o Synapse.o Ionchannel.o modelHHneuron.o HHneuron.o Calciumchannel.o mersenne.o  Couplingcurrent.o TwoDsynapse.o modelTwoDsynapse.o Henrysynapse.o modelHenrysynapse.o modelIOpto.o IOpto.o modelMinneuron.o Minneuron.o

	$(C++) -g -Wall -o runOpto HHOpto.o rk4.o Rose.o modelRose.o Connectivity.o Neuron.o Synapse.o Ionchannel.o modelHHneuron.o HHneuron.o Calciumchannel.o mersenne.o Couplingcurrent.o TwoDsynapse.o modelTwoDsynapse.o Henrysynapse.o modelHenrysynapse.o modelIOpto.o IOpto.o modelMinneuron.o Minneuron.o
	
HHOpto.o: HHOpto.cc 
	 $(C++)  -c  -Wall -g $(INCLUDE) HHOpto.cc -Wno-deprecated
 
Neuron.o: $(HOMECC)Neuron.cc 
	$(C++)  -c -Wall -g $(INCLUDE) $(HOMECC)Neuron.cc -Wno-deprecated

Synapse.o: $(HOMECC)Synapse.cc 
	$(C++)  -c -Wall -g $(INCLUDE) $(HOMECC)Synapse.cc -Wno-deprecated

Ionchannel.o: $(HOMECC)/Ionchannel.cc 
	$(C++)  -c -Wall -g $(INCLUDE) $(HOMECC)/Ionchannel.cc -Wno-deprecated

HHneuron.o: $(HOMECC)HHneuron/HHneuron.cc 
	$(C++)  -c -Wall -g $(INCLUDE) $(HOMECC)HHneuron/HHneuron.cc -Wno-deprecated

Minneuron.o: $(HOMECC)Minneuron/Minneuron.cc 
	$(C++)  -c -Wall -g $(INCLUDE) $(HOMECC)Minneuron/Minneuron.cc -Wno-deprecated	
		
Rose.o: $(HOMECC)Rose/Rose.cc 
	$(C++)  -c -Wall -g $(INCLUDE) $(HOMECC)Rose/Rose.cc -Wno-deprecated	
	
rk4.o: $(HOMECC)rk4.cc 
	$(C++)  -c -Wall -g $(HOMECC)rk4.cc -Wno-deprecated
	
Connectivity.o: $(HOMECC)Connectivity.cc 
	$(C++)  -c -Wall -g $(HOMECC)Connectivity.cc -Wno-deprecated	

modelHHneuron.o: $(HOMECC)HHneuron/modelHHneuron.cc 
	$(C++)  -c -Wall -g $(HOMECC)HHneuron/modelHHneuron.cc -Wno-deprecated

modelMinneuron.o: $(HOMECC)Minneuron/modelMinneuron.cc 
	$(C++)  -c -Wall -g $(HOMECC)Minneuron/modelMinneuron.cc -Wno-deprecated

modelRose.o: $(HOMECC)Rose/modelRose.cc 
	$(C++)  -c -Wall -g $(HOMECC)Rose/modelRose.cc -Wno-deprecated

Calciumchannel.o: $(HOMECC)Calciumchannel.cc 
	$(C++) -c -Wall -g $(INCLUDE) $(HOMECC)Calciumchannel.cc -Wno-deprecated

mersenne.o: $(HOMECC)mersenne.cc 
	$(C++) -c -Wall -g $(HOMECC)mersenne.cc -Wno-deprecated

Couplingcurrent.o: $(HOMECC)Couplingcurrent/Couplingcurrent.cc 
	$(C++)  -c -Wall -g $(HOMECC)Couplingcurrent/Couplingcurrent.cc -Wno-deprecated

TwoDsynapse.o: $(HOMECC)TwoDsynapse/TwoDsynapse.cc 
	$(C++)  -c -Wall $(INCLUDE) $(HOMECC)TwoDsynapse/TwoDsynapse.cc -Wno-deprecated

modelTwoDsynapse.o: $(HOMECC)TwoDsynapse/modelTwoDsynapse.cc 
	$(C++)  -c -Wall $(HOMECC)TwoDsynapse/modelTwoDsynapse.cc -Wno-deprecated
	
Henrysynapse.o: $(HOMECC)Henrysynapse/Henrysynapse.cc 
	$(C++)  -c -Wall $(INCLUDE) $(HOMECC)Henrysynapse/Henrysynapse.cc -Wno-deprecated

modelHenrysynapse.o: $(HOMECC)Henrysynapse/modelHenrysynapse.cc 
	$(C++)  -c -Wall $(HOMECC)Henrysynapse/modelHenrysynapse.cc -Wno-deprecated	

modelIOpto.o: $(HOMECC)IOpto/modelIOpto.cc 
	$(C++)  -c -Wall $(INCLUDE) $(HOMECC)IOpto/modelIOpto.cc -Wno-deprecated

IOpto.o: $(HOMECC)IOpto/IOpto.cc 
	$(C++)  -c -Wall $(INCLUDE) $(HOMECC)IOpto/IOpto.cc -Wno-deprecated

 clean:
	$(RM) *.o 
