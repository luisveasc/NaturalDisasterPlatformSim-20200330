#ifndef WORK_H
#define WORK_H

#include "glob.h"
#include "message.h"
#include "executeresponse.h"
#include "network.h"
#include "ram.h"
#include "hhd.h"

class Work{

  public:
    json data;
	uint64_t idpgm;
	uint64_t idActivity;
    string descrip;
    map<string,string> configConn;
    handle<Network> network;

	public:
    Work( const json & _data, const uint64_t & _idpgm, const uint64_t & _idActivity, const string & _descrip);
    ~Work(void);
    virtual shared_ptr<ExecuteResponse> execute(shared_ptr<Message> msg,shared_ptr<RAM> ram, shared_ptr<HHD> hhd) = 0;
    void setConfigConn(map<string,string> cc);
    string toString();
    void setNetwork(handle<Network> net);

};

#endif
