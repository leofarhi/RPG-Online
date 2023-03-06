#include "ParticuleEngine/ParticuleEngine.h"
#include "ParticuleEngine/ParticuleEngineDraw.h"
#include "ParticuleEngine/ParticuleEngineTexture.h"
#include "ParticuleEngine/ParticuleEngineInput.h"
#include "ParticuleEngine/ParticuleEngineFont.h"
#include "ParticuleEngine/Resources.h"
#include "Rpg/SpriteRpg.h"

#include "InterfaceSystem/InterfaceSystem.h"

void LoopTest(){
    int i = 0;
    PC_Texture* texture = PC_LoadTexture("assets/Images/test.png");
    PC_Font* font = NULL;
    #if defined(WIN_MODE)
    font = PC_LoadFont("assets/Fonts/Calibri.ttf", 20);
    #elif defined(PSP_MODE) || defined(NDS_MODE)
    font = PC_LoadFont("assets/Fonts/Font.png", 20, 8, 8, 16, 16);
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
        color = PC_ColorCreate(255, 255, 0, 255);

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
        PC_DrawSubTexture(texture, 50, 0, 0, 0, 50, 50);
        PC_DrawSubTextureSize(texture, 150, 50, 0, 0, 50, 50, 100, 100);
        color = PC_ColorCreate(100, 100, 255, 255);
        PC_DrawSubTextureSizeColored(texture, 150, 150, 0, 0, 50, 50, 100, 100, color);
        color = PC_ColorCreate(200, 50, 205, 255);
        PC_DrawText("Hello World", 0, 0, color, font);
        UpdateScreen();
    }
}

void ExampleDrawRpg(){
	ClearScreen();
    UpdateInputs();
	PC_Texture *texture = PC_LoadTexture("assets/Images/Tiles/Outside_A1.png");
    if (texture == NULL) {
        printf("Error loading texture\n");
        return;
    }
	//DrawSubTexture(texture, 500, 500, INIT_TILE_SIZE*4, 0, INIT_TILE_SIZE, INIT_TILE_SIZE);
	SpriteRpg* sp = FloorTypeRpg(texture, SubsurfaceRpg( 0, 0));
	int count = 0;
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			DrawSprite(sp, count, x * TILE_SIZE, y * TILE_SIZE);
			count++;
		}
	}

	texture = PC_LoadTexture("assets/Images/Tiles/Outside_A3.png");
    if (texture == NULL) {
        printf("Error loading texture\n");
        return;
    }
	sp = WallTypeRpg(texture, SubsurfaceRpg( INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 2));
	count = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			DrawSprite(sp, count, x * TILE_SIZE, (y+9) * TILE_SIZE);
			count++;
		}
	}
	UpdateScreen();
	while (1)
	{
		UpdateInputs();
        #if defined(CG_MODE) || defined(FX_MODE)
        if (IsKeyPressed(KEY_MENU))
            break;
        #endif
	}
}

void button_callback(WidgetUI* w, void* data){
    printf("button_callback %i\n",(int)data);
    w->rect->Position.y += 10;
}

void scroll_callback(WidgetUI* w, void* data){
    int* i = (int*)data;
    ScrollBar* s = (ScrollBar*)w->data;
    //printf("scroll_callback %i\n",s->value);
    (*i) = s->value;
    printf("scroll_callback %i\n",*i);
}

void ExampleDrawUI()
{
    PC_Texture *texture = PC_LoadTexture("assets/Images/Tiles/Outside_A1.png");
    PC_Font* font = NULL;
    #if defined(WIN_MODE)
    font = PC_LoadFont("assets/Fonts/Calibri.ttf", 20);
    #elif defined(PSP_MODE) || defined(NDS_MODE)
    font = PC_LoadFont("assets/Fonts/Font.png", 10, 8, 8, 16, 16);
    #endif

    Interface* ui = interface_create();
    eventDataSystem->selectedUI = ui;
    Button* b = interface_make_button(ui,"b1","test b1",button_callback,(void*)1);
    b->texture = texture;
    b->font = font;
    interface_transform(ui,"b1",(Vector2){100,100},(Vector2){100,100},(Vector2){0,0},(Vector2){0,0});

    b = interface_make_button(ui,"b2","test b2",button_callback,(void*)2);
    b->font = font;
    interface_transform(ui,"b2",(Vector2){10,10},(Vector2){50,50},(Vector2){0,0},(Vector2){0,0});

    interface_make_label(ui,"l1","text1",PC_ColorCreate(255,255,255,255),font);
    interface_transform(ui,"l1",(Vector2){210,150},(Vector2){100,100},(Vector2){0,0},(Vector2){0,0});

    interface_make_inputField(ui,"i1",PC_ColorCreate(255,255,255,255),font);
    interface_transform(ui,"i1",(Vector2){210,250},(Vector2){100,50},(Vector2){0,0},(Vector2){0,0});

    interface_make_image(ui,"t1",texture);
    interface_transform(ui,"t1",(Vector2){210,350},(Vector2){100,100},(Vector2){0,0},(Vector2){0,0});

    ScrollBar* s = interface_make_scrollBar(ui,"s1",100,scroll_callback,NULL);
    s->sizeScroll = 6;
    interface_transform(ui,"s1",(Vector2){250,100},(Vector2){100,50},(Vector2){0,0},(Vector2){0,0});

    interface_make_scrollBar(ui,"s2",100,scroll_callback,NULL);
    interface_transform(ui,"s2",(Vector2){390,150},(Vector2){50,100},(Vector2){0,0},(Vector2){0,0});

    Panel* p = interface_make_panel(ui,"p1");
    WidgetUI* pWid = interface_getWidgetUI(ui,"p1");
    s = interface_get(ui, "s1" );
    s->data = &pWid->rect->Position.x;
    s = interface_get(ui, "s2" );
    s->data = &pWid->rect->Position.y;

    interface_make_rect(p->ui,"r1",PC_ColorCreate(255,0,0,255));
    interface_transform(p->ui,"r1",(Vector2){410,450},(Vector2){100,100},(Vector2){0,0},(Vector2){0,0});

    #ifndef WIN_MODE
    //si c'est pas windows on change la disposition des elements
    interface_transform(ui,"b1",(Vector2){0,0},(Vector2){30,30},(Vector2){0,0},(Vector2){0,0});
    interface_transform(ui,"b2",(Vector2){40,0},(Vector2){30,30},(Vector2){0,0},(Vector2){0,0});
    interface_transform(ui,"l1",(Vector2){10,40},(Vector2){90,30},(Vector2){0,0},(Vector2){0,0});
    interface_transform(ui,"i1",(Vector2){10,80},(Vector2){90,30},(Vector2){0,0},(Vector2){0,0});
    interface_transform(ui,"t1",(Vector2){100,10},(Vector2){20,40},(Vector2){0,0},(Vector2){0,0});
    interface_transform(ui,"s1",(Vector2){10,120},(Vector2){90,30},(Vector2){0,0},(Vector2){0,0});
    interface_transform(ui,"s2",(Vector2){120,80},(Vector2){30,90},(Vector2){0,0},(Vector2){0,0});
    interface_transform(p->ui,"r1",(Vector2){180,80},(Vector2){30,30},(Vector2){0,0},(Vector2){0,0});
    interface_transform(ui,"p1",(Vector2){0,10},(Vector2){0,0},(Vector2){0,0},(Vector2){0,0});
    #endif

    while (1)
    {
        ClearScreen();
        UpdateInputs();
        #if defined(CG_MODE) || defined(FX_MODE)
        if (IsKeyPressed(KEY_MENU))
            break;
        #endif
        ////
        interface_update(ui);
        interface_draw(ui);
        //draw Mouse
        PC_DrawFillRect(MousePosition.x - 5, MousePosition.y - 5, 10, 10, PC_ColorCreate(255, 0, 255, 255));

        if (IsKeyDown(eventDataSystem->submitButton))
            PC_DrawFillRect(SCREEN_WIDTH - 10, 0, 10, 10, PC_ColorCreate(255, 0, 0, 255));
        else if (IsKeyPressed(eventDataSystem->submitButton))
            PC_DrawFillRect(SCREEN_WIDTH - 10, 0, 10, 10, PC_ColorCreate(0, 255, 0, 255));
        else if (IsKeyUp(eventDataSystem->submitButton))
            PC_DrawFillRect(SCREEN_WIDTH - 10, 0, 10, 10, PC_ColorCreate(0, 0, 255, 255));
        UpdateScreen();
    }
    
}