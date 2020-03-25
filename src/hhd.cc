#include "../include/hhd.h"

HHD::HHD(void){
  this->sizebytes 	= 0;
  this->occupiedbytes	= 0;
}

HHD::HHD(const HHD & hhd){
  this->sizebytes=hhd.sizebytes;
  this->occupiedbytes=hhd.occupiedbytes;
}

HHD& HHD::operator=(const HHD & hhd){
  this->sizebytes=hhd.sizebytes;
  this->occupiedbytes=hhd.occupiedbytes;
  return (*this);
}

HHD::~HHD(void){
}

HHD::HHD( const uint64_t & _t, const uint64_t & _u  ){
  this->sizebytes 	= _t;
  this->occupiedbytes	= _u;
}

void HHD::set( const uint64_t & _t, const uint64_t & _u  ){
  this->sizebytes 		= _t;
  this->occupiedbytes	= _u;
}

uint64_t HHD::getSizebytes(){ return sizebytes; }

uint64_t HHD::getOccupiedbytes(){ return occupiedbytes; }

uint64_t HHD::getAvailable(){ return sizebytes-occupiedbytes; }

string HHD::toString(){
  char txt[200];
  sprintf(txt,"{sizebytes:%"PRIu64",occupiedbytes:%"PRIu64"}",sizebytes,occupiedbytes);
  return txt;
}


uint64_t HHD::incrOccupiedbytes( const uint64_t & p){
  uint64_t resp=0;

  if(this->occupiedbytes + p <= this->sizebytes){
    this->occupiedbytes = this->occupiedbytes + p;
  } else {
    resp = 	this->sizebytes - (this->occupiedbytes + p);
    this->occupiedbytes = this->sizebytes;
  }
  return resp;
}

uint64_t HHD::decrOccupiedbytes( const uint64_t & p){
  uint64_t resp=0;
  if(this->occupiedbytes - p>=0){
    this->occupiedbytes = this->occupiedbytes - p;
  } else {
    resp = 	p - this->occupiedbytes;
    this->occupiedbytes = 0;
  }
  return resp;
}
