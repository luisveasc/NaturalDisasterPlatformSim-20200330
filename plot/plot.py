import sys
import os
import json
import subprocess

def makePlotsFiles(filepath,filter):
    ip=""
    serversFileName=[]
    columnsByServer={}

    ipFile=open("temp.dat", "w")
    file = open(filepath, "r")
    for l in file.readlines():
        line = l.replace("\n", "")
        data = line.split('#', len(line) )
        if(line.find("IP")!=-1):
            svr = data[2].split("_",len(data[0]))
            ipFileName = svr[0]+"_"+filter
            serversFileName.append(ipFileName)
            ipFile = open(ipFileName+".dat", "w")

            cols=[]
            i = 2
            while i < len(data):
                cols.append(data[i])
                i = i + 1

            columnsByServer[ipFileName]=cols

        else:
            i = 1
            while i < len(data):
                ipFile.write(data[i]+" ")
                i = i + 1
            ipFile.write("\n")

    os.remove("temp.dat")
    return serversFileName,columnsByServer


def createPlots(serversFileName,columnsByServer,config):

    plotParameters=config["ResumeUsedPercentage"]

    for server in serversFileName:
        plot = "set terminal postscript eps enhanced color solid colortext 12\n"
        plot = plot + "set output '"+server+".pdf'\n"
        plot = plot + "set encoding utf8\n"
        plot = plot + "set title '"+plotParameters["title"]+"' font 'Times-Roman, 18'\n"
        plot = plot + "set xlabel '"+plotParameters["xLabel"]+"' font 'Times-Roman, 14'\n"
        plot = plot + "set ylabel '"+plotParameters["yLabel"]+"' font 'Times-Roman, 14'\n"
        plot = plot + "set xrange "+plotParameters["xRange"]+"\n"
        plot = plot + "set yrange "+plotParameters["yRange"]+"\n"
        plot = plot + "plot "

        i=2
        for col in columnsByServer[server]:
            plot = plot + "'"+server+".dat' using 1:"+str(i)+" smooth csplines t '"+col.replace("_", "\_")+"' lw 1,"
            plot = plot + "'"+server+".dat' using 1:"+str(i)+" notitle with points,"
            i = i + 1

        plot = plot[0 : len(plot)-1] + "; set output"

        plotFile = open(server+".gp","w")
        plotFile.write(plot)

        orden = 'echo "'+plot+'" | gnuplot'

        subprocess.check_output(['bash','-c', orden ])

        # try:
        #     py2output = subprocess.check_output(['gnuplot',server+".gp"],stderr= subprocess.STDOUT)
        #
        # except subprocess.CalledProcessError as e:
        #     print "Calledprocerr"


def main(filepath,filter,config):
    serversFileName,columnsByServer = makePlotsFiles(filepath,filter)
    createPlots(serversFileName,columnsByServer,config)

#lee parametros
if len(sys.argv)!=4:
    print "we need 3 parameters, 'filepath' 'filter', 'json-config'"
else :
    filepath  = sys.argv[1]
    filter = sys.argv[2]
    configFile = sys.argv[3]
    config={}
    with open(configFile) as json_file:
        config = json.load(json_file)

    main(filepath,filter,config)