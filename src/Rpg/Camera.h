#ifndef CAMERA_H
#define CAMERA_H
#include "../ParticuleEngine/ParticuleEngine.h"

typedef struct Camera{
	Vector2 Position; //pixel coordinates (not tile coordinates)
} Camera;

Camera* new_Camera();
void free_Camera(Camera* cam);


#endif