#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <chrono>

class Stopwatch {
private:
    std::chrono::steady_clock::time_point start_time_; // Variable to store Start time
    std::chrono::steady_clock::time_point end_time_;  // Variable to store End time
    std::chrono::duration<double> elapsed_time_;  // Variable to store Elapsed time

public:
    Stopwatch() : elapsed_time_(0) {}

    void start() {
        start_time_ = std::chrono::steady_clock::now(); // Sets the Start time
    }

    void stop() {
        end_time_ = std::chrono::steady_clock::now(); // Sets the End time
        elapsed_time_ += std::chrono::duration_cast<std::chrono::duration<double>>(end_time_ - start_time_); // Calculates the Elapsed time
    }

    void reset() {
        elapsed_time_ = std::chrono::duration<double>(0); // Sets the Elapsed time to 0
    }

    // Returns the Elapsed time in minutes
    double get_minutes() {
        return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time_).count()/(1000.0*1000.0*1000.0*60.0);
    }

    // Returns the Elapsed time in seconds
    double get_seconds() {
        return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time_).count()/(1000.0*1000.0*1000.0);
    }

    // Returns the Elapsed time in milliseconds
    double get_milliseconds() {
        return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time_).count()/(1000.0*1000.0);
    }

    // Returns the Elapsed time in nanoseconds
    double get_nanoseconds() {
        return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time_).count();
    }
};

#endif