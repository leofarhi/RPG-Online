#include "Chunk.h"
#include "World.h"
#include "SpriteRpg.h"

Chunk* new_Chunk(int xOffset, int yOffset)
{
    Chunk* chunk = malloc(sizeof(Chunk));
    chunk->xOffset = xOffset;
    chunk->yOffset = yOffset;
    return chunk;
}
void free_Chunk(Chunk* chunk)
{
    free(chunk);
}

void CreateChunk(int xOffset, int yOffset)
{
    //fill the chunk with data
    Chunk* chunk = new_Chunk(xOffset, yOffset);
    for(int z = 0; z < 3; z++)
    {
        for (int i = 0; i < CHUNK_SIZE; i++)
        {
            for (int j = 0; j < CHUNK_SIZE; j++)
            {
                chunk->tiles[z][i][j] = 0;
            }
        }
    }
    for (int i = 0; i < CHUNK_SIZE; i++)
    {
        for (int j = 0; j < CHUNK_SIZE; j++)
        {
            chunk->tiles[0][i][j] = 100;
        }
    }
    //add the chunk to the world
    List_add(world->chunks, chunk);
    //save the chunk to a file
    //Not Implemented!!
}

void UnloadChunk(Chunk* chunk)
{
    free_Chunk(chunk);
    //remove the chunk from the world
    List_remove(world->chunks, chunk);
}

void DrawChunk(Chunk* chunk)
{
    Camera* cam = world->camera;
	int border = -TILE_SIZE;
	int x0 = ((cam->Position.x+border) / TILE_SIZE) - (chunk->xOffset * CHUNK_SIZE);
	int y0 = ((cam->Position.y+border) / TILE_SIZE) - (chunk->yOffset * CHUNK_SIZE);
	int x1 = ((cam->Position.x+SCREEN_WIDTH-border) / TILE_SIZE) - (chunk->xOffset * CHUNK_SIZE);
	int y1 = ((cam->Position.y+SCREEN_HEIGHT-border) / TILE_SIZE) - (chunk->yOffset * CHUNK_SIZE);
    x0 = fmax(0, x0);
	y0 = fmax(0, y0);
	x1 = fmin(CHUNK_SIZE, x1);
	y1 = fmin(CHUNK_SIZE, y1);
    for(int z = 0; z < 3; z++)
    {
        for (int i = y0; i < y1; i++)
        {
            for (int j = x0; j < x1; j++)
            {
                int tile = chunk->tiles[z][i][j];
                int x = j + (chunk->xOffset * CHUNK_SIZE);
                int y = i + (chunk->yOffset * CHUNK_SIZE);
                DrawTile(x*TILE_SIZE - world->camera->Position.x, y*TILE_SIZE - world->camera->Position.y, tile);
            }
        }
    }
}

void LoadChunk(int xOffset, int yOffset)
{
    Chunk* chunk = new_Chunk(xOffset, yOffset);
    //load the chunk from a file
    //Not Implemented!!
    //add the chunk to the world
    List_add(world->chunks, chunk);
}

void SaveChunk(Chunk* chunk)
{
    //save the chunk to a file
    //Not Implemented!!
}

void UpdateChunk(Chunk* chunk)
{
    //update the chunk
    //Not Implemented!!
}