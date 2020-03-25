#ifndef _GLOB_H_
#define _GLOB_H_

#include <list>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <random>
#include <exception>
#include <cstdlib>
#include <chrono>
#include <unistd.h>
#include <thread>
#include <ctime>
#include <math.h>
#include <fstream>
#include <sstream>
#include <inttypes.h>
#include <limits>
#include <utility>
#include <cppsim.hh>
#include <cstdio>

#include <json.hpp>
using json=nlohmann::json;
using namespace std;


class UtilString{

		public :

		static std::vector<std::string> split(const std::string &s, char delim) {
		  std::stringstream ss(s);
		  std::string item;
		  std::vector<std::string> elems;
		  while (std::getline(ss, item, delim)) {
		    elems.push_back(item);
		  }
		  return elems;
		}
};


#endif
