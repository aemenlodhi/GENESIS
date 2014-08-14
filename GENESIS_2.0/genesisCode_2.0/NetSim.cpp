//============================================================================
// Name        : Network.cpp
// Author      : Aemen Lodhi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "NetSim.h"
using namespace std;


int main(int argc, char** argv){

	if(argc<16 || argc>16){
		cout<<"Usage: maxNodes maxRegions maxIterations maxTraffic runId sZetaTrafficGen sZetaTrafficCon sZetaGeography priceDependancy seed setNumber initNodes sigma playOrderSeed initialTopologySeed"<<endl;
		exit(-1);
	}

	cout.precision(dbl::digits10);
	char logFileName[50];
	char resultLogFileName[50];
	int numProviders=0;
	bool providerChange=true;
	bool peeringChange=true;
	bool depeeringChange=true;
	bool strategyChange=true;

	//log file
	sprintf(logFileName,"logRun_%d.txt",atoi(argv[5]));
	logFile.open(logFileName);

#if RESULTLOG
	//result logFile
	sprintf(resultLogFileName,"resultLog_%d_%d_%d.txt",atoi(argv[10]),atoi(argv[14]),atoi(argv[15]));
	resultLogFile.open(resultLogFileName);
#endif

#if SNAPSHOT
	//snapShot file
	char snapshotFileName[50];
	sprintf(snapshotFileName,"snapshot.txt");
	snapshotFile.open(snapshotFileName);
#endif
	int stackelbergLeader=-1;
	maxNodes=atoi(argv[1]);
	maxRegions=atoi(argv[2]);
	maxIterations=atoi(argv[3]);
	maxTraffic=static_cast<double>(atoi(argv[4]));
	sZetaTrafficGen=atof(argv[6]);
	sZetaTrafficCon=atof(argv[7]);
	sZetaGeography=atof(argv[8]);
	priceDependancy=atoi(argv[9]);
	mySeed=atoi(argv[10]);
	playOrderSeed=atoi(argv[14]);
	initialTopologySeed=atoi(argv[15]);
	initNodes=atoi(argv[12]);
	universalSigma=atof(argv[13]);
	activeNodes=initNodes;
	maxIterations=1000;
	bool stepChange=false;

	//seed setting
	if(mySeed==-1){
		playOrderSeed=time(NULL);
		initialTopologySeed=time(NULL);
		mySeed=time(NULL);
	}
	srand(mySeed);

#if DEBUG
	logFile<<"Seed used: "<<mySeed<<endl;
#endif


#if DEBUG
	cout<<"MaxNodes: "<<maxNodes<<" InitNodes: "<<initNodes<<" MaxRegions: "<<maxRegions*maxRegions<<" MaxIterations: "<<maxIterations<<" sigma: "<<universalSigma<<endl;
	logFile<<"MaxNodes: "<<maxNodes<<" InitNodes: "<<initNodes<<" MaxRegions: "<<maxRegions*maxRegions<<" MaxIterations: "<<maxIterations<<" sigma: "<<universalSigma<<endl;
#endif

	//*********** Initialize ************//
	initialize();

/*
#if RESULTLOG
	measureOneTime();
#endif
*/

#if SNAPSHOT
	snapShot();		//take a snapshot of the initial network
#endif

	//*********** Routing after initial random topology has been established ************//
	routingScale();
	updateVt();

	//*********** Update fitness for all networks in the initial topology **************//
	for(int i=0;i<activeNodes;i++)
		aliveNodes[i].updateFitness();

#if DEBUG

	logFile<<endl<<"After Initialization"<<endl;
	//displayTrafficMatrix();
	displayNodeData();
	displayTopology();
	//displayRouteData();

#endif

	updateNetworkCategories();

	for(int q=0;q<activeNodes;q++){

		if(aliveNodes[q].category[1]==1 || aliveNodes[q].category[2]==1){
			aliveNodes[q].isMajorContentNet=true;
		}

		if(aliveNodes[q].category[1]==1){
			aliveNodes[q].isCP=true;
		}

		if(aliveNodes[q].category[2]==1){
			aliveNodes[q].isCC=true;

		}

	}

	//log initial topology statsu
	printLog(-1);

	//Iterations begin
	permute(false,playOrderSeed);
	while(iterations<maxIterations){

#if DEBUG
		cout<<endl<<endl<<"********** Iterations "<<iterations<<" ************"<<endl;
		logFile<<endl<<endl<<"********** Iterations "<<iterations<<" ************"<<endl;
#endif

		//reset step change marker
		stepChange=false;

		//permute(false,-1);
		refillNodeOrder();
		while((steps=getNewIt())!=-1){

#if DEBUG
			cout<<endl<<endl<<"********** Round "<<numSimulations<<" ************"<<endl;
			cout<<endl<<endl<<"********** Iterations "<<iterations<<" ************"<<endl;
			cout<<endl<<endl<<"********** Step "<<steps<<" ************"<<endl;
			logFile<<endl<<endl<<"********** Step "<<steps<<" ************"<<endl;
#endif

			//********** Steps to be carried out in each iteration ***********
			/*
			 * 1- De-peer with any non-qualifying peers
			 * 2- Get new peers
			 * 3- Get new provider
			 *
			 */

			//strategy change
			strategyChange=false;

			if(!aliveNodes[steps].I.empty() && numSimulations>0){
				strategyChange=aliveNodes[steps].updatePeeringStrategy();
				if(strategyChange){
#if DEBUG
					logFile<<" Node "<<steps<<" switched strategy to "<<aliveNodes[steps].peeringStrategyNumber<<endl;
#endif
				}
			}

			else{
				if(aliveNodes[steps].I.empty() && aliveNodes[steps].peeringStrategyNumber!=1){
					aliveNodes[steps].selectPeeringStrategy(1);
					strategyChange=true;
				}
			}


			//dePeer
			depeeringChange=false;
			if(!aliveNodes[steps].K.empty())
				depeeringChange=aliveNodes[steps].dePeer(-1);

			if(depeeringChange){
				routingScale();
				updateVt();
#if DEBUG
				logFile<<"**** Displaying status after depeering***"<<endl;
				displayTopology();
				//displayRouteData();
#endif
			}

			//get new peer
			peeringChange=false;
			peeringChange=aliveNodes[steps].getNewPeer(-1);

			if(peeringChange){
				routingScale();
				updateVt();
#if DEBUG
				logFile<<"**** Displaying status after peering***"<<endl;
				displayTopology();
				//displayRouteData();
#endif
			}

			//get new provider
			providerChange=false;
			providerChange=aliveNodes[steps].getNewProvider();

			if(providerChange && aliveNodes[steps].QPrev!=aliveNodes[steps].Q){
				routingScale();
				updateVt();
#if DEBUG
				logFile<<"Node "<<steps<<" switched provider to "<<aliveNodes[steps].Q<<endl;
				logFile<<"**** Displaying status after provider change***"<<endl;
				displayTopology();
				//displayTopology();
				//displayRouteData();
#endif
			}

			if(strategyChange==true || providerChange==true || peeringChange==true || depeeringChange==true){

				stepChange=true;

				for(int i=0;i<activeNodes;i++)
					aliveNodes[i].updateFitness();

			}

		}//end steps while loop

		if(stepChange==true){

			recordNetworkMetrics(numSimulations,iterations);

			iterations++;

			//if(iterations>25){	//high likelihood of oscillation

				//logOscillation(iterations-1);

				//kill switch
				if(iterations>25){

					ofstream oscillationFile;
					oscillationFile.open("oscillation.txt", ios::out | ios::app);
					oscillationFile<<mySeed<<"\t"<<initialTopologySeed<<"\t"<<playOrderSeed<<endl;
					oscillationFile.close();

					goto endSimulation;

				}

			//}

		}

		else{	//system reached equilibrium or simulation terminated

			endSimulation:

			//recordNetworkMetrics(numSimulations,iterations);

			if(numSimulations<3){	//equilibrium

				cout<<"System reached equilibrium "<<numSimulations<<" after "<<iterations<<" iterations"<<endl;
				logFile<<"System reached equilibrium "<<numSimulations<<" after "<<iterations<<" iterations"<<endl;


				//record statistics and log
				recordFitness(numSimulations);
				measureTopologicalMetrics(numSimulations);
				//recordStrategyDistribution(numSimulations);

				//print stats
				printLog(numSimulations);
				/*
				printTopologyStats();
				printPeeringLinkClassification(numSimulations+1);
				classifyProviders();
				recordDistributions(numSimulations);
				recordEquilibrium(numSimulations);
				recordJaccardLog(numSimulations);
				recordFitnessLog(numSimulations);
				recordProviderPeering(numSimulations);
				recordBetweennessCentralityDistribution(numSimulations);
				*/

				recordStrategyDistribution2(numSimulations);

				if(numSimulations==0 || numSimulations==1){


					if(numSimulations==1){
						for(int x=0;x<activeNodes;x++){
							aliveNodes[x].availablePeeringStrategies.push_back(1);
							//aliveNodes[x].availablePeeringStrategies.push_back(4);
						}
						
						stackelbergLeader=chooseStackelbergLeader(3);
						cout<<"Node "<<stackelbergLeader<<" chosen as stackelbergLeader with g: "<<aliveNodes[stackelbergLeader].numGPresence<<" i: "<<aliveNodes[stackelbergLeader].I.size()<<" j: "<<aliveNodes[stackelbergLeader].J.size()<<endl;
					}

					permute(true,playOrderSeed,stackelbergLeader);
					
					numSimulations++;
					iterations=0;
					continue;
				}

				else{

					printStackelbergFitness(stackelbergLeader);
					break;
				}

			}

		}

	}//end iterations while loop

	return 0;

}//main ends
