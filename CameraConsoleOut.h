#pragma once
#include "glut.h"
#include "Include\glut.h"

#define _USE_MATH_DEFINES
class CameraConsoleOut
{
public:
	//xpos, ypos, zpos;
	//xrot, yrot, xrot;
	//angle of rotation
	float xpos = 0, ypos = 0, zpos = 0,
		xrot = 0, yrot = 0, angle = 0.0;
	float positionz[11];
	float positionx[11];

	void AssetInit(void);
	void cubepositions(void);
	void cube(void);
	void camera(void);
	void reshape(int w, int h);
	CameraConsoleOut();
	~CameraConsoleOut();
};

