set terminal pngcairo
set output "small_step.png"

set xlabel "czas"
set ylabel "kąt wychylenia"

plot 'sol_20_0.5_1_1_0.data' u 1:2 w l title 'step = 0.5', \
     'sol_1000_0.01_1_1_0.data' u 1:2 w l title 'step = 0.01'
