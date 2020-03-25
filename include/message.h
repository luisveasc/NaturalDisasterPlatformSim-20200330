#ifndef MESSAGE_H
#define MESSAGE_H

#include "glob.h"

class Message
{
  public:
    string ori;
    string des;
    string idmsg;
    uint64_t idActivity;
    uint64_t sizebytes;
    json content;

  public:
    Message(const Message & msg);
    Message(const json & msg);
    Message(const string& o,const string& d,const string& id,
      const uint64_t& idact,const uint64_t &size,const json& ctnt);
    ~Message();
    string toString();
    string getIdActivityDeploymentAsigned( void );
};

#endif
