#include "../include/program.h"

Program::Program(const string & _name,
      const uint64_t & _id,
      vector<string> _config_conn,
      vector<shared_ptr<Activity>> _activities){
    this->name=_name;
    this->id=_id;
    this->config_conn=_config_conn;
    this->activities=_activities;

}

Program::Program(const json & program){
  this->name=program["name"];
  this->id=program["id"];
  this->config_conn=program["config_conn"].get<vector<string>>();
  int n = program["activities"].size();
  for(int i=0;i<n;i++){
    this->activities.push_back( make_shared<Activity>( this->id , program["activities"].at(i) ) );
  }

  std::cout<<"PROGRAM : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

Program::~Program(){
  this->config_conn.clear();
  this->activities.clear();
}

string Program::toString(){
  char txt[200];
  sprintf(txt,"{name:%s,id:%"PRIu64",config_conn:%d, activities:%d}",
    this->name.c_str(),this->id,this->config_conn.size(),this->activities.size());
  return txt;
}
