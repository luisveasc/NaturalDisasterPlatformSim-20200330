#include "../include/workprocess.h"
#include "../include/programdeployment.h"


WorkProcess::WorkProcess( const json & _data, const uint64_t & _idpgm,
const uint64_t & _idActivity, const string & _descrip) : Work(_data,_idpgm,_idActivity,_descrip){
}

WorkProcess::~WorkProcess(void){
}

shared_ptr<ExecuteResponse> WorkProcess::execute(shared_ptr<Message> msg,shared_ptr<RAM> ram, shared_ptr<HHD> hhd){

    double time = 0;

    static std::random_device rd;
    static std::mt19937 gen(rd());

    vector<double> params	=  this->data["time_fun_distribution"]["params"].get<std::vector<double>>();
    string typeDistr = this->data["time_fun_distribution"]["type"];
    if(typeDistr=="norm"){
    std::normal_distribution<double> distribution(params[0],params[1]);
        time=distribution(gen);
    } else if(typeDistr=="cauchy"){
        std::cauchy_distribution<double> distribution(params[0],params[1]);
        time=distribution(gen);
    } else if(typeDistr=="chi2"){
        std::chi_squared_distribution<double> distribution(params[0]);
        time=distribution(gen)*params[2]+params[1];
    } else if(typeDistr=="expon"){
        std::exponential_distribution<double> distribution(params[0]);
        time=distribution(gen)*params[2]+params[1];
    } else if(typeDistr=="uniform"){
        std::uniform_real_distribution<double> distribution(params[0],params[1]);
        time=distribution(gen);
    }

    //uso de ram
    uint64_t bytesUsedRam = 10;
    ram->incrOccupiedbytes(bytesUsedRam);
    uint64_t totalBytesUsedRam = ram->occupiedbytes;
    uint64_t totalBytesRam = ram->sizebytes;

    //uso de hhd
    uint64_t bytesUsedHHD = 100;
    hhd->incrOccupiedbytes(bytesUsedHHD);
    uint64_t totalBytesUsedHHD = hhd->occupiedbytes;
    uint64_t totalBytesHHD =  hhd->sizebytes;


    shared_ptr<ExecuteResponse> resp = make_shared<ExecuteResponse>(nullptr,time,bytesUsedRam,totalBytesUsedRam,totalBytesRam,
                                                                    bytesUsedHHD,totalBytesUsedHHD,totalBytesHHD);
    return resp;

}
