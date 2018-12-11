// File   : QuadTree.cpp
// Author : Jarrett McCarty

// File Description:
//*****************************************************************************

// This file contains all function bodies for the QuadTree class.
// To learn more about what this file contains, see the file QuadTree.h.
// Minor comments are placed throughout the logic.

//*****************************************************************************

#include "QuadTree.h"

/* Constructor */
QuadTree::QuadTree(int level, Rect bounds)
    : level_(level), bounds_(bounds)
{
    /* For all children of the QuadTree assign them NULL */
    for(int i = 0; i < MAX_CHLD; ++i)
    {
        children[i] = NULL;
    }
}

/* Destructor */
QuadTree::~QuadTree()
{
    /* Delete all children */
    for(int i = 0; i < MAX_CHLD; ++i)
    {
        delete children[i];
    }
}

/* Clear function */
void QuadTree::clear()
{
    /* Clears all children within the tree and assigns them NULL */
    cobj_.clear();
    if(children[0] != NULL)
    {
        for(int i = 0; i < MAX_CHLD; ++i)
        {
            children[i]->clear();
            delete children[i];
            children[i] = NULL;
        }
    }
}

/* Inserts particle objects into the QuadTree from index of the particle */
/* If size grows past limits split */
void QuadTree::insert(Particle * particle)
{
    if(children[0] != NULL)
    {
        int index = get_index(particle);

        if(index != -1)
        {
            children[index]->insert(particle);
            return;
        }
    }

    cobj_.push_back(particle);

    if(cobj_.size() > MAX_OBJ && level_ < MAX_LVL)
    {
        if(children[0] == NULL)
        {
            split();
        }

        int i = 0;
        while(i < cobj_.size())
        {
            int index = get_index(cobj_[i]);
            if(index != -1)
            {
                children[index]->insert(cobj_[i]);
                cobj_.erase(cobj_.begin() + i);
            }
            ++i;
            
        }
    }
}

/*
Return a list of particles that occupy the same quadtree
*/
CollisionList QuadTree::retrieve(CollisionList obj_list, Particle * particle)
{
    int index = get_index(particle);
    if(index != -1 && children[0] != NULL)
    {
        CollisionList temp = children[index]->retrieve(obj_list, particle);
        for(int i = 0; i < temp.count; i++)
        {
            obj_list.particles[obj_list.count] = temp.particles[i];
            obj_list.count++;
        }
    }
    
    else
    {
        for(int i = 0; i < cobj_.size(); i++)
        {
            obj_list.particles[obj_list.count] = cobj_[i];
            obj_list.count++;
        }
    }
    
    return obj_list;
}

/* Draw */
void QuadTree::draw(Surface & surface)
{
    draw_rect(surface, bounds_);
    if(children[0] != NULL)
    {
        for(int i = 0; i < 4; ++i)
        {
            children[i]->draw(surface);
        }
    }
}

/*
Subdivides the quadtree into 4 sections
Creating 4 child nodes 1 for each section
*/
void QuadTree::split()
{
    int sub_w = (int)(bounds_.w / 2);
    int sub_h = (int)(bounds_.h / 2);
    int x = (int)bounds_.x;
    int y = (int)bounds_.y;

    Rect c1 = {x, y, sub_w, sub_h};
    children[0] = new QuadTree(level_ + 1, c1);

    Rect c2 = {x + sub_w, y, sub_w, sub_h};
    children[1] = new QuadTree(level_ + 1, c2);

    Rect c3 = {x, y + sub_h, sub_w, sub_h};
    children[2] = new QuadTree(level_ + 1, c3);

    Rect c4 = {x + sub_w, y + sub_h, sub_w, sub_h};
    children[3] = new QuadTree(level_ + 1, c4);
}

/*
Returns which childnode this circle could fit in
if it can't fit exactly into any of the child nodes it returns -1
so it should stay in the parent
*/
int QuadTree::get_index(Particle * particle)
{
    int index = -1;
    Circle dim = particle->get_circle();
    int vert_mid = bounds_.x + bounds_.w / 2;
    int hori_mid = bounds_.y + bounds_.h / 2;

    bool top_quad = dim.y < hori_mid && dim.y + (2 * dim.r) < hori_mid;
    bool bottom_quad = dim.y > hori_mid && dim.y + (2 * dim.r) > hori_mid;

    if(dim.x < vert_mid && dim.x + (2 * dim.r) < vert_mid)
    {
        if(top_quad)
        {
            index = 0;
        }
        else if(bottom_quad)
        {
            index = 2;
        }
    }
    else if(dim.x > vert_mid && dim.x + (2 * dim.r) > vert_mid)
    {
        if(top_quad)
        {
            index = 1;
        }
        else if(bottom_quad)
        {
            index = 3;
        }
    }

    return index;
}

/* Draws rects for visible representation of the QuadTree */
void QuadTree::draw_rect(Surface & surface, Rect rect)
{
    surface.put_rect(rect, WHITE);
    
    rect.x += 1;
    rect.y += 1;
    rect.w -= 2;
    rect.h -= 2;

    surface.put_rect(rect, BLACK);
}
