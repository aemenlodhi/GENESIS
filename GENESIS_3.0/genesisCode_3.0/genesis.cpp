//============================================================================
// Name        : Network.cpp
// Author      : Aemen Lodhi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "globalIncludes.h"
#include "globalStructs.h"
#include "globalVars.h"
#include "node.h"
#include "geography.h"
#include "initialization.h"
#include "support.h"
#include "logDebug.h"

double CONFIDENCE_FACTOR_ESTIMATION;
bool PEERING;
bool PRIVATE_PEERING;
double PRIVATE_PEERING_THRESHOLD;
bool PAID_PEERING;
double UNIVERSAL_SIGMA;
bool DOMINANTDIRECTIONBILLING;
bool COMPETITIVE_PRICING;
double MAX_TRANSIT_PRICE;
double MIN_TRANSIT_PRICE;
double UNIVERSAL_PEERING_PRICE;
double TRANSIT_COST_EXPONENT;
double PEERING_COST_EXPONENT;
unsigned int MAX_NODES;
unsigned int INIT_NODES;
unsigned int MAX_LOCATIONS;
unsigned int MIN_POPS;
unsigned int MAX_POPS;
double ZIPF_PARAM_GEO_EXPANSE;
double MAX_TRAFFIC;
double MEAN_CONSUMED_TRAFFIC;
double ZIPF_PARAM_GENERATED_TRAFFIC;
double ZIPF_PARAM_CONSUMED_TRAFFIC;
unsigned int MULTIHOMING_DEGREE;
unsigned int MAX_ROUNDS;
unsigned int INITIAL_T1_CLIQUE_SIZE;
double MIN_PORT_CAPACITY;
double PORT_PRICE;
double ONE_G_PORT_PRICE;
double TEN_G_PORT_PRICE;
double HUNDRED_G_PORT_PRICE;
bool IXP_PEERING;
double TRANSIT_PRICE_100MBPS;
double TRANSIT_PRICE_1GBPS;
double TRANSIT_PRICE_10GBPS;
double TRANSIT_PRICE_100GBPS;

int main(int argc, char** argv){

	if(argc!=7){
		cout<<"Usage: paramFileName populationSeed initialTopologySeed playOrderSeed readLog logFileName";
		exit(-1);
	}

	cout.precision(dbl::digits10);

	populationSeed=atoi(argv[2]);
	initialTopologySeed=atoi(argv[3]);
	playOrderSeed=atoi(argv[4]);

#if DEBUG
	createLogFiles(logFile,initialNetworkLog,finalNetworkLog,snapshotFile,flowFile,populationSeed,initialTopologySeed,playOrderSeed);
#endif

	bool readInitializationFromFile=atoi(argv[5]);
	char* parameterFile=argv[1];

	initialize(readInitializationFromFile,parameterFile,populationSeed,initialTopologySeed);

	cout<<"Initialization completed"<<endl;


#if DEBUG

	logFile<<endl<<"After Initialization"<<endl;
	displayTrafficMatrix();
	displayNodeData();
	displayRouteData();

#endif

	computeTrafficFlowsAcrossNetwork();

	/*
	ofstream fitnessFile;
	char fitnessFileName[100];
	sprintf(fitnessFileName,"fitnessValues_%ld.txt",populationSeed);
	fitnessFile.open(fitnessFileName,ios::out);
	*/

	list<unsigned int> providers;
	for(unsigned int i=0;i<Node::activeNodes;i++){
		if(!aliveNodes[i].I.empty() && !aliveNodes[i].Q.empty()){
			aliveNodes[i].selectPeeringStrategy(Selective);
			providers.push_back(i);
		}

		if(!aliveNodes[i].I.empty() && aliveNodes[i].Q.empty())
			aliveNodes[i].selectPeeringStrategy(Restrictive);
		else
			aliveNodes[i].selectPeeringStrategy(Open);
	}

	char preExpLogFileName[100];
	char postExpLogFileName[100];
	sprintf(preExpLogFileName,"preExperimentLog_%ld_%ld.txt",initialTopologySeed,populationSeed);
	sprintf(postExpLogFileName,"postExperimentLog_%ld_%ld.txt",initialTopologySeed,populationSeed);
	fstream preExpFile, postExpFile;

	preExpFile.open(preExpLogFileName,ios::out);
	postExpFile.open(postExpLogFileName,ios::out);


	int randomProvider=rand()%providers.size();
	int i=0;

	for(list<unsigned int>::iterator it=providers.begin();it!=providers.end();it++,i++){
		if(i==static_cast<int>(randomProvider)){
			i=*it;
			aliveNodes[i].updateVt();
			aliveNodes[i].updateFitness();
			printNode(i,preExpFile);
			aliveNodes[*it].peerSelectionEstimation(TIGHT,true);
			//computeTrafficFlowsAcrossNode(*it);
			//aliveNodes[*it].updateFitness();

			/*
			fitnessFile<<populationSeed<<"\t"<<*it<<"\t"<<aliveNodes[*it].fitness<<"\t"<<aliveNodes[*it].K.size()<<endl;
			cout<<"Ports used by selected node: ";
			for(vector<IXPPort>::iterator it=aliveNodes[i].peeringPorts.begin();it!=aliveNodes[i].peeringPorts.end();it++){
				if((*it).capacity==ONE_G)
					cout<<"ONE_G\t";
				else if((*it).capacity==TEN_G)
					cout<<"TEN_G\t";
				else if((*it).capacity==HUNDRED_G)
					cout<<"HUNDRED_G\t";
			}
			cout<<endl;
			*/

			break;
		}

	}

	printNode(i,postExpFile);

#if EXPERIMENT
	for(unsigned int i=0;i<Node::activeNodes;i++){
		if(!aliveNodes[i].I.empty()){
			aliveNodes[i].dopeeringTrialsContemporary(false);

			cout<<"Provider "<<i<<" peered with: "<<endl;
			for(ptpsMapIt it=aliveNodes[i].peeringTrialsPeersContemporary.begin();it!=aliveNodes[i].peeringTrialsPeersContemporary.end();it++)
				cout<<(*it).first<<"\t"<<(*it).second.outboundTraffic<<"\t"<<(*it).second.inboundTraffic<<"\t"<<(*it).second.totalTraffic<<endl;
		}
	}
#endif


#if DEBUG
	snapShot();
#endif

	/*
	for(unsigned int i=0;i<Node::activeNodes;i++){
		if(!aliveNodes[i].I.empty()){
			aliveNodes[i].dopeeringTrialsProposed(true);

			cout<<"Provider "<<i<<" peered with: "<<endl;
			for(ptpsMapIt it=aliveNodes[i].peeringTrialsPeersProposed.begin();it!=aliveNodes[i].peeringTrialsPeersProposed.end();it++)
				cout<<(*it).first<<"\t"<<(*it).second.outboundTraffic<<"\t"<<(*it).second.inboundTraffic<<"\t"<<(*it).second.totalTraffic<<endl;
		}
	}
	*/


//	for(unsigned int x=0;x<5;x++)
//		for(unsigned int y=0;y<5;y++)
//			if(x!=y){
//
//				if(aliveNodes[])
//
//			}


#if EXPERIMENT
	{

		vector<unsigned int> providers;
		vector<unsigned int> peers;
		unsigned int chosenProvider;
		unsigned int chosenPeer;

		double actualTraffic;
		double estimatedTraffic;

		for(unsigned int q=0;q<Node::activeNodes;q++)
			if(!aliveNodes[q].I.empty() && aliveNodes[q].Q.empty())
				providers.push_back(q);

		do{
			std::random_shuffle(providers.begin(),providers.end());
			chosenProvider=providers.front();

		}while(aliveNodes[chosenProvider].K.empty());

		for(list<NodePrice>::iterator it=aliveNodes[chosenProvider].K.begin();it!=aliveNodes[chosenProvider].K.end();it++){
			if(!aliveNodes[(*it).nId].I.empty() && !aliveNodes[(*it).nId].Q.empty())
				peers.push_back((*it).nId);
		}

		if(!peers.empty()){
			std::random_shuffle(peers.begin(),peers.end());
			chosenPeer=peers.front();

			if(linkIndex[chosenProvider][chosenPeer].index!=-1){
				actualTraffic=linkValueVector[linkIndex[chosenProvider][chosenPeer].index];

				aliveNodes[chosenProvider].dePeer(chosenPeer);

				computeTrafficFlowsAcrossNetwork();

				aliveNodes[chosenProvider].estimateTrafficExchange(chosenPeer);

				char perturbationFileName[100];
				ofstream perturbationFile;
				sprintf(perturbationFileName,"perturbation_%d_%d_%d.txt",static_cast<int>(populationSeed),static_cast<int>(initialTopologySeed),static_cast<int>(playOrderSeed));
				perturbationFile.open(perturbationFileName,ios::app);

				perturbationFile<<(actualTraffic-estimatedTraffic)/actualTraffic<<endl;

			}}




		char allFileName[100];
		char providerFileName[100];
		char theoreticalAllFileName[100];
		char theoreticalProviderFileName[100];
		char numPeersFileName[100];

		ofstream allFlowsFile;
		ofstream providerFlowsFile;
		ofstream theoreticalAllFlowsFile;
		ofstream theoreticalProviderFlowsFile;
		ofstream numPeersFile;

		sprintf(allFileName,"allNodesFlows_%d_%d_%d.txt",static_cast<int>(populationSeed),static_cast<int>(initialTopologySeed),static_cast<int>(playOrderSeed));
		sprintf(providerFileName,"providerNodesFlows_%d_%d_%d.txt",static_cast<int>(populationSeed),static_cast<int>(initialTopologySeed),static_cast<int>(playOrderSeed));
		sprintf(theoreticalAllFileName,"theoreticalAllNodesFlows_%d_%d_%d.txt",static_cast<int>(populationSeed),static_cast<int>(initialTopologySeed),static_cast<int>(playOrderSeed));
		sprintf(theoreticalProviderFileName,"theoreticalProviderNodesFlows_%d_%d_%d.txt",static_cast<int>(populationSeed),static_cast<int>(initialTopologySeed),static_cast<int>(playOrderSeed));
		sprintf(numPeersFileName,"numPeers_%d_%d_%d.txt",static_cast<int>(populationSeed),static_cast<int>(initialTopologySeed),static_cast<int>(playOrderSeed));

		allFlowsFile.open(allFileName,ios::out);
		providerFlowsFile.open(providerFileName,ios::out);
		theoreticalAllFlowsFile.open(theoreticalAllFileName,ios::out);
		theoreticalProviderFlowsFile.open(theoreticalProviderFileName,ios::out);
		numPeersFile.open(numPeersFileName,ios::out);

		char allTrafficFileName[100];
		char providerTrafficFileName[100];

		ofstream allTrafficFile;
		ofstream providerTrafficFile;

		sprintf(allTrafficFileName,"allNodesTraffic_%d_%d_%d.txt",static_cast<int>(populationSeed),static_cast<int>(initialTopologySeed),static_cast<int>(playOrderSeed));
		sprintf(providerTrafficFileName,"providerNodesTraffic_%d_%d_%d.txt",static_cast<int>(populationSeed),static_cast<int>(initialTopologySeed),static_cast<int>(playOrderSeed));

		allTrafficFile.open(allTrafficFileName,ios::out);
		providerTrafficFile.open(providerTrafficFileName,ios::out);

		int theoreticalFlows=0;
		int numColocated=0;
		for(unsigned int i=0;i<Node::activeNodes;i++){

			theoreticalFlows=0;
			numColocated=0;
			allFlowsFile<<i<<"\t"<<aliveNodes[i].numFlows<<endl;

			if(!aliveNodes[i].I.empty()){
				providerFlowsFile<<i<<"\t"<<aliveNodes[i].numFlows<<endl;

				for(unsigned int x=0;x<Node::activeNodes;x++)
					if(aliveNodes[i].colocated[x]==true)
						numColocated++;

				numPeersFile<<i<<"\t"<<numColocated-aliveNodes[i].J.size()<<"\t"<<aliveNodes[i].K.size()<<endl;

				theoreticalFlows+=(aliveNodes[i].J.size()*(aliveNodes[i].J.size()-1));
				theoreticalFlows+=2*aliveNodes[i].J.size()*(Node::activeNodes-aliveNodes[i].J.size());
				theoreticalFlows+=2*(Node::activeNodes-1);

				/*for(list<NodePrice>::iterator it=aliveNodes[i].I.begin();it!=aliveNodes[i].I.end();it++){
					if(!aliveNodes[(*it).nId].I.empty()){
						theoreticalFlows-=(aliveNodes[(*it).nId].J.size()*(aliveNodes[(*it).nId].J.size()-1));
						theoreticalFlows-=(2*aliveNodes[(*it).nId].J.size());
					}
				}*/

				if(theoreticalFlows>(Node::activeNodes*(Node::activeNodes-1))){
					theoreticalFlows=Node::activeNodes*(Node::activeNodes-1);
				}

				theoreticalAllFlowsFile<<i<<"\t"<<theoreticalFlows<<endl;
				theoreticalProviderFlowsFile<<i<<"\t"<<theoreticalFlows<<endl;

				providerTrafficFile<<i<<"\t"<<aliveNodes[i].V<<endl;
			}

			else{
				theoreticalFlows=2*(Node::activeNodes-1);
				theoreticalAllFlowsFile<<i<<"\t"<<theoreticalFlows<<endl;

				allTrafficFile<<i<<"\t"<<aliveNodes[i].V<<endl;
			}

		}

	}
#endif

	cout<<"Reached Omaha"<<endl;

	/*
	char logFileName[50];

	int numProviders=0;
	bool providerChange=true;
	bool peeringChange=true;
	bool depeeringChange=true;
	bool strategyChange=true;

	//log file
	//sprintf(logFileName,"logRun_%d.txt",atoi(argv[5]));
	//logFile.open(logFileName);

	Node::maxNodes=atoi(argv[1]);
	Location::maxLocations=atoi(argv[2]);
	maxIterations=atoi(argv[3]);
	maxTraffic=static_cast<double>(atoi(argv[4]));
	zipfExponentTrafficGeneration=atof(argv[6]);
	zipfExponentTrafficConsumption=atof(argv[7]);
	zipfExponentGeography=atof(argv[8]);
	//priceDependency=atoi(argv[9]);
	populationSeed=atoi(argv[10]);
	playOrderSeed=atoi(argv[14]);
	initialTopologySeed=atoi(argv[15]);
	Node::initNodes=atoi(argv[12]);
	Node::universalSigma=atof(argv[13]);
	Node::activeNodes=Node::initNodes;
	maxIterations=1000;
	bool stepChange=false;

	 */


	//*********** Initialize ************//
	//initialize(populationSeed,initialTopologySeed);


	//*********** Routing after initial random topology has been established ************//
	//routeTraffic();

	//*********** Update fitness for all networks in the initial topology **************//
	/*
	for(unsigned int i=0;i<Node::activeNodes;i++){
		aliveNodes[i].updateVt();
		aliveNodes[i].updateFitness();
	}

#if DEBUG

	logFile<<endl<<"After Initialization"<<endl;
	//displayTrafficMatrix();
	displayNodeData();
	displayTopology();
	//displayRouteData();

#endif


	//Iterations begin
	permute(true,playOrderSeed);

	/*
	while(iterations<maxIterations){

#if DEBUG
		cout<<endl<<endl<<"********** Iterations "<<iterations<<" ************"<<endl;
		logFile<<endl<<endl<<"********** Iterations "<<iterations<<" ************"<<endl;
#endif

		//reset step change marker
		stepChange=false;

		permute(false,-1);

		while((steps=getNextNodeInOrder())!=-1){

#if DEBUG
			cout<<endl<<endl<<"********** Round "<<numSimulations<<" ************"<<endl;
			cout<<endl<<endl<<"********** Iterations "<<iterations<<" ************"<<endl;
			cout<<endl<<endl<<"********** Step "<<steps<<" ************"<<endl;
			logFile<<endl<<endl<<"********** Step "<<steps<<" ************"<<endl;
#endif



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

				recordStrategyDistribution2(numSimulations);

				if(numSimulations==0 || numSimulations==1){


					if(numSimulations==1){
						for(int x=0;x<activeNodes;x++){
							aliveNodes[x].availablePeeringStrategies.push_back(1);
							//aliveNodes[x].availablePeeringStrategies.push_back(4);
						}

					}

					numSimulations++;
					iterations=0;
					continue;
				}

				else{
					break;
				}

			}

		}

	}//end iterations while loop
	*/

	return 0;

}//main ends
