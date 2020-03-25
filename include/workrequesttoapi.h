#ifndef WORKREQUESTTOAPI_H
#define WORKREQUESTTOAPI_H

#include "glob.h"
#include "work.h"

class WorkRequestToApi: public Work {

	public:
		WorkRequestToApi(const json & _data, const uint64_t & _idpgm,
				const uint64_t & _idActivity, const string & _descrip);
		~WorkRequestToApi();
    shared_ptr<ExecuteResponse> execute(shared_ptr<Message> msg,shared_ptr<RAM> ram, shared_ptr<HHD> hhd);

};

#endif
