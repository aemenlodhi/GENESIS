/*
 * traffic.h
 *
 *  Created on: May 28, 2013
 *      Author: aemen
 */

#ifndef TRAFFIC_H_
#define TRAFFIC_H_


class Traffic{
public:
	double maxTraffic;
	double meanConsumedTraffic;
	double totalTraffic;
	double sZetaGenTraffic;	//s parameter for z distribution for generated traffic
	double sZetaConTraffic; //s parameter for z distribution for consumed traffic
	unsigned int trafficSensitivity;	//unused created for future for multiple classes of traffic
	double** trafficMatrix;
	Traffic();

};


extern Traffic trafficObj;

#endif /* TRAFFIC_H_ */
