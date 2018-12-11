// File   : Particle.h
// Author : Jarrett McCarty

// File Description:
//******************************************************************************

// This file contains the class declaration for the Particle class used as a
// wrapper for the SDL Circle object.
// All methods, variables, structs are listed below.

/*
 Public Methods Include:
                    -> Constructor
                    -> Destructor
                    -> get_circle 
                    -> get_state
                    -> get_speed
                    -> set_circle
                    -> set_speed
                    -> change_color
                    -> update
                    -> draw

 Variables Include:
                    -> circle_

 Struct:
                    -> **particles
                    -> count
                    -> size
 */

//*****************************************************************************

#ifndef PARTICLE_H
#define PARTICLE_H

#include "General.h"

class Particle
{
public:
    Particle(Circle circle);
    virtual ~Particle();
    
    Circle get_circle();

    int & get_state();
    
    Point get_speed();
    
    void set_circle(Circle new_circle);
    void set_speed(Point new_speed);

    
    void change_color();
    
    void update();
    void draw(Surface & surface);

private:
    Circle circle_;
};


/* Helper struct for particle collision checking within the quadtree framework*/
struct CollisionList
{
    Particle ** particles;
    int count;
    int size;
};



#endif  
