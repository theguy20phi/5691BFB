/**
 * @file routines.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 * 
 * @copyright Copyright (c) 2020
 * 
 */
 
#pragma once

#include "main.h"

// included to prevent issue with circular dependency
// circular dependency could be unrolled, but this isn't that big of a deal
class Routine;

extern Routine redLeft;
extern Routine redMidLeft;
extern Routine redMidRight;
extern Routine redRight;
extern Routine redRow;
extern Routine skills;
extern Routine blueLeft;
extern Routine blueMidLeft;
extern Routine blueMidRight;
extern Routine blueRight;
extern Routine blueRow;
extern Routine none;