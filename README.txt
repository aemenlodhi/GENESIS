As part of my dissertation research, I have created GENESIS - an open-source computational agent-based model of interdomain network formation, traffic flow and economics. GENESIS provides us with an elaborate computational testbed through which we can experiment with different interconnection and economic strategies, evaluate them under realistic conditions, and observe how the actions of individual ASes manifest into large-scale behaviors at the macroscopic level. To the best of my knowledge, GENESIS is the only simulator which uses agent-based modeling to model the Internet at such scales.

GENESIS has been implemented using C++. GENESIS has evolved with my dissertation research and there may be considerable differences between different versions. Over time I have added scalability and improved the speed of the simulator. GENESIS can currently handle about 1500 nodes on a decent workstation with 8GB memory. Please note that other simulators in the same category can't even reach the 1000 mark and that too when most of them do not use realistic Internet routing, which GENESIS does with ease. The most realistic simulation of the interdomain network, modeling 40,000 nodes, carried out by another group required a super computer!

GENESIS so far has 3 versions:

GENESIS 1.0: The earliest (and crudest) version of GENESIS which could handle only 500 nodes. GENESIS 1.0 followed a different network formation model, i.e., all nodes acted simultaneously, a major constraint, in such simulations. GENESIS 1.0 was used in our publication for NetEcon 2010.

GENESIS 2.0: This was a major change from 1.0. The results were published in IEEE InfoCom 2012.

GENESIS 3.0: This is the latest version of GENESIS which is stable and is more realistic than any previous models. 

GENESIS 4.0: This is the planned version of GENESIS which will be released in future and will mark the end of project. GENESIS 4.0 is expected to scale to at least 25000 nodes.

If you have any questions please refer to our publications and contact me.

thanks

Aemen Lodhi



