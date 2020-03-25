#ifndef PROGRAM_H
#define PROGRAM_H

#include "glob.h"
#include "activity.h"

class Program{

  public:
    string name;
    uint64_t id;
    vector<string> config_conn;
    vector<shared_ptr<Activity>> activities;

  public:
    Program(const string & _name,
      const uint64_t & _id,
      vector<string> _config_conn,
      vector<shared_ptr<Activity>> _activities);

    Program(const json & program);

    ~Program();

    string toString();

};
#endif
