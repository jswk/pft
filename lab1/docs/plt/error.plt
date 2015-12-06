set terminal pngcairo
set output "error.png"

set xlabel "krok czasowy"
set ylabel "maksymalna różnica energii"

set xrange [0.00005:10]
set yrange [1e-6:1e6]
set logscale xy

plot 'error.data' notitle
