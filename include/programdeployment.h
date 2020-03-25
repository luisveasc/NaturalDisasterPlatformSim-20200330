#ifndef PROGRAMDEPLOYMENT_H
#define PROGRAMDEPLOYMENT_H

#include "glob.h"
#include "program.h"
#include "executionrequest.h"
#include "network.h"

class OperatorSystem;
class ProgramDeployment{

	public:
		string id; //ip_port
		uint64_t ip;
		uint64_t port;
		uint64_t nbrThreads;
		vector<string>idThreads;
		shared_ptr<Program> program;
		map<string,string> configConn;
		string status;//online offline
		int lastUsedThread;
		shared_ptr<OperatorSystem> os;

	public:
		ProgramDeployment(const json & pd, shared_ptr<Program> _program);
		~ProgramDeployment();
		string toString(void);
		void setNetwork(handle<Network> _network);
		void addRequest(shared_ptr<Message> Message);

	private:
		void setWorksConfigConn( void );

};
#endif
