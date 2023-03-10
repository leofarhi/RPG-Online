#ifndef PARTICULE_ENGINE_TEXTURE_H
#define PARTICULE_ENGINE_TEXTURE_H
#include "ParticuleEngine.h"
#include "ParticuleEngineDraw.h"

#if defined(WIN_MODE)  || defined(LINUX_MODE)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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

struct VertexTexture
{
    float u, v;
	unsigned int color;
	float x, y, z;
};
#elif defined(NDS_MODE)
#elif defined(CG_MODE) || defined(FX_MODE)
#include <gint/image.h>
#endif

#include <List.h>

typedef struct PC_Texture
{
    #if defined(WIN_MODE)  || defined(LINUX_MODE)
    SDL_Texture* texture;
    int width;
    int height;
    #elif defined(PSP_MODE)
    Texture* texture;
    int vram;
    int width;
    int height;
    #elif defined(NDS_MODE)
    int width;
    int height;
    glImage* imageData;
    const unsigned int* Bitmap;
    const unsigned short* Pal;
    int TextureID;
    #elif defined(CG_MODE)
    bopti_image_t* texture;
    #elif defined(FX_MODE)
    bopti_image_t* texture;
    #endif
} PC_Texture;

int GetWidth(PC_Texture* texture);
//returns the width of a texture
//texture is a pointer to a PC_Texture struct

int GetHeight(PC_Texture* texture);
//returns the height of a texture
//texture is a pointer to a PC_Texture struct

PC_Texture* PC_LoadTexture(const char* path);
//Loads a texture from a file
//path is a path to a file
//returns a pointer to a PC_Texture struct

void PC_FreeTexture(PC_Texture* texture);
//frees the memory allocated for the texture
//texture is a pointer to a PC_Texture struct

void PC_DrawTexture(PC_Texture* texture, int x, int y);
//draws a texture on the screen
//texture is a pointer to a PC_Texture struct
//x and y are the coordinates of the top left corner of the texture

void PC_DrawSubTexture(PC_Texture* texture, int x, int y, int sx, int sy, int sw, int sh);
//draws a part of a texture on the screen
//texture is a pointer to a PC_Texture struct
//x and y are the coordinates of the top left corner of the texture
//sx and sy are the coordinates of the top left corner of the part of the texture to draw
//sw and sh are the width and height of the part of the texture to draw

void PC_DrawSubTextureSize(PC_Texture* texture, int x, int y, int sx, int sy, int sw, int sh, int w, int h);
//draws a part of a texture on the screen
//texture is a pointer to a PC_Texture struct
//x and y are the coordinates of the top left corner of the texture
//sx and sy are the coordinates of the top left corner of the part of the texture to draw
//sw and sh are the width and height of the part of the texture to draw
//w and h are the width and height of the texture to draw

void PC_DrawSubTextureSizeColored(PC_Texture* texture, int x, int y, int sx, int sy, int sw, int sh, int w, int h, PC_Color color);
//draws a part of a texture on the screen
//texture is a pointer to a PC_Texture struct
//x and y are the coordinates of the top left corner of the texture
//sx and sy are the coordinates of the top left corner of the part of the texture to draw
//sw and sh are the width and height of the part of the texture to draw
//w and h are the width and height of the texture to draw
//color is the color of the texture

#endif