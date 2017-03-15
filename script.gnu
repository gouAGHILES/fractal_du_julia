
set terminal png size 1200,800
set output "mon_graphe.png"
set grid
set xlabel "Nombre de thread"
set ylabel "Temps de reponse"
set title "graphe de temps d'execution"
plot "text.txt" using 1:2 with lines
