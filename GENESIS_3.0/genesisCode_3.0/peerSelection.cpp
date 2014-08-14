/*
 * peerSelection.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: aemenlodhi
 */

#include "node.h"
#include "support.h"

void Node::peerSelectionEstimation(estimatorStrength es, bool includePotentialCustomers){

	set<unsigned int> potentialPeers;
	list<peeringTrialsPeersStruct> peersToConsider;
	peeringTrialsPeersStruct tempObj;
	peeringTrialsPeersContemporary.clear();

#if 0
	cout<<"Node "<<nodeId<<" acquiring peers by applying peerOperatorNoTrial"<<endl;
#endif

	//for(std::multimap<unsigned int,NodePrice>::iterator it=colocatedNodePrice.begin();it!=colocatedNodePrice.end();it=colocatedNodePrice.upper_bound(it->first)){
	for(unsigned int i=0;i<Node::activeNodes;i++){
		//if(i==nodeId || !this->isCoLocated(i) || isPeer((*it).second.nId) || isPresentInCustomerTree((*it).second.nId) || nodePointers[(*it).second.nId]->isPresentInCustomerTree(nodeId)){}
		if(i==nodeId || (includePotentialCustomers==false && isPotentialCustomer(i)) || !this->isCoLocated(i) || isPeer(i) || isPresentInCustomerTree(i) || nodePointers[i]->isPresentInCustomerTree(nodeId)){}
		else{

			potentialPeers.insert(i);

		}
	}

	vector<int> upstreamFlowsSym;
	vector<int> upstreamFlowsAsym;
	vector<int> flowsSym;
	vector<int> flowsAsym;

	unsigned int id;
	for(set<unsigned int>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){

		tempObj.restore();
		tempObj.peers.insert(*it);
		id=*it;

		if(es==TIGHT){
			tempObj.inboundTraffic=nodePointers[id]->trafficSent[nodeId];
			if(flowDirectionFrom[flowIndex[nodeId][id]]==id)
				flowsSym.push_back(flowIndex[nodeId][id]);
			else
				flowsAsym.push_back(flowIndex[nodeId][id]);

			tempObj.outboundTraffic=estimateTrafficToTight(id,flowsSym,flowsAsym);
		}

		if(es==SLACK){
			tempObj.inboundTraffic=estimateTrafficFromSlack(id,flowsSym,flowsAsym);
			tempObj.outboundTraffic=estimateTrafficToSlack(id,flowsSym,flowsAsym);
		}

		tempObj.totalTraffic=tempObj.inboundTraffic+tempObj.outboundTraffic;

		//if(tempObj.totalTraffic>=peeringThreshold)
		peersToConsider.push_back(tempObj);

	}

	std::set<unsigned int>::iterator itS;
	for(list<peeringTrialsPeersStruct>::iterator it=peersToConsider.begin();it!=peersToConsider.end();it++){

		if(((*it).inboundTraffic/(*it).outboundTraffic)<=selectivePeerCriteria){

			itS=(*it).peers.begin();

			if(nodePointers[*itS]->applyPeeringCriteria(nodeId)==PEER){
				this->getSettlementFreePeer(*itS,false);
				//updateIXPPorts((*it).totalTraffic);
			}

			peeringTrialsPeersContemporary[static_cast<ostringstream*>( &(ostringstream() << *((*it).peers.begin())) )->str()]=*it;

		}

	}

	computeTrafficFlowsAcrossNode(nodeId);
	updateIXPPorts();
	updateVt();
	updateFitness();


}

void Node::peerSelectionPaidPeering(){

	list<VolumePrice> potentialPeers;
	list<VolumePrice> potentialFreePeers;
	list<VolumePrice> potentialPaidPeersCustomers;
	list<VolumePrice> potentialPaidPeersProviders;
	VolumePrice tempObj;
	double totalTraffic=0;
	double absoluteCostForTransit=0;
	double absoluteCostForPeering=0;

	for(unsigned int i=0;i<Node::activeNodes;i++){
		if(i!=nodeId && this->isCoLocated(i) && !this->isPresentInCustomerTree(i) && !this->isPeer(i) && !nodePointers[i]->isPresentInCustomerTree(nodeId)){
			tempObj.linkedNode=i;
			tempObj.volume=trafficSent[i]+nodePointers[i]->trafficSent[nodeId];
			totalTraffic+=tempObj.volume;

			if(this->applyPeeringCriteria(i)==PEER){

				if(nodePointers[i]->applyPeeringCriteria(nodeId)==PEER)
					potentialFreePeers.push_back(tempObj);
				else
					potentialPaidPeersProviders.push_back(tempObj);

			}

			else
				potentialPaidPeersCustomers.push_back(tempObj);

		}

	}

	absoluteCostForTransit=getTransitCost(totalTraffic);

	if(!potentialPaidPeersCustomers.empty()){
		for(list<VolumePrice>::iterator it=potentialPaidPeersCustomers.begin();it!=potentialPaidPeersCustomers.end();it++){

		}
	}


#if DEBUG
	cout<<"Number of potential peers: "<<potentialPeers.size()<<endl;
	cout<<"Total possible peering traffic: "<<totalTraffic<<endl;
	cout<<"Absolute Cost For Transit: "<<absoluteCostForTransit<<endl;
	cout<<"Absolute Cost For Peering: "<<absoluteCostForPeering<<endl;
#endif

	if(totalTraffic<=1000){
		if(absoluteCostForTransit<absoluteCostForPeering){

#if DEBUG
			cout<<"Going with transit option"<<endl;
#endif
			return;
		}

		else{

			for(list<VolumePrice>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){
				if(nodePointers[(*it).linkedNode]->applyPeeringCriteria(nodeId)==PEER)
					this->getSettlementFreePeer((*it).linkedNode,false);
			}

#if DEBUG
			cout<<"Going with absolute peering option"<<endl;
#endif
			return;

		}

	}

	else if(totalTraffic>1000){

		list<VolumePrice> remainingPeers;
		double unpackedTraffic=0;
		double unpackedCost=0;
		double peeringCost=0;

		if(totalTraffic<10000){
			remainingPeers=binPack(ONE_G,totalTraffic,potentialPeers);

#if DEBUG
			cout<<potentialPeers.size()-remainingPeers.size()<<" peers were packed in ONE_G port"<<endl;
#endif

			peeringCost=800;
		}

		else if(totalTraffic>10000 && totalTraffic<100000){
			remainingPeers=binPack(TEN_G,totalTraffic,potentialPeers);

#if DEBUG
			cout<<potentialPeers.size()-remainingPeers.size()<<" peers were packed in TEN_G port"<<endl;
#endif

			peeringCost=1700;

		}

		else{	//traffic is greater than 100 G
			remainingPeers=binPack(HUNDRED_G,totalTraffic,potentialPeers);

#if DEBUG
			cout<<potentialPeers.size()-remainingPeers.size()<<" peers were packed in HUNDRED_G port"<<endl;
#endif

			peeringCost=7820;
		}

		if(!remainingPeers.empty()){
			for(list<VolumePrice>::iterator it=remainingPeers.begin();it!=remainingPeers.end();it++)
				unpackedTraffic+=(*it).volume;

			unpackedCost=getTransitCost(unpackedTraffic);

#if DEBUG
			cout<<"Unpacked traffic: "<<unpackedTraffic<<endl;
			cout<<"Unpacked transit cost: "<<unpackedCost<<endl;
			cout<<"Peering cost: "<<peeringCost<<endl;

#endif

			if((unpackedCost+peeringCost)<=absoluteCostForPeering && (unpackedCost+peeringCost)<=absoluteCostForTransit){

				for(list<VolumePrice>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){
					if(!isPresentInList<VolumePrice>(remainingPeers,*it))
						if(nodePointers[(*it).linkedNode]->applyPeeringCriteria(nodeId)==PEER)
							this->getSettlementFreePeer((*it).linkedNode,false);
				}

#if DEBUG
				cout<<"Going with packing option"<<endl;
#endif

				return;
			}

			if(absoluteCostForPeering<=(unpackedCost+peeringCost) && absoluteCostForPeering<=absoluteCostForTransit){
				for(list<VolumePrice>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){
					if(nodePointers[(*it).linkedNode]->applyPeeringCriteria(nodeId)==PEER)
						this->getSettlementFreePeer((*it).linkedNode,false);
				}

#if DEBUG
				cout<<"Going with absolute peering option"<<endl;
#endif

				return;
			}

			else{
				//absolute cost for transit is less than any other option
#if DEBUG
				cout<<"Going with transit option"<<endl;
#endif

				return;
			}

		}

	}


}

void Node::peerSelectionFFDLR(){

	list<VolumePrice> potentialPeers;
	list<IXPPort> packedPeersPorts;
	IXPPort port;
	VolumePrice tempObj;

	double totalTraffic=0;

	//computing cost of complete peering option
	for(unsigned int i=0;i<Node::activeNodes;i++){
		if(i!=nodeId && this->isCoLocated(i) && !this->isPresentInCustomerTree(i) && !this->isPeer(i) && !nodePointers[i]->isPresentInCustomerTree(nodeId)){
			if(nodePointers[i]->applyPeeringCriteria(nodeId)==PEER && applyPeeringCriteria(i)==PEER){
				tempObj.linkedNode=i;
				//tempObj.volume=trafficSent[i]+nodePointers[i]->trafficSent[nodeId];
				potentialPeers.push_back(tempObj);
				totalTraffic+=tempObj.volume;

				this->getSettlementFreePeer(i,false);
			}
		}
	}

	computeTrafficFlowsAcrossNode(nodeId);
	updateVt();
	totalTraffic=Vpp;

	for(list<NodePrice>::iterator it=K.begin();it!=K.end();it++){

		for(list<VolumePrice>::iterator itp=potentialPeers.begin();itp!=potentialPeers.end();itp++){

			if((*it).nId==(*itp).linkedNode){
				(*itp).volume=linkValueVector[linkIndex[nodeId][(*it).nId].index];

				if((*itp).volume>100000)
					(*itp).volume=100000;
			}

		}

	}

	peeringPorts.clear();

	binPackFFDLR(potentialPeers,peeringPorts);

	updateVt();
	updateFitness();

#if 0
	cout<<"Utility with packing is: "<<fitness<<endl;
#endif

}

void Node::peerSelectionGreedyPack(){

	list<VolumePrice> potentialPeers;
	list<unsigned int> packedPeers;
	VolumePrice tempObj;
	double totalTraffic=0;
	double transitOnlyUtility=0;
	double peeringOnlyUtility=0;

	double oneGPeeringCost, tenGPeeringCost, hundredGPeeringCost;
	double oneGPeeringUtility, tenGPeeringUtility, hundredGPeeringUtility;

	//computing cost of transit only
	computeTrafficFlowsAcrossNode(nodeId);
	updateVt();
	updateFitness();
	transitOnlyUtility=fitness;

#if 0
	cout<<"Transit only utility: "<<transitOnlyUtility<<endl;
	cout<<"Transit only providerCost: "<<providerCost<<"\t customerRevenue: "<<customerRevenue<<"\t peeringCost: "<<this->freePeerCost<<endl;
#endif

	//computing cost of complete peering option
	for(unsigned int i=0;i<Node::activeNodes;i++){
		if(i!=nodeId && this->isCoLocated(i) && !this->isPresentInCustomerTree(i) && !this->isPeer(i) && !nodePointers[i]->isPresentInCustomerTree(nodeId)){
			if(nodePointers[i]->applyPeeringCriteria(nodeId)==PEER && applyPeeringCriteria(i)==PEER){
				tempObj.linkedNode=i;
				tempObj.volume=trafficSent[i]+nodePointers[i]->trafficSent[nodeId];
				potentialPeers.push_back(tempObj);
				totalTraffic+=tempObj.volume;

				this->getSettlementFreePeer(i,false);
			}
		}
	}

	computeTrafficFlowsAcrossNode(nodeId);
	updateIXPPorts();
	updateVt();
	updateFitness();
	peeringOnlyUtility=fitness;

#if 0
	cout<<"Peering only utility: "<<peeringOnlyUtility<<endl;
	cout<<"Peering only providerCost: "<<providerCost<<"\t customerRevenue: "<<customerRevenue<<"\t peeringCost: "<<this->freePeerCost<<endl;
#endif



#if 0
	cout<<"Number of potential peers: "<<potentialPeers.size()<<endl;
	cout<<"Total possible peering traffic: "<<totalTraffic<<endl;
	cout<<"Absolute Utility For Transit: "<<transitOnlyUtility<<endl;
	cout<<"Absolute Utility For Peering: "<<peeringOnlyUtility<<endl;
#endif

	for(list<VolumePrice>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){

		dePeer((*it).linkedNode);

	}
	peeringPorts.clear();
	packedPeers.clear();
	oneGPeeringCost=binPackGreedy(ONE_G,potentialPeers,packedPeers,false,totalTraffic);
	for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
		this->getSettlementFreePeer(*it,false);
	}
	computeTrafficFlowsAcrossNode(nodeId);
	updateIXPPorts();
	updateVt();
	updateFitness();
	oneGPeeringUtility=this->customerRevenue-this->providerCost-this->freePeerCost;

#if 0
	cout<<"ONE_G utility: "<<oneGPeeringUtility<<endl;
	cout<<"ONE_G providerCost: "<<providerCost<<"\t customerRevenue: "<<customerRevenue<<"\t oneGPeeringCost: "<<this->freePeerCost<<endl;
#endif

	for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
		this->dePeer(*it);
	}
	peeringPorts.clear();
	packedPeers.clear();
	tenGPeeringCost=binPackGreedy(TEN_G,potentialPeers,packedPeers,false,totalTraffic);
	for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
		this->getSettlementFreePeer(*it,false);
	}
	computeTrafficFlowsAcrossNode(nodeId);
	updateIXPPorts();
	updateVt();
	updateFitness();
	tenGPeeringUtility=this->customerRevenue-this->providerCost-this->freePeerCost;


#if 0
	cout<<"TEN_G utility: "<<tenGPeeringUtility<<endl;
	cout<<"TEN_G providerCost: "<<providerCost<<"\t customerRevenue: "<<customerRevenue<<"\t tenGPeeringCost: "<<this->freePeerCost<<endl;
#endif


	for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
		this->dePeer(*it);
	}
	packedPeers.clear();
	peeringPorts.clear();
	hundredGPeeringCost=binPackGreedy(HUNDRED_G,potentialPeers,packedPeers,false,totalTraffic);
	for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
		this->getSettlementFreePeer(*it,false);
	}
	computeTrafficFlowsAcrossNode(nodeId);
	updateIXPPorts();
	updateVt();
	updateFitness();
	hundredGPeeringUtility=this->customerRevenue-this->providerCost-this->freePeerCost;



#if 0
	cout<<"HUNDRED_G utility: "<<hundredGPeeringUtility<<endl;
	cout<<"HUNDRED_G providerCost: "<<providerCost<<"\t customerRevenue: "<<customerRevenue<<"\t hundredGPeeringCost: "<<this->freePeerCost<<endl;
#endif

	/*
	for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
		this->dePeer(*it);
	}
	packedPeers.clear();
	peeringPorts.clear();
	hundredMGPeeringCost=binPackGreedy(HUNDRED_G,potentialPeers,packedPeers,true,totalTraffic);
	for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
		this->getSettlementFreePeer(*it,false);
	}
	computeTrafficFlowsAcrossNode(nodeId);
	updateIXPPorts();
	updateVt();
	updateFitness();
	hundredMGPeeringUtility=this->customerRevenue-this->providerCost-this->freePeerCost;


#if 0
	cout<<"HUNDRED_MG utility: "<<hundredMGPeeringUtility<<endl;
	cout<<"HUNDRED_MG providerCost: "<<providerCost<<"\t customerRevenue: "<<customerRevenue<<"\t hundredGPeeringCost: "<<this->freePeerCost<<endl;
#endif

	*/
	for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
		this->dePeer(*it);
	}
	packedPeers.clear();
	peeringPorts.clear();

	if(transitOnlyUtility>=peeringOnlyUtility && transitOnlyUtility>=oneGPeeringUtility && transitOnlyUtility>=tenGPeeringUtility && transitOnlyUtility>=hundredGPeeringUtility){
		for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
			this->dePeer(*it);
		}
		packedPeers.clear();
		peeringPorts.clear();
		computeTrafficFlowsAcrossNode(nodeId);
		updateVt();
		updateFitness();

#if 0
		cout<<"Transit only option chosen"<<endl;
#endif

	}

	else if(peeringOnlyUtility>=transitOnlyUtility && peeringOnlyUtility>=oneGPeeringUtility && peeringOnlyUtility>=tenGPeeringUtility && peeringOnlyUtility>=hundredGPeeringUtility){
		for(list<VolumePrice>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){
			this->getSettlementFreePeer((*it).linkedNode,false);
		}
		computeTrafficFlowsAcrossNode(nodeId);
		updateIXPPorts();
		updateVt();
		updateFitness();

#if 0
		cout<<"Peering only option chosen"<<endl;
#endif

	}

	else if(oneGPeeringUtility>=transitOnlyUtility && peeringOnlyUtility<=oneGPeeringUtility && oneGPeeringUtility>=tenGPeeringUtility && oneGPeeringUtility>=hundredGPeeringUtility){
		oneGPeeringCost=binPackGreedy(ONE_G,potentialPeers,packedPeers,false,totalTraffic);
		for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
			this->getSettlementFreePeer(*it,false);
		}
		computeTrafficFlowsAcrossNode(nodeId);
		updateVt();
		updateFitness();
		fitness=this->customerRevenue-this->providerCost-oneGPeeringCost;

#if 0
		cout<<"ONE_G only option chosen"<<endl;
#endif


	}

	else if(tenGPeeringUtility>=transitOnlyUtility && peeringOnlyUtility<=tenGPeeringUtility && oneGPeeringUtility<=tenGPeeringUtility && tenGPeeringUtility>=hundredGPeeringUtility){
		tenGPeeringCost=binPackGreedy(TEN_G,potentialPeers,packedPeers,false,totalTraffic);
		for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
			this->getSettlementFreePeer(*it,false);
		}
		computeTrafficFlowsAcrossNode(nodeId);
		updateVt();
		updateFitness();
		fitness=this->customerRevenue-this->providerCost-tenGPeeringCost;

#if 0
		cout<<"TEN_G only option chosen"<<endl;
#endif


	}

	else{
		hundredGPeeringCost=binPackGreedy(HUNDRED_G,potentialPeers,packedPeers,false,totalTraffic);
		for(list<unsigned int>::iterator it=packedPeers.begin();it!=packedPeers.end();it++){
			this->getSettlementFreePeer(*it,false);
		}
		computeTrafficFlowsAcrossNode(nodeId);
		updateVt();
		updateFitness();
		fitness=this->customerRevenue-this->providerCost-hundredGPeeringCost;

#if 0
		cout<<"HUNDRED_G only option chosen"<<endl;
#endif

	}


}

double Node::computePeeringCostForTraffic(double traffic){

	updateIXPPorts(traffic);

	double peeringCost=0;
	for(vector<IXPPort>::iterator it=peeringPorts.begin();it!=peeringPorts.end();it++){

#if 0
		cout<<"Allocated port ";
		if((*it).capacity==ONE_G)
			cout<<"ONE_G";
		else if((*it).capacity==TEN_G)
			cout<<"TEN_G";
		else if((*it).capacity==HUNDRED_G)
			cout<<"HUNDRED_G";
		else{
			string str="ERROR!!! Unknown port capacity encountered";
			endSimulation(str);
		}
		cout<<endl;

#endif

		peeringCost+=(*it).getPortCosts();

	}

	return peeringCost;
}
