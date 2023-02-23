#include "Resources.h"
#include "ParticuleEngine.h"
#include "ParticuleEngineFont.h"
#include "ParticuleEngineTexture.h"
#include <List.h>

#if defined(PSP_MODE)
//*<PROJECT_NAME>*/
#define PROJECT_NAME "Engine"
//*</PROJECT_NAME>*/
PSP_MODULE_INFO(PROJECT_NAME, 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
#endif

List* AllResources = NULL;

void* GetResource(unsigned char* path)
{
    for (List_node*cur=NULL; ForEach(AllResources,&cur);)
    {
        VirtualFile* file = (VirtualFile*)(cur->data);
        if (strcmp(file->path, path) == 0)
        {
            return file->data;
        }
    }
    return NULL;
}

#if defined(NDS_MODE)
void AddTexture(unsigned char* path, const unsigned int* Bitmap, const unsigned short* Pal, int width, int height)
{
    VirtualFile* file = malloc(sizeof(VirtualFile));
    file->path = malloc(strlen(path) + 1);
    strcpy(file->path, path);
    file->data = malloc(sizeof(PC_Texture));
    PC_Texture* texture = (PC_Texture*)file->data;
    texture->imageData = NULL;
    texture->width = width;
    texture->height = height;
    texture->Bitmap = Bitmap;
    texture->TextureID = 0;
    texture->Pal = Pal;
    List_add(AllResources, file);
}
#elif defined(CG_MODE) || defined(FX_MODE)
void AddTexture(unsigned char* path, bopti_image_t* texture)
{
    VirtualFile* file = malloc(sizeof(VirtualFile));
    file->path = malloc(strlen(path) + 1);
    strcpy(file->path, path);
    file->data = malloc(sizeof(PC_Texture));
    PC_Texture* tex = (PC_Texture*)file->data;
    tex->texture = texture;
    List_add(AllResources, file);
}
void AddFont(unsigned char* path, font_t* font)
{
    VirtualFile* file = malloc(sizeof(VirtualFile));
    file->path = malloc(strlen(path) + 1);
    strcpy(file->path, path);
    file->data = malloc(sizeof(PC_Font));
    PC_Font* ft = (PC_Font*)file->data;
    ft->font = font;
    List_add(AllResources, file);
}
#endif

void LoadResources(){
    #if defined(NDS_MODE) || defined(CG_MODE) || defined(FX_MODE)
    AllResources = List_new();
    #endif
//*<RSC_LOAD>*/
//*</RSC_LOAD>*/
}

void UnloadResources(){
//*<RSC_UNLOAD>*/
//*</RSC_UNLOAD>*/
}

//*<RSC>*/
//*</RSC>*/