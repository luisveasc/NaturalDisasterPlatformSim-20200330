#include "../include/network.h"
#include "../include/programdeployment.h"


extern shared_ptr<Monitor>MONITOR;

Network::Network(const string & name, const double & v,
  const string & urt) : process(name){

    this->velocity=v;
    this->unitTrasferRate=urt;
    bpmsVelocityCalculate(this->velocity,this->unitTrasferRate);

  std::cout<<"Network : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

Network::~Network(){
 //this->mapPgmDeployments.clear();
 this->queueMessages.clear();
}

void Network::bpmsVelocityCalculate(const double & v, const string & urt){

  if(v == 0){
    this->bpmsVelocity = 0;
  } else if(urt.compare("bps")==0){
    this->bpmsVelocity = double(1.0)/double(1000.0);
  } else if(urt.compare("kbps")==0){
    this->bpmsVelocity = v * ( double(1000.0)/double(1000.0) );
  } else if(urt.compare("mbps")==0){
    this->bpmsVelocity = v * ( double(1000000.0)/double(1000.0) );
  } else if(urt.compare("gbps")==0){
    this->bpmsVelocity = v * ( double(1000000000.0)/double(1000.0) );
  }

}

void Network::inner_body( void ){
  while(1){
    processMessage();
  }
}

void Network::processMessage(void){

    if( this->queueMessages.empty( ) == true){
		std::cout <<"("<< this->time()<<")ms ["<<this->name()<< "] queueMessages EMPTY, GO TO SLEEP"<< std::endl;
        //Monitor::printServerNETWORK(msg->ori,msg->des, this->time(),0,0,0,0,0);
        passivate();
	}
	else{

        double bpmsTime=0;
        shared_ptr<Message> msg = this->queueMessages.front( );
		this->queueMessages.pop_front( );
        std::cout <<"("<< this->time()<<")ms ["<<this->name()<< "] "<<msg->toString()<< std::endl;

        if(this->bpmsVelocity!=0) {
            double bpmsTime = double(msg->sizebytes * 8) / (this->bpmsVelocity);

        }
        //TODO corregir cuando se tengan los bechmark de latencia de red
        bpmsTime=0;
        hold(bpmsTime);
        MONITOR->printServerNETWORK(msg->ori,msg->des, this->time(),0,1,msg->sizebytes,bpmsTime);

        this->mapPgmDeployments[msg->des]->addRequest(msg);
    }
}

void Network::addMessage(shared_ptr<Message> msg){
    this->queueMessages.push_back(msg);
    MONITOR->printServerNETWORK(msg->ori,msg->des, this->time(),1,0,0,0);
}

void Network::addProgramDeployments(map<string,shared_ptr<ProgramDeployment>> mappd, handle<Network> network){

  for (auto it = mappd.begin(); it != mappd.end(); it++ ){
    shared_ptr<ProgramDeployment> pd = (shared_ptr<ProgramDeployment>)(it->second);
    pd->setNetwork(network);
    this->mapPgmDeployments[it->first]=pd;
  }

  //this->mapPgmDeployments.insert(mappd.begin(),mappd.end());
}

string Network::toString(){
  char txt[200];
  sprintf(txt,"{velocity:%f, unitTrasferRate:%s, bpmsVelocity:%f, mapPgmDeployments:%d}",this->velocity,
      this->unitTrasferRate.c_str(),this->bpmsVelocity,this->mapPgmDeployments.size());
  return txt;
}
