
#include "../include/platformsim.h"

/*#########################################
main
##########################################*/

shared_ptr<Monitor>MONITOR;

int main(int argc,char** argv){

    int c;
	extern char *optarg;
	std::ifstream ifs;
   	json settings;
    string idSimulation;
   	string ouputFilePath;
   	//json instructionstimes;
	double sim_time = 999999999999;//99999999e10000;


	while((c=getopt(argc,argv, "s:i:o:"))!=-1) {
        switch (c) {
            case 's': {
                ifs.open(optarg, std::ifstream::in);
                ifs >> settings;
                //std::cout << "## SETTINGG ## \n" << settings.dump() << std::endl;
                ifs.close();
                break;
            }
            case 'i': {
                ifs.open(optarg, std::ifstream::in);
                //std::cout<<"2->"<<optarg<<std::endl;
                idSimulation = optarg;
                std::cout<<"1->"<<idSimulation<<std::endl;
                ifs.close();
                break;
            }
            case 'o': {
                ifs.open(optarg, std::ifstream::in);
                //std::cout<<"2->"<<optarg<<std::endl;
                ouputFilePath = optarg;
                std::cout<<"2->"<<ouputFilePath<<std::endl;
                ifs.close();
                break;
            }

        }
    }

    if(settings.empty()){
        std::cerr << "Mandatory parameter -s <basic settings> needed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(idSimulation.empty()){
  	    std::cerr << "Mandatory parameter -i <id simulation> needed" << std::endl;
        exit(EXIT_FAILURE);
  	}
    if(ouputFilePath.empty()){
        std::cerr << "Mandatory parameter -o <output files path> needed" << std::endl;
        exit(EXIT_FAILURE);
    }



    MONITOR = make_shared<Monitor>(idSimulation,ouputFilePath);
    simulation *sim = simulation::instance( );sim->begin_simulation( new sqsDll( ) );
    handle<PlatformSim> system( new PlatformSim("PRINCIPAL_SYMTEM_SIM", sim_time, settings) );
    system->activate( );
    sim->run( );
    sim->end_simulation( );

    return 0;
}
