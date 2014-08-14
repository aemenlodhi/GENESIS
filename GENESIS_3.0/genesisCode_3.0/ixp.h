/*
 * ixp.h
 *
 *  Created on: Feb 3, 2014
 *      Author: Aemen
 */

#ifndef IXP_H_
#define IXP_H_

#include "globalIncludes.h"
#include "globalStructs.h"

class IXPPort{

public:

	ixpPortCapacity capacity;			//port capacity
	unsigned int numPeers;				//number of peers exchanging traffic at the port
	unsigned int portOwner;				//who owns the port
	vector<unsigned int> peerIds;		//the ids of peers with whom the owner is exchanging traffic
	double inboundTraffic;				//how much traffic is the owner receiving on this port
	double outboundTraffic;				//how much traffic is the owner sending on this port
	double totalTraffic;					//total traffic being exchanged by the owner on the port
	double price;						//price of the port
	unsigned int locationId;				//at which IXP is this port located
	bool blockPort;						//no more peers at this port
	portCharacteristic portStatus;
	IXPPort();
	void restore();
	double getPortCosts();

};

#endif /* IXP_H_ */
