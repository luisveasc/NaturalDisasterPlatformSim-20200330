#ifndef MONITOR_H
#define MONITOR_H

#include "glob.h"
#include "executeresponse.h"



class Monitor{

    private:
        string idSimulation;
        string filePath;
        string filePathBlk;
        std::ofstream outputFile;
        std::ofstream outputFileBlk;

    public:
    Monitor(const string & idSimulation, const string & outputFilePath);
    ~Monitor();

    void close();


    void printIniSimulation(const double & currentTime);

    void printEndSimulation(const double & currentTime);

    void printServerCPU(const string & ip,const double & currentTime,const string & idCpu,const string & idDeployment,
            const string & idpgm,const string & idActivity,const string & workDescrip, const shared_ptr<ExecuteResponse>  & exceResp);

    void printServerQUEUE(const string & ip,const double & currentTime,const string & idCpu,
            const uint64_t & nbrMsgReceived,const uint64_t & nbrMsgProcessed );

    void printServerNETWORK(const string & ori,const string & des, const double & currentTime,
            const uint64_t & nbrMsgSent,const uint64_t & nbrMsgTrasmitted,
            const uint64_t & sizebytesMsgTrasmitted, const double & timeToMsgTrasmitted );

    void printInfrastructureMulticores(const json & jmulticores);


    };

#endif
