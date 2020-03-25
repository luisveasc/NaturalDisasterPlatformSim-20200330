#ifndef MULTICORE_H
#define MULTICORE_H

#include "glob.h"
//#include "core.h"
#include "ram.h"
#include "hhd.h"
#include "programdeployment.h"

class Core;
class OperatorSystem;
class Multicore{

  public:
    string name;
    uint64_t ip;
    vector < handle< Core > > cores;
    shared_ptr<RAM> ram;
    shared_ptr<HHD> hhd;
    shared_ptr<OperatorSystem> os;

  public:
    Multicore(const string & name,
      const uint64_t & ip,
      vector < handle< Core > > _cores,
      shared_ptr<RAM> _ram,
      shared_ptr<HHD> _hhd
    );

    Multicore(const json & multicore);
    ~Multicore();
    void createSO(shared_ptr<Multicore> multicore);
    void addProgramDeploymentOS(shared_ptr<ProgramDeployment> pd);
    map<string,shared_ptr<ProgramDeployment>> getProgramDeploymentsOS(void);
    string toString(void);
    void activate(void);
    void cancel(void);
    json toJson();

};

#endif
