#pragma once

/**
 * @file globals.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "main.h"

// included to prevent issue with circular dependency
// circular dependency could be unrolled, but this isn't that big of a deal
class RollersMachine;
class ChassisMachine;
class Match;

extern std::unique_ptr<RollersMachine> rollers;
extern std::unique_ptr<ChassisMachine> chassis;
extern std::unique_ptr<Match> match;
extern pros::Controller master;