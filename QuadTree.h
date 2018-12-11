// File   : QuadTree.h
// Author : Jarrett McCarty

// File Description:
//*****************************************************************************

// This file contains the class declaration for the QuadTree used in this project.
// All the variables, methods, and containers are listed below. 

/*
  Public Methods Include:
                     -> Constructor
                     -> Destructor
                     -> clear method
                     -> insertion method
                     -> retrival method
                     -> draw method (used for SDL)

  Private Methods Include:
                     -> split method
                     -> index method 
                     -> draw rect method (used for SDL)

  Variables/Containers Include:
                     -> static int for maximum number of children nodes
                     -> static int for maximum number of objects
                     -> static int for maximum level of the QuadTree
                     -> int for level
                     -> vector of Particle (circle) objects
                     -> SDL rect for bounds
                     -> Pointer Array for children
*/

//*****************************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "General.h"
#include "Particle.h"

class QuadTree
{
public:
    QuadTree(int level, Rect bounds);
    virtual ~QuadTree();
    void clear();
    void insert(Particle * particle);
    CollisionList retrieve(CollisionList obj_list, Particle * particle);
    void draw(Surface & surface);
private:
    static const int MAX_CHLD = 4;
    static const int MAX_OBJ = 2;
    static const int MAX_LVL = 50;
    
    int level_;
    std::vector<Particle*> cobj_;
    Rect bounds_;
    QuadTree * children[MAX_CHLD];
    
    void split();
    int get_index(Particle * particle);
    
    void draw_rect(Surface & surface, Rect rect);
};

#endif 

