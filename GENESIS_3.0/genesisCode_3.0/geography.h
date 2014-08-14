/*
 * geography.h
 *
 *  Created on: May 27, 2013
 *      Author: aemen
 */

#ifndef GEOGRAPHY_H_
#define GEOGRAPHY_H_

#include "globalIncludes.h"
#include "globalStructs.h"

//Geography class
class Location{

public:

	static int maxDensity;
	static unsigned int maxLocations;
	static unsigned int maxPops;
	static unsigned int minPops;

	unsigned int locationId;
	unsigned int population;			//number of Nodes that have PoPs in this region
	list<unsigned int> nodePresent;		//list of all Nodes that have PoPs in this region
	unsigned int maxNodesAllowed;		//maximum number of nodes allowed in the region
	double locationPrice;				//price maintained by all nodes in the region
	unsigned int numProviders;			//number of transit providers at location

	Location();

};

extern Location* world;

#endif /* GEOGRAPHY_H_ */
