#include "../include/executionrequest.h"

ExecutionRequest::ExecutionRequest(shared_ptr<Work> _work,
      shared_ptr<Message> _msg){
  this->work = _work;
  this->msg = _msg;
}

ExecutionRequest::~ExecutionRequest(){
}

string ExecutionRequest::toString(void){
  char txt[2000];
  sprintf(txt,"{work:%s, msg:%s}",this->work->toString().c_str(),
    this->msg->toString().c_str());
  return txt;
}
