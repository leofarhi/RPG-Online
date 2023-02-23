#include "ParticuleEngineFont.h"
#include <math.h>
#include <string.h>

PC_Font* MainFont = NULL;

#if defined(PSP_MODE) || defined(NDS_MODE)
PC_Font* PC_LoadFont(const char* path,int size, int w, int h,int row, int col)
#else
PC_Font* PC_LoadFont(const char* path, int size)
#endif
{
    #if defined(WIN_MODE)
    PC_Font* font = malloc(sizeof(PC_Font));
    font->font = TTF_OpenFont(path, size);
    if (font->font == NULL)
    {
        printf("Error loading font: %s\n", TTF_GetError());
        exit(1);
    }
    return font;
    #elif defined(PSP_MODE) || defined(NDS_MODE)
    PC_Texture* texture = PC_LoadTexture(path);
    if (texture == NULL)
        return NULL;
    PC_Font* font = malloc(sizeof(PC_Font));
    font->texture = texture;
    font->w = w;
    font->h = h;
    font->row = row;
    font->col = col;
    font->size = size;
    return font;
    #elif defined(NDS_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void SetMainFont(PC_Font* font)
{
    MainFont = font;
}

void PC_DrawText(const unsigned char *text, int x, int y, PC_Color color, PC_Font* font)
{
    if (font == NULL)
        return;
    #if defined(WIN_MODE)
    SDL_Color sdlColor = {color.r, color.g, color.b, color.a};
    SDL_Surface* textSurface = TTF_RenderText_Blended(font->font, text, sdlColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect rect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    #elif defined(PSP_MODE) || defined(NDS_MODE)
    int t = fmax(font->h, font->w);
    int scale = font->size / t;
    int len = strlen(text);
    for(int i = 0; i < len; i++){
        char c = text[i];
        int row = c / font->col;
        int col = c % font->col;
        int u = col * font->w;
        int v = row * font->h;
        PC_DrawSubTextureSizeColored(font->texture, x + i * font->w * scale, y, u, v, font->w, font->h, font->w * scale, font->h * scale, color);
    }
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}