#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>

class record {
  public:
    record(std::string fq, std::string cur, int dur, std::string wave, int newId, std::string dt){
      freq = fq;
      current = cur;
      duration = dur;
      id = newId;
      date = dt;
      waveform = wave;
      //std::cout<<id<<std::endl;
    };
    std::string freq;
    std::string current;
    int duration;
    int id;
    std::string waveform;
    std::string date;
};

#endif
