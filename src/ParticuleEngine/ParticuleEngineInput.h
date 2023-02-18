#ifndef PARTICULE_ENGINE_INPUT_H
#define PARTICULE_ENGINE_INPUT_H
#include "ParticuleEngine.h"
#include <List.h>

#if defined(WIN_MODE)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

extern List* InputEvents;
extern List* InputEventsHeld;

#elif defined(PSP_MODE)
static struct SceCtrlData padData;
static struct SceCtrlData oldData;

float InputAnalogX();
float InputAnalogY();
#elif defined(NSD_MODE)
#elif defined(CG_MODE)
#elif defined(FX_MODE)
#endif

void UpdateInputs();
//Updates the inputs

int IsKeyPressed(int key);
//Checks if a key is pressed (Holding down)
//key is the key to check

int IsKeyDown(int key);
//Checks if a key is down (Pressed once)

int IsKeyDownWait(int key);
//Checks if a key is down (Pressed once) and waits until the key is released

int IsKeyUp(int key);
//Checks if a key is up (Released)

int IsMouseButtonPressed(int button);
//Checks if a mouse button is pressed (Holding down)

int IsMouseButtonDown(int button);
//Checks if a mouse button is down (Pressed once)

int IsMouseButtonUp(int button);
//Checks if a mouse button is up (Released)

#endif