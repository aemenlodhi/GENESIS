/*
 * logDebug.h
 *
 *  Created on: Oct 22, 2013
 *      Author: aemen
 */

#ifndef LOGDEBUG_H_
#define LOGDEBUG_H_

#include "globalIncludes.h"
#include "traffic.h"
#include "node.h"

extern fstream logFile;
extern fstream initialNetworkLog;
extern fstream finalNetworkLog;
extern fstream snapshotFile;
extern fstream flowFile;

void createLogFiles(fstream&, fstream&, fstream&, fstream&, fstream&, long int, long int, long int);

void displayTrafficMatrix();
void displayNodeData();
void displayNodeData(unsigned int);
void snapShot();
void displayRouteData();
void printNode(const unsigned int&, fstream&);

#endif /* LOGDEBUG_H_ */
