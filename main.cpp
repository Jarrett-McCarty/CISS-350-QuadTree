// File   : main.cpp
// Author : Jarrett McCarty

// File Description:
//******************************************************************************

// Main file for the CISS 350 (Advanced Algorithms & Data Structures) QuadTree
// final project. 

//******************************************************************************



//---------------------------------------------------------------------------------
/* Necessary Includes */
//---------------------------------------------------------------------------------
#include "General.h"
#include "QuadTree.h"
#include "Particle.h";
#include "Collision.h"
#include "FPS.h"

//---------------------------------------------------------------------------------
/* Function headers */
//---------------------------------------------------------------------------------
std::vector<Particle*> init();
Point gen_vel();
void cleanup(std::vector<Particle*> obj);
int maxi(int x, int y);
//---------------------------------------------------------------------------------
/* const variables */
//---------------------------------------------------------------------------------
static const int MAX_PARTICLES = 1000;

//---------------------------------------------------------------------------------
/* SDL specific objects (Dr.Liows' Library) */
//---------------------------------------------------------------------------------
Surface surface(W, H);
Event event;

int main()
{
//---------------------------------------------------------------------------------
    /* Intialize all objects/variables */
//---------------------------------------------------------------------------------
    Collision collisions;
    bool end = false;
    bool slow = false;
    Rect bounds = {0, 0, W, H};
    QuadTree quad(0, bounds);

    std::vector<Particle*> objs;
    
    srand(time(NULL));

    objs = init();

    int start = getTicks();
    
    FPS sim_time;
    FPS frame_time;
    sim_time.start();
    frame_time.start();
    int last_frame = sim_time.get_ticks();
    int current_frame = last_frame;
    int frames = 0;
    int max_frames = 0;
    int fps_count = 0;
    int fps_avg = 0;
    
    while(!end)
    {
//------------------------------------------------------------------------------------
        /* Start timing */
//------------------------------------------------------------------------------------
        last_frame = current_frame;
        current_frame = sim_time.get_ticks();
//------------------------------------------------------------------------------------
        /* Check if user quits or wishes to slow down/speed up collisions */
//------------------------------------------------------------------------------------
        if (event.poll() && event.type() == QUIT)
        {
            end = true;
            break;
        }
        KeyPressed keypressed = get_keypressed();
        if (keypressed[DOWNARROW]) {slow = true; }
        if (keypressed[UPARROW]) {slow = false; }
//-------------------------------------------------------------------------------------
        /* Update the individual particles/Check boundries */
//-------------------------------------------------------------------------------------
        for(std::vector<Particle*>::const_iterator it = objs.begin(); it != objs.end(); ++it)
        {
            (*it)->update();
        }
//-------------------------------------------------------------------------------------
        /* Clear the QuadTree each pass */
//-------------------------------------------------------------------------------------
        quad.clear();
//-------------------------------------------------------------------------------------
        /* Insert all the Objects into the Tree */
//-------------------------------------------------------------------------------------
        for(std::vector<Particle*>::const_iterator it = objs.begin(); it != objs.end(); ++it)
        {
            quad.insert(*it);
        }
//-------------------------------------------------------------------------------------
        /* Create a Particle list object to help reduce collision checks in the tree */
        /* Intialize the 2D array to the MAX_PARTICLES */
        /* Set count and size of the CollisionList object */
//-------------------------------------------------------------------------------------
        CollisionList collider_list;
        collider_list.particles = new Particle*[MAX_PARTICLES];
        collider_list.count = 0;
        collider_list.size = MAX_PARTICLES;
//-------------------------------------------------------------------------------------
        /* Retreive objects in the QuadTree and perform collision detection */
//-------------------------------------------------------------------------------------
        if (!slow)
        {
            for(std::vector<Particle*>::const_iterator it = objs.begin(); it != objs.end(); ++it)
            {
                collider_list = quad.retrieve(collider_list, *it);
                collisions.collision_detection(*it, collider_list);
                collider_list.count = 0;
            }
        }
        else //if (slow)
        {
            for(std::vector<Particle*>::const_iterator it = objs.begin(); it != objs.end(); ++it)
            {
                for(std::vector<Particle*>::const_iterator it2 = objs.begin(); it2 != objs.end() && it2 != it; ++it2)
                {
                    collisions.collision_detection(*it, *it2);
                }
            }
        }
//-------------------------------------------------------------------------------------
        /* Delete all allocated CollisionList objects */
//-------------------------------------------------------------------------------------
        delete [] collider_list.particles;
//-------------------------------------------------------------------------------------
        /* Begin Drawing phase */
//-------------------------------------------------------------------------------------
        surface.lock();
        surface.fill(BLACK);
//-------------------------------------------------------------------------------------
        /* Draw the QuadTrees regions */
//-------------------------------------------------------------------------------------
        quad.draw(surface);
//-------------------------------------------------------------------------------------
        /* For each Particle object draw it to the screen */
//-------------------------------------------------------------------------------------
        for(std::vector<Particle*>::const_iterator it = objs.begin(); it != objs.end(); ++it) 
        {
            (*it)->draw(surface);
        }
//-------------------------------------------------------------------------------------
        /* End Draw Phase */
//-------------------------------------------------------------------------------------
        surface.unlock();
        surface.flip();
//-------------------------------------------------------------------------------------
        /* Get the FPS */
//-------------------------------------------------------------------------------------
        int current_frame_t = frame_time.get_ticks();
        if (current_frame_t > 1000) // 1 second has past
        {
            max_frames = maxi(frames, max_frames);
            std::cout << "FPS: " << frames << '\n';
            fps_avg += frames;
            ++fps_count;
            frames = 0;
            frame_time.start();
        }
        frames++; /* Update frames */
        //delay(2);
    }
//-------------------------------------------------------------------------------------
    /* Get and display the total run time/various scientific variables */
//-------------------------------------------------------------------------------------
    start = getTicks() - start;
    std::cout << "Total Run Time: " << start << "(milliseconds)" << '\n';
    std::cout << "Total Run Time: " << start * 0.001 << "(seconds)" << '\n';
    std::cout << "Total Run Time: " << (start * 0.001) / 60 << "(minutes)" << '\n';
    std::cout << "Max FPS: " << max_frames << '\n';
    std::cout << "Average FPS: " << fps_avg / fps_count << '\n';
    std::cout << "Total Number of Collisions: " << collisions.get_collision_count() << '\n';
//-------------------------------------------------------------------------------------
    /* Destroy all Particle Objects/clear the QuadTree */
//-------------------------------------------------------------------------------------
    cleanup(objs);
    quad.clear();
        

    return 0;
}

/* Function definition for intializing the Particle Objects */
std::vector<Particle*> init()
{
    std::vector<Particle*> particles;
    for(int i = 0; i < MAX_PARTICLES; ++i)
    {
        double x, y, r;
        if (MAX_PARTICLES > 1000)
        {
            x = rand() % W;
            y = rand() % H;
            r = 2.0;
        }
        else 
        {
            x = 1.0;
            y = 1.0;
            r = 2.0;
        }
        Point vel = gen_vel();
        Circle circle = {x, y, r, vel, CYAN, 0}; 
        Particle * p = new Particle(circle);
        particles.push_back(p);
    }

    return particles;
}

/* Function definition for generating initial velocity (Direction/speed) */
Point gen_vel()
{
    Point vel;

    vel.x = (double) rand() / RAND_MAX * 2.0;
    vel.y = (double) rand() / RAND_MAX * 2.0;
    
    return vel;
}

/* Function definiton for destroying Paricle Objects (acts as destructor) */
void cleanup(std::vector<Particle*> obj)
{
    for(std::vector<Particle*>::const_iterator it = obj.begin(); it != obj.end(); ++it)
    {
        delete *it;
    }
}

/* Function definitions for min/max for fps */
int maxi(int x, int y)
{
    if (x >= y) return x;
    else return y;
}
