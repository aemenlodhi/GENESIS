/*
 * globalVars.h
 *
 *  Created on: Sep 24, 2009
 *      Author: alodhi3
 */

#ifndef GLOBALVARS_H_
#define GLOBALVARS_H_

#include<list>
#include<limits>
using namespace std;

#define PRINTLOG 0
#define DEBUG 0
#define CHECK 1
#define TRUE 1
#define FALSE 0
#define SNAPSHOT 0
#define RESULTLOG 0

extern bool GEXPANSION;
extern bool PEERING;

extern bool netDisconnected;
extern unsigned int maxIterations;
extern unsigned int maxRounds;
extern unsigned int warmupIterations;
extern int maxNodes;
extern int activeNodes;
extern int initNodes;
extern int maxLinks;
extern double maxTraffic;
extern int numAliveNodes;
extern double** trafficMatrix;
extern int maxRegions;
extern double universalSigma;
//variables for geography and traffic distribution
extern double sZeta;
extern double totalTraffic;
extern double gExpandWFactor;
extern double Wg;
extern double trafficGenSignificance;

//variables for routing scheme
extern unsigned int numLinks;
extern unsigned int numFlows;
extern unsigned int maxFlows;
extern bool** routingMatrix;
extern int** flowIndex;
extern double* flowValueVector;
extern double* flowValueVectorAsym;
extern double* linkValueVector;
extern bool* aliveLinkIndicator;
extern bool* aliveFlowIndicator;
extern int* flowDirectionFrom;
extern int* flowDirectionFromAsym;
extern list<int>* routingMatrixScale;
extern list<int>* routingMatrixScaleAsym;
//variables for peering
extern int initialCliqueSize;
extern int totalPeeringStrategies;
extern double peeringThreshold;

enum linkType{
	CPLink,
	PPLink,
	PPPLink	//paid peering link
};

struct linkInfo{
	int index;
	int provider;
	int superPeer;
	linkType linkClass;
};

extern linkInfo** linkIndex;

struct geoIndexPair{

	int index;
	int numGPresence;
};

extern list<geoIndexPair> geoIndexList;

#endif /* GLOBALVARS_H_ */
