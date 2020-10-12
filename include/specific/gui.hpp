/**
 * @file gui.hpp
 * @author Braden Pierce (913153006@bryantschools.org)
 *
 * @copyright Copyright (c) 2020
 *
 */

#pragma once

#include "main.h"

LV_IMG_DECLARE(DOOM);

/**
 * @brief Extra Issue checks.
 *
 */
void extraChecks();

/**
 * @brief Controls the GUI on the remote.
 * Auton selection when the field control is disabled.
 * Issue display otherwise.
 *
 */
void controllerGUITaskFn();

/**
 * @brief Prints the DOOM screen on the brain.
 *
 */
void doomScreen();