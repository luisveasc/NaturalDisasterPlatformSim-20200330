#ifndef CLIENT_H
#define CLIENT_H

#include "glob.h"
#include "message.h"
#include "network.h"

class Client: public process{

	public:
		string pathTrace;
		std::ifstream traceFile;
		handle<Network> network;

	protected:
    void inner_body( void );

  public:
    Client(const string & _name, const string & _pathTrace,
			handle<Network> _network);
    ~Client();
		void generateRequestByTrace(void);
		string toString(void);

};
#endif
