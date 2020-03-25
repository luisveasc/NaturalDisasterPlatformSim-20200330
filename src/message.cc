#include "../include/message.h"

Message::Message(const Message & msg){
  this->ori=msg.ori;
  this->des=msg.des;
  this->idmsg=msg.idmsg;
  this->idActivity=msg.idActivity;
  this->sizebytes=msg.sizebytes;
  this->content=msg.content;
}

Message::Message(const json & msg){
  this->ori=msg["ori"];
  this->des=msg["des"];
  this->idmsg=msg["idmsg"];
  this->idActivity=msg["idActivity"];
  this->sizebytes=msg["sizebytes"];
  this->content=msg["content"];
}

Message::Message(const string& o,const string& d,const string& id,
  const uint64_t& idact,const uint64_t &size,const json& ctnt){

    this->ori=o;
    this->des=d;
    this->idmsg=id;
    this->idActivity=idact;
    this->sizebytes=size;
    this->content=ctnt;

}

Message::~Message(){
}

string Message::toString(){
  char txt[200];
  sprintf(txt,"{ori:%s,des:%s,idmsg:%s, idActivity:%"PRIu64"}",this->ori.c_str(),
      this->des.c_str(),this->idmsg.c_str(),this->idActivity);
  return txt;
}


string Message::getIdActivityDeploymentAsigned( void ){
        char id[200];
        sprintf(id,"%s_%"PRIu64"",this->des.c_str(),this->idActivity);
        return id;

}