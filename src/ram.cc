#include "../include/ram.h"

RAM::RAM(void){
  this->sizebytes 	= 0;
  this->occupiedbytes	= 0;
}

RAM::RAM(const RAM & ram){
  this->sizebytes=ram.sizebytes;
  this->occupiedbytes=ram.occupiedbytes;
}

RAM::RAM( const uint64_t & _t, const uint64_t & _u ){
  this->sizebytes 		= _t;
  this->occupiedbytes	= _u;
}


RAM::~RAM(void){
}

RAM& RAM::operator=(const RAM & ram){
  this->sizebytes=ram.sizebytes;
  this->occupiedbytes=ram.occupiedbytes;
  return (*this);
}

void RAM::set( const uint64_t & _t, const uint64_t & _u  ){
  this->sizebytes 		= _t;
  this->occupiedbytes	= _u;
}

uint64_t RAM::getSizebytes(){ return this->sizebytes; }
uint64_t RAM::getOccupiedbytes(){ return this->occupiedbytes; }

uint64_t RAM::incrOccupiedbytes( const uint64_t & p){
  uint64_t resp=0;

  if(this->occupiedbytes + p <= this->sizebytes){
    this->occupiedbytes = this->occupiedbytes + p;
  } else {
    resp = 	this->sizebytes - (this->occupiedbytes + p);
    this->occupiedbytes = this->sizebytes;
  }
  return resp;
}

uint64_t RAM::decrOccupiedbytes( const uint64_t & p){
  uint64_t resp=0;
  if(this->occupiedbytes - p>=0){
    this->occupiedbytes = this->occupiedbytes - p;
  } else {
    resp = 	p - this->occupiedbytes;
    this->occupiedbytes = 0;
  }
  return resp;
}

uint64_t RAM::getAvailable(){
  return this->sizebytes - this->occupiedbytes;
}

string RAM::toString(){
  char txt[200];
  sprintf(txt,"{sizebytes:%"PRIu64",occupiedbytes:%"PRIu64"}",sizebytes,occupiedbytes);
  return txt;
}
