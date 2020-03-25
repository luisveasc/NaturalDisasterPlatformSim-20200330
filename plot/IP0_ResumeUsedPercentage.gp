set terminal postscript eps enhanced color solid colortext 12
set output 'IP0_ResumeUsedPercentage.pdf'
set encoding utf8
set title 'server utilization, one min by windows' font 'Times-Roman, 18'
set xlabel 'windows' font 'Times-Roman, 14'
set ylabel 'percentage' font 'Times-Roman, 14'
set xrange [0: 20]
set yrange [0: 110]
plot 'IP0_ResumeUsedPercentage.dat' using 1:2 smooth csplines t 'IP0\_CORE0' lw 1,'IP0_ResumeUsedPercentage.dat' using 1:2 notitle with points,'IP0_ResumeUsedPercentage.dat' using 1:3 smooth csplines t 'IP0\_CORE1' lw 1,'IP0_ResumeUsedPercentage.dat' using 1:3 notitle with points,'IP0_ResumeUsedPercentage.dat' using 1:4 smooth csplines t 'IP0\_CORE2' lw 1,'IP0_ResumeUsedPercentage.dat' using 1:4 notitle with points,'IP0_ResumeUsedPercentage.dat' using 1:5 smooth csplines t 'IP0\_CORE3' lw 1,'IP0_ResumeUsedPercentage.dat' using 1:5 notitle with points,'IP0_ResumeUsedPercentage.dat' using 1:6 smooth csplines t 'IP0\_CORE4' lw 1,'IP0_ResumeUsedPercentage.dat' using 1:6 notitle with points,'IP0_ResumeUsedPercentage.dat' using 1:7 smooth csplines t 'IP0\_CORE5' lw 1,'IP0_ResumeUsedPercentage.dat' using 1:7 notitle with points; set output