#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include <iostream>
#include <elma/elma.h>

using namespace std;
using namespace elma;

class Manager {

    public:

    Manager() {}

    Manager& schedule(Process& process, high_resolution_clock::duration period);

    Manager& all(std::function<void(Process&)> f);

    Manager& init();
    Manager& start();
    Manager& stop();
    Manager& run(high_resolution_clock::duration);
    Manager& update();

    inline high_resolution_clock::time_point start_time() { return _start_time; }
    inline high_resolution_clock::duration elapsed() { return _elapsed; }

    private:

    vector<Process *> _processes;
    high_resolution_clock::time_point _start_time;
    high_resolution_clock::duration _elapsed;

};

class RandomProcess : public Process {
  public:
    RandomProcess(string name) : Process(name) {}

    void init() {}
    void start() {}
    void update() {
        double value = ((double)rand() / RAND_MAX); // generates a random double between 0 and 1
        channel("link").send(value); // sends the value to the channel
    }
    void stop() {}
};

#endif