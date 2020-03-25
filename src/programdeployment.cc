#include "../include/programdeployment.h"
#include "../include/operatorsystem.h"
//#include "../include/network.h"


ProgramDeployment::ProgramDeployment(const json & pd,
	shared_ptr<Program> _program){

    this->ip=pd["ip"];
    this->port=pd["port"];
    this->id=pd["id"];
	this->nbrThreads=pd["nbr_threads"];
    this->program=_program;

		char txt[20];
		int n;
		n = this->nbrThreads;
		for(int i=0; i<n; i++){
			sprintf(txt,"%s_%d",this->id.c_str(),i);
			this->idThreads.push_back(txt);
		}

		n = pd["config_conn"].size();
		for(int i=0; i<n; i++){
			string key=pd["config_conn"].at(i)["key"];
			string value=pd["config_conn"].at(i)["value"];
			this->configConn[key]=value;
		}

		setWorksConfigConn();
		std::cout<<"ProgramDeployment : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

ProgramDeployment::~ProgramDeployment(){
}

void ProgramDeployment::addRequest(shared_ptr<Message> msg){


	if(this->lastUsedThread >= this->nbrThreads){
			this->lastUsedThread=0;
	}

	shared_ptr<Activity> act = this->program->activities[ msg->idActivity ];
	int n = act->works.size();
    for(int i=0;i<n;i++){

		this->os->addExecutionRequestToCore(this->idThreads[this->lastUsedThread],
								make_shared<ExecutionRequest>(act->works[i],msg));

	}
	//agregar a la cola del core
	this->lastUsedThread++;

}

void ProgramDeployment::setWorksConfigConn( void ){
	int n = this->program->activities.size();
	for(int i=0; i<n; i++){
		int m = this->program->activities[i]->works.size();
		for(int j=0; j<m; j++){
			this->program->activities[i]->works[j]->setConfigConn(this->configConn);
		}
	}
}

void ProgramDeployment::setNetwork(handle<Network> _network){
	int n = this->program->activities.size();
	for(int i=0; i<n; i++){
		int m = this->program->activities[i]->works.size();
		for(int j=0; j<m; j++){
			this->program->activities[i]->works[j]->setNetwork(_network);
		}
	}
}

string ProgramDeployment::toString(void){
	char txt[400];
  sprintf(txt,"{ip:%"PRIu64",port:%"PRIu64", id:%s, nbr_threads=:%"PRIu64", config_conn:%d, program:%s,idThreads:%d}",
    this->ip,this->port,this->id.c_str(),this->nbrThreads,this->configConn.size(),
		this->program->toString().c_str(),this->idThreads.size());
  return txt;
}
