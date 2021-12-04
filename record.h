#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>

class record {
  public:
    record(int fq, int pwr, int dur, std::string wave, int newId, std::string dt){
      freq = fq;
      powerLevel = pwr;
      duration = dur;
      id = newId;
      date = dt;
      waveform = wave;
      //std::cout<<id<<std::endl;
    };
    int freq;
    int powerLevel;
    int duration;
    int id;
    std::string waveform;
    std::string date;
};

#endif
