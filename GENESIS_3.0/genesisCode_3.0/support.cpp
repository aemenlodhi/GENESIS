/*
 * support.cpp
 *
 *  Created on: Mar 2, 2012
 *      Author: Aemen
 */
#include "support.h"

string createString(set<unsigned int>& myset){

	string outputString;
	for(setIt itps=myset.begin();itps!=myset.end();itps++){

		if(outputString.empty())
			outputString+=convertInt(*itps);

		else
			outputString+=("_"+convertInt(*itps));

	}

	return outputString;
}

string convertInt(const unsigned int& number){

   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

bool sortReverseByVolume(const VolumePrice& n1, const VolumePrice& n2){

	return n1.volume>n2.volume;
}

bool sortReverseByTotalWeight(const nodeTrafficRank& n1, const nodeTrafficRank& n2){

	return n1.totalWeight>n2.totalWeight;

}

bool sortReverseByTotalTraffic(const peeringTrialsPeersStruct& n1, const peeringTrialsPeersStruct& n2){

	return n1.totalTraffic>n2.totalTraffic;
}

bool sortReverseByUtility(const NodePrice & n1, const NodePrice & n2){

	return n1.price>n2.price;
}

bool sortByTotalTraffic(const peeringTrialsPeersStruct& n1, const peeringTrialsPeersStruct& n2){

	return n1.totalTraffic<=n2.totalTraffic;
}

bool sortByPrice(const NodePrice& n1, const NodePrice &n2){

	return n1.price<n2.price;
}


bool removeSameId(const NodePrice& n1, const NodePrice& n2){

	return n1.nId==n2.nId;
}

bool removeIdOnly(const NodePrice& n1, const NodePrice& n2){
	return n1.nId==n2.nId;
}

bool sortById(const NodePrice& n1, const NodePrice& n2){

	return n1.nId<n2.nId;
}

bool sortBySecond(const nodePairs & first, const nodePairs & second){

	if(first.n2 < second.n2)
		return true;

	else if(first.n2==second.n2){
		if(first.n1<second.n1)
			return true;
		else
			return false;
	}

	else
		return false;
}






//////////////////// Unknowns//////////////////////////







bool compareProviders(list<NodePrice>& existing, list<NodePrice>& proposed){


	if(existing.size()!=proposed.size())
		return false;

	list<NodePrice>::iterator it1;
	list<NodePrice>::iterator it2;

	for(it1=existing.begin(),it2=proposed.begin();it1!=existing.end() && it2!=proposed.end();it1++,it2++)
		if(*it1!=*it2)
			return false;

	return true;


}

bool sortReverseByNumGPresence(geoIndexPair n1, geoIndexPair n2){

	if(n1.numGPresence>n2.numGPresence)
		return true;
	else
		return false;
}

bool sortReverseByEntanglementScore(peeringTrialsCombinationsStruct n1, peeringTrialsCombinationsStruct n2){

	if(n1.entanglementScore>n2.entanglementScore)
		return true;
	else
		return false;
}

bool sortByNumGPresence(geoIndexPair n1, geoIndexPair n2){

	if(n1.numGPresence<n2.numGPresence)
		return true;
	else
		return false;
}

void endSimulation(string str){
	cout<<"ERROR IN SIMULATION!!!"<<endl;
	cout<<str<<endl;

	//logFile<<"ERROR IN SIMULATION!!!"<<endl;
	//logFile<<str<<endl;

	char errorFileName[50];
	ofstream errorFile;
	sprintf(errorFileName,"errorRun.txt");
	errorFile.open(errorFileName,ios::app);
	//errorFile<<"Seeds used: "<<populationSeed<<"\t"<<initialTopologySeed<<"\t"<<playOrderSeed<<endl;
	errorFile<<str<<endl;

	exit(-1);
}

bool shuffleProviders(list<NodePrice>& possibleProviders){

	if(possibleProviders.empty())
		return false;

	else if(possibleProviders.size()==1)
		return true;

	else{

		map<unsigned int,double> providerMap;
		list<NodePrice>::iterator itNP;
		list<unsigned int> tempList;
		NodePrice tempNP;

		for(itNP=possibleProviders.begin();itNP!=possibleProviders.end();itNP++){
			providerMap[(*itNP).nId]=(*itNP).price;
			tempList.push_back((*itNP).nId);
		}

		possibleProviders.clear();
		//std::random_shuffle(tempList.begin(),tempList.end());

		for(list<unsigned int>::iterator it=tempList.begin();it!=tempList.end();it++){
			tempNP.nId=*it;
			tempNP.price=providerMap[*it];
			possibleProviders.push_back(tempNP);
		}

		return true;

	}

}

vector<string> splitString(string str, string delim){

	std::size_t start = 0;
	std::size_t end;
	vector<string> v;

	if(!str.empty() && str.at(0)!='#'){

		end = str.find(delim, start);
		v.push_back(str.substr(start, end-start));
		start = end + delim.length();
		v.push_back(str.substr(start,str.length()-start));

	}

	return v;
}

void binPackFFDLR(list<VolumePrice> potentialPeers, vector<IXPPort>& actualPorts){

	potentialPeers.sort(sortReverseByVolume);

	double remainingCapacity=0;
	double cap=0;
	list<IXPPort> packedPeersPorts;
	IXPPort port;

	for(list<VolumePrice>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){

		if(packedPeersPorts.empty() || remainingCapacity<(*it).volume){
			port.capacity=HUNDRED_G;
			cap=100000;
			remainingCapacity=cap;
			packedPeersPorts.push_back(port);
		}

		packedPeersPorts.back().totalTraffic+=(*it).volume;
		packedPeersPorts.back().peerIds.push_back((*it).linkedNode);
		remainingCapacity=100000-packedPeersPorts.back().totalTraffic;

	}


	for(list<IXPPort>::iterator it=packedPeersPorts.begin();it!=packedPeersPorts.end();it++){

		if((*it).totalTraffic>=10000){
			port.capacity=HUNDRED_G;
			actualPorts.push_back(port);
		}

		else if((*it).totalTraffic>=1000 && (*it).totalTraffic<10000){
			port.capacity=TEN_G;
			actualPorts.push_back(port);
		}

		else{
			port.capacity=ONE_G;
			actualPorts.push_back(port);
		}

	}


}


double binPackGreedy(ixpPortCapacity capacity, list<VolumePrice> potentialPeers, list<unsigned int>& packedPeers, bool multipleHundreds, double incomingTraffic){

	double cap=0;
	unsigned int numPortsUsed=0;
	double peeringCost=0;
	IXPPort port;
	port.capacity=capacity;

	if(capacity==ONE_G)
		cap=1000;
	else if(capacity==TEN_G)
		cap=10000;
	else if(capacity==HUNDRED_G)
		cap=100000;
	else{
		string str="ERROR!!! Unknown capacity encountered";
		endSimulation(str);
	}

	double remainingCapacity=cap;
	potentialPeers.sort(sortReverseByVolume);

	for(list<VolumePrice>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){

		if(capacity==HUNDRED_G && multipleHundreds==true){
			numPortsUsed=ceil(incomingTraffic/100000);
			packedPeers.push_back((*it).linkedNode);
		}

		else{

			numPortsUsed=1;
			if((*it).volume<=remainingCapacity){
				remainingCapacity-=(*it).volume;
				packedPeers.push_back((*it).linkedNode);
			}

		}

	}

	for(unsigned int i=1;i<=numPortsUsed;i++){
		peeringCost+=port.getPortCosts();
	}

	return peeringCost;

}

list<VolumePrice> binPack(ixpPortCapacity capacity, double traffic,list<VolumePrice> potentialPeers){

	double pc;

	if(capacity==ONE_G)
		pc=1000;
	else if(capacity==TEN_G)
		pc=10000;
	else if(capacity==HUNDRED_G)
		pc=100000;
	else{
		string str="ERROR!!! Unrecognized port capacity";
		endSimulation(str);
	}

#if DEBUG
	cout<<"Bin packing "<<traffic<<" traffic in port size "<<pc<<endl;
#endif

	if(traffic<=pc){
		potentialPeers.clear();

#if DEBUG
	cout<<"All traffic fits in the port"<<endl;
#endif

		return potentialPeers;
	}

	else{

		potentialPeers.sort(sortReverseByVolume);
		double remainingCapacity=pc;
		bool peerPacked=true;

		do{
			peerPacked=false;
			for(list<VolumePrice>::iterator it=potentialPeers.begin();it!=potentialPeers.end();it++){

#if DEBUG
	cout<<"Encountered potential peer with volume: "<<(*it).volume<<endl;
#endif

				if((*it).volume<=remainingCapacity){
					peerPacked=true;
					remainingCapacity-=(*it).volume;
					potentialPeers.erase(it);

#if DEBUG
					cout<<"Packed peer "<<(*it).linkedNode<<" with traffic "<<(*it).volume<<" and remaining capacity in port is: "<<remainingCapacity<<endl;
#endif

					break;
				}

			}

		}while(peerPacked==true);

		return potentialPeers;

	}

}


