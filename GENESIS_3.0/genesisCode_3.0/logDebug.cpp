/*
 * logDebug.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: aemen
 */
#include "logDebug.h"

fstream logFile;
fstream initialNetworkLog;
fstream finalNetworkLog;
fstream snapshotFile;
fstream flowFile;

void printNode(const unsigned int& i,fstream& output){

	int numColocations=0;
	for(vector<bool>::iterator it=aliveNodes[i].colocated.begin();it!=aliveNodes[i].colocated.end();it++)
		if((*it)==true)
			numColocations++;

	output<<i<<":";
	output<<aliveNodes[i].fitness<<":";
	output<<aliveNodes[i].providerCost<<":"<<aliveNodes[i].freePeerCost<<":"<<aliveNodes[i].paidPeerCost<<":";
	output<<aliveNodes[i].customerRevenue<<":"<<aliveNodes[i].paidPeerRevenue<<":";
	output<<aliveNodes[i].numGPresence<<":";
	output<<numColocations<<":"<<aliveNodes[i].Q.size()<<":"<<aliveNodes[i].I.size()<<":"<<aliveNodes[i].J.size()<<":"<<aliveNodes[i].K.size()<<":";
	output<<aliveNodes[i].totalTrafficGenerated<<":"<<aliveNodes[i].totalTrafficConsumed<<"	"<<aliveNodes[i].V<<":";
	output<<aliveNodes[i].Vp<<":"<<aliveNodes[i].Vpp<<":"<<aliveNodes[i].Vc<<":"<<aliveNodes[i].Vt<<":";
	output<<aliveNodes[i].numFlows<<":";
	output<<aliveNodes[i].peeringStrategy;

}

void createLogFiles(fstream& ldf, fstream& inf, fstream& fnf, fstream& snapshotFile, fstream& fFile,long int popSeed, long int initTopSeed, long int plOrderSeed){

	char ldfName[100];
	char infName[100];
	char fnfName[100];
	char snapshotFileName[100];
	char flowFileName[100];

	sprintf(ldfName,"debugLog_%d_%d_%d.txt",static_cast<int>(popSeed),static_cast<int>(initTopSeed),static_cast<int>(plOrderSeed));
	sprintf(infName,"initialNetworkLog_%d_%d_0.txt",static_cast<int>(popSeed),static_cast<int>(initTopSeed));
	sprintf(fnfName,"finalNetworkLog_%d_%d_%d.txt",static_cast<int>(popSeed),static_cast<int>(initTopSeed),static_cast<int>(plOrderSeed));
	sprintf(snapshotFileName,"snapShot_%d_%d_%d.dot",static_cast<int>(popSeed),static_cast<int>(initTopSeed),static_cast<int>(plOrderSeed));
	sprintf(flowFileName,"flowLog_%d_%d_%d.txt",static_cast<int>(popSeed),static_cast<int>(initTopSeed),static_cast<int>(plOrderSeed));

	ldf.open(ldfName, ios::out);
	inf.open(infName, ios::out);
	fnf.open(fnfName, ios::out);
	snapshotFile.open(snapshotFileName,ios::out);
	fFile.open(flowFileName,ios::out);

}

void displayTrafficMatrix(){

        logFile<<endl<<endl<<"*********Traffic Matrix*********"<<endl<<endl;
        for(unsigned int i=0;i<Node::activeNodes;i++){
                for(unsigned int j=0;j<Node::activeNodes;j++){
                        logFile<<trafficObj.trafficMatrix[i][j]<<"\t";
                }
                logFile<<endl;
        }
        logFile<<endl;

        logFile<<"Flows: "<<endl;
        for(unsigned int i=0;i<(Node::activeNodes-1);i++){
                        for(unsigned int j=i+1;j<Node::activeNodes;j++){
                                logFile<<i<<","<<j<<": "<<trafficObj.trafficMatrix[i][j]+trafficObj.trafficMatrix[j][i]<<endl;
                        }
        }

}

void displayNodeData(){

	logFile<<endl<<endl<<"*********Node Data*********"<<endl<<endl;
	for(unsigned int i=0;i<Node::activeNodes;i++){
		logFile<<i<<":Locations:";
		for(list<unsigned int>::iterator it=aliveNodes[i].gPresence.begin();it!=aliveNodes[i].gPresence.end();it++)
			logFile<<*it<<"\t";
		logFile<<endl;

		logFile<<i<<":Prices:";
		for(list<unsigned int>::iterator it=aliveNodes[i].gPresence.begin();it!=aliveNodes[i].gPresence.end();it++)
			logFile<<aliveNodes[i].transitPriceChart[*it]<<"\t";
		logFile<<endl;

		logFile<<i<<":Colocated-Node-Price:";
		for(multimap<unsigned int,NodePrice>::iterator it=aliveNodes[i].colocatedNodePrice.begin();it!=aliveNodes[i].colocatedNodePrice.end();it++){
			logFile<<"("<<(*it).first<<","<<(*it).second.nId<<","<<(*it).second.price<<"),\t";
		}
		logFile<<endl;

		logFile<<i<<":Providers:";
		if(!aliveNodes[i].Q.empty()){
			for(list<NodePrice>::iterator it=aliveNodes[i].Q.begin();it!=aliveNodes[i].Q.end();it++){
				logFile<<"("<<(*it).nId<<","<<(*it).price<<")";
			}
		}
		logFile<<endl;

		logFile<<i<<":Customers:";
		if(!aliveNodes[i].I.empty()){
			for(list<NodePrice>::iterator it=aliveNodes[i].I.begin();it!=aliveNodes[i].I.end();it++){
				logFile<<"("<<(*it).nId<<","<<(*it).price<<")";
			}
		}
		logFile<<endl;

		logFile<<i<<":Peers:";
		if(!aliveNodes[i].K.empty()){
			for(list<NodePrice>::iterator it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++){
				logFile<<"("<<(*it).nId<<","<<(*it).price<<")";
			}
		}
		logFile<<endl;

		logFile<<i<<":CustomerCone:";
		if(!aliveNodes[i].J.empty()){
			for(list<NodePrice>::iterator it=aliveNodes[i].J.begin();it!=aliveNodes[i].J.end();it++){
				logFile<<"("<<(*it).nId<<","<<(*it).price<<")";
			}
		}
		logFile<<endl;

		logFile<<i<<":PeeringStrategy:";
		logFile<<aliveNodes[i].peeringStrategy;
		logFile<<endl;

		logFile<<i<<":Traffic:";
		logFile<<aliveNodes[i].Vo<<"\t"<<aliveNodes[i].Vp<<"\t"<<aliveNodes[i].Vc<<"\t"<<aliveNodes[i].Vpp<<"\t"<<aliveNodes[i].Vt<<"\t"<<aliveNodes[i].V;
		logFile<<endl;

		logFile<<i<<":Economics:";
		logFile<<aliveNodes[i].providerCost<<"\t"<<aliveNodes[i].customerRevenue<<"\t"<<aliveNodes[i].freePeerCost<<"\t"<<aliveNodes[i].paidPeerCost<<"\t"<<aliveNodes[i].paidPeerRevenue<<"\t"<<aliveNodes[i].fitness<<endl;
		logFile<<endl;

	}

}

void displayNodeData(unsigned int i){

	logFile<<i<<":Locations:";
	for(list<unsigned int>::iterator it=aliveNodes[i].gPresence.begin();it!=aliveNodes[i].gPresence.end();it++)
		logFile<<*it<<"\t";
	logFile<<endl;

	logFile<<i<<":Prices:";
	for(list<unsigned int>::iterator it=aliveNodes[i].gPresence.begin();it!=aliveNodes[i].gPresence.end();it++)
		logFile<<aliveNodes[i].transitPriceChart[*it]<<"\t";
	logFile<<endl;

	logFile<<i<<":Colocated-Node-Price:";
	for(multimap<unsigned int,NodePrice>::iterator it=aliveNodes[i].colocatedNodePrice.begin();it!=aliveNodes[i].colocatedNodePrice.end();it++){
		logFile<<"("<<(*it).first<<","<<(*it).second.nId<<","<<(*it).second.price<<"),\t";
	}
	logFile<<endl;

	logFile<<i<<":Providers:";
	if(!aliveNodes[i].Q.empty()){
		for(list<NodePrice>::iterator it=aliveNodes[i].Q.begin();it!=aliveNodes[i].Q.end();it++){
			logFile<<"("<<(*it).nId<<","<<(*it).price<<")";
		}
	}
	logFile<<endl;

	logFile<<i<<":Customers:";
	if(!aliveNodes[i].I.empty()){
		for(list<NodePrice>::iterator it=aliveNodes[i].I.begin();it!=aliveNodes[i].I.end();it++){
			logFile<<"("<<(*it).nId<<","<<(*it).price<<")";
		}
	}
	logFile<<endl;

	logFile<<i<<":Peers:";
	if(!aliveNodes[i].K.empty()){
		for(list<NodePrice>::iterator it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++){
			logFile<<"("<<(*it).nId<<","<<(*it).price<<")";
		}
	}
	logFile<<endl;

	logFile<<i<<":CustomerCone:";
	if(!aliveNodes[i].J.empty()){
		for(list<NodePrice>::iterator it=aliveNodes[i].J.begin();it!=aliveNodes[i].J.end();it++){
			logFile<<"("<<(*it).nId<<","<<(*it).price<<")";
		}
	}
	logFile<<endl;

	logFile<<i<<":PeeringStrategy:";
	logFile<<aliveNodes[i].peeringStrategy;
	logFile<<endl;

	logFile<<i<<":Traffic:";
	logFile<<aliveNodes[i].Vo<<"\t"<<aliveNodes[i].Vp<<"\t"<<aliveNodes[i].Vc<<"\t"<<aliveNodes[i].Vpp<<"\t"<<aliveNodes[i].Vt<<"\t"<<aliveNodes[i].V;
	logFile<<endl;

	logFile<<i<<":Economics:";
	logFile<<aliveNodes[i].providerCost<<"\t"<<aliveNodes[i].customerRevenue<<"\t"<<aliveNodes[i].freePeerCost<<"\t"<<aliveNodes[i].paidPeerCost<<"\t"<<aliveNodes[i].paidPeerRevenue<<"\t"<<aliveNodes[i].fitness<<endl;
	logFile<<endl;

}

void snapShot(){

	//use graphviz visualization tool
	snapshotFile<<"digraph G{"<<endl;


	snapshotFile<<"node [shape=circle];"<<endl;
	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(aliveNodes[i].I.empty()){
			snapshotFile<<" "<<"\""<<i<<"\"";
			//snapshotFile<<" "<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\"";
		}
	snapshotFile<<";"<<endl;

	snapshotFile<<"node [shape=doublecircle];"<<endl;
	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(!aliveNodes[i].I.empty()){
			snapshotFile<<" "<<"\""<<i<<"\"";
		}
	snapshotFile<<";"<<endl;

	//tier-1s
	for(unsigned int i=0;i<Node::activeNodes;i++)
		for(unsigned int j=i+1;j<Node::activeNodes;j++){
			if(aliveNodes[i].Q.empty() && aliveNodes[j].Q.empty()){
			//if(aliveNodes[i].Q.empty() && aliveNodes[j].Q.empty() && !aliveNodes[i].I.empty() && !aliveNodes[j].I.empty()){
				snapshotFile<<"\""<<i<<"\""<<" ";
				snapshotFile<<"-> ";
				snapshotFile<<"\""<<j<<"\""<<" ";
				snapshotFile<<"[arrowhead = none, color = red, weight = 4.0];"<<endl;
			}
		}

	//snapshotFile<<" node [shape = circle];"<<endl;
	//customer provider
	for(unsigned int i=0;i<Node::activeNodes;i++){
		if(!aliveNodes[i].Q.empty()){
			for(list<NodePrice>::iterator it=aliveNodes[i].Q.begin();it!=aliveNodes[i].Q.end();it++){
				snapshotFile<<"\""<<(*it).nId<<"\"";
				snapshotFile<<" -> ";
				snapshotFile<<"\""<<i<<"\"";
				snapshotFile<<"[dir=\"back\"];";
				snapshotFile<<endl;
			}
		}
	}

	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(!aliveNodes[i].K.empty()){
			for(list<NodePrice>::iterator it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++)
				if(i<(*it).nId){

					if(aliveNodes[i].Q.empty() && aliveNodes[(*it).nId].Q.empty()){}

					else{
						snapshotFile<<"\""<<i<<"\"";
						snapshotFile<<" -> ";
						snapshotFile<<"\""<<(*it).nId<<"\""<<" ";
						snapshotFile<<"[arrowhead = none, color = blue, weight = 2.0];"<<endl;
					}
				}
		}

	snapshotFile<<"}"<<endl;

}


void displayRouteData(){

	/*
	flowFile<<endl<<"LinkIndex: "<<endl;
	for(int c=0;c<Node::activeNodes;c++){
		for(int d=0;d<Node::activeNodes;d++){
			flowFile<<linkIndex[c][d].index<<","<<linkIndex[c][d].provider<<"\t";
		}
		flowFile<<endl;
	}
	*/

	flowFile<<endl<<"RoutingMatrix: "<<endl;

	list<flowInfo>::iterator it;
	for(unsigned int i=0;i<(Node::activeNodes-1);i++)
		for(unsigned int j=i+1;j<Node::activeNodes;j++){

			if(flowIndex[i][j]!=-1){

				if(flowDirectionFrom[flowIndex[i][j]]==i){

					flowFile<<"Flow "<<i<<" -> "<<j<<": ";
					for(it=routingMatrix[flowIndex[i][j]].begin();it!=routingMatrix[flowIndex[i][j]].end();it++){

						for(unsigned int p=0;p<(Node::activeNodes-1);p++)
							for(unsigned int q=p+1;q<Node::activeNodes;q++)
								if(p!=q && linkIndex[p][q].index==(*it).linkId){
									flowFile<<p<<"-"<<q;
									if((*it).flowDirection==UPSTREAM){
										flowFile<<" UPSTREAM + ";
									}
									else{
										flowFile<<" DOWNSTREAM + ";
									}
								}

					}
					flowFile<<endl;

					flowFile<<"Flow "<<j<<" -> "<<i<<": ";
					for(it=routingMatrixAsym[flowIndex[i][j]].begin();it!=routingMatrixAsym[flowIndex[i][j]].end();it++){

						for(unsigned int p=0;p<(Node::activeNodes-1);p++)
							for(unsigned int q=p+1;q<Node::activeNodes;q++)
								if(p!=q && linkIndex[p][q].index==(*it).linkId){
									flowFile<<p<<"-"<<q;
									if((*it).flowDirection==UPSTREAM){
										flowFile<<" UPSTREAM + ";
									}
									else{
										flowFile<<" DOWNSTREAM + ";
									}
								}
					}
					flowFile<<endl;

				}

				else{

					flowFile<<"Flow "<<i<<" -> "<<j<<": ";
					for(it=routingMatrixAsym[flowIndex[i][j]].begin();it!=routingMatrixAsym[flowIndex[i][j]].end();it++){

						for(unsigned int p=0;p<(Node::activeNodes-1);p++)
							for(unsigned int q=p+1;q<Node::activeNodes;q++)
								if(p!=q && linkIndex[p][q].index==(*it).linkId){
									flowFile<<p<<"-"<<q;
									if((*it).flowDirection==UPSTREAM){
										flowFile<<" UPSTREAM + ";
									}
									else{
										flowFile<<" DOWNSTREAM + ";
									}
								}

					}
					flowFile<<endl;

					flowFile<<"Flow "<<j<<" -> "<<i<<": ";
					for(it=routingMatrix[flowIndex[i][j]].begin();it!=routingMatrix[flowIndex[i][j]].end();it++){

						for(unsigned int p=0;p<(Node::activeNodes-1);p++)
							for(unsigned int q=p+1;q<Node::activeNodes;q++)
								if(p!=q && linkIndex[p][q].index==(*it).linkId){
									flowFile<<p<<"-"<<q;
									if((*it).flowDirection==UPSTREAM){
										flowFile<<" UPSTREAM + ";
									}
									else{
										flowFile<<" DOWNSTREAM + ";
									}
								}

					}
					flowFile<<endl;

				}

			}

		}


}

