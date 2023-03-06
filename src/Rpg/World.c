#include "World.h"


World* world = NULL;

World* new_World()
{
    World* world = malloc(sizeof(World));
    world->chunks = List_new();
    world->camera = new_Camera();
    return world;
}

void free_World(World* world)
{
    List_free(world->chunks);
    free_Camera(world->camera);
    free(world);
}

void CreateWorld(char* path)
{
    world = new_World();
    world->path = path;
    //fill the world with data
    //Not Implemented!!
    //save the world to a file
    //Not Implemented!!
}

void UnloadWorld()
{
    free_World(world);
}

void DrawWorld()
{
    List_node * node = world->chunks->head;
    for (int i = 0; i < world->chunks->size; i++)
    {
        Chunk * chunk = node->data;
        DrawChunk(chunk);
        node = node->next;
    }
}

void LoadWorld(char* path)
{
    world = new_World();
    world->path = path;
    //load the world from a file
    //Not Implemented!!
}

void SaveWorld()
{
    //save the world to a file
    //Not Implemented!!
}

void UpdateWorld()
{
    //update the world
    //Not Implemented!!
}

void PutTileWorld(int x, int y, int z, int tile)
{
    //put a tile in the world coordinates
    int xOffset = x / CHUNK_SIZE;
    int yOffset = y / CHUNK_SIZE;
    int xTile = x % CHUNK_SIZE;
    int yTile = y % CHUNK_SIZE;
    Chunk* chunk = GetChunk(xOffset, yOffset);
    if (chunk == NULL)
    {
        CreateChunk(xOffset, yOffset);
        chunk = GetChunk(xOffset, yOffset);
    }
    chunk->tiles[z][xTile][yTile] = tile;
}
int GetTileWorld(int x, int y, int z)
{
    //get a tile from the world coordinates
    int xOffset = x / CHUNK_SIZE;
    int yOffset = y / CHUNK_SIZE;
    int xTile = x % CHUNK_SIZE;
    int yTile = y % CHUNK_SIZE;
    Chunk* chunk = GetChunk(xOffset, yOffset);
    if (chunk == NULL)
    {
        return 0;
    }
    return chunk->tiles[z][xTile][yTile];
}

Chunk* GetChunk(int xOffset, int yOffset)
{
    //get a chunk from the world
    List_node * node = world->chunks->head;
    for (int i = 0; i < world->chunks->size; i++)
    {
        Chunk * chunk = node->data;
        if (chunk->xOffset == xOffset && chunk->yOffset == yOffset)
        {
            return chunk;
        }
        node = node->next;
    }
    return NULL;
}