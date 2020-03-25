#ifndef EXECUTERESPONSE_H
#define EXECUTERESPONSE_H

#include "glob.h"
#include "message.h"

class ExecuteResponse{

	public:
		shared_ptr<Message> msg;
		double executionTime;
		uint64_t bytesUsedRam; 		//usado por el proceso
		uint64_t totalBytesUsedRam; //usado en multicore
		uint64_t totalBytesRam;     //total de ram en el multicore
		uint64_t bytesUsedHHD; 		//usado por el proceso
		uint64_t totalBytesUsedHHD; //usado en multicore
		uint64_t totalBytesHHD;     //total de hhd en el multicore


	public:
		ExecuteResponse(shared_ptr<Message> _msg, double _execTime);
		ExecuteResponse(shared_ptr<Message> _msg, double _execTime, uint64_t _bytesUsedRam, uint64_t _totalBytesUsedRam,
				 uint64_t _totalBytesRam,uint64_t _bytesUsedHHD,uint64_t _totalBytesUsedHHD,uint64_t _totalBytesHHD);
		~ExecuteResponse();
		string toString();

};

#endif
