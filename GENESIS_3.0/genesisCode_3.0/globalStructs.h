/*
 * globalStructs.h
 *
 *  Created on: May 23, 2013
 *      Author: aemen
 */

#ifndef GLOBALSTRUCTS_H_
#define GLOBALSTRUCTS_H_

#include "globalIncludes.h"

enum ixpPortCapacity{
	ONE_G,
	TEN_G,
	HUNDRED_G
};

enum portCharacteristic{
	PUBLIC_PORT,
	PRIVATE_PORT
};

enum estimatorStrength{
	SLACK,
	TIGHT
};

enum peeringDecision{

	PEER,
	DONTPEER

};

enum portRole{

	PUBLIC,
	PRIVATE
};

enum fd{

	UPSTREAM,
	DOWNSTREAM,
	HORIZONTAL,
	LEFT_TO_RIGHT,		//this is for HORIZONTAL peering links. Imagine a flat peering link
	RIGHT_TO_LEFT,		//with two peers on left and right of the link. The one with the lower AS id
				//is to the left of the link and the one with the higher id is to the right of the link

	INBOUND,
	OUTBOUND

};

struct flowInfo{

	int linkId;
	fd flowDirection;

	bool operator == (const flowInfo &rhs){
		return (rhs.linkId == linkId);
	}

};

struct routeComparison{

	int routeProvider;
	list<flowInfo> route;

};

struct VolumePrice{
	unsigned int linkedNode;
	double volume;
	double contractPrice;

	bool operator==(const VolumePrice& rhs){

		if(linkedNode==rhs.linkedNode && volume==rhs.volume)
			return true;
		else
			return false;
	}
};

struct NodePrice{

	unsigned int nId;
	double price;

	bool operator!=(const NodePrice& rhs){
		if(nId!=rhs.nId)
			return true;
		else
			return false;
	}

	bool operator==(const NodePrice& rhs){
		if(nId==rhs.nId)
			return true;
		else
			return false;
	}

};

enum NodeCategory{

	CP,
	CC,
	Provider,
	Stub

};

enum PeeringStrategies{

	Selective,
	Open,
	Restrictive,
	CBA,
	SelectiveReal

};

enum linkType{
	CPLink,	//customer-provider link
	PPLink, //settlement free peering link
	PPPLink	//paid peering link
};

enum matrixInfo{
	SYM,
	ASYM
};

struct linkInfo{
	int index;
	unsigned int provider;
	linkType linkClass;

	vector<int> flowsSym;
	vector<int> flowsAsym;

};

struct nodePairs{

	unsigned int n1;
	unsigned int n2;
	unsigned int n3;

};

struct geoIndexPair{

	int index;
	int numGPresence;
};

struct connectedNodes{

	unsigned int n1;	//n1 is the sender when talking about flows
	unsigned int n2;	//n2 is the receiver

	list<int> flowIndicesSym;
	list<int> flowIndicesAsym;
	list<int> linkIndices;

	bool operator!=(const connectedNodes& rhs){
		if((n1!=rhs.n1 && n2!=rhs.n2) || (n2!=rhs.n1 && n1!=rhs.n2))
			return true;
		else
			return false;
	}

	bool operator==(const connectedNodes& rhs){
		if((n1==rhs.n1 && n2==rhs.n2) || (n2==rhs.n1 && n1==rhs.n2))
			return true;
		else
			return false;
	}

};

struct peeringTrialsCombinationsStruct{

	double inboundTraffic;
	double outboundTraffic;
	double totalTraffic;
	double entanglementScore;
	unsigned int numPeers;
	set<unsigned int> peers;

	peeringTrialsCombinationsStruct(){
		inboundTraffic=outboundTraffic=totalTraffic=entanglementScore=0;
		numPeers=0;
	}

	void restore(){
		inboundTraffic=outboundTraffic=totalTraffic=entanglementScore=0;
		numPeers=0;
	}

};

struct peeringTrialsPeersStruct{

	set<unsigned int> peers;
	vector<int> flows;
	vector<int> flowsAsym;
	double inboundTraffic;
	double outboundTraffic;
	double totalTraffic;
	double rank;

	peeringTrialsPeersStruct(){
		inboundTraffic=outboundTraffic=totalTraffic=0;
		rank=-1;

	}

	void restore(){
		inboundTraffic=outboundTraffic=totalTraffic=0;
		rank=-1;
		flows.clear();
		flowsAsym.clear();
		peers.clear();
	}

};

struct peeringTrialsFlowsStruct{

	unsigned int insider;
	unsigned int outsider;
	set<unsigned int> peers;
	double flowValue;
	fd flowDirection;
	set<unsigned int> providerPeers;

	peeringTrialsFlowsStruct(){
		insider=outsider=-1;
		flowValue=-1;
		flowDirection=INBOUND;
	}

	void restore(){
		insider=outsider=0;
		peers.clear();
		providerPeers.clear();
		flowValue=-1;
		flowDirection=INBOUND;
	}


};

struct nodeTrafficRank{

	unsigned int id;
	double trafficExchange;
	double totalWeight;
	double transitWeight;
	double bypassWeight;
	unsigned int rank;

	unsigned int totalFlows;
	unsigned int transitFlows;
	unsigned int bypassFlows;

	nodeTrafficRank(){
		id=rank=0;
		trafficExchange=totalWeight=transitWeight=bypassWeight=0;
		totalFlows=transitFlows=bypassFlows=0;
	}
};

struct flowPair{

	unsigned int n1;
	unsigned int n2;

	flowPair(){
		n1=0;
		n2=0;
	}

	bool operator==(const flowPair& rhs)const{
		if(n1==rhs.n1 && n2==rhs.n2)
			return true;
		else
			return false;
	}

	bool operator<(const flowPair& rhs)const{

		/* uncomment and use the following if c++11 is available
		 *
		 * return std::tie(n1,n2) < std::tie(rhs.n1,rhs.n2);
		 */

		if(n1!=rhs.n1)
			return n1<rhs.n1;

		return n2<rhs.n2;

	}

};

typedef std::set<unsigned int>::iterator setIt;
typedef std::map<flowPair,peeringTrialsFlowsStruct>::iterator ptfsMapIt;
typedef std::map<string,peeringTrialsPeersStruct>::iterator ptpsMapIt;

#endif /* GLOBALSTRUCTS_H_ */
