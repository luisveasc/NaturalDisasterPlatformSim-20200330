#include "../include/platformsim.h"

extern shared_ptr<Monitor>MONITOR;

PlatformSim::PlatformSim(const string & _name,
        const double & _simlen,
        const json & _settings) : process(_name){

    this->simlen = _simlen;
    this->settings	=_settings;

    //MONITOR =  make_shared<Monitor>(this->settings["monitor_window_size_ms"], this->time());

}

PlatformSim::~PlatformSim(){
  this->multicores.clear();
  this->clusters.clear();
  std::cout<<"destroy sptr"<<std::endl;
}

void PlatformSim::inner_body( void ){

  //MONITOR->printIniSimulation(this->time());

  createMulticores();
  createClusters();
  setProgramsDeployments();
  createNetwork();
  createClient();

  //ACTIVATE
  activateNetwork();
  activateMulticores();
  activateClient();


  hold(this->simlen);
  //CANCEL
  cancelClient();
  cancelMulticores();
  cancelNetwork();

  //MONITOR->printEndSimulation(this->time());
  MONITOR->close();

  end_simulation();
}

void PlatformSim::createMulticores(void){
  int n = settings["multicores"].size();
  json jmulticores = json::array();
  for(int i = 0 ; i<n ; i++){
    this->multicores.push_back( make_shared<Multicore>(settings["multicores"].at(i) ) );
    this->multicores[i]->createSO(this->multicores[i]);
    jmulticores.push_back(this->multicores[i]->toJson());
  }
  MONITOR->printInfrastructureMulticores(jmulticores);
}

void PlatformSim::createClusters(void){
  int n = settings["clusters"].size();
  for(int i = 0 ; i<n ; i++){
    this->clusters.push_back( make_shared<Cluster>(settings["clusters"].at(i), this->multicores) );
  }
}

void PlatformSim::setProgramsDeployments(void){
  int n = settings["programs_deployments"].size();
  for(int i = 0 ; i<n ; i++){
    int ip = settings["programs_deployments"].at(i)["ip"];
    int program_id = settings["programs_deployments"].at(i)["program_id"];
    json pgmDeployment = settings["programs_deployments"].at(i);

    shared_ptr<Program> pgm = make_shared<Program>(settings["programs"].at(program_id));
    shared_ptr<ProgramDeployment> pd = make_shared<ProgramDeployment>(pgmDeployment,pgm);
    this->multicores[ip]->addProgramDeploymentOS(pd);
  }

}

void PlatformSim::createNetwork(void){
  this->network = new Network(settings["network"]["name"],settings["network"]["velocity"],
                              settings["network"]["unit_trasfer_rate"]);
  int n = this->multicores.size();
  for(int i=0;i<n;i++){
    this->network->addProgramDeployments(this->multicores[i]->getProgramDeploymentsOS(),this->network);
  }
}

void PlatformSim::createClient(void){
  this->client = new Client("CLIENT_TRACE",settings["client"]["trace_path"], this->network);
}


void PlatformSim::activateMulticores(void){
  int n = settings["multicores"].size();
  for(int i = 0 ; i<n ; i++){
    this->multicores[i]->activate();
  }
}

void PlatformSim::cancelMulticores(void){
  int n = settings["multicores"].size();
  for(int i = 0 ; i<n ; i++){
    this->multicores[i]->cancel();
  }
}

void PlatformSim::activateNetwork(void){
  this->network->activate();
}

void PlatformSim::activateClient(void){
  this->client->activate();
}


void PlatformSim::cancelNetwork(void){
  this->network->cancel();
}


void PlatformSim::cancelClient(void){
  this->client->cancel();
}
