// File   : FPS.h
// Author : Jarrett McCarty

// File Description:
//****************************************************************************

// This file contains headers for the file "FPS.cpp"
// All methods and variables are listed below.

/*
 Public Methods Include:
                    -> Constructor
                    -> Destructor
                    -> start
                    -> stop
                    -> pause
                    -> unpaused
                    -> get_ticks
                    -> paused
                    -> started
 Variables:
                    -> started_
                    -> paused_
                    -> start_time
                    -> paused_time
 */

//****************************************************************************

#ifndef FPS_H
#define FPS_H

#include "General.h"

class FPS
{
public:
    FPS();
    virtual ~FPS();
    void start();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool paused();
    bool started();
private:
    bool started_;
    bool paused_;
    int start_time;
    int paused_time;
};

#endif 

