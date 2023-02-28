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
#include "IMG_ASSET_280fc51b24f349439e1a8a0ca6ea6705.h"
#include "IMG_ASSET_5fd89ba580e4445ba5093b76e22bbb39.h"
#include "IMG_ASSET_adaa796b9954457bae7eb05f04d6294e.h"
	#endif//*</RSC>*/


#endif