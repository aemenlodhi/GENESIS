/*
 * Statistics.h
 *
 *  Created on: Jan 5, 2010
 *      Author: alodhi3
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

//#include "NetSim.h"
//#include "globalVars.h"


double findModeDouble(list<double>& priceList, list<double>& priceSetList){

	list<double>::iterator itDouble1;
	list<double>::iterator itDouble2;
	int temp=0;
	int freqList[6]={0};

	int maxFreq=0;
	int maxFreqPoint=0;

	if(priceList.size()==1)
		return priceList.front();

	else{

		for(itDouble1=priceList.begin();itDouble1!=priceList.end();itDouble1++){

			temp=0;
			for(itDouble2=priceSetList.begin();itDouble2!=priceSetList.end();itDouble2++,temp++)
				if(*itDouble1==*itDouble2){
					freqList[temp]++;
					break;
				}
		}

		for(int i=0;i<6;i++)
			if(freqList[i]>maxFreq){
				maxFreq=freqList[i];
				maxFreqPoint=i;
			}

		temp=0;
		for(itDouble2=priceSetList.begin();itDouble2!=priceSetList.end();itDouble2++,temp++)
			if(temp==maxFreqPoint)
				return *itDouble2;

	}

}

int findIntMax(list<int>& checkList){

	checkList.sort();
	if(!checkList.empty())
		return checkList.back();
	else
		return 0;

}

int findIntMin(list<int>& checkList){

	checkList.sort();

	if(!checkList.empty())
		return checkList.front();
	else
		return 0;
}

double findIntAvg(list<int>& checkList){

	double avg=0;
	list<int>::iterator it;

	if(checkList.empty())
		return 0;
	else{
		for(it=checkList.begin();it!=checkList.end();it++)
			avg+=*it;
		return avg/checkList.size();
	}
}

double findIntMedian(list<int>& checkList){

	checkList.sort();
	double median=0;
	list<int>::iterator it;
	int count=0;

	if(checkList.empty())
		return 0;
	else if(checkList.size()==1)
		return checkList.front();
	else{

		if(checkList.size()%2){	//odd

			for(it=checkList.begin();it!=checkList.end();it++){
				count++;
				if(count==ceil(checkList.size()/2)){
					it++;
					median=*it;
					break;
				}
			}
		}

		else{
			for(it=checkList.begin();it!=checkList.end();it++){
				count++;
				if(count==checkList.size()/2){
					median=*it;
					it++;
					median+=*it;
					median=median/2;
				}
			}
		}

		return median;
	}
}

double findDoubleMax(list<double>& checkList){

	checkList.sort();
	if(!checkList.empty())
		return checkList.back();
	else
		return 0;

}

double findDoubleMin(list<double>& checkList){

	checkList.sort();

	if(!checkList.empty())
		return checkList.front();
	else
		return 0;
}

double findDoubleAvg(list<double>& checkList){

	double avg=0;
	list<double>::iterator it;

	if(checkList.empty())
		return 0;
	else{
		for(it=checkList.begin();it!=checkList.end();it++)
			avg+=*it;
		return avg/checkList.size();
	}
}

double findDoubleMedian(list<double>& checkList){

	checkList.sort();
	double median=0;
	list<double>::iterator it;
	int count=0;

	if(checkList.empty())
		return 0;
	else if(checkList.size()==1)
		return checkList.front();
	else{

		if(checkList.size()%2){	//odd

			for(it=checkList.begin();it!=checkList.end();it++){
				count++;
				if(count==ceil(checkList.size()/2)){
					it++;
					median=*it;
					break;
				}
			}
		}

		else{
			for(it=checkList.begin();it!=checkList.end();it++){
				count++;
				if(count==checkList.size()/2){
					median=*it;
					it++;
					median+=*it;
					median=median/2;
				}
			}
		}

		return median;
	}
}


#endif /* STATISTICS_H_ */
