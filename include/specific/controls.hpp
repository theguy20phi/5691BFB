#pragma once

#include "main.h"

/**
 * @brief Standard x-drive controls.
 *
 */
void chassisControls();

/**
 * @brief The controls for the rollers.
 * L1 = Intake
 * L2 = Outtake
 * R1 = Shoot
 * L1 + R1 = Cycle
 * L2 + R1 = Fast Shoot
 * N/A = Standby
 *
 */
void rollerControls();

/**
 * @brief Special-use buttons and Issues.
 * 
 */
void contingencies();