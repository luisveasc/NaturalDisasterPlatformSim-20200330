#ifndef HHD_H
#define HHD_H

#include "glob.h"

class HHD
{
  public:
		uint64_t sizebytes;
		uint64_t occupiedbytes;

	public:
		HHD(void);
		HHD(const HHD & hhd);
		HHD( const uint64_t & _t, const uint64_t & _u  );
    ~HHD(void);

		HHD& operator=(const HHD & hhd);
		void set( const uint64_t & _t, const uint64_t & _u);
		uint64_t getSizebytes();
		uint64_t getOccupiedbytes();
		uint64_t incrOccupiedbytes( const uint64_t & p);
		uint64_t decrOccupiedbytes( const uint64_t & p);
		uint64_t getAvailable();
		string toString();

};

#endif
