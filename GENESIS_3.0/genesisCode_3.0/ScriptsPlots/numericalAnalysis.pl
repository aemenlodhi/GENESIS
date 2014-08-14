use POSIX;

		open NA, ">", "numericalAnalysis.txt";
		
		for($j=0;$j<=1.05;$j+=0.05){
	        for($k=0;$k<=1.05;$k+=0.05){
	        	
	        		if($j<1){
	        			$peeringMixCost=$k*($j**0.9335)+(1-$j)**0.9335;
	        			
	        			if($peeringMixCost>=1){
	        				$binVal=1;
	        			}
	        			
	        			else{
	        				$binVal=0;
	        			}
	        			
	        		}
	        		
	        		else{
	        			$peeringMixCost=$k*($j**0.9335);
	        			
	        			if($peeringMixCost>=1){
	        				$binVal=1;
	        			}
	        			
	        			else{
	        				$binVal=0;
	        			}
	        			
	        			
	        		}
	        		print NA "$j\t$k\t$peeringMixCost\t$binVal\n";
	        }
        }