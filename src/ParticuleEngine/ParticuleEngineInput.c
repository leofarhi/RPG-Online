#include "ParticuleEngineInput.h"
#include "ParticuleEngine.h"
#include <List.h>

#if defined(WIN_MODE)
List* InputEvents = NULL;
List* InputEventsHeld = NULL;
#elif defined(PSP_MODE)
float InputAnalogX() {
    float v = (float)padData.Lx / 255.0f;
    v -= 0.5f;
    v *= 2.0f;

    return v;
}

float InputAnalogY() {
    float v = (float)padData.Ly / 255.0f;
    v -= 0.5f;
    v *= 2.0f;

    return v;
}
#elif defined(NDS_MODE)
#elif defined(CG_MODE)
#elif defined(FX_MODE)
#endif

void UpdateInputs()
{
    #if defined(WIN_MODE)
    while (InputEvents->size > 0)
        {
            SDL_Event* event = List_pop(InputEvents);
            if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE))
            {
                exit(0);
            }
            free(event);
        }
        List_clear(InputEvents);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.key.repeat) continue; // Ignore key repeats (holding down a key
            SDL_Event* eventCopy = malloc(sizeof(SDL_Event));
            memcpy(eventCopy, &event, sizeof(SDL_Event));
            List_add(InputEvents, eventCopy);
            if (event.type == SDL_KEYDOWN){
                SDL_Event* eventCopy2 = malloc(sizeof(SDL_Event));
                memcpy(eventCopy2, &event, sizeof(SDL_Event));
                List_add(InputEventsHeld, eventCopy2);
            }
            if (event.type == SDL_KEYUP){
                for (List_node*cur=NULL; ForEach(InputEventsHeld,&cur);)
                {
                    SDL_Event* eventHeld = (SDL_Event*)(cur->data);
                    if (eventHeld->key.keysym.sym == event.key.keysym.sym){
                        List_remove(InputEventsHeld, eventHeld);
                        free(eventHeld);
                    }
                }
            }
        }
    #elif defined(PSP_MODE)
    oldData = padData;
    sceCtrlReadBufferPositive(&padData,1);
    #elif defined(NDS_MODE)
    scanKeys();
    #elif defined(CG_MODE)
    clearevents();
    #elif defined(FX_MODE)
    clearevents();
    #endif
}

int IsKeyPressed(int key)
{
    #if defined(WIN_MODE)
    for (List_node*cur=NULL; ForEach(InputEventsHeld,&cur);)
    {
        SDL_Event* event = (SDL_Event*)(cur->data);
        if (event->type == SDL_KEYDOWN && event->key.keysym.sym == key)
        {
            return 1;
        }
        return 0;
    }
    #elif defined(PSP_MODE)
    bool current = (padData.Buttons & key) == key;
    bool last = (oldData.Buttons & key) == key;
    return current && last; // Currently pressed, and pressed last time
    #elif defined(NDS_MODE)
    return keysHeld() & ((KEYPAD_BITS)key);
    #elif defined(CG_MODE)
    return keydown(key);
    #elif defined(FX_MODE)
    return keydown(key);
    #endif

    return 0;
}

int IsKeyDown(int key)
{
    #if defined(WIN_MODE)
	for (List_node*cur=NULL; ForEach(InputEvents,&cur);)
	{
		SDL_Event* event = (SDL_Event*)(cur->data);
        if (event->type == SDL_KEYDOWN && event->key.keysym.sym == key)
        {
            return 1;
        }
        return 0;
	}
    #elif defined(PSP_MODE)
    bool current = (padData.Buttons & key) == key;
    bool last = (oldData.Buttons & key) == key;
    return current && !last; // Currently pressed, not pressed last time
    #elif defined(NDS_MODE)
    return keysDown() & ((KEYPAD_BITS)key);
    #elif defined(CG_MODE)
    return keydown(key); //a changer
    #elif defined(FX_MODE)
    return keydown(key); //a changer
    #endif

    return 0;
}

int IsKeyDownWait(int key)
{
    if (IsKeyDown(key))
    {
        while (IsKeyPressed(key))
        {
            UpdateInputs();
        }
        return 1;
    }
}

int IsKeyUp(int key)
{
    #if defined(WIN_MODE)
    for (List_node*cur=NULL; ForEach(InputEvents,&cur);)
    {
        SDL_Event* event = (SDL_Event*)(cur->data);
        if (event->type == SDL_KEYUP && event->key.keysym.sym == key)
        {
            return 1;
        }
        return 0;
    }
    #elif defined(PSP_MODE)
    bool current = (padData.Buttons & key) == key;
    bool last = (oldData.Buttons & key) == key;
    return !current && last; // Currently not pressed, and pressed last time
    #elif defined(NDS_MODE)
    return keysUp() & ((KEYPAD_BITS)key);
    #elif defined(CG_MODE)
    //TODO: Implement
    #elif defined(FX_MODE)
    //TODO: Implement
    #endif

    return 0;
}

int IsMouseButtonPressed(int button)
{
    #if defined(WIN_MODE)
    //TODO: Implement
    #elif defined(PSP_MODE)
    
    #elif defined(NDS_MODE)
    #elif defined(CG_MODE)
    //TODO: Implement
    #elif defined(FX_MODE)
    //TODO: Implement
    #endif

    return 0;
}

int IsMouseButtonDown(int button)
{
    #if defined(WIN_MODE)
    for (List_node*cur=NULL; ForEach(InputEvents,&cur);)
    {
        SDL_Event* event = (SDL_Event*)(cur->data);
        if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == button)
        {
            return 1;
        }
        return 0;
    }
    #elif defined(PSP_MODE)
    #elif defined(NDS_MODE)
    #elif defined(CG_MODE)
    //TODO: Implement
    #elif defined(FX_MODE)
    //TODO: Implement
    #endif

    return 0;
}

int IsMouseButtonUp(int button)
{
    #if defined(WIN_MODE)
    for (List_node*cur=NULL; ForEach(InputEvents,&cur);)
    {
        SDL_Event* event = (SDL_Event*)(cur->data);
        if (event->type == SDL_MOUSEBUTTONUP && event->button.button == button)
        {
            return 1;
        }
        return 0;
    }
    #elif defined(PSP_MODE)
    #elif defined(NDS_MODE)
    #elif defined(CG_MODE)
    //TODO: Implement
    #elif defined(FX_MODE)
    //TODO: Implement
    #endif

    return 0;
}