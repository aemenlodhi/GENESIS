/*
 * trafficEstimation.cpp
 *
 *  Created on: Mar 30, 2014
 *      Author: aemen
 */

#include "node.h"
#include "support.h"

double Node::estimateTrafficLowerBound(const unsigned int& id){

	return (trafficSent[id]+nodePointers[id]->trafficSent[nodeId]);
}

double Node::estimateTrafficUpperBound(const unsigned int& id){

	double upperBound=0;
	list<unsigned int> xCustomers;
	list<unsigned int> yCustomers;

	J.sort(sortById);
	J.unique(removeSameId);

	nodePointers[id]->J.sort(sortById);
	nodePointers[id]->J.unique(removeSameId);

	for(list<NodePrice>::iterator itNP=J.begin();itNP!=J.end();itNP++)
		xCustomers.push_back((*itNP).nId);

	for(list<NodePrice>::iterator itNP=nodePointers[id]->J.begin();itNP!=nodePointers[id]->J.end();itNP++)
		if(!isPresentInCustomerTree((*itNP).nId))
			yCustomers.push_back((*itNP).nId);

	for(list<unsigned int>::iterator it=xCustomers.begin();it!=xCustomers.end();it++)
		for(list<unsigned int>::iterator itY=yCustomers.begin();itY!=yCustomers.end();itY++)
			upperBound+=(nodePointers[*it]->trafficSent[*itY]+nodePointers[*itY]->trafficSent[*it]);

	upperBound+=(trafficSent[id]+nodePointers[id]->trafficSent[nodeId]);

	return upperBound;
}

double Node::estimateTrafficFromTight(const unsigned int& id){

	return nodePointers[id]->estimateTrafficToTight(nodeId);
}

double Node::estimateTrafficToTight(const unsigned int& id, vector<int>& flowsSym, vector<int>& flowsAsym){

	double traffic=0;
	list<int> linkIndices;
	list<int> flowIndicesSym;
	list<int> flowIndicesAsym;
	list<int> nodesOfInterest;

	if(!Q.empty())
		for(list<NodePrice>::iterator it=Q.begin();it!=Q.end();it++)
			linkIndices.push_back((*it).nId);

	if(!K.empty())
		for(list<NodePrice>::iterator it=K.begin();it!=K.end();it++)
			linkIndices.push_back((*it).nId);

	if(!nodePointers[id]->I.empty()){
		for(list<NodePrice>::iterator it=nodePointers[id]->I.begin();it!=nodePointers[id]->I.end();it++)
			if(!isPresentInCustomerTree((*it).nId))
				nodesOfInterest.push_back((*it).nId);
	}

	traffic+=trafficSent[id];
	if(flowDirectionFrom[flowIndex[nodeId][id]]==nodeId)
		flowsSym.push_back(flowIndex[nodeId][id]);
	else
		flowsAsym.push_back(flowIndex[nodeId][id]);

	for(list<int>::iterator it=nodesOfInterest.begin();it!=nodesOfInterest.end();it++){
		if(flowDirectionFrom[flowIndex[nodeId][*it]]==nodeId && linkMap[linkIndex[id][*it].index].flowIndicesSym.end()!=std::find(linkMap[linkIndex[id][*it].index].flowIndicesSym.begin(),linkMap[linkIndex[id][*it].index].flowIndicesSym.end(),flowIndex[nodeId][*it])){
			traffic+=trafficSent[*it];
			flowsSym.push_back(flowIndex[nodeId][*it]);
		}

		else if(flowDirectionFromAsym[flowIndex[nodeId][*it]]==nodeId && linkMap[linkIndex[id][*it].index].flowIndicesAsym.end()!=std::find(linkMap[linkIndex[id][*it].index].flowIndicesAsym.begin(),linkMap[linkIndex[id][*it].index].flowIndicesAsym.end(),flowIndex[nodeId][*it])){
			traffic+=trafficSent[*it];
			flowsAsym.push_back(flowIndex[nodeId][*it]);
		}

		else{}
	}

	for(list<NodePrice>::iterator it=I.begin();it!=I.end();it++){

		if(flowDirectionFrom[flowIndex[(*it).nId][id]]==(*it).nId && linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesSym.end()!=std::find(linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesSym.begin(),linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesSym.end(),flowIndex[(*it).nId][id])){
			traffic+=(nodePointers[(*it).nId]->trafficSent[id]);
			flowsSym.push_back(flowIndex[(*it).nId][id]);
		}

		else if(flowDirectionFromAsym[flowIndex[(*it).nId][id]]==(*it).nId && linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesAsym.end()!=std::find(linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesAsym.begin(),linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesAsym.end(),flowIndex[(*it).nId][id])){
			traffic+=(nodePointers[(*it).nId]->trafficSent[id]);
			flowsAsym.push_back(flowIndex[(*it).nId][id]);
		}

		else{}

	}

	unsigned int x;
	unsigned int y;
	for(list<NodePrice>::iterator it=I.begin();it!=I.end();it++){
		x=(*it).nId;
		for(list<int>::iterator itN=nodesOfInterest.begin();itN!=nodesOfInterest.end();itN++){
			y=*itN;

			if(flowDirectionFrom[flowIndex[x][y]]==x && linkMap[linkIndex[nodeId][x].index].flowIndicesSym.end()!=std::find(linkMap[linkIndex[nodeId][x].index].flowIndicesSym.begin(),linkMap[linkIndex[nodeId][x].index].flowIndicesSym.end(),flowIndex[x][y]) && linkMap[linkIndex[id][y].index].flowIndicesSym.end()!=std::find(linkMap[linkIndex[id][y].index].flowIndicesSym.begin(),linkMap[linkIndex[id][y].index].flowIndicesSym.end(),flowIndex[x][y])){
				traffic+=nodePointers[x]->trafficSent[y];
				flowsSym.push_back(flowIndex[x][y]);
			}

			else if(flowDirectionFromAsym[flowIndex[x][y]]==x && linkMap[linkIndex[nodeId][x].index].flowIndicesAsym.end()!=std::find(linkMap[linkIndex[nodeId][x].index].flowIndicesAsym.begin(),linkMap[linkIndex[nodeId][x].index].flowIndicesAsym.end(),flowIndex[x][y]) && linkMap[linkIndex[id][y].index].flowIndicesAsym.end()!=std::find(linkMap[linkIndex[id][y].index].flowIndicesAsym.begin(),linkMap[linkIndex[id][y].index].flowIndicesAsym.end(),flowIndex[x][y])){
				traffic+=nodePointers[x]->trafficSent[y];
				flowsAsym.push_back(flowIndex[x][y]);
			}

			else{}
		}

	}

	return traffic;

}

double Node::estimateTrafficToTight(const unsigned int& id){

	double traffic=0;
	list<int> linkIndices;
	list<int> flowIndicesSym;
	list<int> flowIndicesAsym;
	list<int> nodesOfInterest;

	if(!Q.empty())
		for(list<NodePrice>::iterator it=Q.begin();it!=Q.end();it++)
			linkIndices.push_back((*it).nId);

	if(!K.empty())
		for(list<NodePrice>::iterator it=K.begin();it!=K.end();it++)
			linkIndices.push_back((*it).nId);

	if(!nodePointers[id]->I.empty()){
		for(list<NodePrice>::iterator it=nodePointers[id]->I.begin();it!=nodePointers[id]->I.end();it++)
			if(!isPresentInCustomerTree((*it).nId))
				nodesOfInterest.push_back((*it).nId);
	}

	traffic+=trafficSent[id];
	for(list<int>::iterator it=nodesOfInterest.begin();it!=nodesOfInterest.end();it++){
		if(flowDirectionFrom[flowIndex[nodeId][*it]]==nodeId && linkMap[linkIndex[id][*it].index].flowIndicesSym.end()!=std::find(linkMap[linkIndex[id][*it].index].flowIndicesSym.begin(),linkMap[linkIndex[id][*it].index].flowIndicesSym.end(),flowIndex[nodeId][*it])){
			traffic+=trafficSent[*it];
		}

		else if(flowDirectionFromAsym[flowIndex[nodeId][*it]]==nodeId && linkMap[linkIndex[id][*it].index].flowIndicesAsym.end()!=std::find(linkMap[linkIndex[id][*it].index].flowIndicesAsym.begin(),linkMap[linkIndex[id][*it].index].flowIndicesAsym.end(),flowIndex[nodeId][*it])){
			traffic+=trafficSent[*it];
		}

		else{}
	}

	for(list<NodePrice>::iterator it=I.begin();it!=I.end();it++){

		if(flowDirectionFrom[flowIndex[(*it).nId][id]]==(*it).nId && linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesSym.end()!=std::find(linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesSym.begin(),linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesSym.end(),flowIndex[(*it).nId][id])){
			traffic+=(nodePointers[(*it).nId]->trafficSent[id]);
		}

		else if(flowDirectionFromAsym[flowIndex[(*it).nId][id]]==(*it).nId && linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesAsym.end()!=std::find(linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesAsym.begin(),linkMap[linkIndex[nodeId][(*it).nId].index].flowIndicesAsym.end(),flowIndex[(*it).nId][id])){
			traffic+=(nodePointers[(*it).nId]->trafficSent[id]);
		}

		else{}

	}

	unsigned int x;
	unsigned int y;
	for(list<NodePrice>::iterator it=I.begin();it!=I.end();it++){
		x=(*it).nId;
		for(list<int>::iterator itN=nodesOfInterest.begin();itN!=nodesOfInterest.end();itN++){
			y=*itN;

			if(flowDirectionFrom[flowIndex[x][y]]==x && linkMap[linkIndex[nodeId][x].index].flowIndicesSym.end()!=std::find(linkMap[linkIndex[nodeId][x].index].flowIndicesSym.begin(),linkMap[linkIndex[nodeId][x].index].flowIndicesSym.end(),flowIndex[x][y]) && linkMap[linkIndex[id][y].index].flowIndicesSym.end()!=std::find(linkMap[linkIndex[id][y].index].flowIndicesSym.begin(),linkMap[linkIndex[id][y].index].flowIndicesSym.end(),flowIndex[x][y])){
				traffic+=nodePointers[x]->trafficSent[y];
			}

			else if(flowDirectionFromAsym[flowIndex[x][y]]==x && linkMap[linkIndex[nodeId][x].index].flowIndicesAsym.end()!=std::find(linkMap[linkIndex[nodeId][x].index].flowIndicesAsym.begin(),linkMap[linkIndex[nodeId][x].index].flowIndicesAsym.end(),flowIndex[x][y]) && linkMap[linkIndex[id][y].index].flowIndicesAsym.end()!=std::find(linkMap[linkIndex[id][y].index].flowIndicesAsym.begin(),linkMap[linkIndex[id][y].index].flowIndicesAsym.end(),flowIndex[x][y])){
				traffic+=nodePointers[x]->trafficSent[y];
			}

			else{}
		}

	}

	return traffic;

}

double Node::estimateTrafficExchangeTight(const unsigned int& id){

	return estimateTrafficToTight(id)+nodePointers[id]->trafficSent[nodeId];
}

double Node::estimateTrafficExchangeSlack(const unsigned int& id){

	vector<int> linkIndices;
	vector<int> flowIndicesx;
	vector<int> flowIndicesxAsym;
	vector<int> flowIndicesy;
	vector<int> flowIndicesyAsym;
	vector<int> commonFlows;
	double estimatedTrafficExchange=0;

	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(i!=nodeId && linkIndex[nodeId][i].index!=-1){
			if(linkIndex[nodeId][i].linkClass==PPLink || linkIndex[nodeId][i].linkClass==PPPLink)
				linkIndices.push_back(linkIndex[nodeId][i].index);
			else{

				if(linkIndex[nodeId][i].provider!=nodeId)
					linkIndices.push_back(linkIndex[nodeId][i].index);

			}
		}

	for(unsigned int i=0;i<maxFlows;i++){
		if(aliveFlowIndicator[i] && !routingMatrix[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end())
					flowIndicesx.push_back(i);
		}

		if(aliveFlowIndicator[i] && !routingMatrixAsym[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end())
					flowIndicesxAsym.push_back(i);
		}
	}

	linkIndices.clear();

	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(i!=id && linkIndex[id][i].index!=-1){
			if(linkIndex[id][i].linkClass==PPLink || linkIndex[id][i].linkClass==PPPLink)
				linkIndices.push_back(linkIndex[id][i].index);
			else{

				if(linkIndex[id][i].provider!=id)
					linkIndices.push_back(linkIndex[id][i].index);

			}
		}

	for(unsigned int i=0;i<maxFlows;i++){
		if(aliveFlowIndicator[i] && !routingMatrix[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end())
					flowIndicesy.push_back(i);
		}

		if(aliveFlowIndicator[i] && !routingMatrixAsym[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end())
					flowIndicesyAsym.push_back(i);
		}
	}

	std::set_intersection(flowIndicesx.begin(),flowIndicesx.end(),flowIndicesy.begin(),flowIndicesy.end(),back_inserter(commonFlows));
	for(vector<int>::iterator it=commonFlows.begin();it!=commonFlows.end();it++)
		estimatedTrafficExchange+=flowValueVector[*it];

	commonFlows.clear();
	std::set_intersection(flowIndicesxAsym.begin(),flowIndicesxAsym.end(),flowIndicesyAsym.begin(),flowIndicesyAsym.end(),back_inserter(commonFlows));
		for(vector<int>::iterator it=commonFlows.begin();it!=commonFlows.end();it++)
			estimatedTrafficExchange+=flowValueVectorAsym[*it];

	return estimatedTrafficExchange;

}

double Node::estimateTrafficExchangeSlack(const unsigned int& id, vector<int>& flows, vector<int>& flowsAsym){

	vector<int> linkIndices;
	vector<int> flowIndicesx;
	vector<int> flowIndicesxAsym;
	vector<int> flowIndicesy;
	vector<int> flowIndicesyAsym;
	vector<int> commonFlows;
	double estimatedTrafficExchange=0;

	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(i!=nodeId && linkIndex[nodeId][i].index!=-1){
			if(linkIndex[nodeId][i].linkClass==PPLink || linkIndex[nodeId][i].linkClass==PPPLink)
				linkIndices.push_back(linkIndex[nodeId][i].index);
			else{

				if(linkIndex[nodeId][i].provider!=nodeId)
					linkIndices.push_back(linkIndex[nodeId][i].index);

			}
		}

	for(unsigned int i=0;i<maxFlows;i++){
		if(aliveFlowIndicator[i] && !routingMatrix[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end())
					flowIndicesx.push_back(i);
		}

		if(aliveFlowIndicator[i] && !routingMatrixAsym[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end())
					flowIndicesxAsym.push_back(i);
		}
	}

	linkIndices.clear();

	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(i!=id && linkIndex[id][i].index!=-1){
			if(linkIndex[id][i].linkClass==PPLink || linkIndex[id][i].linkClass==PPPLink)
				linkIndices.push_back(linkIndex[id][i].index);
			else{

				if(linkIndex[id][i].provider!=id)
					linkIndices.push_back(linkIndex[id][i].index);

			}
		}

	for(unsigned int i=0;i<maxFlows;i++){
		if(aliveFlowIndicator[i] && !routingMatrix[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end())
					flowIndicesy.push_back(i);
		}

		if(aliveFlowIndicator[i] && !routingMatrixAsym[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end())
					flowIndicesyAsym.push_back(i);
		}
	}

	std::set_intersection(flowIndicesx.begin(),flowIndicesx.end(),flowIndicesy.begin(),flowIndicesy.end(),back_inserter(commonFlows));
	for(vector<int>::iterator it=commonFlows.begin();it!=commonFlows.end();it++){
		estimatedTrafficExchange+=flowValueVector[*it];
		flows.push_back(*it);
	}

	commonFlows.clear();
	std::set_intersection(flowIndicesxAsym.begin(),flowIndicesxAsym.end(),flowIndicesyAsym.begin(),flowIndicesyAsym.end(),back_inserter(commonFlows));
	for(vector<int>::iterator it=commonFlows.begin();it!=commonFlows.end();it++){
		estimatedTrafficExchange+=flowValueVectorAsym[*it];
		flowsAsym.push_back(*it);
	}

	return estimatedTrafficExchange;

}

double Node::estimateTrafficToSlack(const unsigned int& id){

#if DEBUG
	cout<<"Node "<<nodeId<<" estimating traffic to: "<<id<<endl;
#endif

	vector<int> linkIndices;
	vector<int> flowIndicesx;
	vector<int> flowIndicesxAsym;
	vector<int> flowIndicesy;
	vector<int> flowIndicesyAsym;
	vector<int> commonFlows;
	double estimatedTrafficExchange=0;

	std::map<int,unsigned int> indexNodeMap;
	std::vector<int>::iterator itV;

	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(i!=nodeId && linkIndex[nodeId][i].index!=-1){
			if(linkIndex[nodeId][i].linkClass==PPLink || linkIndex[nodeId][i].linkClass==PPPLink){
				linkIndices.push_back(linkIndex[nodeId][i].index);
				indexNodeMap[linkIndex[nodeId][i].index]=i;
			}

			else{

				if(linkIndex[nodeId][i].provider!=nodeId){
					linkIndices.push_back(linkIndex[nodeId][i].index);

					indexNodeMap[linkIndex[nodeId][i].index]=i;
				}

			}

		}

	for(unsigned int i=0;i<maxFlows;i++){

		if(aliveFlowIndicator[i] && !routingMatrix[i].empty()){

			for(list<flowInfo>::iterator it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++){

				if((itV=find(linkIndices.begin(),linkIndices.end(),(*it).linkId))!=linkIndices.end()){

					if(linkIndex[nodeId][indexNodeMap[*itV]].linkClass==CPLink){

						if((*it).flowDirection==UPSTREAM){

							flowIndicesx.push_back(i);
#if 0
							for(unsigned int p=0;p<Node::activeNodes;p++){
								for(unsigned int q=0;q<Node::activeNodes;q++){
									if(p!=q && flowIndex[p][q]==static_cast<int>(i)){

										cout<<"Pushing index "<<i<<" for flow "<<flowDirectionFrom[i]<<"->"<<flowDirectionFromAsym[i];
										if((*it).flowDirection==UPSTREAM)
											cout<<" flowDirection=UPSTREAM"<<endl;
										else
											cout<<" flowDirection=DOWNSTREAM"<<endl;

										goto loopend;

									}
								}
							}

							loopend:
							cout<<"";
#endif
						}

					}

					else{

						if((nodeId<indexNodeMap[*itV] && (*it).flowDirection==LEFT_TO_RIGHT)){
							flowIndicesx.push_back(i);
						}

						if((nodeId>indexNodeMap[*itV] && (*it).flowDirection==RIGHT_TO_LEFT)){
							flowIndicesx.push_back(i);
						}

					}

				}//end if

			}//end for

		}//end if

		if(aliveFlowIndicator[i] && !routingMatrixAsym[i].empty()){

			for(list<flowInfo>::iterator it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++){

				if((itV=find(linkIndices.begin(),linkIndices.end(),(*it).linkId))!=linkIndices.end()){

					if(linkIndex[nodeId][indexNodeMap[*itV]].linkClass==CPLink){
						if((*it).flowDirection==UPSTREAM){
							flowIndicesxAsym.push_back(i);
#if 0
							for(unsigned int p=0;p<Node::activeNodes;p++){
								for(unsigned int q=0;q<Node::activeNodes;q++){
									if(p!=q && flowIndex[p][q]==static_cast<int>(i)){


										cout<<"Pushing index Asym "<<i<<" for flow "<<flowDirectionFromAsym[i]<<"->"<<flowDirectionFrom[i];
										if((*it).flowDirection==UPSTREAM)
											cout<<" flowDirection=UPSTREAM"<<endl;
										else
											cout<<" flowDirection=DOWNSTREAM"<<endl;

										goto stop;

									}
								}
							}

							stop:
							cout<<"";
#endif
						}


					}

					else{

						if((nodeId<indexNodeMap[*itV] && (*it).flowDirection==LEFT_TO_RIGHT)){
							flowIndicesxAsym.push_back(i);
						}

						if((nodeId>indexNodeMap[*itV] && (*it).flowDirection==RIGHT_TO_LEFT)){
							flowIndicesxAsym.push_back(i);
						}

					}

				}//end if

			}//end for

		}//end if

	}//end for

	linkIndices.clear();

	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(i!=id && linkIndex[id][i].index!=-1){
			if(linkIndex[id][i].linkClass==PPLink || linkIndex[id][i].linkClass==PPPLink)
				linkIndices.push_back(linkIndex[id][i].index);
			else{

				if(linkIndex[id][i].provider!=id)
					linkIndices.push_back(linkIndex[id][i].index);

			}
		}

	for(unsigned int i=0;i<maxFlows;i++){
		if(aliveFlowIndicator[i] && !routingMatrix[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end()){
					flowIndicesy.push_back(i);

				}
		}

		if(aliveFlowIndicator[i] && !routingMatrixAsym[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end()){
					flowIndicesyAsym.push_back(i);

				}

		}
	}

	std::set_intersection(flowIndicesx.begin(),flowIndicesx.end(),flowIndicesy.begin(),flowIndicesy.end(),back_inserter(commonFlows));
	for(vector<int>::iterator it=commonFlows.begin();it!=commonFlows.end();it++){
		estimatedTrafficExchange+=flowValueVector[*it];

	}

	commonFlows.clear();
	std::set_intersection(flowIndicesxAsym.begin(),flowIndicesxAsym.end(),flowIndicesyAsym.begin(),flowIndicesyAsym.end(),back_inserter(commonFlows));
		for(vector<int>::iterator it=commonFlows.begin();it!=commonFlows.end();it++){
			estimatedTrafficExchange+=flowValueVectorAsym[*it];

		}

	return estimatedTrafficExchange;

}

double Node::estimateTrafficFromSlack(const unsigned int& id){

	return nodePointers[id]->estimateTrafficToSlack(nodeId);

}

double Node::estimateTrafficFromSlack(const unsigned int& id, vector<int>& flowsSym, vector<int>& flowsAsym){

	return nodePointers[id]->estimateTrafficToSlack(nodeId,flowsSym,flowsAsym);
}

double Node::estimateTrafficToSlack(const unsigned int& id, vector<int>& flowsSym, vector<int>& flowsAsym){

#if DEBUG
	cout<<"Node "<<nodeId<<" estimating traffic to: "<<id<<endl;
#endif

	vector<int> linkIndices;
	vector<int> flowIndicesx;
	vector<int> flowIndicesxAsym;
	vector<int> flowIndicesy;
	vector<int> flowIndicesyAsym;
	vector<int> commonFlows;
	double estimatedTrafficExchange=0;

	std::map<int,unsigned int> indexNodeMap;
	std::vector<int>::iterator itV;

	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(i!=nodeId && linkIndex[nodeId][i].index!=-1){
			if(linkIndex[nodeId][i].linkClass==PPLink || linkIndex[nodeId][i].linkClass==PPPLink){
				linkIndices.push_back(linkIndex[nodeId][i].index);
				indexNodeMap[linkIndex[nodeId][i].index]=i;
			}

			else{

				if(linkIndex[nodeId][i].provider!=nodeId){
					linkIndices.push_back(linkIndex[nodeId][i].index);

					indexNodeMap[linkIndex[nodeId][i].index]=i;
				}

			}

		}

	for(unsigned int i=0;i<maxFlows;i++){

		if(aliveFlowIndicator[i] && !routingMatrix[i].empty()){

			for(list<flowInfo>::iterator it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++){

				if((itV=find(linkIndices.begin(),linkIndices.end(),(*it).linkId))!=linkIndices.end()){

					if(linkIndex[nodeId][indexNodeMap[*itV]].linkClass==CPLink){

						if((*it).flowDirection==UPSTREAM){

							flowIndicesx.push_back(i);
#if 0
							for(unsigned int p=0;p<Node::activeNodes;p++){
								for(unsigned int q=0;q<Node::activeNodes;q++){
									if(p!=q && flowIndex[p][q]==static_cast<int>(i)){

										cout<<"Pushing index "<<i<<" for flow "<<flowDirectionFrom[i]<<"->"<<flowDirectionFromAsym[i];
										if((*it).flowDirection==UPSTREAM)
											cout<<" flowDirection=UPSTREAM"<<endl;
										else
											cout<<" flowDirection=DOWNSTREAM"<<endl;

										goto loopend;

									}
								}
							}

							loopend:
							cout<<"";
#endif
						}

					}

					else{

						if((nodeId<indexNodeMap[*itV] && (*it).flowDirection==LEFT_TO_RIGHT)){
							flowIndicesx.push_back(i);
						}

						if((nodeId>indexNodeMap[*itV] && (*it).flowDirection==RIGHT_TO_LEFT)){
							flowIndicesx.push_back(i);
						}

					}

				}//end if

			}//end for

		}//end if

		if(aliveFlowIndicator[i] && !routingMatrixAsym[i].empty()){

			for(list<flowInfo>::iterator it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++){

				if((itV=find(linkIndices.begin(),linkIndices.end(),(*it).linkId))!=linkIndices.end()){

					if(linkIndex[nodeId][indexNodeMap[*itV]].linkClass==CPLink){
						if((*it).flowDirection==UPSTREAM){
							flowIndicesxAsym.push_back(i);
#if 0
							for(unsigned int p=0;p<Node::activeNodes;p++){
								for(unsigned int q=0;q<Node::activeNodes;q++){
									if(p!=q && flowIndex[p][q]==static_cast<int>(i)){


										cout<<"Pushing index Asym "<<i<<" for flow "<<flowDirectionFromAsym[i]<<"->"<<flowDirectionFrom[i];
										if((*it).flowDirection==UPSTREAM)
											cout<<" flowDirection=UPSTREAM"<<endl;
										else
											cout<<" flowDirection=DOWNSTREAM"<<endl;

										goto stop;

									}
								}
							}

							stop:
							cout<<"";
#endif
						}


					}

					else{

						if((nodeId<indexNodeMap[*itV] && (*it).flowDirection==LEFT_TO_RIGHT)){
							flowIndicesxAsym.push_back(i);
						}

						if((nodeId>indexNodeMap[*itV] && (*it).flowDirection==RIGHT_TO_LEFT)){
							flowIndicesxAsym.push_back(i);
						}

					}

				}//end if

			}//end for

		}//end if

	}//end for

	linkIndices.clear();

	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(i!=id && linkIndex[id][i].index!=-1){
			if(linkIndex[id][i].linkClass==PPLink || linkIndex[id][i].linkClass==PPPLink)
				linkIndices.push_back(linkIndex[id][i].index);
			else{

				if(linkIndex[id][i].provider!=id)
					linkIndices.push_back(linkIndex[id][i].index);

			}
		}

	for(unsigned int i=0;i<maxFlows;i++){
		if(aliveFlowIndicator[i] && !routingMatrix[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end()){
					flowIndicesy.push_back(i);

				}
		}

		if(aliveFlowIndicator[i] && !routingMatrixAsym[i].empty()){
			for(list<flowInfo>::iterator it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++)
				if(find(linkIndices.begin(),linkIndices.end(),(*it).linkId)!=linkIndices.end()){
					flowIndicesyAsym.push_back(i);

				}

		}

	}

	std::set_intersection(flowIndicesx.begin(),flowIndicesx.end(),flowIndicesy.begin(),flowIndicesy.end(),back_inserter(commonFlows));
	for(vector<int>::iterator it=commonFlows.begin();it!=commonFlows.end();it++){
		estimatedTrafficExchange+=flowValueVector[*it];
		flowsSym.push_back(*it);
	}

	commonFlows.clear();
	std::set_intersection(flowIndicesxAsym.begin(),flowIndicesxAsym.end(),flowIndicesyAsym.begin(),flowIndicesyAsym.end(),back_inserter(commonFlows));
		for(vector<int>::iterator it=commonFlows.begin();it!=commonFlows.end();it++){
			estimatedTrafficExchange+=flowValueVectorAsym[*it];
			flowsAsym.push_back(*it);
		}

	return estimatedTrafficExchange;

}



