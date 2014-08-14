set terminal postscript eps enhanced color font ",18"

set output '| epstopdf --filter --outfile=paidPeeringPricingAnalysis.pdf'

#set view map
#set size ratio .9
#set object 1 rect from graph 0, graph 0 to graph 1, graph 1 back
#set object 1 rect fc rgb "black" fillstyle solid 1.0
#splot "paidPeeringPricing.txt" using 1:2:3 with points pointtype 5 pointsize 1 palette linewidth 30

#set pm3d map
set dgrid 30,30
set hidden3d
set xrange [0:1]
set yrange [0:1]
set isosample 10
set contour base
#set nosurface
set title "Cost of traffic exchange vs fraction of total traffic\nand fraction of transit cost (30 Gbps)"
set xlabel "Fraction of\ntotal traffic"
set ylabel "Fraction of\ntransit cost"
set zlabel "Cost (USD)" rotate by -90
set key off
splot '30_GH_Analysis.txt' using 1:2:3 with lines


reset 
replot
set terminal postscript eps enhanced color font ",18"

set output '| epstopdf --filter --outfile=paidPeeringPricingAnalysisMap.pdf'
set bar 1.000000
set style rectangle back fc lt -3 fillstyle  solid 1.00 border -1
unset key
set view map
set xtics border in scale 0,0 mirror norotate  offset character 0, 0, 0
set ytics border in scale 0,0 mirror norotate  offset character 0, 0, 0
set ztics border in scale 0,0 nomirror norotate  offset character 0, 0, 0
set nocbtics
set rrange [ * : * ] noreverse nowriteback  # (currently [0.00000:10.0000] )
set trange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set urange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set vrange [ * : * ] noreverse nowriteback  # (currently [-5.00000:5.00000] )
set xrange [ 0 : 1 ] noreverse nowriteback
set yrange [0:1]
set ylabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
set y2label  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
set cblabel "Cost" 
set cblabel  offset character 0, 0, 0 font "" textcolor lt -1 rotate by 90
#set cbrange [ 0.00000 : 5.00000 ] noreverse nowriteback
set locale "C"
set palette rgbformulae -7, 2, -7
set xlabel "Fraction of total traffic"
set ylabel "Fraction of transit cost"
set title "Cost of traffic exchange vs fraction of total traffic\nand fraction of transit cost (30 Gbps)"
plot '30_GH_Analysis.txt' using 1:2:3 with image



reset
replot
set terminal postscript eps enhanced color font ",18"

set output '| epstopdf --filter --outfile=paidPeeringAnalysis.pdf'
set style data lines
set xlabel 'Fraction of traffic on paid peering link'
set ylabel 'Total Cost'
set title 'Cost Analysis'
set xzeroaxis
plot '10_G_Analysis.txt' using 1:2 with lines lw 2 lt 1 title "10G",\
'20_G_Analysis.txt' using 1:2 with lines lw 2 lt 2 title "20G",\
'30_G_Analysis.txt' using 1:2 with lines lw 2 lt 3 title "30G",\
'40_G_Analysis.txt' using 1:2 with lines lw 2 lt 4 title "40G",\
'100_G_Analysis.txt' using 1:2 with lines lw 2 lt 5 title "100G"
#'50_G_Analysis.txt' using 1:2 with lines lw 5 lt 1 title "50G",\
#'60_G_Analysis.txt' using 1:2 with lines lw 2 lt 6 title "60G",\
#'70_G_Analysis.txt' using 1:2 with lines lw 2 lt 7 title "70G",\
#'80_G_Analysis.txt' using 1:2 with lines lw 2 lt 8 title "80G",\
#'90_G_Analysis.txt' using 1:2 with lines lw 2 lt 9 title "90G",\
#'100_G_Analysis.txt' using 1:2 with lines lw 2 lt 10 title "100G"


reset
replot
set terminal postscript eps enhanced color font ",18"

set output '| epstopdf --filter --outfile=paidPeeringAnalysisApprox.pdf'
set style data lines
set xlabel 'Fraction of traffic on paid peering link'
set ylabel 'Total Cost'
set title 'Cost Analysis'
plot '10_G_AnalysisApprox.txt' using 2:4 with lines lw 2 lt 1 title "10G",\
'20_G_AnalysisApprox.txt' using 2:4 with lines lw 2 lt 2 title "20G",\
'30_G_AnalysisApprox.txt' using 2:4 with lines lw 2 lt 3 title "30G",\
'40_G_AnalysisApprox.txt' using 2:4 with lines lw 2 lt 4 title "40G",\
'100_G_AnalysisApprox.txt' using 2:4 with lines lw 2 lt 5 title "100G"
#'50_G_Analysis.txt' using 1:2 with lines lw 5 lt 1 title "50G",\
#'60_G_Analysis.txt' using 1:2 with lines lw 2 lt 6 title "60G",\
#'70_G_Analysis.txt' using 1:2 with lines lw 2 lt 7 title "70G",\
#'80_G_Analysis.txt' using 1:2 with lines lw 2 lt 8 title "80G",\
#'90_G_Analysis.txt' using 1:2 with lines lw 2 lt 9 title "90G",\
#'100_G_Analysis.txt' using 1:2 with lines lw 2 lt 10 title "100G"
