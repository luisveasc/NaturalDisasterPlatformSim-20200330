import sys
import json
import pymongo
from bson.objectid import ObjectId
import subprocess


def makeDataFileByMulticore(multicore, outputSimPlath, resumeType,nCore,nWin,winVectorName):
    filePath=outputSimPlath+"IP"+str(multicore["ip"])+"_"+resumeType+".dat"
    file = open(filePath, "w")
    for idWin in range(0,nWin):
        file.write(str(idWin)+" ")
        for idCore in range(0,nCore):
            file.write( str(multicore["cores"][idCore][winVectorName][idWin])+" ")
        file.write("\n")

    return filePath

def makeGnuplot(plotInfo,multicore, outputSimPlath,dataFilePath, resumeType,nCore):
    filePath=outputSimPlath+"IP"+str(multicore["ip"])+"_"+resumeType
    print(str(plotInfo))
    print(filePath)
    title = plotInfo["title"].replace("IP","IP"+str(multicore["ip"]))
    xrange = "["+str(plotInfo["xrange"]["min"])+":"+str(plotInfo["xrange"]["max"])+"]"
    yrange = "["+str(plotInfo["yrange"]["min"])+":"+str(plotInfo["yrange"]["max"])+"]"

    plot = "set terminal postscript eps enhanced color solid colortext 12\n"
    plot = plot + "set output '"+filePath+".pdf '\n"
    plot = plot + "set encoding utf8\n"
    plot = plot + "set title '"+title+"' font 'Times-Roman, 18'\n"
    plot = plot + "set xlabel '"+plotInfo["xlabel"]+"' font 'Times-Roman, 14'\n"
    plot = plot + "set ylabel '"+plotInfo["ylabel"]+"' font 'Times-Roman, 14'\n"
    plot = plot + "set xrange "+xrange+"\n"
    plot = plot + "set yrange "+yrange+"\n"
    plot = plot + "plot "

    i=2
    for idCore in range(0,nCore):
        core = multicore["cores"][idCore]["idCPU"]
        plot = plot + "'"+dataFilePath+"' using 1:"+str(i)+" smooth csplines t '"+core.replace("_", "\_")+"' lw 1,"
        plot = plot + "'"+dataFilePath+"' using 1:"+str(i)+" notitle with points,"
        i = i + 1

    plot = plot[0 : len(plot)-1] + "; set output"

    plotFile = open(filePath+".gp","w")
    plotFile.write(plot)

    orden = 'echo "'+plot+'" | gnuplot'

    subprocess.check_output(['bash','-c', orden ])


def utilizationTime(resume,outputSimPlath,resumeType,resumeTypeMap):

    for multicore in resume["multicores"]:
        nCore = len(multicore["cores"])
        dataFilePath = makeDataFileByMulticore(multicore, outputSimPlath, resumeType, nCore, resume["amountOfWindows"],resumeTypeMap[resumeType])
        makeGnuplot(resume["plotInfo"],multicore, outputSimPlath,dataFilePath, resumeType,nCore)

def percentageUtilizationTime(resume,outputSimPlath,resumeType,resumeTypeMap):

    for multicore in resume["multicores"]:
        nCore = len(multicore["cores"])
        dataFilePath = makeDataFileByMulticore(multicore, outputSimPlath, resumeType, nCore, resume["amountOfWindows"],resumeTypeMap[resumeType])
        makeGnuplot(resume["plotInfo"],multicore, outputSimPlath,dataFilePath, resumeType,nCore)


def plotBySimulationAndResumeType(idSimulation,outputSimPlath):

    resumeTypeMap ={ "utilizationTime":"msExecTimeWin",
                     "percentageUtilizationTime":"msPctgUseTimeWin"
                     }

    myclient = pymongo.MongoClient("mongodb://localhost:27017/")
    mydb = myclient["simulation_platform"]
    mycol = mydb["resumes"]

    for resume in mycol.find({ "idSimulation": idSimulation}):
        globals()[resume["resumeType"]](resume,outputSimPlath,resume["resumeType"],resumeTypeMap)




def main(idSimulation,outputSimPlath):

    plotBySimulationAndResumeType(idSimulation,outputSimPlath)




if len(sys.argv)!=3:
    print "we need 2 parameters => 'idSimulation', 'outputSimPlath'"
else :
    idSimulation  =  sys.argv[1]
    outputSimPlath = sys.argv[2]

main(idSimulation,outputSimPlath)
