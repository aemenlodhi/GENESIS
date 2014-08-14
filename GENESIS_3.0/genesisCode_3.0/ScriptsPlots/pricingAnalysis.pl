use POSIX;

$fnT  = "transitPricing.txt";
$fn1P = "peeringPricingOneNode.txt";
$fn2P = "peeringPricingTwoNode.txt";
$fn3P = "peeringPricingThreeNode.txt";

$transitPrice100MPerMbps      = 6;
$transitPrice1GPerMbps        = 4;
$transitPrice10GPerMbps       = 1;
$peeringPrice100MPortPerMonth = 100;
$peeringPrice1GPortPerMonth   = 800;
$peeringPrice10GPortPerMonth  = 1700;
$peeringPrice100GPortPerMonth = 7820;

open FT, ">", $fnT or die "Could not create file $fnT\n";

for ( $i = 0 ; $i <= 100000 ; $i += 10 ) {

	my $transitCost  = getTransitCost($i);
	my $OnepeeringCost = getPeeringCost( 1, $i );
	my $TwopeeringCost = getPeeringCost( 2, $i );
	my $FivepeeringCost = getPeeringCost( 3, $i );
	my $TenpeeringCost = getPeeringCost(10,$i);
	my $halfTransitCost = getTransitCost($i)/2;

	#print FT "$i\t$transitCost\t$OnepeeringCost\t$TwopeeringCost\t$FivepeeringCost\t$TenpeeringCost\t$halfTransitCost\n";
	print FT "$i\t$transitCost\n";
}

sub getTransitCost {

	$traffic = $_[0];
	$cost    = 0;

	if ( $traffic <= 100 ) {
		$cost = $traffic * $transitPrice100MPerMbps;
	}

	elsif ( $traffic > 100 && $traffic <= 1000 ) {
		$cost = $traffic * $transitPrice1GPerMbps;
	}

	else {
		$cost = $traffic * $transitPrice10GPerMbps;
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
