#ifndef CHUNK_H
#define CHUNK_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <List.h>

#define CHUNK_SIZE 16

typedef struct Chunk
{
    int tiles[3][CHUNK_SIZE][CHUNK_SIZE];
    int xOffset;
	int yOffset;
}Chunk;

Chunk* new_Chunk(int xOffset, int yOffset); // is for allocating memory (is empty)
void free_Chunk(Chunk* chunk); // is for freeing memory

void CreateChunk(int xOffset, int yOffset); // is for creating a chunk
//this function will call new_Chunk and then fill the chunk with data and add it to the world
//and save the chunk to a file

void UnloadChunk(Chunk* chunk); // is for deleting a chunk
//this function will call free_Chunk and then remove the chunk from the world

void DrawChunk(Chunk* chunk); // is for drawing a chunk

void LoadChunk(int xOffset, int yOffset); // is for loading a chunk from a file

void SaveChunk(Chunk* chunk); // is for saving a chunk to a file

void UpdateChunk(Chunk* chunk); // is for updating a chunk



#endif