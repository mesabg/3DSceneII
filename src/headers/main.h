#pragma once
#ifndef __MAIN_H_
#define __MAIN_H_
#include <ConcreteRenderController.h>

//-- Global Variables
unsigned int amountOfEntities = 9;
unsigned int amountOfLights = 1;

//-- Global Functions
float getFrameTimeSeconds();
vec2 getMousePosition();
vec2 getDisplaySize();


#endif