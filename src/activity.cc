#include "../include/activity.h"


Activity::Activity(const uint64_t & _id,const uint64_t & _idpgm, const string & _name,
  vector<shared_ptr<Work>> _works){

    this->id=_id;
    this->idpgm = _idpgm;
    this->name=_name;
    this->works=_works;
}

Activity::Activity(const uint64_t & _idpgm,const json & activity){

    this->id=activity["id"];
    this->idpgm = _idpgm;
    this->name=activity["name"];
    int n = activity["works"].size();

    for(int i=0; i<n; i++){
      this->works.push_back(FactoryWork::CreateWork(activity["works"].at(i),this->idpgm,this->id));
    }

  std::cout<<"Activity : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

Activity::~Activity(){
}

string Activity::toString(void){
  char txt[400];
  sprintf(txt,"{name:%s, id:%"PRIu64", works=%d}",this->name.c_str(),
              this->id,this->works.size());
  return txt;
}
