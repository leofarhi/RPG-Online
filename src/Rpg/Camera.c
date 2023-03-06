#include "Camera.h"

Camera* new_Camera()
{
    Camera* cam = malloc(sizeof(Camera));
    cam->Position = vector2_create(0, 0);
    return cam;
}
void free_Camera(Camera* cam)
{
    free(cam);
}