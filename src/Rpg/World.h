#ifndef WORLD_H
#define WORLD_H
#include "../ParticuleEngine/ParticuleEngine.h"
#include "../ParticuleEngine/ParticuleEngineDraw.h"
#include "../ParticuleEngine/ParticuleEngineTexture.h"
#include "../ParticuleEngine/ParticuleEngineInput.h"
#include "../ParticuleEngine/Resources.h"

#include "Chunk.h"
#include "Camera.h"
#include <List.h>
#include "RpgResources.h"
#include <stdio.h>
#include <stdlib.h>
#include "SpriteRpg.h"

typedef struct World{
    Camera* camera;//is for the camera of the world
    List* chunks;//is for the chunks of the world
    char* path;//is for the path of the world files
}World;

extern World* world;

World* new_World(); // is for allocating memory (is empty)
void free_World(World* world); // is for freeing memory

void CreateWorld(char* path); // is for creating a world
//this function will call new_World and then fill the world with data
//and save the world to a file

void UnloadWorld(); // is for unloading a world

void DrawWorld(); // is for drawing a world

void LoadWorld(char* path); // is for loading a world from a file

void SaveWorld(); // is for saving a world to a file

void UpdateWorld(); // is for updating a world

void PutTileWorld(int x, int y, int z, int tile); // is for putting a tile in the world coordinates
int GetTileWorld(int x, int y, int z); // is for getting a tile from the world coordinates

Chunk* GetChunk(int xOffset, int yOffset); // is for getting a chunk from the world

#endif // WORLD_H