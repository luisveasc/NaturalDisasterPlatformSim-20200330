#include "../include/executeresponse.h"

ExecuteResponse::ExecuteResponse(shared_ptr<Message> _msg, double _execTime){
	this->msg = _msg;
	this->executionTime = _execTime;
}

ExecuteResponse::ExecuteResponse(shared_ptr<Message> _msg, double _execTime, uint64_t _bytesUsedRam, uint64_t _totalBytesUsedRam,
                                 uint64_t _totalBytesRam,uint64_t _bytesUsedHHD,uint64_t _totalBytesUsedHHD,uint64_t _totalBytesHHD){
    this->msg = _msg;
    this->executionTime = _execTime;
    this->bytesUsedRam = _bytesUsedRam; 		//usado por el proceso
    this->totalBytesUsedRam = _totalBytesUsedRam; //usado en multicore
    this->totalBytesRam = _totalBytesRam;     //total de ram en el multicore
    this->bytesUsedHHD = _bytesUsedHHD; 		//usado por el proceso
    this->totalBytesUsedHHD = _totalBytesUsedHHD; //usado en multicore
    this->totalBytesHHD = _totalBytesHHD;     //total de ram en el multicore
}


ExecuteResponse::~ExecuteResponse(){
}

string ExecuteResponse::toString(void){
  char txt[200];
  sprintf(txt,"{msg:%s, executionTime:%f}",
    this->msg->toString().c_str(),this->executionTime);
  return txt;
}
