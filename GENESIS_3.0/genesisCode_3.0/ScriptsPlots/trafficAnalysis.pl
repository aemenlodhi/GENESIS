
open GT, "<", "../generatedTraffic_225_225.txt" or die "Could not find generated file\n";
open CT, "<", "../consumedTraffic_225_225.txt" or die "Could not find consumed file\n";
open ET, "<", "../exchangedTraffic_225_225.txt" or die "Could not find consumed file\n";


@generated;
@consumed;
@exchanged;

while(<GT>){
	
	chomp $_;
	@categories=split('\t',$_);
	push(@generated,$categories[0]);
}

while(<CT>){
	
	chomp $_;
	@categories=split('\t',$_);
	push(@consumed,$categories[0]);
}

while(<ET>){
	
	chomp $_;
	@categories=split('\t',$_);
	push(@exchanged,$categories[0]);
}



printDistribution("generatedTrafficDistribution.txt",@generated);
printDistribution("consumedTrafficDistribution.txt",@consumed);
printDistribution("exchangedTrafficDistribution.txt",@exchanged);


print "Distributions printed\n";

sub printDistribution
{
        print "Printing Distribution\n";
        #prints the cdf of values in the array @dist to $fileName. Takes two arguments
        local($fileName,@dist)=@_;
        @distSorted=sort{$a<=>$b}@dist;

        open OFILE, ">", $fileName or die "Could not open output file $fileName\n";

        for($k=0;$k<@distSorted;$k++){
                $frac=($k+1)/@distSorted;
                print OFILE "$distSorted[$k]\t$frac\n";
        }

}