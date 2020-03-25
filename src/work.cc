#include "../include/work.h"

Work::Work( const json & _data, const uint64_t & _idpgm,
        const uint64_t & _idActivity, const string & _descrip){
    this->data=_data;
    this->idpgm=_idpgm;
    this->idActivity=_idActivity;
    this->descrip=_descrip;
    std::cout<<"Work : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

Work::~Work(void){

}

void Work::setConfigConn(map<string,string> cc){
  this->configConn = cc;
}

void Work::setNetwork(handle<Network> net){
  this->network = net;
}

string Work::toString(){

  string txt="{data:"+this->data.dump()+",idpgm:"+std::to_string(this->idpgm)+",idActivity:"+std::to_string(this->idActivity)+",descrip:"+this->descrip+"}";

  return txt;
}
