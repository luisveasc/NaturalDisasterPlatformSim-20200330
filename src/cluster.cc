#include "../include/cluster.h"


Cluster::Cluster(const string & _name,const float & _id,
    vector <shared_ptr<Multicore >> _multicores ){
  this->name=_name;
  this->id=_id;
  this->multicores=_multicores;
}


Cluster::Cluster(const json  & cluster, vector < shared_ptr<Multicore> > _multicores){
  this->name=cluster["name"];
  this->id=cluster["id"];
  int n = cluster["multicores"].size();

  for (int i=0;i<n;i++){
    this->multicores.push_back( _multicores[ cluster["multicores"].at(i) ] );
  }

  std::cout<<"CLUSTER : "<<this->toString()<<" WAS CREATED"<<std::endl;
}

Cluster::~Cluster(){
  this->multicores.clear();
  std::cout<<this->toString()<<" WAS DELETED"<<std::endl;
}

string Cluster::toString(void){
  char txt[200];
  sprintf(txt,"{name:%s, id:%"PRIu64", multicores=%"PRIu64"}",
  this->name.c_str(),this->id,this->multicores.size());
  return txt;
}
