/*
 * codeDump.cpp
 *
 *  Created on: May 31, 2014
 *      Author: aemenlodhi
 */

//file to dump unused code
/*
void binPackGreedy(){

	peers.sort(sortReverseByVolume);

		unsigned int numPublicPortsRequired=0;
		IXPPort port;

		double totalPublicTraffic=0;

		while(!peers.empty()){

			totalPublicTraffic=peers.front().volume;

	#if 1
			cout<<"Considering peer "<<peers.front().linkedNode<<" with traffic volume "<<totalPublicTraffic<<endl;
	#endif

			if(allocatedPorts.empty()){


				ACQUIRE_NEW_PORT:

	#if 1
				cout<<"Allocating new port"<<endl;
	#endif

				port.portStatus=PUBLIC_PORT;

				if(totalPublicTraffic<1000){
					port.capacity=ONE_G;
					port.totalTraffic=totalPublicTraffic;
					numPublicPortsRequired=1;

	#if 1
				cout<<"ONE_G port allocated"<<endl;
	#endif
				}

				else if(totalPublicTraffic>=1000 && totalPublicTraffic<10000){
					port.capacity=TEN_G;
					port.totalTraffic=totalPublicTraffic;
					numPublicPortsRequired=1;

	#if 1
				cout<<"TEN_G port allocated"<<endl;
	#endif
				}

				else if(totalPublicTraffic>=10000 && totalPublicTraffic<100000){
					port.capacity=HUNDRED_G;
					port.totalTraffic=totalPublicTraffic;
					numPublicPortsRequired=1;

	#if 1
				cout<<"HUNDRED_G port allocated"<<endl;
	#endif
				}

				else{
					port.capacity=HUNDRED_G;
					port.totalTraffic=totalPublicTraffic;
					numPublicPortsRequired=ceil(totalPublicTraffic/100000);

	#if 1
				cout<<numPublicPortsRequired<<" HUNDRED_G ports allocated"<<endl;
	#endif
				}

				for(unsigned int i=1;i<numPublicPortsRequired;i++)
					allocatedPorts.push_back(port);

			}

			else{
				double totalCapacity;
				double usedCapacity;
				double remainingCapacity;
				if(allocatedPorts.back().capacity==ONE_G)
					totalCapacity=1000;
				else if(allocatedPorts.back().capacity==TEN_G)
					totalCapacity=10000;
				else if(allocatedPorts.back().capacity==HUNDRED_G)
					totalCapacity=100000;
				else{
					string str="ERROR!!! Unknown port capacity encountered";
					endSimulation(str);
				}

				usedCapacity=allocatedPorts.back().totalTraffic;
				remainingCapacity=totalCapacity-usedCapacity;

				if(remainingCapacity>totalPublicTraffic){
					allocatedPorts.back().totalTraffic+=totalPublicTraffic;

	#if 1
					cout<<"Peer adjusted in last port with remaining capacity "<<remainingCapacity<<" and now used capacity is "<<allocatedPorts.back().totalTraffic<<endl;
	#endif
				}

				else
					goto ACQUIRE_NEW_PORT;

			}

			peers.pop_front();

		}

		if(allocatedPorts.empty()){
			string str="ERROR!!! No ports were allocated in Greed Bin-Packing";
			endSimulation(str);
		}

		double freePeerCost=0;
		for(list<IXPPort>::iterator it=allocatedPorts.begin();it!=allocatedPorts.end();it++){

			freePeerCost+=(*it).getPortCosts();

		}

	#if 1
			cout<<"Bin-Packing cost is: "<<freePeerCost<<endl;
	#endif

		return freePeerCost;

}*/
