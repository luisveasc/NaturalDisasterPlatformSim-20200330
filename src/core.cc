#include "../include/core.h"
#include "../include/multicore.h"

extern shared_ptr<Monitor>MONITOR;

Core::Core(const string & _name,
    const uint64_t & _id,
    const uint64_t & _frecuency): process(_name){



    this->id=_id;
    this->frecuency=_frecuency;

  std::cout<<"CORE : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

Core::~Core(){
}

void Core::setParentMulticore(shared_ptr<Multicore> _multicore){
    this->multicore=_multicore;
}

void Core::inner_body( void ){
  while(1){
    processRequest();
  }
}

void Core::processRequest(void){

	if( this->queueExecutionRequest.empty( ) == true){
		std::cout <<"("<< this->time()<<")ms ["<<this->name()<< "] QUEUE_REQUEST EMPTY, GO TO SLEEP"<< std::endl;
        //Monitor::printServerQUEUE(std::to_string(this->multicore->ip),this->time(),this->name(),0,0,0);
        passivate();
	}
	else{

        //MONITOR->set_firstTime(this->name(),this->time());

        shared_ptr<ExecutionRequest> execRequest = this->queueExecutionRequest.front( );
        this->queueExecutionRequest.pop_front( );

        //std::cout <<"("<< this->time()<<")ms ["<<this->name()<< "] BEFORE "<<execRequest->toString()<< std::endl;
        shared_ptr<ExecuteResponse> resp = execRequest->work->execute(execRequest->msg, this->multicore->ram, this->multicore->hhd);
        hold(resp->executionTime);
        //std::cout <<"("<< this->time()<<")ms ["<<this->name()<< "] AFTER "<<execRequest->toString()<< std::endl;

        MONITOR->printServerCPU(std::to_string(this->multicore->ip),this->time(),this->name(),execRequest->msg->des,
                std::to_string(execRequest->work->idpgm),std::to_string(execRequest->work->idActivity),
                execRequest->work->descrip,resp);

        MONITOR->printServerQUEUE(std::to_string(this->multicore->ip),this->time(),this->name(),0,1);


        if(resp->msg!= nullptr){
        std::cout <<"("<< this->time()<<")ms ["<<this->name()<< "] REDIRECT MESSAGE ["<<resp->msg->toString()<< "] "<< std::endl;
        execRequest->work->network->addMessage(resp->msg);
        if(execRequest->work->network->idle()){
            execRequest->work->network->activate();
        }
    }
  }
}

void Core::addExecutionRequest(shared_ptr<ExecutionRequest> execRequest){
    this->queueExecutionRequest.push_back(execRequest);
    MONITOR->printServerQUEUE(std::to_string(this->multicore->ip),this->time(),this->name(),1,0);
}


string Core::toString(void){
  char txt[200];
  sprintf(txt,"{name:%s, id:%"PRIu64", frecuency:%"PRIu64"}",
    this->name().c_str(),this->id,this->frecuency);
  return txt;
}

