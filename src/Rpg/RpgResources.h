#ifndef RPG_RESOURCES_H
#define RPG_RESOURCES_H
#include <stdio.h>
#include <stdlib.h>
#include "SpriteRpg.h"
#include <List.h>

#define MAX_SPRITES 200

extern SpriteRpg *AllRpgSprites[MAX_SPRITES];
extern List *AllRpgTexturesLoaded;

void LoadRpgResources();
void UnloadRpgResources();

void DrawTile(int x, int y, int tileId);

#endif