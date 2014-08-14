use List::Util qw(sum);

sub mean {
    
    	my($data) = @_;
        if (not @$data) {
                die("Empty array\n");
        }
        my $total = 0;
        foreach (@$data) {
                $total += $_;
        }
        my $average = $total / @$data;
        return $average;
        
}

sub stdev{
        my($data) = @_;
        if(@$data == 1){
                return 0;
        }
        my $average = &mean($data);
        my $sqtotal = 0;
        foreach(@$data) {
                $sqtotal += ($average-$_) ** 2;
        }
        my $std = ($sqtotal / (@$data-1)) ** 0.5;
        return $std;
}

@geoParams=(1,1.2,1.4,1.6,1.8,2);
open FILE, "<", "topologyStats_500.txt" or die "Could not open input file\n";

open pathLengthFile, ">>", "pathLength.txt" or die "Could not open output file\n";
open linkDensityFile, ">>", "linkDensity.txt" or die "Could not open output file\n";
open peeringTrafficFile, ">>", "peeringTraffic.txt" or die "Could not open output file\n";
open numProvidersFile, ">>", "numProviders.txt" or die "Could not open output file\n"; 



@avgPathLength=();
@linkDensity=();
@peeringTrafficOnly=();
@numProviders=();

$i=0;
$j=0;
while(<FILE>){
	
	chomp $_;
	@categories=split('\t',$_);
	push(@avgPathLength,$categories[6]);
	push(@linkDensity,$categories[7]);
	push(@peeringTrafficOnly,$categories[8]);
	push(@numProviders,$categories[0]);
	
	$i++;
	if(($i%10)==0){
		
			$meanPathLength=&mean(\@avgPathLength);
			$meanlinkDensity=&mean(\@linkDensity);
			$meanPeeringTrafficOnly=&mean(\@peeringTrafficOnly);
			$meanNumProviders=&mean(\@numProviders);
			
			$stdPathLength=&stdev(\@avgPathLength);
			$stdLinkDensity=&stdev(\@linkDensity);
			$stdPeeringTrafficOnly=&stdev(\@peeringTrafficOnly);
			$stdNumProviders=&stdev(\@numProviders);

			print pathLengthFile "$geoParams[$j]\t$meanPathLength\t$stdPathLength\t10\n";
			print linkDensityFile "$geoParams[$j]\t$meanlinkDensity\t$stdLinkDensity\t10\n";
			print peeringTrafficFile "$geoParams[$j]\t$meanPeeringTrafficOnly\t$stdPeeringTrafficOnly\t10\n";
			print numProvidersFile "$geoParams[$j]\t$meanNumProviders\t$stdNumProviders\10\n";
			
				
			$j++;
	}
		
	
}

