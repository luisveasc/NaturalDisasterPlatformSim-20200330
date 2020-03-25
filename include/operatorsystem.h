#ifndef OPERATORSYSTEM_H
#define OPERATORSYSTEM_H

#include "glob.h"
#include "executionrequest.h"

class Multicore;
class Core;
class ProgramDeployment;
class OperatorSystem{

  public:
    map<string,shared_ptr<ProgramDeployment>> mapPgmDeployments;
    map<string,int> mapCoreAssignation; //ip_port_ithread, idCore
    shared_ptr<Multicore> multicore;
    int lastCoreAssigned; //para asignar los cores mediante round robin

  public:
    OperatorSystem(shared_ptr<Multicore> _multicore);
    ~OperatorSystem();
    void addProgramDeployment(shared_ptr<ProgramDeployment> _pd,
                        shared_ptr<OperatorSystem> _os);
    void addExecutionRequestToCore(string keyAssignation,
        shared_ptr<ExecutionRequest> exeReq);
    map<string,shared_ptr<ProgramDeployment>> getPgmDeployments(void);
    string toString();

};
#endif
