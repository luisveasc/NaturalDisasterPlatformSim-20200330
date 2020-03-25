#ifndef EXECUTIONREQUEST_H
#define EXECUTIONREQUEST_H

#include "glob.h"
#include "work.h"
#include "message.h"

class ExecutionRequest{
  public:
    shared_ptr<Work> work;
    shared_ptr<Message> msg;

  public:
    ExecutionRequest(shared_ptr<Work> _work,shared_ptr<Message> _msg);
    ~ExecutionRequest();
    string toString();

};
#endif
