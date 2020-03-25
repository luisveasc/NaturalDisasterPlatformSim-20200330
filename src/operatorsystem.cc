#include "../include/operatorsystem.h"
#include "../include/multicore.h"
#include "../include/core.h"
#include "../include/programdeployment.h"

OperatorSystem::OperatorSystem(shared_ptr<Multicore> _multicore){

  this->multicore=_multicore;
  this->lastCoreAssigned=0;
  std::cout<<"OperatorSystem : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

OperatorSystem::~OperatorSystem(){
  //delete de los core o utilizar los punteros inteligentes
  this->mapPgmDeployments.clear();
  this->mapCoreAssignation.clear();
}

void OperatorSystem::addProgramDeployment(shared_ptr<ProgramDeployment> pd,
  shared_ptr<OperatorSystem> _os){
    pd->os = _os;
    this->mapPgmDeployments[pd->id]=pd;

    for(int i=0;i<pd->nbrThreads; i++){

        if(this->lastCoreAssigned >= this->multicore->cores.size()){
          this->lastCoreAssigned=0;
        }

        this->mapCoreAssignation[ pd->idThreads[i] ] = this->lastCoreAssigned;
        this->lastCoreAssigned++;

    }

  //std::cout<<"OperatorSystem : "<<this->toString()<<" WAS assigned"<<std::endl;
}

void OperatorSystem::addExecutionRequestToCore(string keyAssignation,
    shared_ptr<ExecutionRequest> exeReq){

    int pos = this->mapCoreAssignation[keyAssignation];
    //std::cout<<"keyAssignation;"<< keyAssignation<<";mapCoreAssignation;"<<pos<<";id;"<<exeReq->msg->getIdActivityDeploymentAsigned()<<std::endl;

    this->multicore->cores[pos]->addExecutionRequest(exeReq);
    if(this->multicore->cores[pos]->idle()){
      this->multicore->cores[pos]->activate();
    }

}

map<string,shared_ptr<ProgramDeployment>> OperatorSystem::getPgmDeployments(void){
  return this->mapPgmDeployments;
}

string OperatorSystem::toString(){
  char txt[200];
  sprintf(txt,"{pgmDeployments:%d, mapCoreAssignation:%d}",
        this->mapPgmDeployments.size(), this->mapCoreAssignation.size());
  return txt;
}
