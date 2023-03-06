#include "RpgResources.h"
#include "SpriteRpg.h"
#include <List.h>

SpriteRpg *AllRpgSprites[MAX_SPRITES];
List *AllRpgTexturesLoaded = NULL;

void AddToRpg(void *data, int *index, char* name)
{
    printf("Adding %s to AllRpgSprites[%d]\n", name, *index);
    AllRpgSprites[*index] = data;
    AllRpgSprites[*index]->name = name;
    (*index)++;
}

void LoadRpgResources()
{
    AllRpgTexturesLoaded = List_new();
    PC_Texture *Outside_A1 = PC_LoadTexture("assets/Images/Tiles/Outside_A1.png");
    List_add(AllRpgTexturesLoaded, Outside_A1);
    PC_Texture *Outside_A2 = PC_LoadTexture("assets/Images/Tiles/Outside_A2.png");
    List_add(AllRpgTexturesLoaded, Outside_A2);
    PC_Texture *Outside_A3 = PC_LoadTexture("assets/Images/Tiles/Outside_A3.png");
    List_add(AllRpgTexturesLoaded, Outside_A3);
    PC_Texture *Outside_A4 = PC_LoadTexture("assets/Images/Tiles/Outside_A4.png");
    List_add(AllRpgTexturesLoaded, Outside_A4);
    PC_Texture *Outside_A5 = PC_LoadTexture("assets/Images/Tiles/Outside_A5.png");
    List_add(AllRpgTexturesLoaded, Outside_A5);
    PC_Texture *Outside_B = PC_LoadTexture("assets/Images/Tiles/Outside_B.png");
    List_add(AllRpgTexturesLoaded, Outside_B);
    PC_Texture *Outside_C = PC_LoadTexture("assets/Images/Tiles/Outside_C.png");
    List_add(AllRpgTexturesLoaded, Outside_C);
    
    int index = 0;
    AddToRpg(FloorTypeRpg(Outside_A1, SubsurfaceRpg( 0, 0)), &index, "WaterGrass");
    AddToRpg(FloorTypeRpg(Outside_A1, SubsurfaceRpg( 0, INIT_TILE_SIZE * 3)), &index, "Water");
    AddToRpg(FloorTypeRpg(Outside_A1, SubsurfaceRpg( 0, INIT_TILE_SIZE * 6)), &index, "WaterDirt");
    AddToRpg(FloorTypeRpg(Outside_A1, SubsurfaceRpg( 0, INIT_TILE_SIZE * 9)), &index, "WaterSand");

    AddToRpg(FloorTypeRpg(Outside_A1, SubsurfaceRpg( INIT_TILE_SIZE * 8, 0)), &index, "WaterSnow");
    AddToRpg(FloorTypeRpg(Outside_A1, SubsurfaceRpg( INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 3)), &index, "WaterCity");
    AddToRpg(FloorTypeRpg(Outside_A1, SubsurfaceRpg( INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 6)), &index, "WaterCity2");
    AddToRpg(FloorTypeRpg(Outside_A1, SubsurfaceRpg( INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 9)), &index, "PoisonSand");

    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( 0, 0)), &index, "Grass");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( 0, INIT_TILE_SIZE * 3)), &index, "Dirt");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( 0, INIT_TILE_SIZE * 6)), &index, "Sand");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( 0, INIT_TILE_SIZE * 9)), &index, "Snow");

    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 2, 0)), &index, "GrassDirtRoad");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 3)), &index, "DirtGrassRoad");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 6)), &index, "SandGrassRoad");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 9)), &index, "SnowDirtRoad");

    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 4, 0)), &index, "GrassCobbleRoad");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 3)), &index, "DirtCobbleRoad");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 6)), &index, "SandCobbleRoad");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 9)), &index, "SnowCobbleRoad");

    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 6, 0)), &index, "CobbleRoad");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 3)), &index, "CobbleRoadSnow");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 6)), &index, "CobbleRoad2");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 9)), &index, "Carpet");

    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 8, 0)), &index, "FoliageGrass");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 3)), &index, "FoliageDirt");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 6)), &index, "FoliageSand");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 9)), &index, "FoliageSnow");

    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 10, 0)), &index, "PavedRoad");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 3)), &index, "PavedRoadSnow");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 6)), &index, "holeDirt");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 9)), &index, "holeCity");

    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 12, 0)), &index, "BarrierWood");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 3)), &index, "BarrierMetal");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 6)), &index, "BarrierStone");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 9)), &index, "BarrierWoodSnow");

    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 14, 0)), &index, "Crack");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 3)), &index, "DustBlack");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 6)), &index, "DustGreen");
    AddToRpg(FloorTypeRpg(Outside_A2, SubsurfaceRpg( INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 9)), &index, "Poison");

    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(0, 0)), &index, "House1");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(0, INIT_TILE_SIZE * 2)), &index, "House1Wall");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(0, INIT_TILE_SIZE * 4)), &index, "House2");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(0, INIT_TILE_SIZE * 6)), &index, "House2Wall");

    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 2, 0)), &index, "House3");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 2)), &index, "House3Wall");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 4)), &index, "House4");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 6)), &index, "House4Wall");

    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 4, 0)), &index, "House5");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 2)), &index, "House5Wall");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 4)), &index, "House6");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 6)), &index, "House6Wall");

    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 6, 0)), &index, "House7");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 2)), &index, "House7Wall");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 4)), &index, "House8");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 6)), &index, "House8Wall");

    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 8, 0)), &index, "House9");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 2)), &index, "House9Wall");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 4)), &index, "House10");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 6)), &index, "House10Wall");

    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 10, 0)), &index, "House11");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 2)), &index, "House11Wall");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 4)), &index, "House12");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 6)), &index, "House12Wall");

    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 12, 0)), &index, "House13");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 2)), &index, "House13Wall");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 4)), &index, "House14");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 6)), &index, "House14Wall");

    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 14, 0)), &index, "House15");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 2)), &index, "House15Wall");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 4)), &index, "House16");
    AddToRpg(WallTypeRpg(Outside_A3, SubsurfaceRpg(INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 6)), &index, "House16Wall");

    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(0, 0)), &index, "CobblestoneBrick");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 2, 0)), &index, "RedBrick");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 4, 0)), &index, "BrownBrick");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 6, 0)), &index, "Sandstone");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 8, 0)), &index, "Stone");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 10, 0)), &index, "Marble");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 12, 0)), &index, "Foliage");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 14, 0)), &index, "GlassBrick");

    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(0, INIT_TILE_SIZE * 3)), &index, "CobblestoneBrickWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 3)), &index, "RedBrickWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 3)), &index, "BrownBrickWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 3)), &index, "SandstoneWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 3)), &index, "StoneWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 3)), &index, "MarbleWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 3)), &index, "FoliageWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 3)), &index, "GlassBrickWall");

    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(0, INIT_TILE_SIZE * 5)), &index, "RedBrick2");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 5)), &index, "Sandstone2");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 5)), &index, "Sandstone3");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 5)), &index, "Marble2");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 5)), &index, "CobblestoneBrick2");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 5)), &index, "CobblestoneBrick2Snow");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 5)), &index, "CobblestoneBrick3");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 5)), &index, "CobblestoneBrick3Snow");

    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(0, INIT_TILE_SIZE * 8)), &index, "RedBrick2Wall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 8)), &index, "Sandstone2Wall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 8)), &index, "Sandstone3Wall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 8)), &index, "Marble2Wall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 8)), &index, "CobblestoneBrick2Wall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 8)), &index, "CobblestoneBrick2SnowWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 8)), &index, "CobblestoneBrick3Wall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 8)), &index, "CobblestoneBrick3SnowWall");

    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(0, INIT_TILE_SIZE * 10)), &index, "GrassEdge");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 10)), &index, "DirtEdge");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 10)), &index, "SandEdge");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 10)), &index, "SnowEdge");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 10)), &index, "PavedEdge");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 10)), &index, "Tree");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 10)), &index, "TreeSnow");
    AddToRpg(FloorTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 10)), &index, "DevilEdge");

    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(0, INIT_TILE_SIZE * 12)), &index, "GrassEdgeWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 2, INIT_TILE_SIZE * 12)), &index, "DirtEdgeWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 4, INIT_TILE_SIZE * 12)), &index, "SandEdgeWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 6, INIT_TILE_SIZE * 12)), &index, "SnowEdgeWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 8, INIT_TILE_SIZE * 12)), &index, "PavedEdgeWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 10, INIT_TILE_SIZE * 12)), &index, "TreeWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 12, INIT_TILE_SIZE * 12)), &index, "TreeSnowWall");
    AddToRpg(WallTypeRpg(Outside_A4, SubsurfaceRpg(INIT_TILE_SIZE * 14, INIT_TILE_SIZE * 12)), &index, "DevilEdgeWall");

    printf("lenRpg = %d\n", index);
}

void UnloadRpgResources()
{
    while (AllRpgTexturesLoaded->size > 0)
    {
        PC_Texture *t = (PC_Texture*)List_pop(AllRpgTexturesLoaded);
        PC_FreeTexture(t);
    }
    List_free(AllRpgTexturesLoaded);
    AllRpgTexturesLoaded = NULL;
}

void DrawTile(int x, int y, int tileId)
{
    if (tileId < 100)
        return;
    tileId -= 100;
    int indexBlock = tileId / 100;
    int indexTile = tileId % 100;
    DrawSprite(AllRpgSprites[indexBlock], indexTile, x, y);
}