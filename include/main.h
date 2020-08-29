/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2020, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

//comment out if not running tests
#define TESTING

#include "api.h"
#include "okapi/api.hpp"
#include "bfb/bfb.hpp"
using namespace okapi::literals;
using namespace bfb::literals;

#include "rollersMachine.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
//C++ only headers here
#include <exception>
#include <vector>
#include <iostream>
#include <variant>
#endif
