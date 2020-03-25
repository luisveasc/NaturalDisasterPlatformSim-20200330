#ifndef PLATAFORMSIM_H
#define PLATAFORMSIM_H

#include "glob.h"
#include "multicore.h"
#include "cluster.h"
#include "program.h"
#include "programdeployment.h"
#include "operatorsystem.h"
#include "network.h"
#include "client.h"
#include "monitor.h"

class PlatformSim : public process
{

	private:
		double simlen;
		json settings;
		vector <shared_ptr<Multicore>> multicores;
		vector <shared_ptr<Cluster>> clusters;
		handle<Network> network;
		handle<Client> client;


	protected:
		void inner_body( void );

	public:
    PlatformSim(const string & _name,
			const double & _simlen,
			const json & _settings);
    ~PlatformSim();

		void createMulticores(void);
		void createClusters(void);
		void createNetwork(void);
		void createClient(void);
		void setProgramsDeployments(void);
		void activateMulticores(void);
		void activateNetwork(void);
		void activateClient(void);
		void cancelMulticores(void);
		void cancelNetwork(void);
		void cancelClient(void);
};

#endif
