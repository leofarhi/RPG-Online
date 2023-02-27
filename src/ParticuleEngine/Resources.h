#ifndef RESOURCES_H
#define RESOURCES_H
#include <List.h>
#include "ParticuleEngine.h"

extern List* AllResources;

typedef struct VirtualFile
{
    char* path;
    void* data;
} VirtualFile;

void* GetResource(unsigned char* path);

#if defined(NDS_MODE)
void AddTexture(unsigned char* path, const unsigned int* Bitmap, const unsigned short* Pal, int width, int height);
#elif defined(CG_MODE) || defined(FX_MODE)
void AddTexture(unsigned char* path, bopti_image_t* texture);
void AddFont(unsigned char* path, font_t* font);
#endif

void LoadResources();

void UnloadResources();

//*<RSC>*/
	#if defined(NDS_MODE)
#include "IMG_ASSET_41a8ce6b6d724607a061ad52c70d9fa5.h"
#include "IMG_ASSET_032273f9336e493ebe637da509ae2143.h"
	#endif//*</RSC>*/


#endif