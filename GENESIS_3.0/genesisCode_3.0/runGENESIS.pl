#!/usr/bin/perl

	$n1=$ARGV[0];
	$n2=$ARGV[1];	

	for($seed=$n1;$seed<($n1+$n2);$seed+=1){
	
		system(".././genesisBarcelona params.dat $seed $seed $seed 0 logFile.txt");
		


	}
	

