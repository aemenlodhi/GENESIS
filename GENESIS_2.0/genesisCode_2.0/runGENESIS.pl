#!/usr/bin/perl

$n1=$ARGV[0];
$n2=$ARGV[1];
	my $osCounter=0;
	
	#@geoParams=(1,1.2,1.4,1.6,1.8,2);
	#foreach(@geoParams){
	$geoParam=$_;
	print "Simulating for geoParam: $geoParam\n";
	for($seed=$n2;$seed<($n2+10);$seed+=1){

		print "Simulating for seed $seed\n";
		if(-e "oscillation.txt"){
			print "ERROR!!\n";
		 
			$osCounter++;	
			#system("rm -f errorRun.txt");
			#exit;
		}
	
		#Usage: maxNodes maxRegions maxIterations maxTraffic runId sZetaTrafficGen sZetaTrafficCon sZetaGeography priceDependancy seed setNumber initNodes sigma playOrderSeed initialTopologySeed
		system("./NetSim 500 7 100 409600 $seed 1.0 0.8 1.6 -1 $seed 2 $n1 1 $seed $seed");
		
		exit;

	}
	#}	
	
	#print "$osCounter\n";

