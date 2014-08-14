set terminal postscript eps enhanced color font ",18"

set output '| epstopdf --filter --outfile=numericalAnalysisMap.pdf'
set bar 1.000000
set style rectangle back fc lt -3 fillstyle  solid 1.00 border -1
#unset key
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
plot 'numericalAnalysis.txt' using 1:2:4 with image


reset
replot
set terminal postscript eps enhanced color font ",18"
set output '| epstopdf --filter --outfile=numericalAnalysisLines.pdf'
set dgrid 30,30
set hidden3d
set xrange [0:1]
set yrange [0:1]
set isosample 10
set contour base
set title "Cost of traffic exchange vs fraction of total traffic\nand fraction of transit cost (30 Gbps)"
set xlabel "Fraction of\ntotal traffic"
set ylabel "Fraction of\ntransit cost"
set zlabel "Cost (USD)" rotate by -90
set key off
splot 'numericalAnalysis.txt' using 1:2:3 with lines


reset
replot
set terminal postscript eps enhanced color font ",18"
set output '| epstopdf --filter --outfile=numericalAnalysisExp.pdf'
set pm3d interpolate 0,0
splot "numericalAnalysis.txt" with image
