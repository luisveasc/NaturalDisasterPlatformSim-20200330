#ifndef RAM_H
#define RAM_H

#include "glob.h"

class RAM
{
	public:
		uint64_t sizebytes;
		uint64_t occupiedbytes;

	public:
    RAM();
    RAM(const RAM & ram);
    RAM(const uint64_t & _t, const uint64_t & _u);
    RAM& operator=(const RAM & ram);
    ~RAM(void);

    void set(const uint64_t & _t, const uint64_t & _u  );
		uint64_t getSizebytes();
		uint64_t getOccupiedbytes();
		uint64_t incrOccupiedbytes( const uint64_t & p);
		uint64_t decrOccupiedbytes( const uint64_t & p);
		uint64_t getAvailable();
		string toString();

};

#endif
