set terminal postscript eps enhanced color font ",18"

set output '| epstopdf --filter --outfile=trafficAnalysis.pdf'
set style data lines
set title "Analysis of Traffic"
set xlabel "Traffic volume (Mbps)"
set ylabel "Fraction of nodes"
set key top right
#set logscale x
#set logscale y
plot "generatedTrafficDistribution.txt" using 1:2 with lines lw 2 lt 3 title "Traffic generated", "consumedTrafficDistribution.txt" using 1:2 with lines lw 2 lt 5 title "Traffic consumed"

#plot "exchangedTrafficDistribution.txt" using 1:2 with lines lw 2 lt 1 title "Traffic exchanged b/w two nodes", "generatedTrafficDistribution.txt" using 1:2 with lines lw 2 lt 3 title "Traffic generated", "consumedTrafficDistribution.txt" using 1:2 with lines lw 2 lt 5 title "Traffic consumed"

