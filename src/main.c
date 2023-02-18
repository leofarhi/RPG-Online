#include "ParticuleEngine/ParticuleEngine.h"
#include "ParticuleEngine/ParticuleEngineDraw.h"
#include "ParticuleEngine/ParticuleEngineTexture.h"
#include "ParticuleEngine/ParticuleEngineInput.h"

int main(){//int argc, char *argv[]) {
    PC_Init();
    int i = 0;
    PC_Texture* texture = PC_LoadTexture("cheats/test.png");
    while (1)
    {
        ClearScreen();
        UpdateInputs();
        PC_Color color = PC_ColorCreate(255, 255, 0, 255);
        PC_DrawLine(0, 0, 100, 100,color);
        color = PC_ColorCreate(255, 0, 255, 255);
        PC_DrawRect(0, 0, 100, 100, color);
        color = PC_ColorCreate(0, 255, 255, 255);
        PC_DrawFillRect(100, 100, 100, 100, color);
        color = PC_ColorCreate(255, 0, 0, 255);
        PC_DrawPoint(200, 200, color);
        color = PC_ColorCreate(0, 255, 0, 255);
        if (texture!=NULL)
            PC_DrawFillRect(0+(int)i, 210, 50, 50, color);
        #if defined(WIN_MODE)
        if (IsKeyPressed(SDLK_RIGHT))
            i++;
        if (IsKeyPressed(SDLK_LEFT))
            i--;
        if (IsKeyPressed(SDLK_ESCAPE))
            break;
        #endif
        #if defined(PSP_MODE)
        if (IsKeyPressed(PSP_CTRL_RIGHT))
            i++;
        if (IsKeyPressed(PSP_CTRL_LEFT))
            i--;
        if (IsKeyPressed(PSP_CTRL_CIRCLE))
            break;
        #endif
        //PC_DrawTexture(texture, 0, 0);
        PC_DrawSubTexture(texture, 50, 50, 0, 0, 50, 50);
        UpdateScreen();
    }
    PC_Quit();
    return 0;
}