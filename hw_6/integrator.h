#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <iostream>
#include "elma/elma.h"

using namespace std;
using namespace elma;

class Integrator : public Process {
public:
    Integrator(std::string name) : Process(name), integral(0), count(0) {}

    void init() {}
    void start() {}
    void update() {
        for (double e : channel("link").latest()) {
            integral += delta() * e; // Calculates the Integral
            count++;
        }
    }
    void stop() {}

    double value() const { return integral; } // Returns the value of integral
    double delta() const { return 0.01; } // Returns the Delta value

private:
    double integral;
    int count;
};

// Process named Source that outputs a constant value 
class Source : public Process {
public:
    Source(std::string name, double value) : Process(name), _value(value) {}

    void init() {}
    void start() {}
    void update() {
        channel("link").send(_value); // Send the constant value to channel
    }
    void stop() {}

    double value() const { return _value; } // Returns the constant value

private:
    double _value;
};

#endif