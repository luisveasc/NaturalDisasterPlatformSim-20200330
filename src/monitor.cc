#include "../include/monitor.h"

Monitor::Monitor(const string & idSimulation, const string & outputFilePath){

    this->filePath = outputFilePath+idSimulation+".dat";
    this->filePathBlk = outputFilePath+idSimulation+".blk";

    this->outputFile.open(this->filePath.c_str());
    this->outputFileBlk.open(this->filePathBlk.c_str());
}

Monitor::~Monitor(){
}

void Monitor::close(){

    this->outputFile.close();
    this->outputFileBlk.close();
    remove(this->filePathBlk.c_str());

}

void Monitor::printIniSimulation(const double & currentTime){
    json resume={{"msIniSimulation",currentTime}};
    string txt=resume.dump()+"\n";
    this->outputFile<<txt;
    std::cout<<"MONITOR=>"<<txt;
}


void Monitor::printEndSimulation(const double & currentTime){
    json resume={{"msEndSimulation",currentTime}};
    string txt=resume.dump()+"\n";
    this->outputFile<<txt;
    std::cout<<"MONITOR=>"<<txt;

}


void Monitor::printServerCPU(const string & ip,const double & currentTime,const string & idCpu,const string & idDeployment,
            const string & idpgm,const string & idActivity,const string & workDescrip, const shared_ptr<ExecuteResponse>  & exceResp){
    json resume= {{"collection", "simu_data"},
                  {"content",
                    {
                        {"infrastructureType","server"},
                        {"objectType", "cpu"},
                        {"ip", ip},
                        {"msCurrentTime",currentTime},
                        {"idCPU",idCpu},
                        {"idDeployment",idDeployment},
                        {"idpgm",idpgm},
                        {"idActivity",idActivity},
                        {"workDescrip",workDescrip},
                        {"exceResp",
                            {
                            {"msExecTime", exceResp->executionTime},
                            {"bytesUsedRam", exceResp->bytesUsedRam},
                            {"totalBytesUsedRam", exceResp->totalBytesUsedRam},
                            {"totalBytesRam", exceResp->totalBytesRam},
                            {"bytesUsedHHD", exceResp->bytesUsedHHD},
                            {"totalBytesUsedHHD", exceResp->totalBytesUsedHHD},
                            {"totalBytesHHD", exceResp->totalBytesHHD}
                            }

                        }
                    }
                  }
    };

    string txt=resume.dump()+"\n";
    this->outputFile<<txt;
    std::cout<<"MONITOR=>"<<txt;
}

void Monitor::printServerQUEUE(const string & ip,const double & currentTime,const string & idCpu,
            const uint64_t & nbrMsgReceived,const uint64_t & nbrMsgProcessed ){
    json resume=
            {{"collection", "simu_data"},
             {"content",    {
                                    {"infrastructureType", "server"},
                                    {"objectType", "queue"},
                                    {"ip", ip},
                                    {"msCurrentTime", currentTime},
                                    {"idCPU", idCpu},
                                    {"nbrMsgReceived", nbrMsgReceived},
                                    {"nbrMsgProcessed", nbrMsgProcessed}
                            }}
            };

    string txt=resume.dump()+"\n";
    this->outputFile<<txt;
    std::cout<<"MONITOR=>"<<txt;
}


void Monitor::printServerNETWORK(const string & ori,const string & des, const double & currentTime,
            const uint64_t & nbrMsgSent,const uint64_t & nbrMsgTrasmitted,
            const uint64_t & sizebytesMsgTrasmitted, const double & timeToMsgTrasmitted ){
    json resume={{"collection", "simu_data"},
                 {"content", {
                                {"infrastructureType","network"},
                                {"objectType", "network"},
                                {"ori", ori},
                                {"des", des},
                                {"msCurrentTime",currentTime},
                                {"nbrMsgSent",nbrMsgSent},
                                {"nbrMsgTrasmitted",nbrMsgTrasmitted},
                                {"sizebytesMsgTrasmitted",sizebytesMsgTrasmitted},
                                {"timeToMsgTrasmitted",timeToMsgTrasmitted}
                             }}

                };

    string txt=resume.dump()+"\n";
    this->outputFile<<txt;
    std::cout<<"MONITOR=>"<<txt;
}


void Monitor::printInfrastructureMulticores(const json & jmulticores){

    json resume = {{"collection", "infrastructure"},
                   {"content", {{"multicores", jmulticores}}}
                  };
    string txt=resume.dump()+"\n";
    this->outputFile<<txt;
    std::cout<<"MONITOR=>"<<txt;
}



