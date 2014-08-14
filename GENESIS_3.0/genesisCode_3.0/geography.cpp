/*
 * geography.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: aemen
 */
#include "geography.h"

int Location::maxDensity=-1;
unsigned int Location::maxLocations=0;
unsigned int Location::maxPops=15;
unsigned int Location::minPops=1;

Location::Location(){
	locationId=0;
	population=0;
	maxNodesAllowed=1;
	locationPrice=0;
	numProviders=0;
}

Location* world;

