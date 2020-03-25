#ifndef FACTORYWORK_H
#define FACTORYWORK_H

#include "glob.h"
#include "work.h"
#include "workprocess.h"
#include "workrequesttoapi.h"


class FactoryWork
{

	public:
    static shared_ptr<Work> CreateWork(const json & jWork, const uint64_t & _idpgm, const uint64_t & _idActivity){

      shared_ptr<Work> work;
      string type = jWork["type"];
      json data = jWork["data"];
      //std::cout<<"------>"<<jWork["desc"]<<std::endl;
      string descrip = (jWork["desc"].is_string()==true) ? jWork["desc"] : "";


      if(type.compare("WorkProcess")==0){

        work = std::make_shared<WorkProcess>(data, _idpgm, _idActivity ,descrip);

      } else if(type.compare("WorkRequestToApi")==0){

        work = std::make_shared<WorkRequestToApi>(data, _idpgm, _idActivity, descrip);

      }

      return work;
    }

};

#endif
