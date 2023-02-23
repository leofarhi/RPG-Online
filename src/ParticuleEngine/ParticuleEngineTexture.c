#include "ParticuleEngineTexture.h"
#include "ParticuleEngine.h"
#include "ParticuleEngineDraw.h"
#include "ParticuleEngineFont.h"
#include "Resources.h"
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

#elif defined(NDS_MODE)
#include <List.h>
#include <nds.h>
#include <stdio.h>
#include <string.h>
#include "gl2d_Patched.h"
#include <nds/touch.h>
#include <nds/input.h>
#include <filesystem.h>
#include <dirent.h>

int GetGlTextureSize(int size) {
	if (size <= 8) {
		return TEXTURE_SIZE_8;
	}
	else if (size <= 16) {
		return TEXTURE_SIZE_16;
	}
	else if (size <= 32) {
		return TEXTURE_SIZE_32;
	}
	else if (size <= 64) {
		return TEXTURE_SIZE_64;
	}
	else if (size <= 128) {
		return TEXTURE_SIZE_128;
	}
	else if (size <= 256) {
		return TEXTURE_SIZE_256;
	}
	else if (size <= 512) {
		return TEXTURE_SIZE_512;
	}
	else {
		return TEXTURE_SIZE_1024;
	}
};
#elif defined(CG_MODE) || defined(FX_MODE)
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
    #elif defined(NDS_MODE)
    PC_Texture* texture = (PC_Texture*)GetResource((unsigned char*)path);
    if (texture == NULL)
        return NULL;
    const unsigned int* Bitmap = texture->Bitmap;
    const unsigned short* Pal = texture->Pal;
    int width = texture->width;
    int height = texture->height;
    texture->imageData = malloc(sizeof(glImage));
    texture->TextureID = glLoadTileSet(texture->imageData, // pointer to glImage array
        width, // sprite width
        height, // sprite height
        width, // bitmap width
        height, // bitmap height
        GL_RGB256,			// texture type for glTexImage2D() in videoGL.h
        GetGlTextureSize(width), // sizeX for glTexImage2D() in videoGL.h
        GetGlTextureSize(height), // sizeY for glTexImage2D() in videoGL.h
        GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
        256,				// Length of the palette to use (16 colors)
        (u16*)Pal,		// Load our 256 color tiles palette
        (u8*)Bitmap // image data generated by GRIT
    );
    return texture;
    #elif defined(CG_MODE) || defined(FX_MODE)
    return (PC_Texture*)GetResource((unsigned char*)path);
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
    #elif defined(NDS_MODE)
    free(texture->imageData);
    texture->imageData = NULL;
    texture->TextureID = -1;
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
    #elif defined(NDS_MODE)
    if (texture->imageData == NULL || texture->TextureID == -1)
        return;
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(5));
	glColor(PC_WHITE._rgb15);
	glSetActiveTexture(texture->TextureID);
	glAssignColorTable(0, texture->TextureID);
    glSprite(x, y, GL_FLIP_NONE, texture->imageData);
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
    #elif defined(NDS_MODE)
    if (texture->imageData == NULL || texture->TextureID == -1)
        return;
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(5));
    glColor(PC_WHITE._rgb15);
    glSetActiveTexture(texture->TextureID);
    glAssignColorTable(0, texture->TextureID);
    glSubSprite(x, y, sx, sy, sw, sh, texture->imageData);
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void PC_DrawSubTextureSize(PC_Texture* texture, int x, int y, int sx, int sy, int sw, int sh, int w, int h)
{
    #if defined(WIN_MODE)
    SDL_Rect rect = {x, y, w, h};
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
    vertices[1].x = x + w;
    vertices[1].y = y + h;
    vertices[1].z = 0;
    vertices[1].u = sx + sw;
    vertices[1].v = sy + sh;
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, vertices);
    #elif defined(NDS_MODE)
    if (texture->imageData == NULL || texture->TextureID == -1)
        return;
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(5));
    glColor(PC_WHITE._rgb15);
    glSetActiveTexture(texture->TextureID);
    glAssignColorTable(0, texture->TextureID);
    glSubSpriteScale(x, y, sx, sy, sw, sh,w,h, texture->imageData);
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void PC_DrawSubTextureSizeColored(PC_Texture* texture, int x, int y, int sx, int sy, int sw, int sh, int w, int h, PC_Color color)
{
    #if defined(WIN_MODE)
    SDL_Rect rect = {x, y, w, h};
    SDL_Rect rect2 = {sx, sy, sw, sh};
    SDL_SetTextureColorMod(texture->texture, color.r, color.g, color.b);
    SDL_RenderCopy(renderer, texture->texture, &rect2, &rect);
    SDL_SetTextureColorMod(texture->texture, 255, 255, 255);
    #elif defined(PSP_MODE)
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    sceGuEnable(GU_BLEND);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuTexMode(GU_PSM_8888, 0, 0, texture->vram);
    sceGuTexImage(0, texture->texture->pW, texture->texture->pH, texture->texture->pW, texture->texture->data);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);
    sceGuTexWrap(GU_CLAMP, GU_CLAMP);
    sceGuAmbientColor(0xFFFFFFFF);
    sceGuColor(0xFFFFFFFF);
    sceGuDisable(GU_DEPTH_TEST);
    struct VertexTexture *vertices = (struct VertexTexture *)sceGuGetMemory(4 * sizeof(struct VertexTexture));
    vertices[0].color = color.color;
    vertices[0].x = x;
    vertices[0].y = y;
    vertices[0].z = 0;
    vertices[0].u = sx;
    vertices[0].v = sy;
    vertices[1].color = color.color;
    vertices[1].x = x + w;
    vertices[1].y = y;
    vertices[1].z = 0;
    vertices[1].u = sx + sw;
    vertices[1].v = sy;
    vertices[2].color = color.color;
    vertices[2].x = x;
    vertices[2].y = y + h;
    vertices[2].z = 0;
    vertices[2].u = sx;
    vertices[2].v = sy + sh;
    vertices[3].color = color.color;
    vertices[3].x = x + w;
    vertices[3].y = y + h;
    vertices[3].z = 0;
    vertices[3].u = sx + sw;
    vertices[3].v = sy + sh;
    unsigned short indices[] = {0, 1, 2, 3};
    sceGuDrawArray(GU_TRIANGLE_STRIP, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_2D, 4, indices, vertices);
    #elif defined(NDS_MODE)
    if (texture->imageData == NULL || texture->TextureID == -1)
        return;
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_ID(5));
    glColor(color._rgb15);
    glSetActiveTexture(texture->TextureID);
    glAssignColorTable(0, texture->TextureID);
    glSubSpriteScale(x, y, sx, sy, sw, sh,w,h, texture->imageData);
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

int GetWidth(PC_Texture* texture){
    #if defined(WIN_MODE)
    return texture->width;
    #elif defined(PSP_MODE)
    return texture->texture->width;
    #elif defined(NDS_MODE)
    return texture->width;
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}
int GetHeight(PC_Texture* texture){
    #if defined(WIN_MODE)
    return texture->height;
    #elif defined(PSP_MODE)
    return texture->texture->height;
    #elif defined(NDS_MODE)
    return texture->height;
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}