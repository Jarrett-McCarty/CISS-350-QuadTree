// File   : FPS.cpp
// Author : Jarrett McCarty

// File Description:
//****************************************************************************

// File contains the function bodies for the file "FPS.h"

//****************************************************************************

#include "FPS.h"


FPS::FPS()
{}

FPS::~FPS()
{}

void FPS::start()
{
    start_time = getTicks();
    started_ = true;
    paused_ = false;

}

void FPS::stop()
{
    if(started_ == true)
    {
        start_time = 0;
        started_ = false;
        paused_ = false;
    }

}

void FPS::pause()
{
    if((started_ == true) && (paused_ == false))
    {
            paused_ = true;

            paused_time = getTicks() - start_time;
    }
}

void FPS::unpause()
{
    if((started_ == true) && (paused_ == true))
    {
        paused_ = false;

        start_time = getTicks() - paused_time;

        paused_time = 0;
    }
}

int FPS::get_ticks()
{
    if(started_ == true)
    {
        if(paused_ == true)
        {
            return paused_time;
        }
        else
        {
            return getTicks() - start_time;
        }
    }

    return 0;
}

bool FPS::paused()
{
    return paused_;
}

bool FPS::started()
{
    return started_;
}
