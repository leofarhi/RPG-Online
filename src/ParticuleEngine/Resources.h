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
#include "IMG_ASSET_4cd603af1de04bd0a744c312fc4b2abd.h"
#include "IMG_ASSET_69fa4f661a0a461489dddfb267322f13.h"
#include "IMG_ASSET_46475d9ddd964c03a1a35ff8ca91490a.h"
#include "IMG_ASSET_7638fe2d95b841edaea6e4cbcf387df8.h"
	#endif//*</RSC>*/


#endif