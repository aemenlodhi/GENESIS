/*
 * netManage.cpp
 *
 *  Created on: May 23, 2013
 *      Author: aemen
 */

#include "initialization.h"


bool netDisconnected;
long int populationSeed;
long int playOrderSeed;
long int initialTopologySeed;
unsigned int numLinks;
unsigned int numFlows;
unsigned int maxIterations;


list<unsigned int> nodeOrder;
list<unsigned int> nodeOrderBackup;


//functions used to manage the network initially, and later. save and restore network etc.
//check for disconnections etc.

void saveNetworkState(){

	Node::Tier1Save.clear();
	Node::Tier1Save=Node::Tier1;

	std::copy(aliveNodes,aliveNodes+Node::activeNodes,aliveNodesSave);

	std::copy(routingMatrix,routingMatrix+maxFlows,routingMatrixSave);
	std::copy(routingMatrixAsym,routingMatrixAsym+maxFlows,routingMatrixAsymSave);
	std::copy(flowValueVector,flowValueVector+maxFlows,flowValueVectorSave);
	std::copy(flowValueVectorAsym,flowValueVectorAsym+maxFlows,flowValueVectorAsymSave);
	std::copy(flowDirectionFrom,flowDirectionFrom+maxFlows,flowDirectionFromSave);
	std::copy(flowDirectionFromAsym,flowDirectionFromAsym+maxFlows,flowDirectionFromAsymSave);
	std::copy(aliveFlowIndicator,aliveFlowIndicator+maxFlows,aliveFlowIndicatorSave);

	std::copy(aliveLinkIndicator,aliveLinkIndicator+maxLinks,aliveLinkIndicatorSave);
	std::copy(linkValueVector,linkValueVector+maxLinks,linkValueVectorSave);
	std::copy(linkValueVectorUpstream,linkValueVectorUpstream+maxLinks,linkValueVectorUpstreamSave);
	std::copy(linkValueVectorDownstream,linkValueVectorDownstream+maxLinks,linkValueVectorDownstreamSave);
	std::copy(linkValueVectorFlat,linkValueVectorFlat+maxLinks,linkValueVectorFlatSave);

	for(unsigned int i=0;i<Node::activeNodes;i++)
		for(unsigned int j=0;j<Node::activeNodes;j++){
			flowIndexSave[i][j]=flowIndex[i][j];
			linkIndexSave[i][j]=linkIndex[i][j];
		}

}

void restoreNetworkState(){

	Node::Tier1.clear();
	Node::Tier1=Node::Tier1Save;


	std::copy(aliveNodesSave,aliveNodesSave+Node::activeNodes,aliveNodes);

	std::copy(routingMatrixSave,routingMatrixSave+maxFlows,routingMatrix);
	std::copy(routingMatrixAsymSave,routingMatrixAsymSave+maxFlows,routingMatrixAsym);
	std::copy(flowValueVectorSave,flowValueVectorSave+maxFlows,flowValueVector);
	std::copy(flowValueVectorAsymSave,flowValueVectorAsymSave+maxFlows,flowValueVectorAsym);
	std::copy(flowDirectionFromSave,flowDirectionFromSave+maxFlows,flowDirectionFrom);
	std::copy(flowDirectionFromAsymSave,flowDirectionFromAsymSave+maxFlows,flowDirectionFromAsym);
	std::copy(aliveFlowIndicatorSave,aliveFlowIndicatorSave+maxFlows,aliveFlowIndicator);

	std::copy(aliveLinkIndicatorSave,aliveLinkIndicatorSave+maxLinks,aliveLinkIndicator);
	std::copy(linkValueVectorSave,linkValueVectorSave+maxLinks,linkValueVector);
	std::copy(linkValueVectorUpstreamSave,linkValueVectorUpstreamSave+maxLinks,linkValueVectorUpstream);
	std::copy(linkValueVectorDownstreamSave,linkValueVectorDownstreamSave+maxLinks,linkValueVectorDownstream);
	std::copy(linkValueVectorFlatSave,linkValueVectorFlatSave+maxLinks,linkValueVectorFlat);

	for(unsigned int i=0;i<Node::activeNodes;i++)
		for(unsigned int j=0;j<Node::activeNodes;j++){
			flowIndex[i][j]=flowIndexSave[i][j];
			linkIndex[i][j]=linkIndexSave[i][j];
		}

}

void assignInitialLocations(unsigned int maxlocs, unsigned int maxpops, unsigned int minpops, double sZetaGeography){

	int* y=new int[maxpops+1];
	double* PYy=new double[maxpops+1];
	double* gy=new double[maxpops+1];
	double harmonicSum=0;
	list<geoIndexPair>::iterator itGeo;
	list<geoIndexPair> geoIndexList;
	unsigned int nodeLocation;
	bool nodeDropped=false;

	int tempInt=-1;
	list<int> gPresenceList;

	for(unsigned int i=1;i<=maxpops;i++){
		harmonicSum+=(1/pow(i,sZetaGeography));
		y[i]=i;
	}

	for(unsigned int i=1;i<=maxpops;i++){

		PYy[i]=(1/pow(i,sZetaGeography))/harmonicSum;
		gy[i]=round(Node::activeNodes*PYy[i]);

		for(int j=0;j<static_cast<int>(gy[i]);j++){
			gPresenceList.push_back(y[i]);
		}

	}

	while((tempInt=getNextNodeInOrder())!=-1 && !gPresenceList.empty()){

		aliveNodes[tempInt].numGPresence=gPresenceList.front()%maxpops;
		if(aliveNodes[tempInt].numGPresence==0)
			aliveNodes[tempInt].numGPresence=1;
		gPresenceList.pop_front();

	}

	int leftOver=0;
	//left over nodes if any
	for(unsigned int i=0;i<Node::activeNodes;i++){
		if(aliveNodes[i].numGPresence==0){
			leftOver++;
			aliveNodes[i].numGPresence=1;

		}
	}

	geoIndexList.clear();
	geoIndexPair giPair;
	int temp1;

	for(unsigned int i=0;i<Node::activeNodes;i++){

		giPair.index=i;
		giPair.numGPresence=aliveNodes[i].numGPresence;
		geoIndexList.push_back(giPair);
		temp1+=aliveNodes[i].numGPresence;


	}//end for creation of nodes

	//Assigning geography
	//Step 2b Expand the nodes
	geoIndexList.sort(sortReverseByNumGPresence);	//bigger nodes get regions first

	for(itGeo=geoIndexList.begin();itGeo!=geoIndexList.end();itGeo++){

		//first node can go to any region since initial population in geography is zero
		if(itGeo==geoIndexList.begin()){

			nodeLocation=rand()%Location::maxLocations;

			aliveNodes[(*itGeo).index].gPresence.push_back(nodeLocation);

		}

		else{

			while(nodeDropped==false){

				nodeLocation=rand()%Location::maxLocations;

				if(world[nodeLocation].population==0){
					continue;
				}

				else{
					aliveNodes[(*itGeo).index].gPresence.push_back(nodeLocation);
					aliveNodes[(*itGeo).index].isPresentAtLoc[nodeLocation]=true;
					nodeDropped=true;
					break;
				}

			}//end while

			nodeDropped=false;

		}//end else

		world[nodeLocation].nodePresent.push_back((*itGeo).index);
		world[nodeLocation].population++;

		//expand the node to its allowed expanse
		if((*itGeo).numGPresence>1){
			expandNodeRandom((*itGeo).index,nodeLocation);
		}

	}//end for

	delete []y;
	delete []PYy;
	delete []gy;

#if 0
	list<unsigned int> numPops;
	for(unsigned int i=0;i<Node::activeNodes;i++)
		numPops.push_back(aliveNodes[i].numGPresence);

	numPops.sort();
	double q=0;
	for(list<unsigned int>::iterator i=numPops.begin();i!=numPops.end();q++,i++)
		logFile<<q/numPops.size()<<"\t"<<*i<<endl;

#endif

}

void assignInitialTraffic(double zipfExponentTrafficGeneration, double zipfExponentTrafficConsumption, double maxTraffic, Traffic& tObj, long int initTopologySeed, long int popSeed){

	/*
	 * 1- Compute Generated traffic
	 * 2- Compute Consumed traffic
	 * 3- Compute traffic matrix
	 */

#if TRAFFICLOG
	char generatedTrafficFileName[100];
	char consumedTrafficFileName[100];
	char exchangedTrafficFileName[100];

	sprintf(generatedTrafficFileName,"generatedTraffic_%ld_%ld.txt",initTopologySeed,popSeed);
	sprintf(consumedTrafficFileName,"consumedTraffic_%ld_%ld.txt",initTopologySeed,popSeed);
	sprintf(exchangedTrafficFileName,"exchangedTraffic_%ld_%ld.txt",initTopologySeed,popSeed);

	ofstream gtFile, ctFile, etFile;
	gtFile.open(generatedTrafficFileName,ios::out);
	ctFile.open(consumedTrafficFileName,ios::out);
	etFile.open(exchangedTrafficFileName,ios::out);

#endif

	double harmonicSum=0;
	int temp=0;
	double tempD=0;
	double tempD2=0;
	list<double> trafficConsumptionFractions;
	geoIndexPair tmpPair;
	list<geoIndexPair> pairList;
	list<geoIndexPair>::iterator itPair;
	list<double>::iterator itDouble;

	//re-initialize traffic matrix
	for(unsigned int i=0;i<Node::activeNodes;i++)
		for(unsigned int j=0;j<Node::activeNodes;j++)
			tObj.trafficMatrix[i][j]=-1;


	//Calculating fractions for consumed traffic
	harmonicSum=0;
	tempD=0;
	double* tCon=new double[Node::activeNodes+1];
	for(unsigned int i=1;i<=Node::activeNodes;i++){
		harmonicSum+=(1/pow(i,zipfExponentTrafficConsumption));
	}

	for(unsigned int i=1;i<=Node::activeNodes;i++){
		tCon[i]=(1/pow(i,zipfExponentTrafficConsumption))/harmonicSum;
		tempD+=tCon[i];

		if(i>1 && (tCon[i]>tCon[i-1])){

			cout<<"ERROR in computing fractions for consumed traffic!! Fractions produced in wrong order"<<endl;
			//logFile<<"ERROR in computing fractions for consumed traffic!! Fractions produced in wrong order";

			string str="ERROR!! in initialization";
			endSimulation(str);

		}

	}

	if(tempD<0.98){	//not exact value of 1 used. tempD=0.99999999 Checked earlier.

		cout<<"ERROR in computing fractions for consumed traffic!! Fractions do not sum to 1"<<endl;
		//logFile<<"ERROR in computing fractions for consumed traffic!! Fractions do not sum to 1";

		string str="ERROR!! in initialization";
		endSimulation(str);
	}


	for(unsigned int i=0;i<Node::activeNodes;i++){
		tmpPair.index=i;
		tmpPair.numGPresence=aliveNodes[i].numGPresence;
		pairList.push_back(tmpPair);
	}

	pairList.sort(sortReverseByNumGPresence);

	temp=1;

	for(itPair=pairList.begin();itPair!=pairList.end();itPair++,temp++){
		aliveNodes[(*itPair).index].totalTrafficConsumedFraction=tCon[temp];

	}

	//compute total traffic in the network
	itPair=pairList.begin();

	tObj.totalTraffic=ceil(tObj.maxTraffic/aliveNodes[(*itPair).index].totalTrafficConsumedFraction);

#if DEBUG
	logFile<<"Total Traffic: "<<trafficObj.totalTraffic<<endl;
	logFile<<"Max consumed traffic fraction: "<<aliveNodes[(*itPair).index].totalTrafficConsumedFraction<<endl;
	logFile<<"Max Consumed traffic: "<<trafficObj.totalTraffic*aliveNodes[(*itPair).index].totalTrafficConsumedFraction<<endl;
#endif

	//calculation of generated traffic fractions
	harmonicSum=0;
	tempD=0;
	double* tGen=new double[Node::activeNodes+1];
	for(unsigned int i=1;i<=Node::activeNodes;i++){
		harmonicSum+=(1/pow(i,zipfExponentTrafficGeneration));
	}

	for(unsigned int i=1;i<=Node::activeNodes;i++){
		tGen[i]=(1/pow(i,zipfExponentTrafficGeneration))/harmonicSum;
		tempD+=tGen[i];

		if(i>1 && (tGen[i]>tGen[i-1])){

			cout<<"ERROR in computing fractions for generated traffic!! Fractions produced in wrong order"<<endl;
			//logFile<<"ERROR in computing fractions for generated traffic!! Fractions produced in wrong order";

			string str="ERROR!! in initialization";
			endSimulation(str);

		}

	}

	if(tempD<0.98){	//not exact value of 1 used. tempD=0.99999999 Checked earlier.

		cout<<"ERROR in computing fractions for generated traffic!! Fractions do not sum to 1"<<endl;
		//logFile<<"ERROR in computing fractions for generated traffic!! Fractions do not sum to 1";

		string str="ERROR!! in initialization";
		endSimulation(str);
	}

	temp=-1;
	tempD=0;
	tempD2=0;
	int maxIndex=0;

	for(unsigned int i=1;i<=Node::activeNodes;i++){

		temp=getNextNodeInOrder();
		if(temp>=0){
			aliveNodes[temp].totalTrafficGeneratedFraction=tGen[i];
			aliveNodes[temp].totalTrafficGenerated=ceil(tGen[i]*tObj.totalTraffic);
			tempD+=aliveNodes[temp].totalTrafficGenerated;

			if(aliveNodes[temp].totalTrafficGenerated>tempD2){
				tempD2=aliveNodes[temp].totalTrafficGenerated;
				maxIndex=temp;
			}

		}

	}

	if(tempD<trafficObj.totalTraffic){
		aliveNodes[maxIndex].totalTrafficGenerated+=(trafficObj.totalTraffic-tempD);

	}

	//just in case
	for(unsigned int i=0;i<Node::activeNodes;i++)
		if(aliveNodes[i].totalTrafficGenerated==0){
			cout<<"Something is wrong just in case used for traffic"<<endl;
			//logFile<<"Something is wrong just in case used for traffic"<<endl;
			aliveNodes[i].totalTrafficGenerated=rand()%15+1;
		}



	//computing traffic matrix
	for(unsigned int i=0;i<Node::activeNodes;i++){

		tempD=0;
		tempD2=tObj.totalTraffic*10;
		for(unsigned int j=0;j<Node::activeNodes;j++){

			if(i!=j){

				tObj.trafficMatrix[i][j]=ceil(aliveNodes[i].totalTrafficGenerated*aliveNodes[j].totalTrafficConsumedFraction);
				tempD+=ceil(aliveNodes[i].totalTrafficGenerated*aliveNodes[j].totalTrafficConsumedFraction);
				aliveNodes[j].totalTrafficConsumed+=ceil(aliveNodes[i].totalTrafficGenerated*aliveNodes[j].totalTrafficConsumedFraction);

				if(aliveNodes[j].totalTrafficConsumed<tempD2){
					temp=j;
					tempD2=aliveNodes[j].totalTrafficConsumed;

				}

			}

		}

		if((tempD2=aliveNodes[i].totalTrafficGenerated-tempD)>0){

			tObj.trafficMatrix[i][temp]+=tempD2;
			aliveNodes[temp].totalTrafficConsumed+=tempD2;

		}

	}

	//updating values
	for(unsigned int i=0;i<Node::activeNodes;i++){
		aliveNodes[i].totalTrafficGenerated=0;
		aliveNodes[i].totalTrafficConsumed=0;
	}


	for(unsigned int i=0;i<Node::activeNodes;i++)
		for(unsigned int j=0;j<Node::activeNodes;j++){
			if(i!=j){
				aliveNodes[i].totalTrafficGenerated+=tObj.trafficMatrix[i][j];
			}
		}

	for(unsigned int i=0;i<Node::activeNodes;i++)
		for(unsigned int j=0;j<Node::activeNodes;j++){
			if(i!=j){
				aliveNodes[i].totalTrafficConsumed+=tObj.trafficMatrix[j][i];

				aliveNodes[i].trafficSent[j]=tObj.trafficMatrix[i][j];
				aliveNodes[i].trafficReceived[j]=tObj.trafficMatrix[i][j];
			}

		}

	for(unsigned int i=0;i<Node::activeNodes;i++)
		aliveNodes[i].Vo=aliveNodes[i].totalTrafficGenerated+aliveNodes[i].totalTrafficConsumed;

	delete [] tCon;
	delete [] tGen;

#if TRAFFICLOG
	for(unsigned int i=0;i<Node::activeNodes;i++){
		gtFile<<aliveNodes[i].totalTrafficGeneratedFraction<<endl;
		ctFile<<aliveNodes[i].totalTrafficConsumedFraction<<endl;

		for(unsigned int j=i;j<Node::activeNodes;j++){
			if(i!=j){
				etFile<<aliveNodes[i].trafficSent[j]+aliveNodes[i].trafficReceived[j];
			}
		}
	}
#endif


}

void assignInitialPrices(bool classic,double maxPrice, double minPrice){

	list<unsigned int>::iterator it;

	if(!classic){
		for(unsigned int i=0;i<Location::maxLocations;i++){
			world[i].numProviders=0;
			for(it=world[i].nodePresent.begin();it!=world[i].nodePresent.end();it++)
				if(!aliveNodes[*it].I.empty())
					world[i].numProviders++;
		}

		for(unsigned int i=0;i<Location::maxLocations;i++)
			world[i].locationPrice=(0.0063*pow(static_cast<double>(world[i].numProviders),2)-8.6588*world[i].numProviders+2869.9)/25;
	}

	else{

		for(unsigned int i=0;i<Node::activeNodes;i++){

			for(unsigned int j=0;j<Location::maxLocations;j++){
				if(aliveNodes[i].isPresentAtLoc[j]){
					aliveNodes[i].transitPriceChart[j]=minPrice+rand()%static_cast<int>(maxPrice-minPrice)+(static_cast<double>(rand()%100)/100);

				}

				else
					aliveNodes[i].transitPriceChart[j]=0;
			}

		}

	}


#if 0

	for(unsigned int i=0;i<Node::activeNodes;i++){
		logFile<<i<<": ";
		for(list<unsigned int>::iterator it=aliveNodes[i].gPresence.begin();it!=aliveNodes[i].gPresence.end();it++){
			logFile<<aliveNodes[i].transitPriceChart[*it]<<"\t";
		}

		logFile<<endl;
	}

#endif

}

void expandNodeRandom(int nId, int originPoint){

	int presenceCounter=1;
	int temp;
	list<int>::iterator it;

	list<int> locToChoose;
	int tempCoordinate;

	for(unsigned int i=0;i<Location::maxLocations;i++){


			tempCoordinate=i;

			if((tempCoordinate==originPoint) || (Location::maxDensity!=-1 && static_cast<int>(world[tempCoordinate].population)>=Location::maxDensity)){}

			else
				locToChoose.push_back(tempCoordinate);

	}

	int pops=0;
	while(aliveNodes[nId].gPresence.size()<aliveNodes[nId].numGPresence){

		if(locToChoose.empty()){

			for(unsigned int y=0;y<Location::maxLocations;y++){
				cout<<"Loc nodes at "<<y<<" are "<<world[y].population<<endl;
				pops+=world[y].population;
			}

		}

		presenceCounter=rand()%locToChoose.size();
		temp=0;

		for(it=locToChoose.begin();it!=locToChoose.end();it++,temp++){

			if(temp==presenceCounter){
				aliveNodes[nId].gPresence.push_back(*it);
				aliveNodes[nId].isPresentAtLoc[*it]=true;
				world[*it].nodePresent.push_back(nId);
				world[*it].population++;

				locToChoose.erase(it);
				break;

			}//end if

		}//end for

	}//end while

	locToChoose.clear();

}

void formInitialTopology(long int initialTopologySeed,unsigned int initT1CliqueSize){

	//******************** Initial Topology formation *********************************
	unsigned int numProviderAssigned=0;	//variable to track how many nodes have been assigned provider

	geoIndexPair tempGeoPair;
	list<geoIndexPair> geoIndexList;
	list<geoIndexPair>::iterator itGeo;

	for(unsigned int i=0;i<Node::activeNodes;i++){
		tempGeoPair.index=i;
		tempGeoPair.numGPresence=aliveNodes[i].numGPresence;
		geoIndexList.push_back(tempGeoPair);
	}

	geoIndexList.sort(sortByNumGPresence);

	/*
	 * Assigning provider status to top 10% nodes by geographic size (Experiment only)
	 */
	//TODO Remove experimental stuff from initialization
	double temp=0;
	for(list<geoIndexPair>::reverse_iterator itR=geoIndexList.rbegin();itR!=geoIndexList.rend();itR++){
		aliveNodes[(*itR).index].canBeProvider=true;
		temp++;

		if(static_cast<double>(temp/INIT_NODES)>=0.1){
			cout<<"Number of providers "<<temp<<endl;
			break;
		}
	}
	//*****************************************************************

	for(itGeo=geoIndexList.begin();itGeo!=geoIndexList.end();itGeo++){

		if(PEERING==true && (Node::activeNodes-numProviderAssigned)==initT1CliqueSize)
			break;

		//cout<<"Assigning provider to "<<(*itGeo).index<<endl;

		if(aliveNodes[(*itGeo).index].getInitialProviderRand()){
			numProviderAssigned++;

		}

	}

	//TODO Ideally you should check this condition but for this experiment we are ignoring it
	/*if(numProviderAssigned<(Node::activeNodes-initT1CliqueSize)){

		//logFile<<"Providers not properly assigned"<<endl;
		string str="ERROR!! Error in assignment of providers in initialization";
		endSimulation(str);
	}*/

	NodePrice ownInfo;
	NodePrice peerInfo;
	for(unsigned int m=0;m<Node::activeNodes;m++){

		if(aliveNodes[m].Q.empty()){

			for(unsigned int n=0;n<Node::activeNodes;n++){

				if(m!=n && aliveNodes[n].Q.empty() && !aliveNodes[m].isPeer(n)){

					ownInfo.nId=m;
					ownInfo.price=0;

					peerInfo.nId=n;
					peerInfo.price=0;

					aliveNodes[m].insertPeerInK(peerInfo);
					aliveNodes[n].insertPeerInK(ownInfo);

					establishLinkWithPeer(m,n,false);
					establishFlowWithPeer(m,n);


				}//end if

			}//end for

			Node::Tier1.push_back(m);

		}//end if


	}//end for

	//Step 5- updating routing matrices
	for(unsigned int i=0;i<(Node::activeNodes-1);i++){

		for(unsigned int j=i+1;j<Node::activeNodes;j++){

			if(flowIndex[i][j]==-1){

				establishFlowBetweenNonLinkedNodes(i,j);

			}

		}

	}//end for


}

void permute(bool reorder,long int seed){	//set seed to -1 to fill nodeOrder in order of ids

	list<unsigned int>::iterator it;
	if(reorder==true){	//refill the order list randomly subject to seed

		if(seed!=-1){
			srand(seed);
			unsigned int tempInt;
			nodeOrder.clear();
			nodeOrderBackup.clear();
			while(nodeOrder.size()<Node::activeNodes){
				tempInt=rand()%Node::activeNodes;
				if(!isPresentInList<unsigned int>(nodeOrder,tempInt)){
					nodeOrder.push_back(tempInt);
					nodeOrderBackup.push_back(tempInt);
				}
			}

		}//if orders to be randomly filled

		else{	//to be filled in order of id

			nodeOrder.clear();
			nodeOrderBackup.clear();

			for(unsigned int i=0;i<Node::activeNodes;i++){
				nodeOrder.push_back(i);
				nodeOrderBackup.push_back(i);

			}

		}

	}

	else{	//just refill the order list

		nodeOrder.clear();
		for(it=nodeOrderBackup.begin();it!=nodeOrderBackup.end();it++){
			nodeOrder.push_back(*it);
		}

	}

#if 0
	for(list<unsigned int>::iterator it=nodeOrder.begin();it!=nodeOrder.end();it++)
		cout<<*it<<endl;
	cout<<endl;
#endif

}

void paramReader(char* fileName){

	ifstream readFile;
	readFile.open(fileName);
	string str;
	while(readFile){
		getline(readFile,str);
		if(!str.empty()){
			vector<string> v = splitString(str,":");

			if(!v.empty()){
				if(v[0]=="PEERING"){
					if(v[1]=="TRUE")
						PEERING=true;
					else
						PEERING=false;
				}

				else if(v[0]=="PRIVATE_PEERING"){
					if(v[1]=="TRUE")
						PRIVATE_PEERING=true;
					else
						PRIVATE_PEERING=false;
				}

				else if(v[0]=="PAID_PEERING"){
					if(v[1]=="TRUE")
						PAID_PEERING=true;
					else
						PAID_PEERING=false;
				}

				else if(v[0]=="PRIVATE_PEERING_THRESHOLD"){
					PRIVATE_PEERING_THRESHOLD=atof(v[1].c_str());
				}

				else if(v[0]=="UNIVERSAL_SIGMA"){
					UNIVERSAL_SIGMA=atof(v[1].c_str());
				}

				else if(v[0]=="DOMINANTDIRECTIONBILLING"){
					if(v[1]=="TRUE")
						DOMINANTDIRECTIONBILLING=true;
					else
						DOMINANTDIRECTIONBILLING=false;
				}

				else if(v[0]=="COMPETITIVE_PRICING"){
					if(v[1]=="TRUE")
						COMPETITIVE_PRICING=true;
					else
						COMPETITIVE_PRICING=false;
				}

				else if(v[0]=="MAX_TRANSIT_PRICE"){
					MAX_TRANSIT_PRICE=atof(v[1].c_str());
				}

				else if(v[0]=="MIN_TRANSIT_PRICE"){
					MIN_TRANSIT_PRICE=atof(v[1].c_str());
				}

				else if(v[0]=="UNIVERSAL_PEERING_PRICE"){
					UNIVERSAL_PEERING_PRICE=atof(v[1].c_str());
				}

				else if(v[0]=="TRANSIT_COST_EXPONENT"){
					TRANSIT_COST_EXPONENT=atof(v[1].c_str());
				}

				else if(v[0]=="PEERING_COST_EXPONENT"){
					PEERING_COST_EXPONENT=atof(v[1].c_str());
				}

				else if(v[0]=="MAX_NODES"){
					MAX_NODES=atoi(v[1].c_str());
				}

				else if(v[0]=="INIT_NODES"){
					INIT_NODES=atoi(v[1].c_str());
				}

				else if(v[0]=="MAX_LOCATIONS"){
					MAX_LOCATIONS=atoi(v[1].c_str());
				}

				else if(v[0]=="MIN_POPS"){
					MIN_POPS=atoi(v[1].c_str());
				}

				else if(v[0]=="MAX_POPS"){
					MAX_POPS=atoi(v[1].c_str());
				}

				else if(v[0]=="ZIPF_PARAM_GEO_EXPANSE"){
					ZIPF_PARAM_GEO_EXPANSE=atof(v[1].c_str());
				}

				else if(v[0]=="MEAN_CONSUMED_TRAFFIC"){
					MEAN_CONSUMED_TRAFFIC=atof(v[1].c_str());
				}

				else if(v[0]=="ZIPF_PARAM_GENERATED_TRAFFIC"){
					ZIPF_PARAM_GENERATED_TRAFFIC=atof(v[1].c_str());
				}

				else if(v[0]=="ZIPF_PARAM_CONSUMED_TRAFFIC"){
					ZIPF_PARAM_CONSUMED_TRAFFIC=atof(v[1].c_str());
				}

				else if(v[0]=="MULTIHOMING_DEGREE"){
					MULTIHOMING_DEGREE=atoi(v[1].c_str());
				}

				else if(v[0]=="MAX_ROUNDS"){
					MAX_ROUNDS=atoi(v[1].c_str());
				}

				else if(v[0]=="INITIAL_T1_CLIQUE_SIZE"){
					INITIAL_T1_CLIQUE_SIZE=atoi(v[1].c_str());
				}

				else if(v[0]=="MAX_TRAFFIC"){
					MAX_TRAFFIC=atof(v[1].c_str());
				}

				else if(v[0]=="MIN_PORT_CAPACITY"){
					MIN_PORT_CAPACITY=atof(v[1].c_str());
				}

				else if(v[0]=="PORT_PRICE"){
					PORT_PRICE=atof(v[1].c_str());
				}

				else if(v[0]=="ONE_G_PORT_PRICE"){
					ONE_G_PORT_PRICE=atof(v[1].c_str());
				}

				else if(v[0]=="TEN_G_PORT_PRICE"){
					TEN_G_PORT_PRICE=atof(v[1].c_str());
				}

				else if(v[0]=="HUNDRED_G_PORT_PRICE"){
					HUNDRED_G_PORT_PRICE=atof(v[1].c_str());
				}

				else if(v[0]=="TRANSIT_PRICE_100MBPS"){
					TRANSIT_PRICE_100MBPS=atof(v[1].c_str());
				}

				else if(v[0]=="TRANSIT_PRICE_1GBPS"){
					TRANSIT_PRICE_1GBPS=atof(v[1].c_str());
				}

				else if(v[0]=="TRANSIT_PRICE_10GBPS"){
					TRANSIT_PRICE_10GBPS=atof(v[1].c_str());
				}

				else if(v[0]=="TRANSIT_PRICE_100GBPS"){
					TRANSIT_PRICE_100GBPS=atof(v[1].c_str());
				}

				else if(v[0]=="IXP_PEERING"){
					if(v[1]=="TRUE")
						IXP_PEERING=true;
					else
						IXP_PEERING=false;
				}

				else if(v[0]=="CONFIDENCE_FACTOR_ESTIMATION"){
					CONFIDENCE_FACTOR_ESTIMATION=atof(v[1].c_str());
				}

				else{
					string str="ERROR!!! Unknown global parameter ";
					string str2=v[0];
					string str3=" encountered in parameter database";
					str.append(str2);
					str.append(str3);
					endSimulation(str);
				}

			}

		}

	}

}

void initialize(bool readLog, char* paramFile, long int popSeed, long int initTopSeed){	//initialize the simulation

	//1- create data structures and initialize variables
	//2- initialize nodes
	//3- assign geography to nodes
	//4- assign traffic to nodes
	//5- assign prices to nodes
	//6- determine overlaps
	//7- create initial topology

#if DEBUG
	logFile<<"Initializing network readLog: "<<readLog<<" parameterFile: "<<paramFile<<" populationSeed: "<<popSeed<<" initialTopologySeed: "<<initTopSeed<<endl;
#endif

	paramReader(paramFile);

	//setting population seed for creation of node population

	//******************************** Initializing Routing data structures ****************************

	Node::maxNodes=MAX_NODES;
	Node::initNodes=INIT_NODES;
	Node::activeNodes=INIT_NODES;
	Node::universalSigma=UNIVERSAL_SIGMA;
	trafficObj.maxTraffic=MAX_TRAFFIC;
	trafficObj.meanConsumedTraffic=MEAN_CONSUMED_TRAFFIC;
	Location::maxLocations=MAX_LOCATIONS;
	Location::maxPops=MAX_POPS;
	Location::minPops=MIN_POPS;

	maxFlows=static_cast<unsigned int>(ceil((Node::maxNodes*(Node::maxNodes-1))/2));
	//maxLinks=Node::maxNodes-1;
	maxLinks=maxFlows;

	routingMatrix=new list<flowInfo>[maxFlows];

	routingMatrixAsym=new list<flowInfo>[maxFlows];

	flowIndex=new int*[Node::maxNodes];

	for(unsigned int i=0;i<Node::maxNodes;i++){
		flowIndex[i]=new int[Node::maxNodes];

	}

	for(unsigned int i=0;i<Node::maxNodes;i++)
		for(unsigned int j=0;j<Node::maxNodes;j++){
			flowIndex[i][j]=-1;

		}

	flowValueVector=new double[maxFlows];

	flowValueVectorAsym=new double[maxFlows];

	for(unsigned int i=0;i<maxFlows;i++){
		flowValueVector[i]=0;
		flowValueVectorAsym[i]=0;


	}

#if EXPERIMENT
	numFlowsOverLink=new unsigned int[maxLinks];
#endif

	linkValueVector=new double[maxLinks];


	linkValueVectorUpstream=new double[maxLinks];


	linkValueVectorDownstream=new double[maxLinks];


	linkValueVectorFlat=new double[maxLinks];


	linkValueVectorFlatLeft=new double[maxLinks];


	linkValueVectorFlatRight=new double[maxLinks];


	aliveLinkIndicator=new bool[maxLinks];


	for(unsigned int i=0;i<maxLinks;i++){
		linkValueVector[i]=0;
		linkValueVectorUpstream[i]=0;
		linkValueVectorDownstream[i]=0;
		linkValueVectorFlat[i]=0;
		aliveLinkIndicator[i]=0;
	}

	aliveFlowIndicator=new bool[maxFlows];


	flowDirectionFrom=new unsigned int[maxFlows];


	flowDirectionFromAsym=new unsigned int[maxFlows];


	for(unsigned int i=0;i<maxFlows;i++){
		freeFlowIndices.push_back(i);
		aliveFlowIndicator[i]=0;
		flowDirectionFrom[i]=-1;
		flowDirectionFromAsym[i]=-1;
	}

	linkIndex=new linkInfo*[Node::maxNodes];


	for(unsigned int i=0;i<Node::maxNodes;i++){
		linkIndex[i]=new linkInfo[Node::maxNodes];

	}

	for(unsigned int i=0;i<Node::maxNodes;i++)
		for(unsigned int j=0;j<Node::maxNodes;j++){
			linkIndex[i][j].index=-1;
			linkIndex[i][j].provider=-1;
			linkIndex[i][j].linkClass=CPLink;
		}

	trafficObj.trafficMatrix=new double*[Node::maxNodes];
	for(unsigned int i=0;i<Node::maxNodes;i++)
		trafficObj.trafficMatrix[i]=new double[Node::maxNodes];

	for(unsigned int i=0;i<Node::maxNodes;i++)
		for(unsigned int j=0;j<Node::maxNodes;j++)
			trafficObj.trafficMatrix[i][j]=0;

	world=new Location[Location::maxLocations];

	aliveNodes=new Node[Node::maxNodes];


	for(unsigned int i=0;i<Node::maxNodes;i++){

		aliveNodes[i].multihomingDegree=MULTIHOMING_DEGREE;
		aliveNodes[i].iCustomer.assign(Node::maxNodes,false);
		aliveNodes[i].jCustomer.assign(Node::maxNodes,false);
		aliveNodes[i].qProvider.assign(Node::maxNodes,false);
		aliveNodes[i].isPresentAtLoc.assign(Location::maxLocations,false);
		aliveNodes[i].transitPriceChart.assign(Location::maxLocations,0);
		aliveNodes[i].paidPeeringPriceChart.assign(Location::maxLocations,0);
		aliveNodes[i].kPeer.assign(Node::maxNodes,false);
		aliveNodes[i].privatePeeringThreshold=PRIVATE_PEERING_THRESHOLD;
		aliveNodes[i].nodeId=i;
		aliveNodes[i].selectivePeerCriteria=Node::universalSigma;
	}

	for(unsigned int i=0;i<Node::maxNodes;i++)
		Node::nodePointers.push_back(&aliveNodes[i]);

	if(readLog){	//read network from an existing initialization log instead of creating a new network
		//write code to read network from log

#if DEBUG
		logFile<<"Reading initial network from initialNetworkLog"<<endl;
#endif
	}

	else{

		//Assigning locations to nodes
		permute(true,popSeed);
		assignInitialLocations(MAX_LOCATIONS,MAX_POPS,MIN_POPS,ZIPF_PARAM_GEO_EXPANSE);

		//assigning traffic to nodes
		permute(false,-1);
		assignInitialTraffic(ZIPF_PARAM_GENERATED_TRAFFIC,ZIPF_PARAM_CONSUMED_TRAFFIC,MEAN_CONSUMED_TRAFFIC,trafficObj,initTopSeed,popSeed);

		//assign prices to nodes
		permute(false,-1);
		assignInitialPrices(true,MAX_TRANSIT_PRICE,MIN_TRANSIT_PRICE);	//assign prices in a classical way

		for(unsigned int i=0;i<Node::activeNodes;i++)
			aliveNodes[i].populateColocationList();

#if 0
		for(unsigned int i=0;i<Node::activeNodes;i++){
			logFile<<i<<": ";
			for(multimap<unsigned int,NodePrice>::iterator it=aliveNodes[i].colocatedNodePrice.begin();it!=aliveNodes[i].colocatedNodePrice.end();it++){
				logFile<<"("<<(*it).first<<","<<(*it).second.nId<<","<<(*it).second.price<<")\t";
			}
			logFile<<endl;
		}

#endif

		//create initial topology
		permute(true,initTopSeed);
		formInitialTopology(initialTopologySeed,INITIAL_T1_CLIQUE_SIZE);

	}

}//end initialization

int getNextNodeInOrder(){

	int tempInt;

	if(!nodeOrder.empty()){
		tempInt=nodeOrder.front();
		nodeOrder.pop_front();
		return tempInt;
	}

	else
		return -1;
}

void allocateSpaceForBackup(){

	routingMatrixSave=new list<flowInfo>[maxFlows];
	routingMatrixAsymSave=new list<flowInfo>[maxFlows];
	flowIndexSave=new int*[Node::maxNodes];

	for(unsigned int i=0;i<Node::maxNodes;i++){

		flowIndexSave[i]=new int[Node::maxNodes];
	}

	for(unsigned int i=0;i<Node::maxNodes;i++)
		for(unsigned int j=0;j<Node::maxNodes;j++){

			flowIndexSave[i][j]=-1;
		}

	flowValueVectorSave=new double[maxFlows];
	flowValueVectorAsymSave=new double[maxFlows];

	for(unsigned int i=0;i<maxFlows;i++){

		flowValueVectorSave[i]=0;

		flowValueVectorAsymSave[i]=0;
	}

	linkValueVectorSave=new double[maxLinks];
	linkValueVectorUpstreamSave=new double[maxLinks];
	linkValueVectorDownstreamSave=new double[maxLinks];
	linkValueVectorFlatSave=new double[maxLinks];
	linkValueVectorFlatLeftSave=new double[maxLinks];
	linkValueVectorFlatRightSave=new double[maxLinks];
	aliveLinkIndicatorSave=new bool[maxLinks];
	aliveFlowIndicatorSave=new bool[maxFlows];
	flowDirectionFromSave=new unsigned int[maxFlows];
	flowDirectionFromAsymSave=new unsigned int[maxFlows];
	linkIndexSave=new linkInfo*[Node::maxNodes];

	for(unsigned int i=0;i<Node::maxNodes;i++){

		linkIndexSave[i]=new linkInfo[Node::maxNodes];
	}

	aliveNodesSave=new Node[Node::maxNodes];
}

void releaseSpaceFromBackup(){

	//TODO This function needs to be written!!!

}








