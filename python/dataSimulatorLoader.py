import sys
import json
import pymongo

def loadInfrastructure(idSimulation,outputSimPlath):
    myclient = pymongo.MongoClient("mongodb://localhost:27017/")
    mydb = myclient["simulation_platform"]
    mycol = mydb["infrastructure"]

    file = open(outputSimPlath, "r")

    for l in file.readlines():
        swBulk = False
        line = l.replace("\n", "")
        d = json.loads(line)
        if(d["collection"]=="infrastructure"):

            document = d["content"]
            document["idSimulation"]=idSimulation

            result = mycol.insert(document)
            print(str(result))


def loadData(idSimulation,outputSimPlath):
    myclient = pymongo.MongoClient("mongodb://localhost:27017/")
    mydb = myclient["simulation_platform"]
    mycol = mydb["simu_data"]

    file = open(outputSimPlath, "r")
    swBulk = False
    cont = 0
    bulk = mycol.initialize_ordered_bulk_op()

    for l in file.readlines():
        swBulk = False
        line = l.replace("\n", "")
        d = json.loads(line)
        if(d["collection"]=="simu_data"):
            document=d["content"]
            document["idSimulation"]=idSimulation
            if cont<=1000:
                bulk.insert(document)
            else:
                result = bulk.execute()
                print(str(result))
                swBulk=True
                bulk = mycol.initialize_ordered_bulk_op()
                cont = 0

            cont=cont+1

    if swBulk==False:
        result = bulk.execute()
        print(str(result))

def main(idSimulation,outputSimPlath):
    loadInfrastructure(idSimulation,outputSimPlath)
    loadData(idSimulation,outputSimPlath)



if len(sys.argv)!=3:
    print "we need 2 parameters, 'idSimulation', 'outputSimPlath'"
else :
    idSimulation  =  sys.argv[1]
    outputSimPlath = sys.argv[2]



main(idSimulation,outputSimPlath)
