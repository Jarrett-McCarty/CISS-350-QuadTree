// File   : Particle.cpp
// Author : Jarrett McCarty

#include "General.h"
#include "Particle.h"
#include <iostream>

/* Constructor used as a wrapper for circle object */
Particle::Particle(Circle circle)
    :circle_(circle)
{}

/* Destructor */
Particle::~Particle()
{}

/* Returns circle object */
Circle Particle::get_circle()
{
    return circle_;
}

/* Gets state of the circle */
int & Particle::get_state()
{
    return circle_.state;
}

/* Gets velocity of circle using point struct */
Point Particle::get_speed()
{
    return circle_.speed;
}

/* Ablility to set a circle object */
void Particle::set_circle(Circle new_circle)
{
    circle_ = new_circle;
}

/* Ability to set circle speed */
void Particle::set_speed(Point new_speed)
{
    circle_.speed = new_speed;
}

/* Updates Particle object (speed and directon to keep bounds */
void Particle::update()
{
    circle_.x += circle_.speed.x;
    circle_.y += circle_.speed.y;
    if (circle_.x >= (W - 10) - circle_.r && circle_.speed.x > 0)
    {
        circle_.speed.x = -circle_.speed.x;
    }
    if (circle_.x <= circle_.r && circle_.speed.x < 0)
    {
        circle_.speed.x = -circle_.speed.x;
    }
    if (circle_.y >= (H - 10) - circle_.r && circle_.speed.y > 0)
    {
        circle_.speed.y = -circle_.speed.y;
    }
    if (circle_.y <= circle_.r && circle_.speed.y < 0)
    {
        circle_.speed.y = -circle_.speed.y;
    }
}

/* Fucntion to change color of particles after collision */
/* Will always change in a sequence GREEN->ORANGE->CYAN->GREEN */
void Particle::change_color()
{
    
    switch (circle_.state)
    {
        case 0:
            circle_.color = GREEN;
            circle_.state += 1;
            break;
        case 1:
            if (circle_.state - 1 == 0)
            {
                circle_.color = ORANGE;
                circle_.state += 1;
            }
            break;
        case 2:
            if (circle_.state - 1 == 1)
            {
                circle_.color = CYAN;
                circle_.state = 0;
            }
            break;
    }
}

/* Draws particle to surface */
void Particle::draw(Surface & surface)
{
    surface.put_circle((int)circle_.x - (int)circle_.r, (int)circle_.y - (int)circle_.r, (int)(2 * circle_.r), circle_.color);
}

