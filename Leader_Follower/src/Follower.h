#ifndef __FOLLOWER_AGENT__H
#define __FOLLOWER_AGENT__H 

// Include all required libraries
#include "enviro.h"

using namespace enviro;

// Class created to define methods for controlling Follower Robot. It inherits methods from Process and AgentInterface class.
class FollowerController : public Process, public AgentInterface {

    public:
    FollowerController() : Process(), AgentInterface() {}

    // Method to initialise variables for the Follower Robot
    void init() {
        goal_x = 0;
        goal_y = 0;
        count = 0;
        count_max_bool = false;
        count_max = 0;
        // Get the current position of the Leader Robot and keeps on updating new goal to the Follower Robot
       watch("goal_change", [this](Event e) { 
            goal_x = e.value()["x"];  
            goal_y = e.value()["y"];
        });
    }
    void start() {}
    // Method for the Follower Robot to chase the Leader Robot
    void update() {
        //Current position of Leader robot is assigned to the array in the latest iteration of count.
        position_array_x[count] = goal_x;
        position_array_y[count] = goal_y;
        //For each Follower robot, the maximum count of iterations needed is assigned.
        count_max = (id()*10)+10;
        // When the maximum count of iterations is hit for the first time, the variable is assigned True.
        if(count==count_max-1){
            count_max_bool = true;
        }
        // When the variable is True
        if(count_max_bool==true){
            // Move towards the Leader Robot position which was count_max number of iteration before. speed of 0.15 is assigned.
            omni_move_toward(position_array_x[(count+1)%count_max], position_array_y[(count+1)%count_max],0.15);
        }
        // Increment the count variable for each iteration
        count++;
        // Make sure count does not exceed count_max
        count = count%count_max;
    }
    void stop() {}

    // Variables to store current location of Leader robot
    double goal_x, goal_y;
    // Variable to store count of iterations
    int count;
    // Variable to store whether the maximum count of iterations is hit for the first time or not
    bool count_max_bool;
    // Variables to store previous and current location of Leader robot
    int position_array_x[200], position_array_y[200];
    // Variables to store maximum of previous locations of Leader Robot for each Follower robot to be stored.
    int count_max;
};

// Class created to add a process for Follower Robot.
class Follower : public Agent {
    public:
    Follower(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    FollowerController c;
};

DECLARE_INTERFACE(Follower)

#endif