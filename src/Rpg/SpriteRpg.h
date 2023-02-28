#ifndef SPRITERPG_H
#define SPRITERPG_H

#include "../ParticuleEngine/ParticuleEngine.h"
#include "../ParticuleEngine/ParticuleEngineDraw.h"
#include "../ParticuleEngine/ParticuleEngineTexture.h"
#include "../ParticuleEngine/ParticuleEngineInput.h"
#include "../ParticuleEngine/Resources.h"

#ifdef WIN_MODE
#define INIT_TILE_SIZE 48
#define TILE_SIZE 48
#elif defined(NDS_MODE)
#define INIT_TILE_SIZE 16
#define TILE_SIZE 24
#elif defined(PSP_MODE)
#define INIT_TILE_SIZE 16
#define TILE_SIZE 32
#elif defined(CG_MODE)
#define INIT_TILE_SIZE 16
#define TILE_SIZE 16
#endif

typedef enum TypeSprite{
	FLOOR,
	WALL,
}TypeSprite;

typedef struct SpriteRpg{
	PC_Texture* Tilesheet;
	int** subsurfaceCoords;
	int length;
	TypeSprite type;
}SpriteRpg;

static int FloorTypeID[192] = { 5, 4, 2, 1, 3, 4, 2, 1, 5, 4, 3, 1, 3, 4, 3, 1, 5, 4, 2, 3, 3, 4, 2, 3, 5, 4, 3, 3, 3, 4, 3, 3, 5, 3, 2, 1, 3, 3, 2, 1, 5, 3, 3, 1, 3, 3, 3, 1, 5, 3, 2, 3, 3, 3, 2, 3, 5, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 3, 1, 2, 1, 2, 3, 2, 1, 3, 3, 4, 4, 1, 1, 4, 4, 1, 3, 4, 3, 1, 1, 4, 3, 1, 3, 5, 4, 5, 4, 5, 3, 5, 4, 3, 4, 5, 4, 3, 3, 5, 4, 5, 5, 2, 2, 3, 5, 2, 2, 5, 5, 3, 2, 3, 5, 3, 2, 2, 1, 5, 4, 4, 5, 1, 2, 0, 1, 1, 1, 0, 1, 1, 3, 4, 4, 4, 4, 4, 3, 0, 4, 5, 5, 5, 0, 3, 5, 5, 0, 2, 2, 2, 2, 2, 2, 3, 2, 1, 1, 0, 4, 1, 2, 1, 2, 2, 2, 5, 0, 4, 5, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0 };
static int WallTypeID[64] = { 3, 2, 1, 0, 1, 0, 1, 0, 2, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 0, 3, 2, 2, 2, 2, 2, 0, 0, 2, 2, 3, 3, 1, 1, 1, 1, 1, 1, 2, 3, 0, 1, 0, 1, 0, 1, 3, 3, 3, 3, 1, 1, 3, 3, 2, 3, 2, 3, 0, 1, 2, 3 };

void DrawSprite(SpriteRpg * sprite, int idTexture, int x, int y);
void ExampleDraw();

SpriteRpg * WallType(PC_Texture* Tilesheet, int* Coords);
SpriteRpg * FloorType(PC_Texture* Tilesheet, int* Coords);

int* SubsurfaceRpg(int x, int y, int w, int h);

SpriteRpg* MakeSprite(PC_Texture* Tilesheet,int** Parts, int length, int* TypeID);

void FreeSprite(SpriteRpg* sprite);

int GetFloorID(int mat[9]);

#endif