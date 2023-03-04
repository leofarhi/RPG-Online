#ifndef CAMERA_H
#define CAMERA_H

typedef struct Camera{
	int x; //pixel coordinates (not tile coordinates)
	int y; //pixel coordinates (not tile coordinates)
} Camera;

Camera* new_camera();
void free_camera(Camera* cam);


#endif