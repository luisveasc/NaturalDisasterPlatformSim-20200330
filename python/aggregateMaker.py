import sys
import json
import pymongo
from bson.objectid import ObjectId

def lastTimeByIdSimulation(idSimulation):
        myclient = pymongo.MongoClient("mongodb://localhost:27017/")
        mydb = myclient["simulation_platform"]
        mycol = mydb["simu_data"]

        docs = mycol.find({ "idSimulation": idSimulation}).sort("msCurrentTime", pymongo.DESCENDING).limit(1)

        return  docs[0]["msCurrentTime"]


def getInfrstructureByIdSimulation(idSimulation):
    myclient = pymongo.MongoClient("mongodb://localhost:27017/")
    mydb = myclient["simulation_platform"]
    mycol = mydb["infrastructure"]
    infrastructure = mycol.find_one({ "idSimulation": idSimulation})

    mapIpCores={}
    ipId = 0
    for multicore in infrastructure["multicores"]:
        coreId = 0
        for core in multicore["coresName"]:
            mapIpCores[core]={"ipId":ipId,"coreId":coreId}
            coreId=coreId+1
        ipId=ipId+1

    return infrastructure,mapIpCores

def getEmptyVectorOfWindows(msWindowSize,msLastTime):
    winEnd = 0
    windows = []
    while winEnd <= msLastTime:
        winEnd = winEnd + msWindowSize
        windows.append(0)
    amountOfWindows=len(windows)

    return windows, amountOfWindows

def createResumeBaseByTime(idSimulation,msWindowSize,infrastructure,msLastTime,windows, amountOfWindows,resumeType,winVectorName):

    resume={"idSimulation": idSimulation, "msWindowSize":msWindowSize, "msLastTime": msLastTime, "amountOfWindows":amountOfWindows , "resumeType": resumeType}

    #rellena la infraestructura con blancos en las ventanas de tiempo
    ipId = 0
    for multicore in infrastructure["multicores"]:
        ip = str( int( multicore["ip"] ))
        resume["multicores"] = [{"ip": ip,"cores":[]}]

        for core in multicore["coresName"]:
            resume["multicores"][ipId]["cores"].append({"idCPU":core, winVectorName: windows[:] })

        ipId=ipId+1

    return resume


def aggregateUtilizationTime(idSimulation,msWindowSize,infrastructure,msLastTime,mapIpCores,windows, amountOfWindows):
    myclient = pymongo.MongoClient("mongodb://localhost:27017/")
    mydb = myclient["simulation_platform"]
    mycol = mydb["simu_data"]

    resume = createResumeBaseByTime(idSimulation,msWindowSize,infrastructure,msLastTime,windows, amountOfWindows,"utilizationTime","msExecTimeWin")

    #data para el plot
    resume["plotInfo"]={
        "xrange":{"min":0,"max":amountOfWindows },
        "yrange":{"min":0,"max":float(1.1*msWindowSize)},
        "title":"server IP utilization time, "+str(int(msLastTime))+"ms by windows",
        "xlabel":"windows",
        "ylabel":"time",
    }

    #rellena informacion por core y ventana
    win = 0
    winIni = float(0)
    winEnd = float(msWindowSize)
    for doc in mycol.find({ "idSimulation": idSimulation,"objectType":"cpu"}).sort("msCurrentTime"):
        currentTime=float(doc["msCurrentTime"])

        core = doc["idCPU"]
        ipId = mapIpCores[core]["ipId"]
        coreId = mapIpCores[core]["coreId"]
        value = resume["multicores"][ipId]["cores"][coreId]["msExecTimeWin"][win]

        if winIni < currentTime and  currentTime < winEnd:
            value = value + doc["exceResp"]["msExecTime"]
            resume["multicores"][ipId]["cores"][coreId]["msExecTimeWin"][win] = value
        else:
            win = win + 1
            winIni = winEnd
            winEnd = winEnd + msWindowSize

    print("\n----------------------\n")
    print(str(resume))

    mycol = mydb["resumes"]
    mycol.insert_one(resume)


def aggregatePercentageUtilizationTime(idSimulation,msWindowSize,infrastructure,msLastTime,mapIpCores,windows, amountOfWindows):
    myclient = pymongo.MongoClient("mongodb://localhost:27017/")
    mydb = myclient["simulation_platform"]
    mycol = mydb["simu_data"]

    resume = createResumeBaseByTime(idSimulation,msWindowSize,infrastructure,msLastTime,windows, amountOfWindows,"percentageUtilizationTime","msPctgUseTimeWin")

    resume["plotInfo"]={
        "xrange":{"min":0,"max":amountOfWindows},
        "yrange":{"min":0,"max":110},
        "title":"server IP utilization, "+str(int(msWindowSize))+"ms by windows",
        "xlabel":"windows",
        "ylabel":"percentage",
    }

    win = 0
    winIni = float(0)
    winEnd = float(msWindowSize)
    for doc in mycol.find({ "idSimulation": idSimulation,"objectType":"cpu"}).sort("msCurrentTime"):
        currentTime=float(doc["msCurrentTime"])

        core = doc["idCPU"]
        ipId = mapIpCores[core]["ipId"]
        coreId = mapIpCores[core]["coreId"]
        value = resume["multicores"][ipId]["cores"][coreId]["msPctgUseTimeWin"][win]

        if winIni < currentTime and  currentTime < winEnd:
            value = value + doc["exceResp"]["msExecTime"]
            resume["multicores"][ipId]["cores"][coreId]["msPctgUseTimeWin"][win] = value
        else:
            win = win + 1
            winIni = winEnd
            winEnd = winEnd + msWindowSize


    for k,v in mapIpCores.items():
        ipId = v["ipId"]
        coreId = v["coreId"]

        for win in range(0, amountOfWindows):
            value = 100 * float(resume["multicores"][ipId]["cores"][coreId]["msPctgUseTimeWin"][win]/msWindowSize)
            resume["multicores"][ipId]["cores"][coreId]["msPctgUseTimeWin"][win] = value


    print(str(resume))

    mycol = mydb["resumes"]
    mycol.insert_one(resume)



def main(idSimulation,msWindowSize):
    infrastructure,mapIpCores = getInfrstructureByIdSimulation(idSimulation)
    msLastTime = lastTimeByIdSimulation(idSimulation)
    windows, amountOfWindows = getEmptyVectorOfWindows(msWindowSize,msLastTime)
    aggregateUtilizationTime(idSimulation,msWindowSize,infrastructure,msLastTime,mapIpCores,windows, amountOfWindows)
    aggregatePercentageUtilizationTime(idSimulation,msWindowSize,infrastructure,msLastTime,mapIpCores,windows, amountOfWindows)


if len(sys.argv)!=3:
    print "we need 2 parameters, 'idSimulation', 'msWindowSize'"
else :
    idSimulation = sys.argv[1]
    msWindowSize = float(sys.argv[2])

main(idSimulation,msWindowSize)

