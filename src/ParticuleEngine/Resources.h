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
extern bopti_image_t IMG_ASSET_79d64f252d1e4d7caad296a5120df39a;
extern bopti_image_t IMG_ASSET_3f10cbf39fde41e284127ce9f3730623;
extern bopti_image_t IMG_ASSET_5fd24c34876945c4a8b61b54cfbdd979;
extern bopti_image_t IMG_ASSET_c7cb1bc3a93b43f4a9f0f77aca69a240;
extern bopti_image_t IMG_ASSET_c8cd4ace66c349899f21702f33a66ab2;
extern bopti_image_t IMG_ASSET_43651f91e1b645908815b7f9f52c585f;
extern bopti_image_t IMG_ASSET_8e30160db3ec47579114e8a0c93f9691;
extern bopti_image_t IMG_ASSET_683472dd29444b698217528d6889a5e6;
	#endif
//*</RSC>*/


#endif