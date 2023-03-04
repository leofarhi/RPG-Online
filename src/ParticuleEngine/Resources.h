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

#if defined(PSP_MODE)
void AddTexture(unsigned char* path,int width, int height);
#elif defined(NDS_MODE)
void AddTexture(unsigned char* path, const unsigned int* Bitmap, const unsigned short* Pal, int width, int height);
#elif defined(CG_MODE) || defined(FX_MODE)
void AddTexture(unsigned char* path, bopti_image_t* texture);
void AddFont(unsigned char* path, font_t* font);
#endif

void LoadResources();

void UnloadResources();

//*<RSC>*/
	#if defined(CG_MODE) || defined(FX_MODE)
extern bopti_image_t IMG_ASSET_31f19d6da9c14d6884b855a701bba98d;
extern bopti_image_t IMG_ASSET_fd901d5d3398442093419ce154bbaac2;
extern bopti_image_t IMG_ASSET_c09fd6cfec0342278086147966074e47;
	#endif
//*</RSC>*/


#endif