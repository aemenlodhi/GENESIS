#ifndef SUPPORT_H_
#define SUPPORT_H_

#include "globalIncludes.h"
#include "globalStructs.h"
#include "globalVars.h"
#include "ixp.h"

template <class BidIt>
inline bool next_combination(BidIt, BidIt, BidIt, BidIt);

template <class T>
bool isPresentInList(list<T>&, T&);

template <class T>
bool copySecondListIntoFirst(list<T>&, const list<T>&);

template <class T>
bool copySecondAndThirdListIntoFirst(list<T>&, const list<T>&, const list<T>&);

bool compareProviders(list<NodePrice>& existing, list<NodePrice>& proposed);
bool sortByPrice(const NodePrice&, const NodePrice &);
bool sortBySecond(const nodePairs &, const nodePairs &);
bool sortById(const NodePrice&, const NodePrice&);
bool removeSameId(const NodePrice&, const NodePrice&);
bool removeIdOnly(const NodePrice&, const NodePrice&);
bool sortByTotalTraffic(const peeringTrialsPeersStruct &, const peeringTrialsPeersStruct &);
bool sortReverseByTotalTraffic(const peeringTrialsPeersStruct &, const peeringTrialsPeersStruct &);
bool sortReverseByUtility(const NodePrice &, const NodePrice &);
bool sortReverseByTotalWeight(const nodeTrafficRank &, const nodeTrafficRank &);
bool sortByVolume(const VolumePrice&, const VolumePrice&);
string convertInt(const unsigned int&);
string createString(set<unsigned int>&);
list<VolumePrice> binPack(ixpPortCapacity,double,list<VolumePrice>);
double binPackGreedy(ixpPortCapacity,list<VolumePrice>,list<unsigned int>&, bool,double);
void binPackFFDLR(list<VolumePrice>,vector<IXPPort>&);

//initialization function

vector<string> splitString(string,string);
bool sortReverseByNumGPresence(geoIndexPair n1, geoIndexPair n2);
bool sortByNumGPresence(geoIndexPair n1, geoIndexPair n2);
void endSimulation(string str);
bool shuffleProviders(list<NodePrice> &);
bool sortReverseByEntanglementScore(peeringTrialsCombinationsStruct n1, peeringTrialsCombinationsStruct n2);

template <class T>
bool copySecondListIntoFirst(list<T>& firstList, const list<T>& secondList){

	if(secondList.empty())
		return false;

	else{
		typename list<T>::const_iterator it;
		for(it=secondList.begin();it!=secondList.end();it++){
			firstList.push_back(*it);
		}
		return true;
	}
}

template <class T>
bool copySecondAndThirdListIntoFirst(list<T>& firstList, const list<T>& secondList, const list<T>& thirdList){

	if(secondList.empty() || thirdList.empty())
		return false;

	else{
		typename list<T>::const_iterator it;
		for(it=secondList.begin();it!=secondList.end();it++){
			firstList.push_back(*it);
		}

		for(it=thirdList.begin();it!=thirdList.end();it++){
			firstList.push_back(*it);
		}

		return true;
	}
}

template <class T>
bool isPresentInList(list<T>& checkList, T& toCheck){

	typename list<T>::iterator it;
	for(it=checkList.begin();it!=checkList.end();it++)
		if(*it==toCheck)
			return true;

	return false;

}

// Non recursive template function
template <class BidIt>

inline bool next_combination(BidIt n_begin, BidIt n_end,
BidIt r_begin, BidIt r_end)
{

  bool boolmarked=false;
  BidIt r_marked;

  BidIt n_it1=n_end;
  --n_it1;


  BidIt tmp_r_end=r_end;
  --tmp_r_end;

  for(BidIt r_it1=tmp_r_end; r_it1!=r_begin || r_it1==r_begin; --r_it1,--n_it1)
  {
    if(*r_it1==*n_it1 )
    {
      if(r_it1!=r_begin) //to ensure not at the start of r sequence
      {
        boolmarked=true;
        r_marked=(--r_it1);
        ++r_it1;//add it back again
        continue;
      }
      else // it means it is at the start the sequence, so return false
        return false;
    }
    else //if(*r_it1!=*n_it1 )
    {
      //marked code
      if(boolmarked==true)
      {
        //for loop to find which marked is in the first sequence
        BidIt n_marked;//mark in first sequence
        for (BidIt n_it2=n_begin;n_it2!=n_end;++n_it2)
          if(*r_marked==*n_it2) {n_marked=n_it2;break;}


        BidIt n_it3=++n_marked;
        for  (BidIt r_it2=r_marked;r_it2!=r_end;++r_it2,++n_it3)
        {
          *(r_it2)=*n_it3;
        }
        return true;
      }
      for(BidIt n_it4=n_begin; n_it4!=n_end; ++n_it4)
        if(*r_it1==*n_it4)
        {
          *(r_it1)=*(++n_it4);
          return true;
        }
    }
  }

  return true;//will never reach here
}

//#include "supportTemplates.tcc"

#endif
