#include "globals.hpp"

std::unique_ptr<RollersMachine> rollers;
std::unique_ptr<ChassisMachine> chassis;
std::unique_ptr<Match> match;
pros::Controller master{pros::E_CONTROLLER_MASTER};