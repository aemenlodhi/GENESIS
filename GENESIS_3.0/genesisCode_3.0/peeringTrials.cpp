#include "node.h"
#include "support.h"

peeringDecision Node::tryAndVerify(const unsigned int& id){

	peeringTrialsPeersStruct tempObj;

#if DEBUG
		cout<<"Node "<<nodeId<<" trying and verifying "<<id<<endl;
#endif

	getSettlementFreePeer(id,false);

#if DEBUG
		cout<<"Node "<<nodeId<<" temporarily peered with "<<id<<endl;
#endif

	computeTrafficFlowsAcrossNode(nodeId);


#if DEBUG
		cout<<"Temporary flow computations complete"<<endl;
#endif



#if DEBUG
		cout<<"Node "<<nodeId<<" depeered with "<<id<<endl;
#endif


#if DEBUG
		cout<<"Node "<<nodeId<<" tried and verified "<<id<<endl;
#endif



	{

		if(nodeId<id){
			tempObj.inboundTraffic=linkValueVectorFlatLeft[linkIndex[nodeId][id].index];
			tempObj.outboundTraffic=linkValueVectorFlatRight[linkIndex[nodeId][id].index];
			tempObj.totalTraffic=linkValueVector[linkIndex[nodeId][id].index];

			dePeer(id);

			if((tempObj.inboundTraffic/tempObj.outboundTraffic)<=selectivePeerCriteria && tempObj.totalTraffic>=peeringThreshold)
				return PEER;
			else
				return DONTPEER;
		}

		else{

			tempObj.outboundTraffic=linkValueVectorFlatLeft[linkIndex[nodeId][id].index];
			tempObj.inboundTraffic=linkValueVectorFlatRight[linkIndex[nodeId][id].index];
			tempObj.totalTraffic=linkValueVector[linkIndex[nodeId][id].index];

			dePeer(id);

			if((tempObj.inboundTraffic/tempObj.outboundTraffic)<=selectivePeerCriteria && tempObj.totalTraffic>=peeringThreshold)
				return PEER;
			else
				return DONTPEER;

		}

	}

	return DONTPEER;

}

void Node::peerOperatorTrial(bool includePotentialCustomers){

	set<unsigned int> potentialPeers;
	list<peeringTrialsPeersStruct> peersToConsider;
	peeringTrialsPeersStruct tempObj;
	peeringTrialsPeersContemporary.clear();

#if DEBUG
	cout<<"Node "<<nodeId<<" acquiring peers by applying peerOperatorTrial"<<endl;
#endif

	for(unsigned int i=0;i<Node::activeNodes;i++){
		//if(i==nodeId || !this->isCoLocated(i) || isPeer((*it).second.nId) || isPresentInCustomerTree((*it).second.nId) || nodePointers[(*it).second.nId]->isPresentInCustomerTree(nodeId)){}
		if(i==nodeId || (includePotentialCustomers==false && isPotentialCustomer(i)) || !this->isCoLocated(i) || isPeer(i) || isPresentInCustomerTree(i) || nodePointers[i]->isPresentInCustomerTree(nodeId)){}
		else{

			potentialPeers.insert(i);

#if 1
			cout<<"Potential peer: "<<i<<endl;
#endif
		}
	}

#if DEBUG
				cout<<"Potential peers determined"<<endl;
#endif

	for(set<unsigned int>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){

		tempObj.restore();
		tempObj.peers.insert(*it);
		tempObj.inboundTraffic=nodePointers[*it]->trafficSent[nodeId];
		tempObj.outboundTraffic=trafficSent[*it];
		tempObj.totalTraffic=tempObj.inboundTraffic+tempObj.outboundTraffic;

		if(tempObj.totalTraffic>=peeringThreshold)
			peersToConsider.push_back(tempObj);

	}

	peersToConsider.sort(sortReverseByTotalTraffic);

#if DEBUG
		cout<<peersToConsider.size()<<" potential peers sorted"<<endl;
#endif

	std::set<unsigned int>::iterator itS;
	for(list<peeringTrialsPeersStruct>::iterator it=peersToConsider.begin();it!=peersToConsider.end();it++){
		if(((*it).inboundTraffic/(*it).outboundTraffic)<=selectivePeerCriteria){

			itS=(*it).peers.begin();

			if(tryAndVerify(*itS)==PEER && nodePointers[*itS]->applyPeeringCriteria(nodeId)==PEER){

#if DEBUG
			cout<<"Node "<<nodeId<<" peering with "<<*itS<<endl;
#endif

				this->getSettlementFreePeer(*itS,false);
				peeringTrialsPeersContemporary[static_cast<ostringstream*>( &(ostringstream() << *((*it).peers.begin())) )->str()]=*it;

#if DEBUG
			cout<<"Node "<<nodeId<<" peered with "<<*itS<<endl;
#endif

			}

		}

	}

}

void Node::peerOperatorNoTrial(bool includePotentialCustomers){

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


	for(set<unsigned int>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){

		tempObj.restore();
		tempObj.peers.insert(*it);
		tempObj.inboundTraffic=nodePointers[*it]->trafficSent[nodeId];
		tempObj.outboundTraffic=trafficSent[*it];
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

NodePrice Node::estimateUtility(const unsigned int& id, estimatorStrength es){

	NodePrice np;
	np.nId=id;
	peeringTrialsPeersStruct tempObj;
	vector<int> flowsSym;
	vector<int> flowsAsym;

	double eProviderCost=0;
	double eCustomerRevenue=0;
	double ePeerCost=0;


	computeTrafficFlowsAcrossNode(nodeId);
	updateIXPPorts();
	updateFitness();


	eCustomerRevenue=this->customerRevenue;

	double peeringTraffic=Vpp;
	vector<int> upstreamFlowsSym;
	vector<int> upstreamFlowsAsym;

	tempObj.peers.insert(id);

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

	//difference in upstream traffic

	if(!Q.empty()){
		for(list<NodePrice>::iterator itQ=Q.begin();itQ!=Q.end();itQ++){
			std::copy(linkIndex[nodeId][(*itQ).nId].flowsSym.begin(),linkIndex[nodeId][(*itQ).nId].flowsSym.end(),std::back_inserter(upstreamFlowsSym));
			std::copy(linkIndex[nodeId][(*itQ).nId].flowsAsym.begin(),linkIndex[nodeId][(*itQ).nId].flowsAsym.end(),std::back_inserter(upstreamFlowsAsym));

		}

		std::sort(upstreamFlowsSym.begin(),upstreamFlowsSym.end());
		std::sort(upstreamFlowsAsym.begin(),upstreamFlowsAsym.end());
		std::unique(upstreamFlowsSym.begin(),upstreamFlowsSym.end());
		std::unique(upstreamFlowsAsym.begin(),upstreamFlowsAsym.end());

		std::sort(flowsSym.begin(),flowsSym.end());
		std::sort(flowsAsym.begin(),flowsAsym.end());
		std::unique(flowsSym.begin(),flowsSym.end());
		std::unique(flowsAsym.begin(),flowsAsym.end());

		vector<int> commonFlowsSym;
		vector<int> commonFlowsAsym;

		std::set_intersection(flowsSym.begin(),flowsSym.end(),upstreamFlowsSym.begin(),upstreamFlowsSym.end(),std::back_inserter(commonFlowsSym));
		std::set_intersection(flowsAsym.begin(),flowsAsym.end(),upstreamFlowsAsym.begin(),upstreamFlowsAsym.end(),std::back_inserter(commonFlowsAsym));
#if 1
		cout<<"Number of common flows: "<<commonFlowsSym.size()+commonFlowsAsym.size()<<endl;
#endif
		for(std::vector<int>::iterator itV=commonFlowsSym.begin();itV!=commonFlowsSym.end();itV++)
			for(list<NodePrice>::iterator itQ=Q.begin();itQ!=Q.end();itQ++){

				if(std::find(linkIndex[nodeId][(*itQ).nId].flowsSym.begin(),linkIndex[nodeId][(*itQ).nId].flowsSym.end(),*itV)!=linkIndex[nodeId][(*itQ).nId].flowsSym.end()){

					for(list<VolumePrice>::iterator itP=providerVPList.begin();itP!=providerVPList.end();itP++){
						if((*itP).linkedNode==(*itQ).nId){
							(*itP).volume-=flowValueVector[*itV];
							peeringTraffic+=flowValueVector[*itV];
							break;
						}

					}

				}

			}


		for(std::vector<int>::iterator itV=commonFlowsAsym.begin();itV!=commonFlowsAsym.end();itV++)
			for(list<NodePrice>::iterator itQ=Q.begin();itQ!=Q.end();itQ++){

				if(std::find(linkIndex[nodeId][(*itQ).nId].flowsAsym.begin(),linkIndex[nodeId][(*itQ).nId].flowsAsym.end(),*itV)!=linkIndex[nodeId][(*itQ).nId].flowsAsym.end()){

					for(list<VolumePrice>::iterator itP=providerVPList.begin();itP!=providerVPList.end();itP++){
						if((*itP).linkedNode==(*itQ).nId){
							(*itP).volume-=flowValueVectorAsym[*itV];
							peeringTraffic+=flowValueVectorAsym[*itV];
							break;
						}

					}

				}

			}


		for(std::list<VolumePrice>::iterator itVP=providerVPList.begin();itVP!=providerVPList.end();itVP++){

			//eProviderCost+=((*itVP).contractPrice*pow((*itVP).volume,transitCostExponent));

			if((*itVP).volume<100){
				eProviderCost+=(6*(*itVP).volume);
			}

			else if((*itVP).volume>=100 && (*itVP).volume<1000){
				eProviderCost+=(4*(*itVP).volume);
			}

			else
				eProviderCost+=(1*(*itVP).volume);



#if DEBUG
			cout<<eProviderCost<<":\t"<<(*itVP).contractPrice<<"*"<<(*itVP).volume<<endl;
#endif
		}

#if 1
		cout<<"Estimated Provider costs: "<<eProviderCost<<endl;
#endif
#if DEBUG
		cout<<endl;
#endif

		updateIXPPorts(peeringTraffic);

#if 1
		cout<<"Estimated Peering traffic is: "<<peeringTraffic<<" using "<<peeringPorts.size()<<" ports"<<endl;
#endif

		for(vector<IXPPort>::iterator it=peeringPorts.begin();it!=peeringPorts.end();it++){

			if((*it).capacity==ONE_G)
				ePeerCost+=650;
			if((*it).capacity==TEN_G)
				ePeerCost+=1300;
			if((*it).capacity==HUNDRED_G)
				ePeerCost+=6500;

		}
#if 1
		cout<<"Estimated peering cost: "<<ePeerCost<<endl;
#endif

		np.price=(eCustomerRevenue-eProviderCost-ePeerCost)-fitness;

#if DEBUG
		cout<<"Current peeringTraffic: "<<Vpp<<" Current Utility "<<fitness<<" ";
		cout<<"Current providerCost: "<<this->providerCost<<" Current peeringCost: "<<this->freePeerCost<<" Current customerRevenue: "<<this->customerRevenue<<endl;
		cout<<"Estimated peeringTraffic: "<<peeringTraffic<<" and number of ports required "<<ceil(peeringTraffic/PORT_CAPACITY)<<endl;
		cout<<"Estimated utility "<<(eCustomerRevenue-eProviderCost-ePeerCost)<<" Estimated providerCost: "<<eProviderCost<<" estimated peeringCost: "<<ePeerCost<<endl;
#endif

#if 1
		cout<<"Estimated utility difference: "<<np.price<<endl;
#endif


		return np;

	}

	np.price=0;	//if there are no providers then the traffic is already over peers


	return np;

}


void Node::peerNetFlowEstimation(bool includePotentialCustomers, estimatorStrength es){

	set<unsigned int> potentialPeers;
	list<peeringTrialsPeersStruct> peersToConsider;
	peeringTrialsPeersContemporary.clear();

#if 1
	cout<<"Node "<<nodeId<<" acquiring peers by applying peerEstimatorNetFlow"<<endl;
#endif

	for(unsigned int i=0;i<Node::activeNodes;i++){
		//if(i==nodeId || !this->isCoLocated(i) || isPeer((*it).second.nId) || isPresentInCustomerTree((*it).second.nId) || nodePointers[(*it).second.nId]->isPresentInCustomerTree(nodeId)){}
		if(i==nodeId || (includePotentialCustomers==false && isPotentialCustomer(i)) || !this->isCoLocated(i) || isPeer(i) || isPresentInCustomerTree(i) || nodePointers[i]->isPresentInCustomerTree(nodeId)){}
		else{

			potentialPeers.insert(i);

#if 1
			cout<<"Potential peer: "<<i<<endl;
#endif
		}
	}

#if DEBUG
	cout<<potentialPeers.size()<<"\tPotential peers determined"<<endl;
#endif

	//true estimation based scheme
	list<NodePrice> rankingList;
	if(!potentialPeers.empty())
		do{

			rankingList.clear();
			updateIXPPorts();
			updateFitness();

#if 1
			cout<<"Using: "<<peeringPorts.size()<<" ports"<<endl;
			cout<<"Utility is: "<<this->fitness<<endl;
			cout<<"Provider cost is: "<<this->providerCost<<endl;
			cout<<"Peering cost is: "<<this->freePeerCost<<endl;
#endif

			if(!potentialPeers.empty())

#if 1
				cout<<"Evaluating "<<potentialPeers.size()<<" potential peers"<<endl;
#endif

				for(set<unsigned int>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){

#if 1
					cout<<"Estimating utility for "<<*it<<endl;
#endif

					rankingList.push_back(estimateUtility(*it,es));

#if 1
					cout<<"Estimated utility for "<<*it<<endl;
#endif


				}

			if(!rankingList.empty()){
				rankingList.sort(sortReverseByUtility);

				if(rankingList.front().price<0){
#if 1
					cout<<"Front utility decreased"<<endl;
#endif
					rankingList.clear();
				}

				else{

					bool peering=false;
					for(list<NodePrice>::iterator itNP=rankingList.begin();itNP!=rankingList.end();itNP++){
						if(nodePointers[(*itNP).nId]->applyPeeringCriteria(nodeId)==PEER){
							this->getSettlementFreePeer((*itNP).nId,false);
							potentialPeers.erase(potentialPeers.find((*itNP).nId));
#if 1
					cout<<"Peering with "<<(*itNP).nId<<" as part of estimation complete"<<endl;
#endif
							peering=true;
							break;

						}
					}

					if(peering==false)
						rankingList.clear();

				}

			}

	}while(!rankingList.empty());

#if DEBUG
	cout<<"Acquisition of peers by "<<nodeId<<" complete "<<endl;
#endif

	/*
	bool peered=true;
	std::set<unsigned int>::iterator itS;
	double currentFitness=0;
	do{

		peered=false;
		for(set<unsigned int>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){

			tempObj.restore();

			tempObj.peers.insert(*it);

			if(es==TIGHT){
				tempObj.inboundTraffic=nodePointers[*it]->trafficSent[nodeId];
				tempObj.outboundTraffic=estimateTrafficToTight(*it);
			}

			if(es==SLACK){
				tempObj.inboundTraffic=estimateTrafficFromSlack(*it);
				tempObj.outboundTraffic=estimateTrafficToSlack(*it);
			}

			tempObj.totalTraffic=tempObj.inboundTraffic+tempObj.outboundTraffic;

			if(tempObj.totalTraffic>=peeringThreshold && (tempObj.inboundTraffic/tempObj.outboundTraffic)<=selectivePeerCriteria){

				//carrying out CBA
				updateFitness();
				currentFitness=this->fitness;
				this->getSettlementFreePeer(*it);
				computeTrafficFlowsAcrossNode(nodeId);
				updateFitness();
				if(this->fitness>=currentFitness){	//acquired peer *it
					peered=true;
					potentialPeers.erase(it);
					break;
				}

				else{
					dePeer(*it);
				}

			}

		}

	}while(peered==true);
	*/

#if DEBUG
	cout<<peersToConsider.size()<<" potential peers sorted"<<endl;
	for(std::list<peeringTrialsPeersStruct>::iterator it=peersToConsider.begin();it!=peersToConsider.end();it++)
		cout<<*((*it).peers.begin())<<endl;
#endif

}

bool Node::isTrialCandidate(unsigned int& id){	//is it a trial candidate or an estimation candidate

	static list<unsigned int> p1c;
	static unsigned int jSize=0;
	list<unsigned int> p2c;
	list<unsigned int> intersection;
	double tempD=this->trafficSent[id]+nodePointers[id]->trafficSent[nodeId];

	if(p1c.empty() || jSize==0 || jSize!=J.size()){
		p1c.clear();
		for(list<NodePrice>::iterator it=J.begin();it!=J.end();it++){
			p1c.push_back((*it).nId);
		}
		jSize=p1c.size();
	}

	for(list<NodePrice>::iterator it=nodePointers[id]->J.begin();it!=nodePointers[id]->J.end();it++){
		p2c.push_back((*it).nId);
	}
	p2c.sort();
	p2c.unique();

	std::set_intersection(p1c.begin(),p1c.end(),p2c.begin(),p2c.end(),intersection.begin());

	if(!intersection.empty())
		return true;

	for(list<unsigned int>::iterator it1=p1c.begin();it1!=p1c.end();it1++)
		for(list<unsigned int>::iterator it2=p2c.begin();it2!=p2c.end();it2++)
			tempD+=(nodePointers[*it1]->trafficSent[*it2]+nodePointers[*it2]->trafficSent[*it1]);

	if(estimateTrafficExchangeSlack(id)!=tempD)
		return true;

	return false;

}

bool Node::isPotentialCustomer(unsigned int id){

	if(this->isCoLocated(id) && this->numGPresence>=nodePointers[id]->numGPresence && this->Vt>nodePointers[id]->Vt && isPresentInCustomerTree(id))
		return true;
	else
		return false;

}

void Node::findTrialCandidates(const set<unsigned int>& ufPeers, list<nodeTrafficRank>& trialCandidates){

	if(ufPeers.empty())
		return;

	vector<int> allFlowsSym;
	vector<int> allFlowsAsym;
	vector<int> estimatedFlowsSym;
	vector<int> estimatedFlowsAsym;
	vector<int> bypassFlowsSym;
	vector<int> bypassFlowsAsym;
	double exchangedTraffic;
	double maxExchangedTraffic=-1;
	double maxWithinCustomerConeSentTraffic=-1;
	double maxWithinCustomerConeReceivedTraffic=-1;
	double maxOutsideCustomerConeSentTraffic=-1;
	double maxOutsideCustomerConeReceivedTraffic=-1;
	nodeTrafficRank ntRank;
	unsigned int sender;
	unsigned int receiver;

	for(list<NodePrice>::iterator itNP=J.begin();itNP!=J.end();itNP++){

		if(trafficSent[(*itNP).nId]>maxWithinCustomerConeSentTraffic)
			maxWithinCustomerConeSentTraffic=trafficSent[(*itNP).nId];

		if(trafficReceived[(*itNP).nId]>maxWithinCustomerConeReceivedTraffic)
			maxWithinCustomerConeReceivedTraffic=trafficReceived[(*itNP).nId];

	}

	for(set<unsigned int>::const_iterator it=ufPeers.begin();it!=ufPeers.end();it++){

		//sort and uniquify their customer cones
		nodePointers[*it]->J.sort(sortById);
		nodePointers[*it]->J.unique(removeSameId);

		allFlowsSym.clear();
		allFlowsAsym.clear();
		estimatedFlowsSym.clear();
		estimatedFlowsAsym.clear();
		bypassFlowsSym.clear();
		bypassFlowsAsym.clear();
		maxOutsideCustomerConeSentTraffic=-1;
		maxOutsideCustomerConeReceivedTraffic=-1;

		ntRank.id=*it;

		exchangedTraffic=estimateTrafficExchangeSlack(*it,estimatedFlowsSym,estimatedFlowsAsym);
		if(exchangedTraffic>maxExchangedTraffic)
			maxExchangedTraffic=exchangedTraffic;

		ntRank.transitWeight=exchangedTraffic;	//later after the loop we divide it by maxexchanged traffic to determine the weight
		ntRank.transitFlows=estimatedFlowsSym.size()+estimatedFlowsAsym.size();
		//dealing with bypass flows

		//find maximum local traffic exchanged with any customer cone member of the potential peer
		for(list<NodePrice>::iterator ity=nodePointers[*it]->J.begin();ity!=nodePointers[*it]->J.end();ity++){
			if(trafficSent[(*ity).nId]>maxOutsideCustomerConeSentTraffic)
				maxOutsideCustomerConeSentTraffic=trafficSent[(*ity).nId];

			if(trafficReceived[(*ity).nId]>maxOutsideCustomerConeReceivedTraffic)
				maxOutsideCustomerConeReceivedTraffic=trafficReceived[(*ity).nId];
		}


		//find all possible flows that can traverse the peering link
		for(list<NodePrice>::iterator itx=J.begin();itx!=J.end();itx++){
			for(list<NodePrice>::iterator ity=nodePointers[*it]->J.begin();ity!=nodePointers[*it]->J.end();ity++){
				if(!isPresentInCustomerTree((*ity).nId)){	//not present in customer cones of both nodes

					allFlowsSym.push_back(flowIndex[(*itx).nId][(*ity).nId]);
					allFlowsAsym.push_back(flowIndex[(*itx).nId][(*ity).nId]);

				}//end if
			}//end for
		}//end for


		ntRank.totalFlows=allFlowsSym.size()+allFlowsAsym.size();

		//find flows that currently bypass you
		std::set_difference(allFlowsSym.begin(),allFlowsSym.end(),estimatedFlowsSym.begin(),estimatedFlowsSym.end(),back_inserter(bypassFlowsSym));
		std::set_difference(allFlowsAsym.begin(),allFlowsAsym.end(),estimatedFlowsAsym.begin(),estimatedFlowsAsym.end(),back_inserter(bypassFlowsAsym));

		ntRank.bypassFlows=bypassFlowsSym.size()+bypassFlowsAsym.size();

		//assign weight to each flow
		for(vector<int>::iterator itb=bypassFlowsSym.begin();itb!=bypassFlowsSym.end();itb++){

			sender=flowSymMap[*itb].n1;
			receiver=flowSymMap[*itb].n2;

			if(isPresentInCustomerTree(sender))
				ntRank.bypassWeight+=((trafficReceived[sender]/maxWithinCustomerConeReceivedTraffic)*(trafficSent[receiver]/maxOutsideCustomerConeSentTraffic));

			else
				ntRank.bypassWeight+=((trafficSent[receiver]/maxWithinCustomerConeSentTraffic)*(trafficReceived[sender]/maxOutsideCustomerConeReceivedTraffic));

		}//end for bypass flowsSym

		//assign weight to each flow
		for(vector<int>::iterator itb=bypassFlowsAsym.begin();itb!=bypassFlowsAsym.end();itb++){

			sender=flowAsymMap[*itb].n1;
			receiver=flowAsymMap[*itb].n2;

			if(isPresentInCustomerTree(sender))
				ntRank.bypassWeight+=((trafficReceived[sender]/maxWithinCustomerConeReceivedTraffic)*(trafficSent[receiver]/maxOutsideCustomerConeSentTraffic));

			else
				ntRank.bypassWeight+=((trafficSent[receiver]/maxWithinCustomerConeSentTraffic)*(trafficReceived[sender]/maxOutsideCustomerConeReceivedTraffic));

		}//end for bypass flowsAsym

		ntRank.bypassWeight=ntRank.bypassWeight/(bypassFlowsSym.size()+bypassFlowsAsym.size());

		trialCandidates.push_back(ntRank);

	}//end main for


	for(list<nodeTrafficRank>::iterator it=trialCandidates.begin();it!=trialCandidates.end();it++){

		(*it).transitWeight=(*it).transitWeight/maxExchangedTraffic;
		(*it).totalWeight=(((*it).transitFlows)/((*it).totalFlows))*(*it).transitWeight + (((*it).bypassFlows)/((*it).totalFlows))*(*it).bypassWeight;

	}

	trialCandidates.sort(sortReverseByTotalWeight);

}

void Node::dopeeringTrialsProposed(bool includePotentialCustomers){

	set<unsigned int> potentialPeersStubs;
	set<unsigned int> potentialPeersProviders;
	list<unsigned int> potentialPeersProvidersFullExchange;
	list<unsigned int> potentialPeersProvidersPartialExchange;

	peeringTrialsPeers.clear();
	peeringTrialsFlows.clear();
	peeringTrialsFlowsAsym.clear();

	for(std::multimap<unsigned int,NodePrice>::iterator it=colocatedNodePrice.begin();it!=colocatedNodePrice.end();it++){
		if((includePotentialCustomers==false && isPotentialCustomer((*it).second.nId)) || isPeer((*it).second.nId) || isPresentInCustomerTree((*it).second.nId) || nodePointers[(*it).second.nId]->isPresentInCustomerTree(nodeId)){}
		else{
			if(nodePointers[(*it).second.nId]->I.empty())
				potentialPeersStubs.insert((*it).second.nId);
			else
				potentialPeersProviders.insert((*it).second.nId);
		}
	}

	//trials for stubs
	if(!potentialPeersStubs.empty())
		peeringTrialsProposedStubs(potentialPeersStubs);


	//trials for providers
	if(!potentialPeersProviders.empty())
		peeringTrialsProposedProviders(potentialPeersProviders);

	//clear up memory used by redundant data structures
	peeringTrialsPeers.clear();
	peeringTrialsFlows.clear();
	peeringTrialsFlowsAsym.clear();
	combinationsTrials.clear();

}

void Node::peeringTrialsProposedStubs(set<unsigned int>& potentialPeersStubs){

	//Trial with stubs
	peeringTrialsPeersStruct pt;
	peeringTrialsFlowsStruct lt;
	ptfsMapIt mIt;
	flowPair fp;

	cout<<"Node "<<nodeId<<" will try "<<potentialPeersStubs.size()<<" stubs for first trial: ";

	for(set<unsigned int>::iterator it=potentialPeersStubs.begin();it!=potentialPeersStubs.end();it++){
		getSettlementFreePeer(*it,false);
		cout<<*it<<"\t";
	}
	cout<<endl;

	//TODO find an optimization function for partial routing
	computeTrafficFlowsAcrossNetwork();

	for(set<unsigned int>::iterator it=potentialPeersStubs.begin();it!=potentialPeersStubs.end();it++){

		if(nodeId<*it){
			pt.inboundTraffic=linkValueVectorFlatLeft[linkIndex[nodeId][*it].index];
			pt.outboundTraffic=linkValueVectorFlatRight[linkIndex[nodeId][*it].index];
		}

		else{
			pt.inboundTraffic=linkValueVectorFlatRight[linkIndex[nodeId][*it].index];
			pt.outboundTraffic=linkValueVectorFlatLeft[linkIndex[nodeId][*it].index];
		}

		pt.totalTraffic=linkValueVector[linkIndex[nodeId][*it].index];
		pt.peers.insert(*it);
		pt.flows=linkIndex[nodeId][*it].flowsSym;
		pt.flowsAsym=linkIndex[nodeId][*it].flowsAsym;

		peeringTrialsPeersProposed[static_cast<ostringstream*>( &(ostringstream() << (*it)) )->str()]=pt;

		for(vector<int>::iterator itV=linkIndex[nodeId][*it].flowsSym.begin();itV!=linkIndex[nodeId][*it].flowsSym.end();itV++){

			fp.n1=flowSymMap[*itV].n1;
			fp.n2=flowSymMap[*itV].n2;

			if(!(flowSymMap[*itV].n1==*it || flowSymMap[*itV].n2==*it)){
				cout<<"PROBLEM with flow "<<flowSymMap[*itV].n1<<" -> "<<flowSymMap[*itV].n2<<endl;
			}

			mIt=peeringTrialsFlows.find(fp);
			lt.restore();

			cout<<"Trial with "<<*it<<" FlowNum: "<<*itV<<" "<<flowSymMap[*itV].n1<<" -> "<<flowSymMap[*itV].n2;

			if(mIt==peeringTrialsFlows.end()){

				if(flowSymMap[*itV].n1==nodeId || isPresentInCustomerTree(flowSymMap[*itV].n1)){
					lt.insider=flowSymMap[*itV].n1;
					lt.outsider=flowSymMap[*itV].n2;
					lt.flowDirection=OUTBOUND;
				}

				else{
					lt.insider=flowSymMap[*itV].n2;
					lt.outsider=flowSymMap[*itV].n1;
					lt.flowDirection=INBOUND;
				}

				lt.peers.insert(*it);
				cout<<" goes over peer "<<*it<<endl;

				if(lt.insider==lt.outsider){
					cout<<endl<<"Problem with peer "<<*it<<" flow between "<<lt.insider<<" and "<<lt.outsider<<endl;

					if(flowSymMap[*itV].n1==flowSymMap[*itV].n2)
						cout<<"And the problem is bigger"<<endl;
				}


				peeringTrialsFlows.insert(std::pair<flowPair,peeringTrialsFlowsStruct>(fp,lt));

			}//end if

			else{
				mIt->second.peers.insert(*it);
				cout<<" PROBLEMATIC goes over peer "<<*it<<" when flow is actually "<<mIt->first.n1<<" "<<mIt->first.n2<<endl;
			}

		}//end for

		lt.restore();

		for(vector<int>::iterator itV=linkIndex[nodeId][*it].flowsAsym.begin();itV!=linkIndex[nodeId][*it].flowsAsym.end();itV++){

			if(!(flowAsymMap[*itV].n1==*it || flowAsymMap[*itV].n2==*it)){
				cout<<"PROBLEM with flow "<<flowAsymMap[*itV].n1<<" -> "<<flowAsymMap[*itV].n2<<endl;
			}

			fp.n1=flowAsymMap[*itV].n1;
			fp.n2=flowAsymMap[*itV].n2;

			mIt=peeringTrialsFlowsAsym.find(fp);
			lt.restore();

			cout<<"Trial with "<<*it<<" FlowNum: "<<*itV<<" "<<flowAsymMap[*itV].n1<<" -> "<<flowAsymMap[*itV].n2;
			if(mIt==peeringTrialsFlowsAsym.end()){

				if(flowAsymMap[*itV].n1==nodeId || isPresentInCustomerTree(flowAsymMap[*itV].n1)){
					lt.insider=flowAsymMap[*itV].n1;
					lt.outsider=flowAsymMap[*itV].n2;
					lt.flowDirection=OUTBOUND;
				}

				else{
					lt.insider=flowAsymMap[*itV].n2;
					lt.outsider=flowAsymMap[*itV].n1;
					lt.flowDirection=INBOUND;
				}

				if(lt.insider==lt.outsider){
					cout<<endl<<"Problem with peer "<<*it<<" flow between "<<lt.insider<<" and "<<lt.outsider<<endl;

					if(flowSymMap[*itV].n1==flowSymMap[*itV].n2)
						cout<<"And the problem is bigger"<<endl;
				}


				lt.peers.insert(*it);
				cout<<" goes over peer "<<*it<<endl;
				peeringTrialsFlowsAsym.insert(std::pair<flowPair,peeringTrialsFlowsStruct>(fp,lt));

			}

			else{
				cout<<" PROBLEMATIC goes over peer "<<*it<<" when flow is actually "<<mIt->first.n1<<" "<<mIt->first.n2<<endl;
				mIt->second.peers.insert(*it);
			}

		}//end for

	}

	for(set<unsigned int>::iterator it=potentialPeersStubs.begin();it!=potentialPeersStubs.end();it++)
		dePeer(*it);

	cout<<"Node "<<nodeId<<" tried "<<potentialPeersStubs.size()<<" stubs for first trial"<<endl;

	/*
	for(std::map<flowPair,peeringTrialsFlowsStruct>::iterator it=peeringTrialsFlows.begin();it!=peeringTrialsFlows.end();it++){
		if((*it).second.peers.size()>0){
			cout<<"Stub_Trial Flow ";
			if((*it).second.flowDirection==INBOUND){
				cout<<(*it).second.outsider<<" -> "<<(*it).second.insider;
			}

			else{
				cout<<(*it).second.insider<<" -> "<<(*it).second.outsider;
			}
			cout<<" goes over "<<(*it).second.peers.size()<<" peers: ";
			for(std::set<unsigned int>::iterator chimp=(*it).second.peers.begin();chimp!=(*it).second.peers.end();chimp++)
				cout<<*chimp<<" \t";
			cout<<endl;
		}
	}*/

}

void Node::peeringTrialsProposedProviders(set<unsigned int>& potentialPeersProviders){

	list<unsigned int> someUnknownFlows;
	list<unsigned int> allKnownFlows;
	list<nodeTrafficRank> trialCandidates;

	/*
	for(set<unsigned int>::iterator it=potentialPeersProviders.begin();it!=potentialPeersProviders.end();it++){
		someUnknownFlows.push_back(*it);
	}

	//deal with estimation candidates \mathcal set K
	if(!allKnownFlows.empty()){

		peeringTrialsPeersStruct pt;
		peeringTrialsFlowsStruct lt;

		cout<<"Node "<<nodeId<<" running estimations"<<endl;

		for(list<unsigned int>::iterator it=allKnownFlows.begin();it!=allKnownFlows.end();it++){

			pt.peers.insert(*it);
			pt.inboundTraffic=estimateTrafficFrom(*it);
			pt.outboundTraffic=estimateTrafficTo(*it);
			pt.totalTraffic=estimateTrafficExchange(*it,pt.flows,pt.flowsAsym);

			peeringEstimatedPeersProposed[static_cast<ostringstream*>( &(ostringstream() << (*it)) )->str()]=pt;

			for(vector<int>::iterator itV=pt.flows.begin();itV!=pt.flows.end();itV++){

				if(flowSymMap[flowDirectionFrom[*itV]].n1==nodeId){
					lt.insider=nodeId;
					lt.outsider=*it;
					lt.flowDirection=OUTBOUND;
				}

				else if(isPresentInCustomerTree(flowSymMap[flowDirectionFrom[*itV]].n1)){
					lt.insider=flowSymMap[flowDirectionFrom[*itV]].n1;
					lt.outsider=*it;
					lt.flowDirection=OUTBOUND;
				}

				else{
					lt.insider=*it;
					lt.outsider=flowSymMap[flowDirectionFrom[*itV]].n2;
					lt.flowDirection=INBOUND;
				}

				peeringTrialsFlows.insert(std::pair<int,peeringTrialsFlowsStruct>(*itV,lt));

			}

			for(vector<int>::iterator itV=pt.flowsAsym.begin();itV!=pt.flowsAsym.end();itV++){

				if(flowAsymMap[flowDirectionFromAsym[*itV]].n1==nodeId){
					lt.insider=nodeId;
					lt.outsider=*it;
					lt.flowDirection=OUTBOUND;
				}

				else if(isPresentInCustomerTree(flowAsymMap[flowDirectionFromAsym[*itV]].n1)){
					lt.insider=flowAsymMap[flowDirectionFromAsym[*itV]].n1;
					lt.outsider=*it;
					lt.flowDirection=OUTBOUND;
				}

				else{
					lt.insider=*it;
					lt.outsider=flowAsymMap[flowDirectionFromAsym[*itV]].n2;
					lt.flowDirection=INBOUND;
				}

				peeringTrialsFlowsAsym.insert(std::pair<int,peeringTrialsFlowsStruct>(*itV,lt));

			}

		}

	}//end if for estimation candidates ***Note NO trial was carried out

	else{

		cout<<"No estimation candidate for "<<nodeId<<endl;
	}
	*/

	//deal with trial candidates
	//first figure out candidates for trial
	if(!potentialPeersProviders.empty()){

		cout<<"Node "<<nodeId<<" entering trials with providers"<<endl;

		findTrialCandidates(potentialPeersProviders,trialCandidates); //function returns trial candidates reverse sorted by weight

		cout<<"Node "<<nodeId<<" found "<<trialCandidates.size()<<" trial candidates"<<endl;

		trialWithIndividualProviders(trialCandidates);
		//carry out trials with all trial candidates one by one

		cout<<"Node "<<nodeId<<" carried out individual trials with "<<trialCandidates.size()<<" providers"<<endl;

		peeringTrialsProposedCombinations(trialCandidates);

	}

}

void Node::trialWithIndividualProviders(const list<nodeTrafficRank>& trialCandidates){

	peeringTrialsPeersStruct pt;
	peeringTrialsFlowsStruct lt;
	ptfsMapIt mIt;
	flowPair fp;

	for(list<nodeTrafficRank>::const_iterator it=trialCandidates.begin();it!=trialCandidates.end();it++){

		getSettlementFreePeer((*it).id,false);

		cout<<"Node "<<nodeId<<" peered with "<<(*it).id<<" for individual trial"<<endl;

		computeTrafficFlowsAcrossNetwork();

		if(nodeId<(*it).id){
			pt.inboundTraffic=linkValueVectorFlatLeft[linkIndex[nodeId][(*it).id].index];
			pt.outboundTraffic=linkValueVectorFlatRight[linkIndex[nodeId][(*it).id].index];
		}

		else{
			pt.inboundTraffic=linkValueVectorFlatRight[linkIndex[nodeId][(*it).id].index];
			pt.outboundTraffic=linkValueVectorFlatLeft[linkIndex[nodeId][(*it).id].index];
		}

		pt.totalTraffic=linkValueVector[linkIndex[nodeId][(*it).id].index];
		pt.peers.insert((*it).id);
		pt.flows=linkIndex[nodeId][(*it).id].flowsSym;
		pt.flowsAsym=linkIndex[nodeId][(*it).id].flowsAsym;

		peeringTrialsPeersProposed[static_cast<ostringstream*>( &(ostringstream() << ((*it).id)) )->str()]=pt;

		for(vector<int>::iterator itV=linkIndex[nodeId][(*it).id].flowsSym.begin();itV!=linkIndex[nodeId][(*it).id].flowsSym.end();itV++){

			cout<<"Dealing with flowsym flowNum: "<<*itV<<" "<<flowSymMap[*itV].n1<<" -> "<<flowSymMap[*itV].n2<<endl;

			fp.n1=flowSymMap[*itV].n1;
			fp.n2=flowSymMap[*itV].n2;

			mIt=peeringTrialsFlows.find(fp);
			lt.restore();

			if(mIt==peeringTrialsFlows.end()){

				if(flowSymMap[*itV].n1==nodeId || isPresentInCustomerTree(flowSymMap[*itV].n1)){
					lt.insider=flowSymMap[*itV].n1;
					lt.outsider=flowSymMap[*itV].n2;
					lt.flowDirection=OUTBOUND;
				}

				else{
					lt.insider=flowSymMap[*itV].n2;
					lt.outsider=flowSymMap[*itV].n1;
					lt.flowDirection=INBOUND;
				}

				if(lt.insider==lt.outsider){
					cout<<"Problem with peer "<<(*it).id<<" flow between "<<lt.insider<<" and "<<lt.outsider<<endl;

					if(flowSymMap[*itV].n1==flowSymMap[*itV].n2)
						cout<<"And the problem is bigger"<<endl;

				}

				lt.peers.insert((*it).id);
				lt.providerPeers.insert((*it).id);
				peeringTrialsFlows.insert(std::pair<flowPair,peeringTrialsFlowsStruct>(fp,lt));

			}

			else{

				mIt->second.peers.insert((*it).id);
				mIt->second.providerPeers.insert((*it).id);

				if(mIt->second.providerPeers.size()>1){
					cout<<"Provider trial more than one peers "<<(*it).id<<" Flow: ";
					if(mIt->second.flowDirection==INBOUND){
						cout<<mIt->second.outsider<<" -> "<<mIt->second.insider;
					}

					else{
						cout<<mIt->second.insider<<" -> "<<mIt->second.outsider;
					}

					cout<<endl;
				}

			}

		}

		for(vector<int>::iterator itV=linkIndex[nodeId][(*it).id].flowsAsym.begin();itV!=linkIndex[nodeId][(*it).id].flowsAsym.end();itV++){

			cout<<"Dealing with flowAsym flowNum: "<<*itV<<" "<<flowAsymMap[*itV].n1<<" -> "<<flowAsymMap[*itV].n2<<endl;

			fp.n1=flowAsymMap[*itV].n1;
			fp.n2=flowAsymMap[*itV].n2;

			mIt=peeringTrialsFlowsAsym.find(fp);
			lt.restore();

			if(mIt==peeringTrialsFlowsAsym.end()){

				if(flowAsymMap[*itV].n1==nodeId || isPresentInCustomerTree(flowAsymMap[*itV].n1)){
					lt.insider=flowAsymMap[*itV].n1;
					lt.outsider=flowAsymMap[*itV].n2;
					lt.flowDirection=OUTBOUND;
				}

				else{
					lt.insider=flowAsymMap[*itV].n2;
					lt.outsider=flowAsymMap[*itV].n1;
					lt.flowDirection=INBOUND;
				}

				if(lt.insider==lt.outsider){
					cout<<"Problem with peer "<<(*it).id<<" flow between "<<lt.insider<<" and "<<lt.outsider<<endl;

					if(flowSymMap[*itV].n1==flowSymMap[*itV].n2)
						cout<<"And the problem is bigger"<<endl;
				}

				lt.peers.insert((*it).id);
				lt.providerPeers.insert((*it).id);
				peeringTrialsFlowsAsym.insert(std::pair<flowPair,peeringTrialsFlowsStruct>(fp,lt));

			}//end if

			else{

				mIt->second.peers.insert((*it).id);
				mIt->second.providerPeers.insert((*it).id);

				if(mIt->second.providerPeers.size()>1){
					cout<<"Provider trial more than one peers "<<(*it).id<<" Flow: ";
					if(mIt->second.flowDirection==INBOUND){
						cout<<mIt->second.outsider<<" -> "<<mIt->second.insider;
					}

					else{
						cout<<mIt->second.insider<<" -> "<<mIt->second.outsider;
					}

					cout<<endl;
				}

			}

		}

		dePeer((*it).id);

	//	cout<<"Node "<<nodeId<<" depeered "<<(*it).id<<" after trial"<<endl;

	}

	cout<<"Node "<<nodeId<<" finished individual trials"<<endl;

}

void Node::peeringTrialsProposedCombinations(const list<nodeTrafficRank>& trialCandidates){

	//try combinations of providers based on their entanglement score

	cout<<"Node "<<nodeId<<" trying combinations"<<endl;

	set<unsigned int> peerSet;
	std::multimap<unsigned int,unsigned int> pathLengthMap;
	unsigned int peer;
	unsigned int pathLength;
	unsigned int outsider;
	unsigned int insider;
	list<flowPair> flowIndices;
	list<unsigned int> pathLengthList;
	string inputString;
	stringstream ss;
	peeringTrialsCombinationsStruct combinationsObj;

	//get all flow indices in Sym
	for(ptfsMapIt it=peeringTrialsFlows.begin();it!=peeringTrialsFlows.end();it=peeringTrialsFlows.upper_bound(it->first))
		flowIndices.push_back((*it).first);

	cout<<"Node "<<nodeId<<" will deal with "<<flowIndices.size()<<" flows in symmetric direction"<<endl;

	for(list<flowPair>::iterator it=flowIndices.begin();it!=flowIndices.end();it++){

		if(peeringTrialsFlows.find(*it)!=peeringTrialsFlows.end()){

			combinationsObj.restore();
			pathLengthList.clear();
			pathLengthMap.clear();

			if(peeringTrialsFlows[*it].providerPeers.size()>1){//if flow goes through more than one provider peers

				cout<<"FlowSym "<<(*it).n1<<" -> "<<(*it).n2<<" goes through "<<peeringTrialsFlows[*it].providerPeers.size()<<" provider peers"<<endl;

				if(peeringTrialsFlows[*it].flowDirection==OUTBOUND){
					cout<<"Outbound Flow "<<peeringTrialsFlows[*it].insider<<" -> "<<peeringTrialsFlows[*it].outsider<<" goes through provider peers :";
					for(set<unsigned int>::iterator chimp=peeringTrialsFlows[*it].providerPeers.begin();chimp!=peeringTrialsFlows[*it].providerPeers.end();chimp++)
						cout<<*chimp<<"\t";
					cout<<endl;
				}

				if(peeringTrialsFlows[*it].flowDirection==INBOUND){
					cout<<"Inbound Flow "<<peeringTrialsFlows[*it].outsider<<" -> "<<peeringTrialsFlows[*it].insider<<" goes through peers :";
					for(set<unsigned int>::iterator chimp=peeringTrialsFlows[*it].providerPeers.begin();chimp!=peeringTrialsFlows[*it].providerPeers.end();chimp++)
						cout<<*chimp<<"\t";
					cout<<endl;
				}

				for(set<unsigned int>::iterator itM=peeringTrialsFlows[*it].providerPeers.begin();itM!=peeringTrialsFlows[*it].providerPeers.end();itM++){

					peer=*itM;
					outsider=peeringTrialsFlows[*it].outsider;
					insider=peeringTrialsFlows[*it].insider;

					if(peer==outsider)
						pathLength=1;

					else
						pathLength=routingMatrix[flowIndex[peer][outsider]].size();

					cout<<"Path length for flow "<<(*it).n1<<" -> "<<(*it).n2<<" (outsider= "<<outsider<<") (insider="<<insider<<") through peer "<<peer<<" is "<<pathLength<<endl;
					pathLengthMap.insert(std::pair<unsigned int,unsigned int>(pathLength,peer));

				}

				for(std::multimap<unsigned int,unsigned int>::iterator itX=pathLengthMap.begin();itX!=pathLengthMap.end();itX=pathLengthMap.upper_bound(itX->first)){
					pathLengthList.push_back((*itX).first);
					cout<<"Pushing "<<(*itX).first<<" in pathLengthList"<<endl;
				}

				std::pair <std::multimap<unsigned int,unsigned int>::iterator, std::multimap<unsigned int,unsigned int>::iterator> let;

				for(list<unsigned int>::iterator itY=pathLengthList.begin();itY!=pathLengthList.end();itY++){

					let=pathLengthMap.equal_range(*itY);
					peerSet.clear();
					inputString.clear();

					cout<<"For path length "<<*itY<<" inserting peers ";

					for (std::multimap<unsigned int,unsigned int>::iterator itQ=let.first; itQ!=let.second; ++itQ){
						peerSet.insert((*itQ).second);
						cout<<(*itQ).second<<"\t";
					}

					cout<<endl;
					if(peerSet.size()>2){

						cout<<"Peer set greater than two for length "<<*itY<<endl;
						vector<unsigned int> comboSetVector;
						vector<unsigned int> peerSetVector;
						set<unsigned int> comboSet;
						unsigned int j;
						std::vector<unsigned int>::iterator itS;
						std::copy(peerSet.begin(),peerSet.end(),std::back_inserter(peerSetVector));

						for(unsigned int i=2;i<=peerSet.size();i++){
							comboSetVector.clear();
							inputString.clear();
							for(itS=peerSetVector.begin(),j=0;itS!=peerSetVector.end() && j<i;itS++,j++){
								comboSetVector.push_back(*itS);
							}

							do
							{
								comboSet.clear();
								std::copy(comboSetVector.begin(),comboSetVector.end(),inserter(comboSet,comboSet.end()));
								inputString=createString(comboSet);

								cout<<"Created string "<<inputString<<endl;

								if(peeringTrialsFlows[*it].flowDirection==INBOUND)
									combinationsObj.inboundTraffic=peeringTrialsFlows[*it].flowValue;
								else
									combinationsObj.outboundTraffic=peeringTrialsFlows[*it].flowValue;
								combinationsObj.totalTraffic=peeringTrialsFlows[*it].flowValue;
								combinationsObj.numPeers=peerSet.size();
								combinationsObj.peers=peerSet;

								std::map<string,peeringTrialsCombinationsStruct>::iterator itC;
								itC=combinationsTrials.find(inputString);
								if(itC!=combinationsTrials.end()){
									combinationsTrials[inputString].inboundTraffic+=combinationsObj.inboundTraffic;
									combinationsTrials[inputString].outboundTraffic+=combinationsObj.outboundTraffic;
									combinationsTrials[inputString].numPeers+=combinationsObj.numPeers;
									combinationsTrials[inputString].totalTraffic+=combinationsObj.totalTraffic;
									combinationsTrials[inputString].peers=combinationsObj.peers;
								}

								else{
									combinationsTrials.insert(std::pair<string,peeringTrialsCombinationsStruct>(inputString,combinationsObj));
								}

							}
							while(next_combination(peerSetVector.begin(),peerSetVector.end(),comboSetVector.begin(),comboSetVector.end()) );
						}

					}//end if

					else if(peerSet.size()==2){

						inputString=createString(peerSet);
						cout<<"Created string "<<inputString<<endl;

						if(peeringTrialsFlows[*it].flowDirection==INBOUND)
							combinationsObj.inboundTraffic=peeringTrialsFlows[*it].flowValue;
						else
							combinationsObj.outboundTraffic=peeringTrialsFlows[*it].flowValue;

						combinationsObj.totalTraffic=peeringTrialsFlows[*it].flowValue;
						combinationsObj.numPeers=peerSet.size();
						combinationsObj.peers=peerSet;

						std::map<string,peeringTrialsCombinationsStruct>::iterator itC;
						itC=combinationsTrials.find(inputString);
						if(itC!=combinationsTrials.end()){
							combinationsTrials[inputString].inboundTraffic+=combinationsObj.inboundTraffic;
							combinationsTrials[inputString].outboundTraffic+=combinationsObj.outboundTraffic;
							combinationsTrials[inputString].numPeers+=combinationsObj.numPeers;
							combinationsTrials[inputString].totalTraffic+=combinationsObj.totalTraffic;
							combinationsTrials[inputString].peers=combinationsObj.peers;
						}

						else{
							combinationsTrials.insert(std::pair<string,peeringTrialsCombinationsStruct>(inputString,combinationsObj));
						}

					}

					else{
						//do nothing for a set of size 1
					}

				}//end for

			}//end if flow goes over more than one peers

		}//end if for flow found in map

	}//end main 'for' for all flows

	//now repeating the same procedure for flowsAsym
	flowIndices.clear();
	for(ptfsMapIt it=peeringTrialsFlowsAsym.begin();it!=peeringTrialsFlowsAsym.end();it=peeringTrialsFlowsAsym.upper_bound(it->first))
		flowIndices.push_back((*it).first);

	cout<<"Node "<<nodeId<<" will deal with "<<flowIndices.size()<<" flows in asymmetric direction"<<endl;

	for(list<flowPair>::iterator it=flowIndices.begin();it!=flowIndices.end();it++){

		if(peeringTrialsFlowsAsym.find(*it)!=peeringTrialsFlowsAsym.end()){

			combinationsObj.restore();
			pathLengthList.clear();
			pathLengthMap.clear();

			if(peeringTrialsFlowsAsym[*it].providerPeers.size()>1){//if flow goes through more than one peers

				cout<<"FlowAsym "<<(*it).n1<<" -> "<<(*it).n2<<" goes through "<<peeringTrialsFlowsAsym[*it].providerPeers.size()<<" provider peers"<<endl;

				for(set<unsigned int>::iterator itM=peeringTrialsFlowsAsym[*it].providerPeers.begin();itM!=peeringTrialsFlowsAsym[*it].providerPeers.end();itM++){

					peer=*itM;
					outsider=peeringTrialsFlowsAsym[*it].outsider;
					insider=peeringTrialsFlowsAsym[*it].insider;

					if(peer==outsider)
						pathLength=1;
					else
						pathLength=routingMatrix[flowIndex[peer][outsider]].size();

					cout<<"Path length for flow "<<(*it).n1<<" -> "<<(*it).n2<<" (outsider= "<<outsider<<") (insider="<<insider<<") through peer "<<peer<<" is "<<pathLength<<endl;

					pathLengthMap.insert(std::pair<unsigned int,unsigned int>(pathLength,peer));

				}

				for(std::multimap<unsigned int,unsigned int>::iterator itX=pathLengthMap.begin();itX!=pathLengthMap.end();itX=pathLengthMap.upper_bound(itX->first)){
					pathLengthList.push_back((*itX).first);
					cout<<"Pushing "<<(*itX).first<<" in pathLengthList"<<endl;
				}

				std::pair <std::multimap<unsigned int,unsigned int>::iterator, std::multimap<unsigned int,unsigned int>::iterator> let;

				for(list<unsigned int>::iterator itY=pathLengthList.begin();itY!=pathLengthList.end();itY++){

					peerSet.clear();
					inputString.clear();
					let=pathLengthMap.equal_range(*itY);

					cout<<"For path length "<<*itY<<" inserting peers ";
					for (std::multimap<unsigned int,unsigned int>::iterator itQ=let.first; itQ!=let.second; ++itQ){

						cout<<(*itQ).second<<"\t";
						peerSet.insert((*itQ).second);
					}
					cout<<endl;

					if(peerSet.size()>2){

						cout<<"Peer set greater than two "<<endl;

						vector<unsigned int> comboSetVector;
						vector<unsigned int> peerSetVector;
						set<unsigned int> comboSet;
						unsigned int j;
						std::vector<unsigned int>::iterator itS;
						std::copy(peerSet.begin(),peerSet.end(),std::back_inserter(peerSetVector));

						for(unsigned int i=2;i<=peerSet.size();i++){
							comboSetVector.clear();
							inputString.clear();
							for(itS=peerSetVector.begin(),j=0;itS!=peerSetVector.end() && j<i;itS++,j++){
								comboSetVector.push_back(*itS);
							}

							do
							{
								comboSet.clear();
								std::copy(comboSetVector.begin(),comboSetVector.end(),inserter(comboSet,comboSet.end()));
								inputString=createString(comboSet);

								cout<<"Created string "<<inputString<<endl;

								if(peeringTrialsFlowsAsym[*it].flowDirection==INBOUND)
									combinationsObj.inboundTraffic=peeringTrialsFlowsAsym[*it].flowValue;
								else
									combinationsObj.outboundTraffic=peeringTrialsFlowsAsym[*it].flowValue;
								combinationsObj.totalTraffic=peeringTrialsFlowsAsym[*it].flowValue;
								combinationsObj.numPeers=peerSet.size();
								combinationsObj.peers=peerSet;

								std::map<string,peeringTrialsCombinationsStruct>::iterator itC;
								itC=combinationsTrials.find(inputString);
								if(itC!=combinationsTrials.end()){
									combinationsTrials[inputString].inboundTraffic+=combinationsObj.inboundTraffic;
									combinationsTrials[inputString].outboundTraffic+=combinationsObj.outboundTraffic;
									combinationsTrials[inputString].numPeers+=combinationsObj.numPeers;
									combinationsTrials[inputString].totalTraffic+=combinationsObj.totalTraffic;
									combinationsTrials[inputString].peers=combinationsObj.peers;
								}

								else{
									combinationsTrials.insert(std::pair<string,peeringTrialsCombinationsStruct>(inputString,combinationsObj));
								}

							}
							while(next_combination(peerSetVector.begin(),peerSetVector.end(),comboSetVector.begin(),comboSetVector.end()) );
						}

					}//end if

					else if(peerSet.size()==2){

						inputString=createString(peerSet);

						cout<<"Created string "<<inputString<<endl;

						if(peeringTrialsFlowsAsym[*it].flowDirection==INBOUND)
							combinationsObj.inboundTraffic=peeringTrialsFlowsAsym[*it].flowValue;
						else
							combinationsObj.outboundTraffic=peeringTrialsFlowsAsym[*it].flowValue;
						combinationsObj.totalTraffic=peeringTrialsFlowsAsym[*it].flowValue;
						combinationsObj.numPeers=peerSet.size();
						combinationsObj.peers=peerSet;

						std::map<string,peeringTrialsCombinationsStruct>::iterator itC;
						itC=combinationsTrials.find(inputString);
						if(itC!=combinationsTrials.end()){
							combinationsTrials[inputString].inboundTraffic+=combinationsObj.inboundTraffic;
							combinationsTrials[inputString].outboundTraffic+=combinationsObj.outboundTraffic;
							combinationsTrials[inputString].numPeers+=combinationsObj.numPeers;
							combinationsTrials[inputString].totalTraffic+=combinationsObj.totalTraffic;
							combinationsTrials[inputString].peers=combinationsObj.peers;
						}

						else{
							combinationsTrials.insert(std::pair<string,peeringTrialsCombinationsStruct>(inputString,combinationsObj));
						}

					}

					else{
						//do nothing for a set of size 1
					}

				}//end for

			}//end if flow goes over more than one peers

		}//end if for flow found

	}//end main 'for' for all flowsAsym

	std::list<peeringTrialsCombinationsStruct> entanglementSorter;
	//assign entanglement scores to all combinations
	for(std::map<string,peeringTrialsCombinationsStruct>::iterator it=combinationsTrials.begin();it!=combinationsTrials.end();it++){
		cout<<"Computing entanglement score for combination "<<(*it).first<<endl;
		(*it).second.entanglementScore=sqrt(inboundTrafficWeight*pow((*it).second.inboundTraffic,2)+outboundTrafficWeight*pow((*it).second.outboundTraffic,2)+totalTrafficWeight*pow((*it).second.totalTraffic,2)+numPeersWeight*pow(static_cast<float>((*it).second.numPeers),2));
		entanglementSorter.push_back((*it).second);
	}

	entanglementSorter.sort(sortReverseByEntanglementScore);

	cout<<"Node "<<nodeId<<" tried "<<entanglementSorter.size()<<" combinations"<<endl;

	//TODO Filter by Budget
	peeringTrialsPeersStruct pt;
	for(std::list<peeringTrialsCombinationsStruct>::iterator it=entanglementSorter.begin();it!=entanglementSorter.end();it++){

		cout<<"For combination "<<createString((*it).peers)<<" peering with ";
		pt.restore();

		for(std::set<unsigned int>::iterator itS=(*it).peers.begin();itS!=(*it).peers.end();itS++){
			getSettlementFreePeer(*itS,false);
			cout<<*itS<<"\t";
		}
		cout<<endl;

		computeTrafficFlowsAcrossNetwork();

		for(std::set<unsigned int>::iterator itS=(*it).peers.begin();itS!=(*it).peers.end();itS++){

			if(nodeId<*itS){
				pt.inboundTraffic+=linkValueVectorFlatLeft[linkIndex[nodeId][*itS].index];
				pt.outboundTraffic+=linkValueVectorFlatRight[linkIndex[nodeId][*itS].index];
			}

			else{
				pt.inboundTraffic+=linkValueVectorFlatRight[linkIndex[nodeId][*itS].index];
				pt.outboundTraffic+=linkValueVectorFlatLeft[linkIndex[nodeId][*itS].index];
			}

			pt.totalTraffic+=linkValueVector[linkIndex[nodeId][*itS].index];
			pt.peers.insert(*itS);
			pt.flows.insert(pt.flows.end(),linkIndex[nodeId][*itS].flowsSym.begin(),linkIndex[nodeId][*itS].flowsSym.end());
			pt.flowsAsym.insert(pt.flowsAsym.end(),linkIndex[nodeId][*itS].flowsAsym.begin(),linkIndex[nodeId][*itS].flowsAsym.end());

			peeringTrialsPeersProposed[createString(pt.peers)]=pt;

		}//end for

		for(std::set<unsigned int>::iterator itS=(*it).peers.begin();itS!=(*it).peers.end();itS++){
			dePeer(*itS);
		}

	}//end for

}






