#include "../include/multicore.h"
#include "../include/core.h"
#include "../include/operatorsystem.h"

Multicore::Multicore(const string & _name,
    const uint64_t & _ip,
    vector < handle< Core > > _cores,
    shared_ptr<RAM> _ram,
    shared_ptr<HHD> _hhd){

  this->name=_name;
  this->ip=_ip;
  this->cores = _cores;
  this->ram = _ram;
  this->hhd = _hhd;
}

Multicore::Multicore(const json & multicore){

  this->name = multicore["name"];
  this->ip = multicore["ip"];
  this->ram = make_shared<RAM>(multicore["ram"]["size_bytes"],multicore["ram"]["occupied_bytes"]);
  this->hhd = make_shared<HHD>(multicore["hhd"]["size_bytes"],multicore["hhd"]["occupied_bytes"]);

  char name[100];
  int n = multicore["nbr_cores"];
  for (int i=0;i<n;i++){
    sprintf(name,"IP%"PRIu64"_CORE%d",this->ip,i);
    this->cores.push_back( new Core(name,i,multicore["frecuency"]) );
  }
  std::cout<<"MULTICORE : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

Multicore::~Multicore(){
  //delete de los core o utilizar los punteros inteligentes
  this->cores.clear();
  std::cout<<"MULTICORE : "<<this->toString()<<" WAS DELETED"<<std::endl;
}

void Multicore::createSO(shared_ptr<Multicore> multicore){
    this->os = make_shared<OperatorSystem>(multicore);
    //load shared_ptr del multicore a cada core
    int n = this->cores.size();
    for (int i=0;i<n;i++){
        this->cores[i]->setParentMulticore(multicore);
    }
}



void Multicore::addProgramDeploymentOS(shared_ptr<ProgramDeployment> pd){
  this->os->addProgramDeployment(pd,this->os);
}

map<string,shared_ptr<ProgramDeployment>> Multicore::getProgramDeploymentsOS(void){
  return this->os->getPgmDeployments();
}

void Multicore::activate(void){
  int n = this->cores.size();
  for(int i=0; i<n;i++){
    this->cores[i]->activate();
  }
}

void Multicore::cancel(void){
  int n = this->cores.size();
  for(int i=0; i<n;i++){
    this->cores[i]->cancel();
  }
}

string Multicore::toString(void){
  char txt[400];
  sprintf(txt,"{name:%s, ip:%"PRIu64", cores=%d, ram:%s, hhd:%s}",
    this->name.c_str(),this->ip,this->cores.size(),this->ram->toString().c_str(),
    this->hhd->toString().c_str());
  return txt;
}

json Multicore::toJson(){

  json jcores = json::array();

  int m =  this->cores.size();
  for( int j=0; j<m; j++){
    jcores.push_back( this->cores[j]->name() );
  }

  return {{"name",this->name},
          {"ip",this->ip},
          {"coresName",jcores},
          {"frecuency",this->ip},
          {"ram",{{"sizeBytes",this->ram->sizebytes},
                  {"occupiedBytes",this->ram->occupiedbytes}
                 }
          },
          {"hhd",{{"sizeBytes",this->hhd->sizebytes},
                  {"occupiedBytes",this->hhd->occupiedbytes}
                 }
          }};
}
