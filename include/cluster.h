#ifndef CLUSTER_H
#define CLUSTER_H

#include "glob.h"
#include "multicore.h"

class Cluster{

  public:
    string name;
    uint64_t id;
    vector < shared_ptr<Multicore> > multicores;

  public:
    Cluster(const string & _name, const float & _id,
      vector < shared_ptr<Multicore> > _multicores);
    Cluster(const	json  & _cluster,vector < shared_ptr<Multicore> > _multicores);
    ~Cluster();

    string toString(void);

};

#endif
