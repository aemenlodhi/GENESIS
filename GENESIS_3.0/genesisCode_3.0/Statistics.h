///*
// * Statistics.h
// *
// *  Created on: Jan 5, 2010
// *      Author: alodhi3
// */
//
//#ifndef STATISTICS_H_
//#define STATISTICS_H_
//
////#include "NetSim.h"
////#include "globalVars.h"
//
//
//
//void antiCoalitionMetric(int numSimulations){
//
//	if(numSimulations==0)
//		return;
//
//	ofstream antiCoalitionFile1;
//	antiCoalitionFile1.open("antiCoalition1.txt",ios::out|ios::app);
//
//	ofstream antiCoalitionFile2;
//	antiCoalitionFile2.open("antiCoalition2.txt",ios::out|ios::app);
//
//	double rai=0;
//	double raj=0;
//	double rpi=0;
//	double rpj=0;
//	list<int>::iterator it1;
//	list<int>::iterator it2;
//	list<double>::iterator itD;
//	list<double> ratios1;
//	list<double> ratios2;
//	double temp;
//
//	for(int i=0;i<activeNodes-1;i++)
//		for(int j=i+1;j<activeNodes;j++){
//			if(!aliveNodes[i].I.empty() && !aliveNodes[j].I.empty() && aliveNodes[i].isPeer(j)){
//
//				rai=rpi=raj=rpj=0;
//
//				for(it1=aliveNodes[i].overLap.begin();it1!=aliveNodes[i].overLap.end();it1++){
//					if(aliveNodes[j].isImmediateCustomer(*it1)){
//						rpi++;
//						if(aliveNodes[i].isPeer(*it1))
//							rai++;
//					}
//				}
//
//				for(it1=aliveNodes[j].overLap.begin();it1!=aliveNodes[j].overLap.end();it1++){
//					if(aliveNodes[i].isImmediateCustomer(*it1)){
//						rpj++;
//						if(aliveNodes[j].isPeer(*it1))
//							raj++;
//					}
//				}
//
//				if((rpi+rpj)>0){
//
//					ratios1.push_back((rai+raj)/(rpi+rpj));
//
//
//				}
//
//			}
//		}
//
//	ratios1.sort();
//	double x, xPrev;
//	double xCounter, prevCounter;
//
//	for(itD=ratios1.begin();itD!=ratios1.end();itD++){
//
//		x=*itD;
//
//		if(itD==ratios1.begin()){
//
//			xPrev=*itD;
//			prevCounter=0;
//			xCounter=1;
//		}
//
//		else{
//
//			if(x==xPrev){
//				xCounter++;
//			}
//
//			else{
//				xCounter+=prevCounter;
//
//				if(numSimulations==1){
//					//antiCoalitionFile1<<xPrev<<"\t"<<xCounter/ratios1.size()<<endl;
//					antiCoalitionFile1<<xCounter/ratios1.size()<<"\t"<<xPrev<<endl;
//				}
//				else{
//					//antiCoalitionFile2<<xPrev<<"\t"<<xCounter/ratios1.size()<<endl;
//					antiCoalitionFile2<<xCounter/ratios1.size()<<"\t"<<xPrev<<endl;
//
//				}
//
//				xPrev=*itD;
//				prevCounter=xCounter;
//				xCounter=1;
//
//			}
//
//		}
//
//	}
//
//	xCounter+=prevCounter;
//	if(numSimulations==1){
//		//antiCoalitionFile1<<xPrev<<"\t"<<xCounter/ratios1.size()<<endl;
//		antiCoalitionFile1<<xCounter/ratios1.size()<<"\t"<<xPrev<<endl;
//	}
//	else{
//		//antiCoalitionFile2<<xPrev<<"\t"<<xCounter/ratios1.size()<<endl;
//		antiCoalitionFile2<<xCounter/ratios1.size()<<"\t"<<xPrev<<endl;
//
//	}
//
//	/*
//	ratios1.sort(sortReverse);
//	ratios2.push_back(ratios1.front());
//	temp=ratios1.front();
//
//	for(itD=ratios1.begin();itD!=ratios1.end();itD++){
//
//		if(itD!=ratios1.begin()){
//			temp+=*itD;
//			ratios2.push_back(temp);
//		}
//
//	}
//
//	temp=ratios2.back();
//	cout<<"temp is "<<temp<<endl;
//
//	for(itD=ratios2.begin();itD!=ratios2.end();itD++){
//
//			*itD=*itD/temp;
//			if(numSimulations==1){
//				antiCoalitionFile1<<*itD<<":";
//			}
//			else
//				antiCoalitionFile2<<*itD<<":";
//
//	}
//	*/
//
//}
//
//void printLog(int numSimulations){
//
//	ofstream printLogFile;
//	char printLogFileName[50];
//	sprintf(printLogFileName,"printLog_%d.txt",playOrderSeed);
//	printLogFile.open(printLogFileName,ios::out | ios::app);
//
//	ofstream printProviderFile;
//	char printProviderFileName[50];
//	sprintf(printProviderFileName,"printProvider_%d.txt",playOrderSeed);
//	printProviderFile.open(printProviderFileName,ios::out | ios::app);
//
//	int cheapestInRegions=0;
//	Coordinate presence;
//	list<Coordinate>::iterator itC;
//	list<int>::iterator itInt;
//	list<int>::iterator itInt2;
//	int lowestPriceNode;
//	double lowestPrice=100000;
//
//	int numCPCustomers=0;
//	int numCCCustomers=0;
//	int numProviderPeers=0;
//	int numCPPeers=0;
//	int numCCPeers=0;
//	int numStubPeers=0;
//	int numPotentialPeers=0;
//	int numPotentialProviderPeers=0;
//	int numPotentialCPCCPeers=0;
//	int numPotentialStubPeers=0;
//	int peerCustomerProductAgainst=0;
//	int peerCustomerProduct=0;
//	double trafficStolenFrom=0;
//	double trafficStolenBy=0;
//	double totalUpstreamTraffic=0;
//	double totalPeeringTraffic=0;
//	double totalPeers=0;
//	double totalOpenPeers=0;
//	int potentialCustomers=0;
//
//	for(int i=0;i<activeNodes;i++){
//
//		totalUpstreamTraffic=0;
//		totalPeeringTraffic=0;
//		cheapestInRegions=0;
//		numCPCustomers=0;
//		numCCCustomers=0;
//		numCPPeers=0;
//		numCCPeers=0;
//		numProviderPeers=0;
//		numStubPeers=0;
//
//		numPotentialPeers=0;
//		numPotentialProviderPeers=0;
//		numPotentialCPCCPeers=0;
//		numPotentialStubPeers=0;
//		peerCustomerProductAgainst=0;
//		peerCustomerProduct=0;
//
//		trafficStolenFrom=0;
//		trafficStolenBy=0;
//		totalPeers=0;
//		totalOpenPeers=0;
//		potentialCustomers=0;
//
//		for(itInt=aliveNodes[i].overLap.begin();itInt!=aliveNodes[i].overLap.end();itInt++){
//
//			if(aliveNodes[*itInt].numGPresence<=aliveNodes[i].numGPresence)
//				potentialCustomers++;
//
//			if(!aliveNodes[i].isImmediateCustomer(*itInt) && aliveNodes[i].Q!=*itInt){
//				numPotentialPeers++;
//
//				if(!aliveNodes[*itInt].I.empty())
//					numPotentialProviderPeers++;
//
//				if(aliveNodes[*itInt].isMajorContentNet==true)
//					numPotentialCPCCPeers++;
//
//				else{
//
//					if(aliveNodes[*itInt].I.empty())
//						numPotentialStubPeers++;
//
//				}
//
//			}
//		}
//
//		for(itC=aliveNodes[i].gPresence.begin();itC!=aliveNodes[i].gPresence.end();itC++){
//
//			lowestPrice=100000;
//
//			for(itInt=geography[(*itC).xCoordinate][(*itC).yCoordinate].nodePresent.begin();itInt!=geography[(*itC).xCoordinate][(*itC).yCoordinate].nodePresent.end();itInt++)
//				if(aliveNodes[*itInt].numGPresence>1 && aliveNodes[*itInt].priceChart[(*itC).xCoordinate][(*itC).yCoordinate]<lowestPrice){
//					lowestPrice=aliveNodes[*itInt].priceChart[(*itC).xCoordinate][(*itC).yCoordinate];
//					lowestPriceNode=*itInt;
//				}
//
//			if(lowestPriceNode==i)
//				cheapestInRegions++;
//		}
//
//		for(itInt=aliveNodes[i].I.begin();itInt!=aliveNodes[i].I.end();itInt++){
//
//			if(aliveNodes[*itInt].isCP==true)
//				numCPCustomers++;
//
//			if(aliveNodes[*itInt].isCC==true)
//				numCCCustomers++;
//
//		}
//
//		for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++){
//
//			if(aliveNodes[*itInt].isCP==true)
//				numCPPeers++;
//
//			if(aliveNodes[*itInt].isCC==true)
//				numCCPeers++;
//
//			if(!aliveNodes[*itInt].I.empty())
//				numProviderPeers++;
//
//			if(aliveNodes[*itInt].I.empty() && aliveNodes[*itInt].isMajorContentNet==false)
//				numStubPeers++;
//
//		}
//
//		printLogFile<<numSimulations<<":";
//		printLogFile<<i<<":"<<aliveNodes[i].numGPresence<<":"<<cheapestInRegions<<":";
//		printLogFile<<aliveNodes[i].trafficGenerated<<":"<<aliveNodes[i].trafficConsumed<<":"<<aliveNodes[i].Vt<<":";
//		printLogFile<<aliveNodes[i].isCP<<":"<<aliveNodes[i].isCC<<":";
//		printLogFile<<aliveNodes[i].I.size()<<":"<<aliveNodes[i].J.size()<<":";
//		printLogFile<<numCPCustomers<<":"<<numCCCustomers<<":";
//		printLogFile<<aliveNodes[i].Q<<":";
//		printLogFile<<numPotentialPeers<<":"<<numPotentialCPCCPeers<<":"<<numPotentialProviderPeers<<":"<<numPotentialStubPeers<<":";
//		printLogFile<<aliveNodes[i].peeringStrategyNumber<<":"<<aliveNodes[i].K.size()<<":";
//		printLogFile<<numCPPeers<<":"<<numCCPeers<<":"<<numProviderPeers<<":"<<numStubPeers<<":";
//		printLogFile<<aliveNodes[i].providerCost<<":"<<aliveNodes[i].peerCost<<":"<<aliveNodes[i].customerRevenue<<":"<<aliveNodes[i].fitness<<endl;
//
//
//		if(!aliveNodes[i].I.empty()){
//
//			if(aliveNodes[i].Q!=-1){
//				aliveNodes[i].actualTrafficFractions[0]=linkValueVector[linkIndex[i][aliveNodes[i].Q].index]/aliveNodes[i].V;
//				totalUpstreamTraffic+=linkValueVector[linkIndex[i][aliveNodes[i].Q].index];
//			}
//			else
//				aliveNodes[i].actualTrafficFractions[0]=0;
//
//			aliveNodes[i].actualTrafficFractions[1]=0;
//			for(itInt=aliveNodes[i].I.begin();itInt!=aliveNodes[i].I.end();itInt++)
//				aliveNodes[i].actualTrafficFractions[1]+=linkValueVector[linkIndex[i][*itInt].index];
//			aliveNodes[i].actualTrafficFractions[1]=aliveNodes[i].actualTrafficFractions[1]/aliveNodes[i].V;
//
//			aliveNodes[i].actualTrafficFractions[2]=0;
//			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++)
//				aliveNodes[i].actualTrafficFractions[2]+=linkValueVector[linkIndex[i][*itInt].index];
//			aliveNodes[i].actualTrafficFractions[2]=aliveNodes[i].actualTrafficFractions[2]/aliveNodes[i].V;
//
//			totalPeers=aliveNodes[i].K.size();
//			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++){
//
//				if(aliveNodes[*itInt].peeringStrategyNumber==1)
//					totalOpenPeers++;
//
//				totalUpstreamTraffic+=linkValueVector[linkIndex[i][*itInt].index];
//				totalPeeringTraffic+=linkValueVector[linkIndex[i][*itInt].index];
//
//				if(!aliveNodes[*itInt].I.empty()){
//					for(itInt2=aliveNodes[*itInt].K.begin();itInt2!=aliveNodes[*itInt].K.end();itInt2++){
//						if(aliveNodes[*itInt].isImmediateCustomerOfPeer(*itInt2)==i){
//							peerCustomerProductAgainst++;
//							trafficStolenFrom+=linkValueVector[linkIndex[*itInt][*itInt2].index];
//						}
//					}
//				}
//
//				if(aliveNodes[i].isImmediateCustomerOfPeer(*itInt)!=-1){
//					peerCustomerProduct++;
//					trafficStolenBy+=linkValueVector[linkIndex[i][*itInt].index];
//				}
//			}
//
//
//			printProviderFile<<numSimulations<<":";
//			printProviderFile<<i<<":"<<aliveNodes[i].numGPresence<<":"<<cheapestInRegions<<":";
//			printProviderFile<<aliveNodes[i].trafficGenerated<<":"<<aliveNodes[i].trafficConsumed<<":"<<aliveNodes[i].Vt<<":"<<aliveNodes[i].V<<":";
//			printProviderFile<<aliveNodes[i].isCP<<":"<<aliveNodes[i].isCC<<":";
//			printProviderFile<<aliveNodes[i].I.size()<<":"<<aliveNodes[i].J.size()<<":";
//			printProviderFile<<numCPCustomers<<":"<<numCCCustomers<<":";
//			printProviderFile<<aliveNodes[i].Q<<":";
//			printProviderFile<<numPotentialPeers<<":"<<numPotentialCPCCPeers<<":"<<numPotentialProviderPeers<<":"<<numPotentialStubPeers<<":";
//			printProviderFile<<aliveNodes[i].peeringStrategyNumber<<":"<<aliveNodes[i].K.size()<<":";
//			printProviderFile<<numCPPeers<<":"<<numCCPeers<<":"<<numProviderPeers<<":"<<numStubPeers<<":";
//			printProviderFile<<aliveNodes[i].providerCost<<":"<<aliveNodes[i].peerCost<<":"<<aliveNodes[i].customerRevenue<<":"<<aliveNodes[i].fitness<<":";
//
//
//			for(int j=0;j<3;j++)
//				for(int k=0;k<3;k++)
//					printProviderFile<<trafficFractions[i][j][k]<<":";
//
//			for(int k=0;k<3;k++)
//				printProviderFile<<aliveNodes[i].actualTrafficFractions[k]<<":";
//
//			printProviderFile<<peerCustomerProductAgainst<<":"<<peerCustomerProduct<<":";
//
//			printProviderFile<<trafficStolenFrom<<":"<<trafficStolenBy<<":";
//
//			for(itInt=aliveNodes[i].I.begin();itInt!=aliveNodes[i].I.end();itInt++)
//				printProviderFile<<*itInt<<",";
//			printProviderFile<<":";
//			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++)
//				printProviderFile<<*itInt<<",";
//			printProviderFile<<":";
//
//			if(totalUpstreamTraffic!=0)
//				printProviderFile<<totalPeeringTraffic/totalUpstreamTraffic<<":";
//			else
//				printProviderFile<<"0:";
//
//			if(totalPeers!=0)
//				printProviderFile<<totalOpenPeers/totalPeers<<":";
//			else
//				printProviderFile<<"0:";
//
//			printProviderFile<<aliveNodes[i].overLap.size()<<":"<<potentialCustomers<<":";
//
//			printProviderFile<<endl;
//
//
//		}
//	}
//
//	//antiCoalitionMetric(numSimulations);
//
//}
//
//void snapShot(int numSimulations){
//
//
//	snapshotFile<<endl<<endl<<"****** Simulation "<<numSimulations<<" ******"<<endl<<endl;
//	snapshotFile<<"digraph G{"<<endl;
//
//
//	snapshotFile<<"node [shape=circle];"<<endl;
//	for(int i=0;i<activeNodes;i++)
//		if(aliveNodes[i].Q!=-1 && !aliveNodes[i].I.empty()){
//			snapshotFile<<" "<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\"";
//		}
//	snapshotFile<<";"<<endl;
//
//
//	snapshotFile<<"node [shape=doublecircle];"<<endl;
//	for(int i=0;i<activeNodes;i++)
//		if(aliveNodes[i].Q==-1 && !aliveNodes[i].I.empty()){
//			snapshotFile<<" "<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\"";
//		}
//	snapshotFile<<";"<<endl;
//
//	for(int i=0;i<activeNodes;i++)
//		for(int j=i+1;j<activeNodes;j++){
//			if(aliveNodes[i].Q==-1 && aliveNodes[j].Q==-1 && !aliveNodes[i].I.empty() && !aliveNodes[j].I.empty()){
//				snapshotFile<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\""<<" ";
//				snapshotFile<<"-> ";
//				snapshotFile<<"\""<<j<<"_"<<aliveNodes[j].numGPresence<<"_"<<aliveNodes[j].fitness<<"_"<<aliveNodes[j].peeringStrategyNumber<<"\""<<" ";
//				snapshotFile<<"[arrowhead = none, color = red, weight = 4.0];"<<endl;
//			}
//		}
//
//	//snapshotFile<<" node [shape = circle];"<<endl;
//
//	for(int i=0;i<activeNodes;i++){
//		if(aliveNodes[i].Q!=-1 && !aliveNodes[i].I.empty()){
//			snapshotFile<<"\""<<aliveNodes[i].Q<<"_"<<aliveNodes[aliveNodes[i].Q].numGPresence<<"_"<<aliveNodes[aliveNodes[i].Q].fitness<<"_"<<aliveNodes[aliveNodes[i].Q].peeringStrategyNumber<<"\"";
//			snapshotFile<<" -> ";
//			snapshotFile<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\"";
//			snapshotFile<<"[dir=\"back\"];";
//			snapshotFile<<endl;
//		}
//	}
//
//	list<int>::iterator it;
//	for(int i=0;i<activeNodes;i++)
//		if(!aliveNodes[i].K.empty() && !aliveNodes[i].I.empty()){
//			for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++)
//				if(i<*it && !aliveNodes[*it].I.empty()){
//
//					if(aliveNodes[i].Q==-1 && aliveNodes[*it].Q==-1){}
//
//					else{
//						snapshotFile<<"\""<<i<<"_"<<aliveNodes[i].numGPresence<<"_"<<aliveNodes[i].fitness<<"_"<<aliveNodes[i].peeringStrategyNumber<<"\"";
//						snapshotFile<<" -> ";
//						snapshotFile<<"\""<<*it<<"_"<<aliveNodes[*it].numGPresence<<"_"<<aliveNodes[*it].fitness<<"_"<<aliveNodes[*it].peeringStrategyNumber<<"\""<<" ";
//						snapshotFile<<"[arrowhead = none, color = blue, weight = 2.0];"<<endl;
//					}
//				}
//		}
//
//	snapshotFile<<"}"<<endl;
//
//}
//
//
//void displayRouteData(){
//
//	logFile<<endl<<"LinkIndex: "<<endl;
//	for(int c=0;c<activeNodes;c++){
//		for(int d=0;d<activeNodes;d++){
//			logFile<<linkIndex[c][d].index<<","<<linkIndex[c][d].provider<<"\t";
//		}
//		logFile<<endl;
//	}
//
//	logFile<<endl<<"RoutingMatrix: "<<endl;
//
//	list<int>::iterator it;
//	for(int i=0;i<(activeNodes-1);i++)
//		for(int j=i+1;j<activeNodes;j++){
//
//			if(flowIndex[i][j]!=-1){
//				logFile<<"Flow "<<i<<" <-> "<<j<<": ";
//
//				for(it=routingMatrixScale[flowIndex[i][j]].begin();it!=routingMatrixScale[flowIndex[i][j]].end();it++){
//
//					for(int p=0;p<(activeNodes-1);p++)
//						for(int q=p+1;q<activeNodes;q++)
//							if(p!=q && linkIndex[p][q].index==*it)
//								logFile<<p<<"-"<<q<<" + ";
//
//				}
//
//				logFile<<endl;
//			}
//		}
//
//	logFile<<endl<<"RoutingMatrix Asymmetric: "<<endl;
//
//	for(int i=0;i<(activeNodes-1);i++)
//		for(int j=i+1;j<activeNodes;j++){
//
//			if(flowIndex[i][j]!=-1){
//				logFile<<"Flow "<<i<<" <-> "<<j<<": ";
//
//				for(it=routingMatrixScaleAsym[flowIndex[i][j]].begin();it!=routingMatrixScaleAsym[flowIndex[i][j]].end();it++){
//
//					for(int p=0;p<(activeNodes-1);p++)
//						for(int q=p+1;q<activeNodes;q++)
//							if(p!=q && linkIndex[p][q].index==*it)
//								logFile<<p<<"-"<<q<<" + ";
//
//
//				}
//
//				logFile<<endl;
//			}
//		}
//
//}
//
//void displayTopology(){
//
//	list<int>::iterator itInt;
//	logFile<<"Tier1: ";
//	for(itInt=Tier1.begin();itInt!=Tier1.end();itInt++){
//		logFile<<*itInt<<" ";
//	}
//
//	logFile<<endl;
//
//	for(int b=0;b<activeNodes;b++){
//
//		if(aliveNodes[b].lifeStatus==alive){
//			logFile<<"Status for "<<b<<endl;
//			logFile<<"Q: "<<aliveNodes[b].Q<<endl;
//			logFile<<"I: ";
//			for(itInt=aliveNodes[b].I.begin();itInt!=aliveNodes[b].I.end();itInt++)
//				logFile<<*itInt<<" ";
//			logFile<<endl<<"J: ";
//			for(itInt=aliveNodes[b].J.begin();itInt!=aliveNodes[b].J.end();itInt++)
//				logFile<<*itInt<<" ";
//			logFile<<endl<<"K: ";
//			for(itInt=aliveNodes[b].K.begin();itInt!=aliveNodes[b].K.end();itInt++)
//				logFile<<*itInt<<" ";
//			logFile<<endl;
//		}
//
//	}
//
//}
//
//void recordStrategyDistribution2(int numSims){
//
//	ofstream sFile;
//	char sFileName[50];
//	sprintf(sFileName,"strategyDistribution_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
//	sFile.open(sFileName,ios::out|ios::app);
//
//	double strategyDistribution[5]={0};
//	double numProviders=0;
//
//
//	for(int i=0;i<activeNodes;i++)
//		if(!aliveNodes[i].I.empty()){
//			numProviders++;
//			strategyDistribution[aliveNodes[i].peeringStrategyNumber]++;
//		}
//
//	for(int i=0;i<5;i++){
//		strategyDistribution[i]=(strategyDistribution[i]*100)/numProviders;
//		sFile<<i<<"\t"<<strategyDistribution[i]<<endl;
//	}
//
//}
//
//void recordBetweennessCentralityDistribution(int numSims){
//
//	list<int> transitNodes;
//	list<int>::iterator it;
//	list<double>::iterator itD;
//
//	double transitCounter[500]={0};
//	double totalTransits=0;
//	list<double> betweennessDistribution;
//
//
//	for(int i=0;i<(activeNodes-1);i++)
//		for(int j=i+1;j<activeNodes;j++){
//			if(linkIndex[i][j].index==-1){
//				transitNodes.clear();
//				totalTransits++;
//				for(it=routingMatrixScale[flowIndex[i][j]].begin();it!=routingMatrixScale[flowIndex[i][j]].end();it++){
//
//						for(int x=0;x<(activeNodes-1);x++)
//							for(int y=x+1;y<activeNodes;y++){
//								if(linkIndex[x][y].index==*it){
//									if(x!=i && x!=j && !isPresentInList(transitNodes,x))
//										transitNodes.push_back(x);
//									if(y!=i && y!=j && !isPresentInList(transitNodes,y))
//										transitNodes.push_back(y);
//
//									break;
//								}//end if
//							}//end for
//
//				}//end for
//
//				for(it=transitNodes.begin();it!=transitNodes.end();it++){
//					transitCounter[*it]++;
//				}
//
//				transitNodes.clear();
//				totalTransits++;
//				for(it=routingMatrixScaleAsym[flowIndex[i][j]].begin();it!=routingMatrixScaleAsym[flowIndex[i][j]].end();it++){
//
//					for(int x=0;x<(activeNodes-1);x++)
//						for(int y=x+1;y<activeNodes;y++){
//							if(linkIndex[x][y].index==*it){
//								if(x!=i && x!=j && !isPresentInList(transitNodes,x))
//									transitNodes.push_back(x);
//								if(y!=i && y!=j && !isPresentInList(transitNodes,y))
//									transitNodes.push_back(y);
//
//								break;
//							}//end if
//						}//end for
//
//				}//end for
//
//				for(it=transitNodes.begin();it!=transitNodes.end();it++){
//					transitCounter[*it]++;
//				}
//
//			}//end if
//		}//end for
//
//	for(int i=0;i<activeNodes;i++){
//		transitCounter[i]=transitCounter[i]/totalTransits;
//		if(transitCounter[i]>0){
//			betweennessDistribution.push_back(transitCounter[i]);
//		}
//	}
//
//	betweennessDistribution.sort();
//
//	ofstream bdFile;
//	char bdFileName[50];
//	sprintf(bdFileName,"betweennessCentralityDistribution_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
//	bdFile.open(bdFileName,ios::out|ios::app);
//
//	ofstream bFile;
//	char bFileName[50];
//	sprintf(bFileName,"betweennessCentrality_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
//	bFile.open(bFileName,ios::out|ios::app);
//
//	for(int i=0;i<activeNodes;i++){
//		if(transitCounter[i]>0){
//
//			if(aliveNodes[i].Q==-1)
//				bFile<<i<<"\t"<<"1\t"<<transitCounter[i]<<endl;
//			else if(aliveNodes[aliveNodes[i].Q].Q==-1)
//				bFile<<i<<"\t"<<"2\t"<<transitCounter[i]<<endl;
//			else
//				bFile<<i<<"\t"<<"3\t"<<transitCounter[i]<<endl;
//
//		}
//	}
//
//
//	double counter=1;
//	double frac;
//	for(itD=betweennessDistribution.begin();itD!=betweennessDistribution.end();itD++,counter++){
//		frac=counter/betweennessDistribution.size();
//		bdFile<<frac<<"\t"<<*itD<<endl;
//	}
//}
//
//void recordJaccardLog(int numSims){
//
//	ofstream jFile;
//	char fileName[50];
//	sprintf(fileName,"jaccardLog_%d_%d_%d_%d.txt",mySeed,initialTopologySeed,playOrderSeed,numSims);
//	jFile.open(fileName);
//	int linkType;
//
//	for(int i=0;i<(activeNodes-1);i++)
//		for(int j=i+1;j<activeNodes;j++){
//
//			if(!aliveNodes[i].I.empty() && !aliveNodes[j].I.empty()){
//				if(linkIndex[i][j].index!=-1){
//
//					linkType=linkIndex[i][j].linkClass;
//
//					if(linkType==1)
//						jFile<<i<<"\t"<<j<<"\t"<<linkType<<endl;
//
//					else{
//						if(aliveNodes[i].Q==j)
//							jFile<<i<<"\t"<<j<<"\t"<<"2"<<endl;
//						else
//							jFile<<i<<"\t"<<j<<"\t"<<"3"<<endl;
//
//					}
//				}
//			}
//		}
//}
//
//void displayTrafficMatrix(){
//
//	//cout<<endl<<"Traffic Matrix: "<<endl;
//	for(int i=0;i<activeNodes;i++){
//		for(int j=0;j<activeNodes;j++){
//			//cout<<trafficMatrix[i][j]<<"\t";
//		}
//		//cout<<endl;
//	}
//	//cout<<endl;
//
//	logFile<<endl<<"Traffic Matrix: "<<endl;
//	for(int i=0;i<activeNodes;i++){
//		for(int j=0;j<activeNodes;j++){
//			logFile<<trafficMatrix[i][j]<<"\t";
//		}
//		logFile<<endl;
//	}
//	logFile<<endl;
//
//	logFile<<"Flows: "<<endl;
//	for(int i=0;i<(activeNodes-1);i++){
//			for(int j=i+1;j<activeNodes;j++){
//				logFile<<i<<","<<j<<": "<<trafficMatrix[i][j]+trafficMatrix[j][i]<<endl;
//			}
//	}
//
//}
//
//void printTopologyStats(){
//
//	ofstream idFile;
//	idFile.open("topologyStats.txt",ios::out | ios::app);
//
//	idFile<<numSimulations<<"\t";
//
//	//idFile<<"Providers\t";
//	for(int i=0;i<1;i++)
//		idFile<<numProviders[i]<<"\t";
//
//	//idFile<<endl;
//
//	//idFile<<"CP/CC\t";
//	for(int i=0;i<1;i++)
//		idFile<<numCPCC[i]<<"\t";
//
//	//idFile<<endl;
//
//	//idFile<<"T1\t";
//	for(int i=0;i<1;i++)
//		idFile<<numT1[i]<<"\t";
//
//	//idFile<<endl;
//
//	//idFile<<"Tree Height\t";
//	for(int i=0;i<1;i++)
//		idFile<<treeHeight[i]<<"\t";
//
//	//idFile<<endl;
//
//	//idFile<<"Diameter\t";
//	for(int i=0;i<1;i++)
//		idFile<<networkDiameter[i]<<"\t";
//
//	//idFile<<endl;
//
//
//	//idFile<<"Avg. Weighted Path Length\t";
//	for(int i=0;i<1;i++)
//		idFile<<avgWeightedPathLength[i]<<"\t";
//
//	//idFile<<endl;
//
//
//	//idFile<<"Avg. Path Length\t";
//	for(int i=0;i<1;i++)
//		idFile<<avgPlainPathLength[i]<<"\t";
//	//idFile<<endl;
//	//additions
//
//	//idFile<<"Link Density\t";
//	for(int i=0;i<1;i++)
//		idFile<<linkDensity[i]<<"\t";
//
////	idFile<<endl;
//
//	//idFile<<"Peering Only Traffic %age\t";
//	for(int i=0;i<1;i++)
//		idFile<<peeringTrafficOnly[i]<<"\t";
//
//	//idFile<<endl;
//
//	//idFile<<"Peering Clustering Coefficient\t";
//	for(int i=0;i<1;i++)
//		idFile<<ppClusteringCoefficient[i]<<"\t";
//
//	//idFile<<endl;
//
//	//idFile<<"T1 NT1 transit ratio\t";
//	for(int i=0;i<1;i++)
//		idFile<<t1Nt1TransitRatio[i]<<"\t";
//
//	//idFile<<endl;
//
//	//idFile<<"Wealthiest ID\t";
//	for(int i=0;i<1;i++)
//		idFile<<wealthiestId[i]<<"\t";
//	//idFile<<endl;
//
//	//idFile<<"Max Wealth\t";
//	for(int i=0;i<1;i++)
//		idFile<<maxWealth[i]<<"\t";
//
//
//	for(int i=0;i<1;i++)
//		idFile<<numT2[i]<<"\t";
//
//	for(int i=0;i<1;i++)
//		idFile<<numT3[i]<<"\t";
//
//	idFile<<endl;
//
//
//}
//
//
//void measureTopologicalMetrics(int numSimulations){
//
//	int diameter=0;
//	double avgPathLength=0;
//	int numPaths=0;
//	int numStubs=0;
//	static int numTotalPossibleLinks=0;
//	int totalLinks=0;
//	int numCPLinks=0;
//	int numPPLinks=0;
//	double density=0;
//	double transitTrafficT1=0;
//	double transitTrafficNonT1=0;
//	double t1TransitTrafficRatio=0;
//	list<int>::iterator itInt;
//	double peeringTraffic;
//	double t1PeeringTraffic;
//	double peeringClusteringCoefficient[500]={0};
//	double networkPeeringClusteringCoefficient=0;
//	list<int>::iterator it1;
//	list<int>::iterator it2;
//	double t1VtFraction;
//	double nt1VtFraction;
//	int maxTreeHeight=0;
//	int maxCustomerConeSize=0;
//	int minCustomerConeSize=activeNodes+1;
//	list<int> degreeDistribution;
//	double temp=0;
//	double totalTraffic=0;
//	unsigned int numLinks=0;
//	double plainPath=0;
//
//	double betweennessCentrality[500]={0};
//	double totalPaths=0;
//
//	/*
//	for(int i=0;i<(activeNodes-1);i++){
//		for(int j=i+1;j<activeNodes;j++){
//
//		}
//	}
//	*/
//
//	for(int i=0;i<activeNodes;i++){
//		if(!aliveNodes[i].I.empty()){
//			numProviders[numSimulations]++;
//
//			if(aliveNodes[i].Q==-1){
//				numT1[numSimulations]++;
//				t1VtFraction+=aliveNodes[i].Vt;
//			}
//
//			else{
//				nt1VtFraction+=aliveNodes[i].Vt;
//
//				if(aliveNodes[aliveNodes[i].Q].Q==-1)
//					numT2[numSimulations]++;
//				else
//					numT3[numSimulations]++;
//			}
//
//
//		}
//
//		if(aliveNodes[i].isMajorContentNet==true)
//			numCPCC[numSimulations]++;
//
//		if(aliveNodes[i].Q==-1 && !aliveNodes[i].J.empty()){
//
//			for(it1=aliveNodes[i].J.begin();it1!=aliveNodes[i].J.end();it1++){
//
//				if(routingMatrixScale[flowIndex[i][*it1]].size()>maxTreeHeight)
//					maxTreeHeight=routingMatrixScale[flowIndex[i][*it1]].size();
//
//			}
//
//		}
//	}
//
//
//	t1Nt1TransitRatio[numSimulations]=t1VtFraction/nt1VtFraction;
//	treeHeight[numSimulations]=maxTreeHeight;
//
//	for(int i=0;i<maxFlows;i++){
//		if(!routingMatrixScale[i].empty()){
//
//			if(routingMatrixScale[i].size()>diameter)
//				diameter=routingMatrixScale[i].size();
//
//			if(routingMatrixScaleAsym[i].size()>diameter)
//				diameter=routingMatrixScaleAsym[i].size();
//
//		}
//
//		else
//			break;
//	}//end diameter for
//
//	networkDiameter[numSimulations]=diameter;
//
//	temp=0;
//	for(int i=0;i<(activeNodes-1);i++)
//		for(int j=i+1;j<activeNodes;j++){
//			if(flowIndex[i][j]!=-1){
//
//				totalTraffic+=(trafficMatrix[i][j]+trafficMatrix[j][i]);
//
//				if(aliveNodes[i].isPeer(j)){
//					temp+=(trafficMatrix[i][j]+trafficMatrix[j][i]);
//				}
//
//				numPaths+=2;
//
//				plainPath+=(routingMatrixScale[flowIndex[i][j]].size()+routingMatrixScaleAsym[flowIndex[i][j]].size());
//
//				if(flowDirectionFrom[flowIndex[i][j]]==i){
//					avgPathLength+=(routingMatrixScale[flowIndex[i][j]].size()*trafficMatrix[i][j]);
//					avgPathLength+=(routingMatrixScaleAsym[flowIndex[i][j]].size()*trafficMatrix[j][i]);
//
//				}
//
//				else{
//					avgPathLength+=(routingMatrixScale[flowIndex[i][j]].size()*trafficMatrix[j][i]);
//					avgPathLength+=(routingMatrixScaleAsym[flowIndex[i][j]].size()*trafficMatrix[i][j]);
//
//				}
//			}
//
//		}
//
//	avgPlainPathLength[numSimulations]=plainPath/numPaths;
//	avgWeightedPathLength[numSimulations]=avgPathLength/totalTraffic;
//	peeringTrafficOnly[numSimulations]=(temp/totalTraffic)*100;
//
//	//density & num links
//	if(numTotalPossibleLinks==0){
//		for(int i=0;i<activeNodes;i++)
//			for(itInt=aliveNodes[i].overLap.begin();itInt!=aliveNodes[i].overLap.end();itInt++)
//				if(*itInt>i)
//					numTotalPossibleLinks++;
//	}
//
//	for(int i=0;i<(activeNodes-1);i++)
//		for(int j=i+1;j<activeNodes;j++)
//			if(linkIndex[i][j].index!=-1){
//
//				numLinks++;
//				if(linkIndex[i][j].linkClass==CPLink)
//					numCPLinks++;
//				else
//					numPPLinks++;
//			}
//
//	linkDensity[numSimulations]=static_cast<double>(numLinks)/static_cast<double>(numTotalPossibleLinks);
//
//	for(int i=0;i<activeNodes;i++){
//		if(aliveNodes[i].K.size()>=2){
//
//			for(it1=aliveNodes[i].K.begin();it1!=aliveNodes[i].K.end();it1++)
//				for(it2=aliveNodes[i].K.begin();it2!=aliveNodes[i].K.end();it2++)
//					if(*it1!=*it2 && *it2>*it1){
//						if(aliveNodes[*it1].isPeer(*it2))
//							peeringClusteringCoefficient[i]++;
//					}
//
//			peeringClusteringCoefficient[i]=(2*peeringClusteringCoefficient[i])/(aliveNodes[i].K.size()*(aliveNodes[i].K.size()-1));
//
//		}
//	}
//
//	for(int i=0;i<activeNodes;i++)
//		networkPeeringClusteringCoefficient+=peeringClusteringCoefficient[i];
//
//	networkPeeringClusteringCoefficient=networkPeeringClusteringCoefficient/activeNodes;
//
//	ppClusteringCoefficient[numSimulations]=networkPeeringClusteringCoefficient;
//
//}
//
//void measureLinkClassificationMetrics(bool equilibriumOccured, bool isEquilibriumGood, int numSimulations){
//
//	int cp_cc=0;
//	int cp_t1=0;
//	int cp_nt1=0;
//	int cc_t1=0;
//	int cc_nt1=0;
//	int t1_t1=0;
//	int t1_nt1=0;
//	int nt1_nt1=0;
//
//	if(equilibriumOccured==true && isEquilibriumGood==true){
//
//		for(int i=0;i<activeNodes-1;i++)
//			for(int j=i+1;j<activeNodes;j++){
//
//				if(aliveNodes[i].isPeer(j)){
//
//					if((aliveNodes[i].category[1]==1 && aliveNodes[j].category[2]==1) || (aliveNodes[j].category[1]==1 && aliveNodes[i].category[2]==1)){
//						cp_cc++;
//					}
//
//					if((aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==1 && aliveNodes[j].category[1]==1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].category[4]==1 && aliveNodes[i].category[1]==1)){
//						cp_t1++;
//					}
//
//					if((aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==0 && aliveNodes[j].category[1]==1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].category[4]==0 && aliveNodes[i].category[1]==1)){
//						cp_nt1++;
//					}
//
//					if((aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==1 && aliveNodes[j].category[2]==1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].category[4]==1 && aliveNodes[i].category[2]==1)){
//						cc_t1++;
//					}
//
//					if((aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==0 && aliveNodes[j].category[2]==1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].category[4]==0 && aliveNodes[i].category[2]==1)){
//						cc_nt1++;
//					}
//
//					if(aliveNodes[i].category[0]==1 && aliveNodes[i].Q==-1 && aliveNodes[j].category[0]==1 && aliveNodes[j].Q==-1){
//						t1_t1++;
//					}
//
//					if((aliveNodes[i].category[0]==1 && aliveNodes[i].Q==-1 && aliveNodes[j].category[0]==1 && aliveNodes[j].Q!=-1) || (aliveNodes[j].category[0]==1 && aliveNodes[j].Q==-1 && aliveNodes[i].category[0]==1 && aliveNodes[i].Q!=-1)){
//						t1_nt1++;
//					}
//
//					if(aliveNodes[i].category[0]==1 && aliveNodes[i].Q!=-1 && aliveNodes[j].category[0]==1 && aliveNodes[j].Q!=-1){
//						nt1_nt1++;
//					}
//
//				}
//
//			}
//
//		resultLogFile<<"E:"<<numSimulations<<":G:L:"<<cp_cc<<":"<<cp_t1<<":"<<cp_nt1<<":"<<cc_t1<<":"<<cc_nt1<<":"<<t1_t1<<":"<<t1_nt1<<":"<<nt1_nt1<<endl;
//
//	}//end if
//}
//
//
//double findModeDouble(list<double>& priceList, list<double>& priceSetList){
//
//	list<double>::iterator itDouble1;
//	list<double>::iterator itDouble2;
//	int temp=0;
//	int freqList[6]={0};
//
//	int maxFreq=0;
//	int maxFreqPoint=0;
//
//	if(priceList.size()==1)
//		return priceList.front();
//
//	else{
//
//		for(itDouble1=priceList.begin();itDouble1!=priceList.end();itDouble1++){
//
//			temp=0;
//			for(itDouble2=priceSetList.begin();itDouble2!=priceSetList.end();itDouble2++,temp++)
//				if(*itDouble1==*itDouble2){
//					freqList[temp]++;
//					break;
//				}
//		}
//
//		for(int i=0;i<6;i++)
//			if(freqList[i]>maxFreq){
//				maxFreq=freqList[i];
//				maxFreqPoint=i;
//			}
//
//		temp=0;
//		for(itDouble2=priceSetList.begin();itDouble2!=priceSetList.end();itDouble2++,temp++)
//			if(temp==maxFreqPoint)
//				return *itDouble2;
//
//	}
//
//}
//
//int findIntMax(list<int>& checkList){
//
//	checkList.sort();
//	if(!checkList.empty())
//		return checkList.back();
//	else
//		return 0;
//
//}
//
//int findIntMin(list<int>& checkList){
//
//	checkList.sort();
//
//	if(!checkList.empty())
//		return checkList.front();
//	else
//		return 0;
//}
//
//double findIntAvg(list<int>& checkList){
//
//	double avg=0;
//	list<int>::iterator it;
//
//	if(checkList.empty())
//		return 0;
//	else{
//		for(it=checkList.begin();it!=checkList.end();it++)
//			avg+=*it;
//		return avg/checkList.size();
//	}
//}
//
//double findIntMedian(list<int>& checkList){
//
//	checkList.sort();
//	double median=0;
//	list<int>::iterator it;
//	int count=0;
//
//	if(checkList.empty())
//		return 0;
//	else if(checkList.size()==1)
//		return checkList.front();
//	else{
//
//		if(checkList.size()%2){	//odd
//
//			for(it=checkList.begin();it!=checkList.end();it++){
//				count++;
//				if(count==ceil(checkList.size()/2)){
//					it++;
//					median=*it;
//					break;
//				}
//			}
//		}
//
//		else{
//			for(it=checkList.begin();it!=checkList.end();it++){
//				count++;
//				if(count==checkList.size()/2){
//					median=*it;
//					it++;
//					median+=*it;
//					median=median/2;
//				}
//			}
//		}
//
//		return median;
//	}
//}
//
//double findDoubleMax(list<double>& checkList){
//
//	checkList.sort();
//	if(!checkList.empty())
//		return checkList.back();
//	else
//		return 0;
//
//}
//
//double findDoubleMin(list<double>& checkList){
//
//	checkList.sort();
//
//	if(!checkList.empty())
//		return checkList.front();
//	else
//		return 0;
//}
//
//double findDoubleAvg(list<double>& checkList){
//
//	double avg=0;
//	list<double>::iterator it;
//
//	if(checkList.empty())
//		return 0;
//	else{
//		for(it=checkList.begin();it!=checkList.end();it++)
//			avg+=*it;
//		return avg/checkList.size();
//	}
//}
//
//double findDoubleMedian(list<double>& checkList){
//
//	checkList.sort();
//	double median=0;
//	list<double>::iterator it;
//	int count=0;
//
//	if(checkList.empty())
//		return 0;
//	else if(checkList.size()==1)
//		return checkList.front();
//	else{
//
//		if(checkList.size()%2){	//odd
//
//			for(it=checkList.begin();it!=checkList.end();it++){
//				count++;
//				if(count==ceil(checkList.size()/2)){
//					it++;
//					median=*it;
//					break;
//				}
//			}
//		}
//
//		else{
//			for(it=checkList.begin();it!=checkList.end();it++){
//				count++;
//				if(count==checkList.size()/2){
//					median=*it;
//					it++;
//					median+=*it;
//					median=median/2;
//				}
//			}
//		}
//
//		return median;
//	}
//}
//
////economic stats
//double marshillianEfficiency[2]={0};
//double disparity[2]={0};
//double efficiency[2]={0};
//double competitiveness[2]={0};
//double stubCostsMbps[2]={0};
//double providerFitnessMbps[2]={0};
//void computeEconomicStats(int);
//
//void computeEconomicStats(int numSimulations){
//
//
//	double maxProviderFitness=0;
//	double minProviderFitness=1000000000;
//	double cumulativeProviderFitness=0;
//	double cumulativeStubFitness=0;
//	double exchangeBetweenProviders=0;
//	double totalStubTraffic=0;
//	double totalProviderTraffic=0;
//
//	for(int i=0;i<activeNodes;i++){
//		if(!aliveNodes[i].I.empty()){
//			marshillianEfficiency[numSimulations-1]+=aliveNodes[i].fitness;
//
//			if(aliveNodes[i].fitness>maxProviderFitness)
//				maxProviderFitness=aliveNodes[i].fitness;
//
//			if(aliveNodes[i].fitness<minProviderFitness)
//				minProviderFitness=aliveNodes[i].fitness;
//
//			cumulativeProviderFitness+=aliveNodes[i].fitness;
//
//			totalProviderTraffic+=(aliveNodes[i].trafficConsumed+aliveNodes[i].trafficGenerated+aliveNodes[i].Vt);
//		}
//
//		else{
//			cumulativeStubFitness+=aliveNodes[i].fitness;
//			totalStubTraffic+=(aliveNodes[i].trafficGenerated+aliveNodes[i].trafficConsumed);
//		}
//	}
//
//	disparity[numSimulations-1]=maxProviderFitness-minProviderFitness;
//	efficiency[numSimulations-1]=cumulativeProviderFitness/(-1*cumulativeStubFitness);
//
//	exchangeBetweenProviders=findExchangeBetweenProviders();
//
//	exchangeBetweenProviders=exchangeBetweenProviders/(-1*cumulativeStubFitness);
//	competitiveness[numSimulations-1]=exchangeBetweenProviders;
//
//	stubCostsMbps[numSimulations-1]=(-1*cumulativeStubFitness)/totalStubTraffic;
//	providerFitnessMbps[numSimulations-1]=cumulativeProviderFitness/totalProviderTraffic;
//
//	if(numSimulations==2){
//
//		ofstream mEfficiencyFile;
//		mEfficiencyFile.open("marshillian.txt",ios::out | ios::app);
//
//		ofstream disparityFile;
//		disparityFile.open("disparityFile.txt",ios::out | ios::app);
//
//		ofstream efficiencyFile;
//		efficiencyFile.open("efficiencyFile.txt",ios::out | ios::app);
//
//		ofstream competitivenessFile;
//		competitivenessFile.open("competitiveness.txt",ios::out | ios::app);
//
//		ofstream stubCostFile;
//		stubCostFile.open("stubCost.txt",ios::out | ios::app);
//
//		ofstream providerCostFile;
//		providerCostFile.open("providerCost.txt",ios::out | ios::app);
//
//
//		//first metric
//		if((marshillianEfficiency[1]-marshillianEfficiency[0])>0){
//			mEfficiencyFile<<"1\t0\t0"<<endl;
//		}
//
//		else if((marshillianEfficiency[1]-marshillianEfficiency[0])<0){
//			mEfficiencyFile<<"0\t1\t0"<<endl;
//		}
//
//		else{
//			mEfficiencyFile<<"0\t0\t1"<<endl;
//		}
//
//		//second metric
//		if(disparity[0]>disparity[1]){
//			disparity[1]=disparity[1]/disparity[0];
//			disparity[0]=1;
//		}
//
//		else{
//			disparity[0]=disparity[0]/disparity[1];
//			disparity[1]=1;
//		}
//
//		disparityFile<<disparity[0]<<"\t"<<disparity[1]<<endl;
//
//		//third metric
//		efficiencyFile<<efficiency[0]<<"\t"<<efficiency[1]<<endl;
//
//		//fourth metric
//		competitivenessFile<<competitiveness[0]<<"\t"<<competitiveness[1]<<endl;
//
//		//fifth metric
//		stubCostFile<<stubCostsMbps[0]<<"\t"<<stubCostsMbps[1]<<endl;
//
//		//sixth metric
//		providerCostFile<<providerFitnessMbps[0]<<"\t"<<providerFitnessMbps[1]<<endl;
//
//	}
//
//}
//
//
//double fitnessRecord[5][500];
//void recordIncreaseDecrease(int numSimulations){
//
//	double increase=0;
//	double decrease=0;
//	double constant=0;
//	double numProviders=0;
//
//	for(int i=0;i<activeNodes;i++)
//		if(!aliveNodes[i].I.empty()){
//			numProviders++;
//
//			/*
//			if(aliveNodes[i].deltaFitness>0)
//				increase++;
//			else if(aliveNodes[i].deltaFitness<0)
//				decrease++;
//			else
//				constant++;
//			*/
//
//			if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])>0)
//				increase++;
//			else if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])<0)
//				decrease++;
//			else
//				constant++;
//		}
//
//	increase=(increase/numProviders)*100;
//	decrease=(decrease/numProviders)*100;
//	constant=(constant/numProviders)*100;
//
//	providerIncreaseDecrease[numSimulations][0]=increase;
//	providerIncreaseDecrease[numSimulations][1]=decrease;
//	providerIncreaseDecrease[numSimulations][2]=constant;
//
//
//	double t1Increase=0;
//	double t1Decrease=0;
//	double t1Constant=0;
//	double t2Increase=0;
//	double t2Decrease=0;
//	double t2Constant=0;
//	double t3Increase=0;
//	double t3Decrease=0;
//	double t3Constant=0;
//	double numT1=0;
//	double numT2=0;
//	double numT3=0;
//	list<int>::iterator it;
//	bool isT2=false;
//
//	for(int i=0;i<activeNodes;i++){
//
//		if(!aliveNodes[i].I.empty()){
//
//			isT2=false;
//
//			if(aliveNodes[i].Q==-1){
//
//				numT1++;
//
//				if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])>0)
//					t1Increase++;
//
//				else if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])<0)
//					t1Decrease++;
//
//				else
//					t1Constant++;
//			}//end if for t1;
//
//			else{
//
//				for(it=aliveNodes[i].J.begin();it!=aliveNodes[i].J.end();it++){
//					if(!aliveNodes[*it].I.empty()){
//						isT2=true;
//
//						numT2++;
//						if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])>0)
//							t2Increase++;
//
//						else if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])<0)
//							t2Decrease++;
//
//						else
//							t2Constant++;
//
//						break;
//
//					}
//				}
//
//				if(isT2==false){
//
//					numT3++;
//
//					if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])>0)
//						t3Increase++;
//
//					else if((fitnessRecord[numSimulations][i]-fitnessRecord[numSimulations-1][i])<0)
//						t3Decrease++;
//
//					else
//						t3Constant++;
//
//				}
//
//			}
//
//
//		}
//	}
//
//	if(numT1>0){
//		t1Increase=t1Increase/numT1*100;
//		t1Decrease=t1Decrease/numT1*100;
//		t1Constant=t1Constant/numT1*100;
//	}
//
//	if(numT2>0){
//		t2Increase=t2Increase/numT2*100;
//		t2Decrease=t2Decrease/numT2*100;
//		t2Constant=t2Constant/numT2*100;
//	}
//
//	if(numT3>0){
//		t3Increase=t3Increase/numT3*100;
//		t3Decrease=t3Decrease/numT3*100;
//		t3Constant=t3Constant/numT3*100;
//	}
//
//	t1ProvidersFitness[numSimulations][0]=t1Increase;
//	t1ProvidersFitness[numSimulations][1]=t1Decrease;
//	t1ProvidersFitness[numSimulations][2]=t1Constant;
//
//	t2ProvidersFitness[numSimulations][0]=t2Increase;
//	t2ProvidersFitness[numSimulations][1]=t2Decrease;
//	t2ProvidersFitness[numSimulations][2]=t2Constant;
//
//	t3ProvidersFitness[numSimulations][0]=t3Increase;
//	t3ProvidersFitness[numSimulations][1]=t3Decrease;
//	t3ProvidersFitness[numSimulations][2]=t3Constant;
//
//
//}
//
//
//double strategyDistribution[5][3];
//void recordStrategyDistribution(int numSimulations){
//
//	double numProviders=0;
//	double numRestrictive=0;
//	double numSelective=0;
//	double numOpen=0;
//
//	for(int i=0;i<activeNodes;i++)
//		if(!aliveNodes[i].I.empty()){
//			numProviders++;
//
//			if(aliveNodes[i].peeringStrategyNumber==0)
//				numSelective++;
//
//			else if(aliveNodes[i].peeringStrategyNumber==1)
//				numOpen++;
//
//			else
//				numRestrictive++;
//
//
//		}
//
//	strategyDistribution[numSimulations][0]=(numSelective/numProviders)*100;
//	strategyDistribution[numSimulations][1]=(numOpen/numProviders)*100;
//	strategyDistribution[numSimulations][2]=(numRestrictive/numProviders)*100;
//
//}
//
//void providerClassIncreaseDecreaseStats(){
//
//	ofstream idFile;
//	idFile.open("providerIncreaseDecrease.txt");
//
//	for(int i=1;i<5;i++){
//		for(int j=0;j<3;j++){
//			idFile<<t1ProvidersFitness[i][j]<<"\t";
//		}
//		idFile<<endl;
//	}
//
//	idFile<<endl<<endl;
//
//	for(int i=1;i<5;i++){
//		for(int j=0;j<3;j++){
//			idFile<<t2ProvidersFitness[i][j]<<"\t";
//		}
//		idFile<<endl;
//	}
//
//	idFile<<endl<<endl;
//
//	for(int i=1;i<5;i++){
//		for(int j=0;j<3;j++){
//			idFile<<t3ProvidersFitness[i][j]<<"\t";
//		}
//		idFile<<endl;
//	}
//
//	idFile<<endl<<endl;
//}
//
//double providerIncreaseDecrease[5][3];
//double t1ProvidersFitness[5][3];
//double t2ProvidersFitness[5][3];
//double t3ProvidersFitness[5][3];
//
//
//void increaseDecreaseStats(){
//
//	ofstream id1;
//	id1.open("increaseDecrease_1.txt", ios::out | ios::app);
//
//	ofstream id2;
//	id2.open("increaseDecrease_2.txt", ios::out | ios::app);
//
//	for(int i=1;i<3;i++){
//		for(int j=0;j<3;j++){
//
//			if(i==1)
//				id1<<providerIncreaseDecrease[i][j]<<"\t";
//
//			if(i==2)
//				id2<<providerIncreaseDecrease[i][j]<<"\t";
//
//		}
//
//
//	}
//
//	id1<<endl;
//	id2<<endl;
//
//}
//
//void recordFitness(int numSimulations){
//
//
//	for(int i=0;i<activeNodes;i++){
//		fitnessRecord[numSimulations][i]=aliveNodes[i].fitness;
//
//	}
//
//}
//
//void normalizeProviderFitness(){
//
//	double max=0;
//
//	for(int i=1;i<3;i++)
//		for(int j=0;j<activeNodes;j++)
//			if(fitnessRecord[i][j]!=-1 && !aliveNodes[j].I.empty()){
//
//				aliveNodes[j].percentageChangeInFitness=((fitnessRecord[2][j]-fitnessRecord[0][j])/fitnessRecord[0][j])*100;
//
//				if(abs(fitnessRecord[i][j])>max)
//					max=abs(fitnessRecord[i][j]);
//			}
//
//	if(max!=0){
//
//		for(int i=0;i<5;i++)
//			for(int j=0;j<activeNodes;j++)
//				if(fitnessRecord[i][j]!=-1 && !aliveNodes[j].I.empty()){
//					fitnessRecord[i][j]=fitnessRecord[i][j]/max;
//
//				}
//
//	}
//
//}
//
//void normalizeCPCCFitness(){
//
//	double max=0;
//
//	for(int i=0;i<5;i++)
//		for(int j=0;j<activeNodes;j++)
//			if(fitnessRecord[i][j]!=-1 && aliveNodes[j].isMajorContentNet==true){
//				if(abs(fitnessRecord[i][j])>max)
//					max=abs(fitnessRecord[i][j]);
//			}
//
//	if(max!=0){
//
//		for(int i=0;i<5;i++)
//			for(int j=0;j<activeNodes;j++)
//				if(fitnessRecord[i][j]!=-1 && aliveNodes[j].isMajorContentNet==true){
//					fitnessRecord[i][j]=fitnessRecord[i][j]/max;
//
//				}
//
//	}
//
//}
//
//void normalizeStubFitness(){
//
//	double max=0;
//
//	for(int i=0;i<5;i++)
//		for(int j=0;j<activeNodes;j++)
//			if(fitnessRecord[i][j]!=-1 && aliveNodes[j].isMajorContentNet==false && aliveNodes[j].I.empty()){
//				if(abs(fitnessRecord[i][j])>max)
//					max=abs(fitnessRecord[i][j]);
//			}
//
//	if(max!=0){
//
//		for(int i=0;i<5;i++)
//			for(int j=0;j<activeNodes;j++)
//				if(fitnessRecord[i][j]!=-1 && aliveNodes[j].isMajorContentNet==false && aliveNodes[j].I.empty()){
//					fitnessRecord[i][j]=fitnessRecord[i][j]/max;
//
//				}
//
//	}
//
//}
//
//void providerFitnessStats(){
//
//	ofstream providerStats;
//	providerStats.open("providerFitnessStats.txt");
//
//	double avg=0;
//	double median=0;
//	double min=0;
//	double max=0;
//	list<double> values;
//
//	double stats[5][4];
//
//	for(int i=0;i<5;i++){
//
//		values.clear();
//
//		for(int j=0;j<500;j++){
//			if(!aliveNodes[j].I.empty())
//				values.push_back(fitnessRecord[i][j]);
//		}
//
//		avg=findDoubleAvg(values);
//		median=findDoubleMedian(values);
//		min=findDoubleMin(values);
//		max=findDoubleMax(values);
//
//		stats[i][0]=avg;
//		stats[i][1]=median;
//		stats[i][2]=min;
//		stats[i][3]=max;
//
//	}
//
//	for(int i=0;i<5;i++){
//		for(int j=0;j<4;j++){
//			providerStats<<stats[i][j]<<"\t";
//		}
//		providerStats<<endl;
//	}
//
//}
//
//void cpccFitnessStats(){
//
//	ofstream cpccStats;
//	cpccStats.open("cpccFitnessStats.txt");
//
//	double avg=0;
//	double median=0;
//	double min=0;
//	double max=0;
//	list<double> values;
//
//	double stats[5][4];
//
//	for(int i=0;i<5;i++){
//
//		values.clear();
//
//		for(int j=0;j<500;j++){
//			if(aliveNodes[j].I.empty() && aliveNodes[j].isMajorContentNet==true)
//				values.push_back(fitnessRecord[i][j]);
//		}
//
//		avg=findDoubleAvg(values);
//		median=findDoubleMedian(values);
//		min=findDoubleMin(values);
//		max=findDoubleMax(values);
//
//		stats[i][0]=avg;
//		stats[i][1]=median;
//		stats[i][2]=min;
//		stats[i][3]=max;
//
//	}
//
//	for(int i=0;i<5;i++){
//		for(int j=0;j<4;j++){
//			cpccStats<<stats[i][j]<<"\t";
//		}
//		cpccStats<<endl;
//	}
//
//}
//
//void stubFitnessStats(){
//
//	ofstream stubStats;
//	stubStats.open("stubFitnessStats.txt");
//
//	double avg=0;
//	double median=0;
//	double min=0;
//	double max=0;
//	list<double> values;
//
//	double stats[5][4];
//
//	for(int i=0;i<5;i++){
//
//		values.clear();
//
//		for(int j=0;j<500;j++){
//			if(aliveNodes[j].I.empty() && aliveNodes[j].isMajorContentNet==false)
//				values.push_back(fitnessRecord[i][j]);
//		}
//
//		avg=findDoubleAvg(values);
//		median=findDoubleMedian(values);
//		min=findDoubleMin(values);
//		max=findDoubleMax(values);
//
//		stats[i][0]=avg;
//		stats[i][1]=median;
//		stats[i][2]=min;
//		stats[i][3]=max;
//
//	}
//
//	for(int i=0;i<5;i++){
//		for(int j=0;j<4;j++){
//			stubStats<<stats[i][j]<<"\t";
//		}
//		stubStats<<endl;
//	}
//
//}
//double checkRoutingMatrixScaleAsymNT1(int flowIndex,int start,int end){
//
//	list<int>::iterator itR;
//	double peerTraffic=0;
//
//	for(itR=routingMatrixScaleAsym[flowIndex].begin();itR!=routingMatrixScaleAsym[flowIndex].end();itR++){
//
//		for(int i=0;i<activeNodes-1;i++)
//			for(int j=i+1;j<activeNodes;j++){
//
//				if(linkIndex[i][j].index==*itR){
//
//					if((i==start && aliveNodes[j].isImmediateCustomer(i)) || (j==end && aliveNodes[i].isImmediateCustomer(j))){
//
//						if(flowDirectionFromAsym[flowIndex]==start)
//							return peerTraffic+=trafficMatrix[start][end];
//
//						else
//							return peerTraffic+=trafficMatrix[end][start];
//					}
//
//					if(i!=start && j!=end && (!aliveNodes[i].I.empty() || !aliveNodes[j].I.empty())){
//
//						if(flowDirectionFromAsym[flowIndex]==start)
//							return peerTraffic+=trafficMatrix[start][end];
//
//						else
//							return peerTraffic+=trafficMatrix[end][start];
//
//					}
//
//				}
//
//			}//end for
//
//	}//end for
//
//	return peerTraffic;
//
//}
//
//double checkIfT1Transitted(int flowIndex,int start, int end){
//
//	double peerTraffic=0;
//
//	peerTraffic+=checkRoutingMatrixScale(flowIndex,start,end);
//	peerTraffic+=checkRoutingMatrixScaleAsym(flowIndex,start,end);
//
//	return peerTraffic;
//
//}
//
//double checkIfNT1Transitted(int flowIndex,int start, int end){
//
//	double peerTraffic=0;
//
//	peerTraffic+=checkRoutingMatrixScaleNT1(flowIndex,start,end);
//	peerTraffic+=checkRoutingMatrixScaleAsymNT1(flowIndex,start,end);
//
//	return peerTraffic;
//
//}
//
//
//double measureT1VtTrafficFraction(){
//
//	double density=0;
//	double peerTraffic=0;
//	double totalTraffic=0;
//
//	for(int i=0;i<activeNodes-1;i++)
//		for(int j=i+1;j<activeNodes;j++){
//
//			if(linkIndex[i][j].index==-1){
//
//				peerTraffic+=checkIfT1Transitted(flowIndex[i][j],i,j);
//
//			}//end if
//
//		}//end for
//
//
//	for(int i=0;i<activeNodes;i++)
//		totalTraffic+=aliveNodes[i].trafficGenerated;
//
//	density=(peerTraffic/totalTraffic)*100;
//
//	return density;
//
//}
//
//double measureNT1VtTrafficFraction(){
//
//	double density=0;
//	double peerTraffic=0;
//	double totalTraffic=0;
//
//	for(int i=0;i<activeNodes-1;i++)
//		for(int j=i+1;j<activeNodes;j++){
//
//			if(linkIndex[i][j].index==-1){
//
//				peerTraffic+=checkIfNT1Transitted(flowIndex[i][j],i,j);
//
//			}//end if
//
//		}//end for
//
//
//	for(int i=0;i<activeNodes;i++)
//		totalTraffic+=aliveNodes[i].trafficGenerated;
//
//	density=(peerTraffic/totalTraffic)*100;
//
//	return density;
//
//}
//
//double measureT1PeeringTraffic(){
//
//	double density=0;
//	double peerTraffic=0;
//	double totalTraffic=0;
//
//	for(int i=0;i<(activeNodes-1);i++)
//		for(int j=i+1;j<activeNodes;j++)
//			if(aliveNodes[i].Q==-1 && aliveNodes[j].Q==-1){
//				peerTraffic+=linkValueVector[linkIndex[i][j].index];
//			}
//
//
//	for(int i=0;i<activeNodes;i++)
//		totalTraffic+=aliveNodes[i].trafficGenerated;
//
//	density=(peerTraffic/totalTraffic)*100;
//
//	return density;
//}
//
//
//
//double measurePeeringTraffic(){
//
//	double density=0;
//	double peerTraffic=0;
//	double totalTraffic=0;
//
//	for(int i=0;i<(activeNodes-1);i++)
//		for(int j=i+1;j<activeNodes;j++)
//			if(linkIndex[i][j].index!=-1 && (linkIndex[i][j].linkClass==PPLink || linkIndex[i][j].linkClass==PPPLink)){
//				peerTraffic+=trafficMatrix[i][j]+trafficMatrix[j][i];
//			}
//
//	for(int i=0;i<activeNodes;i++)
//		totalTraffic+=aliveNodes[i].trafficGenerated;
//
//	density=(peerTraffic/totalTraffic)*100;
//
//	return density;
//}
//
//void measureStrategyShifts(bool equilibriumOccured, int steady, int innovate, int imitate,int fittestNode, bool isEquilibriumGood, int numSimulations){
//
//
//	double strategyLog[15][15]={0};
//	double sum=0;
//
//	for(int i=0;i<activeNodes;i++){
//
//		if(aliveNodes[i].category[0]==0)
//			strategyLog[aliveNodes[i].peeringStrategyNumber][0]++;			//stub
//		else
//			strategyLog[aliveNodes[i].peeringStrategyNumber][1]++;			//provider
//
//		if(aliveNodes[i].category[1]==1 || aliveNodes[i].category[1]==2)	//CP
//			strategyLog[aliveNodes[i].peeringStrategyNumber][2]++;
//
//		if(aliveNodes[i].category[2]==1 || aliveNodes[i].category[2]==2)	//CC
//			strategyLog[aliveNodes[i].peeringStrategyNumber][3]++;
//
//		if(aliveNodes[i].category[3]==1)
//			strategyLog[aliveNodes[i].peeringStrategyNumber][4]++;			//GP
//
//		if(aliveNodes[i].category[3]==2)
//			strategyLog[aliveNodes[i].peeringStrategyNumber][5]++;			//RP
//
//		if(aliveNodes[i].category[3]==3)
//			strategyLog[aliveNodes[i].peeringStrategyNumber][6]++;			//LP
//
//		if(aliveNodes[i].category[4]==2)									//T1P
//			strategyLog[aliveNodes[i].peeringStrategyNumber][7]++;
//
//		if(aliveNodes[i].category[0]==1 && aliveNodes[i].category[4]==0)
//			strategyLog[aliveNodes[i].peeringStrategyNumber][8]++;			//Non-T1P
//
//
//		if(aliveNodes[i].category[6]==0 )
//			strategyLog[aliveNodes[i].peeringStrategyNumber][9]++;			//HighPrice
//
//		if(aliveNodes[i].category[6]==1)
//			strategyLog[aliveNodes[i].peeringStrategyNumber][10]++;			//LowPrice
//
//
//	}//end for
//
//	if(equilibriumOccured==false){
//		resultLogFile<<"R:"<<rounds<<":P:";
//	}
//
//	else{
//		if(isEquilibriumGood==true)
//			resultLogFile<<"E:"<<numSimulations<<":G:P:";
//		else
//			resultLogFile<<"E:"<<numSimulations<<":B:P:";
//	}
//
//	if(fittestNode!=-1)
//		resultLogFile<<aliveNodes[fittestNode].peeringStrategyNumber<<":";
//	else
//		resultLogFile<<"-1:";
//
//	for(int i=0;i<11;i++){
//		sum=0;
//
//		for(int j=0;j<totalPeeringStrategies;j++){
//			sum+=strategyLog[j][i];
//		}
//
//		for(int k=0;k<totalPeeringStrategies;k++){
//
//			if(sum>0)
//				strategyLog[k][i]=100*strategyLog[k][i]/sum;
//
//			if(k<(totalPeeringStrategies-1)){
//				resultLogFile<<strategyLog[k][i]<<",";
//			}
//
//			else{
//				resultLogFile<<strategyLog[k][i]<<";"<<sum<<":";
//			}
//
//		}
//
//	}
//
//	resultLogFile<<endl;
//
//}
//
//int findMinConsumedTraffic(int i){
//
//	double traffic=1000000000;
//	int found;
//
//	for(int j=0;j<activeNodes;j++){
//		if(j!=i){
//			if(aliveNodes[j].trafficConsumed<traffic){
//				traffic=aliveNodes[j].trafficConsumed;
//				found=j;
//			}
//		}
//	}
//
//	return found;
//}
//
//double findExchangeBetweenProviders(){
//
//	double exchange=0;
//
//	for(int i=0;i<activeNodes-1;i++)
//		for(int j=i+1;j<activeNodes;j++){
//			if(!aliveNodes[i].I.empty() && !aliveNodes[j].I.empty() && linkIndex[i][j].index!=-1){
//
//				if(aliveNodes[i].isPeer(j)){
//					//they are peers
//					//exchange+=(aliveNodes[i].peeringCostMultiplier*pow(linkValueVector[linkIndex[i][j].index],aliveNodes[i].peeringExponent));
//
//				}
//
//				else{
//					//they have a CP CC relationship
//					if(aliveNodes[i].Q==j){
//						//i is a customer of j
//						exchange+=(aliveNodes[j].price*pow(linkValueVector[linkIndex[i][j].index],aliveNodes[j].providerExponent));
//					}
//
//					else{
//						//j is a customer of i
//						exchange+=(aliveNodes[i].price*pow(linkValueVector[linkIndex[i][j].index],aliveNodes[i].providerExponent));
//					}
//				}
//			}
//		}
//
//	return exchange;
//}
//
//
//
//
//void findStubTraffic(int numSimulations){
//
//	ofstream stubFile;
//	stubFile.open("stubTraffic.txt",ios::out | ios::app);
//
//	ofstream cdFile;
//	cdFile.open("cdFile.txt",ios::out | ios::app);
//
//	double totalTraffic=0;
//	double transitTraffic=0;
//	double stubPeeringTraffic=0;
//	double providerPeeringTraffic=0;
//	double possiblePeeringTraffic=0;
//	list<int>::iterator it;
//	double cpccPeeringTraffic=0;
//	list<int> majorCPCC;
//
//	double cumulativeTraffic=0;
//	double cumulativeStubPeeringTraffic=0;
//	double cumulativeProviderPeeringTraffic=0;
//	double cumulativeTransitTraffic=0;
//	int numProviderOverlap=0;
//	int numStubOverlap=0;
//	int numProviderPeer=0;
//	list<int>::iterator it2;
//	list<int>::iterator it3;
//	list<int> encountered;
//	int k=0;
//	double sum=0;
//
//	//if(numSimulations==2){
//
//		for(int i=0;i<activeNodes;i++)
//			if(aliveNodes[i].I.empty() && aliveNodes[i].isMajorContentNet==true)
//				majorCPCC.push_back(i);
//
//		for(int i=0;i<activeNodes;i++)
//			if(!aliveNodes[i].I.empty())
//				cdFile<<aliveNodes[i].I.size()<<endl;
//
//		for(int i=0;i<activeNodes;i++){
//			if(aliveNodes[i].I.empty()){
//
//				totalTraffic=0;
//				transitTraffic=0;
//				stubPeeringTraffic=0;
//				providerPeeringTraffic=0;
//				cpccPeeringTraffic=0;
//				numProviderOverlap=0;
//				numProviderPeer=0;
//				possiblePeeringTraffic=0;
//				encountered.clear();
//				k=0;
//				sum=0;
//
//				totalTraffic=aliveNodes[i].trafficConsumed+aliveNodes[i].trafficGenerated;
//				cumulativeTraffic+=totalTraffic;
//
//				for(it=aliveNodes[i].overLap.begin();it!=aliveNodes[i].overLap.end();it++){
//					if(!aliveNodes[*it].I.empty()){
//						numProviderOverlap++;
//
//						if(aliveNodes[i].isPeer(*it)){
//							numProviderPeer++;
//						}
//					}
//				}
//
//
//				if(aliveNodes[i].Q!=-1){
//					transitTraffic+=linkValueVector[linkIndex[i][aliveNodes[i].Q].index];
//					cumulativeTransitTraffic+=transitTraffic;
//				}
//
//				else
//					transitTraffic=0;
//
//				transitTraffic=transitTraffic/totalTraffic;
//
//
//				if(!aliveNodes[i].K.empty()){
//					for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++){
//
//						if(!aliveNodes[*it].I.empty()){
//							providerPeeringTraffic+=linkValueVector[linkIndex[i][*it].index];
//							cumulativeProviderPeeringTraffic+=providerPeeringTraffic;
//						}
//
//						else{
//							stubPeeringTraffic+=linkValueVector[linkIndex[i][*it].index];
//							cumulativeStubPeeringTraffic+=stubPeeringTraffic;
//						}
//
//					}
//				}
//
//				if(aliveNodes[i].isMajorContentNet==false){
//					if(!aliveNodes[i].K.empty()){
//						for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++)
//							if(aliveNodes[*it].isMajorContentNet==true){
//								cpccPeeringTraffic+=linkValueVector[linkIndex[i][*it].index];
//							}
//					}
//				}
//
//				cpccPeeringTraffic=cpccPeeringTraffic/stubPeeringTraffic;
//				stubPeeringTraffic=stubPeeringTraffic/totalTraffic;
//				providerPeeringTraffic=providerPeeringTraffic/totalTraffic;
//				sum=transitTraffic+stubPeeringTraffic+providerPeeringTraffic;
//
//				stubFile<<numProviderOverlap<<"\t"<<numProviderPeer<<"\t"<<transitTraffic<<"\t"<<stubPeeringTraffic<<"\t"<<providerPeeringTraffic<<"\t"<<sum<<"\t"<<cpccPeeringTraffic<<endl;
//
//			}
//
//		}
//
//		cout<<"Cumulatives: "<<cumulativeTransitTraffic/cumulativeTraffic<<"\t"<<cumulativeStubPeeringTraffic/cumulativeTraffic<<"\t"<<cumulativeProviderPeeringTraffic/cumulativeTraffic<<endl;
//
//	//}
//	/*
//	//else{
//
//		for(int i=0;i<activeNodes;i++){
//
//			totalTraffic=0;
//			peeringTraffic=0;
//			numProviderOverlap=0;
//			numProviderPeer=0;
//			possiblePeeringTraffic=0;
//			encountered.clear();
//			int k=0;
//
//
//			if(aliveNodes[i].I.empty()){
//				totalTraffic=aliveNodes[i].trafficGenerated+aliveNodes[i].trafficConsumed;
//
//				if(!aliveNodes[i].K.empty()){
//					for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++)
//						if(!aliveNodes[*it].I.empty()){
//							peeringTraffic+=linkValueVector[linkIndex[i][*it].index];
//							possiblePeeringTraffic+=(trafficMatrix[i][*it]+trafficMatrix[*it][i]);
//
//						}
//
//
//					for(int j=0;j<activeNodes;j++)
//						if(i!=j && !aliveNodes[i].isPeer(j) && (k=aliveNodes[i].isPresentInCustomerTreeOfPeer(j))!=-1){
//
//							if(!aliveNodes[k].isPeer(j)){
//
//								possiblePeeringTraffic+=trafficMatrix[i][j];
//
//								if(aliveNodes[j].isPresentInCustomerTreeOfPeer(i)==-1)
//									possiblePeeringTraffic+=trafficMatrix[j][i];
//							}
//						}
//				}
//
//				for(it=aliveNodes[i].overLap.begin();it!=aliveNodes[i].overLap.end();it++){
//					if(!aliveNodes[*it].I.empty()){
//						numProviderOverlap++;
//
//						if(aliveNodes[i].isPeer(*it)){
//							numProviderPeer++;
//						}
//					}
//				}
//
//				stubProviderFile<<numProviderOverlap<<"\t"<<numProviderPeer<<"\t"<<"\t"<<possiblePeeringTraffic/totalTraffic<<"\t"<<peeringTraffic/totalTraffic<<endl;
//
//			}
//
//		}
//
//	//}
//	 */
//}
//
//void customerPeerExpanseCurves(){
//
//	ofstream cpExpanseFile;
//	cpExpanseFile.open("cpExpanse.txt",ios::out | ios::app);
//
//	for(int i=0;i<activeNodes;i++)
//		if(!aliveNodes[i].I.empty()){
//			cpExpanseFile<<aliveNodes[i].numGPresence<<"\t"<<aliveNodes[i].I.size()<<"\t"<<aliveNodes[i].K.size()<<endl;
//		}
//
//}
//
//void strategiesExpanseCurves(int numSimulations){
//
//	int s[16][3]={0};
//
//
//	ofstream sExpanseE1File;
//	ofstream sExpanseE2File;
//
//	sExpanseE1File.open("sExpanseE1.txt",ios::out | ios::app);
//	sExpanseE2File.open("sExpanseE2.txt",ios::out | ios::app);
//
//	for(int i=0;i<activeNodes;i++)
//		if(!aliveNodes[i].I.empty()){
//			s[aliveNodes[i].numGPresence][aliveNodes[i].peeringStrategyNumber]++;
//		}
//
//
//	for(int i=1;i<16;i++){
//		for(int j=0;j<3;j++){
//			if(numSimulations==1){
//				sExpanseE1File<<i<<"\t"<<s[i][j]<<"\t";
//			}
//
//			else{
//				sExpanseE2File<<i<<"\t"<<s[i][j]<<"\t";
//			}
//
//
//		}
//
//		if(numSimulations==0)
//			sExpanseE1File<<endl;
//		else
//			sExpanseE2File<<endl;
//	}
//
//
//}
//
//void customersFitnessCurves(int numSimulations){
//
//	ofstream cfFileE1;
//	ofstream cfFileE2;
//
//	cfFileE1.open("customerFitnessE1.txt",ios::out | ios::app);
//	cfFileE2.open("customerFitnessE2.txt",ios::out | ios::app);
//
//	if(numSimulations==1){
//		for(int i=0;i<activeNodes;i++)
//			if(!aliveNodes[i].I.empty())
//				cfFileE1<<aliveNodes[i].I.size()<<"\t"<<aliveNodes[i].fitness<<endl;
//	}
//
//	else{
//		for(int i=0;i<activeNodes;i++)
//			if(!aliveNodes[i].I.empty())
//				cfFileE2<<aliveNodes[i].I.size()<<"\t"<<aliveNodes[i].fitness<<endl;
//
//	}
//
//}
//
//void peersFitnessCurves(int numSimulations){
//
//	ofstream pfFileE1;
//	ofstream pfFileE2;
//
//	pfFileE1.open("peerFitnessE1.txt",ios::out | ios::app);
//	pfFileE2.open("peerFitnessE2.txt",ios::out | ios::app);
//
//	if(numSimulations==1){
//		for(int i=0;i<activeNodes;i++)
//			if(!aliveNodes[i].I.empty())
//				pfFileE1<<aliveNodes[i].K.size()<<"\t"<<aliveNodes[i].fitness<<endl;
//	}
//
//	else{
//		for(int i=0;i<activeNodes;i++)
//			if(!aliveNodes[i].I.empty())
//				pfFileE2<<aliveNodes[i].K.size()<<"\t"<<aliveNodes[i].fitness<<endl;
//
//	}
//
//}
//
//void t1ExpanseCurves(){
//
//	int expanse[16]={0};
//	ofstream expanseT1File;
//	expanseT1File.open("expanseT1.txt", ios::out | ios::app);
//
//	for(int i=0;i<activeNodes;i++)
//		if(!aliveNodes[i].I.empty() && aliveNodes[i].Q==-1)
//			expanse[aliveNodes[i].numGPresence]++;
//
//	for(int i=1;i<16;i++)
//		expanseT1File<<i<<"\t"<<expanse[i]<<endl;
//
//
//
//}
//
//void fitnessCurves(){
//
//	int t1Increase=0;
//	int t1Decrease=0;
//	int t1Constant=0;
//	int nt1Increase=0;
//	int nt1Decrease=0;
//	int nt1Constant=0;
//
//	list<int>::iterator it;
//	int numStubsAdded=0;
//
//	ofstream f1File;
//	f1File.open("fitnessComparison.txt",ios::out | ios::app);
//
//	ofstream f2FileE1;
//	f2FileE1.open("fitnessExpanseE1Detailed.txt",ios::out | ios::app);
//
//	ofstream f2FileE2;
//	f2FileE2.open("fitnessExpanseE2Detailed.txt",ios::out | ios::app);
//
//	ofstream f3File;
//	f3File.open("fitnessT1.txt",ios::out | ios::app);
//
//	ofstream f4File;
//	f4File.open("fitnessNT1.txt",ios::out | ios::app);
//
//	ofstream f5File;
//	f5File.open("fitnessStubAdded.txt",ios::out | ios::app);
//
//	ofstream f6File;
//	f6File.open("fitnessDifferenceStrategy.txt",ios::out | ios::app);
//
//	for(int i=0;i<activeNodes;i++){
//		if(!aliveNodes[i].I.empty()){
//
//			numStubsAdded=0;
//
//			f1File<<i<<"\t"<<fitnessRecord[0][i]<<"\t"<<fitnessRecord[1][i]<<"\t"<<fitnessRecord[2][i]<<endl;
//
//			if(numSimulations==1)
//				f2FileE1<<i<<"\t"<<aliveNodes[i].peeringStrategyNumber<<"\t"<<aliveNodes[i].numGPresence<<"\t"<<fitnessRecord[1][i]<<endl;
//			else
//				f2FileE2<<i<<"\t"<<aliveNodes[i].peeringStrategyNumber<<"\t"<<aliveNodes[i].numGPresence<<"\t"<<fitnessRecord[2][i]<<endl;
//
//			if(aliveNodes[i].Q==-1){
//
//				f3File<<i<<"\t"<<fitnessRecord[2][i]-fitnessRecord[1][i]<<endl;
//
//				if((fitnessRecord[2][i]-fitnessRecord[1][i])>0)
//					t1Increase++;
//
//				else if((fitnessRecord[2][i]-fitnessRecord[1][i])<0)
//					t1Decrease++;
//
//				else
//					t1Constant++;
//			}
//
//			else{
//
//				f4File<<i<<"\t"<<fitnessRecord[2][i]-fitnessRecord[1][i]<<endl;
//
//				if((fitnessRecord[2][i]-fitnessRecord[1][i])>0)
//					nt1Increase++;
//
//				else if((fitnessRecord[2][i]-fitnessRecord[1][i])<0)
//					nt1Decrease++;
//
//				else
//					nt1Constant++;
//
//			}
//
//			for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++){
//				if(aliveNodes[*it].I.empty() && aliveNodes[*it].isMajorContentNet==false)
//					numStubsAdded++;
//			}
//
//			f5File<<i<<"\t"<<numStubsAdded<<"\t"<<fitnessRecord[2][i]-fitnessRecord[1][i]<<endl;
//
//
//			f6File<<i<<"\t"<<aliveNodes[i].peeringStrategyNumber<<"\t"<<fitnessRecord[2][i]-fitnessRecord[1][i]<<endl;
//
//		}
//	}
//
//}
//
////******************************* Archived Functions ************************************//
////****************************************************************************************
//
//bool checkConnectivitySum(){
//
//	int sum=1;
//	list<int> tempList;
//	list<int>::iterator itInt;
//	list<int>::iterator itInt1;
//	list<int> tempK;
//
//	for(int i=0;i<activeNodes;i++){
//
//		if(!aliveNodes[i].J.empty()){
//			aliveNodes[i].J.sort();
//			aliveNodes[i].J.unique();
//		}
//	}
//
//	for(int i=0;i<activeNodes;i++){
//
//		sum=1;
//		if(!aliveNodes[i].J.empty()){
//			aliveNodes[i].J.sort();
//			aliveNodes[i].J.unique();
//			sum+=aliveNodes[i].J.size();
//		}
//
//		tempList.clear();
//		tempK.clear();
//
//		if(!aliveNodes[i].K.empty()){
//
//			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++)
//				tempK.push_back(*itInt);
//
//			for(itInt=aliveNodes[i].K.begin();itInt!=aliveNodes[i].K.end();itInt++)
//				for(itInt1=aliveNodes[i].K.begin();itInt1!=aliveNodes[i].K.end();itInt1++)
//					if(*itInt!=*itInt1 && aliveNodes[*itInt].isPresentInCustomerTree(*itInt1))
//						tempK.remove(*itInt1);
//
//			sum+=tempK.size();
//
//
//			for(itInt=tempK.begin();itInt!=tempK.end();itInt++)
//				sum+=aliveNodes[*itInt].J.size();
//
//
//		}
//
//		for(int j=0;j<activeNodes;j++){
//			if(j!=i && !aliveNodes[i].isPresentInCustomerTree(j) && !aliveNodes[i].isPeer(j) && -1==aliveNodes[i].isPresentInCustomerTreeOfPeer(j)){
//
//				tempList.push_back(j);
//			}
//		}
//
//		sum+=tempList.size();
//
//		if(sum!=activeNodes){
//
//			logFile<<"Total nodes for "<<i<<" are "<<sum<<" which is "<<activeNodes-sum<<" less than actual value"<<endl;
//			displayTopology();
//			string str("ERROR!! Connectivity breached in Peering");
//			endSimulation(str);
//		}
//
//	}
//
//	return true;
//}
//
//bool checkConnectivity(){
//
//	list<int>::iterator it1;
//	list<int>::iterator it2;
//	int flowSum=0;
//	int flowSumAsym=0;
//
//	for(int i=0;i<activeNodes;i++){
//		if(aliveNodes[i].Q!=-1){
//			if(linkIndex[i][aliveNodes[i].Q].index==-1){
//				logFile<<"Link between "<<i<<" and its provider "<<aliveNodes[i].Q<<" not established"<<endl;
//				string str="ERROR!! Breach in connectivity";
//				endSimulation(str);
//			}
//		}
//
//		else{
//
//			if(!isPresentInList(Tier1,i)){
//				logFile<<"Node "<<i<<" has no provider yet not in Tier1"<<endl;
//				string str="ERROR!! Breach in connectivity";
//				endSimulation(str);
//
//			}
//		}
//
//	}
//
//	for(it1=Tier1.begin();it1!=Tier1.end();it1++)
//		for(it2=Tier1.begin();it2!=Tier1.end();it2++){
//			if(*it2!=*it1){
//				if(!isPresentInList(aliveNodes[*it1].K,*it2)){
//					logFile<<"Peers "<<*it1<<" and "<<*it2<<" not in eachother's K list"<<endl;
//					string str="ERROR!! Breach in connectivity";
//					endSimulation(str);
//				}
//
//				if(linkIndex[*it1][*it2].index==-1 || linkIndex[*it1][*it2].linkClass!=PPLink){
//					logFile<<"Link between peers "<<*it1<<" and "<<*it2<<" not established"<<endl;
//					string str="ERROR!! Breach in connectivity";
//					endSimulation(str);
//				}
//			}
//		}
//
//	for(int i=0;i<activeNodes;i++)
//		for(int j=0;j<activeNodes;j++)
//			if(i!=j){
//
//				flowSum=0;
//				flowSumAsym=0;
//				flowSum+=routingMatrixScale[flowIndex[i][j]].size();
//				flowSumAsym+=routingMatrixScaleAsym[flowIndex[i][j]].size();
//
//				if(flowSum==0){
//					logFile<<"Flow could not be established between "<<i<<" and "<<j<<endl;
//					string str="ERROR!! Flows not properly established";
//					endSimulation(str);
//				}
//
//				if(flowSumAsym==0){
//					logFile<<"Flow could not be established between "<<i<<" and "<<j<<" in asymmetric matrix"<<endl;
//					string str="ERROR!! Flows not properly established";
//					endSimulation(str);
//				}
//			}
//
//	for(int i=0;i<activeNodes;i++)
//		if(aliveNodes[i].isPresentInCustomerTree(i)){
//			logFile<<"Node "<<i<<" is present in its own customer tree"<<endl;
//			string str="ERROR!! Loop detected";
//			endSimulation(str);
//		}
//
//	checkConnectivitySum();
//
//	return true;
//}
//
//
//bool Node::getOrphanProvider(){
//
//	/*
//	list<npPair> GS;
//	list<npPair> TGS;
//	list<Coordinate>::iterator it;
//	list<int>::iterator it2;
//	list<npPair>::iterator it4;
//	int xPoint;
//	int yPoint;
//	npPair possibleProvider;
//	int providerId;
//	int P;
//	int X;
//	int Z;
//
//#if DEBUG
//	logFile<<endl<<"Orphan node "<<nodeId<<" getting new provider"<<endl;
//#endif
//
//
//	//Step 1 Creation of GS
//	for(it=gPresence.begin();it!=gPresence.end();it++){
//
//		xPoint=(*it).xCoordinate;
//		yPoint=(*it).yCoordinate;
//
//		if(geography[xPoint][yPoint].population>1){
//
//			for(it2=geography[xPoint][yPoint].nodePresent.begin();it2!=geography[xPoint][yPoint].nodePresent.end();it2++){
//
//				if((*it2)!=nodeId && aliveNodes[*it2].lifeStatus==alive && aliveNodes[*it2].newborn==false && aliveNodes[*it2].orphan==false && !isPresentInList(prohibitedProviderList,*it2) && !isPresentInCustomerTree(*it2)){
//
//					possibleProvider.nId=*it2;
//					possibleProvider.price=aliveNodes[*it2].price;
//					possibleProvider.trafficVolume=aliveNodes[*it2].Vt;
//
//					GS.push_back(possibleProvider);
//
//				}//end if
//
//			}//end for
//
//		}//end if
//
//	}//end for
//
//	//Step 2 Creation of TGS
//	if(!GS.empty()){
//
//		GS.sort(compareId);
//		GS.unique(checkUniqueness);
//
//		for(it4=GS.begin();it4!=GS.end();it4++){
//
//			if((*it4).trafficVolume>Vt)
//				TGS.push_back(*it4);
//
//		}//end for
//
//	}//end if
//
//
//	if(TGS.empty()){	//orphan node is to become Tier1
//
//		list<int>::iterator itTier1;
//		list<int> xSet;
//		list<int> restSet;
//		list<int>::iterator it;
//		list<int>::iterator itX;
//		list<int>::iterator itRest;
//
//		Q=-1;
//		providerPrice=0;
//
//#if DEBUG
//		logFile<<"Orphan node "<<nodeId<<" becoming Tier1"<<endl;
//#endif
//
//		for(itTier1=Tier1.begin();itTier1!=Tier1.end();itTier1++){
//
//			insertPeerInK(*itTier1);
//			aliveNodes[*itTier1].insertPeerInK(nodeId);
//			establishLinkWithPeer(nodeId,*itTier1);
//			establishFlowWithPeer(nodeId,*itTier1);
//
//		}
//
//		Tier1.push_back(nodeId);
//
//		prohibitedProviderList.remove(nodeId);
//		for(it=J.begin();it!=J.end();it++){
//			prohibitedProviderList.remove(*it);
//			xSet.push_back(*it);
//		}
//
//		for(int i=0;i<activeNodes;i++)
//			if(i!=nodeId && !isPresentInCustomerTree(i) && !isPresentInList(prohibitedProviderList,i))
//				restSet.push_back(i);
//
//		for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
//			if(!isPeer(*itRest))
//				establishFlowPeering(nodeId,*itRest,Q);
//
//		for(itX=xSet.begin();itX!=xSet.end();itX++)
//			for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
//				establishFlowPeering(*itX,*itRest,aliveNodes[*itX].Q);
//
//		return true;
//
//	}//end if node becomes Tier1
//
//	else{
//
//		TGS.sort(comparePrice);
//
//		int Z=TGS.front().nId;
//		list<int>::iterator it;
//		list<int> xSet;
//		list<int> restSet;
//		list<int>::iterator itX;
//		list<int>::iterator itRest;
//
//#if DEBUG
//		logFile<<"Orphan node "<<nodeId<<" got provider "<<Z<<endl;
//#endif
//
//		Q=Z;
//		providerPrice=aliveNodes[Z].price;
//		establishLinkWithProvider(nodeId,Z);
//		establishFlowWithProviderScale(nodeId,Z);
//
//		aliveNodes[Q].addICustomer(nodeId);
//		aliveNodes[Q].addJSubTree(nodeId);
//
//		int P=aliveNodes[Q].Q;
//		while(P!=-1){
//			aliveNodes[P].addJSubTree(nodeId);
//			P=aliveNodes[P].Q;
//		}
//
//
//		prohibitedProviderList.remove(nodeId);
//		for(it=J.begin();it!=J.end();it++){
//			prohibitedProviderList.remove(*it);
//			xSet.push_back(*it);
//		}
//
//		for(int i=0;i<activeNodes;i++)
//			if(i!=nodeId && !isPresentInCustomerTree(i) && !isPresentInList(prohibitedProviderList,i))
//				restSet.push_back(i);
//
//		for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
//			if(*itRest!=Q)
//				establishFlowPeering(nodeId,*itRest,Q);
//
//		for(itX=xSet.begin();itX!=xSet.end();itX++)
//			for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
//				establishFlowPeering(*itX,*itRest,aliveNodes[*itX].Q);
//
//		return true;
//
//	}
//
//	return false;
//	*/
//}
//
//
//bool Node::considerPeeringRequest(int id){
//
//	if((V/aliveNodes[id].V)<=peerCriteria)
//		return true;
//	else
//		return false;
//
//}
//
//
//bool Node::isPresentInProviderChain(int id){
//
//	int p;
//
//	if(Q==-1 || isPresentInCustomerTree(id) || id==nodeId)
//		return false;
//
//	else if(id==Q)
//		return true;
//
//	else{
//		p=aliveNodes[Q].Q;
//
//		while(p!=-1){
//
//			if(id==p)
//				return true;
//			p=aliveNodes[p].Q;
//		}
//
//		return false;
//	}
//
//}
//
//
//void Node::reborn(){
//
//	bool nodeDropped=false;
//	numGPresence=zipf(sZetaGeography,maxRegions*maxRegions);
//	Coordinate nodeLocation;
//	lifeStatus=alive;
//	newborn=true;
//
//
//	while(nodeDropped==false){
//
//		nodeLocation.xCoordinate=rand()%maxRegions;
//		nodeLocation.yCoordinate=rand()%maxRegions;
//
//		if(geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].population==0 || geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].population>=maxD){
//			continue;
//		}
//
//		else{
//			gPresence.push_back(nodeLocation);
//			nodeDropped=true;
//			break;
//		}
//
//	}//end while
//
//	geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].nodePresent.push_back(nodeId);
//	geography[nodeLocation.xCoordinate][nodeLocation.yCoordinate].population++;
//
//	//expand the node to its allowed expanse
//	if(numGPresence>1){
//		expandNodeRandom(nodeLocation,aliveNodes[nodeId]);
//	}
//
//	trafficGenerated=zipf(sZetaGeography,static_cast<int>(totalTraffic))+rand()%30;
//
//	if(priceDependancy==0)
//		price=rand()%(maxRegions*maxRegions)+1+(static_cast<double>(rand()%1000)/1000);
//	else
//		price=numGPresence+(static_cast<double>(rand()%1000)/1000);
//}
//
//void Node::die(){
//
//	/*
//	//end all links and flows for this node
//	if(!K.empty()){ //node is Tier 1
//
//		list<int>::iterator it;
//
//		for(it=K.begin();it!=K.end();it++)
//			aliveNodes[*it].K.remove(nodeId);
//
//	}
//
//	if(isPresentInList(Tier1,nodeId))
//		Tier1.remove(nodeId);
//
//	if(Q!=-1){
//
//		aliveNodes[Q].removeICustomer(nodeId);
//		aliveNodes[Q].removeJSubTree(nodeId);
//		int P=aliveNodes[Q].Q;
//		while(P!=-1){
//
//			aliveNodes[P].removeJSubTree(nodeId);
//			P=aliveNodes[P].Q;
//		}
//
//	}
//
//	if(!I.empty()){
//
//		npPair npOrphan;
//		list<int>::iterator it;
//		for(it=I.begin();it!=I.end();it++){
//			aliveNodes[*it].Q=-1;
//			aliveNodes[*it].orphan=true;
//			npOrphan.nId=*it;
//			npOrphan.trafficVolume=aliveNodes[*it].Vt;
//			orphanList.push_back(npOrphan);
//		}
//
//	}
//
//	//end all existing links
//	for(int j=0;j<activeNodes;j++)
//		if(j!=nodeId && linkIndex[nodeId][j].index!=-1)
//			endLink(nodeId,j);
//
//	//end all existing flows
//	for(int j=0;j<activeNodes;j++)
//		if(j!=nodeId)
//			endFlow(nodeId,j);
//
//	//end flows of its entire customer tree with everyone else
//	if(!I.empty()){
//
//		list<int> customerSet;
//		list<int> restSet;
//		list<int>::iterator itCustomer;
//		list<int>::iterator itRest;
//
//		for(itCustomer=J.begin();itCustomer!=J.end();itCustomer++){
//			customerSet.push_back(*itCustomer);
//			prohibitedProviderList.push_back(*itCustomer);
//		}
//
//		for(int i=0;i<activeNodes;i++)
//			if(i!=nodeId && !isPresentInCustomerTree(i))
//				restSet.push_back(i);
//
//		for(itCustomer=customerSet.begin();itCustomer!=customerSet.end();itCustomer++)
//			for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
//				endFlow(*itCustomer,*itRest);
//
//		customerSet.clear();
//		restSet.clear();
//
//		list<npPair>::iterator itNP;
//
//		for(itNP=orphanList.begin();itNP!=orphanList.end();itNP++){
//
//			cout<<"Came here"<<endl;
//
//			customerSet.clear();
//			restSet.clear();
//
//			for(itCustomer=aliveNodes[(*itNP).nId].J.begin();itCustomer!=aliveNodes[(*itNP).nId].J.end();itCustomer++)
//				customerSet.push_back(*itCustomer);
//			customerSet.push_back((*itNP).nId);
//
//			for(int i=0;i<activeNodes;i++)
//				if(!isPresentInList(customerSet,i))
//					restSet.push_back(i);
//
//			for(itCustomer=customerSet.begin();itCustomer!=customerSet.end();itCustomer++)
//				for(itRest=restSet.begin();itRest!=restSet.end();itRest++)
//					endFlow(*itCustomer,*itRest);
//
//			cout<<"And then came here"<<endl;
//		}
//
//	}
//
//	prohibitedProviderList.push_back(nodeId);
//
//	price=providerPrice=0;
//	Vo=Vp=Vc=Vt=V=Vpp=0;
//	Q=-1;
//	lifeStatus=dead;
//	newborn=false;
//	I.clear();
//	J.clear();
//	K.clear();
//
//	list<Coordinate>::iterator itC;
//	int x;
//	int y;
//
//	for(itC=gPresence.begin();itC!=gPresence.end();itC++){
//
//		x=(*itC).xCoordinate;
//		y=(*itC).yCoordinate;
//
//		geography[x][y].population--;
//		geography[x][y].nodePresent.remove(nodeId);
//
//	}
//
//	gPresence.clear();
//	numGPresence=0;
//	classification=Stub;
//	customerVPList.clear();
//
//	//clear its traffic matrix entries
//	for(int i=0;i<activeNodes;i++)
//		if(i!=nodeId)
//			trafficMatrix[nodeId][i]=0;
//
//	for(int j=0;j<activeNodes;j++)
//		if(j!=nodeId)
//			trafficMatrix[j][nodeId]=0;
//
//	*/
//}
//
//int findNumSPPLinks(){
//
//	numSPPLinks=0;
//	list<int>::iterator it;
//
//
//	for(int i=0;i<activeNodes;i++)
//		if(!aliveNodes[i].I.empty() && !aliveNodes[i].K.empty()){
//
//				for(it=aliveNodes[i].K.begin();it!=aliveNodes[i].K.end();it++){
//					if(aliveNodes[*it].Q!=-1 && aliveNodes[*it].I.empty() && aliveNodes[*it].isMajorContentNet==false)
//						numSPPLinks++;
//				}
//
//		}
//
//	return numSPPLinks;
//
//}
//
//void printPeeringLinkClassification(int numSimulations){
//
//	double linkClass[15]={0};
//	double trafficClass[15]={0};
//	double totalLinks=0;
//	double totalTraffic=0;
//
//	ofstream file1;
//	file1.open("linkClass1.txt",ios::out | ios::app);
//
//	ofstream file3;
//	file3.open("trafficClass1.txt",ios::out | ios::app);
//
//	for(int i=0;i<(activeNodes-1);i++){
//		for(int j=i+1;j<activeNodes;j++){
//
//			if(aliveNodes[i].isPeer(j)){
//
//				totalLinks++;
//				totalTraffic+=linkValueVector[linkIndex[i][j].index];
//
//				if(!aliveNodes[i].I.empty() && !aliveNodes[j].I.empty()){
//					linkClass[0]++;
//					trafficClass[0]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else if((!aliveNodes[i].I.empty() && aliveNodes[j].isCP==true) || (!aliveNodes[j].I.empty() && aliveNodes[i].isCP==true)){
//					linkClass[1]++;
//					trafficClass[1]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else if((!aliveNodes[i].I.empty() && aliveNodes[j].isCC==true) || (!aliveNodes[j].I.empty() && aliveNodes[i].isCC==true)){
//					linkClass[2]++;
//					trafficClass[2]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else if((!aliveNodes[i].I.empty() && aliveNodes[j].I.empty()) || (!aliveNodes[j].I.empty() && aliveNodes[i].I.empty())){
//					linkClass[3]++;
//					trafficClass[3]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else if((aliveNodes[i].isCP==true && aliveNodes[j].isCP==true)){
//					linkClass[4]++;
//					trafficClass[4]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else if((aliveNodes[i].isCP==true && aliveNodes[j].isCC==true) || (aliveNodes[j].isCP==true && aliveNodes[i].isCC==true)){
//					linkClass[5]++;
//					trafficClass[5]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else if((aliveNodes[i].isCP==true && aliveNodes[j].I.empty()) || (aliveNodes[j].isCP==true && aliveNodes[i].I.empty())){
//					linkClass[6]++;
//					trafficClass[6]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else if((aliveNodes[i].isCC==true && aliveNodes[j].isCC==true)){
//					linkClass[7]++;
//					trafficClass[7]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else if((aliveNodes[i].isCC==true && aliveNodes[j].I.empty()) || (aliveNodes[j].isCC==true && aliveNodes[i].I.empty())){
//					linkClass[8]++;
//					trafficClass[8]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else if(aliveNodes[i].I.empty() && aliveNodes[j].I.empty()){
//					linkClass[9]++;
//					trafficClass[9]+=linkValueVector[linkIndex[i][j].index];
//				}
//
//				else{
//
//				}
//
//
//			}
//
//		}
//
//	}
//
//	for(int i=0;i<10;i++){
//
//		if(numSimulations==1){
//			file1<<linkClass[i]/totalLinks<<"\t";
//			file3<<trafficClass[i]/totalTraffic<<"\t";
//		}
//
//	}
//
//	file1<<endl;
//	file3<<endl;
//}
//
///*************************************************************************************
///*************************************************************************************
// */
//
//double sumG(){
//
//	static double sum=0;
//
//	if(sum==0)
//		for(int i=0;i<activeNodes;i++)
//			sum+=aliveNodes[i].numGPresence;
//
//	return sum;
//}
//
//bool validateInitialization(){
//
//	/*
//	 * 1- Check if only init nodes are active
//	 * 2- Check if all active nodes have traffic, geography, price assigned
//	 * 3- Check the status of all flows
//	 * 4- Check if Tier1-s are properly connected
//	 * 5- Check if network is connected
//	 */
//
//	int numActiveNodes=0;
//	list<int>::iterator it1;
//	list<int>::iterator it2;
//
//	for(int i=0;i<maxNodes;i++)
//		if(aliveNodes[i].lifeStatus==alive)
//			numActiveNodes++;
//
//	if(!numActiveNodes==(initNodes-1)){
//		string str="ERROR!! Number of active nodes exceeds number of initNodes in initialization";
//		endSimulation(str);
//	}
//
//	for(int i=0;i<activeNodes;i++){
//
//		if(aliveNodes[i].trafficGenerated==0 || aliveNodes[i].trafficConsumed==0 || aliveNodes[i].V==0 || aliveNodes[i].Vo==0 || (aliveNodes[i].Vo!=(aliveNodes[i].trafficConsumed + aliveNodes[i].trafficGenerated))){
//			cout<<"Node "<<i<<" traffic has a problem"<<endl;
//			string str="ERROR!! Traffic not properly initialized in initialization";
//			endSimulation(str);
//		}
//
//	}
//
//	checkConnectivity();
//}
//
//double measurePeeringTraffic();
//double measureT1PeeringTraffic();
//double estimateTrafficExchange(int,int);
//double measureNT1VtTrafficFraction();
//double measureT1VtTrafficFraction();
//
//
//#endif /* STATISTICS_H_ */
