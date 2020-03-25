#!/usr/bin/env bash

filter="ResumeUsedPercentage"

./run_ayni.sh > plot/salida.temp

cd plot

cat salida.temp | grep "${filter}" > salida1.temp

rm salida.temp

python plot.py "salida1.temp" "${filter}" "plot_ayni.json"

rm salida1.temp
