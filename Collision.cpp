// File   : Collision.cpp
// Author : Jarrett McCarty

// File Description:
//*****************************************************************************

// This file contains all function bodies that are included from "Collision.h"

//*****************************************************************************

/* Including the header file */
#include "Collision.h"

/* Constructor */
Collision::Collision()
{}

/* Destructor */
Collision::~Collision()
{}

/* Function to change the velocity of the circles upon collision*/
/* TODO: NEEDS MORE TESTING + ELASTIC COLLISIONS NEED TO BE IMPLEMENTED */
void Collision::calc_vel(Circle & a, Circle & b)
{
    
    double deltaX = abs(a.x - b.x);
    double deltaY = abs(a.y - b.y);
    double distance = deltaX * deltaX + deltaY * deltaY;
    
    if (distance < (a.r + b.r) * (a.r + b.r))
    {
        
        double newxSpeed1 = (a.speed.x * (4 - 7) + (2 * 7 * b.speed.x)) / 11;
        
        double newxSpeed2 = (b.speed.x * (7 - 4) + (2 * 4 * a.speed.x)) / 11;
        
        double newySpeed1 = (a.speed.y * (4 - 7) + (2 * 7 * b.speed.y)) / 11;
        
        double newySpeed2 = (b.speed.y * (7 - 4) + (2 * 4 * a.speed.y)) / 11;
        
        b.speed.x = (newxSpeed2);
        b.speed.y = (newySpeed2);
        a.speed.x = (newxSpeed1);
        a.speed.y = (newySpeed1);
        
    }
}

/* Collision Detection that works using the "CollisionList" struct
   for improved performance*/
void Collision::collision_detection(Particle * particle, CollisionList colliders)
{
    for(int i = 0; i < colliders.count; i++)
    {
        Particle * particle_2 = colliders.particles[i];
        if(particle != particle_2)
        {
            Circle temp = particle->get_circle();
            Circle temp2 = particle_2->get_circle();
            if (collision(temp, temp2))
            {
                ++count;
                if (temp.state == temp2.state)
                {
                    particle->change_color();
                    particle_2->change_color();
                }
                calc_vel(temp, temp2);
            }
        }
    }
}

/* Collision detection that only detects two separate particles
 USED TO SLOW DOWN PROGRAM/PART OF ASSIGNMENT */
void Collision::collision_detection(Particle * particle, Particle * particle1)
{
    Circle temp = particle->get_circle();
    Circle temp2 = particle1->get_circle();
    if (particle != particle1)
    {
        if (collision(temp, temp2))
        {
            ++count;
            if (temp.state == temp2.state)
            {
                particle->change_color();
                particle1->change_color();
            }
            calc_vel(temp, temp2);
        }
    }
}

/* Boolean function used to measure the distance between cirlces */
bool Collision::collision(Circle & a, Circle & b)
{
    double totalRadiusSquared = a.r + b.r;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    if(distance_squared(a.x, a.y, b.x, b.y) < (totalRadiusSquared))
    {
        return true;
    }

    return false;
}           

/* Utility function for the above */
double Collision::distance_squared(double x1, double y1, double x2, double y2)
{
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;
    return (delta_x * delta_x + delta_y * delta_y);
}

/* Returns total collisions used for Data at the end of the program */
int Collision::get_collision_count()
{
    return count;
}
