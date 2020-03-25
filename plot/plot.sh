#!/usr/bin/env bash



plot=" set terminal postscript eps enhanced color solid colortext 12\n"
plot="${plot} set output 'utilizacion.pdf'\n "
plot="${plot} set encoding utf8\n"
plot="${plot} set title 'IP0 utilization' font 'Times-Roman, 18'\n"
plot="${plot} set xlabel 'windows' font 'Times-Roman, 14'\n "
plot="${plot} set ylabel 'percentage' font 'Times-Roman, 14'\n "
plot="${plot} plot "
plot="${plot} 'temp.dat' using 1:1 smooth csplines t 'IP0\_CORE0' lw 1,"
plot="${plot} 'temp.dat' using 1:1 notitle with points,"
plot="${plot} 'temp.dat' using 1:2 smooth csplines t 'IP0\_CORE1' lw 1,"
plot="${plot} 'temp.dat' using 1:2 notitle with points;"
plot="${plot} set output"

echo -e ${plot} > gnuplotTempFile.gp

gnuplot gnuplotTempFile.gp