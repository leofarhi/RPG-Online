#include "RpgMain.h"
#include "RpgResources.h"
#include "World.h"
#include "Chunk.h"
#include "SpriteRpg.h"
#include "Camera.h"

#include "../ParticuleEngine/ParticuleEngine.h"
#include "../ParticuleEngine/Resources.h"
#include "../InterfaceSystem/InterfaceSystem.h"
#include "../InterfaceSystem/EventDataSystem.h"

void RpgInit(){
    LoadRpgResources();
    CreateWorld("World1");
    CreateChunk(-1,-1);
    CreateChunk(0, 0);
    CreateChunk(1, 0);
    CreateChunk(0, 1);
    CreateChunk(1, 1);
}

void RpgExit(){
    UnloadRpgResources();
}

void RpgLoop(){
    int i = 100;
    while (1)
    {
        ClearScreen();
        UpdateInputs();
        UpdateWorld();
        DrawWorld();
        #if defined(WIN_MODE)
        if (IsKeyPressed(SDLK_ESCAPE))
            break;
        #endif
        #if defined(PSP_MODE)
        if (IsKeyPressed(PSP_CTRL_CIRCLE))
            break;
        #endif
        #if defined(NDS_MODE)
        #endif
        #if defined(CG_MODE) || defined(FX_MODE)
        if (IsKeyPressed(KEY_MENU))
            break;
        #endif
        if (IsKeyPressed(eventDataSystem->upButton))
            world->camera->Position.y -= 5;
        if (IsKeyPressed(eventDataSystem->downButton))
            world->camera->Position.y += 5;
        if (IsKeyPressed(eventDataSystem->leftButton))
            world->camera->Position.x -= 5;
        if (IsKeyPressed(eventDataSystem->rightButton))
            world->camera->Position.x += 5;
        if (IsKeyPressed(eventDataSystem->submitButton))
        {
            PutTileWorld(0,0,0,i);
            printf("PutTileWorld\n");
            i++;
            if (i%100 > AllRpgSprites[(i-100)/100]->length-1)
            {
                i+=100;
                i-=i%100;
            }

        }
        UpdateScreen();
    }
}