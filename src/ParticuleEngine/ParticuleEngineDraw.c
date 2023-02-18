#include "ParticuleEngineDraw.h"
#include "ParticuleEngine.h"

#if defined(WIN_MODE)
#elif defined(PSP_MODE)
#include <stddef.h>
#include <math.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

struct Vertex __attribute__((aligned(16))) line[2] = {
    {0xFF00FF00, 0.0f, 0.0f, -1.0f},
    {0xFF0000FF, 0.0f, 0.5f, -1.0f},
};
#elif defined(NSD_MODE)
#elif defined(CG_MODE)
#elif defined(FX_MODE)
#endif

PC_Color PC_ColorCreate(short r, short g, short b, short a)
{
    PC_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    #if defined(WIN_MODE)
    #elif defined(PSP_MODE)
    color.color = (a << 24) | (b << 16) | (g << 8) | r;
    #elif defined(NSD_MODE)
    _rgb15 = RGB15(r, g, b);
    #elif defined(CG_MODE)
    color.Hexa = rgb(r, g, b);
    #elif defined(FX_MODE)
    color.Hexa = rgb(r, g, b);
    #endif
    return color;
}

void PC_DrawPoint(int x, int y, PC_Color color)
{
    #if defined(WIN_MODE)
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, x, y);
    #elif defined(PSP_MODE)
    sceGuDisable(GU_DEPTH_TEST);
    sceGuDisable(GU_TEXTURE_2D);
    struct Vertex *vertices = (struct Vertex *)sceGuGetMemory(2 * sizeof(struct Vertex));
    vertices[0].color = color.color;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].z = 0;
    vertices[1].color = color.color;
    vertices[1].x = x + 1;
    vertices[1].y = y + 1;
    vertices[1].z = 0;
    sceGuDrawArray(GU_POINTS, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, vertices);
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void PC_DrawLine(int x1, int y1, int x2, int y2, PC_Color color)
{
    #if defined(WIN_MODE)
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    #elif defined(PSP_MODE)
    sceGuDisable(GU_DEPTH_TEST);
    sceGuDisable(GU_TEXTURE_2D);
    struct Vertex *vertices = (struct Vertex *)sceGuGetMemory(2 * sizeof(struct Vertex));
    vertices[0].color = color.color;
    vertices[0].x = x1;
    vertices[0].y = y1;
    vertices[0].z = 0;
    vertices[1].color = color.color;
    vertices[1].x = x2;
    vertices[1].y = y2;
    vertices[1].z = 0;
    sceGuDrawArray(GU_LINES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, vertices);
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void PC_DrawRect(int x, int y, int w, int h, PC_Color color)
{
    #if defined(WIN_MODE)
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &rect);
    #elif defined(PSP_MODE)
    sceGuDisable(GU_DEPTH_TEST);
    sceGuDisable(GU_TEXTURE_2D);
    struct Vertex *vertices = (struct Vertex *)sceGuGetMemory(5 * sizeof(struct Vertex));
    vertices[0].color = color.color;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].z = 0;
    vertices[1].color = color.color;
    vertices[1].x = x + w;
    vertices[1].y = y;
    vertices[1].z = 0;
    vertices[2].color = color.color;
    vertices[2].x = x + w;
    vertices[2].y = y + h;
    vertices[2].z = 0;
    vertices[3].color = color.color;
    vertices[3].x = x;
    vertices[3].y = y + h;
    vertices[3].z = 0;
    vertices[4].color = color.color;
    vertices[4].x = x;
    vertices[4].y = y;
    vertices[4].z = 0;
    sceGuDrawArray(GU_LINE_STRIP, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 5, 0, vertices);
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void PC_DrawFillRect(int x, int y, int w, int h, PC_Color color)
{
    #if defined(WIN_MODE)
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
    #elif defined(PSP_MODE)
    sceGuDisable(GU_DEPTH_TEST);
    sceGuDisable(GU_TEXTURE_2D);
    struct Vertex *vertices = (struct Vertex *)sceGuGetMemory(2 * sizeof(struct Vertex));
    vertices[0].color = color.color;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].z = 0;
    vertices[1].color = color.color;
    vertices[1].x = x + w;
    vertices[1].y = y + h;
    vertices[1].z = 0;
    sceGuDrawArray(GU_SPRITES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, vertices);
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}