set terminal pngcairo
set output "period_change.png"

set xlabel "kąt wychylenia"
set ylabel "okres"

plot 'period.data' w l notitle
