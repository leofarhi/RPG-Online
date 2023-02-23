#ifndef PARTICULE_ENGINE_DRAW_H
#define PARTICULE_ENGINE_DRAW_H

#include "ParticuleEngine.h"

#if defined(WIN_MODE)
#elif defined(PSP_MODE)

// Vert Data
struct Vertex
{
	unsigned int color;
	float x, y, z;
};

#elif defined(NDS_MODE)
#include <nds.h>
#include <stdio.h>
#include <string.h>
#include "gl2d_Patched.h"
#include <nds/touch.h>
#include <nds/input.h>
#include <filesystem.h>
#include <dirent.h>

extern int PaletteID;			// the all-white pal

#elif defined(CG_MODE)
#elif defined(FX_MODE)
#endif

#if defined(CG_MODE) || defined(FX_MODE)
#define rgb(r, g, b) ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | ((b & 0xf8) >> 3);
#endif

typedef struct PC_Color
{
    short r;
    short g;
    short b;
    short a;

    #if defined(WIN_MODE)
    #elif defined(PSP_MODE)
    u32 color;
    #elif defined(NDS_MODE)
    int _rgb15;
    #elif defined(CG_MODE)
    int Hexa;
    #elif defined(FX_MODE)
    int Hexa;
    #endif
} PC_Color;

PC_Color PC_ColorCreate(short r, short g, short b, short a);

void PC_DrawPoint(int x, int y, PC_Color color);
//Draw a point on the screen at (x, y) with the given color

void PC_DrawLine(int x1, int y1, int x2, int y2, PC_Color color);
//Draw a line on the screen from (x1, y1) to (x2, y2) with the given color

void PC_DrawRect(int x, int y, int w, int h, PC_Color color);
//Draw a rectangle on the screen at (x, y) with the given width and height and color

void PC_DrawFillRect(int x, int y, int w, int h, PC_Color color);
//Draw a filled rectangle on the screen at (x, y) with the given width and height and color


#define PC_WHITE PC_ColorCreate(255,255,255,255)
#define PC_BLACK PC_ColorCreate(0,0,0,255)

#endif