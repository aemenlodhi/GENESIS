/*
 * globalVars.h
 *
 *  Created on: Sep 24, 2009
 *      Author: alodhi3
 */

#ifndef GLOBALVARS_H_
#define GLOBALVARS_H_

#include "globalIncludes.h"
using namespace std;


//global variables declaration
#define PRINTLOG 0
#define DEBUG 0
#define CHECK 0
#define TRUE 1
#define FALSE 0
#define SNAPSHOT 0
#define RESULTLOG 0
#define EXPERIMENT 0
#define TRAFFICLOG 0

extern double CONFIDENCE_FACTOR_ESTIMATION;
extern bool PEERING;
extern bool PRIVATE_PEERING;
extern double PRIVATE_PEERING_THRESHOLD;
extern bool PAID_PEERING;
extern double UNIVERSAL_SIGMA;
extern bool DOMINANTDIRECTIONBILLING;
extern bool COMPETITIVE_PRICING;
extern double MAX_TRANSIT_PRICE;
extern double MIN_TRANSIT_PRICE;
extern double UNIVERSAL_PEERING_PRICE;
extern double TRANSIT_COST_EXPONENT;
extern double PEERING_COST_EXPONENT;
extern unsigned int MAX_NODES;
extern unsigned int INIT_NODES;
extern unsigned int MAX_LOCATIONS;
extern unsigned int MIN_POPS;
extern unsigned int MAX_POPS;
extern double ZIPF_PARAM_GEO_EXPANSE;
extern double MAX_TRAFFIC;
extern double MEAN_CONSUMED_TRAFFIC;
extern double ZIPF_PARAM_GENERATED_TRAFFIC;
extern double ZIPF_PARAM_CONSUMED_TRAFFIC;
extern unsigned int MULTIHOMING_DEGREE;
extern unsigned int MAX_ROUNDS;
extern unsigned int INITIAL_T1_CLIQUE_SIZE;
extern double MIN_PORT_CAPACITY;
extern double PORT_PRICE;
extern bool IXP_PEERING;	//enable this option if you want peering on ports and port-cost model
extern double ONE_G_PORT_PRICE;
extern double TEN_G_PORT_PRICE;
extern double HUNDRED_G_PORT_PRICE;
extern double TRANSIT_PRICE_100MBPS;
extern double TRANSIT_PRICE_1GBPS;
extern double TRANSIT_PRICE_10GBPS;
extern double TRANSIT_PRICE_100GBPS;


#endif /* GLOBALVARS_H_ */
