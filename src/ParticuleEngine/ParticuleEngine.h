#ifndef PARTICULE_ENGINE_H
#define PARTICULE_ENGINE_H
#include <List.h>

#if defined(FX9860G)
#define FX_MODE
#elif defined(FXCG50)
#define CG_MODE
#endif

#if defined(WIN_MODE)
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

void errx(int exitcode, const char *format, const char * error);

#elif defined(PSP_MODE)
#include "Libs/PSP/common/common-sce.h"
#include "Libs/PSP/common/callbacks.h"
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

// Define PSP Width / Height
#define PSP_BUF_WIDTH (512)
#define PSP_SCR_WIDTH (480)
#define PSP_SCR_HEIGHT (272)


static unsigned int __attribute__((aligned(16))) list[262144];

#define SCREEN_WIDTH PSP_SCR_WIDTH // 480
#define SCREEN_HEIGHT PSP_SCR_HEIGHT // 272

#elif defined(NSD_MODE)
#include <nds.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gl2d_Patched.h"
#include <nds/touch.h>
#include <nds/input.h>
#include <filesystem.h>
#include <dirent.h>
#elif defined(CG_MODE)
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/display.h>
#include <gint/rtc.h>
#include <gint/keyboard.h>
#include <gint/timer.h>
#include <gint/clock.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#elif defined(FX_MODE)
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/display.h>
#include <gint/rtc.h>
#include <gint/keyboard.h>
#include <gint/timer.h>
#include <gint/clock.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#else
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#endif

//if not c++ compiler
#ifndef __cplusplus
typedef int bool;
#define true 1
#define false 0
#endif

void PC_Init();
//Initializes the engine

void PC_Quit();
//Quits the engine

void ClearScreen();
//Clears the screen

void UpdateScreen();
//Updates the screen

#endif