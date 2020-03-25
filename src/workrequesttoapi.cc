#include "../include/workrequesttoapi.h"

WorkRequestToApi::WorkRequestToApi(const json & _data, const uint64_t & _idpgm,
        const uint64_t & _idActivity, const string & _descrip) : Work(_data,_idpgm,_idActivity,_descrip){
}

WorkRequestToApi::~WorkRequestToApi(void){
}

shared_ptr<ExecuteResponse> WorkRequestToApi::execute(shared_ptr<Message> msg,shared_ptr<RAM> ram, shared_ptr<HHD> hhd){
  double time = 0;
  //cambiar el destino segun la informacion del work (data)
  msg->ori = msg->des;
  msg->des = this->configConn[ data["config_conn"] ];
  msg->idActivity =  data["next_activity"];

    //uso de ram
    uint64_t bytesUsedRam = 0;
    ram->incrOccupiedbytes(bytesUsedRam);
    uint64_t totalBytesUsedRam = ram->occupiedbytes;
    uint64_t totalBytesRam = ram->sizebytes;

    //uso de hhd
    uint64_t bytesUsedHHD = 0;
    hhd->incrOccupiedbytes(bytesUsedHHD);
    uint64_t totalBytesUsedHHD = hhd->occupiedbytes;
    uint64_t totalBytesHHD =  hhd->sizebytes;

  shared_ptr<ExecuteResponse> resp = make_shared<ExecuteResponse>(msg,time,bytesUsedRam,totalBytesUsedRam,totalBytesRam,
                                                                  bytesUsedHHD,totalBytesUsedHHD,totalBytesHHD);
  return resp;
}
