#pragma once
#ifndef __MAIN_H_
#define __MAIN_H_
#include <ConcreteRenderController.h>

//-- Global Variables
unsigned int amountOfEntities = 11;
unsigned int amountOfLights = 1;
unsigned int Gwidth = 1440;
unsigned int Gheight = 900;

//-- Global Functions
float getFrameTimeSeconds();
vec2 getMousePosition();
vec2 getDisplaySize();


#endif