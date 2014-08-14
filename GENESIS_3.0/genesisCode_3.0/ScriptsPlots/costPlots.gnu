
set terminal postscript eps enhanced color font ",18"

set output '| epstopdf --filter --outfile=transitCost.pdf'
set style data lines
set title "Total Cost for traffic volume\n under different pricing/connectivity schemes"
set xlabel "Traffic volume (Mbps)"
set ylabel "Total Cost (USD Monthly)"
set key top left
set logscale x
set logscale y
plot "transitPricing.txt" using 1:2 with lines lw 2 lt 1 title "Transit Cost", "transitPricing.txt" using 1:3 with lines lw 2 lt 3 title "Peering Cost 1 Peers",\
	"transitPricing.txt" using 1:4 with lines lw 3 lt 4 title "Peering Cost 2 Peers", "transitPricing.txt" using 1:5 with lines lw 3 lt 8 title "Peering Cost 3 Peers",\
	"transitPricing.txt" using 1:6 with lines lw 3 lt 9 title "Peering Cost 10 Peers", "transitPricing.txt" using 1:7 with lines lw 3 lt 11 title "Paid Peering Cost" 

