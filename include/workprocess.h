#ifndef WORKPROCESS_H
#define WORKPROCESS_H

#include "glob.h"
#include "work.h"

class WorkProcess: public Work {

	public:
		WorkProcess(const json & _data, const uint64_t & _idpgm,
	const uint64_t & _idActivity, const string & _descrip);
		~WorkProcess();
    shared_ptr<ExecuteResponse> execute(shared_ptr<Message> msg,shared_ptr<RAM> ram, shared_ptr<HHD> hhd);

};

#endif
