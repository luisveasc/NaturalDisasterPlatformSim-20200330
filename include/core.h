#ifndef CORE_H
#define CORE_H

#include "glob.h"
#include "executionrequest.h"
#include "executeresponse.h"
#include "monitor.h"

class Multicore;
class Core: public process{

	public:
    shared_ptr<Multicore> multicore;
    uint64_t id;
    uint64_t frecuency;
    list<shared_ptr<ExecutionRequest>> queueExecutionRequest;
	protected:
    void inner_body( void );

  public:
    Core(const string & _name,const uint64_t & _id, const uint64_t & _frecuency);
    ~Core();
		string toString(void);

    void processRequest(void);
    void setParentMulticore(shared_ptr<Multicore> _multicore);
	void addExecutionRequest(shared_ptr<ExecutionRequest> execRequest);

};
#endif
