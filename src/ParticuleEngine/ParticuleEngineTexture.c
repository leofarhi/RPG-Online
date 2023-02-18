#include "ParticuleEngineTexture.h"
#include "ParticuleEngine.h"
#include "ParticuleEngineDraw.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN_MODE)
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
void free_texture(PC_Texture* tex) {
    if (tex) {
        if (tex->texture) {
            if(!tex->vram){
                free(tex->texture->data);
            }
        }
        free(tex->texture);
    }
}

#elif defined(NSD_MODE)
#elif defined(CG_MODE)
#elif defined(FX_MODE)
#endif

PC_Texture* PC_LoadTexture(const char* path)
{
    #if defined(WIN_MODE)
    PC_Texture* texture = malloc(sizeof(PC_Texture));
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
        errx(EXIT_FAILURE, "error IMG_Load %s", IMG_GetError());
    texture->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture->texture == NULL)
        errx(EXIT_FAILURE, "error SDL_CreateTextureFromSurface %s", SDL_GetError());
    texture->width = surface->w;
    texture->height = surface->h;
    SDL_FreeSurface(surface);
    return texture;
    #elif defined(PSP_MODE)
    Texture* texture = load_texture(path,0,GU_TRUE);
    if (texture == NULL)
        return NULL;
    PC_Texture* pc_texture = malloc(sizeof(PC_Texture));
    pc_texture->texture = texture;
    pc_texture->vram = GU_TRUE;
    return pc_texture;
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif

    return NULL;
}

void PC_FreeTexture(PC_Texture* texture)
{
    #if defined(WIN_MODE)
    SDL_DestroyTexture(texture->texture);
    free(texture);
    #elif defined(PSP_MODE)
    free_texture(texture);
    free(texture);
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}


void PC_DrawTexture(PC_Texture* texture, int x, int y)
{
    #if defined(WIN_MODE)
    SDL_Rect rect = {x, y, texture->width, texture->height};
    SDL_RenderCopy(renderer, texture->texture, NULL, &rect);
    #elif defined(PSP_MODE)
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    sceGuEnable(GU_BLEND);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuTexMode(GU_PSM_8888, 0, 0, texture->vram);
    sceGuTexImage(0, texture->texture->pW, texture->texture->pH, texture->texture->pW, texture->texture->data);
    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);
    sceGuTexWrap(GU_CLAMP, GU_CLAMP);
    sceGuAmbientColor(0xFFFFFFFF);
    sceGuColor(0xFFFFFFFF);
    sceGuDisable(GU_DEPTH_TEST);
    struct VertexTexture *vertices = (struct VertexTexture *)sceGuGetMemory(2 * sizeof(struct VertexTexture));
    vertices[0].color = 0xFFFFFFFF;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].z = 0;
    vertices[0].u = 0;
    vertices[0].v = 0;
    vertices[1].color = 0xFFFFFFFF;
    vertices[1].x = x + texture->texture->width;
    vertices[1].y = y + texture->texture->height;
    vertices[1].z = 0;
    vertices[1].u = texture->texture->width;
    vertices[1].v = texture->texture->height;
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, vertices);
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void PC_DrawSubTexture(PC_Texture* texture, int x, int y, int sx, int sy, int sw, int sh)
{
    #if defined(WIN_MODE)
    SDL_Rect rect = {x, y, sw, sh};
    SDL_Rect rect2 = {sx, sy, sw, sh};
    SDL_RenderCopy(renderer, texture->texture, &rect2, &rect);
    #elif defined(PSP_MODE)
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    sceGuEnable(GU_BLEND);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuTexMode(GU_PSM_8888, 0, 0, texture->vram);
    sceGuTexImage(0, texture->texture->pW, texture->texture->pH, texture->texture->pW, texture->texture->data);
    sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGBA);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);
    sceGuTexWrap(GU_CLAMP, GU_CLAMP);
    sceGuAmbientColor(0xFFFFFFFF);
    sceGuColor(0xFFFFFFFF);
    sceGuDisable(GU_DEPTH_TEST);
    struct VertexTexture *vertices = (struct VertexTexture *)sceGuGetMemory(2 * sizeof(struct VertexTexture));
    vertices[0].color = 0xFFFFFFFF;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].z = 0;
    vertices[0].u = sx;
    vertices[0].v = sy;
    vertices[1].color = 0xFFFFFFFF;
    vertices[1].x = x + sw;
    vertices[1].y = y + sh;
    vertices[1].z = 0;
    vertices[1].u = sx + sw;
    vertices[1].v = sy + sh;
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, vertices);
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

int GetWidth(PC_Texture* texture){
    #if defined(WIN_MODE)
    return texture->width;
    #elif defined(PSP_MODE)
    return texture->texture->width;
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}
int GetHeight(PC_Texture* texture){
    #if defined(WIN_MODE)
    return texture->height;
    #elif defined(PSP_MODE)
    return texture->texture->height;
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}