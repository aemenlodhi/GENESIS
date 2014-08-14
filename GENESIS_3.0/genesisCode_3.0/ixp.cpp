/*
 * ixp.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: Aemen
 */

#include "ixp.h"
#include "globalVars.h"
#include "node.h"

IXPPort::IXPPort(){

	portStatus=PUBLIC_PORT;
	capacity=ONE_G;												//port capacity
	numPeers=0;													//number of peers exchanging traffic at the port
	portOwner=-1;												//who owns the port
	inboundTraffic=0;											//how much traffic is the owner receiving on this port
	outboundTraffic=0;											//how much traffic is the owner sending on this port
	totalTraffic=0;												//total traffic being exchanged by the owner on the port
	price=ONE_G_PORT_PRICE;											//price of the port
	locationId=0;												//at which IXP is this port located
	blockPort=false;
}

void IXPPort::restore(){

	numPeers=0;													//number of peers exchanging traffic at the port
	portOwner=-1;												//who owns the port
	inboundTraffic=0;											//how much traffic is the owner receiving on this port
	outboundTraffic=0;											//how much traffic is the owner sending on this port
	totalTraffic=0;												//total traffic being exchanged by the owner on the port
	price=ONE_G_PORT_PRICE;										//price of the port
	locationId=0;												//at which IXP is this port located
	blockPort=false;
	peerIds.clear();
}

double IXPPort::getPortCosts(){

	if(capacity==ONE_G){
		return ONE_G_PORT_PRICE;
	}

	else if(capacity==TEN_G){
		return TEN_G_PORT_PRICE;
	}

	else if(capacity==HUNDRED_G){
		return HUNDRED_G_PORT_PRICE;
	}

	else{
		string str="ERROR!!!! Unknown port capacity encountered";
		endSimulation(str);
	}

	return -1;
}

void Node::updateIXPPorts(double incomingTraffic){

	//determine the number of ports the node is using

	unsigned int numPublicPortsRequired;
	IXPPort port;
	double totalPublicTraffic=incomingTraffic;

	if(peeringPorts.empty()){

		ACQUIRE_NEW_PORT:
		port.portStatus=PUBLIC_PORT;

		if(totalPublicTraffic<1000){
			port.capacity=ONE_G;
			port.totalTraffic=totalPublicTraffic;
			numPublicPortsRequired=1;

#if 0
			cout<<"ONE_G port allocated"<<endl;
#endif

		}

		else if(totalPublicTraffic>=1000 && totalPublicTraffic<10000){
			port.capacity=TEN_G;
			port.totalTraffic=totalPublicTraffic;
			numPublicPortsRequired=1;


#if 0
			cout<<"TEN_G port allocated"<<endl;
#endif
		}

		else if(totalPublicTraffic>=10000 && totalPublicTraffic<100000){
			port.capacity=HUNDRED_G;
			port.totalTraffic=totalPublicTraffic;
			numPublicPortsRequired=1;


#if 0
			cout<<"HUNDRED_G port allocated"<<endl;
#endif
		}

		else{
			port.capacity=HUNDRED_G;
			port.totalTraffic=totalPublicTraffic;
			numPublicPortsRequired=ceil(totalPublicTraffic/100000);



#if 0
			cout<<numPublicPortsRequired<<" HUNDRED_G ports allocated"<<endl;
#endif
		}


		for(unsigned int i=1;i<=numPublicPortsRequired;i++)
			peeringPorts.push_back(port);

	}

	else{
		double totalCapacity;
		double usedCapacity;
		double remainingCapacity;
		if(peeringPorts.back().capacity==ONE_G)
			totalCapacity=1000;
		else if(peeringPorts.back().capacity==TEN_G)
			totalCapacity=10000;
		else if(peeringPorts.back().capacity==HUNDRED_G)
			totalCapacity=100000;
		else{
			string str="ERROR!!! Unknown port capacity encountered";
			endSimulation(str);
		}

		usedCapacity=peeringPorts.back().totalTraffic;
		remainingCapacity=totalCapacity-usedCapacity;

		if(remainingCapacity>incomingTraffic){
			peeringPorts.back().totalTraffic+=incomingTraffic;
		}

		else
			goto ACQUIRE_NEW_PORT;

	}

}

void Node::updateIXPPorts(){

	//determine the number of ports the node is using

	if(!K.empty()){

		vector<unsigned int> publicPeers;
		vector<unsigned int> privatePeers;
		peeringPorts.clear();
		unsigned int numPublicPortsRequired;
		unsigned int numPrivatePortsRequired;
		IXPPort port;
		double totalPublicTraffic=0;

		for(list<NodePrice>::iterator it=K.begin();it!=K.end();it++){

			if(PRIVATE_PEERING){
				if(linkValueVector[linkIndex[nodeId][(*it).nId].index]<this->privatePeeringThreshold){
					publicPeers.push_back((*it).nId);
					totalPublicTraffic+=linkValueVector[linkIndex[nodeId][(*it).nId].index];
				}
				else
					privatePeers.push_back((*it).nId);
			}

			else{
				publicPeers.push_back((*it).nId);
				totalPublicTraffic+=linkValueVector[linkIndex[nodeId][(*it).nId].index];

			}

		}

#if 0
		cout<<"Total actual peering traffic: "<<totalPublicTraffic<<endl;
#endif
		port.portStatus=PUBLIC_PORT;

		if(totalPublicTraffic<1000){
			port.capacity=ONE_G;
			port.totalTraffic=totalPublicTraffic;
			numPublicPortsRequired=1;

#if 0
			cout<<"ONE_G port used in complete peering"<<endl;
#endif
		}

		else if(totalPublicTraffic>=1000 && totalPublicTraffic<10000){
			port.capacity=TEN_G;
			port.totalTraffic=totalPublicTraffic;
			numPublicPortsRequired=1;

#if 0
			cout<<"TEN_G port used in complete peering"<<endl;
#endif

		}

		else if(totalPublicTraffic>=10000 && totalPublicTraffic<100000){
			port.capacity=HUNDRED_G;
			port.totalTraffic=totalPublicTraffic;
			numPublicPortsRequired=1;


#if 0
			cout<<"HUNDRED_G port used in complete peering"<<endl;
#endif

		}

		else{
			port.capacity=HUNDRED_G;
			port.totalTraffic=totalPublicTraffic;
			numPublicPortsRequired=ceil(totalPublicTraffic/100000);


#if 0
			cout<<numPublicPortsRequired<<" HUNDRED_G ports used in complete peering"<<endl;
#endif

		}

		for(unsigned int i=1;i<=numPublicPortsRequired;i++)
			peeringPorts.push_back(port);

		if(privatePeers.size()>0){

			double privatePeeringTraffic=0;
			port.restore();
			port.portStatus=PRIVATE_PORT;
			numPrivatePortsRequired=0;

			for(vector<unsigned int>::iterator it=privatePeers.begin();it!=privatePeers.end();it++){

				privatePeeringTraffic=linkValueVector[linkIndex[nodeId][(*it)].index];

				if(privatePeeringTraffic<1000){
					port.capacity=ONE_G;
					numPrivatePortsRequired=1;
				}

				else if(privatePeeringTraffic>=1000 && privatePeeringTraffic<10000){
					port.capacity=TEN_G;
					numPrivatePortsRequired=1;
				}

				else if(privatePeeringTraffic<100000){
					port.capacity=HUNDRED_G;
					numPrivatePortsRequired=1;

				}

				else{
					port.capacity=HUNDRED_G;
					numPrivatePortsRequired=ceil(privatePeeringTraffic/100000);

				}

				for(unsigned int i=0;i<numPrivatePortsRequired;i++){
					peeringPorts.push_back(port);
				}

			}

		}

	}

}
