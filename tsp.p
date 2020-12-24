reset
set term postscript eps enhanced color

set output "tsp51-aco.eps"
set xlabel "x"
set ylabel "y"
set title "TSP 51 cities by Ant Colony Optimization"
#set xrange[10:60]
#set yrange[15:70]

plot "ans0.txt" using 2:3 with linespoints linewidth 2 notitle, "ands0.txt" using 2:3:(sprintf("(%d)", $1)) with labels point  pt 7 offset char 1,1 notitle
