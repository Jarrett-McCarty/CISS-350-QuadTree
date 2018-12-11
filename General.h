// File   : General.h
// Author : Jarrett McCarty

// File Description:
//*****************************************************************************

// This file contains all general includes/structs used throughout the various
// files in this project.

//*****************************************************************************

#ifndef GENERAL_H
#define GENERAL_H

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

/* Struct declarations */

struct Point
{
    double x;
    double y;
};

struct Circle
{
    double x, y, r;
    Point speed;
    Color color;
    int state;
};

#endif


