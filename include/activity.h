#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "glob.h"
#include "factorywork.h"

class Activity{

	public:
    uint64_t id;
	uint64_t idpgm;
    string name;
		vector<shared_ptr<Work>> works;

  public:
		Activity(const uint64_t & _id,const uint64_t & _idpgm,  const string & _name,
			vector<shared_ptr<Work>> works);
    Activity(const uint64_t & _idpgm,const json & activity);
    ~Activity();
		string toString(void);

};
#endif
