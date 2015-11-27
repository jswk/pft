set terminal pngcairo
set output "different_fi0.png"

set xlabel "czas"
set ylabel "wychylenie względem amplitudy"

set yrange [-1.5:2]

plot 'ang_001.data' u 1:($2/0.01745) w l title "1 stopień", \
     'ang_030.data' u 1:($2/0.5246) w l title "30 stopni", \
     'ang_090.data' u 1:($2/1.5708) w l title "90 stopni", \
     'ang_170.data' u 1:($2/2.967) w l title "170 stopni"
