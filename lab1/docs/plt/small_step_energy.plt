set terminal pngcairo
set output "small_step_energy.png"

set xlabel "czas"
set ylabel "energia całkowita"

plot 'sol_10000_0.001_1_1_0.data' u 1:4 w l title 'step = 0.001', \
     'sol_1000_0.01_1_1_0.data' u 1:4 w l title 'step = 0.01'
