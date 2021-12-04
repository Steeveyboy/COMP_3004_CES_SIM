#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>

class record {
  public:
    record(int fq, int pwr, int dur, int newId, std::string dt){
      freq = fq;
      powerLevel = pwr;
      duration = dur;
      id = newId;
      date = dt;
      //std::cout<<id<<std::endl;
    };
    int freq;
    int powerLevel;
    int duration;
    int id;
    std::string date;
};

#endif
