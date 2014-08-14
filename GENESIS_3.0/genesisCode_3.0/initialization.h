/*
 * netManage.h
 *
 *  Created on: May 27, 2013
 *      Author: aemen
 */

#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_

#include "globalIncludes.h"
#include "globalVars.h"
#include "node.h"
#include "geography.h"
#include "traffic.h"
#include "support.h"
#include "globalStructs.h"
#include "logDebug.h"

extern bool netDisconnected;
extern long int populationSeed;
extern long int playOrderSeed;
extern long int initialTopologySeed;

extern list<unsigned int> nodeOrder;
extern list<unsigned int> nodeOrderBackup;

void paramReader(char*);	//reads global parameters from a given file name
void assignInitialLocations(unsigned int, unsigned int, unsigned int, double);
void assignInitialTraffic(double,double,double,Traffic&,long int, long int);
void assignInitialPrices(bool,double,double);
void expandNodeRandom(int,int);
void formInitialTopology(unsigned int);
void permute(bool,long int);	//create a permutation of nodeIds for processing
int getNextNodeInOrder();
void initialize(bool, char*, long int,long int);
void allocateSpaceForBackup();
void releaseSpaceFromBackup();

#endif /* INITIALIZATION_H_ */
