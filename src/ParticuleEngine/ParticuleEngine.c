#include "ParticuleEngine.h"

#include "ParticuleEngineDraw.h"
#include "ParticuleEngineTexture.h"
#include "ParticuleEngineInput.h"

#if defined(WIN_MODE)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

void errx(int exitcode, const char *format, const char* error)
{
    fprintf(stderr, format, error);
    exit(exitcode);
}

#elif defined(PSP_MODE)
#include "Libs/PSP/common/callbacks.h"
#include "Libs/PSP/common/common-sce.h"
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>

PSP_MODULE_INFO("Engine", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#elif defined(NSD_MODE)
#elif defined(CG_MODE)
#elif defined(FX_MODE)
#endif

void PC_Init()
{
    #if defined(WIN_MODE)
        // Initializes the SDL.
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            errx(EXIT_FAILURE, "error Init %s", SDL_GetError());
            // Creates a window.
        window = SDL_CreateWindow("Engine", 50, 50, SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);// | SDL_WINDOW_RESIZABLE);
        if (window == NULL)
            errx(EXIT_FAILURE, "error window %s", SDL_GetError());

        // Creates a renderer.
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
            errx(EXIT_FAILURE, "error render %s", SDL_GetError());

        // Initializes the image library.
        if (IMG_Init(IMG_INIT_PNG) == 0)
            errx(EXIT_FAILURE, "error IMG_Init %s", IMG_GetError());

        // Initializes the font library.
        if (TTF_Init() == -1)
            errx(EXIT_FAILURE, "error TTF_Init %s", TTF_GetError());

        // Dispatches the events.
        InputEvents = List_new();
        InputEventsHeld = List_new();
    #elif defined(PSP_MODE)
        // Boilerplate
        SetupCallbacks();

        // Initialize Graphics
        initGraphics(list);

        // Initialize Matrices
        sceGumMatrixMode(GU_PROJECTION);
        sceGumLoadIdentity();
        sceGumOrtho(-16.0f / 9.0f, 16.0f / 9.0f, -1.0f, 1.0f, -10.0f, 10.0f);

        sceGumMatrixMode(GU_VIEW);
        sceGumLoadIdentity();

        sceGumMatrixMode(GU_MODEL);
        sceGumLoadIdentity();

        sceCtrlSetSamplingCycle(0);
        sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void PC_Quit()
{
    #if defined(WIN_MODE)
        // Quits the font library.
        TTF_Quit();

        // Quits the image library.
        IMG_Quit();

        // Destroys the renderer.
        SDL_DestroyRenderer(renderer);

        // Destroys the window.
        SDL_DestroyWindow(window);

        // Quits the SDL.
        SDL_Quit();
    #elif defined(PSP_MODE)
        // Terminate Graphics
        termGraphics();

        // Exit Game
        sceKernelExitGame();
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void ClearScreen()
{
    #if defined(WIN_MODE)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    #elif defined(PSP_MODE)
        startFrame(list);

        // We're doing a 2D, Non-Textured render 
        sceGuDisable(GU_DEPTH_TEST);
        //sceGuDisable(GU_TEXTURE_2D);
        //sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
        sceGuEnable(GU_BLEND);

        //Clear background to Bjack
        sceGuClearColor(0xFF000000);
        sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT | GU_STENCIL_BUFFER_BIT);
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}

void UpdateScreen()
{
    #if defined(WIN_MODE)
        SDL_RenderPresent(renderer);
    #elif defined(PSP_MODE)
        endFrame();
    #elif defined(NSD_MODE)
    #elif defined(CG_MODE)
    #elif defined(FX_MODE)
    #endif
}