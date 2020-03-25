#include "../include/client.h"

Client::Client(const string & _name, const string & _pathTrace,
			handle<Network> _network) : process(_name){

	this->pathTrace = _pathTrace;
	this->traceFile.open(this->pathTrace);
	this->network = _network;

	std::cout<<"CLIENT : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

Client::~Client(){
}

void Client::inner_body( void ){
  while(1){
    generateRequestByTrace();
  }
}

void Client::generateRequestByTrace(void){

	if (this->traceFile.is_open()) {

			string line;
	    if (getline(this->traceFile, line)) {

					json data = json::parse(line);
                    hold(data["timeHold"]);
					json jmsg = data["message"];
					std::cout <<"("<< this->time()<<")ms ["<<this->name()<< "] SEND MESSAGE "<<jmsg.dump()<< std::endl;

					shared_ptr<Message> msg = make_shared<Message>(jmsg);
					this->network->addMessage(msg);
					this->network->activate();


	    } else {
		    this->traceFile.close();
				this->passivate();
		}

	}
}

string Client::toString(void){
	char txt[200];
	sprintf(txt,"{name:%s, pathTrace:%s}",this->name().c_str(),
							this->pathTrace.c_str());
	return txt;

}
