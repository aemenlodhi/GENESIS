$fnT  = "paidPeeringPricing.txt";

$transitPrice100MPerMbps      = 6;
$transitPrice1GPerMbps        = 4;
$transitPrice10GPerMbps       = 1;
$transitPrice100GPerMbps		 =  0.4;
$peeringPrice100MPortPerMonth = 100;
$peeringPrice1GPortPerMonth   = 800;
$peeringPrice10GPortPerMonth  = 1700;
$peeringPrice100GPortPerMonth = 7820;


for($t=0;$t<=100000;$t+=10000){
    
    $fn=$t/1000;
    $fileName=$fn."_G_Analysis.txt";
    open F, ">", $fileName or die "Could not create file $fileName\n";
    

    $fileNameApprox=$fn."_G_AnalysisApprox.txt";
    open FApprox, ">", $fileNameApprox or die "Could not create file $fileNameApprox\n";
    
    print "Filing $fileName\n";
    
    for($j=0;$j<=1.05;$j+=0.05){
        
        print "Ratio: $j\n";

        $transitCost=getTransitCost($t);
        $paidPeeringCost=getPaidPeeringCost($t,0.5);
        $peeringMixCost=getTransitCost($t*(1-$j))+getPaidPeeringCost($t*$j,0.5);
        
        
        $cost=$transitCost+$paidPeeringCost;
        $diff=$transitCost-$peeringMixCost;
        print "$t\t$j\t$cost\n";
        print F "$j\t$diff\t$cost\t$peeringMixCost\t$transitCost\t$paidPeeringCost\t$t\n";
        
        $transitCost=2.0399*($t**0.9335);
        $peeringMixCost=0.5*2.0399*(($j*$t)**0.9335)+2.0399*(((1-$j)*$t)**0.9335);
        $cost=$transitCost+$paidPeeringCost;
        
        $diff=$transitCost-$peeringMixCost;
        
        print FApprox "$t\t$j\t$cost\t$diff\t$transitCost\t$paidPeeringCost\n";

        
        
            
        if($fn==30){
        		
        		print "Inside the heat analysis\n";
        		$fileNameH=$fn."_GH_Analysis.txt";
        		open FH, ">>", $fileNameH or die "Could not create file $fileNameH\n";

        		for($k=0;$k<=1.05;$k+=0.05){
        			$transitCost=getTransitCost($t*(1-$j));
        			$paidPeeringCost=getPaidPeeringCost($t*$j,$k);

        			$cost=$transitCost+$paidPeeringCost;
        			print FH "$j\t$k\t$cost\t$transitCost\t$paidPeeringCost\t$t\n";
        			
        			
        			 			    
        			
        		}
        	
        }
        
    }
    
}

sub getTransitCost {
    
	$traffic = $_[0];
	$cost    = 0;
    
	if ( $traffic <= 1000 ) {
		$cost = $traffic * $transitPrice100MPerMbps;
	}
    
	elsif ( $traffic > 1000 && $traffic <= 10000 ) {
		$cost = $traffic * $transitPrice1GPerMbps;
	}
    
	else {
		$cost = $traffic * $transitPrice10GPerMbps;
	}
    
	return $cost;
    
}

sub getPaidPeeringCost {
    
    $traffic= $_[0];
    $pricingFrac=$_[1];
    
    $cost=0;
    
    
    if ( $traffic <= 1000 ) {
		$cost = $traffic * $pricingFrac* $transitPrice100MPerMbps;
	}
    
	elsif ( $traffic > 1000 && $traffic <= 10000 ) {
		$cost = $traffic * $pricingFrac*$transitPrice1GPerMbps;
	}
    
	else {
		$cost = $traffic * $pricingFrac *  $transitPrice10GPerMbps;
	}
    
	return $cost;

}

sub getPeeringCost {
    
	$numPeers       = $_[0];
	$traffic        = $_[1];
	$cost           = 0;
	$perPeerTraffic = 0;
    
	if ( $numPeers > 1 ) {
		$perPeerTraffic = ceil( $traffic / $numPeers );
	}
    
	#	if($traffic<=100){
	#		$cost=$peeringPrice100MPortPerMonth;
	#	}
    
	if ( $numPeers == 1 || $perPeerTraffic < 250 ) {
        
		if ( $traffic <= 1000 ) {
			$cost = $peeringPrice1GPortPerMonth;
		}
        
		elsif ( $traffic > 1000 && $traffic <= 10000 ) {
			$cost = $peeringPrice10GPortPerMonth;
		}
        
        
		else {
            
			if ( $traffic < 100000 ) {
				
				$cost=$peeringPrice100GPortPerMonth;
				
			}
            
			else {
                
				my $num100GPorts = ceil( $traffic / 100000 );
				$cost = $num100GPorts * $peeringPrice100GPortPerMonth;
			}
            
		}
	}
    
	else {
        
		for ( $j = 1 ; $j <= $numPeers ; $j++ ) {
			$cost = $cost + getPeeringCost( 1, $perPeerTraffic );
		}
        
	}
    
	return $cost;
}
