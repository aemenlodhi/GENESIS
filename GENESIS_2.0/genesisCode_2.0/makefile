
NetSim: NetSim.o
	g++ NetSim.o -o NetSim

#GENESIS.o: GENESIS.cpp GENESIS.h globalVars.h
#	g++ -c GENESIS.cpp

NetSim.o: NetSim.cpp NetSim.h globalVars.h
	g++ -c -O2 NetSim.cpp

#Statistics.o: Statistics.cpp Statistics.h
#	g++ -c Statistics.cpp 

clean:	
	rm -f *.o NetSim
