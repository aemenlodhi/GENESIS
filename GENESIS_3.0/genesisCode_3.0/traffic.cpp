/*
 * traffic.cpp
 *
 *  Created on: May 30, 2013
 *      Author: aemen
 */
#include "traffic.h"

Traffic::Traffic(){

	maxTraffic=0;
	meanConsumedTraffic=0;
	sZetaConTraffic=0;
	sZetaGenTraffic=0;
	totalTraffic=0;
	trafficSensitivity=1;

}

Traffic trafficObj;

