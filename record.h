#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>

class record {
  public:
    record(int fq, int pwr, int dur, int id, std::string dt){
      freq = fq;
      powerLevel = pwr;
      duration = dur;
      id = id;
      date = dt;
    };
    int freq;
    int powerLevel;
    int duration;
    int id;
    std::string date;
};

#endif
