/*
 * routing.cpp
 *
 *  Created on: Mar 1, 2012
 *      Author: Aemen
 */

#include "node.h"
#include "support.h"

linkInfo** linkIndex;
linkInfo** linkIndexSave;

map<int,connectedNodes> linkMap;
map<int,connectedNodes> flowSymMap;
map<int,connectedNodes> flowAsymMap;

list<int> freeFlowIndices;
int** flowIndex;
int** flowIndexSave;

bool* aliveLinkIndicator;
bool* aliveLinkIndicatorSave;

bool* aliveFlowIndicator;
bool* aliveFlowIndicatorSave;

list<flowInfo>* routingMatrix;
list<flowInfo>* routingMatrixAsym;
list<flowInfo>* routingMatrixSave;
list<flowInfo>* routingMatrixAsymSave;

unsigned int* flowDirectionFrom;
unsigned int* flowDirectionFromAsym;
unsigned int* flowDirectionFromSave;
unsigned int* flowDirectionFromAsymSave;

double* flowValueVector;
double* flowValueVectorAsym;
double* flowValueVectorSave;
double* flowValueVectorAsymSave;

double* linkValueVector;
double* linkValueVectorSave;
double* linkValueVectorUpstream;
double* linkValueVectorUpstreamSave;
double* linkValueVectorDownstream;
double* linkValueVectorDownstreamSave;
double* linkValueVectorFlat;
double* linkValueVectorFlatSave;
double* linkValueVectorFlatLeft;
double* linkValueVectorFlatLeftSave;
double* linkValueVectorFlatRight;
double* linkValueVectorFlatRightSave;

unsigned int maxFlows;
unsigned int maxLinks;

//TODO Remove experimental stuff
unsigned int* numFlowsOverLink;

void establishLinkWithProvider(const unsigned int& pNode, const unsigned int& qNode){

	unsigned int designatedRow=0;
	bool linkFound=false;

	for(unsigned int i=0;i<maxLinks;i++)
		if(aliveLinkIndicator[i]==0){
			aliveLinkIndicator[i]=1;
			designatedRow=i;
			linkFound=true;
			break;
		}

	if(linkFound){
		connectedNodes tmp;
		linkIndex[pNode][qNode].index=designatedRow;
		linkIndex[qNode][pNode].index=designatedRow;
		linkIndex[pNode][qNode].provider=qNode;
		linkIndex[qNode][pNode].provider=qNode;
		linkIndex[pNode][qNode].linkClass=CPLink;
		linkIndex[qNode][pNode].linkClass=CPLink;
		tmp.n1=pNode;
		tmp.n2=qNode;
		linkMap[designatedRow]=tmp;
	}

	else{

		string str("ERROR!! NO ROW AVAILABLE IN ROUTING MATRIX TO ESTABLISH LINK");
		endSimulation(str);

	}

}

void establishFlowWithProvider(const unsigned int& pNode,const unsigned int& qNode){

	unsigned int designatedColumn;
	//bool columnFound=false;
	flowInfo fi;

	/*
	if(flowIndex[pNode][qNode]==-1){	//flow does not exist
		for(unsigned int j=0;j<maxFlows;j++)
			if(aliveFlowIndicator[j]==0){
				aliveFlowIndicator[j]=1;
				designatedColumn=j;
				columnFound=true;
				break;
			}

		if(columnFound){
			flowIndex[pNode][qNode]=designatedColumn;
			flowIndex[qNode][pNode]=designatedColumn;
			aliveFlowIndicator[designatedColumn]=1;
		}

		else{
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}
	}

	else
		designatedColumn=flowIndex[pNode][qNode];
	*/

	if(flowIndex[pNode][qNode]==-1){
		if(freeFlowIndices.empty()){
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}

		else{
			designatedColumn=freeFlowIndices.front();
			freeFlowIndices.pop_front();
			flowIndex[pNode][qNode]=designatedColumn;
			flowIndex[qNode][pNode]=designatedColumn;
			aliveFlowIndicator[designatedColumn]=1;

		}
	}

	else{
		string str("ERROR!! TRYING TO ESTABLISH FLOW WHEN FLOW ALREADY EXISTS");
		endSimulation(str);
	}

	connectedNodes tmp;
	aliveFlowIndicator[designatedColumn]=1;

	fi.linkId=linkIndex[pNode][qNode].index;
	fi.flowDirection=UPSTREAM;
	routingMatrix[designatedColumn].push_back(fi);
	flowValueVector[designatedColumn]=trafficObj.trafficMatrix[pNode][qNode];
	flowDirectionFrom[designatedColumn]=pNode;
	tmp.n1=pNode;
	tmp.n2=qNode;
	tmp.linkIndices.push_back(fi.linkId);
	flowSymMap[designatedColumn]=tmp;

	fi.linkId=linkIndex[qNode][pNode].index;
	fi.flowDirection=DOWNSTREAM;
	routingMatrixAsym[designatedColumn].push_back(fi);
	flowValueVectorAsym[designatedColumn]=trafficObj.trafficMatrix[qNode][pNode];
	flowDirectionFromAsym[designatedColumn]=qNode;
	tmp.n1=qNode;
	tmp.n2=pNode;
	tmp.linkIndices.push_back(fi.linkId);
	flowAsymMap[designatedColumn]=tmp;

	linkMap[linkIndex[pNode][qNode].index].flowIndicesSym.push_back(designatedColumn);
	linkMap[linkIndex[pNode][qNode].index].flowIndicesAsym.push_back(designatedColumn);

}

void endLink(const unsigned int& pNode,const unsigned int& qNode){

	aliveLinkIndicator[linkIndex[pNode][qNode].index]=0;

	linkIndex[pNode][qNode].flowsSym.clear();
	linkIndex[qNode][pNode].flowsSym.clear();
	linkIndex[pNode][qNode].flowsAsym.clear();
	linkIndex[pNode][qNode].flowsAsym.clear();

	flowInfo fi;
	fi.linkId=linkIndex[pNode][qNode].index;
	routingMatrix[flowIndex[pNode][qNode]].remove(fi);
	routingMatrixAsym[flowIndex[pNode][qNode]].remove(fi);

	for(std::list<int>::iterator it=linkMap[linkIndex[pNode][qNode].index].flowIndicesSym.begin();it!=linkMap[linkIndex[pNode][qNode].index].flowIndicesSym.end();it++)
		flowSymMap[*it].linkIndices.remove(linkIndex[pNode][qNode].index);

	for(std::list<int>::iterator it=linkMap[linkIndex[pNode][qNode].index].flowIndicesAsym.begin();it!=linkMap[linkIndex[pNode][qNode].index].flowIndicesAsym.end();it++)
		flowAsymMap[*it].linkIndices.remove(linkIndex[pNode][qNode].index);

	linkMap.erase(linkIndex[pNode][qNode].index);

	linkIndex[pNode][qNode].index=-1;
	linkIndex[pNode][qNode].provider=-1;
	linkIndex[qNode][pNode].index=-1;
	linkIndex[qNode][pNode].provider=-1;

}

void endFlow(const unsigned int& sNode,const unsigned int& eNode){

	routingMatrix[flowIndex[sNode][eNode]].clear();
	routingMatrixAsym[flowIndex[sNode][eNode]].clear();

	for(std::list<int>::iterator it=flowSymMap[flowIndex[sNode][eNode]].linkIndices.begin();it!=flowSymMap[flowIndex[sNode][eNode]].linkIndices.end();it++)
		linkMap[*it].flowIndicesSym.remove(flowIndex[sNode][eNode]);

	for(std::list<int>::iterator it=flowAsymMap[flowIndex[sNode][eNode]].linkIndices.begin();it!=flowAsymMap[flowIndex[sNode][eNode]].linkIndices.end();it++)
		linkMap[*it].flowIndicesAsym.remove(flowIndex[sNode][eNode]);

	flowSymMap.erase(flowIndex[sNode][eNode]);
	flowAsymMap.erase(flowIndex[sNode][eNode]);

	aliveFlowIndicator[flowIndex[sNode][eNode]]=0;
	flowDirectionFrom[flowIndex[sNode][eNode]]=-1;
	flowDirectionFromAsym[flowIndex[sNode][eNode]]=-1;

	freeFlowIndices.push_front(flowIndex[sNode][eNode]);
	flowIndex[sNode][eNode]=-1;
	flowIndex[eNode][sNode]=-1;

}

void establishLinkWithPeer(const unsigned int& sPeer,const unsigned int& ePeer, bool isPaidPeeringLink){

	//TODO: Establishment of links and flows can be greatly optimized
	//instead of looping and finding out hte aliveLinkIndicator empty (and flows) just maintain  indices which are empty in a list

	int designatedRow=0;
	bool linkFound=false;

	for(unsigned int i=0;i<maxLinks;i++)
		if(aliveLinkIndicator[i]==0){
			aliveLinkIndicator[i]=1;
			designatedRow=i;
			linkFound=true;
			break;
		}

	if(linkFound){

		connectedNodes tmp;
		linkIndex[sPeer][ePeer].index=designatedRow;
		linkIndex[ePeer][sPeer].index=designatedRow;
		linkIndex[sPeer][ePeer].linkClass=PPLink;
		linkIndex[ePeer][sPeer].linkClass=PPLink;

		tmp.n1=sPeer;
		tmp.n2=ePeer;
		linkMap[designatedRow]=tmp;

		if(isPaidPeeringLink){
			linkIndex[sPeer][ePeer].provider=ePeer;
			linkIndex[ePeer][sPeer].provider=ePeer;
			linkIndex[sPeer][ePeer].linkClass=PPPLink;
			linkIndex[ePeer][sPeer].linkClass=PPPLink;
		}

	}

	else{

		string str("ERROR!! NO ROW AVAILABLE IN ROUTING MATRIX TO ESTABLISH LINK");
		endSimulation(str);

	}

}

void establishFlowWithPeer(const unsigned int& sPeer,const unsigned int& ePeer){

	int designatedColumn;
	//bool columnFound=false;
	flowInfo fi;

	/*
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

		}

		else{
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}
	}

	else
		designatedColumn=flowIndex[sPeer][ePeer];
	*/

	if(flowIndex[sPeer][ePeer]==-1){
		if(freeFlowIndices.empty()){
			string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
			endSimulation(str);
		}

		else{
			designatedColumn=freeFlowIndices.front();
			freeFlowIndices.pop_front();
			flowIndex[sPeer][ePeer]=designatedColumn;
			flowIndex[ePeer][sPeer]=designatedColumn;
			aliveFlowIndicator[designatedColumn]=true;
		}
	}

	else{
		string str("ERROR!! TRYING TO RE-ESTABLISH FLOW WITH WHEN A FLOW ALREADY EXISTS");
		endSimulation(str);
	}

	connectedNodes tmp;
	fi.linkId=linkIndex[sPeer][ePeer].index;
	if(sPeer<ePeer)
		fi.flowDirection=LEFT_TO_RIGHT;
	else
		fi.flowDirection=RIGHT_TO_LEFT;
	routingMatrix[designatedColumn].push_back(fi);
	flowValueVector[designatedColumn]=trafficObj.trafficMatrix[sPeer][ePeer];
	flowDirectionFrom[designatedColumn]=sPeer;
	tmp.n1=sPeer;
	tmp.n2=ePeer;
	tmp.linkIndices.push_back(fi.linkId);
	flowSymMap[designatedColumn]=tmp;


	fi.linkId=linkIndex[ePeer][sPeer].index;
	if(ePeer<sPeer)
		fi.flowDirection=LEFT_TO_RIGHT;
	else
		fi.flowDirection=RIGHT_TO_LEFT;
	routingMatrixAsym[designatedColumn].push_back(fi);
	flowValueVectorAsym[designatedColumn]=trafficObj.trafficMatrix[ePeer][sPeer];
	flowDirectionFromAsym[designatedColumn]=ePeer;
	tmp.n1=ePeer;
	tmp.n2=sPeer;
	tmp.linkIndices.push_back(fi.linkId);
	flowAsymMap[designatedColumn]=tmp;

	linkMap[linkIndex[sPeer][ePeer].index].flowIndicesSym.push_back(designatedColumn);
	linkMap[linkIndex[sPeer][ePeer].index].flowIndicesAsym.push_back(designatedColumn);

}

void endConditionalFlowsBetweenSets(const list<unsigned int>& sourceSet, const list<unsigned int>& endSet){

	//TODO: Optimize

	//ending previous flows between the two sets
	list<unsigned int>::const_iterator itS;
	list<unsigned int>::const_iterator itE;
	for(itS=sourceSet.begin();itS!=sourceSet.end();itS++)
		for(itE=endSet.begin();itE!=endSet.end();itE++)
			if(*itS!=*itE && linkIndex[*itS][*itE].index==-1 && flowIndex[*itS][*itE]!=-1){	//no link exists between the two nodes
#if DEBUG
		cout<<"Terminating flow between "<<*itS<<" and "<<*itE<<endl;
#endif

				endFlow(*itS,*itE);

#if DEBUG
		cout<<"Terminated flow between "<<*itS<<" and "<<*itE<<endl;
#endif

			}

}

void establishFlowsBetweenNodeAndSet(const unsigned int & x,const list<unsigned int> & endSet){

	list<unsigned int>::const_iterator itE;
	for(itE=endSet.begin();itE!=endSet.end();itE++)
		if(x!=*itE && flowIndex[x][*itE]==-1)
			establishFlowBetweenNonLinkedNodes(x,*itE);

}

void establishFlowsBetweenSets(const list<unsigned int> & sourceSet,const list<unsigned int> & endSet){

	list<unsigned int>::const_iterator itS;
	list<unsigned int>::const_iterator itE;
	for(itS=sourceSet.begin();itS!=sourceSet.end();itS++)
		for(itE=endSet.begin();itE!=endSet.end();itE++)
			if(*itS!=*itE && flowIndex[*itS][*itE]==-1){

				establishFlowBetweenNonLinkedNodes(*itS,*itE);

			}

}

bool establishFlowBetweenNonLinkedNodes(const unsigned int & startNode, const unsigned int & endNode){


	if(static_cast<int>(startNode)==-1 || static_cast<int>(endNode)==-1 || (startNode==endNode)){

		if(static_cast<int>(startNode)==-1){
			string str("ERROR!! ONE OF THE NODES (startNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}

		else{
			string str("ERROR!! ONE OF THE NODES (endNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}
	}

	if(flowIndex[startNode][endNode]!=-1){
		char errorString[100];
		sprintf(errorString,"ERROR!! Flow already exists between %d and %d",startNode,endNode);
		string str(errorString);
		endSimulation(str);
	}

	//Step 1 Find designated column
	//Step 2 Check if endnode is present in customer tree
	//Step 3 If Step 2 is false check if the endnode can be reached through peers
	//Step 4 If Step 3 is false ask providers to return path and choose the shortest among them

	int designatedColumn;
	//bool columnFound=false;

	/*
	if(flowIndex[startNode][endNode]==-1){
		for(unsigned int j=0;j<maxFlows;j++)
			if(aliveFlowIndicator[j]==0){
				aliveFlowIndicator[j]=1;
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
	*/

	if(freeFlowIndices.empty()){
		string str("ERROR!! NO COLUMN AVAILABLE IN ROUTING MATRIX TO ESTABLISH FLOW");
		endSimulation(str);
	}

	else{
		designatedColumn=freeFlowIndices.front();
		freeFlowIndices.pop_front();
		flowIndex[startNode][endNode]=designatedColumn;
		flowIndex[endNode][startNode]=designatedColumn;
		aliveFlowIndicator[designatedColumn]=true;
		flowDirectionFrom[designatedColumn]=startNode;
	}

	if(aliveNodes[startNode].isPresentInCustomerTree(endNode)){	//endNode is present in customer tree of startNode

		list<NodePrice>::iterator it;
		routeComparison* customerRouteComparison;
		list<nodePairs> tempList;
		nodePairs tempNP;
		int temp=0;
		int index=0;

		customerRouteComparison=new routeComparison[aliveNodes[startNode].I.size()];

		for(it=aliveNodes[startNode].I.begin();it!=aliveNodes[startNode].I.end();it++,temp++){

			customerRouteComparison[temp].routeProvider=(*it).nId;

			if(aliveNodes[(*it).nId].isPresentInCustomerTree(endNode)){

				if(flowIndex[(*it).nId][endNode]==-1){

					if(!establishFlowBetweenNonLinkedNodes((*it).nId,endNode)){

						netDisconnected=true;
						string str("ERROR!! Flow could not be established in establishFlow for node in CustomerTree");
						endSimulation(str);
						return false;
					}
				}

				if(flowDirectionFrom[flowIndex[(*it).nId][endNode]]==(*it).nId){
					copySecondListIntoFirst<flowInfo>(customerRouteComparison[temp].route,routingMatrix[flowIndex[(*it).nId][endNode]]);
				}

				else{
					copySecondListIntoFirst<flowInfo>(customerRouteComparison[temp].route,routingMatrixAsym[flowIndex[(*it).nId][endNode]]);
				}

				tempNP.n1=(*it).nId;
				tempNP.n2=customerRouteComparison[temp].route.size();
				tempNP.n3=temp;
				tempList.push_back(tempNP);

			}//end if endNode is present in customer tree of immediate customer

		}//end for

		tempList.sort(sortBySecond);
		temp=tempList.front().n1;
		index=tempList.front().n3;

		if(flowDirectionFrom[flowIndex[startNode][temp]]==startNode)
			copySecondAndThirdListIntoFirst<flowInfo>(routingMatrix[designatedColumn],routingMatrix[flowIndex[startNode][temp]],customerRouteComparison[index].route);
		else
			copySecondAndThirdListIntoFirst<flowInfo>(routingMatrix[designatedColumn],routingMatrixAsym[flowIndex[startNode][temp]],customerRouteComparison[index].route);

		aliveFlowIndicator[designatedColumn]=1;
		flowValueVector[designatedColumn]=trafficObj.trafficMatrix[startNode][endNode];
		flowDirectionFrom[designatedColumn]=startNode;

		delete []customerRouteComparison;

		if(establishFlowBetweenNonLinkedNodesAsym(endNode,startNode)){

			connectedNodes tmp;
			tmp.n1=startNode;
			tmp.n2=endNode;
			flowSymMap[designatedColumn]=tmp;

			//update linkMaps for the flows
			for(list<flowInfo>::iterator ft=routingMatrix[designatedColumn].begin();ft!=routingMatrix[designatedColumn].end();ft++){
				linkMap[(*ft).linkId].flowIndicesSym.push_back(designatedColumn);
				flowSymMap[designatedColumn].linkIndices.push_back((*ft).linkId);
			}

			for(list<flowInfo>::iterator ft=routingMatrixAsym[designatedColumn].begin();ft!=routingMatrixAsym[designatedColumn].end();ft++){
				linkMap[(*ft).linkId].flowIndicesAsym.push_back(designatedColumn);
				flowAsymMap[designatedColumn].linkIndices.push_back((*ft).linkId);
			}

			return true;
		}

		else
			return false;

	}//end node is present in customer tree of start node

	//endNode not present in customer tree of start node
	//ask peers
	if(!aliveNodes[startNode].K.empty()){

		list<unsigned int>::iterator it;
		routeComparison* peerRouteComparison;
		int temp=0;
		int index=0;
		peerRouteComparison=new routeComparison[aliveNodes[startNode].K.size()];
		nodePairs tempNP;
		list<nodePairs> tempList;
		bool peerHasPath=false;

		for(std::list<NodePrice>::iterator itNP=aliveNodes[startNode].K.begin();itNP!=aliveNodes[startNode].K.end();itNP++,temp++){

			peerRouteComparison[temp].routeProvider=(*itNP).nId;

			if(aliveNodes[(*itNP).nId].isPresentInCustomerTree(endNode)){

				peerHasPath=true;
				if(flowIndex[(*itNP).nId][endNode]==-1){

					if(!establishFlowBetweenNonLinkedNodes((*itNP).nId,endNode)){

						netDisconnected=true;
						string str("ERROR!! Flow could not be established in establishFlow for node in CustomerTree");
						endSimulation(str);
						return false;
					}
				}

				if(flowDirectionFrom[flowIndex[(*itNP).nId][endNode]]==(*itNP).nId){
					copySecondListIntoFirst<flowInfo>(peerRouteComparison[temp].route,routingMatrix[flowIndex[(*itNP).nId][endNode]]);
				}

				else{
					copySecondListIntoFirst<flowInfo>(peerRouteComparison[temp].route,routingMatrixAsym[flowIndex[(*itNP).nId][endNode]]);
				}

				tempNP.n1=(*itNP).nId;
				tempNP.n2=peerRouteComparison[temp].route.size();
				tempNP.n3=temp;
				tempList.push_back(tempNP);

			}//end if endNode is present in customer tree of immediate customer

		}//end for

		if(peerHasPath){
			tempList.sort(sortBySecond);
			temp=tempList.front().n1;
			index=tempList.front().n3;

			if(flowDirectionFrom[flowIndex[startNode][temp]]==startNode)
				copySecondAndThirdListIntoFirst<flowInfo>(routingMatrix[designatedColumn],routingMatrix[flowIndex[startNode][temp]],peerRouteComparison[index].route);
			else
				copySecondAndThirdListIntoFirst<flowInfo>(routingMatrix[designatedColumn],routingMatrixAsym[flowIndex[startNode][temp]],peerRouteComparison[index].route);

			aliveFlowIndicator[designatedColumn]=1;
			flowValueVector[designatedColumn]=trafficObj.trafficMatrix[startNode][endNode];
			flowDirectionFrom[designatedColumn]=startNode;

			delete []peerRouteComparison;

			if(establishFlowBetweenNonLinkedNodesAsym(endNode,startNode)){

				connectedNodes tmp;
				tmp.n1=startNode;
				tmp.n2=endNode;
				flowSymMap[designatedColumn]=tmp;

				//update linkMaps for the flows
				for(list<flowInfo>::iterator ft=routingMatrix[designatedColumn].begin();ft!=routingMatrix[designatedColumn].end();ft++){
					linkMap[(*ft).linkId].flowIndicesSym.push_back(designatedColumn);
				}

				for(list<flowInfo>::iterator ft=routingMatrixAsym[designatedColumn].begin();ft!=routingMatrixAsym[designatedColumn].end();ft++){
					linkMap[(*ft).linkId].flowIndicesAsym.push_back(designatedColumn);
				}

				return true;
			}

			else
				return false;
		}

	}//end if asking peers

	if(!aliveNodes[startNode].Q.empty()){

		list<NodePrice>::iterator it;
		routeComparison* providerRouteComparison;
		int temp=0;
		int index=0;
		nodePairs tempNP;
		list<nodePairs> tempList;

		providerRouteComparison=new routeComparison[aliveNodes[startNode].Q.size()];

		for(it=aliveNodes[startNode].Q.begin();it!=aliveNodes[startNode].Q.end();it++,temp++){

			providerRouteComparison[temp].routeProvider=(*it).nId;

			if(flowIndex[(*it).nId][endNode]==-1){

				if(!establishFlowBetweenNonLinkedNodes((*it).nId,endNode)){

					netDisconnected=true;
					string str("ERROR!! Flow could not be established in establishFlow for node in PeerTree");
					endSimulation(str);
					return false;
				}

			}

			if(flowDirectionFrom[flowIndex[(*it).nId][endNode]]==(*it).nId){
				copySecondListIntoFirst<flowInfo>(providerRouteComparison[temp].route,routingMatrix[flowIndex[(*it).nId][endNode]]);
			}

			else{
				copySecondListIntoFirst<flowInfo>(providerRouteComparison[temp].route,routingMatrixAsym[flowIndex[(*it).nId][endNode]]);
			}

			tempNP.n1=(*it).nId;
			tempNP.n2=providerRouteComparison[temp].route.size();
			tempNP.n3=temp;
			tempList.push_back(tempNP);

		}//end for

		tempList.sort(sortBySecond);
		temp=tempList.front().n1;
		index=tempList.front().n3;

		if(flowDirectionFrom[flowIndex[startNode][temp]]==startNode)
			copySecondAndThirdListIntoFirst<flowInfo>(routingMatrix[designatedColumn],routingMatrix[flowIndex[startNode][temp]],providerRouteComparison[index].route);
		else
			copySecondAndThirdListIntoFirst<flowInfo>(routingMatrix[designatedColumn],routingMatrixAsym[flowIndex[startNode][temp]],providerRouteComparison[index].route);

		aliveFlowIndicator[designatedColumn]=1;
		flowValueVector[designatedColumn]=trafficObj.trafficMatrix[startNode][endNode];
		flowDirectionFrom[designatedColumn]=startNode;

		delete []providerRouteComparison;

		if(establishFlowBetweenNonLinkedNodesAsym(endNode,startNode)){

			connectedNodes tmp;
			tmp.n1=startNode;
			tmp.n2=endNode;
			flowSymMap[designatedColumn]=tmp;

			//update linkMaps for the flows
			for(list<flowInfo>::iterator ft=routingMatrix[designatedColumn].begin();ft!=routingMatrix[designatedColumn].end();ft++){
				linkMap[(*ft).linkId].flowIndicesSym.push_back(designatedColumn);
			}

			for(list<flowInfo>::iterator ft=routingMatrixAsym[designatedColumn].begin();ft!=routingMatrixAsym[designatedColumn].end();ft++){
				linkMap[(*ft).linkId].flowIndicesAsym.push_back(designatedColumn);
			}

			return true;
		}

		else
			return false;

	}

	return false;

}

bool establishFlowBetweenNonLinkedNodesAsym(const unsigned int & startNode, const unsigned int & endNode){

	if(static_cast<int>(startNode)==-1 || static_cast<int>(endNode)==-1){

		if(static_cast<int>(startNode)==-1){
			string str("ERROR!! ONE OF THE NODES (startNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}
		else{
			string str("ERROR!! ONE OF THE NODES (endNode) IN ESTABLISH FLOW IS -1. TERMINATING SIMULATION");
			endSimulation(str);
		}
	}

	//Step 1 Find designated column
	//Step 2 Check if endnode is present in customer tree
	//Step 3 If Step 2 is false check if the endnode can be reached through peers
	//Step 4 If Step 3 is false ask providers to return path and choose the shortest among them

	int designatedColumn;
	//bool columnFound=false;

	if(flowIndex[startNode][endNode]==-1){

		char errorString[100];
		sprintf(errorString,"ERROR!!! establishFlowBetweenNonLinkedNodesAsym called between %d and %d when no flow exists between %d and %d",startNode,endNode,endNode,startNode);
		string str(errorString);
		endSimulation(str);
		/*
		for(unsigned int j=0;j<maxFlows;j++)
			if(aliveFlowIndicator[j]==0){
				aliveFlowIndicator[j]=1;
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
		*/

	}

	designatedColumn=flowIndex[startNode][endNode];
	flowDirectionFromAsym[designatedColumn]=startNode;

	if(aliveNodes[startNode].isPresentInCustomerTree(endNode)){	//endNode is present in customer tree of startNode

		list<NodePrice>::iterator it;
		routeComparison* customerRouteComparison;
		list<nodePairs> tempList;
		nodePairs tempNP;
		int temp=0;
		int index=0;

		customerRouteComparison=new routeComparison[aliveNodes[startNode].I.size()];

		for(it=aliveNodes[startNode].I.begin();it!=aliveNodes[startNode].I.end();it++,temp++){

			customerRouteComparison[temp].routeProvider=(*it).nId;

			if(aliveNodes[(*it).nId].isPresentInCustomerTree(endNode)){

				if(flowIndex[(*it).nId][endNode]==-1){

					if(!establishFlowBetweenNonLinkedNodes((*it).nId,endNode)){

						netDisconnected=true;
						string str("ERROR!! Flow could not be established in establishFlow for node in CustomerTree");
						endSimulation(str);
						return false;
					}
				}

				if(flowDirectionFrom[flowIndex[(*it).nId][endNode]]==(*it).nId){
					copySecondListIntoFirst<flowInfo>(customerRouteComparison[temp].route,routingMatrix[flowIndex[(*it).nId][endNode]]);
				}

				else{
					copySecondListIntoFirst<flowInfo>(customerRouteComparison[temp].route,routingMatrixAsym[flowIndex[(*it).nId][endNode]]);
				}

				tempNP.n1=(*it).nId;
				tempNP.n2=customerRouteComparison[temp].route.size();
				tempNP.n3=temp;
				tempList.push_back(tempNP);

			}//end if endNode is present in customer tree of immediate customer

		}//end for

		tempList.sort(sortBySecond);
		temp=tempList.front().n1;
		index=tempList.front().n3;

		if(flowDirectionFrom[flowIndex[startNode][temp]]==startNode)
			copySecondAndThirdListIntoFirst<flowInfo>(routingMatrixAsym[designatedColumn],routingMatrix[flowIndex[startNode][temp]],customerRouteComparison[index].route);
		else
			copySecondAndThirdListIntoFirst<flowInfo>(routingMatrixAsym[designatedColumn],routingMatrixAsym[flowIndex[startNode][temp]],customerRouteComparison[index].route);

		aliveFlowIndicator[designatedColumn]=1;
		flowValueVectorAsym[designatedColumn]=trafficObj.trafficMatrix[startNode][endNode];
		flowDirectionFromAsym[designatedColumn]=startNode;

		delete []customerRouteComparison;

		connectedNodes tmp;
		tmp.n1=startNode;
		tmp.n2=endNode;
		flowAsymMap[designatedColumn]=tmp;

		return true;

	}//end node is present in customer tree of start node

	//endNode not present in customer tree of start node
	//ask peers
	if(!aliveNodes[startNode].K.empty()){

		bool peerHasPath=false;
		list<unsigned int>::iterator it;
		routeComparison* peerRouteComparison;
		int temp=0;
		int index=0;
		peerRouteComparison=new routeComparison[aliveNodes[startNode].K.size()];
		nodePairs tempNP;
		list<nodePairs> tempList;

		for(std::list<NodePrice>::iterator itNP=aliveNodes[startNode].K.begin();itNP!=aliveNodes[startNode].K.end();itNP++,temp++){

			peerRouteComparison[temp].routeProvider=(*itNP).nId;

			if(aliveNodes[(*itNP).nId].isPresentInCustomerTree(endNode)){
				peerHasPath=true;
				if(flowIndex[(*itNP).nId][endNode]==-1){

					if(!establishFlowBetweenNonLinkedNodes((*itNP).nId,endNode)){

						netDisconnected=true;
						string str("ERROR!! Flow could not be established in establishFlow for node in CustomerTree");
						endSimulation(str);
						return false;
					}
				}

				if(flowDirectionFrom[flowIndex[(*itNP).nId][endNode]]==(*itNP).nId){
					copySecondListIntoFirst<flowInfo>(peerRouteComparison[temp].route,routingMatrix[flowIndex[(*itNP).nId][endNode]]);
				}

				else{
					copySecondListIntoFirst<flowInfo>(peerRouteComparison[temp].route,routingMatrixAsym[flowIndex[(*itNP).nId][endNode]]);
				}

				tempNP.n1=(*itNP).nId;
				tempNP.n2=peerRouteComparison[temp].route.size();
				tempNP.n3=temp;
				tempList.push_back(tempNP);

			}//end if endNode is present in customer tree of immediate customer

		}//end for

		if(peerHasPath){
			tempList.sort(sortBySecond);
			temp=tempList.front().n1;
			index=tempList.front().n3;

			if(flowDirectionFrom[flowIndex[startNode][temp]]==startNode)
				copySecondAndThirdListIntoFirst<flowInfo>(routingMatrixAsym[designatedColumn],routingMatrix[flowIndex[startNode][temp]],peerRouteComparison[index].route);
			else
				copySecondAndThirdListIntoFirst<flowInfo>(routingMatrixAsym[designatedColumn],routingMatrixAsym[flowIndex[startNode][temp]],peerRouteComparison[index].route);

			aliveFlowIndicator[designatedColumn]=1;
			flowValueVectorAsym[designatedColumn]=trafficObj.trafficMatrix[startNode][endNode];
			flowDirectionFromAsym[designatedColumn]=startNode;

			delete []peerRouteComparison;

			connectedNodes tmp;
			tmp.n1=startNode;
			tmp.n2=endNode;
			flowAsymMap[designatedColumn]=tmp;

			return true;
		}

	}//end if asking peers


	if(!aliveNodes[startNode].Q.empty()){

		list<NodePrice>::iterator it;
		routeComparison* providerRouteComparison;
		int temp=0;
		int index=0;
		nodePairs tempNP;
		list<nodePairs> tempList;

		providerRouteComparison=new routeComparison[aliveNodes[startNode].Q.size()];

		for(it=aliveNodes[startNode].Q.begin();it!=aliveNodes[startNode].Q.end();it++,temp++){

			providerRouteComparison[temp].routeProvider=(*it).nId;

			if(flowIndex[(*it).nId][endNode]==-1){

				if(!establishFlowBetweenNonLinkedNodes((*it).nId,endNode)){

					netDisconnected=true;
					string str("ERROR!! Flow could not be established in establishFlow for node in PeerTree");
					endSimulation(str);
					return false;
				}

			}

			if(flowDirectionFrom[flowIndex[(*it).nId][endNode]]==(*it).nId){
				copySecondListIntoFirst<flowInfo>(providerRouteComparison[temp].route,routingMatrix[flowIndex[(*it).nId][endNode]]);
			}

			else{
				copySecondListIntoFirst<flowInfo>(providerRouteComparison[temp].route,routingMatrixAsym[flowIndex[(*it).nId][endNode]]);
			}

			tempNP.n1=(*it).nId;
			tempNP.n2=providerRouteComparison[temp].route.size();
			tempNP.n3=temp;
			tempList.push_back(tempNP);

		}//end for

		tempList.sort(sortBySecond);
		temp=tempList.front().n1;
		index=tempList.front().n3;

		if(flowDirectionFrom[flowIndex[startNode][temp]]==startNode)
			copySecondAndThirdListIntoFirst<flowInfo>(routingMatrixAsym[designatedColumn],routingMatrix[flowIndex[startNode][temp]],providerRouteComparison[index].route);
		else
			copySecondAndThirdListIntoFirst<flowInfo>(routingMatrixAsym[designatedColumn],routingMatrixAsym[flowIndex[startNode][temp]],providerRouteComparison[index].route);

		aliveFlowIndicator[designatedColumn]=1;
		flowValueVectorAsym[designatedColumn]=trafficObj.trafficMatrix[startNode][endNode];
		flowDirectionFromAsym[designatedColumn]=startNode;

		delete []providerRouteComparison;

		connectedNodes tmp;
		tmp.n1=startNode;
		tmp.n2=endNode;
		flowAsymMap[designatedColumn]=tmp;

		return true;

	}

	return false;

}

void computeTrafficFlowsAcrossNetwork(){

	VolumePrice tempVP;
	std::multimap<int,int> numFlowsOverLinkMap;
	std::multimap<int,int> numFlowsOverLinkMapAsym;

	for(unsigned int i=0;i<maxLinks;i++){
		linkValueVector[i]=0;
		linkValueVectorUpstream[i]=0;
		linkValueVectorDownstream[i]=0;
		linkValueVectorFlat[i]=0;
		linkValueVectorFlatLeft[i]=0;
		linkValueVectorFlatRight[i]=0;

#if EXPERIMENT
		numFlowsOverLink[i]=0;
#endif
	}

	for(unsigned int i=0;i<Node::activeNodes;i++){
		aliveNodes[i].customerVPList.clear();
		aliveNodes[i].providerVPList.clear();
		aliveNodes[i].freePeerVPList.clear();
		aliveNodes[i].paidPeerVPList.clear();
		aliveNodes[i].paidPeerVCList.clear();
		aliveNodes[i].Vp=aliveNodes[i].Vc=aliveNodes[i].Vpp=aliveNodes[i].Vt=aliveNodes[i].V=0;

#if EXPERIMENT
		aliveNodes[i].numFlows=0;
		aliveNodes[i].flowsObserved.clear();
		aliveNodes[i].flowsObservedAsym.clear();
#endif
	}

	list<flowInfo>::iterator it;
	for(unsigned int i=0;i<maxFlows;i++){

		if(!routingMatrix[i].empty() && !routingMatrixAsym[i].empty()){
			for(it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++){

				linkIndex[linkMap[(*it).linkId].n1][linkMap[(*it).linkId].n2].flowsSym.push_back(i);
				linkIndex[linkMap[(*it).linkId].n2][linkMap[(*it).linkId].n1].flowsAsym.push_back(i);

				if((*it).flowDirection==UPSTREAM)
					linkValueVectorUpstream[(*it).linkId]+=flowValueVector[i];

				else if((*it).flowDirection==DOWNSTREAM)
					linkValueVectorDownstream[(*it).linkId]+=flowValueVector[i];

				else if((*it).flowDirection==LEFT_TO_RIGHT)
					linkValueVectorFlatLeft[(*it).linkId]+=flowValueVector[i];

				else if((*it).flowDirection==RIGHT_TO_LEFT)
					linkValueVectorFlatRight[(*it).linkId]+=flowValueVector[i];


				else{
					string str("ERROR!! UNKNOWN FLOW DIRECTION OVER LINK");
					endSimulation(str);

				}

#if EXPERIMENT
				numFlowsOverLink[(*it).linkId]++;
				numFlowsOverLinkMap.insert(std::pair<int,int>((*it).linkId,i));
#endif
			}

			for(it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++){

				linkIndex[linkMap[(*it).linkId].n1][linkMap[(*it).linkId].n2].flowsAsym.push_back(i);
				linkIndex[linkMap[(*it).linkId].n2][linkMap[(*it).linkId].n1].flowsAsym.push_back(i);

				if((*it).flowDirection==UPSTREAM)
					linkValueVectorUpstream[(*it).linkId]+=flowValueVectorAsym[i];

				else if((*it).flowDirection==DOWNSTREAM)
					linkValueVectorDownstream[(*it).linkId]+=flowValueVectorAsym[i];

				else if((*it).flowDirection==LEFT_TO_RIGHT)
					linkValueVectorFlatLeft[(*it).linkId]+=flowValueVectorAsym[i];

				else if((*it).flowDirection==RIGHT_TO_LEFT)
					linkValueVectorFlatRight[(*it).linkId]+=flowValueVectorAsym[i];


				else{
					string str("ERROR!! UNKNOWN FLOW DIRECTION OVER LINK");
					endSimulation(str);

				}

#if EXPERIMENT
				numFlowsOverLink[(*it).linkId]++;
				numFlowsOverLinkMapAsym.insert(std::pair<int,int>((*it).linkId,i));
#endif
			}

		}

	}

	for(unsigned int i=0;i<maxLinks;i++){
		linkValueVector[i]=linkValueVectorFlatLeft[i]+linkValueVectorFlatRight[i]+linkValueVectorUpstream[i]+linkValueVectorDownstream[i];
	}

	for(unsigned int i=0;i<(Node::activeNodes-1);i++){

		for(unsigned int j=i+1;j<Node::activeNodes;j++){

			if(linkIndex[i][j].index!=-1){

				//TODO Remove Experimental Stuff
				std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> ret;
				ret=numFlowsOverLinkMap.equal_range(linkIndex[i][j].index);
				for(std::multimap<int,int>::iterator it=ret.first; it!=ret.second; ++it){
					aliveNodes[i].flowsObserved.push_back(it->second);
					aliveNodes[j].flowsObserved.push_back(it->second);
				}

				ret=numFlowsOverLinkMapAsym.equal_range(linkIndex[i][j].index);
				for(std::multimap<int,int>::iterator it=ret.first; it!=ret.second; ++it){
					aliveNodes[i].flowsObservedAsym.push_back(it->second);
					aliveNodes[j].flowsObservedAsym.push_back(it->second);
				}

				if(linkIndex[i][j].linkClass==CPLink){

					if(linkIndex[i][j].provider==i){

						if(DOMINANTDIRECTIONBILLING==false){

							tempVP.volume=linkValueVector[linkIndex[i][j].index];
							tempVP.contractPrice=aliveNodes[j].getContractPriceForProvider(i);

							aliveNodes[j].Vp+=linkValueVector[linkIndex[i][j].index];
							aliveNodes[i].Vc+=linkValueVector[linkIndex[i][j].index];

							aliveNodes[i].customerVPList.push_back(tempVP);
							aliveNodes[j].providerVPList.push_back(tempVP);

						}

						else{

							if(linkValueVectorUpstream[linkIndex[i][j].index]>linkValueVector[linkIndex[i][j].index])
								tempVP.volume=linkValueVectorUpstream[linkIndex[i][j].index];
							else
								tempVP.volume=linkValueVectorDownstream[linkIndex[i][j].index];

							tempVP.contractPrice=aliveNodes[j].getContractPriceForProvider(i);

							aliveNodes[j].Vp+=tempVP.volume;
							aliveNodes[i].Vc+=tempVP.volume;

							aliveNodes[i].customerVPList.push_back(tempVP);
							aliveNodes[j].providerVPList.push_back(tempVP);

						}

					}//end if

					else{

						if(DOMINANTDIRECTIONBILLING==false){

							tempVP.volume=linkValueVector[linkIndex[i][j].index];
							tempVP.contractPrice=aliveNodes[i].getContractPriceForProvider(j);

							aliveNodes[i].Vp+=linkValueVector[linkIndex[i][j].index];
							aliveNodes[j].Vc+=linkValueVector[linkIndex[i][j].index];

							aliveNodes[j].customerVPList.push_back(tempVP);
							aliveNodes[i].providerVPList.push_back(tempVP);

						}

						else{

							if(linkValueVectorUpstream[linkIndex[i][j].index]>linkValueVector[linkIndex[i][j].index])
								tempVP.volume=linkValueVectorUpstream[linkIndex[i][j].index];
							else
								tempVP.volume=linkValueVectorDownstream[linkIndex[i][j].index];

							tempVP.contractPrice=aliveNodes[i].getContractPriceForProvider(j);

							aliveNodes[i].Vp+=tempVP.volume;
							aliveNodes[j].Vc+=tempVP.volume;

							aliveNodes[j].customerVPList.push_back(tempVP);
							aliveNodes[i].providerVPList.push_back(tempVP);

						}

					}//end else

				}//end if for CPLink

				else if(linkIndex[i][j].linkClass==PPLink){	//ordinary peering link

					tempVP.volume=linkValueVector[linkIndex[i][j].index];

					aliveNodes[i].Vpp+=linkValueVector[linkIndex[i][j].index];
					aliveNodes[j].Vpp+=linkValueVector[linkIndex[i][j].index];

					aliveNodes[i].freePeerVPList.push_back(tempVP);
					aliveNodes[j].freePeerVPList.push_back(tempVP);

				}

			}//end if for index!=-1

		}//end for

	}//end for

#if EXPERIMENT
	for(unsigned int i=0;i<Node::activeNodes;i++){

		aliveNodes[i].flowsObserved.sort();
		aliveNodes[i].flowsObservedAsym.sort();
		aliveNodes[i].flowsObserved.unique();
		aliveNodes[i].flowsObservedAsym.unique();
		aliveNodes[i].numFlows=aliveNodes[i].flowsObserved.size()+aliveNodes[i].flowsObservedAsym.size();

	}
#endif

}

void computeTrafficFlowsAcrossNode(const unsigned int& id){

	VolumePrice tempVP;
	std::multimap<int,int> numFlowsOverLinkMap;
	std::multimap<int,int> numFlowsOverLinkMapAsym;

	for(unsigned int i=0;i<maxLinks;i++){
		linkValueVector[i]=0;
		linkValueVectorUpstream[i]=0;
		linkValueVectorDownstream[i]=0;
		linkValueVectorFlat[i]=0;
		linkValueVectorFlatLeft[i]=0;
		linkValueVectorFlatRight[i]=0;

#if EXPERIMENT
		numFlowsOverLink[i]=0;
#endif
	}

	{
		aliveNodes[id].customerVPList.clear();
		aliveNodes[id].providerVPList.clear();
		aliveNodes[id].freePeerVPList.clear();
		aliveNodes[id].paidPeerVPList.clear();
		aliveNodes[id].paidPeerVCList.clear();
		aliveNodes[id].Vp=aliveNodes[id].Vc=aliveNodes[id].Vpp=aliveNodes[id].Vt=aliveNodes[id].V=0;

#if EXPERIMENT
		aliveNodes[i].numFlows=0;
		aliveNodes[i].flowsObserved.clear();
		aliveNodes[i].flowsObservedAsym.clear();
#endif
	}

	list<flowInfo>::iterator it;
	list<int> linkIndices;
	list<int> flowIndices;

	if(!aliveNodes[id].Q.empty())
		for(list<NodePrice>::iterator itNP=aliveNodes[id].Q.begin();itNP!=aliveNodes[id].Q.end();itNP++){
			linkIndices.push_back(linkIndex[id][(*itNP).nId].index);
		}

	if(!aliveNodes[id].I.empty())
		for(list<NodePrice>::iterator itNP=aliveNodes[id].I.begin();itNP!=aliveNodes[id].I.end();itNP++){
			linkIndices.push_back(linkIndex[id][(*itNP).nId].index);
		}

	if(!aliveNodes[id].K.empty())
		for(list<NodePrice>::iterator itNP=aliveNodes[id].K.begin();itNP!=aliveNodes[id].K.end();itNP++){
			linkIndices.push_back(linkIndex[id][(*itNP).nId].index);
		}

	for(list<int>::iterator itL=linkIndices.begin();itL!=linkIndices.end();itL++){
		std::copy(linkMap[*itL].flowIndicesSym.begin(),linkMap[*itL].flowIndicesSym.end(),back_inserter(flowIndices));
		std::copy(linkMap[*itL].flowIndicesAsym.begin(),linkMap[*itL].flowIndicesAsym.end(),back_inserter(flowIndices));
	}

	flowIndices.sort();
	flowIndices.unique();

	unsigned int i;

	for(list<int>::iterator itF=flowIndices.begin();itF!=flowIndices.end();itF++){

		i=*itF;
		if(!routingMatrix[i].empty() && !routingMatrixAsym[i].empty()){
			for(it=routingMatrix[i].begin();it!=routingMatrix[i].end();it++){

				linkIndex[linkMap[(*it).linkId].n1][linkMap[(*it).linkId].n2].flowsSym.push_back(i);
				linkIndex[linkMap[(*it).linkId].n2][linkMap[(*it).linkId].n1].flowsAsym.push_back(i);

				if((*it).flowDirection==UPSTREAM)
					linkValueVectorUpstream[(*it).linkId]+=flowValueVector[i];

				else if((*it).flowDirection==DOWNSTREAM)
					linkValueVectorDownstream[(*it).linkId]+=flowValueVector[i];

				else if((*it).flowDirection==LEFT_TO_RIGHT)
					linkValueVectorFlatLeft[(*it).linkId]+=flowValueVector[i];

				else if((*it).flowDirection==RIGHT_TO_LEFT)
					linkValueVectorFlatRight[(*it).linkId]+=flowValueVector[i];


				else{
					string str("ERROR!! UNKNOWN FLOW DIRECTION OVER LINK");
					endSimulation(str);

				}

#if EXPERIMENT
				numFlowsOverLink[(*it).linkId]++;
				numFlowsOverLinkMap.insert(std::pair<int,int>((*it).linkId,i));
#endif
			}

			for(it=routingMatrixAsym[i].begin();it!=routingMatrixAsym[i].end();it++){

				linkIndex[linkMap[(*it).linkId].n1][linkMap[(*it).linkId].n2].flowsAsym.push_back(i);
				linkIndex[linkMap[(*it).linkId].n2][linkMap[(*it).linkId].n1].flowsAsym.push_back(i);

				if((*it).flowDirection==UPSTREAM)
					linkValueVectorUpstream[(*it).linkId]+=flowValueVectorAsym[i];

				else if((*it).flowDirection==DOWNSTREAM)
					linkValueVectorDownstream[(*it).linkId]+=flowValueVectorAsym[i];

				else if((*it).flowDirection==LEFT_TO_RIGHT)
					linkValueVectorFlatLeft[(*it).linkId]+=flowValueVectorAsym[i];

				else if((*it).flowDirection==RIGHT_TO_LEFT)
					linkValueVectorFlatRight[(*it).linkId]+=flowValueVectorAsym[i];


				else{
					string str("ERROR!! UNKNOWN FLOW DIRECTION OVER LINK");
					endSimulation(str);

				}

#if EXPERIMENT
				numFlowsOverLink[(*it).linkId]++;
				numFlowsOverLinkMapAsym.insert(std::pair<int,int>((*it).linkId,i));
#endif
			}

		}

	}

	for(list<int>::iterator itL=linkIndices.begin();itL!=linkIndices.end();itL++){
		i=*itL;
		linkValueVector[i]=linkValueVectorFlatLeft[i]+linkValueVectorFlatRight[i]+linkValueVectorUpstream[i]+linkValueVectorDownstream[i];
	}

	i=id;
	//for(unsigned int i=0;i<(Node::activeNodes-1);i++){

	for(unsigned int j=0;j<Node::activeNodes;j++){

		if(linkIndex[i][j].index!=-1){

			//TODO Remove Experimental Stuff
			std::pair <std::multimap<int,int>::iterator, std::multimap<int,int>::iterator> ret;
			ret=numFlowsOverLinkMap.equal_range(linkIndex[i][j].index);
			for(std::multimap<int,int>::iterator it=ret.first; it!=ret.second; ++it){
				aliveNodes[i].flowsObserved.push_back(it->second);
				aliveNodes[j].flowsObserved.push_back(it->second);
			}

			ret=numFlowsOverLinkMapAsym.equal_range(linkIndex[i][j].index);
			for(std::multimap<int,int>::iterator it=ret.first; it!=ret.second; ++it){
				aliveNodes[i].flowsObservedAsym.push_back(it->second);
				aliveNodes[j].flowsObservedAsym.push_back(it->second);
			}

			if(linkIndex[i][j].linkClass==CPLink){

				if(linkIndex[i][j].provider==i){

					if(DOMINANTDIRECTIONBILLING==false){

						tempVP.volume=linkValueVector[linkIndex[i][j].index];
						tempVP.contractPrice=aliveNodes[j].getContractPriceForProvider(i);


						aliveNodes[j].Vp+=linkValueVector[linkIndex[i][j].index];
						aliveNodes[i].Vc+=linkValueVector[linkIndex[i][j].index];

						tempVP.linkedNode=j;
						aliveNodes[i].customerVPList.push_back(tempVP);

						tempVP.linkedNode=i;
						aliveNodes[j].providerVPList.push_back(tempVP);

					}

					else{

						if(linkValueVectorUpstream[linkIndex[i][j].index]>linkValueVector[linkIndex[i][j].index])
							tempVP.volume=linkValueVectorUpstream[linkIndex[i][j].index];
						else
							tempVP.volume=linkValueVectorDownstream[linkIndex[i][j].index];

						tempVP.contractPrice=aliveNodes[j].getContractPriceForProvider(i);

						aliveNodes[j].Vp+=tempVP.volume;
						aliveNodes[i].Vc+=tempVP.volume;

						tempVP.linkedNode=j;
						aliveNodes[i].customerVPList.push_back(tempVP);

						tempVP.linkedNode=i;
						aliveNodes[j].providerVPList.push_back(tempVP);

					}

				}//end if

				else{

					if(DOMINANTDIRECTIONBILLING==false){

						tempVP.volume=linkValueVector[linkIndex[i][j].index];
						tempVP.contractPrice=aliveNodes[i].getContractPriceForProvider(j);

						aliveNodes[i].Vp+=linkValueVector[linkIndex[i][j].index];
						aliveNodes[j].Vc+=linkValueVector[linkIndex[i][j].index];

						tempVP.linkedNode=i;
						aliveNodes[j].customerVPList.push_back(tempVP);

						tempVP.linkedNode=j;
						aliveNodes[i].providerVPList.push_back(tempVP);

					}

					else{

						if(linkValueVectorUpstream[linkIndex[i][j].index]>linkValueVector[linkIndex[i][j].index])
							tempVP.volume=linkValueVectorUpstream[linkIndex[i][j].index];
						else
							tempVP.volume=linkValueVectorDownstream[linkIndex[i][j].index];

						tempVP.contractPrice=aliveNodes[i].getContractPriceForProvider(j);

						aliveNodes[i].Vp+=tempVP.volume;
						aliveNodes[j].Vc+=tempVP.volume;

						tempVP.linkedNode=i;
						aliveNodes[j].customerVPList.push_back(tempVP);

						tempVP.linkedNode=j;
						aliveNodes[i].providerVPList.push_back(tempVP);

					}

				}//end else

			}//end if for CPLink

			else if(linkIndex[i][j].linkClass==PPLink){	//ordinary peering link

				tempVP.volume=linkValueVector[linkIndex[i][j].index];

				aliveNodes[i].Vpp+=linkValueVector[linkIndex[i][j].index];
				aliveNodes[j].Vpp+=linkValueVector[linkIndex[i][j].index];

				tempVP.linkedNode=j;
				aliveNodes[i].freePeerVPList.push_back(tempVP);

				tempVP.linkedNode=i;
				aliveNodes[j].freePeerVPList.push_back(tempVP);

			}

		}//end if for index!=-1

	}//end for

	//}//end for

#if EXPERIMENT
	for(unsigned int i=0;i<Node::activeNodes;i++){

		aliveNodes[i].flowsObserved.sort();
		aliveNodes[i].flowsObservedAsym.sort();
		aliveNodes[i].flowsObserved.unique();
		aliveNodes[i].flowsObservedAsym.unique();
		aliveNodes[i].numFlows=aliveNodes[i].flowsObserved.size()+aliveNodes[i].flowsObservedAsym.size();

	}
#endif

}



