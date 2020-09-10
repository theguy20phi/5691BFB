#include "globals.hpp"

std::unique_ptr<RollersMachine> rollers{nullptr};
std::unique_ptr<ChassisMachine> chassis{nullptr};
std::unique_ptr<Match> match{nullptr};
pros::Controller master{pros::E_CONTROLLER_MASTER};