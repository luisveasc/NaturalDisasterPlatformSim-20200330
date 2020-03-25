#ifndef NETWORK_H
#define NETWORK_H

#include "glob.h"
#include "message.h"
#include "monitor.h"

class ProgramDeployment;
class Network : public process{

  public:
    double bpmsVelocity;
    double velocity;
    string unitTrasferRate;
    list<shared_ptr<Message>> queueMessages;
    map<string,shared_ptr<ProgramDeployment>> mapPgmDeployments;

  protected:
    void inner_body( void );

  public:
    Network(const string & name, const double & v, const string & urt);
    ~Network();
    void bpmsVelocityCalculate(const double & v, const string & urt);
    void processMessage(void);
    void addMessage(shared_ptr<Message> msg);
    void addProgramDeployments(map<string,shared_ptr<ProgramDeployment>> mappd, handle<Network> network);
    string toString();
};

#endif
