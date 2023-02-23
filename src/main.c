#include "ParticuleEngine/ParticuleEngine.h"
#include "ParticuleEngine/ParticuleEngineDraw.h"
#include "ParticuleEngine/ParticuleEngineTexture.h"
#include "ParticuleEngine/ParticuleEngineInput.h"
#include "ParticuleEngine/ParticuleEngineFont.h"
#include "ParticuleEngine/Resources.h"

int main(){//int argc, char *argv[]) {
    PC_Init();
    int i = 0;
    const char* pathImg = "libs/images/test.png";
    #ifdef NDS_MODE
    AddTexture((unsigned char*)pathImg, Tilesets_Outside_A1Bitmap, Tilesets_Outside_A1Pal,256,192);
    AddTexture((unsigned char*)"libs/fonts/Font.png", FontBitmap, FontPal, 128, 128);
    #endif
    PC_Texture* texture = PC_LoadTexture(pathImg);
    PC_Font* font = NULL;
    #if defined(WIN_MODE)
    font = PC_LoadFont("libs/fonts/Calibri.ttf", 20);
    #elif defined(PSP_MODE) || defined(NDS_MODE)
    font = PC_LoadFont("libs/fonts/Font.png", 20, 8, 8, 16, 16);
    #endif
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
            PC_DrawFillRect(0+(int)i, 10, 50, 50, color);
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
        #if defined(NDS_MODE)
        if (IsKeyPressed(KEY_RIGHT))
            i++;
        if (IsKeyPressed(KEY_LEFT))
            i--;
        #endif
        #if defined(CG_MODE) || defined(FX_MODE)
        if (IsKeyPressed(KEY_RIGHT))
            i++;
        if (IsKeyPressed(KEY_LEFT))
            i--;
        if (IsKeyPressed(KEY_MENU))
            break;
        #endif
        //PC_DrawTexture(texture, 0, 0);
        PC_DrawSubTexture(texture, 50, 50, 0, 0, 50, 50);
        PC_DrawSubTextureSize(texture, 150, 50, 0, 0, 50, 50, 100, 100);
        color = PC_ColorCreate(100, 100, 255, 255);
        PC_DrawSubTextureSizeColored(texture, 150, 150, 0, 0, 50, 50, 100, 100, color);
        color = PC_ColorCreate(200, 50, 205, 255);
        PC_DrawText("Hello World", 0, 0, color, font);
        UpdateScreen();
    }
    PC_Quit();
    return 0;
}