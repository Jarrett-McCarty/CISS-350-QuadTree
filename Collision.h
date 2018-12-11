// File   : Collision.h
// Author : Jarrett McCarty

// File Description:

//***************************************************************************

// This file contains the class declaration for the Collision detection used in this project
// All methods and variables are listed below.

/*
 Public Methods Include:
                    -> Constructor
                    -> Destructor
                    -> collision_detection x2 (One for optimized collision other used as project specification)
                    -> calc_vel TODO
                    -> distance_sqaured
                    -> collision
                    -> get_collision_count

 Variables:
                    -> count
 */

//***************************************************************************

#ifndef COLLISION_H
#define COLLISION_H

/* Includes */
#include "General.h"
#include "Particle.h"

class Collision
{
public:
    Collision();
    virtual ~Collision(); 
    void collision_detection(Particle * particle, CollisionList colliders);
    void collision_detection(Particle * particle, Particle * particle1);
    void calc_vel(Circle & a, Circle & b);
    double distance_squared(double, double, double, double);
    bool collision(Circle & a, Circle & b);
    int get_collision_count();
private:
    int count = 0;
};

#endif 
