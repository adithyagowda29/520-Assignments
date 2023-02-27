#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include <elma/elma.h>
#include "random_process.h"

using namespace std;
using namespace elma;

class Filter : public Process {
  private:
    vector<double> buffer; // variable for buffer to store the last 10 values
    double running_avg; // variable to store running average of the last 10 values
    int count; // variable to store count of values received so far

  public:
    Filter(string name) : Process(name), buffer(10, 0), running_avg(0), count(0) {}

    void init() {}
    void start() {}
    void update() {
        double value = channel("link").latest(); // reads the latest value from the channel
        if(value==0) return; 
        buffer[9 - (count % 10)] = value; // adds the value to the buffer
        count++;
        int n = min(count, 10); // number of values to use in the running average calculation
        running_avg = accumulate(buffer.end() - n, buffer.end(), 0.0) / n; // calculates the running average
    }
    void stop() {}

    double value() {
        return running_avg; // returns the running average
    }
};

#endif