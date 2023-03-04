#include "SpriteRpg.h"

int* SubsurfaceRpg(int x, int y, int w, int h) {
	int* sub = malloc(sizeof(int) * 2);
	sub[0] = x;
	sub[1] = y;
	//sub[2] = w;
	//sub[3] = h;
	return sub;
};

SpriteRpg* MakeSprite(PC_Texture* Tilesheet,int** Parts, int length, int* TypeID){
	SpriteRpg* sp = malloc(sizeof(SpriteRpg));
	sp->Tilesheet = Tilesheet;
	sp->subsurfaceCoords = malloc(sizeof(int*) * length);
	sp->length = length;
	for (int i = 0; i < length; i++)
	{
		int* i1=Parts[TypeID[(i * 4) + 0]];
		int* i2=Parts[TypeID[(i * 4) + 1]];
		int* i3=Parts[TypeID[(i * 4) + 2]];
		int* i4=Parts[TypeID[(i * 4) + 3]];
		sp->subsurfaceCoords[i] = malloc(sizeof(int) * 8);
		int* temp = sp->subsurfaceCoords[i];
		temp[0] = i1[0];
		temp[1] = i1[1];

		temp[2] = i3[0]+(INIT_TILE_SIZE/2);
		temp[3] = i3[1];

		temp[4] = i2[0];
		temp[5] = i2[1] + (INIT_TILE_SIZE/2);

		temp[6] = i4[0] + (INIT_TILE_SIZE/2);
		temp[7] = i4[1] + (INIT_TILE_SIZE/2);       
	}
	return sp;
}

void DrawSprite(SpriteRpg * sprite, int idTexture, int x, int y){
	int* sub = sprite->subsurfaceCoords[idTexture];
	//printf("%d %d %d %d\n", sub[0], sub[1], sub[2], sub[3]);
    PC_DrawSubTextureSize(sprite->Tilesheet, x, y, sub[0], sub[1], (INIT_TILE_SIZE/2), (INIT_TILE_SIZE/2), TILE_SIZE/2, TILE_SIZE/2);
    PC_DrawSubTextureSize(sprite->Tilesheet, x+TILE_SIZE/2, y, sub[2], sub[3], (INIT_TILE_SIZE/2), (INIT_TILE_SIZE/2), TILE_SIZE/2, TILE_SIZE/2);
    PC_DrawSubTextureSize(sprite->Tilesheet, x, y+TILE_SIZE/2, sub[4], sub[5], (INIT_TILE_SIZE/2), (INIT_TILE_SIZE/2), TILE_SIZE/2, TILE_SIZE/2);
    PC_DrawSubTextureSize(sprite->Tilesheet, x+TILE_SIZE/2, y+TILE_SIZE/2, sub[6], sub[7], (INIT_TILE_SIZE/2), (INIT_TILE_SIZE/2), TILE_SIZE/2, TILE_SIZE/2);
}

SpriteRpg * FloorTypeRpg(PC_Texture* Tilesheet, int* Coords) {
	int** Parts = malloc(sizeof(int*) * 6);
	int count = 0;
	for (int x = 0; x < INIT_TILE_SIZE * 2; x += INIT_TILE_SIZE)
	{
		for (int y = 0; y < INIT_TILE_SIZE * 3; y += INIT_TILE_SIZE)
		{
			Parts[count] = SubsurfaceRpg(x, y, INIT_TILE_SIZE, INIT_TILE_SIZE);
			(Parts[count])[0] += Coords[0];
			(Parts[count])[1] += Coords[1];
			count++;
		}
	}
	SpriteRpg* sp = MakeSprite(Tilesheet, Parts,48, FloorTypeID);
	sp->type = FLOOR;
	for (int i = 0; i < 6; i++)
	{
		free(Parts[i]);
	}
	free(Parts);
	free(Coords);
	return sp;
};

SpriteRpg * WallTypeRpg(PC_Texture* Tilesheet, int* Coords) {
	int** Parts = malloc(sizeof(int*) * 6);
	int count = 0;
	for (int x = 0; x < INIT_TILE_SIZE * 2; x += INIT_TILE_SIZE)
	{
		for (int y = 0; y < INIT_TILE_SIZE * 2; y += INIT_TILE_SIZE)
		{
			Parts[count] = SubsurfaceRpg(x, y, INIT_TILE_SIZE, INIT_TILE_SIZE);
			(Parts[count])[0] += Coords[0];
			(Parts[count])[1] += Coords[1];
			count++;
		}
	}

	SpriteRpg* sp = MakeSprite(Tilesheet, Parts,16, WallTypeID);
	sp->type = WALL;
	for (int i = 0; i < 4; i++)
	{
		free(Parts[i]);
	}
	free(Parts);
	free(Coords);
	return sp;
};

void FreeSprite(SpriteRpg* sprite)
{
	for (int i = 0; i < sprite->length; i++)
	{
		free(sprite->subsurfaceCoords[i]);
	}
	free(sprite->subsurfaceCoords);
	free(sprite);
}

int GetFloorID(int mat_i[9])
{
	/*double* mat = malloc(sizeof(double)*9);
	for (int i = 0; i < 9; i++)
		mat[i] = (double)mat_i[i];
	feedForward(NN_FloorSpriteID, mat);
	double* output = getOutput(NN_FloorSpriteID);
	free(mat);
	for (int j = 0; j < 47; j++){
		if (output[j] > 0.9){
			free(output);
			return j;
		}
	}
	printf("default case found\n");
	free(output);*/
	return 46;
}