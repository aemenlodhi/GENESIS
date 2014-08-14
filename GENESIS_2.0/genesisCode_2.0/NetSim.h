/*
 * NetSim.h
 *
 *  Created on: Sep 24, 2009
 *      Author: alodhi3
 */

//Changing this file

#ifndef NETSIM_H_
#define NETSIM_H_

#include<list>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<fstream>
#include<stdio.h>
#include "globalVars.h"
#include "Statistics.h"

using namespace std;

typedef std::numeric_limits< double > dbl;

//global variables defined
unsigned int maxIterations=10;
unsigned int maxRounds=10;
int maxNodes=4;
double universalSigma=2;
double universalSigma2=10;
int activeNodes=4;
int initNodes=4;
int maxLinks=10;
int numAliveNodes=0;
double** trafficMatrix;
int maxRegions=2;
unsigned int iterations=0;
unsigned int rounds=0;
int steps=0;
unsigned int numFlows=0;

unsigned int maxFlows;
list<int>* routingMatrixScale;
list<int>* routingMatrixScaleAsym;
int** flowIndex;
double* flowValueVector;
double* flowValueVectorAsym;
double* linkValueVector;
bool* aliveLinkIndicator;
bool* aliveFlowIndicator;
int* flowDirectionFrom;
int* flowDirectionFromAsym;
bool* activeFlowIndicator;
linkInfo** linkIndex;
//int** oscillationLog;
ofstream logFile;
ofstream resultLogFile;
ofstream snapshotFile;
long int mySeed;	//population seed
long int playOrderSeed;
long int initialTopologySeed;
int numSimulations=0;

struct LogVector{


	int peeringStrategyNumber;
	list<int> K;
	list<int> I;
};

LogVector **oscillationLog;

//peering global variables
int initialCliqueSize=3;
int totalPeeringStrategies=3;
bool PEERING=true;
list<int> Tier1;
double peeringThreshold=0;
bool cbAnalysis=false;
bool paidPeering=true;
int peeringLinksStats[5][5];

//economic stats
double marshillianEfficiency[2]={0};
double disparity[2]={0};
double efficiency[2]={0};
double competitiveness[2]={0};
double stubCostsMbps[2]={0};
double providerFitnessMbps[2]={0};
void computeEconomicStats(int);


//variables for geography and traffic distribution
double sZetaTrafficGen=0.8;
double sZetaTrafficCon=0.8;
double sZetaGeography=0.8;
int maxD=-1;
double totalTraffic=1000000;
double maxTraffic=1000000;
int priceDependancy=0;


//data structures to save the state of the network
double strategyDistribution[5][3];
double fitnessRecord[5][500];
double providerIncreaseDecrease[5][3];
double t1ProvidersFitness[5][3];
double t2ProvidersFitness[5][3];
double t3ProvidersFitness[5][3];
double numProviders[5]={0};
double numT1[5]={0};
double numT2[5]={0};
double numT3[5]={0};
double numCPCC[5]={0};
double treeHeight[5]={0};
double avgWeightedPathLength[5]={0};
double networkDiameter[5]={0};
double linkDensity[5]={0};
double ppClusteringCoefficient[5]={0};
double t1Nt1TransitRatio[5]={0};
double peeringTrafficOnly[5]={0};
int wealthiestId[5]={0};
double maxWealth[5]={0};
double avgPlainPathLength[5]={0};
list<int> numStubProviderPeeringLinks;
int numSPPLinks=0;
double trafficFractions[500][3][3];


list<int>* routingMatrixScaleSave;
list<int>* routingMatrixScaleAsymSave;
int** flowIndexSave;
double* flowValueVectorSave;
double* flowValueVectorAsymSave;
double* linkValueVectorSave;
bool* aliveLinkIndicatorSave;
bool* aliveFlowIndicatorSave;
int* flowDirectionFromSave;
int* flowDirectionFromAsymSave;
bool* activeFlowIndicatorSave;
linkInfo** linkIndexSave;

//unused variable retained to avoid compilation errors with existing functions
bool** routingMatrix;
bool netDisconnected=false;

//play order
list<int> nodeOrder;
list<int> nodeOrderBackup;

enum life{
	dead,
	alive
};

enum nodeClass{

	CP,
	CC,
	Ordinary

};

void refillNodeOrder();
void printFitness();
void routingScale();
void endSimulation(string str);
void establishLinkWithProvider(int,int);
void establishFlowWithProvider(int,int);
bool establishFlow(int,int,int);
bool findFlow(int,int,bool* &);
void endLink(int,int);
void endFlow(int,int);
bool isPresentInList(list<int> &,int);
double sumG();
void permute(bool);
void permute(bool,int);
void permute(bool,int,int);
int getNewIt();
void compactMatrix();
void updateVt();
bool checkConnectivity();
void providerFitnessStats();

//scaled functions
void endLinkScale(int,int);
void endFlowScale(int,int);
void establishFlowWithProviderScale(int,int);
void establishFlowWithPeerScale(int,int);
bool findFlowPeeringScale(int,int,list<int> &,bool);
bool findFlowPeeringScaleAsym(int,int,list<int> &,bool);
bool establishFlowPeeringScale(int,int,int);
bool establishFlowPeeringScaleAsym(int,int,int);
void mergeListsIntoOneScale(list<int>&, list<int>&, list<int>&);
void mergeTwoListsScale(list<int>&, list<int>&);


//peering related
void establishLinkWithPeer(int,int);
void establishFlowWithPeer(int,int);
bool establishFlowPeering(int,int,int);
bool findFlowPeering(int,int,bool* &);
double measurePeeringTraffic();
double measureT1PeeringTraffic();
double estimateTrafficExchange(int,int);
double measureNT1VtTrafficFraction();
double measureT1VtTrafficFraction();

//coalitions related
bool formCoalition(int,int);

// Log related
void displayRouteData();
void displayTopology();
void displayNodeData();
void displayTrafficMatrix();

//math functions
double rand_val(int);
int zipf(double,int);
int findMinConsumedTraffic(int);

enum StrategySelectionState{
	Steady,
	Move
};

struct Coordinate{
	int xCoordinate;
	int yCoordinate;
};

struct npPair{
	int nId;
	double price;
	double trafficVolume;
	int gExpanse;
	int numCustomers;
	bool shouldAct;
};


struct VolumePrice{
	double volume;
	double contractPrice;
};

struct twoPair{
	int n1;
	int n2;

	int start;
	int end;
};

int zipf(double alpha, int n)
{

  static int first = TRUE;      // Static first time flag
  static double c = 0;          // Normalization constant
  double z;                     // Uniform random number (0 < z < 1)
  double sum_prob;              // Sum of probabilities
  double zipf_value;            // Computed exponential value to be returned
  int    i;                     // Loop counter


  // Compute normalization constant on first call only
  if (first == TRUE)
  {
    for (i=1; i<=n; i++)
      c = c + (1.0 / pow((double) i, alpha));
    c = 1.0 / c;
    first = FALSE;
  }

  // Pull a uniform random number (0 < z < 1)
  do{

	  z=static_cast<double>(rand()%10000)/10000;

  }while(z==0 || z==1);





  // Map z to the value
  sum_prob = 0;
  for (i=1; i<=n; i++)
  {
    sum_prob = sum_prob + c / pow((double) i, alpha);
    if (sum_prob >= z)
    {
      zipf_value = i;
      break;
    }
  }

  // Assert that zipf_value is between 1 and N
  //assert((zipf_value >=1) && (zipf_value <= n));

  return static_cast<int>(zipf_value);
}

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - x_n = 7^5*x_(n-1)mod(2^31 - 1)                                    =
//=   - With x seeded to 1 the 10000th x value should be 1043618065       =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================
double rand_val(int seed)
{
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x;               // Random int value
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // Set the seed if argument is non-zero and then return zero
  if (seed > 0)
  {
    x = seed;
    return(0.0);
  }

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random value between 0.0 and 1.0
  return((double) x / m);
}

bool sortGExpansePrice(npPair p1, npPair p2){

	return (p1.gExpanse<p2.gExpanse);
}

bool sortReverse(double n1, double n2) {

	return (n1>n2);
}

bool sortCustomersNP(npPair p1, npPair p2){

	return (p1.numCustomers<p2.numCustomers);
}

bool sortVolumeReverseNP(npPair p1, npPair p2){

	return p1.trafficVolume>p2.trafficVolume;
}

bool sortGExpanse(geoIndexPair p1, geoIndexPair p2){

	return (p1.numGPresence<p2.numGPresence);
}

bool sortGExpanseReverse(geoIndexPair p1, geoIndexPair p2){

	return (p1.numGPresence>p2.numGPresence);
}


bool sortVolume(npPair p1, npPair p2){

	return (p1.trafficVolume<p2.trafficVolume);
}

bool sortGExpansePriceReverse(npPair p1, npPair p2){

        return (p1.gExpanse>p2.gExpanse);
}

bool sortVt(npPair p1, npPair p2){

        return (p1.trafficVolume<p2.trafficVolume);
}


bool sortVtReverse(npPair p1, npPair p2){

        return (p1.trafficVolume>p2.trafficVolume);
}

bool sortFitness(npPair p1, npPair p2){

        return (p1.price<p2.price);
}

bool sortFitnessReverse(npPair p1, npPair p2){

        return (p1.price>p2.price);
}



bool compareId(npPair E1, npPair E2){

	if(E1.nId<E2.nId)
		return true;
	else
		return false;
}

bool comparePrice(npPair E1, npPair E2){

	if(E1.price<E2.price)
		return true;
	else
		return false;
}

bool comparePriceReverse(npPair E1, npPair E2){

	if(E1.price>E2.price)
		return true;
	else
		return false;
}

bool checkUniqueness(npPair P1, npPair P2){

	return P1.nId==P2.nId;
}

class Region{

public:

	Coordinate location;
	unsigned int population;			//number of Nodes that have PoPs in this region
	list<int> nodePresent;		//list of all Nodees that have PoPs in this region
	int maxDensityAllowed;

	Region();

};

Region::Region(){
	location.xCoordinate=-1;
	location.yCoordinate=-1;
	population=0;
	maxDensityAllowed=10000;
}

class FitnessRecord{

public:
	int nodeId;
	list<double> fitRecord[4];
	double fitnessAtPlay;
	double recordedFitness;

	int p1;
	int p2;
	int deltaP;
	double f1;
	double f2;
	double deltaF;

	FitnessRecord();

};

FitnessRecord::FitnessRecord(){

	nodeId=0;
	fitnessAtPlay=0;
	recordedFitness=0;
}

FitnessRecord nodeRecords[500];

class Node{

public:

	//Identity
	int nodeId;
	life lifeStatus;
	bool newborn;
	bool orphan;
	nodeClass netClass;
	double stateProbability;

	//Economics
	double **priceChart;
	double price;
	double providerPrice;
	double providerCost;
	double peerCost;
	double poorPeerCost;
	double superPeerRevenue;
	double customerRevenue;
	double peeringExponent;
	double peeringCostMultiplier;
	double providerExponent;
	double providerCostMultiplier;
	double percentageChangeInFitness;
	void updateFitness();
	double computeDelFitness(double,double);
	void updateState(int &, int&, int&, int&, const int&);
	bool updatePeeringStrategy();
	double fitnessAtTimeOfPlay;
	double getActualDF();

	//Traffic
	double trafficGenerated;	//traffic generated by x
	double trafficConsumed;
	double trafficConsumedFraction;
	double Vo;	//own traffic trafficGenerated + trafficConsumed + trafficLocal
	double Vp;	//traffic exchanged with provider
	double Vc;	//total traffic exchanged with customers
	double Vt;	//transit traffic
	double V;	//sum of all traffics
	double Vpp;	//peering traffic
	list<VolumePrice> customerVPList;
	list<VolumePrice> providerVPList;
	list<VolumePrice> peerVPList;
	list<VolumePrice> superPeerVPList;
	list<VolumePrice> poorPeerVPList;

	//Geography
	list<Coordinate> gPresence;		//locations where Node has presence
	int numGPresence;				//number of regions where Node has presence

	//Topology
	int QPrev;
	int Q;
	list<int> I;			//immediate customers of x
	list<int> J;			//all Nodees in customer tree of x
	list<int> overLap;

	//category related
	int category[10];
	double actualTrafficFractions[3];

	Node();

	//update network functions
	bool getNewProvider();
	int getProviderAsZ(int);
	bool getInitialProviderRand();
	void addICustomer(int id);	//add to immediate customer list
	void addJCustomer(int id);	//add to J customer list
	void removeICustomer(int id);
	void removeJCustomer(int id);
	void removeJSubTree(int id);
	void addJSubTree(int id);
	bool isPresentInCustomerTree(int id); //is the node present in customer tree

	//category related
	void updateCategories();
	bool isMajorContentNet;
	bool isCP;
	bool isCC;

	//peering related
	list<int> K;	//list of peers
	double peerCriteria;
	bool isImmediateCustomer(int id);
	bool isPeer(int id);
	bool isPresentInCustomerTreeOfAlly(int id);
	int isPresentInCustomerTreeOfPeer(int id);
	int isImmediateCustomerOfPeer(int id);
	bool insertPeerInK(int);
	bool checkAndRemovePeersInCustomerTree(int);
	bool getNewPeer(int);
	int getHypotheticalProviderPeering(int);
	int getProviderAfterDePeering(int);
	bool dePeer(int id);
	bool dePeerSingular(int id);
	int getProviderAfterPeering();
	double paidPeeringPrice;
	list<int> availablePeeringStrategies;

	//coalition related
	bool isInCoalition;
	list<int> allies;
	bool isCoalitionAllowed;
	bool getNewCoalition();
	npPair evaluateAllyRequest(int);
	bool isCustomerOfAlly(int);
	bool isProviderOfAlly(int);
	npPair evaluateAlly(int);
	bool isAlly(int);

	//peering strategies
	bool isPeeringWithStubsAllowed;
	bool isPeeringWithCPCCAllowed;
	bool isGrandOpenAllowed;
	int peeringStrategyNumber;
	double fitnessPrev;
	double fitness;
	double deltaFitness;
	StrategySelectionState selectionState;
	bool applyPeeringCriteria(int,bool);
	bool evaluateExistingPeer(int);
	bool (Node::*strategyPointer)(int);
	bool (Node::*dStrategyPointer)(int);
	bool evaluatePeeringThreshold(int);

	void selectPeeringStrategy(int);
	bool areAllPeersT1();

	bool peeringStrategy0(int);
	bool dePeeringStrategy0(int);

	bool peeringStrategy1(int);
	bool dePeeringStrategy1(int);

	bool peeringStrategy2(int);
	bool dePeeringStrategy2(int);

	//hybrid
	bool peeringStrategy3(int);
	bool dePeeringStrategy3(int);

	//cb analysis
	bool peeringStrategy4(int);
	bool dePeeringStrategy4(int);

	//paid peering
	bool peeringStrategy5(int);
	bool dePeeringStrategy5(int);

	bool cbAnalysisForPaidPeer(int);
	bool cbAnalysisForPaidDePeer(int);

	//saved for later	**Function definitions can be found in archived sections
	bool isPresentInRegion(Coordinate);
	bool doesShareGeography(int);
	void die();
	void reborn();
	bool isPresentInProviderChain(int id);
	bool considerPeeringRequest(int);
	bool getOrphanProvider();

};

//more global entities defined
Region** geography;
Coordinate chosenMaxDLoc;
Node* aliveNodes;

//to save the state of the network
Node* aliveNodesSave;
list<int> Tier1Save;

void computeTraffic();

void saveNetworkState();
void restoreNetworkState();

Node::Node(){

	//coalitions
	isInCoalition=false;
	isCoalitionAllowed=false;

	//Identity
	netClass=Ordinary;
	nodeId=-1;
	lifeStatus=dead;
	isMajorContentNet=false;
	isCP=false;
	isCC=false;

	//Economics
	price=providerPrice=0;
	providerCost=peerCost=customerRevenue=0;
	peeringExponent=0.43;
	peeringCostMultiplier=25;
	providerExponent=0.75;
	providerCostMultiplier=1;
	poorPeerCost=superPeerRevenue=0;


	//Traffic
	trafficGenerated=trafficConsumed=Vo=Vp=Vc=Vt=V=Vpp=0;
	trafficConsumedFraction=0;

	//support
	newborn=false;
	orphan=false;

	//Geography
	numGPresence=0;

	//Topology
	Q=-1;
	QPrev=-1;

	//peering
	peerCriteria=0;
	peeringStrategyNumber=2;
	fitness=0;
	fitnessPrev=0;
	deltaFitness=0;
	selectionState=Move;
	paidPeeringPrice=0;
	isGrandOpenAllowed=true;	//only applies to open peering
	isPeeringWithStubsAllowed=false;
	isPeeringWithCPCCAllowed=false;

	selectPeeringStrategy(2);

	//strategyPointer=&Node::peeringStrategy1;
	//dStrategyPointer=&Node::dePeeringStrategy1;

	for(int i=0;i<10;i++)
		category[i]=-1;

	fitnessAtTimeOfPlay=0;

	availablePeeringStrategies.push_back(0);
	//availablePeeringStrategies.push_back(1);
	availablePeeringStrategies.push_back(2);
	//availablePeeringStrategies.push_back(4);

}

void expandNodeRandom(Coordinate, Node&);

bool Node::isPresentInRegion(Coordinate gridPoint){

	list<Coordinate>::iterator itC;

	for(itC=gPresence.begin();itC!=gPresence.end();itC++){

		if((*itC).xCoordinate==gridPoint.xCoordinate && (*itC).yCoordinate==gridPoint.yCoordinate)
			return true;
	}

	return false;
}

bool Node::doesShareGeography(int id){

	list<Coordinate>::iterator itC;
	list<Coordinate>::iterator itD;

	for(itC=gPresence.begin();itC!=gPresence.end();itC++){
		for(itD=aliveNodes[id].gPresence.begin();itD!=aliveNodes[id].gPresence.end();itD++){

			if((*itC).xCoordinate==(*itD).xCoordinate && (*itC).yCoordinate==(*itD).yCoordinate)
				return true;
		}
	}

	return false;

}

/*
bool Node::updatePeeringStrategy(){

	bool returnValue=false;
	if(I.empty()){
		if(peeringStrategyNumber!=1)
			returnValue=true;
		selectPeeringStrategy(1);
	}
	else{
		if(Q==-1){
			if(peeringStrategyNumber!=2)
				returnValue=true;
			selectPeeringStrategy(2);

		}
		else{
			if(peeringStrategyNumber!=0)
				returnValue=true;
			selectPeeringStrategy(0);
		}
	}

}
*/

bool Node::updatePeeringStrategy(){

	/*
	 * Steps: Save state of the network
	 * Go over each strategy one by one and note down the fitness of each strategy
	 * Choose strategy that gives the best fitness
	 * Restore state of the network
	 * Return true if peering strategy changed
	 */


	double deltaFitnessRecord[7];
	double fitnessRecord[7];
	list<int>::iterator it;
	bool dePeeringChange=false;
	bool peeringChange=false;
	bool providerChange=false;
	double maxDf=-10;
	int bestStrategy=-1;
	int currentStrategy=peeringStrategyNumber;
	double currentDf=deltaFitness;
	double currentFitness=fitness;

	list<int>::iterator itInt;

	for(int i=0;i<7;i++){
		fitnessRecord[i]=-1;
		deltaFitnessRecord[i]=-100;
	}

	updateFitness();

	saveNetworkState();

#if DEBUG
	logFile<<"Current fitness of "<<nodeId<<" with strategy "<<peeringStrategyNumber<<" is "<<fitness<<endl;
#endif

	for(it=availablePeeringStrategies.begin();it!=availablePeeringStrategies.end();it++){


		if(it!=availablePeeringStrategies.begin())
			restoreNetworkState();

		selectPeeringStrategy(*it);

#if DEBUG
		logFile<<"Node "<<nodeId<<" evaluating strategy "<<*it<<endl;
#endif

		dePeeringChange=dePeer(-1);

		peeringChange=getNewPeer(-1);

		providerChange=getNewProvider();

#if DEBUG
		logFile<<"Node "<<nodeId<<" completed evaluation for strategy "<<*it<<endl;
#endif

		if(dePeeringChange || peeringChange || providerChange){

			routingScale();
			updateVt();
		}
		updateFitness();

#if DEBUG
		logFile<<"Fitness of "<<nodeId<<" with strategy "<<*it<<" is "<<fitness<<endl;
#endif

		fitnessRecord[*it]=fitness;

	}

	restoreNetworkState();

	bestStrategy=0;
	currentFitness=fitnessRecord[0];

	for(int i=0;i<5;i++){

		//if((numSimulations==1 && i!=1 && i!=4) || numSimulations==2){
		if(numSimulations==2){
			if(isPresentInList(availablePeeringStrategies,i) && fitnessRecord[i]>currentFitness){
				bestStrategy=i;
				currentFitness=fitnessRecord[i];

			}
		}
	}

	/*
	if(Q!=-1 && currentStrategy==2 && deltaFitnessRecord[currentStrategy]==deltaFitnessRecord[1])
		bestStrategy=1;

	if(bestStrategy==-1)
		bestStrategy=currentStrategy;

	if(deltaFitnessRecord[4]==deltaFitnessRecord[1] && bestStrategy==1)
		bestStrategy=4;

	if(deltaFitnessRecord[0]==deltaFitnessRecord[1] && bestStrategy==0)
		bestStrategy=1;
	*/
#if DEBUG
		logFile<<"Strategy of "<<nodeId<<" is "<<bestStrategy<<endl;
#endif

	selectPeeringStrategy(bestStrategy);

	//nodeRecords[nodeId].recordedFitness=fitnessRecord[bestStrategy];

	if(bestStrategy!=currentStrategy)
		return true;
	else
		return false;

}

void Node::updateState(int &steadyStrat, int& imitateStrat, int& numProviders, int& stableProviders, const int& stateSwitchProbabilityNegative){

	if(I.empty()){

		if(peeringStrategyNumber==1){

			steadyStrat++;

#if DEBUG
			logFile<<"Node "<<nodeId<<" remains steady with strategy "<<peeringStrategyNumber<<" and adopts state Steady"<<endl;
#endif

		}

		else{

			imitateStrat++;
#if DEBUG
			logFile<<"Node "<<nodeId<<" innovates to new strategy 1 and adopts state Steady"<<endl;
#endif

		}

		selectionState=Steady;
		selectPeeringStrategy(1);

	}//end if

	else{

		numProviders++;

		if(selectionState==Steady && deltaFitness>=0){
			selectionState=Steady;
			stableProviders++;
		}

		else if(selectionState==Steady && deltaFitness<0){

				stateProbability=rand()%100;
			if((stateProbability)<stateSwitchProbabilityNegative){
				selectionState=Move;
				cout<<"Provider "<<nodeId<<" switched to move state"<<endl;

			}

			else
				selectionState=Steady;

		}

		else if(selectionState==Move && deltaFitness<0){
			selectionState=Move;
			cout<<"Provider "<<nodeId<<" switched to move state"<<endl;
		}

		else if(selectionState==Move && deltaFitness>=0)
			selectionState=Steady;

		else{}

	}//end else

}

double Node::getActualDF(){

	return computeDelFitness(nodeRecords[nodeId].recordedFitness,fitness);
}

double Node::computeDelFitness(double fit1, double fit2){

	if(fit1==0 && fit2==0)
		return 0;

	else
		return (fit2-fit1)/max(abs(fit1),abs(fit2));
}

void Node::updateFitness(){

	list<VolumePrice>::iterator itVP;
	fitnessPrev=fitness;
	double publicPeerVolume=0;

	poorPeerCost=superPeerRevenue=peerCost=providerCost=customerRevenue=0;

	//calculating peer cost
	if(!K.empty() && !peerVPList.empty()){

		for(itVP=peerVPList.begin();itVP!=peerVPList.end();itVP++){
			if((*itVP).volume>=50)
				peerCost+=pow((*itVP).volume,peeringExponent);
			else
				publicPeerVolume+=(*itVP).volume;
		}

		peerCost+=pow(publicPeerVolume,peeringExponent);

		for(itVP=superPeerVPList.begin();itVP!=superPeerVPList.end();itVP++)
			peerCost+=pow((*itVP).volume,peeringExponent);

		for(itVP=poorPeerVPList.begin();itVP!=poorPeerVPList.end();itVP++)
			peerCost+=pow((*itVP).volume,peeringExponent);

		peerCost=peerCost*peeringCostMultiplier;

#if DEBUG
		logFile<<"Peer Cost for node "<<nodeId<<": "<<peerCost<<endl;
#endif

	}

	//calculating provider cost
	if(!providerVPList.empty()){

		for(itVP=providerVPList.begin();itVP!=providerVPList.end();itVP++)
			providerCost+=((*itVP).contractPrice*pow((*itVP).volume,providerExponent));

		providerCost=providerCost*providerCostMultiplier;

#if DEBUG
		logFile<<"Provider Cost for node "<<nodeId<<": "<<providerCost<<endl;
#endif


	}

	//calculating poor peer cost
	if(!poorPeerVPList.empty()){

		for(itVP=poorPeerVPList.begin();itVP!=poorPeerVPList.end();itVP++)
			poorPeerCost+=((*itVP).contractPrice*pow((*itVP).volume,peeringExponent));

	}

	//calculating customer revenue
	if(!I.empty() && !customerVPList.empty()){

		for(itVP=customerVPList.begin();itVP!=customerVPList.end();itVP++)
			customerRevenue+=((*itVP).contractPrice*pow((*itVP).volume,providerExponent));

#if DEBUG
		logFile<<"Customer Revenue for node "<<nodeId<<": "<<customerRevenue<<endl;
#endif


	}

	//calculating super peer revenue
	if(!superPeerVPList.empty()){

		for(itVP=superPeerVPList.begin();itVP!=superPeerVPList.end();itVP++)
			superPeerRevenue+=((*itVP).contractPrice*pow((*itVP).volume,peeringExponent));

	}

	fitness=superPeerRevenue+customerRevenue-providerCost-peerCost-poorPeerCost;

#if DEBUG
	logFile<<"Fitness for node "<<nodeId<<": "<<fitness<<endl;
#endif

	deltaFitness=fitness-fitnessPrev;
	/*
	if(fitnessPrev==0 && fitness==0)
		deltaFitness=0;

	else{
		deltaFitness=(fitness-fitnessPrev)/max(abs(fitness),abs(fitnessPrev));
	}
	*/
}

void Node::updateCategories(){

	if(I.empty()){
		category[0]=0;
		category[3]=0;
		category[4]=0;
		category[6]=0;

		if(category[1]!=0)
			category[1]=1;

		if(category[2]!=0)
			category[2]=1;

	}

	else{

		if(category[1]!=0)
			category[1]=1;

		if(category[2]!=0)
			category[2]=1;


		category[0]=1;	//its a provider

		//provider status		//its a global provider
		if((static_cast<double>(numGPresence)/static_cast<double>((maxRegions*maxRegions)))>=0.5){
			category[3]=1;
		}

		else if((static_cast<double>(numGPresence)/static_cast<double>((maxRegions*maxRegions)))>=0.1){	//regional provider
			category[3]=2;

		}
		else{				//local provider
			category[3]=3;
		}

		if(Q==-1)
			category[4]=1;
		else
			category[4]=0;

		/*
		if(category[1]!=0)
			category[1]=0;

		if(category[2]!=0)
			category[2]=0;
		*/
	}

}

bool Node::isImmediateCustomer(int id){

	list<int>::iterator it;

	for(it=I.begin();it!=I.end();it++)
		if(*it==id){
			return true;
		}

	return false;

}

bool Node::isPeer(int id){

	return isPresentInList(K,id);

}

bool Node::isPresentInCustomerTreeOfAlly(int id){

	list<int>::iterator it;

	for(it=allies.begin();it!=allies.end();it++)
		if(*it!=id){
			//if(aliveNodes[*it].isPresentInCustomerTree(id))
			//	return true;
			if(aliveNodes[*it].isImmediateCustomer(id))
				return true;
		}

	return false;

}

int Node::isImmediateCustomerOfPeer(int id){

	list<int>::iterator itInt;

	if(K.empty())
		return -1;

	else{

		for(itInt=K.begin();itInt!=K.end();itInt++){

			if(aliveNodes[*itInt].isImmediateCustomer(id))
				return *itInt;

		}//end for

	}//end else

	return -1;

}

int Node::isPresentInCustomerTreeOfPeer(int id){

	list<int>::iterator itInt;

	if(K.empty())
		return -1;

	else{

		for(itInt=K.begin();itInt!=K.end();itInt++){

			if(aliveNodes[*itInt].isPresentInCustomerTree(id))
				return *itInt;

		}//end for

	}//end else

	return -1;
}

bool Node::insertPeerInK(int id){

	list<int>::iterator itK;
	bool inserted=false;

	if(isPeer(id)){
		logFile<<"Node "<<nodeId<<" peering twice with "<<id<<endl;
		string str("ERROR!! Peering with an existing peer.");
		endSimulation(str);
		return false;
	}


	else{

		if(K.empty()){
			K.push_back(id);
			inserted=true;
		}

		else{

			for(itK=K.begin();itK!=K.end();itK++){

				if(aliveNodes[*itK].isPresentInCustomerTree(id)){
					K.insert(itK,id);
					inserted=true;
					break;
				}
			}
		}

		if(!inserted)
			K.push_back(id);

		return true;
	}

}

bool Node::peeringStrategy0(int id){

	//total volume based strategy
	peerCriteria=universalSigma;

	if(id==-1)return false;

	if(aliveNodes[id].peeringStrategyNumber!=5){
		if((V/aliveNodes[id].V)<=peerCriteria)
			return true;
		else
			return false;
	}//end if

	else{	//y uses paid peering strategy

		if((V/aliveNodes[id].V)<=peerCriteria){
			return cbAnalysisForPaidPeer(id);

		}

		else
			return false;
	}//end else

}

bool Node::dePeeringStrategy0(int id){

	if(aliveNodes[id].peeringStrategyNumber!=5){
		if(((V-linkValueVector[linkIndex[nodeId][id].index])/aliveNodes[id].V)<=peerCriteria)
			return true;
		else
			return false;
	}

	else{
		if(((V-linkValueVector[linkIndex[nodeId][id].index])/aliveNodes[id].V)<=peerCriteria)
			return cbAnalysisForPaidDePeer(id);

		else
			return false;
	}

}

bool Node::peeringStrategy1(int id){

	if(id==-1)
		return false;

	if(aliveNodes[id].peeringStrategyNumber!=5){

		/*
		if(numSimulations<2){
			if(!I.empty() || !aliveNodes[id].I.empty())
				return false;
		}
		*/

		if(isGrandOpenAllowed==true){

				return true;
		}

		else{

			if((I.empty() && isMajorContentNet==false && !aliveNodes[id].I.empty()) || (!I.empty() && aliveNodes[id].I.empty() && aliveNodes[id].isMajorContentNet==false)){
			//if((I.empty() && !aliveNodes[id].I.empty()) || (!I.empty() && aliveNodes[id].I.empty())){
				return false;
			}

			else
				return true;

		}

	}

	else
		return cbAnalysisForPaidPeer(id);

}

bool Node::dePeeringStrategy1(int id){

	if(Q==-1 && aliveNodes[id].Q==-1)
		return true;

	else{
		if(aliveNodes[id].peeringStrategyNumber!=5)
			return true;

		else
			return cbAnalysisForPaidDePeer(id);
	}
}

bool Node::peeringStrategy2(int id){

	//peer by necessity only
	peerCriteria=universalSigma;

	if(id==-1)return false;

	if(aliveNodes[id].Q!=-1)
		return false;

	else
		return false;
}

bool Node::dePeeringStrategy2(int id){

	return false;
}


//selective-open hybrid
bool Node::peeringStrategy3(int id){


	/*
	//total volume based strategy
	peerCriteria=universalSigma;

	if(id==-1)return false;

	if(aliveNodes[id].peeringStrategyNumber!=5){
		if(aliveNodes[id].netClass==Ordinary){
			if((V/aliveNodes[id].V)<=peerCriteria)
				return true;
		}

		else if(aliveNodes[id].netClass==CC || aliveNodes[id].netClass==CP)
			return true;

		else
			return false;
	}

	else{

		if(aliveNodes[id].netClass==Ordinary){
			if((V/aliveNodes[id].V)<=peerCriteria)
				return cbAnalysisForPaidPeer(id);
		}

		else if(aliveNodes[id].netClass==CC || aliveNodes[id].netClass==CP)
			return cbAnalysisForPaidPeer(id);

		else
			return false;

	}*/

	//total volume based strategy
	peerCriteria=universalSigma2;

	if(id==-1)return false;

	if(aliveNodes[id].peeringStrategyNumber!=5){
		if((V/aliveNodes[id].V)<=peerCriteria)
			return true;
		else
			return false;
	}//end if

	else{	//y uses paid peering strategy

		if((V/aliveNodes[id].V)<=peerCriteria){
			return cbAnalysisForPaidPeer(id);

		}

		else
			return false;
	}//end else


}

bool Node::dePeeringStrategy3(int id){

	if(aliveNodes[id].peeringStrategyNumber!=5){
		if(((V-linkValueVector[linkIndex[nodeId][id].index])/aliveNodes[id].V)<=peerCriteria)
			return true;
		else
			return false;
	}

	else{
		if(((V-linkValueVector[linkIndex[nodeId][id].index])/aliveNodes[id].V)<=peerCriteria)
			return cbAnalysisForPaidDePeer(id);

		else
			return false;
	}

	/*
	if(aliveNodes[id].peeringStrategyNumber!=5){
		if(aliveNodes[id].netClass==Ordinary){
			if(((V-linkValueVector[linkIndex[nodeId][id].index])/aliveNodes[id].V)<=peerCriteria)
				return true;
		}

		else if(aliveNodes[id].netClass==CP || aliveNodes[id].netClass==CC)
			return true;

		else
			return false;
	}

	else{

		if(aliveNodes[id].netClass==Ordinary){
			if((V/aliveNodes[id].V)<=peerCriteria)
				return cbAnalysisForPaidDePeer(id);
		}

		else if(aliveNodes[id].netClass==CC || aliveNodes[id].netClass==CP)
			return cbAnalysisForPaidDePeer(id);

		else
			return false;

	}*/

}

//cost benefit peering strategy
bool Node::peeringStrategy4(int id){

	/*
	if(id==-1)
		return false;

	bool shouldPeer=false;

	double currentFitness=fitness;

	saveNetworkState();

	getNewPeer(id);
	routingScale();
	updateFitness();

	if(fitness>currentFitness)
		shouldPeer=true;

	restoreNetworkState();

#if DEBUG
	if(shouldPeer)
		logFile<<"Node "<<nodeId<<" with strategy 4 approved peering with "<<id<<endl;
#endif

	return shouldPeer;
	*/

	//total volume based strategy
	peerCriteria=universalSigma;

	if(id==-1)return false;

	list<int> startList;
	list<int> endList;
	list<int> startRemove;
	list<int> endRemove;
	list<int>::iterator it;
	list<int>::iterator itToRemove;
	list<twoPair> pairs;
	list<twoPair>::iterator itPair;
	list<twoPair>::iterator itPairRemove;
	twoPair tmpPair;
	list<twoPair> pairToRemove;
	double trafficExchange=0;
	list<int> linksTraversed;
	double existingCost=0;
	double potentialCost=0;
	double providerCost=0;
	double peeringCost=0;
	int numPeeringLinksTraversed=0;
	int angelPeer=-1;

	/*
	mergeTwoListsScale(startList,J);
	mergeTwoListsScale(endList,aliveNodes[id].J);

	startList.push_front(nodeId);
	endList.push_front(id);

	if(!K.empty())
		for(it=K.begin();it!=K.end();it++){
			linksTraversed.push_back(linkIndex[nodeId][*it].index);
		}

	if(Q!=-1)
		linksTraversed.push_back(linkIndex[nodeId][Q].index);


	for(it=startList.begin();it!=startList.end();it++)
		for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){

			tmpPair.n1=flowIndex[*it][*itToRemove];
			tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);
			pairs.push_back(tmpPair);

		}

	for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
		for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
			if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
				trafficExchange+=(*itPair).n2;

			}

	 */

	/*
	for(it=endList.begin();it!=endList.end();it++)
		if(isPeer(*it)){
			endRemove.push_back(*it);
			mergeTwoListsScale(endRemove,aliveNodes[*it].J);
		}

	for(it=startList.begin();it!=startList.end();it++)
		if(aliveNodes[id].isPeer(*it)){
			startRemove.push_back(*it);
			mergeTwoListsScale(startRemove,aliveNodes[*it].J);
		}

	for(it=startRemove.begin();it!=startRemove.end();it++)
		startList.remove(*it);

	for(it=endRemove.begin();it!=endRemove.end();it++)
		endList.remove(*it);

	startRemove.clear();
	endRemove.clear();

	startList.push_front(nodeId);
	endList.push_front(id);

	for(it=startList.begin();it!=startList.end();it++)
		for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){

			tmpPair.n1=flowIndex[*it][*itToRemove];
			tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);
			pairs.push_back(tmpPair);

		}
	*/

	trafficExchange=estimateTrafficExchange(nodeId,id);

#if 0
	logFile<<"Node "<<nodeId<<" and "<<id<<" exchange traffic "<<trafficExchange<<endl;
#endif

	if(aliveNodes[id].isPresentInCustomerTreeOfPeer(nodeId)!=-1){	//nodeId in customer tree of peer of id

		if((angelPeer=isPresentInCustomerTreeOfPeer(id))!=-1){	//potential peer in customer tree of peer

			/*
		for(it=K.begin();it!=K.end();it++){
			linksTraversed.push_back(linkIndex[nodeId][*it].index);
		}

		for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
			for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
				if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
					trafficExchange+=(*itPair).n2;
					numPeeringLinksTraversed=*itToRemove;

				}
			 */


			if(aliveNodes[angelPeer].peeringStrategyNumber==5){

				if(aliveNodes[id].peeringStrategyNumber==5){

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent);
					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent)+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent)+providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent);


				}

				else{

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent);
					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent)+providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent);

				}


			}

			else{

				if(aliveNodes[id].peeringStrategyNumber==5){

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent);
					potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent)+pow(trafficExchange,peeringExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent)+providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent);

				}

				else{

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent);
					potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent)+pow(trafficExchange,peeringExponent))+providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent);

				}

			}


			if(potentialCost<existingCost)
				return true;
			else
				return false;


		}//end if

		else{		//potential peer not in customer tree of any peer

			if(Q==-1){
				string str="ERROR!! Potential peer not in customer tree of any peer of T1";
				cout<<"ERROR!! Error in Cost-Benefit analysis"<<endl;
				endSimulation(str);
				return false;
			}//end if

			else{

				/*
			linksTraversed.push_back(linkIndex[nodeId][Q].index);

			for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
				for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
					if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
						trafficExchange+=(*itPair).n2;

					}
				 */

				if(aliveNodes[id].peeringStrategyNumber!=5){
					existingCost=providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent));
				}

				else{
					existingCost=providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);

				}

				if(potentialCost<existingCost)
					return true;
				else
					return false;

			}//end else

		}//end else

	}//end if node not present in customer tree of potential peer

	else{	//node not present in the customer tree of peer of potential node

		if((angelPeer=isPresentInCustomerTreeOfPeer(id))!=-1){	//potential peer in customer tree of peer

			/*
				for(it=K.begin();it!=K.end();it++){
					linksTraversed.push_back(linkIndex[nodeId][*it].index);
				}

				for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
					for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
						if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
							trafficExchange+=(*itPair).n2;
							numPeeringLinksTraversed=*itToRemove;

						}
			 */


			if(aliveNodes[angelPeer].peeringStrategyNumber==5){

				if(aliveNodes[id].peeringStrategyNumber==5){

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent);
					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent)+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);


				}

				else{

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent);
					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent);

				}


			}

			else{

				if(aliveNodes[id].peeringStrategyNumber==5){

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
					potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent)+pow(trafficExchange,peeringExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);

				}

				else{


					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
					potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent)+pow(trafficExchange,peeringExponent));

				}

			}

			if(potentialCost<existingCost)
				return true;
			else
				return false;


		}//end if

		else{		//potential peer not in customer tree of any peer

			if(Q==-1){
				string str="ERROR!! Potential peer not in customer tree of any peer of T1";
				cout<<"ERROR!! Error in Cost-Benefit analysis"<<endl;
				endSimulation(str);
				return false;
			}//end if

			else{

				/*
					linksTraversed.push_back(linkIndex[nodeId][Q].index);

					for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
						for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
							if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
								trafficExchange+=(*itPair).n2;

							}
				 */

				if(aliveNodes[id].peeringStrategyNumber!=5){
					existingCost=providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent));
				}

				else{
					existingCost=providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);

				}

				if(potentialCost<existingCost)
					return true;
				else
					return false;

			}//end else

		}

	}
}

bool Node::dePeeringStrategy4(int id){

	/*
	bool shouldDePeer=false;

	double currentFitness=fitness;

	saveNetworkState();

	dePeerSingular(id);
	routingScale();
	updateFitness();

	if(fitness>currentFitness)
		shouldDePeer=true;

	restoreNetworkState();

	return shouldDePeer;
	*/
	list<int> startList;
	list<int> endList;
	list<int> startRemove;
	list<int> endRemove;
	list<int>::iterator it;
	list<int>::iterator itToRemove;
	list<twoPair> pairs;
	list<twoPair>::iterator itPair;
	list<twoPair>::iterator itPairRemove;
	twoPair tmpPair;
	list<twoPair> pairToRemove;
	double trafficExchange=0;
	double trafficExchangeFrom=0;
	double trafficExchangeTo=0;
	list<int> linksTraversed;
	double existingCost=0;
	double potentialCost=0;
	double providerCost=0;
	double peeringCost=0;
	int angelPeer=-1;

	//depeer someone who is in customer tree
	if(isPresentInCustomerTree(id))
		return false;

	//if both are Tier-1 just adopt a conservative approach and do not depeer
	if(Q==-1 && aliveNodes[id].Q==-1)
		return true;

	else{

		trafficExchange=linkValueVector[linkIndex[nodeId][id].index];


		if(aliveNodes[id].isPresentInCustomerTreeOfPeer(nodeId)!=-1){	//nodeId present in the customer tree of peer of id

			if((angelPeer=isPresentInCustomerTreeOfPeer(id))!=-1){	//peer is present in customer tree of another peer

				if(aliveNodes[angelPeer].peeringStrategyNumber==5){

					if(aliveNodes[id].peeringStrategyNumber==5){

						existingCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);
						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent);

					}

					else{

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent);
						potentialCost=peeringCostMultiplier*(pow(trafficExchange+linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent);

					}

				}

				else{

					if(aliveNodes[id].peeringStrategyNumber==5){

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+aliveNodes[id].paidPeeringPrice*(pow(trafficExchange,peeringExponent));
						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));

					}

					else{

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));

					}

				}

				if(existingCost<potentialCost)
					return true;

				else
					return false;

			}

			else{	//peer is not present in customer tree of any peer

				if(aliveNodes[id].peeringStrategyNumber==5){

					existingCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent)+providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
					potentialCost=providerCostMultiplier*(providerPrice*pow(trafficExchange+linkValueVector[linkIndex[nodeId][Q].index],providerExponent));


				}

				else{

					existingCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
					potentialCost=providerCostMultiplier*(providerPrice*pow(trafficExchange+linkValueVector[linkIndex[nodeId][Q].index],providerExponent));

				}


				if(existingCost<potentialCost)
					return true;

				else
					return false;


			}

		}

		else{	//nodeId not present in the customer tree of peer of id

			if((angelPeer=isPresentInCustomerTreeOfPeer(id))!=-1){	//peer is present in customer tree of another peer

				if(aliveNodes[angelPeer].peeringStrategyNumber==5){

					if(aliveNodes[id].peeringStrategyNumber==5){

						existingCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);
						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent);

					}

					else{

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent);
						potentialCost=peeringCostMultiplier*(pow(trafficExchange+linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent);

					}

				}

				else{

					if(aliveNodes[id].peeringStrategyNumber==5){

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+aliveNodes[id].paidPeeringPrice*(pow(trafficExchange,peeringExponent));
						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));

					}

					else{

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent));
						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));

					}

				}

				if(existingCost<potentialCost)
					return true;

				else
					return false;

			}

			else{	//peer is not present in customer tree of any peer

				if(aliveNodes[id].peeringStrategyNumber==5){

					existingCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent)+providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
					potentialCost=providerCostMultiplier*(providerPrice*pow(trafficExchange+linkValueVector[linkIndex[nodeId][Q].index],providerExponent));


				}

				else{

					existingCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
					potentialCost=providerCostMultiplier*(providerPrice*pow(trafficExchange+linkValueVector[linkIndex[nodeId][Q].index],providerExponent));

				}


				if(existingCost<potentialCost)
					return true;

				else
					return false;


			}

		}

	}

}

//paid peering strategy
bool Node::peeringStrategy5(int id){


	peerCriteria=universalSigma;

	if(id==-1)return false;

	list<int> startList;
	list<int> endList;
	list<int> startRemove;
	list<int> endRemove;
	list<int>::iterator it;
	list<int>::iterator itToRemove;
	list<twoPair> pairs;
	list<twoPair>::iterator itPair;
	list<twoPair>::iterator itPairRemove;
	twoPair tmpPair;
	list<twoPair> pairToRemove;
	double trafficExchange=0;
	list<int> linksTraversed;
	double existingCost=0;
	double existingRevenue=0;
	double potentialRevenue=0;
	double potentialCost=0;
	int numPeeringLinksTraversed=0;
	int angelPeer=-1;
	double adoptPaidPeeringPrice=0;

#if DEBUG
	logFile<<"Node "<<nodeId<<" strategy 5 evaluating node "<<id<<" strategy "<<aliveNodes[id].peeringStrategyNumber<<" for peering"<<endl;
#endif

	/*
	mergeTwoListsScale(startList,J);
	mergeTwoListsScale(endList,aliveNodes[id].J);

	startList.push_front(nodeId);
	endList.push_front(id);

	if(!K.empty())
		for(it=K.begin();it!=K.end();it++){
			linksTraversed.push_back(linkIndex[nodeId][*it].index);
		}

	if(Q!=-1)
		linksTraversed.push_back(linkIndex[nodeId][Q].index);


	for(it=startList.begin();it!=startList.end();it++)
		for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){


#if DEBUG
			logFile<<"Creating pair "<<*it<<" and "<<*itToRemove<<endl;
#endif
			tmpPair.n1=flowIndex[*it][*itToRemove];
			tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);
			pairs.push_back(tmpPair);

		}

	for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
		for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
			if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){

#if DEBUG
				logFile<<"Link index "<<*itToRemove<<" being used for flow index "<<(*itPair).n1<<endl;
#endif

				trafficExchange+=(*itPair).n2;

			}

	*/



	/*
	for(it=endList.begin();it!=endList.end();it++)
		if(isPeer(*it)){
			endRemove.push_back(*it);
			mergeTwoListsScale(endRemove,aliveNodes[*it].J);
		}

	for(it=startList.begin();it!=startList.end();it++)
		if(aliveNodes[id].isPeer(*it)){
			startRemove.push_back(*it);
			mergeTwoListsScale(startRemove,aliveNodes[*it].J);
		}

	for(it=startRemove.begin();it!=startRemove.end();it++)
		startList.remove(*it);

	for(it=endRemove.begin();it!=endRemove.end();it++)
		endList.remove(*it);

	startRemove.clear();
	endRemove.clear();

	startList.push_front(nodeId);
	endList.push_front(id);

	for(it=startList.begin();it!=startList.end();it++)
		for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){

			tmpPair.n1=flowIndex[*it][*itToRemove];
			tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);
			pairs.push_back(tmpPair);

		}
	*/

	trafficExchange=estimateTrafficExchange(nodeId,id);

	#if DEBUG
		logFile<<"Node "<<nodeId<<" and "<<id<<" exchange traffic "<<trafficExchange<<endl;
	#endif


	if((angelPeer=isPresentInCustomerTreeOfPeer(id))!=-1){	//potential peer in customer tree of peer

#if DEBUG
		logFile<<"Node "<<id<<" is present in customer tree of peer "<<angelPeer<<" with strategy "<<aliveNodes[angelPeer].peeringStrategyNumber<<" of node "<<nodeId<<endl;
#endif

		/*
		for(it=K.begin();it!=K.end();it++){
			linksTraversed.push_back(linkIndex[nodeId][*it].index);
		}

		for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
			for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
				if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
					trafficExchange+=(*itPair).n2;
					numPeeringLinksTraversed=*itToRemove;

				}
		*/

#if DEBUG
		logFile<<"Node "<<nodeId<<" and node "<<id<<" exchange "<<trafficExchange<<endl;
		logFile<<"Node "<<nodeId<<" and node "<<angelPeer<<" have "<<linkValueVector[linkIndex[nodeId][angelPeer].index]<<" traffic on their link"<<endl;
#endif

		if((aliveNodes[id].peeringStrategyNumber!=5) || (aliveNodes[id].peeringStrategyNumber==5 && aliveNodes[id].paidPeeringPrice<paidPeeringPrice)){	//if y does not use paid peering


			if(aliveNodes[id].peeringStrategyNumber==5){
				adoptPaidPeeringPrice=paidPeeringPrice-aliveNodes[id].paidPeeringPrice;
#if DEBUG
			logFile<<"Node "<<nodeId<<" has ppp: "<<paidPeeringPrice<<" and node "<<id<<" has ppp: "<<aliveNodes[id].paidPeeringPrice<<endl;
#endif
			}

			else{
				adoptPaidPeeringPrice=paidPeeringPrice;
#if DEBUG
			logFile<<"Node "<<nodeId<<" has ppp: "<<paidPeeringPrice<<endl;
#endif

			}

			if(aliveNodes[angelPeer].peeringStrategyNumber!=5){

				existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
				existingRevenue=paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent);

				potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent));
				potentialRevenue=paidPeeringPrice*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);

			}//end if

			else{

#if DEBUG
			logFile<<"Node "<<angelPeer<<" has ppp: "<<aliveNodes[angelPeer].paidPeeringPrice<<endl;
#endif

				if(aliveNodes[angelPeer].paidPeeringPrice>paidPeeringPrice){

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+(aliveNodes[angelPeer].paidPeeringPrice-paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
					existingRevenue=0;

					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+(aliveNodes[angelPeer].paidPeeringPrice-paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent));
					potentialRevenue=adoptPaidPeeringPrice*(pow(trafficExchange,peeringExponent));

				}//end if

				else{

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
					existingRevenue=(paidPeeringPrice-aliveNodes[angelPeer].paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));

					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent));
					potentialRevenue=adoptPaidPeeringPrice*(pow(trafficExchange,peeringExponent))+(paidPeeringPrice-aliveNodes[angelPeer].paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent));

				}//end else

			}//end else

		}//end if

		else{

#if DEBUG
			logFile<<"Node "<<nodeId<<" has ppp: "<<paidPeeringPrice<<" and node "<<id<<" has ppp: "<<aliveNodes[id].paidPeeringPrice<<endl;
#endif

			adoptPaidPeeringPrice=aliveNodes[id].paidPeeringPrice-paidPeeringPrice;

			if(aliveNodes[angelPeer].peeringStrategyNumber!=5){

				existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
				existingRevenue=paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent);

				potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+adoptPaidPeeringPrice*(pow(trafficExchange,peeringExponent));
				potentialRevenue=paidPeeringPrice*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent));

			}//end if

			else{

				if(aliveNodes[angelPeer].paidPeeringPrice>paidPeeringPrice){

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+(aliveNodes[angelPeer].paidPeeringPrice-paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
					existingRevenue=0;

					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+(aliveNodes[angelPeer].paidPeeringPrice-paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+adoptPaidPeeringPrice*(pow(trafficExchange,peeringExponent));
					potentialRevenue=0;

				}//end if

				else{

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
					existingRevenue=(paidPeeringPrice-aliveNodes[angelPeer].paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));

					potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+adoptPaidPeeringPrice*(pow(trafficExchange,peeringExponent));
					potentialRevenue=(paidPeeringPrice-aliveNodes[angelPeer].paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent));

				}//end else

			}//end else

		}//end else

	}//end if

	else{		//potential peer not in customer tree of peer

		if(Q==-1){
			string str="ERROR!! Potential peer not in customer tree of any peer of T1";
			cout<<"ERROR!! Error in Cost-Benefit analysis"<<endl;
			endSimulation(str);
			return false;
		}//end if

		else{

#if DEBUG
		logFile<<"Node "<<id<<" is not present in any customer tree of peer of node "<<nodeId<<endl;
#endif

		/*
			linksTraversed.push_back(linkIndex[nodeId][Q].index);

			for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
				for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
					if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
						trafficExchange+=(*itPair).n2;

					}
		*/

#if DEBUG
		logFile<<"Node "<<nodeId<<" and "<<id<<" exchange traffic "<<trafficExchange<<endl;
		logFile<<"Node "<<nodeId<<" has provider price "<<providerPrice<<endl;
		logFile<<"Node "<<nodeId<<" exchanges traffic "<<linkValueVector[linkIndex[nodeId][Q].index]<<" with its provider "<<Q<<endl;
#endif

			if(aliveNodes[id].peeringStrategyNumber!=5 || (aliveNodes[id].peeringStrategyNumber==5 && aliveNodes[id].paidPeeringPrice<paidPeeringPrice)){


				if(aliveNodes[id].peeringStrategyNumber==5){
					adoptPaidPeeringPrice=paidPeeringPrice-aliveNodes[id].paidPeeringPrice;
#if DEBUG
		logFile<<"Node "<<nodeId<<" has ppp: "<<paidPeeringPrice<<" and node "<<id<<" has ppp: "<<aliveNodes[id].paidPeeringPrice<<endl;
#endif
				}
				else{

#if DEBUG
		logFile<<"Node "<<nodeId<<" has ppp: "<<paidPeeringPrice<<endl;
#endif

					adoptPaidPeeringPrice=paidPeeringPrice;
				}

				existingCost=providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent);
				existingRevenue=0;

				potentialCost=providerCostMultiplier*providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent)+peeringCostMultiplier*pow(trafficExchange,peeringExponent);
				potentialRevenue=adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);

			}//end if

			else{

				adoptPaidPeeringPrice=aliveNodes[id].paidPeeringPrice-paidPeeringPrice;

				existingCost=providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent);
				existingRevenue=0;

				potentialCost=providerCostMultiplier*providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent)+adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent)+peeringCostMultiplier*pow(trafficExchange,peeringExponent);
				potentialRevenue=0;

			}//end else

		}//end else

	}//end else

#if DEBUG
	logFile<<"For node "<<nodeId<<" EC: "<<existingCost<<" ER: "<<existingRevenue<<" PC: "<<potentialCost<<" PR: "<<potentialRevenue<<endl;
#endif

	if((potentialRevenue-potentialCost)>(existingRevenue-existingCost))
		return true;
	else
		return false;

}

bool Node::dePeeringStrategy5(int id){

	list<int> startList;
	list<int> endList;
	list<int> startRemove;
	list<int> endRemove;
	list<int>::iterator it;
	list<int>::iterator itToRemove;
	list<twoPair> pairs;
	list<twoPair>::iterator itPair;
	list<twoPair>::iterator itPairRemove;
	twoPair tmpPair;
	list<twoPair> pairToRemove;
	double trafficExchange=0;
	list<int> linksTraversed;
	double existingCost=0;
	double existingRevenue=0;
	double potentialRevenue=0;
	double potentialCost=0;
	double providerCost=0;
	double peeringCost=0;
	int angelPeer=-1;
	double adoptPaidPeeringPrice=0;

	//depeer someone who is in customer tree
	if(isPresentInCustomerTree(id))
		return false;

	//if both are Tier-1 just adopt a conservative approach and do not depeer
	if(Q==-1 && aliveNodes[id].Q==-1)
		return true;

	else{

		trafficExchange=linkValueVector[linkIndex[nodeId][id].index];

		if((angelPeer=isPresentInCustomerTreeOfPeer(id))!=-1){

			if((aliveNodes[id].peeringStrategyNumber!=5) || (aliveNodes[id].peeringStrategyNumber==5 && aliveNodes[id].paidPeeringPrice<paidPeeringPrice)){	//if y does not use paid peering

				if(aliveNodes[id].peeringStrategyNumber==5)
					adoptPaidPeeringPrice=paidPeeringPrice-aliveNodes[id].paidPeeringPrice;

				else
					adoptPaidPeeringPrice=paidPeeringPrice;

				if(aliveNodes[angelPeer].peeringStrategyNumber!=5){

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent));
					existingRevenue=paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);

					potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));
					potentialRevenue=paidPeeringPrice*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));

				}//end if z is not using pp

				else{

					if(aliveNodes[angelPeer].paidPeeringPrice>paidPeeringPrice){

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+(aliveNodes[angelPeer].paidPeeringPrice-paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
						existingRevenue=adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);

						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent))+(aliveNodes[angelPeer].paidPeeringPrice-paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));
						potentialRevenue=0;

					}//end if z.ppp>x.ppp

					else{

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent));
						existingRevenue=(paidPeeringPrice-aliveNodes[angelPeer].paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);

						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));
						potentialRevenue=(paidPeeringPrice-aliveNodes[angelPeer].paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));

					}//end else z.ppp<x.ppp

				}//end else z is using pp

			}//end if y is not using paid peering or y.ppp<x.ppp

			else{

				adoptPaidPeeringPrice=aliveNodes[id].paidPeeringPrice-paidPeeringPrice;

				if(aliveNodes[angelPeer].peeringStrategyNumber!=5){

					existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);
					existingRevenue=paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent);

					potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent))+adoptPaidPeeringPrice*(pow(trafficExchange,peeringExponent));
					potentialRevenue=paidPeeringPrice*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));

				}//end if

				else{

					if(aliveNodes[angelPeer].paidPeeringPrice>paidPeeringPrice){

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+(aliveNodes[angelPeer].paidPeeringPrice-paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);
						existingRevenue=0;

						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent))+(aliveNodes[angelPeer].paidPeeringPrice-paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent))+adoptPaidPeeringPrice*(pow(trafficExchange,peeringExponent));
						potentialRevenue=0;

					}//end if

					else{

						existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);
						existingRevenue=(paidPeeringPrice-aliveNodes[angelPeer].paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));

						potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent))+adoptPaidPeeringPrice*(pow(trafficExchange,peeringExponent));
						potentialRevenue=(paidPeeringPrice-aliveNodes[angelPeer].paidPeeringPrice)*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));

					}//end else

				}//end else

			}//end else y is using ppp and y.ppp>x.ppp

		}//end if present in customer tree of peer

		else{

			if(aliveNodes[id].peeringStrategyNumber!=5 || (aliveNodes[id].peeringStrategyNumber==5 && aliveNodes[id].paidPeeringPrice<paidPeeringPrice)){

				if(aliveNodes[id].peeringStrategyNumber==5)
					adoptPaidPeeringPrice=paidPeeringPrice-aliveNodes[id].paidPeeringPrice;
				else
					adoptPaidPeeringPrice=paidPeeringPrice;

				existingCost=providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent)+peeringCostMultiplier*pow(trafficExchange,peeringExponent);
				existingRevenue=adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);

				potentialCost=providerCostMultiplier*providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index]+trafficExchange,providerExponent);
				potentialRevenue=0;

			}//end if

			else{

				adoptPaidPeeringPrice=aliveNodes[id].paidPeeringPrice-paidPeeringPrice;

				existingCost=providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent)+peeringCostMultiplier*pow(trafficExchange,peeringExponent)+adoptPaidPeeringPrice*pow(trafficExchange,peeringExponent);
				existingRevenue=0;

				potentialCost=providerCostMultiplier*providerPrice*pow(linkValueVector[linkIndex[nodeId][Q].index]+trafficExchange,providerExponent);
				potentialRevenue=0;

			}//end else

		}//end else not present in customer tree of peer


		if((potentialRevenue-potentialCost)>(existingRevenue-existingCost))
			return false;
		else
			return true;

	}//end else actual calculation

}

bool Node::cbAnalysisForPaidPeer(int id){

	list<int> startList;
	list<int> endList;
	list<int> startRemove;
	list<int> endRemove;
	list<int>::iterator it;
	list<int>::iterator itToRemove;
	list<twoPair> pairs;
	list<twoPair>::iterator itPair;
	list<twoPair>::iterator itPairRemove;
	twoPair tmpPair;
	list<twoPair> pairToRemove;
	double trafficExchange=0;
	list<int> linksTraversed;
	double existingCost=0;
	double potentialCost=0;
	int numPeeringLinksTraversed=0;
	int angelPeer=-1;

#if DEBUG
		logFile<<"Node "<<nodeId<<" with strategy "<<peeringStrategyNumber<<" doing cb-analysis for node "<<id<<endl;
#endif

	/*
	mergeTwoListsScale(startList,J);
	mergeTwoListsScale(endList,aliveNodes[id].J);

	startList.push_front(nodeId);
	endList.push_front(id);

	if(!K.empty())
		for(it=K.begin();it!=K.end();it++){
			linksTraversed.push_back(linkIndex[nodeId][*it].index);
		}

	if(Q!=-1)
		linksTraversed.push_back(linkIndex[nodeId][Q].index);


	for(it=startList.begin();it!=startList.end();it++)
		for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){

#if DEBUG
			logFile<<"Creating pair "<<*it<<" and "<<*itToRemove<<endl;
#endif

			tmpPair.n1=flowIndex[*it][*itToRemove];
			tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);
			pairs.push_back(tmpPair);

		}

	for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
		for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
			if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){

#if DEBUG
				logFile<<"Link index "<<*itToRemove<<" being used for flow index "<<(*itPair).n1<<endl;
#endif
				trafficExchange+=(*itPair).n2;

			}
	*/

	/*
	for(it=endList.begin();it!=endList.end();it++)
		if(isPeer(*it)){
			endRemove.push_back(*it);
			mergeTwoListsScale(endRemove,aliveNodes[*it].J);
		}

	for(it=startList.begin();it!=startList.end();it++)
		if(aliveNodes[id].isPeer(*it)){
			startRemove.push_back(*it);
			mergeTwoListsScale(startRemove,aliveNodes[*it].J);
		}

	for(it=startRemove.begin();it!=startRemove.end();it++)
		startList.remove(*it);

	for(it=endRemove.begin();it!=endRemove.end();it++)
		endList.remove(*it);

	startRemove.clear();
	endRemove.clear();

	startList.push_front(nodeId);
	endList.push_front(id);

	for(it=startList.begin();it!=startList.end();it++)
		for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){

			tmpPair.n1=flowIndex[*it][*itToRemove];
			tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);
			pairs.push_back(tmpPair);

		}
	*/

	trafficExchange=estimateTrafficExchange(nodeId,id);

#if DEBUG
		logFile<<"Node "<<nodeId<<" and "<<id<<" exchange traffic "<<trafficExchange<<endl;
#endif


	if((angelPeer=isPresentInCustomerTreeOfPeer(id))!=-1){	//potential peer in customer tree of peer

#if DEBUG
		logFile<<"Node "<<id<<" is present in customer tree of peer "<<angelPeer<<endl;
#endif

		/*
		for(it=K.begin();it!=K.end();it++){
			linksTraversed.push_back(linkIndex[nodeId][*it].index);
		}

		for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
			for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
				if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
					trafficExchange+=(*itPair).n2;
					numPeeringLinksTraversed=*itToRemove;

				}
		*/

#if DEBUG
		logFile<<"Node "<<nodeId<<" and node "<<id<<" exchange traffic "<<trafficExchange<<endl;
#endif

		if(aliveNodes[angelPeer].peeringStrategyNumber==5){

			existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent);
			potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent)+pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent)+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);

		}

		else{

			existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent));
			potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]-trafficExchange,peeringExponent)+pow(trafficExchange,peeringExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);

		}

#if DEBUG
		logFile<<"For node "<<nodeId<<" EC: "<<existingCost<<" and PC: "<<potentialCost<<endl;
#endif

		if(potentialCost<existingCost)
			return true;
		else
			return false;


	}//end if

	else{		//potential peer not in customer tree

		/*if(Q==-1){
			string str="ERROR!! Potential peer not in customer tree of any peer of T1";
			cout<<"ERROR!! Error in Cost-Benefit analysis"<<endl;
			endSimulation(str);
			return false;
		}//end if

		else*/{

#if DEBUG
		logFile<<"Node "<<id<<" not present in any customer tree of peer of "<<nodeId<<endl;
#endif

			/*
			linksTraversed.push_back(linkIndex[nodeId][Q].index);

			for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
				for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
					if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
						trafficExchange+=(*itPair).n2;

					}
			*/

#if DEBUG
		logFile<<"Node "<<nodeId<<" and node "<<id<<" exchange traffic "<<trafficExchange<<endl;
		logFile<<"Node "<<nodeId<<" and its provider with price "<<providerPrice<<" exchange traffic "<<linkValueVector[linkIndex[nodeId][Q].index]<<endl;
#endif

			existingCost=providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent));
			potentialCost=peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index]-trafficExchange,providerExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);

#if DEBUG
		logFile<<"For node "<<nodeId<<" EC: "<<existingCost<<" and PC: "<<potentialCost<<endl;
#endif

			if(potentialCost<existingCost)
				return true;
			else
				return false;

		}//end else

	}//end else

}

bool Node::cbAnalysisForPaidDePeer(int id){

	list<int> startList;
	list<int> endList;
	list<int> startRemove;
	list<int> endRemove;
	list<int>::iterator it;
	list<int>::iterator itToRemove;
	list<twoPair> pairs;
	list<twoPair>::iterator itPair;
	list<twoPair>::iterator itPairRemove;
	twoPair tmpPair;
	list<twoPair> pairToRemove;
	double trafficExchange=0;
	list<int> linksTraversed;
	double existingCost=0;
	double potentialCost=0;
	double providerCost=0;
	double peeringCost=0;
	int numPeeringLinksTraversed=0;
	int angelPeer=-1;


#if DEBUG
		logFile<<"Node "<<nodeId<<" with strategy "<<peeringStrategyNumber<<" doing dePeer cb-analysis for node "<<id<<endl;
#endif

		/*
	mergeTwoListsScale(startList,J);
	mergeTwoListsScale(endList,aliveNodes[id].J);

	startList.push_front(nodeId);
	endList.push_front(id);

	for(it=endList.begin();it!=endList.end();it++)
		if(isPeer(*it)){
			endRemove.push_back(*it);
			mergeTwoListsScale(endRemove,aliveNodes[*it].J);
		}

	for(it=startList.begin();it!=startList.end();it++)
		if(aliveNodes[id].isPeer(*it)){
			startRemove.push_back(*it);
			mergeTwoListsScale(startRemove,aliveNodes[*it].J);
		}

	for(it=startRemove.begin();it!=startRemove.end();it++)
		startList.remove(*it);

	for(it=endRemove.begin();it!=endRemove.end();it++)
		endList.remove(*it);

	startRemove.clear();
	endRemove.clear();

	for(it=startList.begin();it!=startList.end();it++)
		for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){

#if DEBUG
			logFile<<"Creating pair of "<<*it<<" and "<<*itToRemove<<endl;
#endif

			tmpPair.n1=flowIndex[*it][*itToRemove];
			tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);
			pairs.push_back(tmpPair);

		}
		*/

	trafficExchange=linkValueVector[linkIndex[nodeId][id].index];

	if((angelPeer=isPresentInCustomerTreeOfPeer(id))!=-1){	//potential peer in customer tree of peer

#if DEBUG
		logFile<<"Node "<<id<<" is present in customer tree of peer "<<angelPeer<<endl;
#endif


		/*
		for(it=K.begin();it!=K.end();it++){
			linksTraversed.push_back(linkIndex[nodeId][*it].index);
		}

		for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
			for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
				if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
					trafficExchange+=(*itPair).n2;
					numPeeringLinksTraversed=*itToRemove;

				}
		*/
#if DEBUG
		logFile<<"Node "<<nodeId<<" and node "<<id<<" exchange traffic "<<trafficExchange<<endl;
#endif

		if(aliveNodes[angelPeer].peeringStrategyNumber==5){

			existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);
			potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent))+aliveNodes[angelPeer].paidPeeringPrice*pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent);

		}

		else{

			existingCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index],peeringExponent)+pow(trafficExchange,peeringExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);
			potentialCost=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][angelPeer].index]+trafficExchange,peeringExponent));
		}

#if DEBUG
		logFile<<"For node "<<nodeId<<" EC: "<<existingCost<<" and PC: "<<potentialCost<<endl;
#endif

		if(potentialCost<existingCost)
			return false;
		else
			return true;


	}//end if

	else{		//potential peer not in customer tree

		/*if(Q==-1){
			string str="ERROR!! Potential peer not in customer tree of any peer of T1";
			cout<<"ERROR!! Error in Cost-Benefit analysis"<<endl;
			endSimulation(str);
			return false;
		}//end if

		else*/{

#if DEBUG
		logFile<<"Node "<<id<<" not present in any customer tree of peer of "<<nodeId<<endl;
#endif

			/*
			trafficExchange=linkValueVector[linkIndex[nodeId][id].index];

			for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
				for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
					if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
						trafficExchange+=(*itPair).n2;

					}
			*/
#if DEBUG
		logFile<<"Node "<<nodeId<<" and node "<<id<<" exchange traffic "<<trafficExchange<<endl;
#endif

			existingCost=providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index],providerExponent))+peeringCostMultiplier*(pow(trafficExchange,peeringExponent))+aliveNodes[id].paidPeeringPrice*pow(trafficExchange,peeringExponent);
			potentialCost=providerCostMultiplier*providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index]+trafficExchange,providerExponent));

#if DEBUG
		logFile<<"For node "<<nodeId<<" EC: "<<existingCost<<" and PC: "<<potentialCost<<endl;
#endif

			if(potentialCost<existingCost)
				return false;
			else
				return true;

		}//end else

	}//end else

}

bool Node::areAllPeersT1(){

	bool allPeersT1=true;
	list<int>::iterator it;

	if(K.empty())
		return true;

	else{
		for(it=K.begin();it!=K.end();it++)
			if(aliveNodes[*it].Q!=-1)
				return false;

		return true;

	}
}

void Node::selectPeeringStrategy(int selectedStrategy){

	peeringStrategyNumber=selectedStrategy;

	switch(peeringStrategyNumber){

	case 0:

		strategyPointer=&Node::peeringStrategy0;
		dStrategyPointer=&Node::dePeeringStrategy0;
		peeringStrategy0(-1);
		break;

	case 1:
		strategyPointer=&Node::peeringStrategy1;
		dStrategyPointer=&Node::dePeeringStrategy1;
		peeringStrategy1(-1);
		break;

	case 2:
		strategyPointer=&Node::peeringStrategy2;
		dStrategyPointer=&Node::dePeeringStrategy2;
		peeringStrategy2(-1);
		break;

	case 3:
		strategyPointer=&Node::peeringStrategy3;
		dStrategyPointer=&Node::dePeeringStrategy3;
		peeringStrategy3(-1);
		break;

	case 4:
		strategyPointer=&Node::peeringStrategy4;
		dStrategyPointer=&Node::dePeeringStrategy4;
		peeringStrategy4(-1);
		break;

	case 5:
		strategyPointer=&Node::peeringStrategy5;
		dStrategyPointer=&Node::dePeeringStrategy5;
		peeringStrategy5(-1);
		break;


	default:
		string str="Non-existing peering strategy selected";
		logFile<<"ERROR!!! Non-existing peering strategy "<<peeringStrategyNumber<<" chose by node "<<nodeId<<endl;
		endSimulation(str);

	}
}

bool Node::evaluatePeeringThreshold(int id){

		list<int> startList;
		list<int> endList;
		list<int> startRemove;
		list<int> endRemove;
		list<int>::iterator it;
		list<int>::iterator itToRemove;
		list<twoPair> pairs;
		list<twoPair>::iterator itPair;
		list<twoPair>::iterator itPairRemove;
		twoPair tmpPair;
		list<twoPair> pairToRemove;
		double trafficExchange=0;
		list<int> linksTraversed;

		mergeTwoListsScale(startList,J);
		mergeTwoListsScale(endList,aliveNodes[id].J);

		startList.push_front(nodeId);
		endList.push_front(id);

		if(!K.empty())
			for(it=K.begin();it!=K.end();it++){
				linksTraversed.push_back(linkIndex[nodeId][*it].index);
			}

		if(Q!=-1)
			linksTraversed.push_back(linkIndex[nodeId][Q].index);


		for(it=startList.begin();it!=startList.end();it++)
			for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){

				tmpPair.n1=flowIndex[*it][*itToRemove];
				tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);
				pairs.push_back(tmpPair);

			}

		for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
			for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
				if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
					trafficExchange+=(*itPair).n2;

				}



		/*
		for(it=endList.begin();it!=endList.end();it++)
			if(isPeer(*it)){
				endRemove.push_back(*it);
				mergeTwoListsScale(endRemove,aliveNodes[*it].J);
			}

		for(it=startList.begin();it!=startList.end();it++)
			if(aliveNodes[id].isPeer(*it)){
				startRemove.push_back(*it);
				mergeTwoListsScale(startRemove,aliveNodes[*it].J);
			}

		for(it=startRemove.begin();it!=startRemove.end();it++)
			startList.remove(*it);

		for(it=endRemove.begin();it!=endRemove.end();it++)
			endList.remove(*it);

		startRemove.clear();
		endRemove.clear();

		if(Q!=-1){
			linksTraversed.push_back(linkIndex[nodeId][Q].index);
		}

		if(!K.empty()){

			for(it=K.begin();it!=K.end();it++){
				linksTraversed.push_back(linkIndex[nodeId][*it].index);
			}
		}

		for(it=startList.begin();it!=startList.end();it++)
			for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){

				tmpPair.n1=flowIndex[*it][*itToRemove];
				tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);
				pairs.push_back(tmpPair);

			}

		for(itToRemove=linksTraversed.begin();itToRemove!=linksTraversed.end();itToRemove++)
			for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
				if(isPresentInList(routingMatrixScale[(*itPair).n1],*itToRemove)){
					trafficExchange+=(*itPair).n2;

				}
		*/

		if(trafficExchange>peeringThreshold)
			return true;

		else
			return false;

}

bool Node::applyPeeringCriteria(int id, bool recipient){

	if(isInCoalition==true && isPresentInCustomerTreeOfAlly(id)==true)
		return false;

	if(isPresentInCustomerTree(id))
		return false;

	else if((this->*strategyPointer)(id)){

		if(recipient==false && !evaluatePeeringThreshold(id))
			return false;
		else
			return true;

	}

	else
		return false;

}

bool Node::evaluateExistingPeer(int id){

	return (this->*dStrategyPointer)(id);

}

bool Node::checkAndRemovePeersInCustomerTree(int dePeeredNode){

	list<int>::iterator itInt;
	bool peerInCustomer=false;
	if(K.empty())
		return false;

	J.sort();
	J.unique();
	for(itInt=J.begin();itInt!=J.end();itInt++)
		if(isPeer(*itInt)){

			if(aliveNodes[dePeeredNode].isPresentInCustomerTree(*itInt) || dePeeredNode==*itInt){

				endLink(nodeId,*itInt);
				endFlow(nodeId,*itInt);
				K.remove(*itInt);
				aliveNodes[*itInt].K.remove(nodeId);
				peerInCustomer=true;

			}

			else{

				cout<<"Node "<<nodeId<<" has peer "<<*itInt<<" in customer tree"<<endl;
				string str="ERROR!! Peer in customer tree";
				endSimulation(str);
			}
		}

	return peerInCustomer;
}

int Node::getHypotheticalProviderPeering(int x){

	npPair tmpNP;
	list<npPair> PP;
	list<npPair>::iterator itNP;
	list<int>::iterator it;
	list<npPair> PP2;
	int i=0;

	if(x!=-1)
		K.remove(x);	//temporarily remove x from peering list to expand possible provider set

	for(it=overLap.begin();it!=overLap.end();it++){

		i=*it;

		if(i!=nodeId && !isPresentInCustomerTree(i) && !isPeer(i) && -1==isPresentInCustomerTreeOfPeer(i) && aliveNodes[i].numGPresence>=numGPresence){

			tmpNP.nId=i;
			tmpNP.price=aliveNodes[i].price;
			tmpNP.trafficVolume=aliveNodes[i].Vt;
			PP.push_back(tmpNP);

		}

	}

	if(x!=-1)
		insertPeerInK(x);

	if(PP.empty())
		return -1;

	else{

		for(itNP=PP.begin();itNP!=PP.end();itNP++)
			if((*itNP).trafficVolume>Vt)
				PP2.push_back(*itNP);

		if(!PP2.empty()){
			PP2.sort(comparePrice);
			return PP2.front().nId;
		}

		else{
			return -1;
		}
	}

}


int Node::getProviderAfterDePeering(int x){

	npPair tmpNP;
	list<npPair> PP;
	list<npPair> PP2;
	list<npPair>::iterator itNP;
	list<int> tempList;
	list<int>::iterator itT;
	int i=0;

	if(x!=-1)
		K.remove(x);	//temporarily remove x from peering list to expand possible provider set

	for(itT=overLap.begin();itT!=overLap.end();itT++){

		i=*itT;

		if(i!=nodeId && doesShareGeography(i) && !isPresentInCustomerTree(i) && !isPeer(i) && -1==isPresentInCustomerTreeOfPeer(i) && aliveNodes[i].numGPresence>=numGPresence){

			tmpNP.nId=i;
			tmpNP.price=aliveNodes[i].price;
			tmpNP.trafficVolume=aliveNodes[i].Vt;
			PP.push_back(tmpNP);

		}

	}

	if(x!=-1)
		insertPeerInK(x);

	if(PP.empty())
		return -1;

	else{

		for(itNP=PP.begin();itNP!=PP.end();itNP++)
			if((*itNP).trafficVolume>Vt)
				PP2.push_back(*itNP);

		if(!PP2.empty()){
			PP2.sort(comparePrice);
			return PP2.front().nId;
		}

		else{
			return -1;
		}
	}

}

bool Node::dePeer(int id){

	/*
	 * Node doing de-peering is called: x
	 * Node being de-peered is called: y
	 *
	 */

	if(K.empty())
		return false;

	bool dePeered=false;
	list<int>::iterator itK;
	list<int>::iterator itD;
	list<int> toDePeer;
	list<int>::iterator itX;
	list<int>::iterator itY;
	list<int> setX;
	list<int> setY;
	int z=-1;
	int y=-1;
	list<int>::iterator it1;
	list<int>::iterator it2;
	list<int> setRest;
	list<int>::iterator itRest;

	list<int> copyK;

	if(!K.empty()){
		for(itK=K.begin();itK!=K.end();itK++)
			copyK.push_back(*itK);
	}

#if DEBUG
	logFile<<"Node "<<nodeId<<" depeering using peering strategy "<<peeringStrategyNumber<<endl;
#endif

	if(id==-1){
		if(isInCoalition==true && !allies.empty()){
			for(itK=K.begin();itK!=K.end();itK++){
#if DEBUG
				logFile<<"Considering peer "<<*itK<<"\t";
#endif
				if(!isPresentInList(toDePeer,*itK) && isPresentInCustomerTreeOfAlly(*itK)){
					toDePeer.push_back(*itK);

#if DEBUG
					logFile<<"Node "<<nodeId<<" depeering node "<<*itK<<" because of alliance";
#endif
				}

#if DEBUG
				logFile<<endl;
#endif
			}
		}

		for(itK=copyK.begin();itK!=copyK.end();itK++){
			if(!isPresentInList(toDePeer,*itK)){
				if(!evaluateExistingPeer(*itK))
					toDePeer.push_back(*itK);
			}
		}
	}

	else{
		toDePeer.push_back(id);
	}

	if(toDePeer.empty())
		return false;

	for(itD=toDePeer.begin();itD!=toDePeer.end();itD++){

		if(!isPeer(*itD))	//forced depeering might have taken place
			continue;

		//logFile<<"Node "<<nodeId<<" depeering "<<*itD<<endl;

		y=*itD;	//y is the node being depeered
		setX.clear();
		setY.clear();
		setRest.clear();

		if(aliveNodes[*itD].Q==-1 && Q==-1){	//if both x and y are tier1

			if(!doesShareGeography(*itD) && isPresentInList(Tier1,*itD))		//if they don't share geography then peering by necessity
				continue;

			else if(((z=aliveNodes[*itD].getProviderAfterDePeering(nodeId))==nodeId && getProviderAfterDePeering(*itD)==*itD) || z==-1)
				continue;

			else{

				dePeered=true;

#if DEBUG
				cout<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" depeered "<<y<<" Strategy: "<<aliveNodes[y].peeringStrategyNumber<<" V: "<<aliveNodes[y].V<<endl;
				logFile<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" depeered "<<y<<" Strategy: "<<aliveNodes[y].peeringStrategyNumber<<" V: "<<aliveNodes[y].V<<endl;
#endif

				//remove from eachother's peering list
				K.remove(y);
				aliveNodes[y].K.remove(nodeId);

				//remove y from Tier1
				Tier1.remove(y);

				//end link and flow between eachother
				endLinkScale(nodeId,y);
				endFlowScale(nodeId,y);

				//end peering by necessity with other Tier-1 peers
				list<int>::iterator itT;
				for(itT=Tier1.begin();itT!=Tier1.end();itT++)
					if(aliveNodes[y].isPeer(*itT) && !aliveNodes[y].doesShareGeography(*itT)){
						//end peering by necessity between the two
						aliveNodes[y].K.remove(*itT);
						aliveNodes[*itT].K.remove(y);
						endLinkScale(*itT,y);
						endFlowScale(*itT,y);
					}


				//get new provider for y
				aliveNodes[y].Q=z;
				aliveNodes[y].providerPrice=aliveNodes[z].price;

				aliveNodes[z].addICustomer(y);
				aliveNodes[z].addJSubTree(y);

				int P=aliveNodes[z].Q;
				while(P!=-1){
					aliveNodes[P].addJSubTree(y);
					P=aliveNodes[P].Q;
				}

				endFlowScale(y,z);
				establishLinkWithProvider(y,aliveNodes[y].Q);
				establishFlowWithProviderScale(y,aliveNodes[y].Q);

				//end all flows of the customer tree of y with the rest of the world
				for(it1=aliveNodes[y].I.begin();it1!=aliveNodes[y].I.end();it1++)
					setY.push_back(*it1);

				for(it1=setY.begin();it1!=setY.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						setY.push_back(*it2);
				setY.push_front(y);

				for(int i=0;i<activeNodes;i++)
					if(i!=y && !aliveNodes[y].isPresentInCustomerTree(i)){
						setRest.push_back(i);

					}

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
						if(!(*itY==y && *itRest==aliveNodes[y].Q) && !aliveNodes[*itY].isPeer(*itRest)){
							endFlowScale(*itY,*itRest);

						}

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
						if(!(*itY==y && *itRest==aliveNodes[y].Q) && !aliveNodes[*itY].isPeer(*itRest)){
							establishFlowPeeringScale(*itY,*itRest,aliveNodes[*itY].Q);

						}

				/*
				//re-establish flows within the customer tree of y
				list<int>::iterator itS;
				list<int>::iterator itE;
				for(itS=setY.begin();itS!=setY.end();itS++)
					for(itE=setY.begin();itE!=setY.end();itE++)
						if(*itS!=*itE && linkIndex[*itS][*itE].index!=-1)
							endFlowScale(*itS,*itE);

				for(itS=setY.begin();itS!=setY.end();itS++)
					for(itE=setY.begin();itE!=setY.end();itE++)
						if(*itS!=*itE && linkIndex[*itS][*itE].index!=-1 && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
							establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);

				*/
			}//end else Tier-1 y being depeered

		}//end if both Tier-1

		else{		//either x or y or both have a provider
					//no need to find a new provider for y. just end peering between x & y


			dePeered=true;

#if DEBUG
			cout<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" depeered "<<y<<" Strategy: "<<aliveNodes[y].peeringStrategyNumber<<" V: "<<aliveNodes[y].V<<endl;
			logFile<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" depeered "<<y<<" Strategy: "<<aliveNodes[y].peeringStrategyNumber<<" V: "<<aliveNodes[y].V<<endl;
#endif

			//remove from eachother's peering list
			K.remove(y);
			aliveNodes[y].K.remove(nodeId);

			//end link and flow between eachother
			endLinkScale(nodeId,y);
			endFlowScale(nodeId,y);

			if(isPresentInCustomerTree(y)){	//y is in the customer tree of x

				for(it1=aliveNodes[y].I.begin();it1!=aliveNodes[y].I.end();it1++)
					setY.push_back(*it1);

				for(it1=setY.begin();it1!=setY.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						setY.push_back(*it2);
				setY.push_front(y);

				for(it1=I.begin();it1!=I.end();it1++)
					if(!isPresentInList(setY,*it1))
						setX.push_back(*it1);

				for(it1=setX.begin();it1!=setX.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						if(!isPresentInList(setY,*it2))
							setX.push_back(*it2);
				setX.push_front(nodeId);

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itX=setX.begin();itX!=setX.end();itX++)
						if(!aliveNodes[*itY].isPeer(*itX) && aliveNodes[*itY].Q!=*itX)
							endFlowScale(*itY,*itX);

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itX=setX.begin();itX!=setX.end();itX++)
						if(!aliveNodes[*itY].isPeer(*itX) && aliveNodes[*itY].Q!=*itX)
							establishFlowPeeringScale(*itY,*itX,aliveNodes[*itY].Q);

			}//end if y is in the customer tree of x

			else if(aliveNodes[y].isPresentInCustomerTree(nodeId)){	//x is in the customer tree of y

				for(it1=I.begin();it1!=I.end();it1++)
					setX.push_back(*it1);

				for(it1=setX.begin();it1!=setX.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						setX.push_back(*it2);
				setX.push_front(nodeId);

				for(it1=aliveNodes[y].I.begin();it1!=aliveNodes[y].I.end();it1++)
					if(!isPresentInList(setX,*it1))
						setY.push_back(*it1);

				for(it1=setY.begin();it1!=setY.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						if(!isPresentInList(setX,*it2))
							setY.push_back(*it2);
				setY.push_front(y);

				for(itY=setY.begin();itY!=setY.end();itY++){
					for(itX=setX.begin();itX!=setX.end();itX++){
						if(!aliveNodes[*itY].isPeer(*itX) && aliveNodes[*itX].Q!=*itY){
							endFlowScale(*itY,*itX);
						}
					}
				}


				for(itX=setX.begin();itX!=setX.end();itX++)
					for(itY=setY.begin();itY!=setY.end();itY++)
						if(!aliveNodes[*itY].isPeer(*itX) && aliveNodes[*itX].Q!=*itY)
							establishFlowPeeringScale(*itX,*itY,aliveNodes[*itX].Q);


			}//end else if x is in the customer tree of y

			else{	//x & y are not in each other's customer tree

				for(it1=I.begin();it1!=I.end();it1++)
					setX.push_back(*it1);

				for(it1=setX.begin();it1!=setX.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						setX.push_back(*it2);
				setX.push_front(nodeId);

				for(it1=aliveNodes[y].I.begin();it1!=aliveNodes[y].I.end();it1++)
					if(!isPresentInList(setX,*it1))
						setY.push_back(*it1);

				for(it1=setY.begin();it1!=setY.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						if(!isPresentInList(setX,*it1))
							setY.push_back(*it2);
				setY.push_front(y);

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itX=setX.begin();itX!=setX.end();itX++)
						if(!aliveNodes[*itY].isPeer(*itX))
							endFlowScale(*itY,*itX);

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itX=setX.begin();itX!=setX.end();itX++)
						if(!aliveNodes[*itY].isPeer(*itX))
							establishFlowPeeringScale(*itY,*itX,aliveNodes[*itY].Q);

			}//end else x & y are not in each other's customer tree

		}//end else x & y are not both Tier-1

	}//end peering for loop

	return dePeered;

}


bool Node::dePeerSingular(int id){

	/*
	 * Node doing de-peering is called: x
	 * Node being de-peered is called: y
	 *
	 */

	if(K.empty())
		return false;

	bool dePeered=false;
	list<int>::iterator itK;
	list<int>::iterator itD;
	list<int> toDePeer;
	list<int>::iterator itX;
	list<int>::iterator itY;
	list<int> setX;
	list<int> setY;
	int z=-1;
	int y=-1;
	list<int>::iterator it1;
	list<int>::iterator it2;
	list<int> setRest;
	list<int>::iterator itRest;

	toDePeer.push_back(id);

	if(toDePeer.empty())
		return false;

	for(itD=toDePeer.begin();itD!=toDePeer.end();itD++){

		if(!isPeer(*itD))	//forced depeering might have taken place
			continue;

		//logFile<<"Node "<<nodeId<<" depeering "<<*itD<<endl;

		y=*itD;	//y is the node being depeered
		setX.clear();
		setY.clear();
		setRest.clear();

		if(aliveNodes[*itD].Q==-1 && Q==-1){	//if both x and y are tier1

			if(!doesShareGeography(*itD) && isPresentInList(Tier1,*itD))		//if they don't share geography then peering by necessity
				continue;

			else if(((z=aliveNodes[*itD].getProviderAfterDePeering(nodeId))==nodeId && getProviderAfterDePeering(*itD)==*itD) || z==-1)
				continue;

			else{

				dePeered=true;

#if DEBUG
				cout<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" depeered "<<y<<" Strategy: "<<aliveNodes[y].peeringStrategyNumber<<" V: "<<aliveNodes[y].V<<endl;
				logFile<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" depeered "<<y<<" Strategy: "<<aliveNodes[y].peeringStrategyNumber<<" V: "<<aliveNodes[y].V<<endl;
#endif

				//remove from eachother's peering list
				K.remove(y);
				aliveNodes[y].K.remove(nodeId);

				//remove y from Tier1
				Tier1.remove(y);

				//end link and flow between eachother
				endLinkScale(nodeId,y);
				endFlowScale(nodeId,y);

				//end peering by necessity with other Tier-1 peers
				list<int>::iterator itT;
				for(itT=Tier1.begin();itT!=Tier1.end();itT++)
					if(aliveNodes[y].isPeer(*itT) && !aliveNodes[y].doesShareGeography(*itT)){
						//end peering by necessity between the two
						aliveNodes[y].K.remove(*itT);
						aliveNodes[*itT].K.remove(y);
						endLinkScale(*itT,y);
						endFlowScale(*itT,y);
					}


				//get new provider for y
				aliveNodes[y].Q=z;
				aliveNodes[y].providerPrice=aliveNodes[z].price;

				aliveNodes[z].addICustomer(y);
				aliveNodes[z].addJSubTree(y);

				int P=aliveNodes[z].Q;
				while(P!=-1){
					aliveNodes[P].addJSubTree(y);
					P=aliveNodes[P].Q;
				}

				endFlowScale(y,z);
				establishLinkWithProvider(y,aliveNodes[y].Q);
				establishFlowWithProviderScale(y,aliveNodes[y].Q);

				//end all flows of the customer tree of y with the rest of the world
				for(it1=aliveNodes[y].I.begin();it1!=aliveNodes[y].I.end();it1++)
					setY.push_back(*it1);

				for(it1=setY.begin();it1!=setY.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						setY.push_back(*it2);
				setY.push_front(y);

				for(int i=0;i<activeNodes;i++)
					if(i!=y && !aliveNodes[y].isPresentInCustomerTree(i)){
						setRest.push_back(i);

					}

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
						if(!(*itY==y && *itRest==aliveNodes[y].Q) && !aliveNodes[*itY].isPeer(*itRest)){
							endFlowScale(*itY,*itRest);

						}

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
						if(!(*itY==y && *itRest==aliveNodes[y].Q) && !aliveNodes[*itY].isPeer(*itRest)){
							establishFlowPeeringScale(*itY,*itRest,aliveNodes[*itY].Q);

						}

				/*
				//re-establish flows within the customer tree of y
				list<int>::iterator itS;
				list<int>::iterator itE;
				for(itS=setY.begin();itS!=setY.end();itS++)
					for(itE=setY.begin();itE!=setY.end();itE++)
						if(*itS!=*itE && linkIndex[*itS][*itE].index!=-1)
							endFlowScale(*itS,*itE);

				for(itS=setY.begin();itS!=setY.end();itS++)
					for(itE=setY.begin();itE!=setY.end();itE++)
						if(*itS!=*itE && linkIndex[*itS][*itE].index!=-1 && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
							establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);

				*/
			}//end else Tier-1 y being depeered

		}//end if both Tier-1

		else{		//either x or y or both have a provider
					//no need to find a new provider for y. just end peering between x & y


			dePeered=true;

#if DEBUG
			cout<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" depeered "<<y<<" Strategy: "<<aliveNodes[y].peeringStrategyNumber<<" V: "<<aliveNodes[y].V<<endl;
			logFile<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" depeered "<<y<<" Strategy: "<<aliveNodes[y].peeringStrategyNumber<<" V: "<<aliveNodes[y].V<<endl;
#endif

			//remove from eachother's peering list
			K.remove(y);
			aliveNodes[y].K.remove(nodeId);

			//end link and flow between eachother
			endLinkScale(nodeId,y);
			endFlowScale(nodeId,y);

			if(isPresentInCustomerTree(y)){	//y is in the customer tree of x

				for(it1=aliveNodes[y].I.begin();it1!=aliveNodes[y].I.end();it1++)
					setY.push_back(*it1);

				for(it1=setY.begin();it1!=setY.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						setY.push_back(*it2);
				setY.push_front(y);

				for(it1=I.begin();it1!=I.end();it1++)
					if(!isPresentInList(setY,*it1))
						setX.push_back(*it1);

				for(it1=setX.begin();it1!=setX.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						if(!isPresentInList(setY,*it2))
							setX.push_back(*it2);
				setX.push_front(nodeId);

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itX=setX.begin();itX!=setX.end();itX++)
						if(!aliveNodes[*itY].isPeer(*itX) && aliveNodes[*itY].Q!=*itX)
							endFlowScale(*itY,*itX);

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itX=setX.begin();itX!=setX.end();itX++)
						if(!aliveNodes[*itY].isPeer(*itX) && aliveNodes[*itY].Q!=*itX)
							establishFlowPeeringScale(*itY,*itX,aliveNodes[*itY].Q);

			}//end if y is in the customer tree of x

			else if(aliveNodes[y].isPresentInCustomerTree(nodeId)){	//x is in the customer tree of y

				for(it1=I.begin();it1!=I.end();it1++)
					setX.push_back(*it1);

				for(it1=setX.begin();it1!=setX.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						setX.push_back(*it2);
				setX.push_front(nodeId);

				for(it1=aliveNodes[y].I.begin();it1!=aliveNodes[y].I.end();it1++)
					if(!isPresentInList(setX,*it1))
						setY.push_back(*it1);

				for(it1=setY.begin();it1!=setY.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						if(!isPresentInList(setX,*it2))
							setY.push_back(*it2);
				setY.push_front(y);

				for(itY=setY.begin();itY!=setY.end();itY++){
					for(itX=setX.begin();itX!=setX.end();itX++){
						if(!aliveNodes[*itY].isPeer(*itX) && aliveNodes[*itX].Q!=*itY){
							endFlowScale(*itY,*itX);
						}
					}
				}


				for(itX=setX.begin();itX!=setX.end();itX++)
					for(itY=setY.begin();itY!=setY.end();itY++)
						if(!aliveNodes[*itY].isPeer(*itX) && aliveNodes[*itX].Q!=*itY)
							establishFlowPeeringScale(*itX,*itY,aliveNodes[*itX].Q);


			}//end else if x is in the customer tree of y

			else{	//x & y are not in each other's customer tree

				for(it1=I.begin();it1!=I.end();it1++)
					setX.push_back(*it1);

				for(it1=setX.begin();it1!=setX.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						setX.push_back(*it2);
				setX.push_front(nodeId);

				for(it1=aliveNodes[y].I.begin();it1!=aliveNodes[y].I.end();it1++)
					if(!isPresentInList(setX,*it1))
						setY.push_back(*it1);

				for(it1=setY.begin();it1!=setY.end();it1++)
					for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
						if(!isPresentInList(setX,*it1))
							setY.push_back(*it2);
				setY.push_front(y);

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itX=setX.begin();itX!=setX.end();itX++)
						if(!aliveNodes[*itY].isPeer(*itX))
							endFlowScale(*itY,*itX);

				for(itY=setY.begin();itY!=setY.end();itY++)
					for(itX=setX.begin();itX!=setX.end();itX++)
						if(!aliveNodes[*itY].isPeer(*itX))
							establishFlowPeeringScale(*itY,*itX,aliveNodes[*itY].Q);

			}//end else x & y are not in each other's customer tree

		}//end else x & y are not both Tier-1

	}//end peering for loop

	return dePeered;

}



bool Node::getNewPeer(int id){

	list<int> PP;
	list<int>::iterator itPP;
	list<int> setX;
	list<int> setY;
	list<int> setRest;
	list<int>::iterator itX;
	list<int>::iterator itY;
	list<int>::iterator itRest;
	int y;
	list<int>::iterator it1;
	list<int>::iterator it2;
	int i;

#if DEBUG
	logFile<<"Node "<<nodeId<<" searching for new peers using strategy "<<peeringStrategyNumber<<endl;
#endif

	if(id==-1){
		for(it1=overLap.begin();it1!=overLap.end();it1++){

			i=*it1;

			if(!isPeer(i) && !isImmediateCustomer(i) && i!=Q && !isPresentInCustomerTree(i)){
			//if(!isPeer(i) && !isImmediateCustomer(i) && i!=Q){


				if(aliveNodes[i].applyPeeringCriteria(nodeId,true)){	//do both sides agree to peer

					if(applyPeeringCriteria(i,false))
						PP.push_back(i);

				}
			}
		}
	}

	else
		PP.push_back(id);

	if(PP.empty())
		return false;

	else{

		for(itPP=PP.begin();itPP!=PP.end();itPP++){

#if DEBUG
			cout<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" peering with "<<*itPP<<" Strategy: "<<aliveNodes[*itPP].peeringStrategyNumber<<" V: "<<aliveNodes[*itPP].V<<endl;
			logFile<<"Node "<<nodeId<<" Strategy: "<<aliveNodes[nodeId].peeringStrategyNumber<<" V: "<<aliveNodes[nodeId].V<<" peering with "<<*itPP<<" Strategy: "<<aliveNodes[*itPP].peeringStrategyNumber<<" V: "<<aliveNodes[*itPP].V<<endl;
#endif

			if(isPeer(*itPP) && aliveNodes[*itPP].Q==-1 && Q==-1)	//*itPP is already peering by necessity with the node
				continue;

			y=*itPP;
			setX.clear();
			setY.clear();
			setRest.clear();

			endFlowScale(nodeId,y);		//end existing flows between the two

			insertPeerInK(y);
			aliveNodes[y].insertPeerInK(nodeId);

			establishLinkWithPeer(nodeId,y);
			establishFlowWithPeerScale(nodeId,y);

			for(it1=aliveNodes[y].I.begin();it1!=aliveNodes[y].I.end();it1++)
				setY.push_back(*it1);

			for(it1=setY.begin();it1!=setY.end();it1++)
				for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
					setY.push_back(*it2);
			setY.push_front(y);

			for(it1=I.begin();it1!=I.end();it1++)
				setX.push_back(*it1);

			for(it1=setX.begin();it1!=setX.end();it1++)
				for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
					setX.push_back(*it2);
			setX.push_front(nodeId);

			for(itX=setX.begin();itX!=setX.end();itX++)
				for(itY=setY.begin();itY!=setY.end();itY++)
					if(!aliveNodes[*itX].isPeer(*itY))
						endFlowScale(*itX,*itY);

			for(itX=setX.begin();itX!=setX.end();itX++)
				for(itY=setY.begin();itY!=setY.end();itY++)
					if(!aliveNodes[*itX].isPeer(*itY))
						establishFlowPeeringScale(*itX,*itY,aliveNodes[*itX].Q);

		}//end for loop

	}//end else

	logFile<<"Came here before crash"<<endl;
	return true;
}

int Node::getProviderAfterPeering(){

	npPair tmpNP;
	list<npPair> PP;
	list<int>::iterator it;
	int i;
	list<npPair> PP2;
	list<npPair>::iterator itNP;

	for(it=overLap.begin();it!=overLap.end();it++){

		i=*it;

		if(i!=nodeId && doesShareGeography(i) && !isPresentInCustomerTree(i) && !isPeer(i) && -1==isPresentInCustomerTreeOfPeer(i) && aliveNodes[i].numGPresence>=numGPresence){

			tmpNP.nId=i;
			tmpNP.price=aliveNodes[i].price;
			tmpNP.trafficVolume=aliveNodes[i].Vt;
			PP.push_back(tmpNP);

		}
	}

	if(PP.empty())
		return -1;

	else{

		for(itNP=PP.begin();itNP!=PP.end();itNP++)
			if((*itNP).trafficVolume>Vt)
				PP2.push_back(*itNP);

		if(!PP2.empty()){
			PP2.sort(comparePrice);
			return PP2.front().nId;
		}

		else{
			return -1;
		}
	}

}

inline void Node::addICustomer(int id){

	I.push_back(id);

}

inline void Node::addJCustomer(int id){

	J.push_back(id);
}

bool Node::isPresentInCustomerTree(int id){

	list<int>::iterator it;
	if(J.empty())
		return false;

	else{

		for(it=J.begin();it!=J.end();it++){
			if(id==*it)
				return true;
		}

		return false;
	}
}

inline void Node::removeICustomer(int id){

	I.remove(id);
}

inline void Node::removeJCustomer(int id){

	J.remove(id);
}

void Node::removeJSubTree(int id){

	list<Node>::iterator it;
	list<int>::iterator it2;

	removeJCustomer(id);

	if(!aliveNodes[id].J.empty()){

		for(it2=aliveNodes[id].J.begin();it2!=aliveNodes[id].J.end();it2++){

			removeJCustomer(*it2);

		}//end for

	}

}

void Node::addJSubTree(int id){


	list<int>::iterator it;

	addJCustomer(id);

	if(!aliveNodes[id].J.empty()){

		for(it=aliveNodes[id].J.begin();it!=aliveNodes[id].J.end();it++)
			addJCustomer(*it);
	}

}

bool Node::getInitialProviderRand(){

		list<npPair> GS;
		list<npPair> TGS;
		list<Coordinate>::iterator it;
		list<int>::iterator it2;
		list<npPair>::iterator it4;
		int xPoint;
		int yPoint;
		npPair possibleProvider;
		int P;

		//Step 1 Creation of GS
		for(it=gPresence.begin();it!=gPresence.end();it++){

			xPoint=(*it).xCoordinate;
			yPoint=(*it).yCoordinate;

			if(geography[xPoint][yPoint].population>1){

				for(it2=geography[xPoint][yPoint].nodePresent.begin();it2!=geography[xPoint][yPoint].nodePresent.end();it2++){

					if((*it2)!=nodeId && aliveNodes[*it2].lifeStatus==alive && !isPresentInCustomerTree(*it2) && aliveNodes[*it2].numGPresence>1 && aliveNodes[*it2].numGPresence>=numGPresence){

						possibleProvider.nId=*it2;
						possibleProvider.price=aliveNodes[*it2].priceChart[xPoint][yPoint];
						possibleProvider.trafficVolume=aliveNodes[*it2].V;
						possibleProvider.gExpanse=aliveNodes[*it2].numGPresence;
						possibleProvider.numCustomers=aliveNodes[*it2].J.size();

						GS.push_back(possibleProvider);

					}//end if

				}//end for

			}//end if

		}//end for

		int tempRand;
		int tempVar=0;
		if(!GS.empty()){

			if(GS.size()>1){

				tempRand=rand()%GS.size();

				for(it4=GS.begin();it4!=GS.end();it4++,tempVar++){
					if(tempVar==tempRand){
						Q=(*it4).nId;
						providerPrice=(*it4).price;
						aliveNodes[Q].addICustomer(nodeId);
						aliveNodes[Q].addJSubTree(nodeId);
					}
				}

			}

			else{
				Q=GS.front().nId;
				providerPrice=GS.front().price;
				aliveNodes[Q].addICustomer(nodeId);
				aliveNodes[Q].addJSubTree(nodeId);
			}
		}

		//Step 5 Update parent providers
		if(Q != -1){

			P=aliveNodes[Q].Q;

			while(P != -1){

				aliveNodes[P].addJSubTree(nodeId);
				P=aliveNodes[P].Q;

			}//end while

		}//end if

		else
			providerPrice=0;

		return true;
}

int Node::getProviderAsZ(int X){

	list<npPair> GS;
	list<npPair> TGS;
	list<npPair> TG2;
	list<Coordinate>::iterator it;
	list<int>::iterator it2;
	list<npPair>::iterator it4;
	int xPoint;
	int yPoint;
	npPair possibleProvider;
	int providerId;
	int i=0;

	for(it=gPresence.begin();it!=gPresence.end();it++){

		xPoint=(*it).xCoordinate;
		yPoint=(*it).yCoordinate;

		if(geography[xPoint][yPoint].population>1){

			for(it2=geography[xPoint][yPoint].nodePresent.begin();it2!=geography[xPoint][yPoint].nodePresent.end();it2++){

				if((*it2)!=nodeId && (*it2)!=X && aliveNodes[*it2].lifeStatus==alive && aliveNodes[*it2].newborn==false && !isPeer(*it2) && -1==isPresentInCustomerTreeOfPeer(*it2) && !isPresentInCustomerTree(*it2) && aliveNodes[*it2].numGPresence>=numGPresence){

					possibleProvider.nId=*it2;
					//possibleProvider.price=aliveNodes[*it2].price;
					possibleProvider.price=aliveNodes[*it2].priceChart[xPoint][yPoint];
					possibleProvider.trafficVolume=aliveNodes[*it2].Vt;

					//logFile<<"Node "<<nodeId<<" considering provider "<<possibleProvider.nId<<endl;

					TGS.push_back(possibleProvider);

				}//end if

			}//end for

		}//end if

	}//end for

	/*
	for(it2=overLap.begin();it2!=overLap.end();it2++){
		i=*it2;
		if(i!=nodeId && i!=X && !isPresentInCustomerTree(i) && !isPeer(i) && -1==isPresentInCustomerTreeOfPeer(i) && !aliveNodes[X].isPresentInCustomerTree(i) && aliveNodes[i].numGPresence>=numGPresence){
			possibleProvider.nId=i;
			possibleProvider.price=aliveNodes[i].price;
			possibleProvider.trafficVolume=aliveNodes[i].Vt;
			TGS.push_back(possibleProvider);
		}

	}
	*/

	if(TGS.empty())
		return -1;

	else{

		for(it4=TGS.begin();it4!=TGS.end();it4++)
			if((*it4).trafficVolume>Vt)
				TG2.push_back(*it4);

		if(!TG2.empty()){
			TG2.sort(comparePrice);
			return TG2.front().nId;
		}

		else{
			return -1;
		}
	}

}

bool Node::isAlly(int id){

	if(isPresentInList(allies,id))
		return true;

	else
		return false;
}

bool Node::isProviderOfAlly(int id){

	list<int>::iterator it;

	if(allies.empty())
		return false;

	for(it=allies.begin();it!=allies.end();it++)
		if(aliveNodes[*it].Q==id)
			return true;

	return false;

}

bool Node::isCustomerOfAlly(int id){

	list<int>::iterator it;

	if(allies.empty())
		return false;

	for(it=allies.begin();it!=allies.end();it++)
		if(aliveNodes[*it].isPresentInCustomerTree(id))
			return true;

	return false;
}

/*
npPair Node::evaluateAllyRequest(int id){

	npPair tempNP;

	if(isCustomerOfAlly(id) || isProviderOfAlly(id)){
		tempNP.shouldAct=false;
		return tempNP;
	}

	else{

		tempNP=evaluateAlly(id);
		return tempNP;
	}
}
*/

/*
npPair Node::evaluateAlly(int id){

	double existingCost=0;
	double existingRevenue=0;
	double potentialCost=0;
	double potentialRevenue=0;
	double existingPeerTraffic=0;
	double directExchangeTraffic=0;
	double existingTransitTraffic=0;
	double existingProviderTraffic=0;
	double potentialPeerTraffic=0;
	double potentialProviderTraffic=0;
	double existingCustomerTraffic=0;
	double potentialCustomerTraffic=0;
	list<int>::iterator it;
	npPair tempNP;
	tempNP.shouldAct=false;


	if(isPeer(id)){

		existingPeerTraffic=linkValueVector[linkIndex[nodeId][id].index];
		directExchangeTraffic=trafficMatrix[nodeId][id]+trafficMatrix[id][nodeId];
		existingCost=peeringCostMultiplier*(pow(existingPeerTraffic,peeringExponent));

		if(Q!=-1){
			existingCost+=providerPrice*(pow(linkValueVector[linkIndex[nodeId][Q].index]),providerExponent);
		}

		for(it=K.begin();it!=K.end();it++)
			if(aliveNodes[id].isImmediateCustomer(*it)){
				existingPeerTraffic+=linkValueVector[linkIndex[nodeId][*it].index];
				directExchangeTraffic+=trafficMatrix[nodeId][*it]+trafficMatrix[*it][nodeId];
				existingCost+=peeringCostMultiplier*(pow(linkValueVector[linkIndex[nodeId][*it].index]),peeringExponent);
			}

		existingRevenue=price*(pow(existingPeerTraffic-directExchangeTraffic),providerExponent);

		//potentials
		directExchangeTraffic=0;
		potentialPeerTraffic=linkValueVector[linkIndex[nodeId][id].index];
		directExchangeTraffic=trafficMatrix[nodeId][id]+trafficMatrix[id][nodeId];
		potentialCustomerTraffic=potentialPeerTraffic-directExchangeTraffic;
		potentialProviderTraffic=linkValueVector[linkIndex[nodeId][Q].index];


		for(it=K.begin();it!=K.end();it++){
			if(aliveNodes[id].isImmediateCustomer(*it)){

				if(aliveNodes[*it].isPresentInCustomerTreeOfPeer(nodeId)){

					potentialProviderTraffic+=linkValueVector[linkIndex[nodeId][*it].index];
					directExchangeTraffic+=trafficMatrix[nodeId][*it]+trafficMatrix[*it][nodeId];
					potentialCustomerTraffic+=(linkValueVector[linkIndex[nodeId][*it].index]-trafficMatrix[nodeId][*it]-trafficMatrix[*it][nodeId]);

				}

				else{

					potentialPeerTraffic+=linkValueVector[linkIndex[nodeId][*it].index];
					directExchangeTraffic+=trafficMatrix[nodeId][*it]+trafficMatrix[*it][nodeId];
					potentialCustomerTraffic+=(linkValueVector[linkIndex[nodeId][*it].index]-trafficMatrix[nodeId][*it]-trafficMatrix[*it][nodeId]);

				}

			}
		}

		potentialCost=providerPrice*(pow(potentialProviderTraffic,providerExponent));
		potentialCost+=(peeringCostMultiplier*(pow(potentialPeerTraffic,peeringExponent)));

		potentialRevenue=price*(pow(potentialCustomerTraffic,providerExponent));


		if((potentialRevenue-potentialCost)>(existingRevenue-existingCost)){
			tempNP.price=potentialRevenue-potentialCost;
			tempNP.shouldAct=true;
			return tempNP;
		}


		else{

			tempNP.shouldAct=false;
			return tempNP;
		}

	}//end if peer

	return tempNP;
}
*/

/*
bool Node::getNewCoalition(){


	list<int> potentialAllies;
	list<npPair> evaluatedAllies;
	list<int> checkedAllies;
	list<int> bestAllies;
	list<int>::iterator it;
	npPair tempNP;
	npPair tempNP2;
	int chosenAlly;
	list<int> toDePeer;

	if(isCoalitionAllowed==false || K.empty() || I.empty())
		return false;

	else{

		for(int i=0;i<activeNodes;i++)
			if(i!=nodeId && doesShareGeography(i) && !isPresentInCustomerTree(i) && !aliveNodes[i].isPresentInCustomerTree(nodeId) && !aliveNodes[i].I.empty())
				potentialAllies.push_back(i);

		if(!potentialAllies.empty()){
			for(it=potentialAllies.begin();it!=potentialAllies.end();it++){
				tempNP=evaluateAlly(*it);
				tempNP2=evaluateAllyRequest(nodeId);
				if(tempNP.shouldAct==true && tempNP2.shouldAct==true){

					tempNP.nId=*it;
					evaluatedAllies.push_back(tempNP);

				}
			}

			if(!evaluatedAllies.empty()){

				evaluatedAllies.sort(comparePriceReverse);






				//nodeId acts
				allies.push_back(chosenAlly);
				for(it=K.begin();it!=K.end();it++){

					if(aliveNodes[chosenAlly].isImmediateCustomer(*it)){

						if(isAlly(*it)){
							allies.remove(*it);
							aliveNodes[*it].allies.remove(nodeId);
							if(aliveNodes[*it].allies.empty())
								aliveNodes[*it].isInCoalition=false;
						}
					}

				}

				if(!allies.empty()){
					isInCoalition=true;
				}


				//chosenAlly acts
				aliveNodes[chosenAlly].allies.push_back(nodeId);
				for(it=aliveNodes[chosenAlly].K.begin();it!=aliveNodes[chosenAlly].K.end();it++){

					if(isImmediateCustomer(*it)){

						if(aliveNodes[chosenAlly].isAlly(*it)){
							aliveNodes[chosenAlly].allies.remove(*it);
							aliveNodes[*it].allies.remove(chosenAlly);
							if(aliveNodes[*it].allies.empty())
								aliveNodes[*it].isInCoalition=false;
						}
					}

				}

				if(!aliveNodes[chosenAlly].allies.empty()){
					aliveNodes[chosenAlly].isInCoalition=true;
				}


				return true;

			}

			else
				return false;


		}

		else
			return false;

	}//end else


}
*/

bool Node::getNewProvider(){

	QPrev=Q;

	list<npPair> GS;
	list<npPair> TGS;
	list<npPair> TGS2;
	list<Coordinate>::iterator it;
	list<int>::iterator it2;
	list<npPair>::iterator it4;
	int xPoint;
	int yPoint;
	npPair possibleProvider;
	int P;
	int X;
	int z;
	list<int> setX;
	list<int> setY;
	list<int> setRest;
	list<int> setZ;
	list<int>::iterator itX;
	list<int>::iterator itY;
	list<int>::iterator itRest;
	list<int>::iterator itZ;
	bool providerChange=false;
	Coordinate tempCoordinate;
	list<double> tempPriceList;

#if DEBUG
	logFile<<"Node "<<nodeId<<" getting new provider"<<endl;
#endif

	if(Q!=-1)	//update the price offered by current provider
		providerPrice=aliveNodes[Q].price;

	//Step 1 Creation of GS
	for(it=gPresence.begin();it!=gPresence.end();it++){

		xPoint=(*it).xCoordinate;
		yPoint=(*it).yCoordinate;

		if(geography[xPoint][yPoint].population>1){

			for(it2=geography[xPoint][yPoint].nodePresent.begin();it2!=geography[xPoint][yPoint].nodePresent.end();it2++){

				if((*it2)!=nodeId && aliveNodes[*it2].lifeStatus==alive && aliveNodes[*it2].newborn==false && !isPeer(*it2) && -1==isPresentInCustomerTreeOfPeer(*it2) && aliveNodes[*it2].numGPresence>=numGPresence){

					possibleProvider.nId=*it2;
					//possibleProvider.price=aliveNodes[*it2].price;
					possibleProvider.price=aliveNodes[*it2].priceChart[xPoint][yPoint];
					possibleProvider.trafficVolume=aliveNodes[*it2].Vt;

					//logFile<<"Node "<<nodeId<<" considering provider "<<possibleProvider.nId<<endl;

					GS.push_back(possibleProvider);

				}//end if

			}//end for

		}//end if

	}//end for

	//Step 2 Creation of TGS
	if(!GS.empty()){

		GS.sort(compareId);
		GS.unique(checkUniqueness);

		for(it4=GS.begin();it4!=GS.end();it4++){

			if(newborn==false){
				if((*it4).trafficVolume>Vt){
					TGS.push_back(*it4);

				}
			}

			else{

				if((*it4).trafficVolume>Vt)
					TGS.push_back(*it4);

			}

		}//end for

		//*********** Price based selection ***********
		if(!TGS.empty())
			TGS.sort(comparePrice);

		//*********** Vt based selection Select highest Vt **************
		//if(!TGS.empty())
		//	TGS.sort(sortVolumeReverseNP);


	}//end if


	if(TGS.empty()){	//there are no nodes which satisfy provider criteria

		if(Q==-1 && newborn==false)	//node was formerly also Tier-1 no change in provider
			return false;

		else{	//node was formerly not Tier-1 so provider changes


			//end link with old provider
			endLinkScale(nodeId,Q);
			endFlowScale(nodeId,Q);

			//update previous provider chain
			X=Q;
			aliveNodes[X].removeICustomer(nodeId);
			aliveNodes[X].removeJSubTree(nodeId);
			X=aliveNodes[X].Q;

			while(X!=-1){

				aliveNodes[X].removeJSubTree(nodeId);
				X=aliveNodes[X].Q;
			}

			//new provider assigned
			Q=-1;
			providerPrice=0;

			//re-establish flows
			list<int> endSet;
			list<int> sourceSet;
			list<int>::iterator itS;
			list<int>::iterator itE;

			//populating endSet which includes every node except the node itself and its customers
			for(int i=0;i<activeNodes;i++){

				if(i!=nodeId && !isPresentInCustomerTree(i))
					endSet.push_back(i);

			}

			//populating sourceSet which includes the node and its customers (all customers in the tree)
			for(itS=J.begin();itS!=J.end();itS++)
				sourceSet.push_back(*itS);
			sourceSet.push_back(nodeId);

			//ending previous flows between the two sets
			for(itS=sourceSet.begin();itS!=sourceSet.end();itS++)
				for(itE=endSet.begin();itE!=endSet.end();itE++)
					if(!aliveNodes[*itS].isPeer(*itE))
						endFlowScale(*itS,*itE);


			//establishing links and flows with Tier-1 nodes
			list<int>::iterator itT;
			for(itT=Tier1.begin();itT!=Tier1.end();itT++)
				if(!isPeer(*itT)){
					endFlowScale(nodeId,*itT);
					insertPeerInK(*itT);
					aliveNodes[*itT].insertPeerInK(nodeId);
					establishLinkWithPeer(nodeId,*itT);
					establishFlowWithPeerScale(nodeId,*itT);
				}

			Tier1.push_back(nodeId);

			//establish flows between x and the endSet
			for(itE=endSet.begin();itE!=endSet.end();itE++)
				if(!isPeer(*itE))
					establishFlowPeeringScale(nodeId,*itE,Q);


			//establish flows
			for(itS=sourceSet.begin();itS!=sourceSet.end();itS++)
				for(itE=endSet.begin();itE!=endSet.end();itE++)
					if(*itS!=nodeId && !aliveNodes[*itS].isPeer(*itE) && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
						establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);


			//re-establish flows within the customer tree of x
			for(itS=sourceSet.begin();itS!=sourceSet.end();itS++)
				for(itE=sourceSet.begin();itE!=sourceSet.end();itE++){
					//logFile<<"*itS: "<<*itS<<" *itE: "<<*itE<<" linkIndex: "<<linkIndex[*itS][*itE].index<<endl;
					if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==1){
						endFlowScale(*itS,*itE);
						//logFile<<"Ending flow between "<<*itS<<" and "<<*itE<<endl;
					}
				}

			for(itS=sourceSet.begin();itS!=sourceSet.end();itS++)
				for(itE=sourceSet.begin();itE!=sourceSet.end();itE++)
					if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && !aliveNodes[*itS].isPresentInCustomerTree(*itE) && activeFlowIndicator[flowIndex[*itS][*itE]]==0){
						establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);
						//logFile<<"Establishing flow between "<<*itS<<" and "<<*itE<<endl;
					}

			return true;

		}//end else Q!=-1

	}//end if TGS.empty()

	else{	//TGS not empty

		TRY_OTHER_Z:	//this is a goto label

		z=TGS.front().nId;


		/*
		//check for peering by necessity
		if(aliveNodes[z].getHypotheticalProviderPeering(-1)==nodeId && getHypotheticalProviderPeering(-1)==z){

			if(!(providerChange=peerByNecessity(z))){
				logFile<<"Peering by necessity caused some problem while choosing provider for node "<<nodeId<<endl;
				string str="ERROR!!! Peering by necessity has problems";
				endSimulation(str);
			}

			TGS.pop_front();
			if(TGS.empty())
				return providerChange;
			else
				goto TRY_OTHER_Z;

		}//end if peering by necessity
		*/

		//if(TGS.front().nId==Q || TGS.front().price==providerPrice)	//cheapest node is existing provider or price is equal to existing provider
		if(TGS.front().nId==Q)	//cheapest node is existing provider or price is equal to existing provider
			return providerChange;

		if(Q==-1){	//x is Tier 1

			if(aliveNodes[z].Q==-1){ //if z is Tier1

				cout<<"ERROR!!! Tier1 choosing another Tier1 as provider without depeering"<<endl;
				string str="ERROR!! Provider selection flawed";
				endSimulation(str);
				return false;

			}//end if Z is tier 1

			else{	//Z is not tier1

				int zNewProvider=aliveNodes[z].getProviderAsZ(nodeId);

				if(zNewProvider==-1){	//z is capable of becoming Tier1 -> degrade X

					//remove x from Tier1
					Tier1.remove(nodeId);

					list<int>::iterator itT;
					for(itT=Tier1.begin();itT!=Tier1.end();itT++)
						if(isPeer(*itT) && !doesShareGeography(*itT)){
							K.remove(*itT);
							aliveNodes[*itT].K.remove(nodeId);
							endLinkScale(nodeId,*itT);
							endFlowScale(nodeId,*itT);
						}

					//end relationship of z with its previous provider
					endLinkScale(z,aliveNodes[z].Q);
					endFlowScale(z,aliveNodes[z].Q);
					aliveNodes[aliveNodes[z].Q].removeICustomer(z);
					aliveNodes[aliveNodes[z].Q].removeJSubTree(z);

					P=aliveNodes[aliveNodes[z].Q].Q;
					while(P!=-1){
						aliveNodes[P].removeJSubTree(z);
						P=aliveNodes[P].Q;
					}

					//populate setX
					list<int>::iterator it1;
					for(it1=I.begin();it1!=I.end();it1++)
						setX.push_back(*it1);

					for(it1=setX.begin();it1!=setX.end();it1++)
						for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
							setX.push_back(*it2);
					setX.push_front(nodeId);

					//populate setZ
					for(it1=aliveNodes[z].I.begin();it1!=aliveNodes[z].I.end();it1++)
						setZ.push_back(*it1);

					for(it1=setZ.begin();it1!=setZ.end();it1++)
						for(it2=aliveNodes[*it1].I.begin();it2!=aliveNodes[*it1].I.end();it2++)
							setZ.push_back(*it2);
					setZ.push_front(z);

					//make z tier1
					aliveNodes[z].Q=-1;
					aliveNodes[z].providerPrice=0;

					for(it1=Tier1.begin();it1!=Tier1.end();it1++)
						if(!aliveNodes[z].isPeer(*it1)){
							endFlowScale(*it1,z);
							aliveNodes[z].insertPeerInK(*it1);
							aliveNodes[*it1].insertPeerInK(z);
							establishLinkWithPeer(*it1,z);
							establishFlowWithPeerScale(*it1,z);

						}

					Tier1.push_back(z);

					//put x in the customer tree of z
					endFlowScale(nodeId,z);
					Q=z;
					//providerPrice=aliveNodes[z].price;


					for(int k=0;k<maxRegions;k++)
						for(int m=0;m<maxRegions;m++){
							tempCoordinate.xCoordinate=k;
							tempCoordinate.yCoordinate=m;

							if(isPresentInRegion(tempCoordinate) && aliveNodes[z].isPresentInRegion(tempCoordinate))
								tempPriceList.push_back(aliveNodes[z].priceChart[k][m]);
						}

					tempPriceList.sort();
					providerPrice=tempPriceList.front();


					establishLinkWithProvider(nodeId,Q);
					establishFlowWithProviderScale(nodeId,Q);

					aliveNodes[z].addICustomer(nodeId);
					aliveNodes[z].addJSubTree(nodeId);
					//no need to go up since z is tier1

					for(int i=0;i<activeNodes;i++)
						if(!isPresentInList(setX,i) && !isPresentInList(setZ,i))
							setRest.push_back(i);

					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
							if(linkIndex[*itX][*itZ].index==-1)
								endFlowScale(*itX,*itZ);

					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(linkIndex[*itX][*itRest].index==-1){
								endFlowScale(*itX,*itRest);

							}

					for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(linkIndex[*itZ][*itRest].index==-1)
								endFlowScale(*itZ,*itRest);

					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
							if(linkIndex[*itX][*itZ].index==-1)
								establishFlowPeeringScale(*itX,*itZ,aliveNodes[*itX].Q);

					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(linkIndex[*itX][*itRest].index==-1){
								establishFlowPeeringScale(*itX,*itRest,aliveNodes[*itX].Q);

							}

					for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(linkIndex[*itZ][*itRest].index==-1)
								establishFlowPeeringScale(*itZ,*itRest,aliveNodes[*itZ].Q);

					//re-establish flows within the customer tree of x and z
					list<int>::iterator itS;
					list<int>::iterator itE;
					for(itS=setX.begin();itS!=setX.end();itS++)
						for(itE=setX.begin();itE!=setX.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==1)
								endFlowScale(*itS,*itE);

					for(itS=setX.begin();itS!=setX.end();itS++)
						for(itE=setX.begin();itE!=setX.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==0 && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
								establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);

					for(itS=setZ.begin();itS!=setZ.end();itS++)
						for(itE=setZ.begin();itE!=setZ.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==1)
								endFlowScale(*itS,*itE);

					for(itS=setZ.begin();itS!=setZ.end();itS++)
						for(itE=setZ.begin();itE!=setZ.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==0 && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
								establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);

					return true;

				}//if z is capable of becoming Tier1

				else{	//z is not capable of becoming Tier1

					TGS.pop_front();
					if(TGS.empty())
						return providerChange;
					else
						goto TRY_OTHER_Z;

				}

			}//end else Z is not tier1

		}//end if x is Tier 1

		else{	//x is not Tier1

			if(isPresentInCustomerTree(z)){	//z is present in customer tree of x

				int zNewProvider=aliveNodes[z].getProviderAsZ(nodeId);

				if(zNewProvider==-1){	//z becomes Tier1

					endLinkScale(nodeId,Q);
					endFlowScale(nodeId,Q);

					X=Q;
					aliveNodes[X].removeICustomer(nodeId);
					aliveNodes[X].removeJSubTree(nodeId);
					while(X!=-1){

						aliveNodes[X].removeJSubTree(nodeId);
						X=aliveNodes[X].Q;
					}

					endLinkScale(z,aliveNodes[z].Q);
					endFlowScale(z,aliveNodes[z].Q);
					X=aliveNodes[z].Q;
					aliveNodes[X].removeICustomer(z);
					aliveNodes[X].removeJSubTree(z);

					while(X!=-1){

						aliveNodes[X].removeJSubTree(z);
						X=aliveNodes[X].Q;
					}

					list<int> setX;
					list<int> setZ;
					list<int> setRest;
					list<int>::iterator itX;
					list<int>::iterator itZ;
					list<int>::iterator itRest;
					list<int>::iterator it1;

					//populate setX
					for(itX=J.begin();itX!=J.end();itX++)
						setX.push_back(*itX);
					setX.push_front(nodeId);

					//populate setZ
					for(itZ=aliveNodes[z].J.begin();itZ!=aliveNodes[z].J.end();itZ++)
						setZ.push_back(*itZ);
					setZ.push_front(z);

					//populate setRest
					for(int i=0;i<activeNodes;i++)
						if(i!=nodeId && i!=z && !isPresentInCustomerTree(i) && !aliveNodes[z].isPresentInCustomerTree(i))
							setRest.push_back(i);

					//ending flows between the three sets
					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
							if(!aliveNodes[*itX].isPeer(*itZ))
								endFlowScale(*itX,*itZ);

					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(!aliveNodes[*itX].isPeer(*itRest))
								endFlowScale(*itX,*itRest);

					for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(!aliveNodes[*itZ].isPeer(*itRest))
								endFlowScale(*itZ,*itRest);

					//updating provider of x
					Q=z;
					establishLinkWithProvider(nodeId,Q);
					establishFlowWithProviderScale(nodeId,Q);
					//providerPrice=aliveNodes[Q].price;

					for(int k=0;k<maxRegions;k++)
						for(int m=0;m<maxRegions;m++){
							tempCoordinate.xCoordinate=k;
							tempCoordinate.yCoordinate=m;

							if(isPresentInRegion(tempCoordinate) && aliveNodes[z].isPresentInRegion(tempCoordinate))
								tempPriceList.push_back(aliveNodes[z].priceChart[k][m]);
						}

					tempPriceList.sort();
					providerPrice=tempPriceList.front();


					//updating new parent providers	& no need to go up since z is Tier-1
					aliveNodes[Q].addICustomer(nodeId);
					aliveNodes[Q].addJSubTree(nodeId);

					//estabish flow between x and z.J
					for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
						if(*itZ!=Q && !isPresentInCustomerTree(*itZ) && !isPeer(*itZ)){
							establishFlowPeeringScale(nodeId,*itZ,Q);
						}

					//establish flow between x.J and z + z.J
					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
							if(*itX!=nodeId && !aliveNodes[*itX].isPresentInCustomerTree(*itZ) && !aliveNodes[*itX].isPeer(*itZ)){
								establishFlowPeeringScale(*itX,*itZ,aliveNodes[*itX].Q);
							}

					//establish Tier-1 status of z
					aliveNodes[z].Q=-1;
					aliveNodes[z].providerPrice=0;
					for(itZ=Tier1.begin();itZ!=Tier1.end();itZ++){
						if(!aliveNodes[z].isPeer(*itZ)){
							endFlowScale(z,*itZ);
							establishLinkWithPeer(z,*itZ);
							establishFlowWithPeerScale(z,*itZ);
							aliveNodes[z].insertPeerInK(*itZ);
							aliveNodes[*itZ].insertPeerInK(z);
						}
					}
					Tier1.push_back(z);

					//establish flow between z and rest of the world
					for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
						if(!aliveNodes[z].isPeer(*itRest) && !aliveNodes[z].isPresentInCustomerTree(*itRest)){
							establishFlowPeeringScale(z,*itRest,aliveNodes[z].Q);
						}

					//establish flow between setZ and rest of the world
					for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(*itZ!=z && !aliveNodes[*itZ].isPresentInCustomerTree(*itRest) && !aliveNodes[*itZ].isPeer(*itRest)){

								establishFlowPeeringScale(*itZ,*itRest,aliveNodes[*itZ].Q);
							}

					//establish flow between x + x.J with rest of the world
					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(!aliveNodes[*itX].isPresentInCustomerTree(*itRest) && !aliveNodes[*itX].isPeer(*itRest)){
								establishFlowPeeringScale(*itX,*itRest,aliveNodes[*itX].Q);
							}

					//re-establish flows within the customer tree of x and z
					list<int>::iterator itS;
					list<int>::iterator itE;
					for(itS=setX.begin();itS!=setX.end();itS++)
						for(itE=setX.begin();itE!=setX.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==1)
								endFlowScale(*itS,*itE);

					for(itS=setX.begin();itS!=setX.end();itS++)
						for(itE=setX.begin();itE!=setX.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==0 && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
								establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);

					for(itS=setZ.begin();itS!=setZ.end();itS++)
						for(itE=setZ.begin();itE!=setZ.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==1)
								endFlowScale(*itS,*itE);

					for(itS=setZ.begin();itS!=setZ.end();itS++)
						for(itE=setZ.begin();itE!=setZ.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==0 && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
								establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);

					return true;

				}//end if Z becomes Tier 1

				else{	//z does not become Tier1

					list<int> setX;
					list<int> setZ;
					list<int> setRest;
					list<int>::iterator itX;
					list<int>::iterator itZ;
					list<int>::iterator itRest;

					for(itX=J.begin();itX!=J.end();itX++)
						if(*itX!=z && !aliveNodes[z].isPresentInCustomerTree(*itX))
							setX.push_back(*itX);
					setX.push_front(nodeId);

					for(itZ=aliveNodes[z].J.begin();itZ!=aliveNodes[z].J.end();itZ++)
						setZ.push_back(*itZ);
					setZ.push_front(z);

					for(int i=0;i<activeNodes;i++)
						if(i!=nodeId && i!=z && !isPresentInCustomerTree(i))
							setRest.push_back(i);

					endLinkScale(z,aliveNodes[z].Q);
					endFlowScale(z,aliveNodes[z].Q);

					X=aliveNodes[z].Q;
					aliveNodes[X].removeICustomer(z);
					aliveNodes[X].removeJSubTree(z);

					while(X!=-1){

						aliveNodes[X].removeJSubTree(z);
						X=aliveNodes[X].Q;
					}

					endLinkScale(nodeId,Q);
					endFlowScale(nodeId,Q);

					X=Q;
					aliveNodes[X].removeICustomer(nodeId);
					aliveNodes[X].removeJSubTree(nodeId);

					while(X!=-1){

						aliveNodes[X].removeJSubTree(nodeId);
						X=aliveNodes[X].Q;
					}

					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
							if(!aliveNodes[*itX].isPeer(*itZ))
								endFlowScale(*itX,*itZ);

					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(!aliveNodes[*itX].isPeer(*itRest))
								endFlowScale(*itX,*itRest);

					for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(!aliveNodes[*itZ].isPeer(*itRest))
								endFlowScale(*itZ,*itRest);

					endFlowScale(z,zNewProvider);
					aliveNodes[z].Q=zNewProvider;
					//aliveNodes[z].providerPrice=aliveNodes[aliveNodes[z].Q].price;
					for(int k=0;k<maxRegions;k++)
						for(int m=0;m<maxRegions;m++){
							tempCoordinate.xCoordinate=k;
							tempCoordinate.yCoordinate=m;

							if(aliveNodes[z].isPresentInRegion(tempCoordinate) && aliveNodes[zNewProvider].isPresentInRegion(tempCoordinate))
								tempPriceList.push_back(aliveNodes[zNewProvider].priceChart[k][m]);
						}

					tempPriceList.sort();
					aliveNodes[z].providerPrice=tempPriceList.front();

					tempPriceList.clear();



					establishLinkWithProvider(z,aliveNodes[z].Q);
					establishFlowWithProviderScale(z,aliveNodes[z].Q);

					X=aliveNodes[z].Q;
					aliveNodes[X].addICustomer(z);
					aliveNodes[X].addJSubTree(z);
					X=aliveNodes[X].Q;

					while(X!=-1){

						aliveNodes[X].addJSubTree(z);
						X=aliveNodes[X].Q;
					}

					endFlowScale(nodeId,z);
					Q=z;
					//providerPrice=aliveNodes[Q].price;
					for(int k=0;k<maxRegions;k++)
						for(int m=0;m<maxRegions;m++){
							tempCoordinate.xCoordinate=k;
							tempCoordinate.yCoordinate=m;

							if(isPresentInRegion(tempCoordinate) && aliveNodes[z].isPresentInRegion(tempCoordinate))
								tempPriceList.push_back(aliveNodes[z].priceChart[k][m]);
						}

					tempPriceList.sort();
					providerPrice=tempPriceList.front();



					establishLinkWithProvider(nodeId,Q);
					establishFlowWithProviderScale(nodeId,Q);

					X=Q;
					aliveNodes[X].addICustomer(nodeId);
					aliveNodes[X].addJSubTree(nodeId);
					X=aliveNodes[X].Q;
					while(X!=-1){

						aliveNodes[X].addJSubTree(nodeId);
						X=aliveNodes[X].Q;
					}

					list<int>::iterator it1;

					for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
						if(*itRest!=aliveNodes[z].Q && !aliveNodes[z].isPresentInCustomerTree(*itRest) && !aliveNodes[z].isPeer(*itRest))
							establishFlowPeeringScale(z,*itRest,aliveNodes[z].Q);

					for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
						if(*itZ!=Q && !isPresentInCustomerTree(*itZ) && !isPeer(*itZ))
							establishFlowPeeringScale(nodeId,*itZ,Q);

					for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(*itZ!=z && !aliveNodes[*itZ].isPresentInCustomerTree(*itRest) && !aliveNodes[*itZ].isPeer(*itRest))
								establishFlowPeeringScale(*itZ,*itRest,aliveNodes[*itZ].Q);

					for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
						if(!isPresentInCustomerTree(*itRest) && !isPeer(*itRest))
							establishFlowPeeringScale(nodeId,*itRest,Q);

					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itZ=setZ.begin();itZ!=setZ.end();itZ++)
							if(*itX!=nodeId && !aliveNodes[*itX].isPresentInCustomerTree(*itZ) && !aliveNodes[*itX].isPeer(*itZ))
								establishFlowPeeringScale(*itX,*itZ,aliveNodes[*itX].Q);


					for(itX=setX.begin();itX!=setX.end();itX++)
						for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
							if(*itX!=nodeId && !aliveNodes[*itX].isPresentInCustomerTree(*itRest) && !aliveNodes[*itX].isPeer(*itRest))
								establishFlowPeeringScale(*itX,*itRest,aliveNodes[*itX].Q);

					//re-establish flows within the customer tree of x and z
					list<int>::iterator itS;
					list<int>::iterator itE;
					for(itS=setX.begin();itS!=setX.end();itS++)
						for(itE=setX.begin();itE!=setX.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==1)
								endFlowScale(*itS,*itE);

					for(itS=setX.begin();itS!=setX.end();itS++)
						for(itE=setX.begin();itE!=setX.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==0 && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
								establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);

					for(itS=setZ.begin();itS!=setZ.end();itS++)
						for(itE=setZ.begin();itE!=setZ.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==1)
								endFlowScale(*itS,*itE);

					for(itS=setZ.begin();itS!=setZ.end();itS++)
						for(itE=setZ.begin();itE!=setZ.end();itE++)
							if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==0 && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
								establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);

				return true;

				}//end else Z is not Tier 1

			}// end if z is present in customer tree

			else{	//z is not present in customer tree

				endLinkScale(nodeId,Q);
				endFlowScale(nodeId,Q);

				X=Q;
				aliveNodes[X].removeICustomer(nodeId);
				aliveNodes[X].removeJSubTree(nodeId);
				X=aliveNodes[X].Q;

				while(X!=-1){

					aliveNodes[X].removeJSubTree(nodeId);
					X=aliveNodes[X].Q;
				}

				list<int> setX;
				list<int> setRest;
				list<int>::iterator itX;
				list<int>::iterator itRest;

				for(itX=J.begin();itX!=J.end();itX++)
					setX.push_back(*itX);
				setX.push_back(nodeId);

				for(int i=0;i<activeNodes;i++)
					if(i!=nodeId && !isPresentInCustomerTree(i))
						setRest.push_back(i);

				for(itX=setX.begin();itX!=setX.end();itX++)
					for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
						if(!aliveNodes[*itX].isPeer(*itRest)){
							endFlowScale(*itX,*itRest);

						}

				endFlowScale(nodeId,z);
				Q=z;
				//providerPrice=aliveNodes[Q].price;

				for(int k=0;k<maxRegions;k++)
					for(int m=0;m<maxRegions;m++){
						tempCoordinate.xCoordinate=k;
						tempCoordinate.yCoordinate=m;

						if(isPresentInRegion(tempCoordinate) && aliveNodes[z].isPresentInRegion(tempCoordinate))
							tempPriceList.push_back(aliveNodes[z].priceChart[k][m]);
					}

				tempPriceList.sort();
				providerPrice=tempPriceList.front();

				establishLinkWithProvider(nodeId,z);
				establishFlowWithProviderScale(nodeId,z);

				//updating new parent providers
				aliveNodes[Q].addICustomer(nodeId);
				aliveNodes[Q].addJSubTree(nodeId);

				P=aliveNodes[Q].Q;

				while(P!=-1){

					aliveNodes[P].addJSubTree(nodeId);
					P=aliveNodes[P].Q;

				}//end while

				list<int>::iterator it1;

				for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
					if(*itRest!=Q && !isPresentInCustomerTree(*itRest) && !isPeer(*itRest)){
						establishFlowPeeringScale(nodeId,*itRest,Q);

					}

				for(itX=setX.begin();itX!=setX.end();itX++)
					for(itRest=setRest.begin();itRest!=setRest.end();itRest++)
						if(*itX!=nodeId && !aliveNodes[*itX].isPresentInCustomerTree(*itRest) && !aliveNodes[*itX].isPeer(*itRest))
							establishFlowPeeringScale(*itX,*itRest,aliveNodes[*itX].Q);


				//re-establish flows within the customer tree of x
				list<int>::iterator itS;
				list<int>::iterator itE;
				for(itS=setX.begin();itS!=setX.end();itS++)
					for(itE=setX.begin();itE!=setX.end();itE++)
						if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==1)
							endFlowScale(*itS,*itE);

				for(itS=setX.begin();itS!=setX.end();itS++)
					for(itE=setX.begin();itE!=setX.end();itE++)
						if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && activeFlowIndicator[flowIndex[*itS][*itE]]==0 && !aliveNodes[*itS].isPresentInCustomerTree(*itE))
							establishFlowPeeringScale(*itS,*itE,aliveNodes[*itS].Q);

				return true;

			}//end else z is not present in customer tree

		}//end else x is not Tier 1

	}//end else TGS is not empty

	GS.clear();
	TGS.clear();
	return providerChange;

}//end getNewProvider

void updateVt(){

	for(int i=0;i<activeNodes;i++){
		aliveNodes[i].Vt=0.5*(aliveNodes[i].Vpp + aliveNodes[i].Vp + aliveNodes[i].Vc - (aliveNodes[i].trafficConsumed+aliveNodes[i].trafficGenerated));

		aliveNodes[i].V=aliveNodes[i].trafficConsumed+aliveNodes[i].trafficGenerated+aliveNodes[i].Vt;

		if(aliveNodes[i].Vt<0){
			cout<<"Node "<<i<<" Vt turned out to be less than zero: "<<aliveNodes[i].Vt<<endl;

			displayNodeData();
			displayTrafficMatrix();
			displayTopology();
			displayRouteData();

			string str="ERROR!!! Vt fallen below zero for a node";
			endSimulation(str);

		}

		if(aliveNodes[i].V<(aliveNodes[i].trafficGenerated+aliveNodes[i].trafficConsumed)){

			cout<<"Node "<<i<<" V turned out to be less than local traffic: "<<aliveNodes[i].V<<endl;

			displayNodeData();
			displayTrafficMatrix();
			displayTopology();
			displayRouteData();

			string str="ERROR!!! V less than local traffic for a node";
			endSimulation(str);

		}

	}
}

void expandNodeRandom(Coordinate originPoint, Node& nodeToExpand){

	int presenceCounter=1;
	int temp;
	list<Coordinate>::iterator it;

	list<Coordinate> locToChoose;
	Coordinate tempCoordinate;

	for(int i=0;i<maxRegions;i++)
		for(int j=0;j<maxRegions;j++){

			tempCoordinate.xCoordinate=i;
			tempCoordinate.yCoordinate=j;

			if((tempCoordinate.xCoordinate==originPoint.xCoordinate && tempCoordinate.yCoordinate==originPoint.yCoordinate) || (maxD!=-1 && geography[tempCoordinate.xCoordinate][tempCoordinate.yCoordinate].population>=maxD)){}

			else
				locToChoose.push_back(tempCoordinate);

		}

	int pops=0;
	while(nodeToExpand.gPresence.size()<nodeToExpand.numGPresence){

		if(locToChoose.empty()){

			for(int x=0;x<maxRegions;x++)
				for(int y=0;y<maxRegions;y++){
					cout<<"Loc nodes at "<<x<<","<<y<<" are "<<geography[x][y].population<<endl;
					pops+=geography[x][y].population;
				}


		}

		presenceCounter=rand()%locToChoose.size();
		temp=0;

		for(it=locToChoose.begin();it!=locToChoose.end();it++,temp++){

			if(temp==presenceCounter){
				nodeToExpand.gPresence.push_back(*it);

				geography[(*it).xCoordinate][(*it).yCoordinate].nodePresent.push_back(nodeToExpand.nodeId);
				geography[(*it).xCoordinate][(*it).yCoordinate].population++;

				locToChoose.erase(it);
				break;

			}//end if

		}//end for

	}//end while

	locToChoose.clear();

}

bool sortStraightByNumGPresence(geoIndexPair n1, geoIndexPair n2){

	if(n1.numGPresence<n2.numGPresence)
		return true;
	else
		return false;
}

bool sortReverseByNumGPresence(geoIndexPair n1, geoIndexPair n2){

	if(n1.numGPresence>n2.numGPresence)
		return true;
	else
		return false;
}

void updateFlowValueVectors(){

	for(int i=0;i<(activeNodes-1);i++){

		for(int j=i+1;j<activeNodes;j++){

			flowValueVector[flowIndex[i][j]]=trafficMatrix[i][j]+trafficMatrix[j][i];

		}

	}

}

void computeTraffic(){


	/*
	 * 1- Compute Generated traffic
	 * 2- Compute Consumed traffic
	 * 3- Compute traffic matrix
	 */

	double harmonicSum=0;
	int temp=0;
	double tempD=0;
	double tempD2=0;
	double totalConsumedTraffic=0;
	double totalGeneratedTraffic=0;
	double sZetaTrafficConsumption=0.8;
	list<double> trafficConsumptionFractions;
	geoIndexPair tmpPair;
	list<geoIndexPair> pairList;
	list<geoIndexPair>::iterator itPair;
	list<double>::iterator itDouble;

	//re-initialize traffic matrix
	for(int i=0;i<activeNodes;i++)
		for(int j=0;j<activeNodes;j++)
			trafficMatrix[i][j]=-1;


	//Calculating fractions for consumed traffic
	harmonicSum=0;
	tempD=0;
	double* tCon=new double[activeNodes+1];
	for(int i=1;i<=activeNodes;i++){
		harmonicSum+=(1/pow(i,sZetaTrafficCon));
	}

	for(int i=1;i<=activeNodes;i++){
		tCon[i]=(1/pow(i,sZetaTrafficCon))/harmonicSum;
		tempD+=tCon[i];

		if(i>1 && (tCon[i]>tCon[i-1])){

			cout<<"ERROR in computing fractions for consumed traffic!! Fractions produced in wrong order"<<endl;
			logFile<<"ERROR in computing fractions for consumed traffic!! Fractions produced in wrong order";

			string str="ERROR!! in initialization";
			endSimulation(str);

		}

	}

	if(tempD<0.98){	//not exact value of 1 used. tempD=0.99999999 Checked earlier.

		cout<<"ERROR in computing fractions for consumed traffic!! Fractions do not sum to 1"<<endl;
		logFile<<"ERROR in computing fractions for consumed traffic!! Fractions do not sum to 1";

		string str="ERROR!! in initialization";
		endSimulation(str);
	}


	for(int i=0;i<activeNodes;i++){
		tmpPair.index=i;
		tmpPair.numGPresence=aliveNodes[i].numGPresence;
		pairList.push_back(tmpPair);
	}

	pairList.sort(sortGExpanseReverse);

	temp=1;
	//cout<<"Consumed traffic: "<<endl;
	for(itPair=pairList.begin();itPair!=pairList.end();itPair++,temp++){
		aliveNodes[(*itPair).index].trafficConsumedFraction=tCon[temp];
	//	cout<<(*itPair).index<<"\t"<<(*itPair).numGPresence<<"\t"<<tCon[temp]<<endl;
	}


	//compute total traffic in the network
	itPair=pairList.begin();

	totalTraffic=ceil(maxTraffic/aliveNodes[(*itPair).index].trafficConsumedFraction);

	cout<<"Total Traffic: "<<totalTraffic<<endl;
	cout<<"Max consumed traffic fraction: "<<aliveNodes[(*itPair).index].trafficConsumedFraction<<endl;
	cout<<"Max Consumed traffic: "<<totalTraffic*aliveNodes[(*itPair).index].trafficConsumedFraction<<endl;


	//calculation of generated traffic fractions
	harmonicSum=0;
	tempD=0;
	double* tGen=new double[activeNodes+1];
	for(int i=1;i<=activeNodes;i++){
		harmonicSum+=(1/pow(i,sZetaTrafficGen));
	}

	for(int i=1;i<=activeNodes;i++){
		tGen[i]=(1/pow(i,sZetaTrafficGen))/harmonicSum;
		tempD+=tGen[i];

		if(i>1 && (tGen[i]>tGen[i-1])){

			cout<<"ERROR in computing fractions for generated traffic!! Fractions produced in wrong order"<<endl;
			logFile<<"ERROR in computing fractions for generated traffic!! Fractions produced in wrong order";

			string str="ERROR!! in initialization";
			endSimulation(str);

		}

	}

	if(tempD<0.98){	//not exact value of 1 used. tempD=0.99999999 Checked earlier.

		cout<<"ERROR in computing fractions for generated traffic!! Fractions do not sum to 1"<<endl;
		logFile<<"ERROR in computing fractions for generated traffic!! Fractions do not sum to 1";

		string str="ERROR!! in initialization";
		endSimulation(str);
	}

	//permute(true);
	if(nodeOrder.size()<activeNodes)
		refillNodeOrder();

	temp=-1;
	tempD=0;
	tempD2=0;
	int maxIndex=0;

	for(int i=1;i<=activeNodes;i++){

		temp=getNewIt();
		if(temp>=0){
			aliveNodes[temp].trafficGenerated=round(tGen[i]*totalTraffic);
			tempD+=aliveNodes[temp].trafficGenerated;

			if(aliveNodes[temp].trafficGenerated>tempD2){
				tempD2=aliveNodes[temp].trafficGenerated;
				maxIndex=temp;
			}

		}

	}

	if(tempD<totalTraffic){
		aliveNodes[maxIndex].trafficGenerated+=(totalTraffic-tempD);

	}

	//just in case
	for(int i=0;i<activeNodes;i++)
		if(aliveNodes[i].trafficGenerated==0){
			cout<<"Something is wrong just in case used for traffic"<<endl;
			logFile<<"Something is wrong just in case used for traffic"<<endl;
			aliveNodes[i].trafficGenerated=rand()%15+1;
		}

	//computing traffic matrix
	for(int i=0;i<activeNodes;i++){

		tempD=0;
		tempD2=totalTraffic*10;
		for(int j=0;j<activeNodes;j++){

			if(i!=j){

				trafficMatrix[i][j]=round(aliveNodes[i].trafficGenerated*aliveNodes[j].trafficConsumedFraction);
				tempD+=round(aliveNodes[i].trafficGenerated*aliveNodes[j].trafficConsumedFraction);
				aliveNodes[j].trafficConsumed+=round(aliveNodes[i].trafficGenerated*aliveNodes[j].trafficConsumedFraction);

				if(aliveNodes[j].trafficConsumed<tempD2){
					temp=j;
					tempD2=aliveNodes[j].trafficConsumed;

				}
			}

		}

		if((tempD2=aliveNodes[i].trafficGenerated-tempD)>0){

			/*
			cout<<"Previous temp is: "<<temp<<endl;
			temp=findMinConsumedTraffic(i);
			cout<<"New temp is : "<<temp<<endl;
			*/

			//cout<<"Sending additional traffic "<<tempD2<<" from "<<i<<" to "<<temp<<endl;
			trafficMatrix[i][temp]+=tempD2;
			aliveNodes[temp].trafficConsumed+=tempD2;

		}

	}

	//updating values
	for(int i=0;i<activeNodes;i++){
		aliveNodes[i].trafficGenerated=0;
		aliveNodes[i].trafficConsumed=0;
	}

	for(int i=0;i<activeNodes;i++)
		for(int j=0;j<activeNodes;j++){
			if(i!=j){
				aliveNodes[i].trafficGenerated+=trafficMatrix[i][j];
			}
		}

	for(int i=0;i<activeNodes;i++)
		for(int j=0;j<activeNodes;j++){
			if(i!=j){
				aliveNodes[i].trafficConsumed+=trafficMatrix[j][i];
			}
		}

	temp=0;
	for(int i=0;i<activeNodes;i++)
		if(aliveNodes[i].trafficConsumed==0)
			temp++;

	cout<<"No consumed traffic for "<<temp<<" number of nodes"<<endl;


	int numOverlap=0;
	int potentialPeers=0;

	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++)
			if(aliveNodes[i].doesShareGeography(j)){
				numOverlap++;
				if((trafficMatrix[i][j]+trafficMatrix[j][i])>peeringThreshold)
					potentialPeers++;
			}

	cout<<"Overlap: "<<numOverlap<<endl;
	cout<<"PP: "<<potentialPeers<<endl;
	cout<<"Percentage: "<<static_cast<double>(potentialPeers*100)/static_cast<double>(numOverlap)<<endl;

	delete [] tCon;
	delete [] tGen;

}




bool validateInitialization(){

	/*
	 * 1- Check if only init nodes are active
	 * 2- Check if all active nodes have traffic, geography, price assigned
	 * 3- Check the status of all flows
	 * 4- Check if Tier1-s are properly connected
	 * 5- Check if network is connected
	 */

	int numActiveNodes=0;
	list<int>::iterator it1;
	list<int>::iterator it2;

	for(int i=0;i<maxNodes;i++)
		if(aliveNodes[i].lifeStatus==alive)
			numActiveNodes++;

	if(!numActiveNodes==(initNodes-1)){
		string str="ERROR!! Number of active nodes exceeds number of initNodes in initialization";
		endSimulation(str);
	}

	for(int i=0;i<activeNodes;i++){

		if(aliveNodes[i].trafficGenerated==0 || aliveNodes[i].trafficConsumed==0 || aliveNodes[i].V==0 || aliveNodes[i].Vo==0 || (aliveNodes[i].Vo!=(aliveNodes[i].trafficConsumed + aliveNodes[i].trafficGenerated))){
			cout<<"Node "<<i<<" traffic has a problem"<<endl;
			string str="ERROR!! Traffic not properly initialized in initialization";
			endSimulation(str);
		}

	}

	checkConnectivity();
}

void initialize(){	//initialize the simulation

	/*
	 * Initializing data structures associated with routing scheme
	 */

	list<geoIndexPair> geoIndexList;
	geoIndexPair giPair;
	Coordinate nodeLocation;
	bool nodeDropped=false;
	list<int>::iterator itInt;
	list<geoIndexPair>::iterator itGeo;
	int temp1=0;
	int tempInt=-1;

#if DEBUG
	logFile<<"Initializing "<<maxNodes<<" nodes."<<endl;
#endif

	for(int i=0;i<5;i++)
		for(int j=0;j<500;j++)
			fitnessRecord[i][j]=-1;

	maxLinks=static_cast<int>(ceil((maxNodes*(maxNodes-1))/2));
	activeNodes=initNodes;

//******************************** Initializing Routing data structures ****************************
	if(maxNodes>1000){
		cout<<"WARNING!! Very large network being simulated"<<endl;
		logFile<<"WARNING!! Very large network being simulated"<<endl;
	}

	maxFlows=static_cast<int>(ceil((maxNodes*(maxNodes-1))/2));

	/*
	routingMatrixScale=new list<int>[maxFlows];

	routingMatrixScaleAsym=new list<int>[maxFlows];

	flowIndex=new int*[maxNodes];

	for(int i=0;i<maxNodes;i++){
		flowIndex[i]=new int[maxNodes];
	}

	for(int i=0;i<maxNodes;i++)
		for(int j=0;j<maxNodes;j++)
			flowIndex[i][j]=-1;

	flowValueVector=new double[maxFlows];

	flowValueVectorAsym=new double[maxFlows];

	for(unsigned int i=0;i<maxFlows;i++){
			flowValueVector[i]=0;
			flowValueVectorAsym[i]=0;
	}

	linkValueVector=new double[maxLinks];

	aliveLinkIndicator=new bool[maxLinks];

	for(int i=0;i<maxLinks;i++){
		linkValueVector[i]=0;
		aliveLinkIndicator[i]=0;
	}

	aliveFlowIndicator=new bool[maxFlows];

	activeFlowIndicator=new bool[maxFlows];

	flowDirectionFrom=new int[maxFlows];

	flowDirectionFromAsym=new int[maxFlows];

	for(unsigned int i=0;i<maxFlows;i++){
		aliveFlowIndicator[i]=0;
		activeFlowIndicator[i]=0;
		flowDirectionFrom[i]=-1;
		flowDirectionFromAsym[i]=-1;
	}

	linkIndex=new linkInfo*[maxNodes];

	for(int i=0;i<maxNodes;i++){
		linkIndex[i]=new linkInfo[maxNodes];

	}
	*/

	routingMatrixScale=new list<int>[maxFlows];
	routingMatrixScaleSave=new list<int>[maxFlows];

	routingMatrixScaleAsym=new list<int>[maxFlows];
	routingMatrixScaleAsymSave=new list<int>[maxFlows];

	flowIndex=new int*[maxNodes];
	flowIndexSave=new int*[maxNodes];

	for(int i=0;i<maxNodes;i++){
		flowIndex[i]=new int[maxNodes];
		flowIndexSave[i]=new int[maxNodes];
	}

	for(int i=0;i<maxNodes;i++)
		for(int j=0;j<maxNodes;j++)
			flowIndex[i][j]=-1;

	flowValueVector=new double[maxFlows];
	flowValueVectorSave=new double[maxFlows];

	flowValueVectorAsym=new double[maxFlows];
	flowValueVectorAsymSave=new double[maxFlows];

	for(unsigned int i=0;i<maxFlows;i++){
		flowValueVector[i]=0;
		flowValueVectorAsym[i]=0;
	}

	linkValueVector=new double[maxLinks];
	linkValueVectorSave=new double[maxLinks];

	aliveLinkIndicator=new bool[maxLinks];
	aliveLinkIndicatorSave=new bool[maxLinks];

	for(int i=0;i<maxLinks;i++){
		linkValueVector[i]=0;
		aliveLinkIndicator[i]=0;
	}

	aliveFlowIndicator=new bool[maxFlows];
	aliveFlowIndicatorSave=new bool[maxFlows];

	activeFlowIndicator=new bool[maxFlows];
	activeFlowIndicatorSave=new bool[maxFlows];

	flowDirectionFrom=new int[maxFlows];
	flowDirectionFromSave=new int[maxFlows];

	flowDirectionFromAsym=new int[maxFlows];
	flowDirectionFromAsymSave=new int[maxFlows];

	for(unsigned int i=0;i<maxFlows;i++){
		aliveFlowIndicator[i]=0;
		activeFlowIndicator[i]=0;
		flowDirectionFrom[i]=-1;
		flowDirectionFromAsym[i]=-1;
	}

	linkIndex=new linkInfo*[maxNodes];
	linkIndexSave=new linkInfo*[maxNodes];

	for(int i=0;i<maxNodes;i++){
		linkIndex[i]=new linkInfo[maxNodes];
		linkIndexSave[i]=new linkInfo[maxNodes];
	}



	//*********************************************************************************
	for(int i=0;i<maxNodes;i++)
		for(int j=0;j<maxNodes;j++){
			linkIndex[i][j].index=-1;
			linkIndex[i][j].provider=-1;
			linkIndex[i][j].linkClass=CPLink;
		}

	//******************************** Creating traffic matrix **************************************
	trafficMatrix=new double*[maxNodes];
	for(int i=0;i<maxNodes;i++)
		trafficMatrix[i]=new double[maxNodes];

	//all traffic defaults to -1
	for(int i=0;i<maxNodes;i++)
		for(int j=0;j<maxNodes;j++)
			trafficMatrix[i][j]=-1;

	//******************************* Creating geography & geographic distribution ******************
	geography=new Region*[maxRegions];
	for(int i=0;i<maxRegions;i++)
		geography[i]=new Region[maxRegions];

	for(int i=0;i<maxRegions;i++)
		for(int j=0;j<maxRegions;j++){
			geography[i][j].location.xCoordinate=i;
			geography[i][j].location.yCoordinate=j;
			geography[i][j].maxDensityAllowed=maxD;
		}


	/*
	 * Steps to be carried out
	 * 0- Create aliveNodes array
	 * 1- Initialize init Nodes
	 * 2- Assign geography
	 * 3- Create Traffic matrix
	 * 4- Populate Traffic matrix entries
	 * 5- Find providers
	 * 6- Establish flows and update routing matrices
	 */

	//creating aliveNodes array
	aliveNodes=new Node[maxNodes];
	aliveNodesSave=new Node[maxNodes];

	for(int i=0;i<maxNodes;i++){

		aliveNodes[i].nodeId=i;
		aliveNodes[i].lifeStatus=dead;
		aliveNodes[i].priceChart=new double*[maxRegions];

		for(int j=0;j<maxRegions;j++)
			aliveNodes[i].priceChart[j]=new double[maxRegions];

	}

	//seed for population
	permute(true,mySeed);

	int* y=new int[maxRegions*maxRegions+1];
	double* PYy=new double[maxRegions*maxRegions+1];
	double* gy=new double[maxRegions*maxRegions+1];
	double harmonicSum=0;

	list<int> gPresenceList;

	//evaluating denominator for Zipf
	for(int i=1;i<=maxRegions*maxRegions;i++){
		harmonicSum+=(1/pow(i,sZetaGeography));
		y[i]=i;
	}

	for(int i=1;i<=maxRegions*maxRegions;i++){

		PYy[i]=(1/pow(i,sZetaGeography))/harmonicSum;
		gy[i]=round(activeNodes*PYy[i]);

		for(int j=0;j<static_cast<int>(gy[i]);j++){
			gPresenceList.push_back(y[i]);
		}

	}

	while((tempInt=getNewIt())!=-1 && !gPresenceList.empty()){

		aliveNodes[tempInt].numGPresence=gPresenceList.front()%16;
		if(aliveNodes[tempInt].numGPresence==0)
			aliveNodes[tempInt].numGPresence=1;
		gPresenceList.pop_front();

	}

	int leftOver=0;
	//left over nodes if any
	for(int i=0;i<activeNodes;i++){
		if(aliveNodes[i].numGPresence==0){
			leftOver++;
			aliveNodes[i].numGPresence=1;

		}
	}

	geoIndexList.clear();
	//Initializing
	for(int i=0;i<activeNodes;i++){

		//populating structure for sorting by geographic expanse
		aliveNodes[i].lifeStatus=alive;
		giPair.index=i;
		giPair.numGPresence=aliveNodes[i].numGPresence;
		geoIndexList.push_back(giPair);
		temp1+=aliveNodes[i].numGPresence;
		aliveNodes[i].peerCriteria=universalSigma;

	}//end for creation of nodes

#if DEBUG
	logFile<<"Total PoPs are: "<<temp1<<endl;
#endif

	//Assigning geography
	//Step 2b Expand the nodes
	geoIndexList.sort(sortReverseByNumGPresence);	//bigger nodes get regions first

	for(itGeo=geoIndexList.begin();itGeo!=geoIndexList.end();itGeo++){

		//first node can go to any region since initial population in geography is zero
		if(itGeo==geoIndexList.begin()){

			nodeLocation.xCoordinate=rand()%maxRegions;
			nodeLocation.yCoordinate=rand()%maxRegions;
			aliveNodes[(*itGeo).index].gPresence.push_back(nodeLocation);

			if(maxD!=-1){
				chosenMaxDLoc.xCoordinate=nodeLocation.xCoordinate;
				chosenMaxDLoc.yCoordinate=nodeLocation.yCoordinate;
			}

		}

		else{

			while(nodeDropped==false){

				nodeLocation.xCoordinate=rand()%maxRegions;
				nodeLocation.yCoordinate=rand()%maxRegions;

				/*if(maxD!=-1 && geography[chosenMaxDLoc.xCoordinate][chosenMaxDLoc.yCoordinate].population<maxD){
					nodeLocation.xCoordinate=chosenMaxDLoc.xCoordinate;
					nodeLocation.yCoordinate=chosenMaxDLoc.yCoordinate;
				}*/

				if(geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].population==0){
					continue;
				}

				else{
					aliveNodes[(*itGeo).index].gPresence.push_back(nodeLocation);
					nodeDropped=true;
					break;
				}

			}//end while

			nodeDropped=false;

		}//end else

		geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].nodePresent.push_back((*itGeo).index);
		geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].population++;

		//expand the node to its allowed expanse
		if((*itGeo).numGPresence>1){
			expandNodeRandom(nodeLocation,aliveNodes[(*itGeo).index]);
		}

	}//end for

	//****************************** Traffic Matrix calculation

	computeTraffic();

	//****************************** Price Assignment *********************************
	//complete randomization

	Coordinate tempCoordinate;
	for(int i=activeNodes-1;i>=0;i--){

		for(int j=0;j<maxRegions;j++)
			for(int k=0;k<maxRegions;k++){
				tempCoordinate.xCoordinate=j;
				tempCoordinate.yCoordinate=k;
				if(aliveNodes[i].isPresentInRegion(tempCoordinate)){
					aliveNodes[i].priceChart[j][k]=35+rand()%10+(static_cast<double>(rand()%100)/100);
					aliveNodes[i].price+=aliveNodes[i].priceChart[j][k];
				}
			}

		aliveNodes[i].price=aliveNodes[i].price/aliveNodes[i].numGPresence;
		aliveNodes[i].paidPeeringPrice=aliveNodes[i].price/2;

	}

	//****************************** Determining overlaps *******************************
	for(int i=0;i<activeNodes;i++)
		for(int j=0;j<activeNodes;j++)
			if(i!=j && aliveNodes[i].doesShareGeography(j))
				aliveNodes[i].overLap.push_back(j);

	//******************** Initial Topology formation *********************************
	int numProviderAssigned=0;	//variable to track how many nodes have been assigned provider

	initialCliqueSize=5;

	permute(true,initialTopologySeed);

	geoIndexList.sort(sortStraightByNumGPresence);

	for(itGeo=geoIndexList.begin();itGeo!=geoIndexList.end();itGeo++){

		if(PEERING==true && (activeNodes-numProviderAssigned)==initialCliqueSize)
			break;

		aliveNodes[(*itGeo).index].getInitialProviderRand();

		if(aliveNodes[(*itGeo).index].Q!=-1){

			numProviderAssigned++;
			establishLinkWithProvider((*itGeo).index,aliveNodes[(*itGeo).index].Q);
			establishFlowWithProviderScale((*itGeo).index,aliveNodes[(*itGeo).index].Q);

		}

	}

	if(numProviderAssigned<(initNodes-initialCliqueSize)){

		logFile<<"Providers not properly assigned"<<endl;
		string str="ERROR!! Error in assignment of providers in initialization";
		endSimulation(str);
	}


	for(int m=0;m<activeNodes;m++){

		if(aliveNodes[m].Q==-1){

			for(int n=0;n<activeNodes;n++){

				if(m!=n && aliveNodes[n].Q==-1 && !aliveNodes[m].isPeer(n)){

					aliveNodes[m].insertPeerInK(n);
					aliveNodes[n].insertPeerInK(m);

					establishLinkWithPeer(m,n);
					establishFlowWithPeerScale(m,n);


				}//end if

			}//end for

		}//end if

	}//end for

	//Step 5- updating routing matrices
	for(int i=0;i<activeNodes;i++){

		for(int j=0;j<activeNodes;j++){

			if(j!=i && j!=aliveNodes[i].Q && !aliveNodes[i].isPresentInCustomerTree(j) && !aliveNodes[i].isPeer(j) && flowIndex[i][j]==-1){

				establishFlowPeeringScale(i,j,aliveNodes[i].Q);
			}

		}

	}//end for

	for(int i=0;i<activeNodes;i++){
		if(!aliveNodes[i].J.empty()){
			aliveNodes[i].J.sort();
			aliveNodes[i].J.unique();
		}

		if(aliveNodes[i].Q==-1)
			Tier1.push_back(i);

	}


}//end initialization

void routingScale(){

	VolumePrice tempVP;
	compactMatrix();

	for(int i=0;i<maxLinks;i++){
		linkValueVector[i]=0;
	}

	for(int i=0;i<activeNodes;i++){
		aliveNodes[i].customerVPList.clear();
		aliveNodes[i].providerVPList.clear();
		aliveNodes[i].peerVPList.clear();
		aliveNodes[i].superPeerVPList.clear();
		aliveNodes[i].poorPeerVPList.clear();
		aliveNodes[i].Vp=aliveNodes[i].Vc=aliveNodes[i].Vpp=0;
	}

	list<int>::iterator it;
	for(unsigned int i=0;i<maxFlows;i++){

		for(it=routingMatrixScale[i].begin();it!=routingMatrixScale[i].end();it++){
			linkValueVector[*it]+=flowValueVector[i];

		}

		for(it=routingMatrixScaleAsym[i].begin();it!=routingMatrixScaleAsym[i].end();it++){
			linkValueVector[*it]+=flowValueVectorAsym[i];

		}

	}

	for(int i=0;i<(activeNodes-1);i++){

		for(int j=i+1;j<activeNodes;j++){

			if(linkIndex[i][j].index!=-1){

				if(linkIndex[i][j].linkClass==CPLink){

					if(linkIndex[i][j].provider==i){

						tempVP.volume=linkValueVector[linkIndex[i][j].index];
						tempVP.contractPrice=aliveNodes[j].providerPrice;

						aliveNodes[j].Vp+=linkValueVector[linkIndex[i][j].index];
						aliveNodes[i].Vc+=linkValueVector[linkIndex[i][j].index];

						aliveNodes[i].customerVPList.push_back(tempVP);
						aliveNodes[j].providerVPList.push_back(tempVP);

					}//end if

					else{

						tempVP.volume=linkValueVector[linkIndex[i][j].index];
						tempVP.contractPrice=aliveNodes[i].providerPrice;

						aliveNodes[i].Vp+=linkValueVector[linkIndex[i][j].index];
						aliveNodes[j].Vc+=linkValueVector[linkIndex[i][j].index];

						aliveNodes[j].customerVPList.push_back(tempVP);
						aliveNodes[i].providerVPList.push_back(tempVP);

					}//end else

				}//end if for CPLink

				else if(linkIndex[i][j].linkClass==PPLink){	//ordinary peering link

					tempVP.volume=linkValueVector[linkIndex[i][j].index];

					aliveNodes[i].Vpp+=linkValueVector[linkIndex[i][j].index];
					aliveNodes[j].Vpp+=linkValueVector[linkIndex[i][j].index];

					aliveNodes[i].peerVPList.push_back(tempVP);
					aliveNodes[j].peerVPList.push_back(tempVP);
				}

				else{		//paid peering link

					if(linkIndex[i][j].superPeer==i){

						tempVP.volume=linkValueVector[linkIndex[i][j].index];
						tempVP.contractPrice=aliveNodes[i].paidPeeringPrice;

						aliveNodes[j].Vpp+=linkValueVector[linkIndex[i][j].index];
						aliveNodes[i].Vpp+=linkValueVector[linkIndex[i][j].index];

						aliveNodes[i].superPeerVPList.push_back(tempVP);
						aliveNodes[j].poorPeerVPList.push_back(tempVP);

					}//end if

					else{

						tempVP.volume=linkValueVector[linkIndex[i][j].index];
						tempVP.contractPrice=aliveNodes[i].paidPeeringPrice;

						aliveNodes[i].Vpp+=linkValueVector[linkIndex[i][j].index];
						aliveNodes[j].Vpp+=linkValueVector[linkIndex[i][j].index];

						aliveNodes[j].superPeerVPList.push_back(tempVP);
						aliveNodes[i].poorPeerVPList.push_back(tempVP);

					}//end else

				}

			}//end if for index!=-1

		}//end for

	}//end for


	//update customer volume
	list<VolumePrice>::iterator itVP;
	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].customerVPList.empty()){

			for(itVP=aliveNodes[i].customerVPList.begin();itVP!=aliveNodes[i].customerVPList.end();itVP++)
				aliveNodes[i].Vc+=(*itVP).volume;
		}

}


void compactMatrix(){

	numFlows=0;
	unsigned int j=0;
	while(aliveFlowIndicator[j]==1 && j<maxFlows){
		numFlows++;
		j++;
	}

}//end function

void establishLinkWithPeer(int sPeer, int ePeer){

	int designatedRow=0;
	bool linkFound=false;

	for(int i=0;i<maxLinks;i++)
		if(aliveLinkIndicator[i]==0){
			aliveLinkIndicator[i]=1;
			designatedRow=i;
			linkFound=true;
			break;
		}

	if(linkFound){

		if(aliveNodes[sPeer].peeringStrategyNumber!=5 && aliveNodes[ePeer].peeringStrategyNumber!=5){
			linkIndex[sPeer][ePeer].index=designatedRow;
			linkIndex[ePeer][sPeer].index=designatedRow;
			linkIndex[sPeer][ePeer].linkClass=PPLink;
			linkIndex[ePeer][sPeer].linkClass=PPLink;
		}

		else{

			linkIndex[sPeer][ePeer].index=designatedRow;
			linkIndex[ePeer][sPeer].index=designatedRow;
			linkIndex[sPeer][ePeer].linkClass=PPPLink;
			linkIndex[ePeer][sPeer].linkClass=PPPLink;

			if(aliveNodes[sPeer].peeringStrategyNumber!=5 && aliveNodes[ePeer].peeringStrategyNumber==5){
				linkIndex[sPeer][ePeer].superPeer=ePeer;
				linkIndex[ePeer][sPeer].superPeer=ePeer;
			}

			else if(aliveNodes[sPeer].peeringStrategyNumber==5 && aliveNodes[ePeer].peeringStrategyNumber!=5){
				linkIndex[sPeer][ePeer].superPeer=sPeer;
				linkIndex[ePeer][sPeer].superPeer=sPeer;
			}

			else{

				if(aliveNodes[sPeer].paidPeeringPrice>aliveNodes[ePeer].paidPeeringPrice){
					linkIndex[sPeer][ePeer].superPeer=sPeer;
					linkIndex[ePeer][sPeer].superPeer=sPeer;
				}
				else{
					linkIndex[sPeer][ePeer].superPeer=ePeer;
					linkIndex[ePeer][sPeer].superPeer=ePeer;
				}
			}
		}
	}

	else{

		string str("ERROR!! NO ROW AVAILABLE IN ROUTING MATRIX TO ESTABLISH LINK");
		endSimulation(str);

	}

}

void establishFlowWithPeerScale(int sPeer, int ePeer){

	int designatedColumn;
	bool columnFound=false;

	if(flowIndex[sPeer][ePeer]==-1){
		for(unsigned int j=0;j<maxFlows;j++)
			if(aliveFlowIndicator[j]==0){
				aliveFlowIndicator[j]=1;
				designatedColumn=j;
				columnFound=true;
				break;
			}

		if(columnFound){
			flowIndex[sPeer][ePeer]=designatedColumn;
			flowIndex[ePeer][sPeer]=designatedColumn;
			activeFlowIndicator[designatedColumn]=1;
		}

		else{
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}
	}

	else
		designatedColumn=flowIndex[sPeer][ePeer];

	activeFlowIndicator[designatedColumn]=1;

	//routingMatrix[linkIndex[sPeer][ePeer].index][designatedColumn]=1;
	routingMatrixScale[designatedColumn].push_back(linkIndex[sPeer][ePeer].index);
	routingMatrixScaleAsym[designatedColumn].push_back(linkIndex[sPeer][ePeer].index);

	//Asymmetric routing
	flowValueVector[designatedColumn]=trafficMatrix[sPeer][ePeer];
	flowValueVectorAsym[designatedColumn]=trafficMatrix[ePeer][sPeer];

	flowDirectionFrom[designatedColumn]=sPeer;
	flowDirectionFromAsym[designatedColumn]=ePeer;

}

void establishFlowWithPeer(int sPeer,int ePeer){

	int designatedColumn;
	bool columnFound=false;

	if(flowIndex[sPeer][ePeer]==-1){
		for(int j=0;j<maxFlows;j++)
			if(aliveFlowIndicator[j]==0){
				aliveFlowIndicator[j]=1;
				designatedColumn=j;
				columnFound=true;
				break;
			}

		if(columnFound){
			flowIndex[sPeer][ePeer]=designatedColumn;
			flowIndex[ePeer][sPeer]=designatedColumn;
			activeFlowIndicator[designatedColumn]=1;
		}

		else{
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}
	}

	else
		designatedColumn=flowIndex[sPeer][ePeer];

	activeFlowIndicator[designatedColumn]=1;
	routingMatrix[linkIndex[sPeer][ePeer].index][designatedColumn]=1;
	flowValueVector[designatedColumn]=trafficMatrix[ePeer][sPeer]+trafficMatrix[sPeer][ePeer];

}

void establishLinkWithProvider(int pNode, int qNode){

	int designatedRow=0;
	bool linkFound=false;

	for(int i=0;i<maxLinks;i++)
		if(aliveLinkIndicator[i]==0){
			aliveLinkIndicator[i]=1;
			designatedRow=i;
			linkFound=true;
			break;
		}


	if(linkFound){
		linkIndex[pNode][qNode].index=designatedRow;
		linkIndex[qNode][pNode].index=designatedRow;
		linkIndex[pNode][qNode].provider=qNode;
		linkIndex[qNode][pNode].provider=qNode;
		linkIndex[pNode][qNode].linkClass=CPLink;
		linkIndex[qNode][pNode].linkClass=CPLink;
	}

	else{

		string str("ERROR!! NO ROW AVAILABLE IN ROUTING MATRIX TO ESTABLISH LINK");
		endSimulation(str);

	}

}

void establishFlowWithProviderScale(int pNode,int qNode){


	int designatedColumn;
	bool columnFound=false;

	if(flowIndex[pNode][qNode]==-1){
		for(int j=0;j<maxFlows;j++)
			if(aliveFlowIndicator[j]==0){
				aliveFlowIndicator[j]=1;
				designatedColumn=j;
				columnFound=true;
				break;
			}

		if(columnFound){
			flowIndex[pNode][qNode]=designatedColumn;
			flowIndex[qNode][pNode]=designatedColumn;
			activeFlowIndicator[designatedColumn]=1;
		}

		else{
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}
	}

	else
		designatedColumn=flowIndex[pNode][qNode];

	activeFlowIndicator[designatedColumn]=1;

	//routingMatrix[linkIndex[pNode][qNode].index][designatedColumn]=1;
	routingMatrixScale[designatedColumn].push_back(linkIndex[pNode][qNode].index);

	//Asymmetric routing introduced
	routingMatrixScaleAsym[designatedColumn].push_back(linkIndex[pNode][qNode].index);

	flowValueVector[designatedColumn]=trafficMatrix[pNode][qNode];
	flowValueVectorAsym[designatedColumn]=trafficMatrix[qNode][pNode];

	flowDirectionFrom[designatedColumn]=pNode;
	flowDirectionFromAsym[designatedColumn]=qNode;

}

void establishFlowWithProvider(int pNode,int qNode){

	int designatedColumn;
	bool columnFound=false;

	if(flowIndex[pNode][qNode]==-1){
		for(int j=0;j<maxFlows;j++)
			if(aliveFlowIndicator[j]==0){
				aliveFlowIndicator[j]=1;
				designatedColumn=j;
				columnFound=true;
				break;
			}

		if(columnFound){
			flowIndex[pNode][qNode]=designatedColumn;
			flowIndex[qNode][pNode]=designatedColumn;
			activeFlowIndicator[designatedColumn]=1;
		}

		else{
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}
	}

	else
		designatedColumn=flowIndex[pNode][qNode];

	activeFlowIndicator[designatedColumn]=1;
	routingMatrix[linkIndex[pNode][qNode].index][designatedColumn]=1;
	flowValueVector[designatedColumn]=trafficMatrix[pNode][qNode]+trafficMatrix[qNode][pNode];

}


void mergeTwoListsScale(list<int>& missingFlow, list<int>& firstList){

	list<int>::iterator it;

	for(it=firstList.begin();it!=firstList.end();it++)
		missingFlow.push_back(*it);

	missingFlow.sort();
	missingFlow.unique();

}

void mergeListsIntoOneScale(list<int>& destinationList, list<int>& firstList, list<int>& endList){

	list<int>::iterator it;
	for(it=firstList.begin();it!=firstList.end();it++)
		destinationList.push_back(*it);

	for(it=endList.begin();it!=endList.end();it++)
		destinationList.push_back(*it);

	destinationList.sort();
	destinationList.unique();

}


bool establishFlowPeeringScale(int startNode, int endNode, int qNode){

	if(startNode==-1 || endNode==-1){

		if(startNode==-1){
			string str("ERROR!! ONE OF THE NODES (startNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}
		else{
			string str("ERROR!! ONE OF THE NODES (endNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}
	}

	//Step 1 Find designated column
	//Step 2 Go over peers to see if the endNode is in the customer tree of peer
	//Step 3 Go to parent

	int designatedColumn;
	bool columnFound=false;
	list<int>::iterator itK;
	bool presentInPeerTree=false;
	int intermediaryPeer=-1;
	list<int> missingFlow;
	list<int>::iterator itInt;

	if(flowIndex[startNode][endNode]==-1){
		for(int j=0;j<maxFlows;j++)
			if(aliveFlowIndicator[j]==0){
				aliveFlowIndicator[j]=1;
				activeFlowIndicator[j]=1;
				designatedColumn=j;
				columnFound=true;
				break;
			}

		if(columnFound){
			flowIndex[startNode][endNode]=designatedColumn;
			flowIndex[endNode][startNode]=designatedColumn;
		}

		else{
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}

	}

	designatedColumn=flowIndex[startNode][endNode];

	//Step 2 Go over all peers in order
	if(!aliveNodes[startNode].K.empty()){
		for(itK=aliveNodes[startNode].K.begin();itK!=aliveNodes[startNode].K.end();itK++){
			if(aliveNodes[*itK].isPresentInCustomerTree(endNode)){
				presentInPeerTree=true;
				intermediaryPeer=*itK;
				break;
			}
		}
	}

	if(aliveNodes[startNode].isPresentInCustomerTree(endNode)){	//endNode is present in customer tree of startNode

		for(itInt=aliveNodes[startNode].I.begin();itInt!=aliveNodes[startNode].I.end();itInt++){

			if(aliveNodes[*itInt].isPresentInCustomerTree(endNode)){	//end node is present in immediate customer *itInt's customer tree

				if(flowIndex[*itInt][endNode]!=-1 && activeFlowIndicator[flowIndex[*itInt][endNode]]==1 && aliveNodes[*itInt].isImmediateCustomer(endNode)){

					//*itInt has endNode as its direct customer
					mergeListsIntoOneScale(routingMatrixScale[designatedColumn],routingMatrixScale[flowIndex[startNode][*itInt]],routingMatrixScale[flowIndex[*itInt][endNode]]);
					activeFlowIndicator[designatedColumn]=1;
					flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode];
					flowDirectionFrom[designatedColumn]=startNode;

					//asymmetric route establishment
					establishFlowPeeringScaleAsym(endNode,startNode,aliveNodes[endNode].Q);

					return true;

				}//end if not direct customer of *itInt

				else{	//*itInt does not have direct path to endNode

					mergeTwoListsScale(missingFlow,routingMatrixScale[flowIndex[startNode][*itInt]]);

					if(findFlowPeeringScale(*itInt,endNode,missingFlow,false)){	//false flag set since request being made by provider

						mergeTwoListsScale(routingMatrixScale[designatedColumn],missingFlow);
						activeFlowIndicator[designatedColumn]=1;
						flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode];
						flowDirectionFrom[designatedColumn]=startNode;
						missingFlow.clear();

						//asymmetric route establishment
						establishFlowPeeringScaleAsym(endNode,startNode,aliveNodes[endNode].Q);

						return true;

					}

					else{

						netDisconnected=true;
						missingFlow.clear();
						string str("ERROR!! Flow could not be established in establishFlow for node in PeeringTree");
						endSimulation(str);
						return false;
					}

				}

			}//end if

		}//end for

		//Control should not come here
		string str("CONTROL REACHES WRONG POINT IN FINDFLOW FUNCTION");
		endSimulation(str);

	}//end if present in customer tree

	else if(presentInPeerTree){	//if endNode is present in the customer tree of peer

		if(flowIndex[intermediaryPeer][endNode]!=-1 && activeFlowIndicator[flowIndex[intermediaryPeer][endNode]]==1 && aliveNodes[intermediaryPeer].isImmediateCustomer(endNode)){

			//peer has endNode as its direct customer
			mergeListsIntoOneScale(routingMatrixScale[designatedColumn],routingMatrixScale[flowIndex[startNode][intermediaryPeer]],routingMatrixScale[flowIndex[intermediaryPeer][endNode]]);
			activeFlowIndicator[designatedColumn]=1;
			flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode];
			flowDirectionFrom[designatedColumn]=startNode;

			//asymmetric routing
			establishFlowPeeringScaleAsym(endNode,startNode,aliveNodes[endNode].Q);

			return true;
		}

		else{	//peer does not have endNode as its direct customer

			if(findFlowPeeringScale(intermediaryPeer,endNode,missingFlow,false)){	//false flag being set since request being made by peer

				mergeListsIntoOneScale(routingMatrixScale[designatedColumn],routingMatrixScale[flowIndex[startNode][intermediaryPeer]],missingFlow);
				activeFlowIndicator[designatedColumn]=1;
				flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode];
				flowDirectionFrom[designatedColumn]=startNode;
				missingFlow.clear();

				//asymmetric routing
				establishFlowPeeringScaleAsym(endNode,startNode,aliveNodes[endNode].Q);

				return true;

			}

			else{
				netDisconnected=true;
				missingFlow.clear();
				string str("ERROR!! Flow could not be established in establishFlow for node in PeeringTree");
				endSimulation(str);
				return false;
			}

		}

	}//end if

	else{	//endNode is neither in the customer tree nor in the peer tree. Ask provider

		if(flowIndex[qNode][endNode]!=-1 && activeFlowIndicator[flowIndex[qNode][endNode]]==1 && (aliveNodes[qNode].isImmediateCustomer(endNode) || aliveNodes[qNode].isPeer(endNode) || aliveNodes[qNode].Q==endNode)){

			//endNode is a direct customer of qNode or peer of qNode or provider of qNode

			mergeListsIntoOneScale(routingMatrixScale[designatedColumn],routingMatrixScale[flowIndex[startNode][qNode]],routingMatrixScale[flowIndex[qNode][endNode]]);
			activeFlowIndicator[designatedColumn]=1;
			flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode];
			flowDirectionFrom[designatedColumn]=startNode;

			//asymmetric routing
			establishFlowPeeringScaleAsym(endNode,startNode,aliveNodes[endNode].Q);

			return true;
		}

		else{	//endNode is not the direct customer of qNode

			if(findFlowPeeringScale(qNode,endNode,missingFlow,true)){	//flag set to true since request being made by customer

				mergeListsIntoOneScale(routingMatrixScale[designatedColumn],routingMatrixScale[flowIndex[startNode][qNode]],missingFlow);
				activeFlowIndicator[designatedColumn]=1;
				flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode];
				flowDirectionFrom[designatedColumn]=startNode;
				missingFlow.clear();

				//asymmetric routing
				establishFlowPeeringScaleAsym(endNode,startNode,aliveNodes[endNode].Q);

				return true;

			}

			else{
				netDisconnected=true;
				missingFlow.clear();
				cout<<"Flow could not be established. Error!!"<<endl;
				string str("ERROR!! Flow could not be established in establishFlow");
				endSimulation(str);
				return false;
			}

		}

	}//end else

	return false;

}

bool establishFlowPeeringScaleAsym(int startNode, int endNode, int qNode){

	if(startNode==-1 || endNode==-1){

		if(startNode==-1){
			string str("ERROR!! ONE OF THE NODES (startNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}
		else{
			string str("ERROR!! ONE OF THE NODES (endNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}
	}

	//Step 1 Find designated column
	//Step 2 Go over peers to see if the endNode is in the customer tree of peer
	//Step 3 Go to parent

	int designatedColumn;
	bool columnFound=false;
	list<int>::iterator itK;
	bool presentInPeerTree=false;
	int intermediaryPeer=-1;
	list<int> missingFlow;
	list<int>::iterator itInt;

	designatedColumn=flowIndex[startNode][endNode];

	//Step 2 Go over all peers in order
	if(!aliveNodes[startNode].K.empty()){
		for(itK=aliveNodes[startNode].K.begin();itK!=aliveNodes[startNode].K.end();itK++){
			if(aliveNodes[*itK].isPresentInCustomerTree(endNode)){
				presentInPeerTree=true;
				intermediaryPeer=*itK;
				break;
			}
		}
	}

	if(aliveNodes[startNode].isPresentInCustomerTree(endNode)){	//endNode is present in customer tree of startNode

		for(itInt=aliveNodes[startNode].I.begin();itInt!=aliveNodes[startNode].I.end();itInt++){

			if(aliveNodes[*itInt].isPresentInCustomerTree(endNode)){	//end node is present in immediate customer *itInt's customer tree

				if(flowIndex[*itInt][endNode]!=-1 && activeFlowIndicator[flowIndex[*itInt][endNode]]==1 && aliveNodes[*itInt].isImmediateCustomer(endNode)){

					//*itInt has endNode as its direct customer
					mergeListsIntoOneScale(routingMatrixScaleAsym[designatedColumn],routingMatrixScaleAsym[flowIndex[startNode][*itInt]],routingMatrixScaleAsym[flowIndex[*itInt][endNode]]);
					activeFlowIndicator[designatedColumn]=1;
					flowValueVectorAsym[designatedColumn]=trafficMatrix[startNode][endNode];
					flowDirectionFromAsym[designatedColumn]=startNode;

					return true;

				}//end if not direct customer of *itInt

				else{	//*itInt does not have direct path to endNode

					mergeTwoListsScale(missingFlow,routingMatrixScaleAsym[flowIndex[startNode][*itInt]]);

					if(findFlowPeeringScaleAsym(*itInt,endNode,missingFlow,false)){	//false flag set since request being made by provider

						mergeTwoListsScale(routingMatrixScaleAsym[designatedColumn],missingFlow);
						activeFlowIndicator[designatedColumn]=1;
						flowValueVectorAsym[designatedColumn]=trafficMatrix[startNode][endNode];
						flowDirectionFromAsym[designatedColumn]=startNode;

						missingFlow.clear();

						return true;

					}

					else{

						netDisconnected=true;
						missingFlow.clear();
						string str("ERROR!! Flow could not be established in establishFlow for node in PeeringTree");
						endSimulation(str);
						return false;
					}

				}

			}//end if

		}//end for

		//Control should not come here
		string str("CONTROL REACHES WRONG POINT IN FINDFLOW FUNCTION");
		endSimulation(str);

	}//end if present in customer tree

	else if(presentInPeerTree){	//if endNode is present in the customer tree of peer

		if(flowIndex[intermediaryPeer][endNode]!=-1 && activeFlowIndicator[flowIndex[intermediaryPeer][endNode]]==1 && aliveNodes[intermediaryPeer].isImmediateCustomer(endNode)){

			//peer has endNode as its direct customer
			mergeListsIntoOneScale(routingMatrixScaleAsym[designatedColumn],routingMatrixScaleAsym[flowIndex[startNode][intermediaryPeer]],routingMatrixScaleAsym[flowIndex[intermediaryPeer][endNode]]);
			activeFlowIndicator[designatedColumn]=1;
			flowValueVectorAsym[designatedColumn]=trafficMatrix[startNode][endNode];
			flowDirectionFromAsym[designatedColumn]=startNode;

			return true;
		}

		else{	//peer does not have endNode as its direct customer

			if(findFlowPeeringScaleAsym(intermediaryPeer,endNode,missingFlow,false)){	//false flag being set since request being made by peer

				mergeListsIntoOneScale(routingMatrixScaleAsym[designatedColumn],routingMatrixScaleAsym[flowIndex[startNode][intermediaryPeer]],missingFlow);
				activeFlowIndicator[designatedColumn]=1;
				flowValueVectorAsym[designatedColumn]=trafficMatrix[startNode][endNode];
				flowDirectionFromAsym[designatedColumn]=startNode;
				missingFlow.clear();

				return true;

			}

			else{
				netDisconnected=true;
				missingFlow.clear();
				string str("ERROR!! Flow could not be established in establishFlow for node in PeeringTree");
				endSimulation(str);
				return false;
			}

		}

	}//end if

	else{	//endNode is neither in the customer tree nor in the peer tree. Ask provider

		if(flowIndex[qNode][endNode]!=-1 && activeFlowIndicator[flowIndex[qNode][endNode]]==1 && (aliveNodes[qNode].isImmediateCustomer(endNode) || aliveNodes[qNode].isPeer(endNode) || aliveNodes[qNode].Q==endNode)){

			//endNode is a direct customer of qNode
			mergeListsIntoOneScale(routingMatrixScaleAsym[designatedColumn],routingMatrixScaleAsym[flowIndex[startNode][qNode]],routingMatrixScaleAsym[flowIndex[qNode][endNode]]);
			activeFlowIndicator[designatedColumn]=1;
			flowValueVectorAsym[designatedColumn]=trafficMatrix[startNode][endNode];
			flowDirectionFromAsym[designatedColumn]=startNode;

			return true;
		}

		else{	//endNode is not the direct customer of qNode

			if(findFlowPeeringScaleAsym(qNode,endNode,missingFlow,true)){	//flag set to true since request being made by customer

				mergeListsIntoOneScale(routingMatrixScaleAsym[designatedColumn],routingMatrixScaleAsym[flowIndex[startNode][qNode]],missingFlow);
				activeFlowIndicator[designatedColumn]=1;
				flowValueVectorAsym[designatedColumn]=trafficMatrix[startNode][endNode];
				flowDirectionFromAsym[designatedColumn]=startNode;
				missingFlow.clear();

				return true;

			}

			else{
				netDisconnected=true;
				missingFlow.clear();
				cout<<"Flow could not be established. Error!!"<<endl;
				string str("ERROR!! Flow could not be established in establishFlow");
				endSimulation(str);
				return false;
			}

		}

	}//end else

	return false;

}

bool findFlowPeeringScaleAsym(int startNode, int endNode, list<int>& missingFlow, bool flag){

	list<int>::iterator itInt;
	int peer;

	//direct link from startNode to endNode exists
	if((flowIndex[startNode][endNode]!=-1 && activeFlowIndicator[flowIndex[startNode][endNode]]==1 && ((flag==false && aliveNodes[startNode].isImmediateCustomer(endNode)) || (flag==true && (aliveNodes[startNode].isImmediateCustomer(endNode) || aliveNodes[startNode].isPeer(endNode) || aliveNodes[startNode].Q==endNode))))){

		mergeTwoListsScale(missingFlow,routingMatrixScaleAsym[flowIndex[startNode][endNode]]);

		return true;
	}

	else{	//direct link from startNode to endNode does not exist

		if(aliveNodes[startNode].isPresentInCustomerTree(endNode)){	//endNode is present in customer tree of startNode

			for(itInt=aliveNodes[startNode].I.begin();itInt!=aliveNodes[startNode].I.end();itInt++){

				if(aliveNodes[*itInt].isPresentInCustomerTree(endNode)){	//end node is present in immediate customer *itInt's customer tree

					mergeTwoListsScale(missingFlow,routingMatrixScaleAsym[flowIndex[startNode][*itInt]]);

					if(flowIndex[*itInt][endNode]!=-1 && activeFlowIndicator[flowIndex[*itInt][endNode]]==1 && aliveNodes[*itInt].isImmediateCustomer(endNode)){

						mergeTwoListsScale(missingFlow,routingMatrixScaleAsym[flowIndex[*itInt][endNode]]);
						return true;

					}//end if not direct customer of *itInt

					else{	//*itInt does not have direct path to endNode

						return findFlowPeeringScaleAsym(*itInt,endNode,missingFlow,false);	//flag set to false since customer being asked to find path

					}

				}//end if

			}//end for

			//Control should not come here
			string str("CONTROL REACHES WRONG POINT IN FINDFLOW FUNCTION");
			endSimulation(str);

		}//end if

		else if(flag==true && (peer=aliveNodes[startNode].isPresentInCustomerTreeOfPeer(endNode))!=-1){	//endNode is present in customer tree of peer

			mergeTwoListsScale(missingFlow,routingMatrixScaleAsym[flowIndex[startNode][peer]]);

			if((flowIndex[peer][endNode]!=-1 && activeFlowIndicator[flowIndex[peer][endNode]]==1) && aliveNodes[peer].isImmediateCustomer(endNode)){

				mergeTwoListsScale(missingFlow,routingMatrixScaleAsym[flowIndex[peer][endNode]]);

				return true;

			}//end if

			else
				return findFlowPeeringScaleAsym(peer,endNode,missingFlow,false);

		}

		else{	//endNode is not present in customer tree of startNode or peers' customer tree

			if(aliveNodes[startNode].Q!=-1 && flag==true){

				mergeTwoListsScale(missingFlow,routingMatrixScaleAsym[flowIndex[startNode][aliveNodes[startNode].Q]]);

				return findFlowPeeringScaleAsym(aliveNodes[startNode].Q,endNode,missingFlow,true);
			}

			else{
				cout<<"ERROR!! Flow could not be established between "<<startNode<<" and "<<endNode<<endl;
				string str("FIND FLOW ERROR!! COULD NOT ESTABLISH FLOW");
				endSimulation(str);

			}

		}//end else

	}

}


bool establishFlowPeering(int startNode, int endNode, int qNode){

	if(startNode==-1 || endNode==-1){

		if(startNode==-1){
			string str("ERROR!! ONE OF THE NODES (startNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}
		else{
			string str("ERROR!! ONE OF THE NODES (endNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}
	}

	//Step 1 Find designated column
	//Step 2 Go over peers to see if the endNode is in the customer tree of peer
	//Step 3 Go to parent

	int designatedColumn;
	bool columnFound=false;
	list<int>::iterator itK;
	bool presentInPeerTree=false;
	int intermediaryPeer=-1;

	if(flowIndex[startNode][endNode]==-1){
		for(int j=0;j<maxFlows;j++)
			if(aliveFlowIndicator[j]==0){
				aliveFlowIndicator[j]=1;
				activeFlowIndicator[j]=1;
				designatedColumn=j;
				columnFound=true;
				break;
			}

		if(columnFound){
			flowIndex[startNode][endNode]=designatedColumn;
			flowIndex[endNode][startNode]=designatedColumn;
		}

		else{
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}

	}

	//Step 2 Go over all peers in order
	if(!aliveNodes[startNode].K.empty()){
		for(itK=aliveNodes[startNode].K.begin();itK!=aliveNodes[startNode].K.end();itK++){
			if(aliveNodes[*itK].isPresentInCustomerTree(endNode)){
				presentInPeerTree=true;
				intermediaryPeer=*itK;
				break;
			}
		}
	}

	if(presentInPeerTree){

		if(flowIndex[intermediaryPeer][endNode]!=-1 && activeFlowIndicator[flowIndex[intermediaryPeer][endNode]]==1){

			designatedColumn=flowIndex[startNode][endNode];
			activeFlowIndicator[designatedColumn]=1;

			for(int i=0;i<maxLinks;i++)
				routingMatrix[i][designatedColumn]=routingMatrix[i][flowIndex[startNode][intermediaryPeer]] | routingMatrix[i][flowIndex[intermediaryPeer][endNode]];

			flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode]+trafficMatrix[endNode][startNode];
			return true;
		}

		else{

			bool* missingFlow=new bool[maxLinks];

			for(int i=0;i<maxLinks;i++)
				missingFlow[i]=0;

			designatedColumn=flowIndex[startNode][endNode];

			if(findFlowPeering(intermediaryPeer,endNode,missingFlow)){

				for(int i=0;i<maxLinks;i++)
					routingMatrix[i][designatedColumn]=routingMatrix[i][flowIndex[startNode][intermediaryPeer]] | missingFlow[i];

				activeFlowIndicator[designatedColumn]=1;
				flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode]+trafficMatrix[endNode][startNode];

				delete []missingFlow;
				return true;

			}

			else{
				netDisconnected=true;
				delete []missingFlow;
				string str("ERROR!! Flow could not be established in establishFlow for node in PeeringTree");
				endSimulation(str);
				return false;
			}

		}

	}//end if

	else{

		if(flowIndex[qNode][endNode]!=-1 && activeFlowIndicator[flowIndex[qNode][endNode]]==1){

			designatedColumn=flowIndex[startNode][endNode];

			for(int i=0;i<maxLinks;i++)
				routingMatrix[i][designatedColumn]=routingMatrix[i][flowIndex[startNode][qNode]] | routingMatrix[i][flowIndex[qNode][endNode]];

			activeFlowIndicator[designatedColumn]=1;
			flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode]+trafficMatrix[endNode][startNode];

			return true;
		}

		else{

			bool* missingFlow=new bool[maxLinks];

			for(int i=0;i<maxLinks;i++)
				missingFlow[i]=0;

			designatedColumn=flowIndex[startNode][endNode];

			if(findFlowPeering(qNode,endNode,missingFlow)){


				for(int i=0;i<maxLinks;i++)
					routingMatrix[i][designatedColumn]=routingMatrix[i][flowIndex[startNode][qNode]] | missingFlow[i];

				activeFlowIndicator[designatedColumn]=1;
				flowValueVector[designatedColumn]=trafficMatrix[startNode][endNode]+trafficMatrix[endNode][startNode];

				delete []missingFlow;
				return true;

			}

			else{
				netDisconnected=true;
				delete []missingFlow;
				cout<<"Flow could not be established. Error!!"<<endl;
				string str("ERROR!! Flow could not be established in establishFlow");
				endSimulation(str);
				return false;
			}

		}

	}//end else

}//end function

bool findFlowPeeringScale(int startNode, int endNode, list<int>& missingFlow, bool flag){

	list<int>::iterator itInt;
	int peer;

	//direct link from startNode to endNode exists
	if((flowIndex[startNode][endNode]!=-1 && activeFlowIndicator[flowIndex[startNode][endNode]]==1 && ((flag==false && aliveNodes[startNode].isImmediateCustomer(endNode)) || (flag==true && (aliveNodes[startNode].isImmediateCustomer(endNode) || aliveNodes[startNode].isPeer(endNode) || aliveNodes[startNode].Q==endNode))))){

		mergeTwoListsScale(missingFlow,routingMatrixScale[flowIndex[startNode][endNode]]);

		return true;
	}

	else{	//direct link from startNode to endNode does not exist

		if(aliveNodes[startNode].isPresentInCustomerTree(endNode)){	//endNode is present in customer tree of startNode

			for(itInt=aliveNodes[startNode].I.begin();itInt!=aliveNodes[startNode].I.end();itInt++){

				if(aliveNodes[*itInt].isPresentInCustomerTree(endNode)){	//end node is present in immediate customer *itInt's customer tree

					mergeTwoListsScale(missingFlow,routingMatrixScale[flowIndex[startNode][*itInt]]);

					if(flowIndex[*itInt][endNode]!=-1 && activeFlowIndicator[flowIndex[*itInt][endNode]]==1 && aliveNodes[*itInt].isImmediateCustomer(endNode)){

						mergeTwoListsScale(missingFlow,routingMatrixScale[flowIndex[*itInt][endNode]]);
						return true;

					}//end if not direct customer of *itInt

					else{	//*itInt does not have direct path to endNode

						return findFlowPeeringScale(*itInt,endNode,missingFlow,false);	//flag set to false since customer being asked to find path

					}

				}//end if

			}//end for

			//Control should not come here
			string str("CONTROL REACHES WRONG POINT IN FINDFLOW FUNCTION");
			endSimulation(str);

		}//end if

		else if(flag==true && (peer=aliveNodes[startNode].isPresentInCustomerTreeOfPeer(endNode))!=-1){	//endNode is present in customer tree of peer

			mergeTwoListsScale(missingFlow,routingMatrixScale[flowIndex[startNode][peer]]);

			if((flowIndex[peer][endNode]!=-1 && activeFlowIndicator[flowIndex[peer][endNode]]==1) && aliveNodes[peer].isImmediateCustomer(endNode)){

				mergeTwoListsScale(missingFlow,routingMatrixScale[flowIndex[peer][endNode]]);

				return true;

			}//end if

			else
				return findFlowPeeringScale(peer,endNode,missingFlow,false);

		}

		else{	//endNode is not present in customer tree of startNode or peers' customer tree

			if(aliveNodes[startNode].Q!=-1 && flag==true){

				mergeTwoListsScale(missingFlow,routingMatrixScale[flowIndex[startNode][aliveNodes[startNode].Q]]);

				return findFlowPeeringScale(aliveNodes[startNode].Q,endNode,missingFlow,true);
			}

			else{
				cout<<"ERROR!! Flow could not be established between "<<startNode<<" and "<<endNode<<endl;
				string str("FIND FLOW ERROR!! COULD NOT ESTABLISH FLOW");
				endSimulation(str);

			}

		}//end else

	}

}

bool findFlowPeering(int startNode, int endNode, bool* &missingFlow){

	list<Node>::iterator itS;
	list<Node>::iterator itE;
	list<int>::iterator itInt;
	list<Node>::iterator it1;
	bool found=false;
	int peer=-1;

#if 0
	cout<<"FindFlow: "<<startNode<<" "<<endNode<<endl;
#endif

	if(flowIndex[startNode][endNode]!=-1 && activeFlowIndicator[flowIndex[startNode][endNode]]==1){

		for(int i=0;i<maxLinks;i++)
			missingFlow[i]=missingFlow[i] | routingMatrix[i][flowIndex[startNode][endNode]];

		return true;
	}

	else{

		if(aliveNodes[startNode].isPresentInCustomerTree(endNode)){	//endNode is present in customer tree of startNode

			for(itInt=aliveNodes[startNode].I.begin();itInt!=aliveNodes[startNode].I.end();itInt++){

				if(aliveNodes[*itInt].isPresentInCustomerTree(endNode)){

					for(int i=0;i<maxLinks;i++)
						missingFlow[i]=missingFlow[i] | routingMatrix[i][flowIndex[startNode][*itInt]];

					if(flowIndex[*itInt][endNode]!=-1){

						for(int i=0;i<maxLinks;i++)
							missingFlow[i]=missingFlow[i] | routingMatrix[i][flowIndex[*itInt][endNode]];

						return true;

					}//end if

					else
						return findFlowPeering(*itInt,endNode,missingFlow);

				}//end if

			}//end for

			//Control should not come here
			string str("CONTROL REACHES WRONG POINT IN FINDFLOW FUNCTION");
			endSimulation(str);

		}//end if

		else if((peer=aliveNodes[startNode].isPresentInCustomerTreeOfPeer(endNode))!=-1){	//endNode is present in customer tree of peer

			for(int i=0;i<maxLinks;i++)
				missingFlow[i]=missingFlow[i] | routingMatrix[i][flowIndex[startNode][peer]];

			if(flowIndex[peer][endNode]!=-1 && activeFlowIndicator[flowIndex[peer][endNode]]==1){

				for(int i=0;i<maxLinks;i++)
					missingFlow[i]=missingFlow[i] | routingMatrix[i][flowIndex[peer][endNode]];

				return true;

			}//end if

			else
				return findFlowPeering(peer,endNode,missingFlow);

		}

		else{	//endNode is not present in customer tree of startNode

			if(aliveNodes[startNode].Q!=-1){

				/*//Orig Code before maxLinks
				for(int i=0;i<maxNodes;i++)
					missingFlow[i]=missingFlow[i] | routingMatrix[i][flowIndex[startNode][aliveNodes[startNode].Q]];
				*/

				for(int i=0;i<maxLinks;i++)
					missingFlow[i]=missingFlow[i] | routingMatrix[i][flowIndex[startNode][aliveNodes[startNode].Q]];

				return findFlowPeering(aliveNodes[startNode].Q,endNode,missingFlow);
			}

			else{
				cout<<"ERROR!! Flow could not be established between "<<startNode<<" and "<<endNode<<endl;
				string str("FIND FLOW ERROR!! COULD NOT ESTABLISH FLOW");
				endSimulation(str);

			}

		}//end else
	}

}

void endLinkScale(int pNode, int qNode){

	//routingMatrixScale[linkIndex[pNode][qNode].index].clear();

	routingMatrixScale[flowIndex[pNode][qNode]].remove(linkIndex[pNode][qNode].index);

	routingMatrixScaleAsym[flowIndex[pNode][qNode]].remove(linkIndex[pNode][qNode].index);

	aliveLinkIndicator[linkIndex[pNode][qNode].index]=0;

	linkIndex[pNode][qNode].index=-1;
	linkIndex[pNode][qNode].provider=-1;
	linkIndex[qNode][pNode].index=-1;
	linkIndex[qNode][pNode].provider=-1;

}



void endLink(int pNode, int qNode){

	routingMatrix[linkIndex[pNode][qNode].index][flowIndex[pNode][qNode]]=0;

	aliveLinkIndicator[linkIndex[pNode][qNode].index]=0;

	for(int i=0;i<maxFlows;i++)
		routingMatrix[linkIndex[pNode][qNode].index][i]=0;

	linkIndex[pNode][qNode].index=-1;
	linkIndex[pNode][qNode].provider=-1;
	linkIndex[qNode][pNode].index=-1;
	linkIndex[qNode][pNode].provider=-1;


}

void endFlowScale(int sNode, int eNode){


	routingMatrixScale[flowIndex[sNode][eNode]].clear();
	activeFlowIndicator[flowIndex[sNode][eNode]]=0;
	flowDirectionFrom[flowIndex[sNode][eNode]]=-1;
	flowDirectionFromAsym[flowIndex[sNode][eNode]]=-1;

	if(flowIndex[sNode][eNode]==-1)
		aliveFlowIndicator[flowIndex[sNode][eNode]]=0;

	//********* Additions for asymmetric routing***********
	routingMatrixScaleAsym[flowIndex[sNode][eNode]].clear();


}

void endFlow(int sNode, int eNode){

	double flowThreshold=0;

	if(flowIndex[sNode][eNode]!=-1){

		if((trafficMatrix[sNode][eNode]+trafficMatrix[eNode][sNode])>flowThreshold){
			//only nullify the flow

			for(int i=0;i<maxLinks;i++)
				routingMatrix[i][flowIndex[sNode][eNode]]=0;

			activeFlowIndicator[flowIndex[sNode][eNode]]=0;

		}//end if

		else{

			for(int i=0;i<maxLinks;i++)
				routingMatrix[i][flowIndex[sNode][eNode]]=0;

			aliveFlowIndicator[flowIndex[sNode][eNode]]=0;
			activeFlowIndicator[flowIndex[sNode][eNode]]=0;

			flowValueVector[flowIndex[sNode][eNode]]=0;

			flowIndex[sNode][eNode]=flowIndex[eNode][sNode]=-1;

		}//end else

	}//end if
}

void chooseInnovator(int& innovatorId,const int& innovatorClass, const int & innovatedStrategy){

	int tmp1=0;
	int tmp2=0;
	list<int> potentialInnovators;
	list<int>::iterator itInt;

	cout<<"Innovator class: "<<innovatorClass<<" InnovatedStrategy: "<<innovatedStrategy<<endl;

	//randomly choose a network in designated class as innovator
	for(int i=0;i<activeNodes;i++){

		if(aliveNodes[i].peeringStrategyNumber!=innovatedStrategy){

			if(innovatorClass==3){	//any non-T1 provider
				if(aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==0 && aliveNodes[i].peeringStrategyNumber!=1)
						potentialInnovators.push_back(i);
			}

			if(innovatorClass==1 || innovatorClass==2)	//content providers or content consumers
				if(aliveNodes[i].category[innovatorClass]!=0)
					potentialInnovators.push_back(i);

			if(innovatorClass==31)	//global provider
				if(aliveNodes[i].category[3]==1)
					potentialInnovators.push_back(i);

			if(innovatorClass==32)	//regional provider
				if(aliveNodes[i].category[3]==2)
					potentialInnovators.push_back(i);

			if(innovatorClass==33)	//local provider
				if(aliveNodes[i].category[3]==3)
					potentialInnovators.push_back(i);

			if(innovatorClass==4)	//T1 provider
				if(aliveNodes[i].category[4]==2)
					potentialInnovators.push_back(i);

		}//end if

	}//end for

	if(!potentialInnovators.empty()){
		tmp1=rand()%potentialInnovators.size();
	}

	for(itInt=potentialInnovators.begin(),tmp2=0;itInt!=potentialInnovators.end();itInt++,tmp2++)
		if(tmp2==tmp1){
			innovatorId=*itInt;
			break;
		}


}

void updateNetworkCategories(){

	npPair tmpNP;
	list<npPair> npList;
	list<npPair>::iterator itNP;
	double counter=0;
	double totalGeneratedTraffic=0;
	double totalConsumedTraffic=0;
	static bool firstTime=true;

	if(firstTime==true){

		//Content Generators
		for(int i=0;i<activeNodes;i++){
			tmpNP.nId=i;
			tmpNP.trafficVolume=aliveNodes[i].trafficGenerated;
			totalGeneratedTraffic+=tmpNP.trafficVolume;
			npList.push_back(tmpNP);
		}
		npList.sort(sortVolume);

		for(itNP=npList.begin();itNP!=npList.end();itNP++){

			counter+=(*itNP).trafficVolume;
			if((counter/totalGeneratedTraffic)<0.40){
				aliveNodes[(*itNP).nId].category[1]=0;
			}

			else
				break;

		}

		//Content Consumers
		npList.clear();
		counter=0;
		for(int i=0;i<activeNodes;i++){
			tmpNP.nId=i;
			tmpNP.trafficVolume=aliveNodes[i].trafficConsumed;
			totalConsumedTraffic+=tmpNP.trafficVolume;
			npList.push_back(tmpNP);
		}
		npList.sort(sortVolume);

		for(itNP=npList.begin();itNP!=npList.end();itNP++){

			counter+=(*itNP).trafficVolume;
			if((counter/totalConsumedTraffic)<0.50){
				aliveNodes[(*itNP).nId].category[2]=0;
			}

			else
				break;

		}

		//price
		npList.clear();
		counter=0;
		for(int i=0;i<activeNodes;i++){
			tmpNP.nId=i;
			tmpNP.price=aliveNodes[i].price;
			npList.push_back(tmpNP);
		}
		npList.sort(comparePrice);

		for(itNP=npList.begin();itNP!=npList.end();itNP++,counter++){

			if((counter/activeNodes)<0.5)
				aliveNodes[(*itNP).nId].category[5]=1;

			else
				aliveNodes[(*itNP).nId].category[5]=0;

		}

		firstTime=false;
	}//end if first time

	for(int i=0;i<activeNodes;i++)
		aliveNodes[i].updateCategories();


	//update Transit traffic cases
	npList.clear();
	counter=0;
	for(int i=0;i<activeNodes;i++){

		if(!aliveNodes[i].I.empty()){
			tmpNP.nId=i;
			tmpNP.trafficVolume=aliveNodes[i].Vt;
			npList.push_back(tmpNP);
		}

		else
			aliveNodes[i].category[6]=2;

	}
	npList.sort(sortVolume);
	for(itNP=npList.begin();itNP!=npList.end();itNP++,counter++){

		if((counter/npList.size())<0.5)
			aliveNodes[(*itNP).nId].category[6]=1;

		else
			aliveNodes[(*itNP).nId].category[6]=0;

	}

}


bool isPresentInList(list<int> &checkList,int toCheck){

	list<int>::iterator it;
	for(it=checkList.begin();it!=checkList.end();it++)
		if(*it==toCheck)
			return true;

	return false;

}

void endSimulation(string str){
	cout<<"ERROR IN SIMULATION!!!"<<endl;
	cout<<str<<endl;

	logFile<<"ERROR IN SIMULATION!!!"<<endl;
	logFile<<str<<endl;

	char errorFileName[50];
	ofstream errorFile;
	sprintf(errorFileName,"errorRun.txt");
	errorFile.open(errorFileName,ios::app);
	errorFile<<"Seed used: "<<mySeed<<" "<<str<<endl;

	/**
	 * DO CLEANING FOR SIMULATION
	 */

	exit(-1);
}

void antiCoalitionMetric(int numSimulations){

	if(numSimulations==0)
		return;

	ofstream antiCoalitionFile1;
	antiCoalitionFile1.open("antiCoalition1.txt",ios::out|ios::app);

	ofstream antiCoalitionFile2;
	antiCoalitionFile2.open("antiCoalition2.txt",ios::out|ios::app);

	double rai=0;
	double raj=0;
	double rpi=0;
	double rpj=0;
	list<int>::iterator it1;
	list<int>::iterator it2;
	list<double>::iterator itD;
	list<double> ratios1;
	list<double> ratios2;
	double temp;

	for(int i=0;i<activeNodes-1;i++)
		for(int j=i+1;j<activeNodes;j++){
			if(!aliveNodes[i].I.empty() && !aliveNodes[j].I.empty() && aliveNodes[i].isPeer(j)){

				rai=rpi=raj=rpj=0;

				for(it1=aliveNodes[i].overLap.begin();it1!=aliveNodes[i].overLap.end();it1++){
					if(aliveNodes[j].isImmediateCustomer(*it1)){
						rpi++;
						if(aliveNodes[i].isPeer(*it1))
							rai++;
					}
				}

				for(it1=aliveNodes[j].overLap.begin();it1!=aliveNodes[j].overLap.end();it1++){
					if(aliveNodes[i].isImmediateCustomer(*it1)){
						rpj++;
						if(aliveNodes[j].isPeer(*it1))
							raj++;
					}
				}

				if((rpi+rpj)>0){

					ratios1.push_back((rai+raj)/(rpi+rpj));


				}

			}
		}

	ratios1.sort();
	double x, xPrev;
	double xCounter, prevCounter;

	for(itD=ratios1.begin();itD!=ratios1.end();itD++){

		x=*itD;

		if(itD==ratios1.begin()){

			xPrev=*itD;
			prevCounter=0;
			xCounter=1;
		}

		else{

			if(x==xPrev){
				xCounter++;
			}

			else{
				xCounter+=prevCounter;

				if(numSimulations==1){
					//antiCoalitionFile1<<xPrev<<"\t"<<xCounter/ratios1.size()<<endl;
					antiCoalitionFile1<<xCounter/ratios1.size()<<"\t"<<xPrev<<endl;
				}
				else{
					//antiCoalitionFile2<<xPrev<<"\t"<<xCounter/ratios1.size()<<endl;
					antiCoalitionFile2<<xCounter/ratios1.size()<<"\t"<<xPrev<<endl;

				}

				xPrev=*itD;
				prevCounter=xCounter;
				xCounter=1;

			}

		}

	}

	xCounter+=prevCounter;
	if(numSimulations==1){
		//antiCoalitionFile1<<xPrev<<"\t"<<xCounter/ratios1.size()<<endl;
		antiCoalitionFile1<<xCounter/ratios1.size()<<"\t"<<xPrev<<endl;
	}
	else{
		//antiCoalitionFile2<<xPrev<<"\t"<<xCounter/ratios1.size()<<endl;
		antiCoalitionFile2<<xCounter/ratios1.size()<<"\t"<<xPrev<<endl;

	}

	/*
	ratios1.sort(sortReverse);
	ratios2.push_back(ratios1.front());
	temp=ratios1.front();

	for(itD=ratios1.begin();itD!=ratios1.end();itD++){

		if(itD!=ratios1.begin()){
			temp+=*itD;
			ratios2.push_back(temp);
		}

	}

	temp=ratios2.back();
	cout<<"temp is "<<temp<<endl;

	for(itD=ratios2.begin();itD!=ratios2.end();itD++){

			*itD=*itD/temp;
			if(numSimulations==1){
				antiCoalitionFile1<<*itD<<":";
			}
			else
				antiCoalitionFile2<<*itD<<":";

	}
	*/

}

void printLog(int numSimulations){

	ofstream printLogFile;
	char printLogFileName[50];
	sprintf(printLogFileName,"printLog_%d.txt",playOrderSeed);
	printLogFile.open(printLogFileName,ios::out | ios::app);

	ofstream printProviderFile;
	char printProviderFileName[50];
	sprintf(printProviderFileName,"printProvider_%d.txt",playOrderSeed);
	printProviderFile.open(printProviderFileName,ios::out | ios::app);

	int cheapestInRegions=0;
	Coordinate presence;
	list<Coordinate>::iterator itC;
	list<int>::iterator itInt;
	list<int>::iterator itInt2;
	int lowestPriceNode;
	double lowestPrice=100000;

	int numCPCustomers=0;
	int numCCCustomers=0;
	int numProviderPeers=0;
	int numCPPeers=0;
	int numCCPeers=0;
	int numStubPeers=0;
	int numPotentialPeers=0;
	int numPotentialProviderPeers=0;
	int numPotentialCPCCPeers=0;
	int numPotentialStubPeers=0;
	int peerCustomerProductAgainst=0;
	int peerCustomerProduct=0;
	double trafficStolenFrom=0;
	double trafficStolenBy=0;
	double totalUpstreamTraffic=0;
	double totalPeeringTraffic=0;
	double totalPeers=0;
	double totalOpenPeers=0;
	int potentialCustomers=0;

	for(int i=0;i<activeNodes;i++){

		totalUpstreamTraffic=0;
		totalPeeringTraffic=0;
		cheapestInRegions=0;
		numCPCustomers=0;
		numCCCustomers=0;
		numCPPeers=0;
		numCCPeers=0;
		numProviderPeers=0;
		numStubPeers=0;

		numPotentialPeers=0;
		numPotentialProviderPeers=0;
		numPotentialCPCCPeers=0;
		numPotentialStubPeers=0;
		peerCustomerProductAgainst=0;
		peerCustomerProduct=0;

		trafficStolenFrom=0;
		trafficStolenBy=0;
		totalPeers=0;
		totalOpenPeers=0;
		potentialCustomers=0;

		for(itInt=aliveNodes[i].overLap.begin();itInt!=aliveNodes[i].overLap.end();itInt++){

			if(aliveNodes[*itInt].numGPresence<=aliveNodes[i].numGPresence)
				potentialCustomers++;

			if(!aliveNodes[i].isImmediateCustomer(*itInt) && aliveNodes[i].Q!=*itInt){
				numPotentialPeers++;

				if(!aliveNodes[*itInt].I.empty())
					numPotentialProviderPeers++;

				if(aliveNodes[*itInt].isMajorContentNet==true)
					numPotentialCPCCPeers++;

				else{

					if(aliveNodes[*itInt].I.empty())
						numPotentialStubPeers++;

				}

			}
		}

		for(itC=aliveNodes[i].gPresence.begin();itC!=aliveNodes[i].gPresence.end();itC++){

			lowestPrice=100000;

			for(itInt=geography[(*itC).xCoordinate][(*itC).yCoordinate].nodePresent.begin();itInt!=geography[(*itC).xCoordinate][(*itC).yCoordinate].nodePresent.end();itInt++)
				if(aliveNodes[*itInt].numGPresence>1 && aliveNodes[*itInt].priceChart[(*itC).xCoordinate][(*itC).yCoordinate]<lowestPrice){
					lowestPrice=aliveNodes[*itInt].priceChart[(*itC).xCoordinate][(*itC).yCoordinate];
					lowestPriceNode=*itInt;
				}

			if(lowestPriceNode==i)
				cheapestInRegions++;
		}

		for(itInt=aliveNodes[i].I.begin();itInt!=aliveNodes[i].I.end();itInt++){

			if(aliveNodes[*itInt].isCP==true)
				numCPCustomers++;

			if(aliveNodes[*itInt].isCC==true)
				numCCCustomers++;

		}

		for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++){

			if(aliveNodes[*itInt].isCP==true)
				numCPPeers++;

			if(aliveNodes[*itInt].isCC==true)
				numCCPeers++;

			if(!aliveNodes[*itInt].I.empty())
				numProviderPeers++;

			if(aliveNodes[*itInt].I.empty() && aliveNodes[*itInt].isMajorContentNet==false)
				numStubPeers++;

		}

		printLogFile<<numSimulations<<":";
		printLogFile<<i<<":"<<aliveNodes[i].numGPresence<<":"<<cheapestInRegions<<":";
		printLogFile<<aliveNodes[i].trafficGenerated<<":"<<aliveNodes[i].trafficConsumed<<":"<<aliveNodes[i].Vt<<":";
		printLogFile<<aliveNodes[i].isCP<<":"<<aliveNodes[i].isCC<<":";
		printLogFile<<aliveNodes[i].I.size()<<":"<<aliveNodes[i].J.size()<<":";
		printLogFile<<numCPCustomers<<":"<<numCCCustomers<<":";
		printLogFile<<aliveNodes[i].Q<<":";
		printLogFile<<numPotentialPeers<<":"<<numPotentialCPCCPeers<<":"<<numPotentialProviderPeers<<":"<<numPotentialStubPeers<<":";
		printLogFile<<aliveNodes[i].peeringStrategyNumber<<":"<<aliveNodes[i].K.size()<<":";
		printLogFile<<numCPPeers<<":"<<numCCPeers<<":"<<numProviderPeers<<":"<<numStubPeers<<":";
		printLogFile<<aliveNodes[i].providerCost<<":"<<aliveNodes[i].peerCost<<":"<<aliveNodes[i].customerRevenue<<":"<<aliveNodes[i].fitness<<endl;


		if(!aliveNodes[i].I.empty()){

			if(aliveNodes[i].Q!=-1){
				aliveNodes[i].actualTrafficFractions[0]=linkValueVector[linkIndex[i][aliveNodes[i].Q].index]/aliveNodes[i].V;
				totalUpstreamTraffic+=linkValueVector[linkIndex[i][aliveNodes[i].Q].index];
			}
			else
				aliveNodes[i].actualTrafficFractions[0]=0;

			aliveNodes[i].actualTrafficFractions[1]=0;
			for(itInt=aliveNodes[i].I.begin();itInt!=aliveNodes[i].I.end();itInt++)
				aliveNodes[i].actualTrafficFractions[1]+=linkValueVector[linkIndex[i][*itInt].index];
			aliveNodes[i].actualTrafficFractions[1]=aliveNodes[i].actualTrafficFractions[1]/aliveNodes[i].V;

			aliveNodes[i].actualTrafficFractions[2]=0;
			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++)
				aliveNodes[i].actualTrafficFractions[2]+=linkValueVector[linkIndex[i][*itInt].index];
			aliveNodes[i].actualTrafficFractions[2]=aliveNodes[i].actualTrafficFractions[2]/aliveNodes[i].V;

			totalPeers=aliveNodes[i].K.size();
			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++){

				if(aliveNodes[*itInt].peeringStrategyNumber==1)
					totalOpenPeers++;

				totalUpstreamTraffic+=linkValueVector[linkIndex[i][*itInt].index];
				totalPeeringTraffic+=linkValueVector[linkIndex[i][*itInt].index];

				if(!aliveNodes[*itInt].I.empty()){
					for(itInt2=aliveNodes[*itInt].K.begin();itInt2!=aliveNodes[*itInt].K.end();itInt2++){
						if(aliveNodes[*itInt].isImmediateCustomerOfPeer(*itInt2)==i){
							peerCustomerProductAgainst++;
							trafficStolenFrom+=linkValueVector[linkIndex[*itInt][*itInt2].index];
						}
					}
				}

				if(aliveNodes[i].isImmediateCustomerOfPeer(*itInt)!=-1){
					peerCustomerProduct++;
					trafficStolenBy+=linkValueVector[linkIndex[i][*itInt].index];
				}
			}


			printProviderFile<<numSimulations<<":";
			printProviderFile<<i<<":"<<aliveNodes[i].numGPresence<<":"<<cheapestInRegions<<":";
			printProviderFile<<aliveNodes[i].trafficGenerated<<":"<<aliveNodes[i].trafficConsumed<<":"<<aliveNodes[i].Vt<<":"<<aliveNodes[i].V<<":";
			printProviderFile<<aliveNodes[i].isCP<<":"<<aliveNodes[i].isCC<<":";
			printProviderFile<<aliveNodes[i].I.size()<<":"<<aliveNodes[i].J.size()<<":";
			printProviderFile<<numCPCustomers<<":"<<numCCCustomers<<":";
			printProviderFile<<aliveNodes[i].Q<<":";
			printProviderFile<<numPotentialPeers<<":"<<numPotentialCPCCPeers<<":"<<numPotentialProviderPeers<<":"<<numPotentialStubPeers<<":";
			printProviderFile<<aliveNodes[i].peeringStrategyNumber<<":"<<aliveNodes[i].K.size()<<":";
			printProviderFile<<numCPPeers<<":"<<numCCPeers<<":"<<numProviderPeers<<":"<<numStubPeers<<":";
			printProviderFile<<aliveNodes[i].providerCost<<":"<<aliveNodes[i].peerCost<<":"<<aliveNodes[i].customerRevenue<<":"<<aliveNodes[i].fitness<<":";


			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					printProviderFile<<trafficFractions[i][j][k]<<":";

			for(int k=0;k<3;k++)
				printProviderFile<<aliveNodes[i].actualTrafficFractions[k]<<":";

			printProviderFile<<peerCustomerProductAgainst<<":"<<peerCustomerProduct<<":";

			printProviderFile<<trafficStolenFrom<<":"<<trafficStolenBy<<":";

			for(itInt=aliveNodes[i].I.begin();itInt!=aliveNodes[i].I.end();itInt++)
				printProviderFile<<*itInt<<",";
			printProviderFile<<":";
			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++)
				printProviderFile<<*itInt<<",";
			printProviderFile<<":";

			if(totalUpstreamTraffic!=0)
				printProviderFile<<totalPeeringTraffic/totalUpstreamTraffic<<":";
			else
				printProviderFile<<"0:";

			if(totalPeers!=0)
				printProviderFile<<totalOpenPeers/totalPeers<<":";
			else
				printProviderFile<<"0:";

			printProviderFile<<aliveNodes[i].overLap.size()<<":"<<potentialCustomers<<":";

			printProviderFile<<endl;


		}
	}

	//antiCoalitionMetric(numSimulations);

}

void snapShot(int numSimulations){


	snapshotFile<<endl<<endl<<"****** Simulation "<<numSimulations<<" ******"<<endl<<endl;
	snapshotFile<<"digraph G{"<<endl;


	snapshotFile<<"node [shape=circle];"<<endl;
	for(int i=0;i<activeNodes;i++)
		if(aliveNodes[i].Q!=-1 && !aliveNodes[i].I.empty()){
			snapshotFile<<" "<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\"";
		}
	snapshotFile<<";"<<endl;


	snapshotFile<<"node [shape=doublecircle];"<<endl;
	for(int i=0;i<activeNodes;i++)
		if(aliveNodes[i].Q==-1 && !aliveNodes[i].I.empty()){
			snapshotFile<<" "<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\"";
		}
	snapshotFile<<";"<<endl;

	for(int i=0;i<activeNodes;i++)
		for(int j=i+1;j<activeNodes;j++){
			if(aliveNodes[i].Q==-1 && aliveNodes[j].Q==-1 && !aliveNodes[i].I.empty() && !aliveNodes[j].I.empty()){
				snapshotFile<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\""<<" ";
				snapshotFile<<"-> ";
				snapshotFile<<"\""<<j<<"_"<<aliveNodes[j].numGPresence<<"_"<<aliveNodes[j].fitness<<"_"<<aliveNodes[j].peeringStrategyNumber<<"\""<<" ";
				snapshotFile<<"[arrowhead = none, color = red, weight = 4.0];"<<endl;
			}
		}

	//snapshotFile<<" node [shape = circle];"<<endl;

	for(int i=0;i<activeNodes;i++){
		if(aliveNodes[i].Q!=-1 && !aliveNodes[i].I.empty()){
			snapshotFile<<"\""<<aliveNodes[i].Q<<"_"<<aliveNodes[aliveNodes[i].Q].numGPresence<<"_"<<aliveNodes[aliveNodes[i].Q].fitness<<"_"<<aliveNodes[aliveNodes[i].Q].peeringStrategyNumber<<"\"";
			snapshotFile<<" -> ";
			snapshotFile<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\"";
			snapshotFile<<"[dir=\"back\"];";
			snapshotFile<<endl;
		}
	}

	list<int>::iterator it;
	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].K.empty() && !aliveNodes[i].I.empty()){
			for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++)
				if(i<*it && !aliveNodes[*it].I.empty()){

					if(aliveNodes[i].Q==-1 && aliveNodes[*it].Q==-1){}

					else{
						snapshotFile<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\"";
						snapshotFile<<" -> ";
						snapshotFile<<"\""<<*it<<"_"<<aliveNodes[*it].numGPresence<<"_"<<aliveNodes[*it].fitness<<"_"<<aliveNodes[*it].peeringStrategyNumber<<"\""<<" ";
						snapshotFile<<"[arrowhead = none, color = blue, weight = 2.0];"<<endl;
					}
				}
		}

	snapshotFile<<"}"<<endl;

}


void displayRouteData(){

	logFile<<endl<<"LinkIndex: "<<endl;
	for(int c=0;c<activeNodes;c++){
		for(int d=0;d<activeNodes;d++){
			logFile<<linkIndex[c][d].index<<","<<linkIndex[c][d].provider<<"\t";
		}
		logFile<<endl;
	}

	logFile<<endl<<"RoutingMatrix: "<<endl;

	list<int>::iterator it;
	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++){

			if(flowIndex[i][j]!=-1){
				logFile<<"Flow "<<i<<" <-> "<<j<<": ";

				for(it=routingMatrixScale[flowIndex[i][j]].begin();it!=routingMatrixScale[flowIndex[i][j]].end();it++){

					for(int p=0;p<(activeNodes-1);p++)
						for(int q=p+1;q<activeNodes;q++)
							if(p!=q && linkIndex[p][q].index==*it)
								logFile<<p<<"-"<<q<<" + ";

				}

				logFile<<endl;
			}
		}

	logFile<<endl<<"RoutingMatrix Asymmetric: "<<endl;

	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++){

			if(flowIndex[i][j]!=-1){
				logFile<<"Flow "<<i<<" <-> "<<j<<": ";

				for(it=routingMatrixScaleAsym[flowIndex[i][j]].begin();it!=routingMatrixScaleAsym[flowIndex[i][j]].end();it++){

					for(int p=0;p<(activeNodes-1);p++)
						for(int q=p+1;q<activeNodes;q++)
							if(p!=q && linkIndex[p][q].index==*it)
								logFile<<p<<"-"<<q<<" + ";


				}

				logFile<<endl;
			}
		}

}

void displayTopology(){

	list<int>::iterator itInt;
	logFile<<"Tier1: ";
	for(itInt=Tier1.begin();itInt!=Tier1.end();itInt++){
		logFile<<*itInt<<" ";
	}

	logFile<<endl;

	for(int b=0;b<activeNodes;b++){

		if(aliveNodes[b].lifeStatus==alive){
			logFile<<"Status for "<<b<<endl;
			logFile<<"Q: "<<aliveNodes[b].Q<<endl;
			logFile<<"I: ";
			for(itInt=aliveNodes[b].I.begin();itInt!=aliveNodes[b].I.end();itInt++)
				logFile<<*itInt<<" ";
			logFile<<endl<<"J: ";
			for(itInt=aliveNodes[b].J.begin();itInt!=aliveNodes[b].J.end();itInt++)
				logFile<<*itInt<<" ";
			logFile<<endl<<"K: ";
			for(itInt=aliveNodes[b].K.begin();itInt!=aliveNodes[b].K.end();itInt++)
				logFile<<*itInt<<" ";
			logFile<<endl;
		}

	}

}

void classifyProviders(){

	double fitnessStats[3][5]={0};	//avg, median, min, max, sum
	list<int> T1;
	list<int> T2;
	list<int> T3;
	list<int>::iterator it;
	list<double> fitness;

	ofstream providerFile;
	char providerFileName[50];
	sprintf(providerFileName,"providerClass_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed);
	providerFile.open(providerFileName,ios::out|ios::app);


	for(int i=0;i<activeNodes;i++){
		if(!aliveNodes[i].I.empty()){

			if(aliveNodes[i].Q==-1)
				T1.push_back(i);

			else{

				if(aliveNodes[aliveNodes[i].Q].Q==-1)
					T2.push_back(i);

				else
					T3.push_back(i);

			}

		}
	}

	for(it=T1.begin();it!=T1.end();it++){

		fitnessStats[0][4]+=aliveNodes[*it].fitness;
		fitness.push_back(aliveNodes[*it].fitness);
		providerFile<<*it<<"\t";

	}

	providerFile<<endl;

	fitnessStats[0][0]=findDoubleAvg(fitness);
	fitnessStats[0][1]=findDoubleMedian(fitness);
	fitnessStats[0][2]=findDoubleMin(fitness);
	fitnessStats[0][3]=findDoubleMax(fitness);

	fitness.clear();

	for(it=T2.begin();it!=T2.end();it++){

		fitnessStats[1][4]+=aliveNodes[*it].fitness;
		fitness.push_back(aliveNodes[*it].fitness);
		providerFile<<*it<<"\t";

	}

	providerFile<<endl;

	fitnessStats[1][0]=findDoubleAvg(fitness);
	fitnessStats[1][1]=findDoubleMedian(fitness);
	fitnessStats[1][2]=findDoubleMin(fitness);
	fitnessStats[1][3]=findDoubleMax(fitness);

	fitness.clear();

	for(it=T3.begin();it!=T3.end();it++){

		fitnessStats[2][4]+=aliveNodes[*it].fitness;
		fitness.push_back(aliveNodes[*it].fitness);
		providerFile<<*it<<"\t";

	}
	providerFile<<endl;

	fitnessStats[2][0]=findDoubleAvg(fitness);
	fitnessStats[2][1]=findDoubleMedian(fitness);
	fitnessStats[2][2]=findDoubleMin(fitness);
	fitnessStats[2][3]=findDoubleMax(fitness);

	ofstream dataFile;
	char dataFileName[50];
	sprintf(dataFileName,"fitnessHierarchyStats_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed);
	dataFile.open(dataFileName,ios::out|ios::app);

	for(int i=0;i<3;i++){
		for(int j=0;j<5;j++){
			dataFile<<fitnessStats[i][j]<<"\t";
		}
		dataFile<<endl;
	}

}

void recordStrategyDistribution2(int numSims){

	ofstream sFile;
	char sFileName[50];
	sprintf(sFileName,"strategyDistribution_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	sFile.open(sFileName,ios::out|ios::app);

	double strategyDistribution[5]={0};
	double numProviders=0;


	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].I.empty()){
			numProviders++;
			strategyDistribution[aliveNodes[i].peeringStrategyNumber]++;
		}

	for(int i=0;i<5;i++){
		strategyDistribution[i]=(strategyDistribution[i]*100)/numProviders;
		sFile<<i<<"\t"<<strategyDistribution[i]<<endl;
	}

}

void recordBetweennessCentralityDistribution(int numSims){

	list<int> transitNodes;
	list<int>::iterator it;
	list<double>::iterator itD;

	double transitCounter[500]={0};
	double totalTransits=0;
	list<double> betweennessDistribution;


	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++){
			if(linkIndex[i][j].index==-1){
				transitNodes.clear();
				totalTransits++;
				for(it=routingMatrixScale[flowIndex[i][j]].begin();it!=routingMatrixScale[flowIndex[i][j]].end();it++){

						for(int x=0;x<(activeNodes-1);x++)
							for(int y=x+1;y<activeNodes;y++){
								if(linkIndex[x][y].index==*it){
									if(x!=i && x!=j && !isPresentInList(transitNodes,x))
										transitNodes.push_back(x);
									if(y!=i && y!=j && !isPresentInList(transitNodes,y))
										transitNodes.push_back(y);

									break;
								}//end if
							}//end for

				}//end for

				for(it=transitNodes.begin();it!=transitNodes.end();it++){
					transitCounter[*it]++;
				}

				transitNodes.clear();
				totalTransits++;
				for(it=routingMatrixScaleAsym[flowIndex[i][j]].begin();it!=routingMatrixScaleAsym[flowIndex[i][j]].end();it++){

					for(int x=0;x<(activeNodes-1);x++)
						for(int y=x+1;y<activeNodes;y++){
							if(linkIndex[x][y].index==*it){
								if(x!=i && x!=j && !isPresentInList(transitNodes,x))
									transitNodes.push_back(x);
								if(y!=i && y!=j && !isPresentInList(transitNodes,y))
									transitNodes.push_back(y);

								break;
							}//end if
						}//end for

				}//end for

				for(it=transitNodes.begin();it!=transitNodes.end();it++){
					transitCounter[*it]++;
				}

			}//end if
		}//end for

	for(int i=0;i<activeNodes;i++){
		transitCounter[i]=transitCounter[i]/totalTransits;
		if(transitCounter[i]>0){
			betweennessDistribution.push_back(transitCounter[i]);
		}
	}

	betweennessDistribution.sort();

	ofstream bdFile;
	char bdFileName[50];
	sprintf(bdFileName,"betweennessCentralityDistribution_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	bdFile.open(bdFileName,ios::out|ios::app);

	ofstream bFile;
	char bFileName[50];
	sprintf(bFileName,"betweennessCentrality_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	bFile.open(bFileName,ios::out|ios::app);

	for(int i=0;i<activeNodes;i++){
		if(transitCounter[i]>0){

			if(aliveNodes[i].Q==-1)
				bFile<<i<<"\t"<<"1\t"<<transitCounter[i]<<endl;
			else if(aliveNodes[aliveNodes[i].Q].Q==-1)
				bFile<<i<<"\t"<<"2\t"<<transitCounter[i]<<endl;
			else
				bFile<<i<<"\t"<<"3\t"<<transitCounter[i]<<endl;

		}
	}


	double counter=1;
	double frac;
	for(itD=betweennessDistribution.begin();itD!=betweennessDistribution.end();itD++,counter++){
		frac=counter/betweennessDistribution.size();
		bdFile<<frac<<"\t"<<*itD<<endl;
	}
}

void recordProviderPeering(int numSims){

	ofstream plFile;
	char plFileName[50];
	sprintf(plFileName,"providerLinkLog_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	plFile.open(plFileName,ios::out|ios::app);

	ofstream ptFile;
	char ptFileName[50];
	sprintf(ptFileName,"providerTrafficLog_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	ptFile.open(ptFileName,ios::out|ios::app);

	int linkClass[5]={0};
	double trafficClass[5]={0};

	for(int i=0;i<(activeNodes-1);i++){
		for(int j=i+1;j<activeNodes;j++){
			if(aliveNodes[i].isPeer(j)){

				if(!aliveNodes[i].I.empty() && !aliveNodes[j].I.empty()){

					if(aliveNodes[i].Q!=-1 && aliveNodes[j].Q!=-1){

						if(aliveNodes[aliveNodes[i].Q].Q==-1 && aliveNodes[aliveNodes[j].Q].Q==-1){
							linkClass[0]++;
							trafficClass[0]+=linkValueVector[linkIndex[i][j].index];
						}

						if((aliveNodes[aliveNodes[i].Q].Q==-1 && aliveNodes[aliveNodes[j].Q].Q!=-1) || (aliveNodes[aliveNodes[j].Q].Q==-1 && aliveNodes[aliveNodes[i].Q].Q!=-1)){
							linkClass[1]++;
							trafficClass[1]+=linkValueVector[linkIndex[i][j].index];
						}

						if(aliveNodes[aliveNodes[i].Q].Q!=-1 && aliveNodes[aliveNodes[j].Q].Q!=-1){
							linkClass[2]++;
							trafficClass[2]+=linkValueVector[linkIndex[i][j].index];
						}


					}

				}//end if both providers

				if(!aliveNodes[i].I.empty() && aliveNodes[i].Q!=-1 && aliveNodes[j].I.empty()){

					if(aliveNodes[aliveNodes[i].Q].Q==-1){
						linkClass[3]++;
						trafficClass[3]+=linkValueVector[linkIndex[i][j].index];
					}

					else{
						linkClass[4]++;
						trafficClass[4]+=linkValueVector[linkIndex[i][j].index];

					}

				}

				if(!aliveNodes[j].I.empty() && aliveNodes[j].Q!=-1 && aliveNodes[i].I.empty()){

					if(aliveNodes[aliveNodes[j].Q].Q==-1){
						linkClass[3]++;
						trafficClass[3]+=linkValueVector[linkIndex[i][j].index];
					}

					else{
						linkClass[4]++;
						trafficClass[4]+=linkValueVector[linkIndex[i][j].index];

					}

				}

			}
		}
	}

	for(int i=0;i<5;i++){
		plFile<<linkClass[i]<<"\t";
		ptFile<<trafficClass[i]<<"\t";
	}

	plFile<<endl;
	ptFile<<endl;

}

void recordFitnessLog(int numSims){

	ofstream fitnessFile;
	char fitnessFileName[50];
	sprintf(fitnessFileName,"fitnessLog_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);

	fitnessFile.open(fitnessFileName,ios::out|ios::app);

	for(int i=0;i<activeNodes;i++){

		fitnessFile<<universalSigma<<"\t"<<i<<"\t";

		if(!aliveNodes[i].I.empty()){
			if(aliveNodes[i].Q==-1)
				fitnessFile<<"T1\t";
			else if(aliveNodes[i].Q!=-1){
				if(aliveNodes[aliveNodes[i].Q].Q==-1)
					fitnessFile<<"T2\t";
				else
					fitnessFile<<"T3\t";
			}
		}

		else{
			if(aliveNodes[i].isCP)
				fitnessFile<<"CP\t";
			else if(aliveNodes[i].isCC)
				fitnessFile<<"CC\t";
			else
				fitnessFile<<"Stub\t";
		}

		fitnessFile<<aliveNodes[i].fitness<<endl;
	}
}

void recordJaccardLog(int numSims){

	ofstream jFile;
	char fileName[50];
	sprintf(fileName,"jaccardLog_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	jFile.open(fileName);
	int linkType;

	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++){

			if(!aliveNodes[i].I.empty() && !aliveNodes[j].I.empty()){
				if(linkIndex[i][j].index!=-1){

					linkType=linkIndex[i][j].linkClass;

					if(linkType==1)
						jFile<<i<<"\t"<<j<<"\t"<<linkType<<endl;

					else{
						if(aliveNodes[i].Q==j)
							jFile<<i<<"\t"<<j<<"\t"<<"2"<<endl;
						else
							jFile<<i<<"\t"<<j<<"\t"<<"3"<<endl;

					}
				}
			}
		}
}

void recordDistributions(int numSims){

	ofstream dFile;
	char fileName[50];
	sprintf(fileName,"distributions_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	dFile.open(fileName);

	ofstream linkLoadFile;
	char linkfileName[50];
	sprintf(linkfileName,"linkLoadDistribution_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	linkLoadFile.open(linkfileName);
	list<double> linkLoad;

	ofstream stubDegreeFile;
	char stubDegreefileName[50];
	sprintf(stubDegreefileName,"stubDegree_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	stubDegreeFile.open(stubDegreefileName);

	ofstream providerDegreeFile;
	char providerDegreefileName[50];
	sprintf(providerDegreefileName,"providerDegree_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	providerDegreeFile.open(providerDegreefileName);


	list<double> vt;
	list<double> fitness;
	list<int> customers;
	list<int> peers;
	list<int>::iterator itInt1;
	list<int>::iterator itInt2;
	list<double>::iterator itDouble1;
	list<double>::iterator itDouble2;
	double counter=1;

	for(int i=0;i<activeNodes;i++){
		vt.push_back(aliveNodes[i].Vt);
		fitness.push_back(aliveNodes[i].fitness);
		customers.push_back(aliveNodes[i].I.size());
		peers.push_back(aliveNodes[i].K.size());
	}

	vt.sort();
	fitness.sort();
	customers.sort();
	peers.sort();

	for(itInt1=customers.begin(),itInt2=peers.begin(),itDouble1=vt.begin(),itDouble2=fitness.begin();itInt1!=customers.end();itInt1++,itInt2++,itDouble1++,itDouble2++,counter++){

		dFile<<counter/customers.size()<<"\t"<<*itInt1<<"\t"<<*itInt2<<"\t"<<*itDouble1<<"\t"<<*itDouble2<<endl;

	}

	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++){
			if(linkIndex[i][j].index!=-1){
				linkLoad.push_back(linkValueVector[linkIndex[i][j].index]);
			}
		}

	linkLoad.sort();
	int i=1;
	for(itDouble1=linkLoad.begin();itDouble1!=linkLoad.end();itDouble1++,i++){
		linkLoadFile<<*itDouble1<<(i/linkLoad.size())<<endl;
	}

	for(int i=0;i<activeNodes;i++){
		if(aliveNodes[i].I.empty()){
			stubDegreeFile<<i<<"\t"<<aliveNodes[i].K.size()<<endl;
		}

		else{
			providerDegreeFile<<i<<"\t"<<aliveNodes[i].I.size()<<"\t"<<aliveNodes[i].K.size()<<endl;
		}
	}
}

void recordEquilibrium(int numSims){

	ofstream eFile;
	char fileName[50];
	sprintf(fileName,"equilibrium_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
	eFile.open(fileName);

	list<int>::iterator itInt;
	eFile<<"Tier1: ";
	for(itInt=Tier1.begin();itInt!=Tier1.end();itInt++){
		eFile<<*itInt<<" ";
	}

	eFile<<endl;

	for(int b=0;b<activeNodes;b++){

		if(aliveNodes[b].lifeStatus==alive){
			eFile<<"Status for "<<b<<endl;
			eFile<<"Q: "<<aliveNodes[b].Q<<endl;
			eFile<<"I: ";
			for(itInt=aliveNodes[b].I.begin();itInt!=aliveNodes[b].I.end();itInt++)
				eFile<<*itInt<<" ";
			eFile<<endl<<"J: ";
			for(itInt=aliveNodes[b].J.begin();itInt!=aliveNodes[b].J.end();itInt++)
				eFile<<*itInt<<" ";
			eFile<<endl<<"K: ";
			for(itInt=aliveNodes[b].K.begin();itInt!=aliveNodes[b].K.end();itInt++)
				eFile<<*itInt<<" ";
			eFile<<endl;
			eFile<<"S: "<<aliveNodes[b].peeringStrategyNumber<<endl;
		}

	}

}

void displayNodeData(){

	list<Coordinate>::iterator itCo;
	string classification;

	for(int i=0;i<activeNodes;i++){
		if(aliveNodes[i].lifeStatus==alive){

			logFile<<endl<<"Node: "<<aliveNodes[i].nodeId<<" Vgen: "<<aliveNodes[i].trafficGenerated<<" Vcon: "<<aliveNodes[i].trafficConsumed<<" Vc: "<<aliveNodes[i].Vc<<" Vp: "<<aliveNodes[i].Vp<<" Vt: "<<aliveNodes[i].Vt<<" E: "<<aliveNodes[i].price<<" NumGPresence: "<<aliveNodes[i].numGPresence<<" G: ";
			for(itCo=aliveNodes[i].gPresence.begin();itCo!=aliveNodes[i].gPresence.end();itCo++){
				logFile<<(*itCo).xCoordinate*maxRegions+(*itCo).yCoordinate<<" ";
			}

			logFile<<"Categories: ";

			for(int j=0;j<7;j++)
				logFile<<aliveNodes[i].category[j]<<" ";

			logFile<<endl;
		}
	}

	logFile<<endl<<endl<<"Possible Provider Set Sx"<<endl<<endl;

	list<int> GS;
	list<Coordinate>::iterator it;
	list<int>::iterator it2;
	list<int>::iterator itNP;
	int xPoint;
	int yPoint;

	for(int i=0;i<activeNodes;i++){

		for(it=aliveNodes[i].gPresence.begin();it!=aliveNodes[i].gPresence.end();it++){

			xPoint=(*it).xCoordinate;
			yPoint=(*it).yCoordinate;

			if(geography[xPoint][yPoint].population>1){

				for(it2=geography[xPoint][yPoint].nodePresent.begin();it2!=geography[xPoint][yPoint].nodePresent.end();it2++){

					if((*it2)!=i){

						GS.push_back(*it2);

					}//end if

				}//end for

			}//end if

		}//end for
		GS.sort();
		GS.unique();

		//cout<<"S"<<i<<": ";
		logFile<<"S"<<i<<": ";
		for(itNP=GS.begin();itNP!=GS.end();itNP++){
			//cout<<*itNP<<"\t";
			logFile<<*itNP<<"\t";
		}
		//cout<<endl;
		logFile<<endl;
		GS.clear();

	}

}

void displayTrafficMatrix(){

	//cout<<endl<<"Traffic Matrix: "<<endl;
	for(int i=0;i<activeNodes;i++){
		for(int j=0;j<activeNodes;j++){
			//cout<<trafficMatrix[i][j]<<"\t";
		}
		//cout<<endl;
	}
	//cout<<endl;

	logFile<<endl<<"Traffic Matrix: "<<endl;
	for(int i=0;i<activeNodes;i++){
		for(int j=0;j<activeNodes;j++){
			logFile<<trafficMatrix[i][j]<<"\t";
		}
		logFile<<endl;
	}
	logFile<<endl;

	logFile<<"Flows: "<<endl;
	for(int i=0;i<(activeNodes-1);i++){
			for(int j=i+1;j<activeNodes;j++){
				logFile<<i<<","<<j<<": "<<trafficMatrix[i][j]+trafficMatrix[j][i]<<endl;
			}
	}

}

double sumG(){

	static double sum=0;

	if(sum==0)
		for(int i=0;i<activeNodes;i++)
			sum+=aliveNodes[i].numGPresence;

	return sum;
}

void permute(bool random,int seed){
	//fill up random order list

	list<int>::iterator it;

	if(random){

		if(seed!=-1){

			srand(seed);

			int tempInt;
			nodeOrder.clear();
			nodeOrderBackup.clear();
			while(nodeOrder.size()<activeNodes){
				tempInt=rand()%activeNodes;
				if(!isPresentInList(nodeOrder,tempInt)){
					nodeOrder.push_back(tempInt);
					nodeOrderBackup.push_back(tempInt);
				}
			}
		}

		else{

			nodeOrder.clear();
			for(it=nodeOrderBackup.begin();it!=nodeOrderBackup.end();it++){
				nodeOrder.push_back(*it);
			}

		}//end else

	}

	else{
		nodeOrder.clear();
		nodeOrderBackup.clear();

		for(int i=0;i<activeNodes;i++){
			nodeOrder.push_back(i);
			nodeOrderBackup.push_back(i);

		}
	}
}

void permute(bool random,int seed,int stackelbergLeader){
	//fill up random order list

	list<int>::iterator it;

	if(random){

		if(seed!=-1){

			srand(seed);

			int tempInt;
			nodeOrder.clear();
			nodeOrderBackup.clear();

			if(stackelbergLeader!=-1){
				nodeOrder.push_back(stackelbergLeader);
				nodeOrderBackup.push_back(stackelbergLeader);
			}
			while(nodeOrder.size()<activeNodes){
				tempInt=rand()%activeNodes;
				if(!isPresentInList(nodeOrder,tempInt)){
					nodeOrder.push_back(tempInt);
					nodeOrderBackup.push_back(tempInt);
				}
			}
		}

		else{

			nodeOrder.clear();
			for(it=nodeOrderBackup.begin();it!=nodeOrderBackup.end();it++){
				nodeOrder.push_back(*it);
			}

		}//end else

	}

	else{
		nodeOrder.clear();
		nodeOrderBackup.clear();

		for(int i=0;i<activeNodes;i++){
			nodeOrder.push_back(i);
			nodeOrderBackup.push_back(i);

		}
	}
}
void permute(bool random){

	//fill up random order list
	static int i=0;
	static bool seedAssigned=false;

	if(random){

		if(playOrderSeed!=-1){

			if(seedAssigned==false){
				srand(playOrderSeed);
				seedAssigned=true;
			}

			i++;
			int tempInt;
			nodeOrder.clear();
			nodeOrderBackup.clear();
			while(nodeOrder.size()<activeNodes){
				tempInt=rand()%activeNodes;
				if(!isPresentInList(nodeOrder,tempInt)){
					nodeOrder.push_back(tempInt);
					nodeOrderBackup.push_back(tempInt);
				}
			}
		}

		else{

			for(int i=0;i<activeNodes;i++){
				nodeOrder.push_back(i);
				nodeOrderBackup.push_back(i);

			}

		}//end else

	}

	else{
		nodeOrder.clear();
		nodeOrderBackup.clear();

		for(int i=0;i<activeNodes;i++){
			nodeOrder.push_back(i);
			nodeOrderBackup.push_back(i);

		}
	}
}

void refillNodeOrder(){

	list<int>::iterator itInt;

	for(itInt=nodeOrderBackup.begin();itInt!=nodeOrderBackup.end();itInt++)
		nodeOrder.push_back(*itInt);
}

int getNewIt(){

	int tempInt;

	if(!nodeOrder.empty()){
		tempInt=nodeOrder.front();
		nodeOrder.pop_front();
		return tempInt;
	}

	else
		return -1;
}

void recordIncreaseDecrease(int numSimulations){

	double increase=0;
	double decrease=0;
	double constant=0;
	double numProviders=0;

	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].I.empty()){
			numProviders++;

			/*
			if(aliveNodes[i].deltaFitness>0)
				increase++;
			else if(aliveNodes[i].deltaFitness<0)
				decrease++;
			else
				constant++;
			*/

			if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])>0)
				increase++;
			else if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])<0)
				decrease++;
			else
				constant++;
		}

	increase=(increase/numProviders)*100;
	decrease=(decrease/numProviders)*100;
	constant=(constant/numProviders)*100;

	providerIncreaseDecrease[numSimulations][0]=increase;
	providerIncreaseDecrease[numSimulations][1]=decrease;
	providerIncreaseDecrease[numSimulations][2]=constant;


	double t1Increase=0;
	double t1Decrease=0;
	double t1Constant=0;
	double t2Increase=0;
	double t2Decrease=0;
	double t2Constant=0;
	double t3Increase=0;
	double t3Decrease=0;
	double t3Constant=0;
	double numT1=0;
	double numT2=0;
	double numT3=0;
	list<int>::iterator it;
	bool isT2=false;

	for(int i=0;i<activeNodes;i++){

		if(!aliveNodes[i].I.empty()){

			isT2=false;

			if(aliveNodes[i].Q==-1){

				numT1++;

				if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])>0)
					t1Increase++;

				else if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])<0)
					t1Decrease++;

				else
					t1Constant++;
			}//end if for t1;

			else{

				for(it=aliveNodes[i].J.begin();it!=aliveNodes[i].J.end();it++){
					if(!aliveNodes[*it].I.empty()){
						isT2=true;

						numT2++;
						if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])>0)
							t2Increase++;

						else if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])<0)
							t2Decrease++;

						else
							t2Constant++;

						break;

					}
				}

				if(isT2==false){

					numT3++;

					if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])>0)
						t3Increase++;

					else if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])<0)
						t3Decrease++;

					else
						t3Constant++;

				}

			}


		}
	}

	if(numT1>0){
		t1Increase=t1Increase/numT1*100;
		t1Decrease=t1Decrease/numT1*100;
		t1Constant=t1Constant/numT1*100;
	}

	if(numT2>0){
		t2Increase=t2Increase/numT2*100;
		t2Decrease=t2Decrease/numT2*100;
		t2Constant=t2Constant/numT2*100;
	}

	if(numT3>0){
		t3Increase=t3Increase/numT3*100;
		t3Decrease=t3Decrease/numT3*100;
		t3Constant=t3Constant/numT3*100;
	}

	t1ProvidersFitness[numSimulations][0]=t1Increase;
	t1ProvidersFitness[numSimulations][1]=t1Decrease;
	t1ProvidersFitness[numSimulations][2]=t1Constant;

	t2ProvidersFitness[numSimulations][0]=t2Increase;
	t2ProvidersFitness[numSimulations][1]=t2Decrease;
	t2ProvidersFitness[numSimulations][2]=t2Constant;

	t3ProvidersFitness[numSimulations][0]=t3Increase;
	t3ProvidersFitness[numSimulations][1]=t3Decrease;
	t3ProvidersFitness[numSimulations][2]=t3Constant;


}

void recordStrategyDistribution(int numSimulations){

	double numProviders=0;
	double numRestrictive=0;
	double numSelective=0;
	double numOpen=0;

	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].I.empty()){
			numProviders++;

			if(aliveNodes[i].peeringStrategyNumber==0)
				numSelective++;

			else if(aliveNodes[i].peeringStrategyNumber==1)
				numOpen++;

			else
				numRestrictive++;


		}

	strategyDistribution[numSimulations][0]=(numSelective/numProviders)*100;
	strategyDistribution[numSimulations][1]=(numOpen/numProviders)*100;
	strategyDistribution[numSimulations][2]=(numRestrictive/numProviders)*100;

}

void recordFitness(int numSimulations){


	for(int i=0;i<activeNodes;i++){
		fitnessRecord[numSimulations][i]=aliveNodes[i].fitness;

	}

}

void normalizeProviderFitness(){

	double max=0;

	for(int i=1;i<3;i++)
		for(int j=0;j<activeNodes;j++)
			if(fitnessRecord[i][j]!=-1 && !aliveNodes[j].I.empty()){

				aliveNodes[j].percentageChangeInFitness=((fitnessRecord[2][j]-fitnessRecord[0][j])/fitnessRecord[0][j])*100;

				if(abs(fitnessRecord[i][j])>max)
					max=abs(fitnessRecord[i][j]);
			}

	if(max!=0){

		for(int i=0;i<5;i++)
			for(int j=0;j<activeNodes;j++)
				if(fitnessRecord[i][j]!=-1 && !aliveNodes[j].I.empty()){
					fitnessRecord[i][j]=fitnessRecord[i][j]/max;

				}

	}

}

void normalizeCPCCFitness(){

	double max=0;

	for(int i=0;i<5;i++)
		for(int j=0;j<activeNodes;j++)
			if(fitnessRecord[i][j]!=-1 && aliveNodes[j].isMajorContentNet==true){
				if(abs(fitnessRecord[i][j])>max)
					max=abs(fitnessRecord[i][j]);
			}

	if(max!=0){

		for(int i=0;i<5;i++)
			for(int j=0;j<activeNodes;j++)
				if(fitnessRecord[i][j]!=-1 && aliveNodes[j].isMajorContentNet==true){
					fitnessRecord[i][j]=fitnessRecord[i][j]/max;

				}

	}

}

void normalizeStubFitness(){

	double max=0;

	for(int i=0;i<5;i++)
		for(int j=0;j<activeNodes;j++)
			if(fitnessRecord[i][j]!=-1 && aliveNodes[j].isMajorContentNet==false && aliveNodes[j].I.empty()){
				if(abs(fitnessRecord[i][j])>max)
					max=abs(fitnessRecord[i][j]);
			}

	if(max!=0){

		for(int i=0;i<5;i++)
			for(int j=0;j<activeNodes;j++)
				if(fitnessRecord[i][j]!=-1 && aliveNodes[j].isMajorContentNet==false && aliveNodes[j].I.empty()){
					fitnessRecord[i][j]=fitnessRecord[i][j]/max;

				}

	}

}

void providerFitnessStats(){

	ofstream providerStats;
	providerStats.open("providerFitnessStats.txt");

	double avg=0;
	double median=0;
	double min=0;
	double max=0;
	list<double> values;

	double stats[5][4];

	for(int i=0;i<5;i++){

		values.clear();

		for(int j=0;j<500;j++){
			if(!aliveNodes[j].I.empty())
				values.push_back(fitnessRecord[i][j]);
		}

		avg=findDoubleAvg(values);
		median=findDoubleMedian(values);
		min=findDoubleMin(values);
		max=findDoubleMax(values);

		stats[i][0]=avg;
		stats[i][1]=median;
		stats[i][2]=min;
		stats[i][3]=max;

	}

	for(int i=0;i<5;i++){
		for(int j=0;j<4;j++){
			providerStats<<stats[i][j]<<"\t";
		}
		providerStats<<endl;
	}

}

void cpccFitnessStats(){

	ofstream cpccStats;
	cpccStats.open("cpccFitnessStats.txt");

	double avg=0;
	double median=0;
	double min=0;
	double max=0;
	list<double> values;

	double stats[5][4];

	for(int i=0;i<5;i++){

		values.clear();

		for(int j=0;j<500;j++){
			if(aliveNodes[j].I.empty() && aliveNodes[j].isMajorContentNet==true)
				values.push_back(fitnessRecord[i][j]);
		}

		avg=findDoubleAvg(values);
		median=findDoubleMedian(values);
		min=findDoubleMin(values);
		max=findDoubleMax(values);

		stats[i][0]=avg;
		stats[i][1]=median;
		stats[i][2]=min;
		stats[i][3]=max;

	}

	for(int i=0;i<5;i++){
		for(int j=0;j<4;j++){
			cpccStats<<stats[i][j]<<"\t";
		}
		cpccStats<<endl;
	}

}

void stubFitnessStats(){

	ofstream stubStats;
	stubStats.open("stubFitnessStats.txt");

	double avg=0;
	double median=0;
	double min=0;
	double max=0;
	list<double> values;

	double stats[5][4];

	for(int i=0;i<5;i++){

		values.clear();

		for(int j=0;j<500;j++){
			if(aliveNodes[j].I.empty() && aliveNodes[j].isMajorContentNet==false)
				values.push_back(fitnessRecord[i][j]);
		}

		avg=findDoubleAvg(values);
		median=findDoubleMedian(values);
		min=findDoubleMin(values);
		max=findDoubleMax(values);

		stats[i][0]=avg;
		stats[i][1]=median;
		stats[i][2]=min;
		stats[i][3]=max;

	}

	for(int i=0;i<5;i++){
		for(int j=0;j<4;j++){
			stubStats<<stats[i][j]<<"\t";
		}
		stubStats<<endl;
	}

}

void printTopologyStats(){

	ofstream idFile;
	idFile.open("topologyStats.txt",ios::out | ios::app);

	idFile<<numSimulations<<"\t";

	//idFile<<"Providers\t";
	for(int i=0;i<1;i++)
		idFile<<numProviders[i]<<"\t";

	//idFile<<endl;

	//idFile<<"CP/CC\t";
	for(int i=0;i<1;i++)
		idFile<<numCPCC[i]<<"\t";

	//idFile<<endl;

	//idFile<<"T1\t";
	for(int i=0;i<1;i++)
		idFile<<numT1[i]<<"\t";

	//idFile<<endl;

	//idFile<<"Tree Height\t";
	for(int i=0;i<1;i++)
		idFile<<treeHeight[i]<<"\t";

	//idFile<<endl;

	//idFile<<"Diameter\t";
	for(int i=0;i<1;i++)
		idFile<<networkDiameter[i]<<"\t";

	//idFile<<endl;


	//idFile<<"Avg. Weighted Path Length\t";
	for(int i=0;i<1;i++)
		idFile<<avgWeightedPathLength[i]<<"\t";

	//idFile<<endl;


	//idFile<<"Avg. Path Length\t";
	for(int i=0;i<1;i++)
		idFile<<avgPlainPathLength[i]<<"\t";
	//idFile<<endl;
	//additions

	//idFile<<"Link Density\t";
	for(int i=0;i<1;i++)
		idFile<<linkDensity[i]<<"\t";

//	idFile<<endl;

	//idFile<<"Peering Only Traffic %age\t";
	for(int i=0;i<1;i++)
		idFile<<peeringTrafficOnly[i]<<"\t";

	//idFile<<endl;

	//idFile<<"Peering Clustering Coefficient\t";
	for(int i=0;i<1;i++)
		idFile<<ppClusteringCoefficient[i]<<"\t";

	//idFile<<endl;

	//idFile<<"T1 NT1 transit ratio\t";
	for(int i=0;i<1;i++)
		idFile<<t1Nt1TransitRatio[i]<<"\t";

	//idFile<<endl;

	//idFile<<"Wealthiest ID\t";
	for(int i=0;i<1;i++)
		idFile<<wealthiestId[i]<<"\t";
	//idFile<<endl;

	//idFile<<"Max Wealth\t";
	for(int i=0;i<1;i++)
		idFile<<maxWealth[i]<<"\t";


	for(int i=0;i<1;i++)
		idFile<<numT2[i]<<"\t";

	for(int i=0;i<1;i++)
		idFile<<numT3[i]<<"\t";

	idFile<<endl;


}

void strategyStats(){

		ofstream s1;
		s1.open("strategyDistribution_1.txt", ios::out | ios::app);

		ofstream s2;
		s2.open("strategyDistribution_2.txt", ios::out | ios::app);

		for(int i=1;i<3;i++){
			for(int j=0;j<3;j++){

				if(i==1)
					s1<<strategyDistribution[i][j]<<"\t";

				if(i==2)
					s2<<strategyDistribution[i][j]<<"\t";

			}


		}

		s1<<endl;
		s2<<endl;

}

void providerClassIncreaseDecreaseStats(){

	ofstream idFile;
	idFile.open("providerIncreaseDecrease.txt");

	for(int i=1;i<5;i++){
		for(int j=0;j<3;j++){
			idFile<<t1ProvidersFitness[i][j]<<"\t";
		}
		idFile<<endl;
	}

	idFile<<endl<<endl;

	for(int i=1;i<5;i++){
		for(int j=0;j<3;j++){
			idFile<<t2ProvidersFitness[i][j]<<"\t";
		}
		idFile<<endl;
	}

	idFile<<endl<<endl;

	for(int i=1;i<5;i++){
		for(int j=0;j<3;j++){
			idFile<<t3ProvidersFitness[i][j]<<"\t";
		}
		idFile<<endl;
	}

	idFile<<endl<<endl;
}

void increaseDecreaseStats(){

	ofstream id1;
	id1.open("increaseDecrease_1.txt", ios::out | ios::app);

	ofstream id2;
	id2.open("increaseDecrease_2.txt", ios::out | ios::app);

	for(int i=1;i<3;i++){
		for(int j=0;j<3;j++){

			if(i==1)
				id1<<providerIncreaseDecrease[i][j]<<"\t";

			if(i==2)
				id2<<providerIncreaseDecrease[i][j]<<"\t";

		}


	}

	id1<<endl;
	id2<<endl;

}

void recordNetworkMetrics(int numSimulations, int numIterations){


	ofstream rlFile;
	rlFile.open("resultLog.txt", ios::out | ios::app);
	int category=0;
	list<int>::iterator it;
	list<int>::iterator it2;
	bool isCategory2=false;
	int publicPeers=0;
	int privatePeers=0;


	for(int i=0;i<activeNodes;i++){
		if(!aliveNodes[i].I.empty()){

			isCategory2=false;
			publicPeers=0;
			privatePeers=0;

			if(aliveNodes[i].Q==-1)
				category=1;

			else{

				for(it=aliveNodes[i].J.begin();it!=aliveNodes[i].J.end();it++)
					if(!aliveNodes[*it].I.empty()){
						isCategory2=true;
						break;
					}

				if(isCategory2==true)
					category=2;
				else
					category=3;

			}

			if(!aliveNodes[i].K.empty()){
				for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++){

					if(linkValueVector[linkIndex[i][*it].index]>=50)
						privatePeers++;
					else
						publicPeers++;
				}

			}

			rlFile<<numSimulations<<":"<<numIterations<<":"<<i<<":"<<category<<":";
			rlFile<<aliveNodes[i].peeringStrategyNumber<<":";
			rlFile<<privatePeers<<":"<<publicPeers<<":"<<aliveNodes[i].I.size()<<":"<<aliveNodes[i].J.size()<<":";
			rlFile<<aliveNodes[i].fitness<<":"<<aliveNodes[i].providerCost<<":"<<aliveNodes[i].peerCost<<":"<<aliveNodes[i].customerRevenue<<endl;
		}
	}

}

void printFitness(){

	list<double>::iterator it;
	list<int>::iterator itInt;
	providerFitnessStats();
	cpccFitnessStats();
	stubFitnessStats();
	increaseDecreaseStats();
	providerClassIncreaseDecreaseStats();
	strategyStats();


	ofstream fitnessFile;
	fitnessFile.open("fitness.txt");

	ofstream deltaFitnessFile;
	deltaFitnessFile.open("deltaFitness.txt");


	bool recordFound=false;


	for(int j=0;j<activeNodes;j++){
		recordFound=false;
		for(int i=0;i<3;i++){
			if(fitnessRecord[i][j]!=-1 && !aliveNodes[j].I.empty()){
				recordFound=true;
				fitnessFile<<fitnessRecord[i][j]<<"\t";
			}
		}
		if(recordFound==true){
			fitnessFile<<aliveNodes[j].percentageChangeInFitness<<"\t"<<nodeRecords[j].deltaP<<"\t"<<nodeRecords[j].deltaF<<endl;
			fitnessFile<<endl;
		}
	}

}

bool formCoalition(int type, int size){

	list<int>::iterator itInt;
	list<int>::iterator itInt2;
	list<int>::iterator itInt3;
	int temp=0;
	list<int> allies;

	list<int> potentialAllies;
	list<int> potentialAllies2;
	bool isTier3=true;

	if(type==3){	//form coalitions of Tier-3

		for(int i=0;i<activeNodes;i++)
			if(!aliveNodes[i].I.empty() && aliveNodes[i].Q!=-1){
				isTier3=true;
				for(itInt=aliveNodes[i].I.begin();itInt!=aliveNodes[i].I.end();itInt++){
					if(!aliveNodes[*itInt].I.empty()){
						isTier3=false;
						break;
					}
				}

				if(isTier3==true)
					potentialAllies.push_back(i);

			}

		for(itInt=potentialAllies.begin();itInt!=potentialAllies.end();itInt++){
			potentialAllies2.push_back(*itInt);
			for(itInt2=aliveNodes[*itInt].K.begin();itInt2!=aliveNodes[*itInt].K.end();itInt2++){
				if(isPresentInList(potentialAllies,*itInt2)){
					potentialAllies2.push_back(*itInt2);
				}
			}

			if(potentialAllies2.size()>=size){

				for(itInt2=potentialAllies2.begin();itInt2!=potentialAllies2.end();itInt2++){
					aliveNodes[*itInt2].isInCoalition=true;
				}

#if DEBUG
				logFile<<"Nodes ";
#endif



				for(itInt2=potentialAllies2.begin();itInt2!=potentialAllies2.end();itInt2++){

#if DEBUG
					logFile<<*itInt2<<"\t";
#endif
					for(itInt3=potentialAllies2.begin();itInt3!=potentialAllies2.end();itInt3++){
						if(*itInt2!=*itInt3){
							aliveNodes[*itInt2].allies.push_back(*itInt3);
						}

					}
				}

#if DEBUG
					logFile<<" are now allies"<<endl;
#endif

				break;
			}
		}


	}

	if(type==1){

		//form coalitions of Tier-1

		if(size>Tier1.size())
			return false;

		else{

			for(itInt=Tier1.begin();itInt!=Tier1.end();itInt++){

				if(allies.size()==size)
					break;

				if(!aliveNodes[*itInt].I.empty()){
					allies.push_back(*itInt);
					aliveNodes[*itInt].isInCoalition=true;
				}

			}//end for

			for(itInt=allies.begin();itInt!=allies.end();itInt++){
				for(itInt2=allies.begin();itInt2!=allies.end();itInt2++){
					if(*itInt!=*itInt2){
						aliveNodes[*itInt].allies.push_back(*itInt2);
					}
				}
			}

#if DEBUG
			logFile<<"Node ";
			for(itInt=allies.begin();itInt!=allies.end();itInt++)
				logFile<<*itInt<<"\t";
			logFile<<" are now allies"<<endl;
#endif

			return true;

		}

	}//end if type==1


}

void measureClassMetrics(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations){

	int numProviders=0;
	int numT1=0;
	int numNT1=0;
	int numGP=0;
	int numRP=0;
	int numLP=0;
	int numStubs=0;
	int numCP=0;
	int numCC=0;

	double allNets[7]={0};
	double providers[7]={0};
	double t1[7]={0};
	double nt1[7]={0};
	double gp[7]={0};
	double rp[7]={0};
	double lp[7]={0};
	double stubs[7]={0};
	double cp[7]={0};
	double cc[7]={0};

	for(int i=0;i<activeNodes;i++){

		if(!aliveNodes[i].I.empty()){

			numProviders++;
			if(aliveNodes[i].Q==-1)
				numT1++;
			else
				numNT1++;

			if(aliveNodes[i].category[3]==1)
				numGP++;
			else if(aliveNodes[i].category[3]==2)
				numRP++;
			else if(aliveNodes[i].category[3]==3)
				numLP++;
			else{}

		}

		else
			numStubs++;

		if(aliveNodes[i].category[1]==1)
			numCP++;

		if(aliveNodes[i].category[2]==1)
			numCC++;

	}

	for(int i=0;i<activeNodes;i++){

		allNets[aliveNodes[i].peeringStrategyNumber]++;

		if(!aliveNodes[i].I.empty()){

			providers[aliveNodes[i].peeringStrategyNumber]++;

			if(aliveNodes[i].Q==-1)
				t1[aliveNodes[i].peeringStrategyNumber]++;

			else
				nt1[aliveNodes[i].peeringStrategyNumber]++;


			if(aliveNodes[i].category[3]==1)
				gp[aliveNodes[i].peeringStrategyNumber]++;

			if(aliveNodes[i].category[3]==2)
				rp[aliveNodes[i].peeringStrategyNumber]++;

			if(aliveNodes[i].category[3]==3)
				lp[aliveNodes[i].peeringStrategyNumber]++;

		}

		else{

			if(aliveNodes[i].category[1]==1)
				cp[aliveNodes[i].peeringStrategyNumber]++;

			if(aliveNodes[i].category[2]==1)
				cc[aliveNodes[i].peeringStrategyNumber]++;

			stubs[aliveNodes[i].peeringStrategyNumber]++;
		}

	}

	for(int i=0;i<7;i++){

		if(numProviders>0)
			providers[i]=static_cast<double>(100*providers[i])/numProviders;
		else
			providers[i]=0;

		if(activeNodes>0){

			allNets[i]=static_cast<double>(100*allNets[i])/activeNodes;

		}
		else
			allNets[i]=0;


		if(numT1>0)
			t1[i]=static_cast<double>(100*t1[i])/numT1;
		else
			t1[i]=0;

		if(numNT1>0)
			nt1[i]=static_cast<double>(100*nt1[i])/numNT1;

		else
			nt1[i]=0;

		if(numGP>0)
			gp[i]=static_cast<double>(100*gp[i])/numGP;

		else
			gp[i]=0;

		if(numRP>0)
			rp[i]=static_cast<double>(100*rp[i])/numRP;

		else
			rp[i]=0;

		if(numLP>0)
			lp[i]=static_cast<double>(100*lp[i])/numLP;

		else
			lp[i]=0;

		if(numStubs>0)
			stubs[i]=static_cast<double>(100*stubs[i])/numStubs;

		else
			stubs[i]=0;

		if(numCP>0)
			cp[i]=static_cast<double>(100*cp[i])/numCP;

		else
			cp[i]=0;

		if(numCC>0)
			cc[i]=static_cast<double>(100*cc[i])/numCC;

		else
			cc[i]=0;
	}

	if(equilibriumOccured==true){

		if(isEquilibriumGood==true){
			resultLogFile<<"E:"<<numSimulations<<":G:C:"<<numProviders<<":"<<numT1<<":"<<numNT1<<":"<<numGP<<":"<<numRP<<":"<<numLP<<":"<<numStubs<<":"<<numCP<<":"<<numCC<<endl;
			resultLogFile<<"E:"<<numSimulations<<":G:S:";

			for(int i=0;i<7;i++)
				resultLogFile<<allNets[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<providers[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<t1[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<nt1[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<gp[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<rp[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<lp[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<stubs[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<cp[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<cc[i]<<",";
			resultLogFile<<":";

			resultLogFile<<endl;
		}

		else{
			resultLogFile<<"E:"<<numSimulations<<":B:C:"<<numProviders<<":"<<numT1<<":"<<numNT1<<":"<<numGP<<":"<<numRP<<":"<<numLP<<":"<<numStubs<<":"<<numCP<<":"<<numCC<<endl;

			for(int i=0;i<7;i++)
				resultLogFile<<allNets[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<providers[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<t1[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<nt1[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<gp[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<rp[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<lp[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<stubs[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<cp[i]<<",";
			resultLogFile<<":";

			for(int i=0;i<7;i++)
				resultLogFile<<cc[i]<<",";
			resultLogFile<<":";

			resultLogFile<<endl;

		}
	}

}

void measureRichestNetwork(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations, int innovatedStrategy){

	static list<int> richestId;
	static list<int> richestStrategy;
	list<int>::iterator it;

	double maxFitness=-10000000;
	int fitId;
	int richStrategy;

	if(equilibriumOccured==false){
		for(int i=0;i<activeNodes;i++){
			if(aliveNodes[i].fitness>maxFitness){
				maxFitness=aliveNodes[i].fitness;
				fitId=i;
				richStrategy=aliveNodes[i].peeringStrategyNumber;
			}
		}

		richestId.push_back(fitId);
		richestStrategy.push_back(richStrategy);
	}

	else{

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:R:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:R:";

		if(!richestId.empty()){
			for(it=richestId.begin();it!=richestId.end();it++)
				resultLogFile<<*it<<":";
		}

		else
			resultLogFile<<"X";

		resultLogFile<<endl;

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:RS:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:RS:";

		if(!richestStrategy.empty()){
			for(it=richestStrategy.begin();it!=richestStrategy.end();it++)
				resultLogFile<<*it<<":";
		}

		else
			resultLogFile<<"X";

		resultLogFile<<endl;

	}

}


void measureAvgClassFitness(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations, int innovatedStrategy){

	static list<double> cpFitnessList;
	static list<double> ccFitnessList;
	static list<double> t1FitnessList;
	static list<double> nt1FitnessList;

	list<double>::iterator itD;
	double cpFitness=0;
	double ccFitness=0;
	double t1Fitness=0;
	double nt1Fitness=0;

	int numCP=0;
	int numCC=0;
	int numT1=0;
	int numNT1=0;

	if(equilibriumOccured==false){
		for(int i=0;i<activeNodes;i++){
			if(aliveNodes[i].category[1]==1){
				numCP++;
				cpFitness+=aliveNodes[i].fitness;
			}

			if(aliveNodes[i].category[2]==1){
				numCC++;
				ccFitness+=aliveNodes[i].fitness;
			}

			if(aliveNodes[i].Q==-1 && !aliveNodes[i].I.empty()){
				numT1++;
				t1Fitness+=aliveNodes[i].fitness;
			}

			if(aliveNodes[i].Q!=-1 && !aliveNodes[i].I.empty()){
				numNT1++;
				nt1Fitness+=aliveNodes[i].fitness;
			}


		}

		cpFitnessList.push_back(cpFitness/numCP);
		ccFitnessList.push_back(ccFitness/numCC);
		t1FitnessList.push_back(t1Fitness/numT1);
		nt1FitnessList.push_back(nt1Fitness/numNT1);

	}

	else{

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:CF:CP:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:CF:CP:";

		if(!cpFitnessList.empty())
			for(itD=cpFitnessList.begin();itD!=cpFitnessList.end();itD++){
				resultLogFile<<*itD<<":";
			}
		else
			resultLogFile<<"X";

		resultLogFile<<endl;

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:CF:CC:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:CF:CC:";

		if(!ccFitnessList.empty())
			for(itD=ccFitnessList.begin();itD!=ccFitnessList.end();itD++){
				resultLogFile<<*itD<<":";
			}
		else
			resultLogFile<<"X";

		resultLogFile<<endl;

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:CF:T1:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:CF:T1:";

		if(!t1FitnessList.empty()){
			for(itD=t1FitnessList.begin();itD!=t1FitnessList.end();itD++){
				resultLogFile<<*itD<<":";
			}
		}

		else
			resultLogFile<<"X";

		resultLogFile<<endl;

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:CF:NT1:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:CF:NT1:";

		if(!nt1FitnessList.empty()){
			for(itD=nt1FitnessList.begin();itD!=nt1FitnessList.end();itD++){
				resultLogFile<<*itD<<":";
			}
		}

		else
			resultLogFile<<"X";

		resultLogFile<<endl;



	}


}

void measureProviderStrategies(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations, int innovatedStrategy){

	static list<int> strategyHistory[7];
	int strategyCount[7]={0};
	list<int>::iterator it;

	if(equilibriumOccured==false){
		for(int i=0;i<activeNodes;i++)
			if(!aliveNodes[i].I.empty())
				strategyCount[aliveNodes[i].peeringStrategyNumber]++;

		for(int i=0;i<7;i++)
			strategyHistory[i].push_back(strategyCount[i]);
	}

	else{

		for(int i=0;i<7;i++){

			if(isEquilibriumGood==true)
				resultLogFile<<"E:"<<numSimulations<<":G:SN:";
			else
				resultLogFile<<"E:"<<numSimulations<<":B:SN:";

			resultLogFile<<i<<":";

			if(strategyHistory[i].empty())
				resultLogFile<<"X"<<endl;

			else{

				for(it=strategyHistory[i].begin();it!=strategyHistory[i].end();it++)
					resultLogFile<<*it<<":";

				resultLogFile<<endl;

			}
		}

	}

	list<int>::iterator itI;
	for(int i=0;i<activeNodes;i++){
		if(!aliveNodes[i].I.empty()){

			resultLogFile<<"E:P:"<<i<<":"<<aliveNodes[i].peeringStrategyNumber<<":"<<aliveNodes[i].V<<":C:";
			for(int x=3;x<5;x++)
				resultLogFile<<aliveNodes[i].category[x]<<":";
			resultLogFile<<"O:";
			for(itI=aliveNodes[i].overLap.begin();itI!=aliveNodes[i].overLap.end();itI++)
				if(!aliveNodes[*itI].I.empty())
					resultLogFile<<*itI<<":";
			resultLogFile<<"I:";
			for(itI=aliveNodes[i].I.begin();itI!=aliveNodes[i].I.end();itI++)
				if(!aliveNodes[*itI].I.empty())
					resultLogFile<<*itI<<":";
			resultLogFile<<"J:";
			for(itI=aliveNodes[i].J.begin();itI!=aliveNodes[i].J.end();itI++)
				if(!aliveNodes[*itI].I.empty())
					resultLogFile<<*itI<<":";
			resultLogFile<<"PK:";
			for(itI=aliveNodes[i].K.begin();itI!=aliveNodes[i].K.end();itI++)
				if(!aliveNodes[*itI].I.empty())
					resultLogFile<<*itI<<":";
			resultLogFile<<"SK:";
			for(itI=aliveNodes[i].K.begin();itI!=aliveNodes[i].K.end();itI++)
				if(aliveNodes[*itI].I.empty())
					resultLogFile<<*itI<<":";
			resultLogFile<<"PP:";
			for(itI=aliveNodes[i].overLap.begin();itI!=aliveNodes[i].overLap.end();itI++)
				if(!aliveNodes[i].isPresentInCustomerTree(*itI) && !aliveNodes[*itI].isPresentInCustomerTree(i))
					resultLogFile<<*itI<<":";


			resultLogFile<<endl<<endl;
		}

	}


}


void measureNumAdopters(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations, int innovatorId, int innovatedStrategy){

	static list<int> numAdoptersList;
	static list<double> adoptersFitnessList;
	list<int>::iterator it;
	list<double>::iterator itD;
	int numAdopters=0;
	double adoptersFitness=0;

	if(equilibriumOccured==false){
		for(int i=0;i<activeNodes;i++)
			if(i!=innovatorId && aliveNodes[i].peeringStrategyNumber==innovatedStrategy){
				numAdopters++;
				adoptersFitness+=aliveNodes[i].fitness;
			}

		adoptersFitnessList.push_back(adoptersFitness/numAdopters);
		numAdoptersList.push_back(numAdopters);
	}

	else{

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:AN:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:AN:";

		if(!numAdoptersList.empty()){
			for(it=numAdoptersList.begin();it!=numAdoptersList.end();it++){
				resultLogFile<<*it<<":";
			}
		}

		else
			resultLogFile<<"X";

		resultLogFile<<endl;

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:CF:A:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:CF:A:";

		if(adoptersFitnessList.empty())
			resultLogFile<<"X";

		else{
			for(itD=adoptersFitnessList.begin();itD!=adoptersFitnessList.end();itD++){
				resultLogFile<<*itD<<":";
			}
		}

		resultLogFile<<endl;

	}

}

void measureInnovatorFitness(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations, int innovatorId){

	static list<double> innovatorFitness;
	list<double>::iterator it;

	if(equilibriumOccured==false)
		innovatorFitness.push_back(aliveNodes[innovatorId].fitness);

	else{

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:IF:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:IF:";

		if(!innovatorFitness.empty()){
			for(it=innovatorFitness.begin();it!=innovatorFitness.end();it++){
				resultLogFile<<*it<<":";
			}
		}

		else
			resultLogFile<<"X";

		resultLogFile<<endl;
	}

}

void measureInnovatorCharacteristics(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations, int innovatorId){

	int k=innovatorId;
	if(isEquilibriumGood==true)
		resultLogFile<<"E:"<<numSimulations<<":G:ID:";
	else
		resultLogFile<<"E:"<<numSimulations<<":B:ID:";


	for(int x=0;x<7;x++)
		resultLogFile<<aliveNodes[k].category[x]<<",";

	resultLogFile<<":"<<aliveNodes[k].Vp<<":"<<aliveNodes[k].Vc<<":"<<aliveNodes[k].Vt<<":"<<aliveNodes[k].Vpp<<":";
	resultLogFile<<aliveNodes[k].providerPrice<<":"<<aliveNodes[k].I.size()<<":"<<aliveNodes[k].J.size()<<":"<<aliveNodes[k].K.size()<<":";
	resultLogFile<<aliveNodes[k].fitness<<":"<<aliveNodes[k].deltaFitness<<":"<<aliveNodes[k].peeringStrategyNumber<<":"<<aliveNodes[k].selectionState<<endl;


}

void measureOneTime(){

	static bool firstTime=false;
	list<double> trafficExchange;
	double totalTrafficExchanged=0;
	double temp;
	int arraySize;
	list<double>::iterator itD;
	list<double> trafficGeneration;
	list<double> trafficConsumed;
	list<double> trafficExchange2;
	double* gExpanseCounter;
	int* overlapCounter;

	if(firstTime==false){

		for(int i=1;i<(activeNodes-1);i++)
			for(int j=i+1;j<activeNodes;j++){
				trafficExchange.push_back(trafficMatrix[i][j]+trafficMatrix[j][i]);
				totalTrafficExchanged+=trafficMatrix[i][j]+trafficMatrix[j][i];
			}

		trafficExchange.sort(sortReverse);
		trafficExchange2.push_back(trafficExchange.front());
		temp=trafficExchange.front();

		for(itD=trafficExchange.begin();itD!=trafficExchange.end();itD++){

			if(itD!=trafficExchange.begin()){
				temp+=*itD;
				trafficExchange2.push_back(temp);
			}

		}

		for(itD=trafficExchange2.begin();itD!=trafficExchange2.end();itD++)
			*itD=*itD/totalTrafficExchanged;

		resultLogFile<<"I:TE:";
		for(itD=trafficExchange2.begin();itD!=trafficExchange2.end();itD++)
			resultLogFile<<100*(*itD)<<":";
		resultLogFile<<endl;


		//******* Traffic Generated ****************
		temp=0;
		trafficExchange.clear();
		trafficExchange2.clear();
		totalTrafficExchanged=0;

		for(int i=0;i<activeNodes;i++){
			trafficExchange.push_back(aliveNodes[i].trafficGenerated);
			totalTrafficExchanged+=aliveNodes[i].trafficGenerated;
		}
		trafficExchange.sort(sortReverse);

		trafficExchange2.push_back(trafficExchange.front());
		temp=trafficExchange.front();

		for(itD=trafficExchange.begin();itD!=trafficExchange.end();itD++){

			if(itD!=trafficExchange.begin()){
				temp+=*itD;
				trafficExchange2.push_back(temp);
			}

		}

		for(itD=trafficExchange2.begin();itD!=trafficExchange2.end();itD++)
			*itD=*itD/totalTrafficExchanged;

		resultLogFile<<"I:TG:";
		for(itD=trafficExchange2.begin();itD!=trafficExchange2.end();itD++)
			resultLogFile<<100*(*itD)<<":";
		resultLogFile<<endl;


		//****** Traffic Consumed ***********
		temp=0;
		trafficExchange.clear();
		trafficExchange2.clear();
		totalTrafficExchanged=0;

		for(int i=0;i<activeNodes;i++){
			trafficExchange.push_back(aliveNodes[i].trafficConsumed);
			totalTrafficExchanged+=aliveNodes[i].trafficConsumed;
		}
		trafficExchange.sort(sortReverse);

		trafficExchange2.push_back(trafficExchange.front());
		temp=trafficExchange.front();

		for(itD=trafficExchange.begin();itD!=trafficExchange.end();itD++){

			if(itD!=trafficExchange.begin()){
				temp+=*itD;
				trafficExchange2.push_back(temp);
			}

		}

		for(itD=trafficExchange2.begin();itD!=trafficExchange2.end();itD++)
			*itD=*itD/totalTrafficExchanged;

		resultLogFile<<"I:TC:";
		for(itD=trafficExchange2.begin();itD!=trafficExchange2.end();itD++)
			resultLogFile<<100*(*itD)<<":";
		resultLogFile<<endl;

		//****** geographic expanse *********//
		temp=0;
		trafficExchange.clear();
		trafficExchange2.clear();
		totalTrafficExchanged=0;
		double pops=0;
		gExpanseCounter=new double[maxRegions*maxRegions+1];

		for(int i=0;i<(maxRegions*maxRegions+1);i++)
			gExpanseCounter[i]=0;

		for(int i=0;i<activeNodes;i++){
			gExpanseCounter[aliveNodes[i].numGPresence]++;

		}

		pops=gExpanseCounter[1];
		for(int i=2;i<(maxRegions*maxRegions+1);i++){
			gExpanseCounter[i]+=gExpanseCounter[i-1];
			pops+=gExpanseCounter[i];
		}

		resultLogFile<<"I:G:";
		for(int i=1;i<(maxRegions*maxRegions+1);i++)
			resultLogFile<<(gExpanseCounter[i]*100)/activeNodes<<":";
		resultLogFile<<endl;

		int total=static_cast<int>(ceil(activeNodes*(activeNodes-1)/2));
		overlapCounter= new int[total];
		for(int i=0;i<total;i++)
			overlapCounter[i]=0;
		for(int i=0;i<activeNodes;i++)
			overlapCounter[aliveNodes[i].overLap.size()]++;
		pops=overlapCounter[0];
		for(int i=1;i<total;i++)
			overlapCounter[i]+=overlapCounter[i-1];

		resultLogFile<<"I:O:";
		for(int i=0;i<total;i++)
			resultLogFile<<(overlapCounter[i]*100)/activeNodes<<":";
		resultLogFile<<endl;



	}

	delete []gExpanseCounter;

}

void measureTrafficMetrics(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations){

	double transitTrafficT1=0;
	double transitTrafficNonT1=0;
	double peeringTraffic=0;
	double t1TransitTrafficRatio=0;
	double t1PeeringTraffic=0;
	double t1VtTrafficFraction=0;
	double nt1VtTrafficFraction=0;

	for(int i=0;i<activeNodes;i++){

		if(aliveNodes[i].Q==-1 && !aliveNodes[i].I.empty()){
			transitTrafficT1+=aliveNodes[i].Vt;
		}

		if(!aliveNodes[i].I.empty() && aliveNodes[i].Q!=-1){
			transitTrafficNonT1+=aliveNodes[i].Vt;
		}
	}

	if(transitTrafficNonT1!=0)
		t1TransitTrafficRatio=transitTrafficT1/transitTrafficNonT1;
	else
		t1TransitTrafficRatio=-1;

	peeringTraffic=measurePeeringTraffic();

	t1PeeringTraffic=measureT1PeeringTraffic();

	t1VtTrafficFraction=measureT1VtTrafficFraction();

	nt1VtTrafficFraction=measureNT1VtTrafficFraction();


	if(equilibriumOccured==false)
		resultLogFile<<"R:"<<numSimulations<<":"<<rounds<<":F:"<<peeringTraffic<<":"<<t1TransitTrafficRatio<<":"<<t1PeeringTraffic<<":"<<t1VtTrafficFraction<<":"<<nt1VtTrafficFraction<<endl;
	else{

		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:F:"<<peeringTraffic<<":"<<t1TransitTrafficRatio<<":"<<t1PeeringTraffic<<":"<<t1VtTrafficFraction<<":"<<nt1VtTrafficFraction<<endl;
		else
			resultLogFile<<"E:"<<numSimulations<<":B:F:"<<peeringTraffic<<":"<<t1TransitTrafficRatio<<":"<<t1PeeringTraffic<<":"<<t1VtTrafficFraction<<":"<<nt1VtTrafficFraction<<endl;
	}

}

void displayProviderGraph(int numSimulations){

	list<int>::iterator it;

	logFile<<"Provider Graph at "<<numSimulations<<endl;

	logFile<<"Tier1: ";
	for(it=Tier1.begin();it!=Tier1.end();it++)
		if(!aliveNodes[*it].I.empty())
			logFile<<*it<<"\t";

	logFile<<endl;

	for(int i=0;i<activeNodes;i++){
		if(!aliveNodes[i].I.empty()){
			logFile<<"Provider: "<<i<<endl;

			logFile<<"I: ";
			for(it=aliveNodes[i].I.begin();it!=aliveNodes[i].I.end();it++)
				if(!aliveNodes[*it].I.empty())
					logFile<<*it<<"\t";

			logFile<<endl;

			logFile<<"J: ";
			for(it=aliveNodes[i].J.begin();it!=aliveNodes[i].J.end();it++)
				if(!aliveNodes[*it].I.empty())
					logFile<<*it<<"\t";

			logFile<<endl;

			logFile<<"K: ";
			for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++)
				if(!aliveNodes[*it].I.empty())
					logFile<<*it<<"\t";

			logFile<<endl;


		}
	}

}

void measureNetworkCharacteristics(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations){


	for(int k=0;k<activeNodes;k++){

		if(equilibriumOccured==true){

			if(isEquilibriumGood==true)
				resultLogFile<<"E:"<<numSimulations<<":G:N:"<<k<<":";
			else
				resultLogFile<<"E:"<<numSimulations<<":B:N:"<<k<<":";
		}

		else{
			resultLogFile<<"R:"<<numSimulations<<":"<<rounds+1<<":N:"<<k<<":";
		}

		for(int x=0;x<7;x++)
			resultLogFile<<aliveNodes[k].category[x]<<",";

		resultLogFile<<":"<<aliveNodes[k].Vp<<":"<<aliveNodes[k].Vc<<":"<<aliveNodes[k].Vt<<":"<<aliveNodes[k].Vpp<<":";
		resultLogFile<<aliveNodes[k].providerPrice<<":"<<aliveNodes[k].I.size()<<":"<<aliveNodes[k].J.size()<<":"<<aliveNodes[k].K.size()<<":";
		resultLogFile<<aliveNodes[k].fitness<<":"<<aliveNodes[k].deltaFitness<<":"<<aliveNodes[k].peeringStrategyNumber<<":"<<aliveNodes[k].selectionState<<":"<<aliveNodes[k].stateProbability<<endl;

	}


}

void measureTopologicalMetrics(int numSimulations){

	int diameter=0;
	double avgPathLength=0;
	int numPaths=0;
	int numStubs=0;
	static int numTotalPossibleLinks=0;
	int totalLinks=0;
	int numCPLinks=0;
	int numPPLinks=0;
	double density=0;
	double transitTrafficT1=0;
	double transitTrafficNonT1=0;
	double t1TransitTrafficRatio=0;
	list<int>::iterator itInt;
	double peeringTraffic;
	double t1PeeringTraffic;
	double peeringClusteringCoefficient[500]={0};
	double networkPeeringClusteringCoefficient=0;
	list<int>::iterator it1;
	list<int>::iterator it2;
	double t1VtFraction;
	double nt1VtFraction;
	int maxTreeHeight=0;
	int maxCustomerConeSize=0;
	int minCustomerConeSize=activeNodes+1;
	list<int> degreeDistribution;
	double temp=0;
	double totalTraffic=0;
	unsigned int numLinks=0;
	double plainPath=0;

	double betweennessCentrality[500]={0};
	double totalPaths=0;

	/*
	for(int i=0;i<(activeNodes-1);i++){
		for(int j=i+1;j<activeNodes;j++){

		}
	}
	*/

	for(int i=0;i<activeNodes;i++){
		if(!aliveNodes[i].I.empty()){
			numProviders[numSimulations]++;

			if(aliveNodes[i].Q==-1){
				numT1[numSimulations]++;
				t1VtFraction+=aliveNodes[i].Vt;
			}

			else{
				nt1VtFraction+=aliveNodes[i].Vt;

				if(aliveNodes[aliveNodes[i].Q].Q==-1)
					numT2[numSimulations]++;
				else
					numT3[numSimulations]++;
			}


		}

		if(aliveNodes[i].isMajorContentNet==true)
			numCPCC[numSimulations]++;

		if(aliveNodes[i].Q==-1 && !aliveNodes[i].J.empty()){

			for(it1=aliveNodes[i].J.begin();it1!=aliveNodes[i].J.end();it1++){

				if(routingMatrixScale[flowIndex[i][*it1]].size()>maxTreeHeight)
					maxTreeHeight=routingMatrixScale[flowIndex[i][*it1]].size();

			}

		}
	}


	t1Nt1TransitRatio[numSimulations]=t1VtFraction/nt1VtFraction;
	treeHeight[numSimulations]=maxTreeHeight;

	for(int i=0;i<maxFlows;i++){
		if(!routingMatrixScale[i].empty()){

			if(routingMatrixScale[i].size()>diameter)
				diameter=routingMatrixScale[i].size();

			if(routingMatrixScaleAsym[i].size()>diameter)
				diameter=routingMatrixScaleAsym[i].size();

		}

		else
			break;
	}//end diameter for

	networkDiameter[numSimulations]=diameter;

	temp=0;
	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++){
			if(flowIndex[i][j]!=-1){

				totalTraffic+=(trafficMatrix[i][j]+trafficMatrix[j][i]);

				if(aliveNodes[i].isPeer(j)){
					temp+=(trafficMatrix[i][j]+trafficMatrix[j][i]);
				}

				numPaths+=2;

				plainPath+=(routingMatrixScale[flowIndex[i][j]].size()+routingMatrixScaleAsym[flowIndex[i][j]].size());

				if(flowDirectionFrom[flowIndex[i][j]]==i){
					avgPathLength+=(routingMatrixScale[flowIndex[i][j]].size()*trafficMatrix[i][j]);
					avgPathLength+=(routingMatrixScaleAsym[flowIndex[i][j]].size()*trafficMatrix[j][i]);

				}

				else{
					avgPathLength+=(routingMatrixScale[flowIndex[i][j]].size()*trafficMatrix[j][i]);
					avgPathLength+=(routingMatrixScaleAsym[flowIndex[i][j]].size()*trafficMatrix[i][j]);

				}
			}

		}

	avgPlainPathLength[numSimulations]=plainPath/numPaths;
	avgWeightedPathLength[numSimulations]=avgPathLength/totalTraffic;
	peeringTrafficOnly[numSimulations]=(temp/totalTraffic)*100;

	//density & num links
	if(numTotalPossibleLinks==0){
		for(int i=0;i<activeNodes;i++)
			for(itInt=aliveNodes[i].overLap.begin();itInt!=aliveNodes[i].overLap.end();itInt++)
				if(*itInt>i)
					numTotalPossibleLinks++;
	}

	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++)
			if(linkIndex[i][j].index!=-1){

				numLinks++;
				if(linkIndex[i][j].linkClass==CPLink)
					numCPLinks++;
				else
					numPPLinks++;
			}

	linkDensity[numSimulations]=static_cast<double>(numLinks)/static_cast<double>(numTotalPossibleLinks);

	for(int i=0;i<activeNodes;i++){
		if(aliveNodes[i].K.size()>=2){

			for(it1=aliveNodes[i].K.begin();it1!=aliveNodes[i].K.end();it1++)
				for(it2=aliveNodes[i].K.begin();it2!=aliveNodes[i].K.end();it2++)
					if(*it1!=*it2 && *it2>*it1){
						if(aliveNodes[*it1].isPeer(*it2))
							peeringClusteringCoefficient[i]++;
					}

			peeringClusteringCoefficient[i]=(2*peeringClusteringCoefficient[i])/(aliveNodes[i].K.size()*(aliveNodes[i].K.size()-1));

		}
	}

	for(int i=0;i<activeNodes;i++)
		networkPeeringClusteringCoefficient+=peeringClusteringCoefficient[i];

	networkPeeringClusteringCoefficient=networkPeeringClusteringCoefficient/activeNodes;

	ppClusteringCoefficient[numSimulations]=networkPeeringClusteringCoefficient;

}

void measureLinkClassificationMetrics(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations){

	int cp_cc=0;
	int cp_t1=0;
	int cp_nt1=0;
	int cc_t1=0;
	int cc_nt1=0;
	int t1_t1=0;
	int t1_nt1=0;
	int nt1_nt1=0;

	if(equilibriumOccured==true && isEquilibriumGood==true){

		for(int i=0;i<activeNodes-1;i++)
			for(int j=i+1;j<activeNodes;j++){

				if(aliveNodes[i].isPeer(j)){

					if((aliveNodes[i].category[1]==1 && aliveNodes[j].category[2]==1) || (aliveNodes[j].category[1]==1 && aliveNodes[i].category[2]==1)){
						cp_cc++;
					}

					if((aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==1 && aliveNodes[j].category[1]==1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].category[4]==1 && aliveNodes[i].category[1]==1)){
						cp_t1++;
					}

					if((aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==0 && aliveNodes[j].category[1]==1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].category[4]==0 && aliveNodes[i].category[1]==1)){
						cp_nt1++;
					}

					if((aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==1 && aliveNodes[j].category[2]==1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].category[4]==1 && aliveNodes[i].category[2]==1)){
						cc_t1++;
					}

					if((aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==0 && aliveNodes[j].category[2]==1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].category[4]==0 && aliveNodes[i].category[2]==1)){
						cc_nt1++;
					}

					if(aliveNodes[i].category[0]==1 && aliveNodes[i].Q==-1 && aliveNodes[j].category[0]==1 && aliveNodes[j].Q==-1){
						t1_t1++;
					}

					if((aliveNodes[i].category[0]==1 && aliveNodes[i].Q==-1 && aliveNodes[j].category[0]==1 && aliveNodes[j].Q!=-1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].Q==-1 && aliveNodes[i].category[0]==1 && aliveNodes[i].Q!=-1)){
						t1_nt1++;
					}

					if(aliveNodes[i].category[0]==1 && aliveNodes[i].Q!=-1 && aliveNodes[j].category[0]==1 && aliveNodes[j].Q!=-1){
						nt1_nt1++;
					}

				}

			}

		resultLogFile<<"E:"<<numSimulations<<":G:L:"<<cp_cc<<":"<<cp_t1<<":"<<cp_nt1<<":"<<cc_t1<<":"<<cc_nt1<<":"<<t1_t1<<":"<<t1_nt1<<":"<<nt1_nt1<<endl;

	}//end if
}

double estimateTraffic(int from, int to){

	list<int> startList;
	list<int> endList;
	list<int> startRemove;
	list<int> endRemove;
	list<int>::iterator it;
	list<int>::iterator itToRemove;
	list<twoPair> pairs;
	list<twoPair>::iterator itPair;
	list<twoPair>::iterator itPairRemove;
	twoPair tmpPair;
	list<twoPair> pairToRemove;
	double trafficExchange=0;
	list<int> linksTraversed;
	double existingCost=0;
	double potentialCost=0;
	int numPeeringLinksTraversed=0;
	int angelPeer=-1;
	list<int>::iterator itStart;
	list<int>::iterator itEnd;
	list<int> linkIndexList;

#if 0
	logFile<<"Estimating traffic exchange between "<<from<<" and "<<to<<endl;
#endif

	mergeTwoListsScale(startList,aliveNodes[from].J);
	mergeTwoListsScale(endList,aliveNodes[to].J);

	startList.push_front(from);
	endList.push_front(to);

	for(it=aliveNodes[from].I.begin();it!=aliveNodes[from].I.end();it++)
		linkIndexList.push_back(linkIndex[from][*it].index);

	for(it=aliveNodes[to].I.begin();it!=aliveNodes[to].I.end();it++)
			linkIndexList.push_back(linkIndex[to][*it].index);

	//**********************************
	//**********************************

	for(itStart=startList.begin();itStart!=startList.end();itStart++){
		for(itEnd=endList.begin();itEnd!=endList.end();itEnd++){

		//	cout<<"Pair "<<*itStart<<","<<*itEnd<<": "<<trafficMatrix[*itStart][*itEnd]<<endl;

			if(!aliveNodes[*itStart].isPeer(*itEnd) && !aliveNodes[from].isPeer(*itEnd) && !aliveNodes[to].isPeer(*itStart)){

			//	cout<<"Pair passed check 1"<<endl;

				if(aliveNodes[to].isPresentInCustomerTree(aliveNodes[from].isPresentInCustomerTreeOfPeer(*itEnd))){}

				else{

				//	cout<<"Pair passed check 2"<<endl;

					if(flowDirectionFrom[flowIndex[*itStart][*itEnd]]==*itStart){

						for(it=linkIndexList.begin();it!=linkIndexList.end();it++){

							if(isPresentInList(routingMatrixScale[flowIndex[*itStart][*itEnd]],*it)){

//								cout<<"Pair passed check 3"<<endl;
								trafficExchange+=trafficMatrix[*itStart][*itEnd];
//								cout<<"Adding "<<trafficMatrix[*itStart][*itEnd]<<endl;

								break;
							}

						}
					}

					else{

						for(it=linkIndexList.begin();it!=linkIndexList.end();it++){

							if(isPresentInList(routingMatrixScaleAsym[flowIndex[*itStart][*itEnd]],*it)){

	//							cout<<"Pair passed check 3"<<endl;
	//							cout<<"Adding "<<trafficMatrix[*itStart][*itEnd]<<endl;
								trafficExchange+=trafficMatrix[*itStart][*itEnd];


								break;
							}

						}
					}
				}
			}


		}
	}

	/*
	cout<<"Pair "<<from<<","<<to<<": "<<trafficMatrix[from][to]<<endl;
	*/
	//cout<<"Adding "<<trafficMatrix[from][to]<<endl;
	trafficExchange+=trafficMatrix[from][to];

	return trafficExchange;


	//**********************************
	//**********************************


	for(it=endList.begin();it!=endList.end();it++)
		if(aliveNodes[from].isPeer(*it)){
			endRemove.push_back(*it);
			mergeTwoListsScale(endRemove,aliveNodes[*it].J);
		}

	for(it=endRemove.begin();it!=endRemove.end();it++)
		endList.remove(*it);

	for(it=startList.begin();it!=startList.end();it++)
		if(aliveNodes[to].isPeer(*it)){
			startRemove.push_back(*it);
			mergeTwoListsScale(startRemove,aliveNodes[*it].J);
		}

	for(it=startRemove.begin();it!=startRemove.end();it++)
		startList.remove(*it);

	startList.push_front(from);
	endList.push_front(to);

	if(!aliveNodes[from].K.empty()){
		for(it=aliveNodes[from].K.begin();it!=aliveNodes[from].K.end();it++)
			if(!aliveNodes[to].isPresentInCustomerTree(*it))
				linksTraversed.push_back(linkIndex[from][*it].index);
	}

	if(aliveNodes[from].Q!=-1)
		linksTraversed.push_back(linkIndex[from][aliveNodes[from].Q].index);

	for(it=startList.begin();it!=startList.end();it++)
		for(itToRemove=endList.begin();itToRemove!=endList.end();itToRemove++){

#if 0
			logFile<<"Creating pair "<<*it<<" and "<<*itToRemove<<endl;
#endif

			tmpPair.n1=flowIndex[*it][*itToRemove];
			tmpPair.n2=static_cast<int>(trafficMatrix[*it][*itToRemove]+trafficMatrix[*itToRemove][*it]);

			tmpPair.start=*it;
			tmpPair.end=*itToRemove;

			pairs.push_back(tmpPair);

		}

	for(itPair=pairs.begin();itPair!=pairs.end();itPair++)
		for(it=linksTraversed.begin();it!=linksTraversed.end();it++){

			if(trafficMatrix[(*itPair).start][(*itPair).end]==trafficMatrix[(*itPair).end][(*itPair).start]){

				if(flowDirectionFrom[(*itPair).n1]==(*itPair).start){
					if(isPresentInList(routingMatrixScale[(*itPair).n1],*it)){
						trafficExchange+=flowValueVector[(*itPair).n1];
#if 0
						logFile<<"Node "<<(*itPair).start<<" sends traffic "<<flowValueVector[(*itPair).n1]<<" to "<<(*itPair).end<<endl;
#endif

					}
				}

				else if(flowDirectionFromAsym[(*itPair).n1]==(*itPair).start){
					if(isPresentInList(routingMatrixScaleAsym[(*itPair).n1],*it)){
						trafficExchange+=flowValueVectorAsym[(*itPair).n1];
#if 0
						logFile<<"Node "<<(*itPair).start<<" sends traffic "<<flowValueVector[(*itPair).n1]<<" to "<<(*itPair).end<<endl;
#endif


					}
				}

				else{
					cout<<"ERROR in traffic estimation"<<endl;
					string str="ERROR!! Traffic estimation caused error when traffic in both directions was equal";
					endSimulation(str);
				}

			}//end if

			else{

				if(flowDirectionFrom[(*itPair).n1]==(*itPair).start){
					if(isPresentInList(routingMatrixScale[(*itPair).n1],*it)){
						trafficExchange+=flowValueVector[(*itPair).n1];
#if 0
						logFile<<"Node "<<(*itPair).start<<" sends traffic "<<flowValueVector[(*itPair).n1]<<" to "<<(*itPair).end<<endl;
#endif

					}
				}

				else if(flowDirectionFromAsym[(*itPair).n1]==(*itPair).start){
					if(isPresentInList(routingMatrixScaleAsym[(*itPair).n1],*it)){
						trafficExchange+=flowValueVectorAsym[(*itPair).n1];

#if 0
						logFile<<"Node "<<(*itPair).start<<" sends traffic "<<flowValueVector[(*itPair).n1]<<" to "<<(*itPair).end<<endl;
#endif


					}
				}

				else{
					cout<<"ERROR in traffic estimation"<<endl;
					string str="ERROR!!! Traffic estimation error. Traffic estimation caused error when traffic in both directions was not equal";
					logFile<<"flowDirectionFrom["<<(*itPair).n1<<"]: "<<flowDirectionFrom[(*itPair).n1]<<endl;
					logFile<<"flowDirectionFromAsym["<<(*itPair).n1<<"]: "<<flowDirectionFromAsym[(*itPair).n1]<<endl;
					endSimulation(str);
				}

			}//end else

		}//end for

	return trafficExchange;
}

double estimateTrafficExchange(int from, int to){

	return (estimateTraffic(from,to)+estimateTraffic(to,from));

}

double checkRoutingMatrixScale(int flowIndex,int start,int end){

	list<int>::iterator itR;
	double peerTraffic=0;

	for(itR=routingMatrixScale[flowIndex].begin();itR!=routingMatrixScale[flowIndex].end();itR++){

		for(int i=0;i<activeNodes-1;i++)
			for(int j=i+1;j<activeNodes;j++){

				if(linkIndex[i][j].index==*itR){

					if((i==start && aliveNodes[j].Q==-1) || (j==end && aliveNodes[i].Q==-1)){

						if(flowDirectionFrom[flowIndex]==start)
							return peerTraffic+=trafficMatrix[start][end];

						else
							return peerTraffic+=trafficMatrix[end][start];
					}

					if(i!=start && j!=end && (aliveNodes[i].Q==-1 || aliveNodes[j].Q==-1)){

						if(flowDirectionFrom[flowIndex]==start)
							return peerTraffic+=trafficMatrix[start][end];

						else
							return peerTraffic+=trafficMatrix[end][start];

					}

				}

			}//end for

	}//end for

	return peerTraffic;


}

double checkRoutingMatrixScaleAsym(int flowIndex,int start,int end){

	list<int>::iterator itR;
	double peerTraffic=0;

	for(itR=routingMatrixScaleAsym[flowIndex].begin();itR!=routingMatrixScaleAsym[flowIndex].end();itR++){

		for(int i=0;i<activeNodes-1;i++)
			for(int j=i+1;j<activeNodes;j++){

				if(linkIndex[i][j].index==*itR){

					if((i==start && aliveNodes[j].Q==-1) || (j==end && aliveNodes[i].Q==-1)){

						if(flowDirectionFromAsym[flowIndex]==start)
							return peerTraffic+=trafficMatrix[start][end];

						else
							return peerTraffic+=trafficMatrix[end][start];
					}

					if(i!=start && j!=end && (aliveNodes[i].Q==-1 || aliveNodes[j].Q==-1)){

						if(flowDirectionFrom[flowIndex]==start)
							return peerTraffic+=trafficMatrix[start][end];

						else
							return peerTraffic+=trafficMatrix[end][start];

					}

				}

			}//end for

	}//end for

	return peerTraffic;
}

double checkRoutingMatrixScaleNT1(int flowIndex,int start,int end){

	double peerTraffic=0;
	list<int>::iterator itR;

	for(itR=routingMatrixScale[flowIndex].begin();itR!=routingMatrixScale[flowIndex].end();itR++){

		for(int i=0;i<activeNodes-1;i++)
			for(int j=i+1;j<activeNodes;j++){

				if(linkIndex[i][j].index==*itR){

					if((i==start && aliveNodes[j].isImmediateCustomer(i)) || (j==end && aliveNodes[i].isImmediateCustomer(j))){

						if(flowDirectionFrom[flowIndex]==start)
							return peerTraffic+=trafficMatrix[start][end];

						else
							return peerTraffic+=trafficMatrix[end][start];
					}

					if(i!=start && j!=end && (!aliveNodes[i].I.empty() || !aliveNodes[j].I.empty())){

						if(flowDirectionFrom[flowIndex]==start)
							return peerTraffic+=trafficMatrix[start][end];

						else
							return peerTraffic+=trafficMatrix[end][start];

					}

				}

			}//end for

	}//end for

	return peerTraffic;

}

double checkRoutingMatrixScaleAsymNT1(int flowIndex,int start,int end){

	list<int>::iterator itR;
	double peerTraffic=0;

	for(itR=routingMatrixScaleAsym[flowIndex].begin();itR!=routingMatrixScaleAsym[flowIndex].end();itR++){

		for(int i=0;i<activeNodes-1;i++)
			for(int j=i+1;j<activeNodes;j++){

				if(linkIndex[i][j].index==*itR){

					if((i==start && aliveNodes[j].isImmediateCustomer(i)) || (j==end && aliveNodes[i].isImmediateCustomer(j))){

						if(flowDirectionFromAsym[flowIndex]==start)
							return peerTraffic+=trafficMatrix[start][end];

						else
							return peerTraffic+=trafficMatrix[end][start];
					}

					if(i!=start && j!=end && (!aliveNodes[i].I.empty() || !aliveNodes[j].I.empty())){

						if(flowDirectionFromAsym[flowIndex]==start)
							return peerTraffic+=trafficMatrix[start][end];

						else
							return peerTraffic+=trafficMatrix[end][start];

					}

				}

			}//end for

	}//end for

	return peerTraffic;

}

double checkIfT1Transitted(int flowIndex,int start, int end){

	double peerTraffic=0;

	peerTraffic+=checkRoutingMatrixScale(flowIndex,start,end);
	peerTraffic+=checkRoutingMatrixScaleAsym(flowIndex,start,end);

	return peerTraffic;

}

double checkIfNT1Transitted(int flowIndex,int start, int end){

	double peerTraffic=0;

	peerTraffic+=checkRoutingMatrixScaleNT1(flowIndex,start,end);
	peerTraffic+=checkRoutingMatrixScaleAsymNT1(flowIndex,start,end);

	return peerTraffic;

}


double measureT1VtTrafficFraction(){

	double density=0;
	double peerTraffic=0;
	double totalTraffic=0;

	for(int i=0;i<activeNodes-1;i++)
		for(int j=i+1;j<activeNodes;j++){

			if(linkIndex[i][j].index==-1){

				peerTraffic+=checkIfT1Transitted(flowIndex[i][j],i,j);

			}//end if

		}//end for


	for(int i=0;i<activeNodes;i++)
		totalTraffic+=aliveNodes[i].trafficGenerated;

	density=(peerTraffic/totalTraffic)*100;

	return density;

}

double measureNT1VtTrafficFraction(){

	double density=0;
	double peerTraffic=0;
	double totalTraffic=0;

	for(int i=0;i<activeNodes-1;i++)
		for(int j=i+1;j<activeNodes;j++){

			if(linkIndex[i][j].index==-1){

				peerTraffic+=checkIfNT1Transitted(flowIndex[i][j],i,j);

			}//end if

		}//end for


	for(int i=0;i<activeNodes;i++)
		totalTraffic+=aliveNodes[i].trafficGenerated;

	density=(peerTraffic/totalTraffic)*100;

	return density;

}

double measureT1PeeringTraffic(){

	double density=0;
	double peerTraffic=0;
	double totalTraffic=0;

	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++)
			if(aliveNodes[i].Q==-1 && aliveNodes[j].Q==-1){
				peerTraffic+=linkValueVector[linkIndex[i][j].index];
			}


	for(int i=0;i<activeNodes;i++)
		totalTraffic+=aliveNodes[i].trafficGenerated;

	density=(peerTraffic/totalTraffic)*100;

	return density;
}



double measurePeeringTraffic(){

	double density=0;
	double peerTraffic=0;
	double totalTraffic=0;

	for(int i=0;i<(activeNodes-1);i++)
		for(int j=i+1;j<activeNodes;j++)
			if(linkIndex[i][j].index!=-1 && (linkIndex[i][j].linkClass==PPLink || linkIndex[i][j].linkClass==PPPLink)){
				peerTraffic+=trafficMatrix[i][j]+trafficMatrix[j][i];
			}

	for(int i=0;i<activeNodes;i++)
		totalTraffic+=aliveNodes[i].trafficGenerated;

	density=(peerTraffic/totalTraffic)*100;

	return density;
}

void measureStrategyShifts(bool equilibriumOccured, int steady, int innovate, int imitate,int fittestNode, bool isEquilibriumGood, int numSimulations){


	double strategyLog[15][15]={0};
	double sum=0;

	for(int i=0;i<activeNodes;i++){

		if(aliveNodes[i].category[0]==0)
			strategyLog[aliveNodes[i].peeringStrategyNumber][0]++;			//stub
		else
			strategyLog[aliveNodes[i].peeringStrategyNumber][1]++;			//provider

		if(aliveNodes[i].category[1]==1 || aliveNodes[i].category[1]==2)	//CP
			strategyLog[aliveNodes[i].peeringStrategyNumber][2]++;

		if(aliveNodes[i].category[2]==1 || aliveNodes[i].category[2]==2)	//CC
			strategyLog[aliveNodes[i].peeringStrategyNumber][3]++;

		if(aliveNodes[i].category[3]==1)
			strategyLog[aliveNodes[i].peeringStrategyNumber][4]++;			//GP

		if(aliveNodes[i].category[3]==2)
			strategyLog[aliveNodes[i].peeringStrategyNumber][5]++;			//RP

		if(aliveNodes[i].category[3]==3)
			strategyLog[aliveNodes[i].peeringStrategyNumber][6]++;			//LP

		if(aliveNodes[i].category[4]==2)									//T1P
			strategyLog[aliveNodes[i].peeringStrategyNumber][7]++;

		if(aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==0)
			strategyLog[aliveNodes[i].peeringStrategyNumber][8]++;			//Non-T1P


		if(aliveNodes[i].category[6]==0 )
			strategyLog[aliveNodes[i].peeringStrategyNumber][9]++;			//HighPrice

		if(aliveNodes[i].category[6]==1)
			strategyLog[aliveNodes[i].peeringStrategyNumber][10]++;			//LowPrice


	}//end for

	if(equilibriumOccured==false){
		resultLogFile<<"R:"<<rounds<<":P:";
	}

	else{
		if(isEquilibriumGood==true)
			resultLogFile<<"E:"<<numSimulations<<":G:P:";
		else
			resultLogFile<<"E:"<<numSimulations<<":B:P:";
	}

	if(fittestNode!=-1)
		resultLogFile<<aliveNodes[fittestNode].peeringStrategyNumber<<":";
	else
		resultLogFile<<"-1:";

	for(int i=0;i<11;i++){
		sum=0;

		for(int j=0;j<totalPeeringStrategies;j++){
			sum+=strategyLog[j][i];
		}

		for(int k=0;k<totalPeeringStrategies;k++){

			if(sum>0)
				strategyLog[k][i]=100*strategyLog[k][i]/sum;

			if(k<(totalPeeringStrategies-1)){
				resultLogFile<<strategyLog[k][i]<<",";
			}

			else{
				resultLogFile<<strategyLog[k][i]<<";"<<sum<<":";
			}

		}

	}

	resultLogFile<<endl;

}

int findMinConsumedTraffic(int i){

	double traffic=1000000000;
	int found;

	for(int j=0;j<activeNodes;j++){
		if(j!=i){
			if(aliveNodes[j].trafficConsumed<traffic){
				traffic=aliveNodes[j].trafficConsumed;
				found=j;
			}
		}
	}

	return found;
}

double findExchangeBetweenProviders(){

	double exchange=0;

	for(int i=0;i<activeNodes-1;i++)
		for(int j=i+1;j<activeNodes;j++){
			if(!aliveNodes[i].I.empty() && !aliveNodes[j].I.empty() && linkIndex[i][j].index!=-1){

				if(aliveNodes[i].isPeer(j)){
					//they are peers
					//exchange+=(aliveNodes[i].peeringCostMultiplier*pow(linkValueVector[linkIndex[i][j].index],aliveNodes[i].peeringExponent));

				}

				else{
					//they have a CP CC relationship
					if(aliveNodes[i].Q==j){
						//i is a customer of j
						exchange+=(aliveNodes[j].price*pow(linkValueVector[linkIndex[i][j].index],aliveNodes[j].providerExponent));
					}

					else{
						//j is a customer of i
						exchange+=(aliveNodes[i].price*pow(linkValueVector[linkIndex[i][j].index],aliveNodes[i].providerExponent));
					}
				}
			}
		}

	return exchange;
}


void computeEconomicStats(int numSimulations){


	double maxProviderFitness=0;
	double minProviderFitness=1000000000;
	double cumulativeProviderFitness=0;
	double cumulativeStubFitness=0;
	double exchangeBetweenProviders=0;
	double totalStubTraffic=0;
	double totalProviderTraffic=0;

	for(int i=0;i<activeNodes;i++){
		if(!aliveNodes[i].I.empty()){
			marshillianEfficiency[numSimulations-1]+=aliveNodes[i].fitness;

			if(aliveNodes[i].fitness>maxProviderFitness)
				maxProviderFitness=aliveNodes[i].fitness;

			if(aliveNodes[i].fitness<minProviderFitness)
				minProviderFitness=aliveNodes[i].fitness;

			cumulativeProviderFitness+=aliveNodes[i].fitness;

			totalProviderTraffic+=(aliveNodes[i].trafficConsumed+aliveNodes[i].trafficGenerated+aliveNodes[i].Vt);
		}

		else{
			cumulativeStubFitness+=aliveNodes[i].fitness;
			totalStubTraffic+=(aliveNodes[i].trafficGenerated+aliveNodes[i].trafficConsumed);
		}
	}

	disparity[numSimulations-1]=maxProviderFitness-minProviderFitness;
	efficiency[numSimulations-1]=cumulativeProviderFitness/(-1*cumulativeStubFitness);

	exchangeBetweenProviders=findExchangeBetweenProviders();

	exchangeBetweenProviders=exchangeBetweenProviders/(-1*cumulativeStubFitness);
	competitiveness[numSimulations-1]=exchangeBetweenProviders;

	stubCostsMbps[numSimulations-1]=(-1*cumulativeStubFitness)/totalStubTraffic;
	providerFitnessMbps[numSimulations-1]=cumulativeProviderFitness/totalProviderTraffic;

	if(numSimulations==2){

		ofstream mEfficiencyFile;
		mEfficiencyFile.open("marshillian.txt",ios::out | ios::app);

		ofstream disparityFile;
		disparityFile.open("disparityFile.txt",ios::out | ios::app);

		ofstream efficiencyFile;
		efficiencyFile.open("efficiencyFile.txt",ios::out | ios::app);

		ofstream competitivenessFile;
		competitivenessFile.open("competitiveness.txt",ios::out | ios::app);

		ofstream stubCostFile;
		stubCostFile.open("stubCost.txt",ios::out | ios::app);

		ofstream providerCostFile;
		providerCostFile.open("providerCost.txt",ios::out | ios::app);


		//first metric
		if((marshillianEfficiency[1]-marshillianEfficiency[0])>0){
			mEfficiencyFile<<"1\t0\t0"<<endl;
		}

		else if((marshillianEfficiency[1]-marshillianEfficiency[0])<0){
			mEfficiencyFile<<"0\t1\t0"<<endl;
		}

		else{
			mEfficiencyFile<<"0\t0\t1"<<endl;
		}

		//second metric
		if(disparity[0]>disparity[1]){
			disparity[1]=disparity[1]/disparity[0];
			disparity[0]=1;
		}

		else{
			disparity[0]=disparity[0]/disparity[1];
			disparity[1]=1;
		}

		disparityFile<<disparity[0]<<"\t"<<disparity[1]<<endl;

		//third metric
		efficiencyFile<<efficiency[0]<<"\t"<<efficiency[1]<<endl;

		//fourth metric
		competitivenessFile<<competitiveness[0]<<"\t"<<competitiveness[1]<<endl;

		//fifth metric
		stubCostFile<<stubCostsMbps[0]<<"\t"<<stubCostsMbps[1]<<endl;

		//sixth metric
		providerCostFile<<providerFitnessMbps[0]<<"\t"<<providerFitnessMbps[1]<<endl;

	}

}

void findStubTraffic(int numSimulations){

	ofstream stubFile;
	stubFile.open("stubTraffic.txt",ios::out | ios::app);

	ofstream cdFile;
	cdFile.open("cdFile.txt",ios::out | ios::app);

	double totalTraffic=0;
	double transitTraffic=0;
	double stubPeeringTraffic=0;
	double providerPeeringTraffic=0;
	double possiblePeeringTraffic=0;
	list<int>::iterator it;
	double cpccPeeringTraffic=0;
	list<int> majorCPCC;

	double cumulativeTraffic=0;
	double cumulativeStubPeeringTraffic=0;
	double cumulativeProviderPeeringTraffic=0;
	double cumulativeTransitTraffic=0;
	int numProviderOverlap=0;
	int numStubOverlap=0;
	int numProviderPeer=0;
	list<int>::iterator it2;
	list<int>::iterator it3;
	list<int> encountered;
	int k=0;
	double sum=0;

	//if(numSimulations==2){

		for(int i=0;i<activeNodes;i++)
			if(aliveNodes[i].I.empty() && aliveNodes[i].isMajorContentNet==true)
				majorCPCC.push_back(i);

		for(int i=0;i<activeNodes;i++)
			if(!aliveNodes[i].I.empty())
				cdFile<<aliveNodes[i].I.size()<<endl;

		for(int i=0;i<activeNodes;i++){
			if(aliveNodes[i].I.empty()){

				totalTraffic=0;
				transitTraffic=0;
				stubPeeringTraffic=0;
				providerPeeringTraffic=0;
				cpccPeeringTraffic=0;
				numProviderOverlap=0;
				numProviderPeer=0;
				possiblePeeringTraffic=0;
				encountered.clear();
				k=0;
				sum=0;

				totalTraffic=aliveNodes[i].trafficConsumed+aliveNodes[i].trafficGenerated;
				cumulativeTraffic+=totalTraffic;

				for(it=aliveNodes[i].overLap.begin();it!=aliveNodes[i].overLap.end();it++){
					if(!aliveNodes[*it].I.empty()){
						numProviderOverlap++;

						if(aliveNodes[i].isPeer(*it)){
							numProviderPeer++;
						}
					}
				}


				if(aliveNodes[i].Q!=-1){
					transitTraffic+=linkValueVector[linkIndex[i][aliveNodes[i].Q].index];
					cumulativeTransitTraffic+=transitTraffic;
				}

				else
					transitTraffic=0;

				transitTraffic=transitTraffic/totalTraffic;


				if(!aliveNodes[i].K.empty()){
					for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++){

						if(!aliveNodes[*it].I.empty()){
							providerPeeringTraffic+=linkValueVector[linkIndex[i][*it].index];
							cumulativeProviderPeeringTraffic+=providerPeeringTraffic;
						}

						else{
							stubPeeringTraffic+=linkValueVector[linkIndex[i][*it].index];
							cumulativeStubPeeringTraffic+=stubPeeringTraffic;
						}

					}
				}

				if(aliveNodes[i].isMajorContentNet==false){
					if(!aliveNodes[i].K.empty()){
						for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++)
							if(aliveNodes[*it].isMajorContentNet==true){
								cpccPeeringTraffic+=linkValueVector[linkIndex[i][*it].index];
							}
					}
				}

				cpccPeeringTraffic=cpccPeeringTraffic/stubPeeringTraffic;
				stubPeeringTraffic=stubPeeringTraffic/totalTraffic;
				providerPeeringTraffic=providerPeeringTraffic/totalTraffic;
				sum=transitTraffic+stubPeeringTraffic+providerPeeringTraffic;

				stubFile<<numProviderOverlap<<"\t"<<numProviderPeer<<"\t"<<transitTraffic<<"\t"<<stubPeeringTraffic<<"\t"<<providerPeeringTraffic<<"\t"<<sum<<"\t"<<cpccPeeringTraffic<<endl;

			}

		}

		cout<<"Cumulatives: "<<cumulativeTransitTraffic/cumulativeTraffic<<"\t"<<cumulativeStubPeeringTraffic/cumulativeTraffic<<"\t"<<cumulativeProviderPeeringTraffic/cumulativeTraffic<<endl;

	//}
	/*
	//else{

		for(int i=0;i<activeNodes;i++){

			totalTraffic=0;
			peeringTraffic=0;
			numProviderOverlap=0;
			numProviderPeer=0;
			possiblePeeringTraffic=0;
			encountered.clear();
			int k=0;


			if(aliveNodes[i].I.empty()){
				totalTraffic=aliveNodes[i].trafficGenerated+aliveNodes[i].trafficConsumed;

				if(!aliveNodes[i].K.empty()){
					for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++)
						if(!aliveNodes[*it].I.empty()){
							peeringTraffic+=linkValueVector[linkIndex[i][*it].index];
							possiblePeeringTraffic+=(trafficMatrix[i][*it]+trafficMatrix[*it][i]);

						}


					for(int j=0;j<activeNodes;j++)
						if(i!=j && !aliveNodes[i].isPeer(j) && (k=aliveNodes[i].isPresentInCustomerTreeOfPeer(j))!=-1){

							if(!aliveNodes[k].isPeer(j)){

								possiblePeeringTraffic+=trafficMatrix[i][j];

								if(aliveNodes[j].isPresentInCustomerTreeOfPeer(i)==-1)
									possiblePeeringTraffic+=trafficMatrix[j][i];
							}
						}
				}

				for(it=aliveNodes[i].overLap.begin();it!=aliveNodes[i].overLap.end();it++){
					if(!aliveNodes[*it].I.empty()){
						numProviderOverlap++;

						if(aliveNodes[i].isPeer(*it)){
							numProviderPeer++;
						}
					}
				}

				stubProviderFile<<numProviderOverlap<<"\t"<<numProviderPeer<<"\t"<<"\t"<<possiblePeeringTraffic/totalTraffic<<"\t"<<peeringTraffic/totalTraffic<<endl;

			}

		}

	//}
	 */
}

void customerPeerExpanseCurves(){

	ofstream cpExpanseFile;
	cpExpanseFile.open("cpExpanse.txt",ios::out | ios::app);

	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].I.empty()){
			cpExpanseFile<<aliveNodes[i].numGPresence<<"\t"<<aliveNodes[i].I.size()<<"\t"<<aliveNodes[i].K.size()<<endl;
		}

}

void strategiesExpanseCurves(int numSimulations){

	int s[16][3]={0};


	ofstream sExpanseE1File;
	ofstream sExpanseE2File;

	sExpanseE1File.open("sExpanseE1.txt",ios::out | ios::app);
	sExpanseE2File.open("sExpanseE2.txt",ios::out | ios::app);

	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].I.empty()){
			s[aliveNodes[i].numGPresence][aliveNodes[i].peeringStrategyNumber]++;
		}


	for(int i=1;i<16;i++){
		for(int j=0;j<3;j++){
			if(numSimulations==1){
				sExpanseE1File<<i<<"\t"<<s[i][j]<<"\t";
			}

			else{
				sExpanseE2File<<i<<"\t"<<s[i][j]<<"\t";
			}


		}

		if(numSimulations==0)
			sExpanseE1File<<endl;
		else
			sExpanseE2File<<endl;
	}


}

void customersFitnessCurves(int numSimulations){

	ofstream cfFileE1;
	ofstream cfFileE2;

	cfFileE1.open("customerFitnessE1.txt",ios::out | ios::app);
	cfFileE2.open("customerFitnessE2.txt",ios::out | ios::app);

	if(numSimulations==1){
		for(int i=0;i<activeNodes;i++)
			if(!aliveNodes[i].I.empty())
				cfFileE1<<aliveNodes[i].I.size()<<"\t"<<aliveNodes[i].fitness<<endl;
	}

	else{
		for(int i=0;i<activeNodes;i++)
			if(!aliveNodes[i].I.empty())
				cfFileE2<<aliveNodes[i].I.size()<<"\t"<<aliveNodes[i].fitness<<endl;

	}

}

void peersFitnessCurves(int numSimulations){

	ofstream pfFileE1;
	ofstream pfFileE2;

	pfFileE1.open("peerFitnessE1.txt",ios::out | ios::app);
	pfFileE2.open("peerFitnessE2.txt",ios::out | ios::app);

	if(numSimulations==1){
		for(int i=0;i<activeNodes;i++)
			if(!aliveNodes[i].I.empty())
				pfFileE1<<aliveNodes[i].K.size()<<"\t"<<aliveNodes[i].fitness<<endl;
	}

	else{
		for(int i=0;i<activeNodes;i++)
			if(!aliveNodes[i].I.empty())
				pfFileE2<<aliveNodes[i].K.size()<<"\t"<<aliveNodes[i].fitness<<endl;

	}

}

void t1ExpanseCurves(){

	int expanse[16]={0};
	ofstream expanseT1File;
	expanseT1File.open("expanseT1.txt", ios::out | ios::app);

	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].I.empty() && aliveNodes[i].Q==-1)
			expanse[aliveNodes[i].numGPresence]++;

	for(int i=1;i<16;i++)
		expanseT1File<<i<<"\t"<<expanse[i]<<endl;



}

void fitnessCurves(){

	int t1Increase=0;
	int t1Decrease=0;
	int t1Constant=0;
	int nt1Increase=0;
	int nt1Decrease=0;
	int nt1Constant=0;

	list<int>::iterator it;
	int numStubsAdded=0;

	ofstream f1File;
	f1File.open("fitnessComparison.txt",ios::out | ios::app);

	ofstream f2FileE1;
	f2FileE1.open("fitnessExpanseE1Detailed.txt",ios::out | ios::app);

	ofstream f2FileE2;
	f2FileE2.open("fitnessExpanseE2Detailed.txt",ios::out | ios::app);

	ofstream f3File;
	f3File.open("fitnessT1.txt",ios::out | ios::app);

	ofstream f4File;
	f4File.open("fitnessNT1.txt",ios::out | ios::app);

	ofstream f5File;
	f5File.open("fitnessStubAdded.txt",ios::out | ios::app);

	ofstream f6File;
	f6File.open("fitnessDifferenceStrategy.txt",ios::out | ios::app);

	for(int i=0;i<activeNodes;i++){
		if(!aliveNodes[i].I.empty()){

			numStubsAdded=0;

			f1File<<i<<"\t"<<fitnessRecord[0][i]<<"\t"<<fitnessRecord[1][i]<<"\t"<<fitnessRecord[2][i]<<endl;

			if(numSimulations==1)
				f2FileE1<<i<<"\t"<<aliveNodes[i].peeringStrategyNumber<<"\t"<<aliveNodes[i].numGPresence<<"\t"<<fitnessRecord[1][i]<<endl;
			else
				f2FileE2<<i<<"\t"<<aliveNodes[i].peeringStrategyNumber<<"\t"<<aliveNodes[i].numGPresence<<"\t"<<fitnessRecord[2][i]<<endl;

			if(aliveNodes[i].Q==-1){

				f3File<<i<<"\t"<<fitnessRecord[2][i]-fitnessRecord[1][i]<<endl;

				if((fitnessRecord[2][i]-fitnessRecord[1][i])>0)
					t1Increase++;

				else if((fitnessRecord[2][i]-fitnessRecord[1][i])<0)
					t1Decrease++;

				else
					t1Constant++;
			}

			else{

				f4File<<i<<"\t"<<fitnessRecord[2][i]-fitnessRecord[1][i]<<endl;

				if((fitnessRecord[2][i]-fitnessRecord[1][i])>0)
					nt1Increase++;

				else if((fitnessRecord[2][i]-fitnessRecord[1][i])<0)
					nt1Decrease++;

				else
					nt1Constant++;

			}

			for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++){
				if(aliveNodes[*it].I.empty() && aliveNodes[*it].isMajorContentNet==false)
					numStubsAdded++;
			}

			f5File<<i<<"\t"<<numStubsAdded<<"\t"<<fitnessRecord[2][i]-fitnessRecord[1][i]<<endl;


			f6File<<i<<"\t"<<aliveNodes[i].peeringStrategyNumber<<"\t"<<fitnessRecord[2][i]-fitnessRecord[1][i]<<endl;

		}
	}

}

//******************************* Archived Functions ************************************//
//****************************************************************************************

bool checkConnectivitySum(){

	int sum=1;
	list<int> tempList;
	list<int>::iterator itInt;
	list<int>::iterator itInt1;
	list<int> tempK;

	for(int i=0;i<activeNodes;i++){

		if(!aliveNodes[i].J.empty()){
			aliveNodes[i].J.sort();
			aliveNodes[i].J.unique();
		}
	}

	for(int i=0;i<activeNodes;i++){

		sum=1;
		if(!aliveNodes[i].J.empty()){
			aliveNodes[i].J.sort();
			aliveNodes[i].J.unique();
			sum+=aliveNodes[i].J.size();
		}

		tempList.clear();
		tempK.clear();

		if(!aliveNodes[i].K.empty()){

			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++)
				tempK.push_back(*itInt);

			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++)
				for(itInt1=aliveNodes[i].K.begin();itInt1!=aliveNodes[i].K.end();itInt1++)
					if(*itInt!=*itInt1 && aliveNodes[*itInt].isPresentInCustomerTree(*itInt1))
						tempK.remove(*itInt1);

			sum+=tempK.size();


			for(itInt=tempK.begin();itInt!=tempK.end();itInt++)
				sum+=aliveNodes[*itInt].J.size();


		}

		for(int j=0;j<activeNodes;j++){
			if(j!=i && !aliveNodes[i].isPresentInCustomerTree(j) && !aliveNodes[i].isPeer(j) && -1==aliveNodes[i].isPresentInCustomerTreeOfPeer(j)){

				tempList.push_back(j);
			}
		}

		sum+=tempList.size();

		if(sum!=activeNodes){

			logFile<<"Total nodes for "<<i<<" are "<<sum<<" which is "<<activeNodes-sum<<" less than actual value"<<endl;
			displayTopology();
			string str("ERROR!! Connectivity breached in Peering");
			endSimulation(str);
		}

	}

	return true;
}

bool checkConnectivity(){

	list<int>::iterator it1;
	list<int>::iterator it2;
	int flowSum=0;
	int flowSumAsym=0;

	for(int i=0;i<activeNodes;i++){
		if(aliveNodes[i].Q!=-1){
			if(linkIndex[i][aliveNodes[i].Q].index==-1){
				logFile<<"Link between "<<i<<" and its provider "<<aliveNodes[i].Q<<" not established"<<endl;
				string str="ERROR!! Breach in connectivity";
				endSimulation(str);
			}
		}

		else{

			if(!isPresentInList(Tier1,i)){
				logFile<<"Node "<<i<<" has no provider yet not in Tier1"<<endl;
				string str="ERROR!! Breach in connectivity";
				endSimulation(str);

			}
		}

	}

	for(it1=Tier1.begin();it1!=Tier1.end();it1++)
		for(it2=Tier1.begin();it2!=Tier1.end();it2++){
			if(*it2!=*it1){
				if(!isPresentInList(aliveNodes[*it1].K,*it2)){
					logFile<<"Peers "<<*it1<<" and "<<*it2<<" not in eachother's K list"<<endl;
					string str="ERROR!! Breach in connectivity";
					endSimulation(str);
				}

				if(linkIndex[*it1][*it2].index==-1 || linkIndex[*it1][*it2].linkClass!=PPLink){
					logFile<<"Link between peers "<<*it1<<" and "<<*it2<<" not established"<<endl;
					string str="ERROR!! Breach in connectivity";
					endSimulation(str);
				}
			}
		}

	for(int i=0;i<activeNodes;i++)
		for(int j=0;j<activeNodes;j++)
			if(i!=j){

				flowSum=0;
				flowSumAsym=0;
				flowSum+=routingMatrixScale[flowIndex[i][j]].size();
				flowSumAsym+=routingMatrixScaleAsym[flowIndex[i][j]].size();

				if(flowSum==0){
					logFile<<"Flow could not be established between "<<i<<" and "<<j<<endl;
					string str="ERROR!! Flows not properly established";
					endSimulation(str);
				}

				if(flowSumAsym==0){
					logFile<<"Flow could not be established between "<<i<<" and "<<j<<" in asymmetric matrix"<<endl;
					string str="ERROR!! Flows not properly established";
					endSimulation(str);
				}
			}

	for(int i=0;i<activeNodes;i++)
		if(aliveNodes[i].isPresentInCustomerTree(i)){
			logFile<<"Node "<<i<<" is present in its own customer tree"<<endl;
			string str="ERROR!! Loop detected";
			endSimulation(str);
		}

	checkConnectivitySum();

	return true;
}


bool Node::getOrphanProvider(){

	/*
	list<npPair> GS;
	list<npPair> TGS;
	list<Coordinate>::iterator it;
	list<int>::iterator it2;
	list<npPair>::iterator it4;
	int xPoint;
	int yPoint;
	npPair possibleProvider;
	int providerId;
	int P;
	int X;
	int Z;

#if DEBUG
	logFile<<endl<<"Orphan node "<<nodeId<<" getting new provider"<<endl;
#endif


	//Step 1 Creation of GS
	for(it=gPresence.begin();it!=gPresence.end();it++){

		xPoint=(*it).xCoordinate;
		yPoint=(*it).yCoordinate;

		if(geography[xPoint][yPoint].population>1){

			for(it2=geography[xPoint][yPoint].nodePresent.begin();it2!=geography[xPoint][yPoint].nodePresent.end();it2++){

				if((*it2)!=nodeId && aliveNodes[*it2].lifeStatus==alive && aliveNodes[*it2].newborn==false && aliveNodes[*it2].orphan==false && !isPresentInList(prohibitedProviderList,*it2) && !isPresentInCustomerTree(*it2)){

					possibleProvider.nId=*it2;
					possibleProvider.price=aliveNodes[*it2].price;
					possibleProvider.trafficVolume=aliveNodes[*it2].Vt;

					GS.push_back(possibleProvider);

				}//end if

			}//end for

		}//end if

	}//end for

	//Step 2 Creation of TGS
	if(!GS.empty()){

		GS.sort(compareId);
		GS.unique(checkUniqueness);

		for(it4=GS.begin();it4!=GS.end();it4++){

			if((*it4).trafficVolume>Vt)
				TGS.push_back(*it4);

		}//end for

	}//end if


	if(TGS.empty()){	//orphan node is to become Tier1

		list<int>::iterator itTier1;
		list<int> xSet;
		list<int> restSet;
		list<int>::iterator it;
		list<int>::iterator itX;
		list<int>::iterator itRest;

		Q=-1;
		providerPrice=0;

#if DEBUG
		logFile<<"Orphan node "<<nodeId<<" becoming Tier1"<<endl;
#endif

		for(itTier1=Tier1.begin();itTier1!=Tier1.end();itTier1++){

			insertPeerInK(*itTier1);
			aliveNodes[*itTier1].insertPeerInK(nodeId);
			establishLinkWithPeer(nodeId,*itTier1);
			establishFlowWithPeer(nodeId,*itTier1);

		}

		Tier1.push_back(nodeId);

		prohibitedProviderList.remove(nodeId);
		for(it=J.begin();it!=J.end();it++){
			prohibitedProviderList.remove(*it);
			xSet.push_back(*it);
		}

		for(int i=0;i<activeNodes;i++)
			if(i!=nodeId && !isPresentInCustomerTree(i) && !isPresentInList(prohibitedProviderList,i))
				restSet.push_back(i);

		for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
			if(!isPeer(*itRest))
				establishFlowPeering(nodeId,*itRest,Q);

		for(itX=xSet.begin();itX!=xSet.end();itX++)
			for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
				establishFlowPeering(*itX,*itRest,aliveNodes[*itX].Q);

		return true;

	}//end if node becomes Tier1

	else{

		TGS.sort(comparePrice);

		int Z=TGS.front().nId;
		list<int>::iterator it;
		list<int> xSet;
		list<int> restSet;
		list<int>::iterator itX;
		list<int>::iterator itRest;

#if DEBUG
		logFile<<"Orphan node "<<nodeId<<" got provider "<<Z<<endl;
#endif

		Q=Z;
		providerPrice=aliveNodes[Z].price;
		establishLinkWithProvider(nodeId,Z);
		establishFlowWithProviderScale(nodeId,Z);

		aliveNodes[Q].addICustomer(nodeId);
		aliveNodes[Q].addJSubTree(nodeId);

		int P=aliveNodes[Q].Q;
		while(P!=-1){
			aliveNodes[P].addJSubTree(nodeId);
			P=aliveNodes[P].Q;
		}


		prohibitedProviderList.remove(nodeId);
		for(it=J.begin();it!=J.end();it++){
			prohibitedProviderList.remove(*it);
			xSet.push_back(*it);
		}

		for(int i=0;i<activeNodes;i++)
			if(i!=nodeId && !isPresentInCustomerTree(i) && !isPresentInList(prohibitedProviderList,i))
				restSet.push_back(i);

		for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
			if(*itRest!=Q)
				establishFlowPeering(nodeId,*itRest,Q);

		for(itX=xSet.begin();itX!=xSet.end();itX++)
			for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
				establishFlowPeering(*itX,*itRest,aliveNodes[*itX].Q);

		return true;

	}

	return false;
	*/
}


bool Node::considerPeeringRequest(int id){

	if((V/aliveNodes[id].V)<=peerCriteria)
		return true;
	else
		return false;

}


bool Node::isPresentInProviderChain(int id){

	int p;

	if(Q==-1 || isPresentInCustomerTree(id) || id==nodeId)
		return false;

	else if(id==Q)
		return true;

	else{
		p=aliveNodes[Q].Q;

		while(p!=-1){

			if(id==p)
				return true;
			p=aliveNodes[p].Q;
		}

		return false;
	}

}


void Node::reborn(){

	bool nodeDropped=false;
	numGPresence=zipf(sZetaGeography,maxRegions*maxRegions);
	Coordinate nodeLocation;
	lifeStatus=alive;
	newborn=true;


	while(nodeDropped==false){

		nodeLocation.xCoordinate=rand()%maxRegions;
		nodeLocation.yCoordinate=rand()%maxRegions;

		if(geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].population==0 || geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].population>=maxD){
			continue;
		}

		else{
			gPresence.push_back(nodeLocation);
			nodeDropped=true;
			break;
		}

	}//end while

	geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].nodePresent.push_back(nodeId);
	geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].population++;

	//expand the node to its allowed expanse
	if(numGPresence>1){
		expandNodeRandom(nodeLocation,aliveNodes[nodeId]);
	}

	trafficGenerated=zipf(sZetaGeography,static_cast<int>(totalTraffic))+rand()%30;

	if(priceDependancy==0)
		price=rand()%(maxRegions*maxRegions)+1+(static_cast<double>(rand()%1000)/1000);
	else
		price=numGPresence+(static_cast<double>(rand()%1000)/1000);
}

void Node::die(){

	/*
	//end all links and flows for this node
	if(!K.empty()){ //node is Tier 1

		list<int>::iterator it;

		for(it=K.begin();it!=K.end();it++)
			aliveNodes[*it].K.remove(nodeId);

	}

	if(isPresentInList(Tier1,nodeId))
		Tier1.remove(nodeId);

	if(Q!=-1){

		aliveNodes[Q].removeICustomer(nodeId);
		aliveNodes[Q].removeJSubTree(nodeId);
		int P=aliveNodes[Q].Q;
		while(P!=-1){

			aliveNodes[P].removeJSubTree(nodeId);
			P=aliveNodes[P].Q;
		}

	}

	if(!I.empty()){

		npPair npOrphan;
		list<int>::iterator it;
		for(it=I.begin();it!=I.end();it++){
			aliveNodes[*it].Q=-1;
			aliveNodes[*it].orphan=true;
			npOrphan.nId=*it;
			npOrphan.trafficVolume=aliveNodes[*it].Vt;
			orphanList.push_back(npOrphan);
		}

	}

	//end all existing links
	for(int j=0;j<activeNodes;j++)
		if(j!=nodeId && linkIndex[nodeId][j].index!=-1)
			endLink(nodeId,j);

	//end all existing flows
	for(int j=0;j<activeNodes;j++)
		if(j!=nodeId)
			endFlow(nodeId,j);

	//end flows of its entire customer tree with everyone else
	if(!I.empty()){

		list<int> customerSet;
		list<int> restSet;
		list<int>::iterator itCustomer;
		list<int>::iterator itRest;

		for(itCustomer=J.begin();itCustomer!=J.end();itCustomer++){
			customerSet.push_back(*itCustomer);
			prohibitedProviderList.push_back(*itCustomer);
		}

		for(int i=0;i<activeNodes;i++)
			if(i!=nodeId && !isPresentInCustomerTree(i))
				restSet.push_back(i);

		for(itCustomer=customerSet.begin();itCustomer!=customerSet.end();itCustomer++)
			for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
				endFlow(*itCustomer,*itRest);

		customerSet.clear();
		restSet.clear();

		list<npPair>::iterator itNP;

		for(itNP=orphanList.begin();itNP!=orphanList.end();itNP++){

			cout<<"Came here"<<endl;

			customerSet.clear();
			restSet.clear();

			for(itCustomer=aliveNodes[(*itNP).nId].J.begin();itCustomer!=aliveNodes[(*itNP).nId].J.end();itCustomer++)
				customerSet.push_back(*itCustomer);
			customerSet.push_back((*itNP).nId);

			for(int i=0;i<activeNodes;i++)
				if(!isPresentInList(customerSet,i))
					restSet.push_back(i);

			for(itCustomer=customerSet.begin();itCustomer!=customerSet.end();itCustomer++)
				for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
					endFlow(*itCustomer,*itRest);

			cout<<"And then came here"<<endl;
		}

	}

	prohibitedProviderList.push_back(nodeId);

	price=providerPrice=0;
	Vo=Vp=Vc=Vt=V=Vpp=0;
	Q=-1;
	lifeStatus=dead;
	newborn=false;
	I.clear();
	J.clear();
	K.clear();

	list<Coordinate>::iterator itC;
	int x;
	int y;

	for(itC=gPresence.begin();itC!=gPresence.end();itC++){

		x=(*itC).xCoordinate;
		y=(*itC).yCoordinate;

		geography[x][y].population--;
		geography[x][y].nodePresent.remove(nodeId);

	}

	gPresence.clear();
	numGPresence=0;
	classification=Stub;
	customerVPList.clear();

	//clear its traffic matrix entries
	for(int i=0;i<activeNodes;i++)
		if(i!=nodeId)
			trafficMatrix[nodeId][i]=0;

	for(int j=0;j<activeNodes;j++)
		if(j!=nodeId)
			trafficMatrix[j][nodeId]=0;

	*/
}

int findNumSPPLinks(){

	numSPPLinks=0;
	list<int>::iterator it;


	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].I.empty() && !aliveNodes[i].K.empty()){

				for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++){
					if(aliveNodes[*it].Q!=-1 && aliveNodes[*it].I.empty() && aliveNodes[*it].isMajorContentNet==false)
						numSPPLinks++;
				}

		}

	return numSPPLinks;

}

void logOscillation(int iterations){

	static bool spaceAllocated=false;
	static int counter=0;

	ofstream strategyFile;
	strategyFile.open("strategyVector.txt",ios::out|ios::app);

	if(!spaceAllocated){

		spaceAllocated=true;

		oscillationLog=new LogVector*[50];
		for(int i=0;i<50;i++){
			oscillationLog[i]=new LogVector[activeNodes];

		}

		for(int i=0;i<50;i++)
			for(int j=0;j<activeNodes;j++)
				oscillationLog[i][j].peeringStrategyNumber=-1;

	}

	strategyFile<<iterations<<":\t";
	for(int i=0;i<activeNodes;i++)
		if(!aliveNodes[i].I.empty()){

			oscillationLog[counter][i].peeringStrategyNumber=aliveNodes[i].peeringStrategyNumber;
			oscillationLog[counter][i].I=aliveNodes[i].I;
			oscillationLog[counter][i].K=aliveNodes[i].K;

			strategyFile<<aliveNodes[i].peeringStrategyNumber<<"\t";

		}

	strategyFile<<endl;
	counter++;

}

void analyzeOscillations(){

	int numMismatch=0;
	int measurements=0;
	int k=0;
	int i=0;
	list<int> cycleTime;
	list<int> oscillatoryNodes;
	list<int>::iterator it;

	ofstream cycleFile;
	cycleFile.open("cycle.txt",ios::out|ios::app);

	ofstream oscillatoryNodesFile;
	oscillatoryNodesFile.open("oscillatoryNodes.txt",ios::out|ios::app);

	restart:
	//cout<<"Doing analysis for vector "<<k<<endl;
	for(i=k+1;i<25;i++){

		numMismatch=0;

		for(int j=0;j<activeNodes;j++){
			if(oscillationLog[k][j].peeringStrategyNumber!=oscillationLog[i][j].peeringStrategyNumber)
				numMismatch++;
			else if(oscillationLog[k][j].I!=oscillationLog[i][j].I)
				numMismatch++;
			else if(oscillationLog[k][j].K!=oscillationLog[i][j].K)
				numMismatch++;
			else{}
		}

		if(numMismatch==0){
			measurements++;
			cycleTime.push_back(i-k);
			k=i;
			goto restart;
		}

		else
			oscillatoryNodes.push_back(numMismatch);
	}

	for(it=cycleTime.begin();it!=cycleTime.end();it++){
		cycleFile<<*it<<"\t";
	}
	cycleFile<<endl;

	for(it=oscillatoryNodes.begin();it!=oscillatoryNodes.end();it++){
		oscillatoryNodesFile<<*it<<"\t";
	}
	oscillatoryNodesFile<<endl;

}

void printPeeringLinkClassification(int numSimulations){

	double linkClass[15]={0};
	double trafficClass[15]={0};
	double totalLinks=0;
	double totalTraffic=0;

	ofstream file1;
	file1.open("linkClass1.txt",ios::out | ios::app);

	ofstream file3;
	file3.open("trafficClass1.txt",ios::out | ios::app);

	for(int i=0;i<(activeNodes-1);i++){
		for(int j=i+1;j<activeNodes;j++){

			if(aliveNodes[i].isPeer(j)){

				totalLinks++;
				totalTraffic+=linkValueVector[linkIndex[i][j].index];

				if(!aliveNodes[i].I.empty() && !aliveNodes[j].I.empty()){
					linkClass[0]++;
					trafficClass[0]+=linkValueVector[linkIndex[i][j].index];
				}

				else if((!aliveNodes[i].I.empty() && aliveNodes[j].isCP==true) || (!aliveNodes[j].I.empty() && aliveNodes[i].isCP==true)){
					linkClass[1]++;
					trafficClass[1]+=linkValueVector[linkIndex[i][j].index];
				}

				else if((!aliveNodes[i].I.empty() && aliveNodes[j].isCC==true) || (!aliveNodes[j].I.empty() && aliveNodes[i].isCC==true)){
					linkClass[2]++;
					trafficClass[2]+=linkValueVector[linkIndex[i][j].index];
				}

				else if((!aliveNodes[i].I.empty() && aliveNodes[j].I.empty()) || (!aliveNodes[j].I.empty() && aliveNodes[i].I.empty())){
					linkClass[3]++;
					trafficClass[3]+=linkValueVector[linkIndex[i][j].index];
				}

				else if((aliveNodes[i].isCP==true && aliveNodes[j].isCP==true)){
					linkClass[4]++;
					trafficClass[4]+=linkValueVector[linkIndex[i][j].index];
				}

				else if((aliveNodes[i].isCP==true && aliveNodes[j].isCC==true) || (aliveNodes[j].isCP==true && aliveNodes[i].isCC==true)){
					linkClass[5]++;
					trafficClass[5]+=linkValueVector[linkIndex[i][j].index];
				}

				else if((aliveNodes[i].isCP==true && aliveNodes[j].I.empty()) || (aliveNodes[j].isCP==true && aliveNodes[i].I.empty())){
					linkClass[6]++;
					trafficClass[6]+=linkValueVector[linkIndex[i][j].index];
				}

				else if((aliveNodes[i].isCC==true && aliveNodes[j].isCC==true)){
					linkClass[7]++;
					trafficClass[7]+=linkValueVector[linkIndex[i][j].index];
				}

				else if((aliveNodes[i].isCC==true && aliveNodes[j].I.empty()) || (aliveNodes[j].isCC==true && aliveNodes[i].I.empty())){
					linkClass[8]++;
					trafficClass[8]+=linkValueVector[linkIndex[i][j].index];
				}

				else if(aliveNodes[i].I.empty() && aliveNodes[j].I.empty()){
					linkClass[9]++;
					trafficClass[9]+=linkValueVector[linkIndex[i][j].index];
				}

				else{

				}


			}

		}

	}

	for(int i=0;i<10;i++){

		if(numSimulations==1){
			file1<<linkClass[i]/totalLinks<<"\t";
			file3<<trafficClass[i]/totalTraffic<<"\t";
		}

	}

	file1<<endl;
	file3<<endl;
}

/*************************************************************************************
/*************************************************************************************
 */

void saveNetworkState(){

	Tier1Save.clear();
	list<int>::iterator itInt;

	for(itInt=Tier1.begin();itInt!=Tier1.end();itInt++)
		Tier1Save.push_back(*itInt);

	for(int i=0;i<activeNodes;i++)
		aliveNodesSave[i]=aliveNodes[i];

	for(int i=0;i<maxFlows;i++){
		routingMatrixScaleSave[i]=routingMatrixScale[i];
		routingMatrixScaleAsymSave[i]=routingMatrixScale[i];
		flowValueVectorSave[i]=flowValueVector[i];
		flowValueVectorAsymSave[i]=flowValueVectorAsym[i];
		flowDirectionFromSave[i]=flowDirectionFrom[i];
		flowDirectionFromAsymSave[i]=flowDirectionFromAsym[i];
		aliveFlowIndicatorSave[i]=aliveFlowIndicator[i];
		activeFlowIndicatorSave[i]=activeFlowIndicator[i];
	}

	for(int i=0;i<maxLinks;i++){

		aliveLinkIndicatorSave[i]=aliveLinkIndicator[i];
		linkValueVectorSave[i]=linkValueVector[i];

	}

	for(int i=0;i<activeNodes;i++)
		for(int j=0;j<activeNodes;j++){
			flowIndexSave[i][j]=flowIndex[i][j];
			linkIndexSave[i][j].index=linkIndex[i][j].index;
			linkIndexSave[i][j].linkClass=linkIndex[i][j].linkClass;
			linkIndexSave[i][j].provider=linkIndex[i][j].provider;
			linkIndexSave[i][j].superPeer=linkIndex[i][j].superPeer;

		}


}

void restoreNetworkState(){

	list<int>::iterator itInt;

	Tier1.clear();

	for(itInt=Tier1Save.begin();itInt!=Tier1Save.end();itInt++)
		Tier1.push_back(*itInt);

	for(int i=0;i<activeNodes;i++)
		aliveNodes[i]=aliveNodesSave[i];

	for(int i=0;i<maxFlows;i++){
		routingMatrixScale[i]=routingMatrixScaleSave[i];
		routingMatrixScaleAsym[i]=routingMatrixScaleSave[i];
		flowValueVector[i]=flowValueVectorSave[i];
		flowValueVectorAsym[i]=flowValueVectorAsymSave[i];
		flowDirectionFrom[i]=flowDirectionFromSave[i];
		flowDirectionFromAsym[i]=flowDirectionFromAsymSave[i];
		aliveFlowIndicator[i]=aliveFlowIndicatorSave[i];
		activeFlowIndicator[i]=activeFlowIndicatorSave[i];
	}

	for(int i=0;i<maxLinks;i++){

		aliveLinkIndicator[i]=aliveLinkIndicatorSave[i];
		linkValueVector[i]=linkValueVectorSave[i];

	}



	for(int i=0;i<activeNodes;i++)
		for(int j=0;j<activeNodes;j++){
			flowIndex[i][j]=flowIndexSave[i][j];
			linkIndex[i][j].index=linkIndexSave[i][j].index;
			linkIndex[i][j].linkClass=linkIndexSave[i][j].linkClass;
			linkIndex[i][j].provider=linkIndexSave[i][j].provider;
			linkIndex[i][j].superPeer=linkIndexSave[i][j].superPeer;

		}


}

int chooseStackelbergLeader(int nodeClass){

	int choseNode;

	list<npPair> stackelbergLeaderList;
	npPair tempNP;
	list<npPair>::iterator it;

	for(int i=0;i<activeNodes;i++){
		if(!aliveNodes[i].I.empty()){

			tempNP.nId=i;
			tempNP.numCustomers=aliveNodes[i].I.size();
			tempNP.gExpanse=aliveNodes[i].numGPresence;
			tempNP.trafficVolume=aliveNodes[i].Vt;
			tempNP.price=aliveNodes[i].fitness;

			if(aliveNodes[i].Q==-1)
				tempNP.shouldAct=true;

			stackelbergLeaderList.push_back(tempNP);

		}
	}

	if(nodeClass==1){
		for(it=stackelbergLeaderList.begin();it!=stackelbergLeaderList.end();it++){
			if((*it).shouldAct==true)
				return (*it).nId;
		}
	}

	else if(nodeClass==2){

		stackelbergLeaderList.sort(sortGExpansePriceReverse);

		return stackelbergLeaderList.front().nId;

	}

	else if(nodeClass==3){
		stackelbergLeaderList.sort(sortVtReverse);

		return stackelbergLeaderList.front().nId;
	}

	else if(nodeClass==4){
                stackelbergLeaderList.sort(sortVt);

                return stackelbergLeaderList.front().nId;
        }


	else if(nodeClass==5){
		stackelbergLeaderList.sort(sortFitnessReverse);

		return stackelbergLeaderList.front().nId;
	}

	else if(nodeClass==6){
                stackelbergLeaderList.sort(sortFitness);

                return stackelbergLeaderList.front().nId;
        }

	
	else{
		return -1;
	}


	return -1;

}

void printStackelbergFitness(int stackelbergLeader){

	ofstream fitnessFile;
	char fitnessFileName[50];
	sprintf(fitnessFileName,"regularFitness_%d.txt",playOrderSeed);

	fitnessFile.open(fitnessFileName,ios::out|ios::app);

	fitnessFile<<stackelbergLeader<<"\t"<<aliveNodes[stackelbergLeader].fitness<<endl;
}



#endif /* NETSIM_H_ */
