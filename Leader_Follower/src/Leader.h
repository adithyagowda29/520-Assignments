#ifndef __LEADER_AGENT__H
#define __LEADER_AGENT__H

// Include all required libraries
#include <string>
#include <math.h>
#include "enviro.h"

namespace
{

    using namespace enviro;

    // Class created to define methods for moving forward the Leader Robot on one of the sides of the rectangular loop path.
    class MovingForward : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {}
        void during()
        {
            // Move the Leader Robot towards the given point
            move_toward(300,-100);
            // When Leader Robot is near the point, emit the signal to go to the next transition
            if (sensor_value(0) < 50)
            {
                emit(Event(tick_name));    
            }
            // Creates event goal_change to send Leader Robot position to the Follower Robot
            emit(Event("goal_change", { 
                { "x", position().x}, 
                { "y", position().y },
                
            }));
        }
        void exit(const Event &e) {}
        // Method to set the name of the Tick
        void set_tick_name(std::string s) { tick_name = s; }
        // Variable to store the name of the Tick
        std::string tick_name;
    };

    // Class created to define methods for moving forward the Leader Robot on one of the sides of the rectangular loop path.
    class MovingForward2 : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {}
        void during()
        {
            // Move the Leader Robot towards the given point
            move_toward(300,100);
            
            // When Leader Robot is near the point, emit the signal to go to the next transition
            if (sensor_value(0) < 50)
            {
                emit(Event(tick_name));
                
            }
            // Creates event goal_change to send Leader Robot position to the Follower Robot
            emit(Event("goal_change", { 
                { "x", position().x}, 
                { "y", position().y },
                
            }));
            
        }
        void exit(const Event &e) {}
        // Method to set the name of the Tick
        void set_tick_name(std::string s) { tick_name = s; }
        // Variable to store the name of the Tick
        std::string tick_name;
    };

    class MovingForward3 : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {}
        void during()
        {
            // Move the Leader Robot towards the given point
            move_toward(-300,100);
            
            // When Leader Robot is near the point, emit the signal to go to the next transition
            if (sensor_value(0) < 50)
            {
                emit(Event(tick_name));
                
            }
            // Creates event goal_change to send Leader Robot position to the Follower Robot
            emit(Event("goal_change", { 
                { "x", position().x}, 
                { "y", position().y },
                
            }));
            
        }
        void exit(const Event &e) {}
        // Method to set the name of the Tick
        void set_tick_name(std::string s) { tick_name = s; }
        // Variable to store the name of the Tick
        std::string tick_name;
    };

    class MovingForward4 : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {}
        void during()
        {
            // Move the Leader Robot towards the given point
            move_toward(-300,-100);
            
            // When Leader Robot is near the point, emit the signal to go to the next transition
            if (sensor_value(0) < 50)
            {
                emit(Event(tick_name));
                
            }
            // Creates event goal_change to send Leader Robot position to the Follower Robot
            emit(Event("goal_change", { 
                { "x", position().x}, 
                { "y", position().y },
                
            }));
            
        }
        void exit(const Event &e) {}
        // Method to set the name of the Tick
        void set_tick_name(std::string s) { tick_name = s; }
        // Variable to store the name of the Tick
        std::string tick_name;
    };

    class Rotating : public State, public AgentInterface
    {
    public:
        // Set the angular velocity for the Leader Robot
        void entry(const Event &e) { rate = 4; }
        void during()
        {
            // Rotate the Leader Robot with the given velocity rate
            track_velocity(0, rate);
            // When Leader Robot is has rotated enough for the next point, emit the signal to go to the next transition
            if (sensor_value(0) >= 70)
            {
                emit(Event(tick_name));
                
            }
        }
        void exit(const Event &e) {}
        // Variable to store the angular velocity for the Leader Robot
        double rate;
        // Method to set the name of the Tick
        void set_tick_name(std::string s) { tick_name = s; }
        // Variable to store the name of the Tick
        std::string tick_name;
    };

    class Rotating2 : public State, public AgentInterface
    {
    public:
        // Set the angular velocity for the Leader Robot
        void entry(const Event &e) { rate = 4; }
        void during()
        {
            // Rotate the Leader Robot with the given velocity rate
            track_velocity(0, rate);
            
            if (sensor_value(0) >= 70)
            {
                emit(Event(tick_name));
                
            }
        }
        void exit(const Event &e) {}
        // Variable to store the angular velocity for the Leader Robot
        double rate;
        // Method to set the name of the Tick
        void set_tick_name(std::string s) { tick_name = s; }
        // Variable to store the name of the Tick
        std::string tick_name;
    };

    class Rotating3 : public State, public AgentInterface
    {
    public:
        // Set the angular velocity for the Leader Robot
        void entry(const Event &e) { rate = 4; }
        void during()
        {
            // Rotate the Leader Robot with the given velocity rate
            track_velocity(0, rate);
            
            if (sensor_value(0) >= 70)
            {
                emit(Event(tick_name));
                
            }
        }
        void exit(const Event &e) {}
        // Variable to store the angular velocity for the Leader Robot
        double rate;
        // Method to set the name of the Tick
        void set_tick_name(std::string s) { tick_name = s; }
        // Variable to store the name of the Tick
        std::string tick_name;
    };

    class Rotating4 : public State, public AgentInterface
    {
    public:
        // Set the angular velocity for the Leader Robot
        void entry(const Event &e) { rate = 4; }
        void during()
        {
            // Rotate the Leader Robot with the given velocity rate
            track_velocity(0, rate);
            
            if (sensor_value(0) >= 70)
            {
                emit(Event(tick_name));
                
            }
        }
        void exit(const Event &e) {}
        // Variable to store the angular velocity for the Leader Robot
        double rate;
        // Method to set the name of the Tick
        void set_tick_name(std::string s) { tick_name = s; }
        // Variable to store the name of the Tick
        std::string tick_name;
    };

    // Class created to define methods for controlling Leader Robot. It inherits methods from StateMachine and AgentInterface class.
    class LeaderController : public StateMachine, public AgentInterface
    {

    public:
        LeaderController() : StateMachine()
        {
            // Set initial state for the State Machine
            set_initial(moving_forward);
            tick_name = "tick_" + std::to_string(rand() % 1000); // use an agent specific generated
                                                                 // event name in case there are
                                                                 // multiple instances of this class
            // Add transitions for the State Machine
            add_transition(tick_name, moving_forward, rotating);
            add_transition(tick_name, rotating, moving_forward2);
            add_transition(tick_name, moving_forward2, rotating2);
            add_transition(tick_name, rotating2, moving_forward3);
            add_transition(tick_name, moving_forward3, rotating3);
            add_transition(tick_name, rotating3, moving_forward4);
            add_transition(tick_name, moving_forward4, rotating4);
            add_transition(tick_name, rotating4, moving_forward);
            moving_forward.set_tick_name(tick_name);
            moving_forward2.set_tick_name(tick_name);
            moving_forward3.set_tick_name(tick_name);
            moving_forward4.set_tick_name(tick_name);
            rotating.set_tick_name(tick_name);
            rotating2.set_tick_name(tick_name);
            rotating3.set_tick_name(tick_name);
            rotating4.set_tick_name(tick_name);
        }

        void update()
        {
           if (rand() % 100 <= 5)
           {
               emit(Event("tick"));
           }
           StateMachine::update();
        }

        // Defining an object for each class
        MovingForward moving_forward;
        MovingForward2 moving_forward2;
        MovingForward3 moving_forward3;
        MovingForward4 moving_forward4;
        Rotating rotating;
        Rotating rotating2;
        Rotating rotating3;
        Rotating rotating4;
        // Variable to store the name of the Tick
        std::string tick_name;
    };

    // Class created to add a process for Leader Robot.
    class Leader : public Agent
    {

    public:
        Leader(json spec, World &world) : Agent(spec, world)
        {
            add_process(wc);
        }

        LeaderController wc;
    };

    DECLARE_INTERFACE(Leader);

}

#endif