#ifndef CHUNK_H
#define CHUNK_H

#include <List.h>

#define CHUNK_SIZE 32

typedef struct Chunk
{
    int* tiles[CHUNK_SIZE][CHUNK_SIZE];
}Chunk;

Chunk* new_Chunk(int xOffset, int yOffset); // is for allocating memory (is empty)
void free_Chunk(Chunk* chunk); // is for freeing memory

void CreateChunk(int xOffset, int yOffset); // is for creating a chunk
//this function will call new_Chunk and then fill the chunk with data and add it to the world
//and save the chunk to a file

void UnloadChunk(int xOffset, int yOffset); // is for deleting a chunk
//this function will call free_Chunk and then remove the chunk from the world

void DrawChunk(int xOffset, int yOffset); // is for drawing a chunk

void LoadChunk(int xOffset, int yOffset); // is for loading a chunk from a file

void SaveChunk(int xOffset, int yOffset); // is for saving a chunk to a file

void UpdateChunk(int xOffset, int yOffset); // is for updating a chunk



#endif